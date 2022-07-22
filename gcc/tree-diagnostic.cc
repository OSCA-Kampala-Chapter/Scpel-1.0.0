/* Language-independent diagnostic subroutines for the GNU Compiler
   Collection that are only for use in the compilers proper and not
   the driver or other programs.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tree.h"
#include "diagnostic.h"
#include "tree-pretty-print.h"
#include "gimple-pretty-print.h"
#include "tree-diagnostic.h"
#include "diagnostic-client-data-hooks.h"
#include "langhooks.h"
#include "intl.h"

/* Prints out, if necessary, the name of the current function
   that caused an error.  Called from all error and warning functions.  */
void
diagnostic_report_current_function (diagnostic_context *context, diagnostic_info *diagnostic)
{
  location_t loc = diagnostic_location (diagnostic);
  diagnostic_report_current_module (context, loc);
  lang_hooks.print_error_function (context, LOCATION_FILE (loc), diagnostic);
}

static void
default_tree_diagnostic_starter (diagnostic_context *context,
				 diagnostic_info *diagnostic)
{
  diagnostic_report_current_function (context, diagnostic);
  pp_set_prefix (context->printer, diagnostic_build_prefix (context,
							    diagnostic));
}

/* This is a pair made of a location and the line map it originated
   from.  It's used in the maybe_unwind_expanded_macro_loc function
   below.  */
struct loc_map_pair
{
  const line_map_macro *map;
  location_t where;
};


/* Unwind the different macro expansions that lead to the token which
   location is WHERE and emit diagnostics showing the resulting
   unwound macro expansion trace.  Let's look at an example to see how
   the trace looks like.  Suppose we have this piece of code,
   artificially annotated with the line numbers to increase
   legibility:

    $ cat -n test.c
      1    #define OPERATE(OPRD1, OPRT, OPRD2) \
      2      OPRD1 OPRT OPRD2;
      3
      4    #define SHIFTL(A,B) \
      5      OPERATE (A,<<,B)
      6
      7    #define MULT(A) \
      8      SHIFTL (A,1)
      9
     10    void
     11    g ()
     12    {
     13      MULT (1.0);// 1.0 << 1; <-- so this is an error.
     14    }

   Here is the diagnostic that we want the compiler to generate:

    test.c: In function ‘g’:
    test.c:5:14: error: invalid operands to binary << (have ‘double’ and ‘int’)
    test.c:2:9: note: in definition of macro 'OPERATE'
    test.c:8:3: note: in expansion of macro 'SHIFTL'
    test.c:13:3: note: in expansion of macro 'MULT'

   The part that goes from the third to the fifth line of this
   diagnostic (the lines containing the 'note:' string) is called the
   unwound macro expansion trace.  That's the part generated by this
   function.  */

void
maybe_unwind_expanded_macro_loc (diagnostic_context *context,
                                 location_t where)
{
  const struct line_map *map;
  auto_vec<loc_map_pair> loc_vec;
  unsigned ix;
  loc_map_pair loc, *iter;

  const location_t original_loc = where;

  map = linemap_lookup (line_table, where);
  if (!linemap_macro_expansion_map_p (map))
    return;

  /* Let's unwind the macros that got expanded and led to the token
     which location is WHERE.  We are going to store these macros into
     LOC_VEC, so that we can later walk it at our convenience to
     display a somewhat meaningful trace of the macro expansion
     history to the user.  Note that the first macro of the trace
     (which is OPERATE in the example above) is going to be stored at
     the beginning of LOC_VEC.  */

  do
    {
      loc.where = where;
      loc.map = linemap_check_macro (map);

      loc_vec.safe_push (loc);

      /* WHERE is the location of a token inside the expansion of a
         macro.  MAP is the map holding the locations of that macro
         expansion.  Let's get the location of the token inside the
         context that triggered the expansion of this macro.
         This is basically how we go "down" in the trace of macro
         expansions that led to WHERE.  */
      where = linemap_unwind_toward_expansion (line_table, where, &map);
    } while (linemap_macro_expansion_map_p (map));

  /* Now map is set to the map of the location in the source that
     first triggered the macro expansion.  This must be an ordinary map.  */
  const line_map_ordinary *ord_map = linemap_check_ordinary (map);

  /* Walk LOC_VEC and print the macro expansion trace, unless the
     first macro which expansion triggered this trace was expanded
     inside a system header.  */
  int saved_location_line =
    expand_location_to_spelling_point (original_loc).line;

  if (!LINEMAP_SYSP (ord_map))
    FOR_EACH_VEC_ELT (loc_vec, ix, iter)
      {
	/* Sometimes, in the unwound macro expansion trace, we want to
	   print a part of the context that shows where, in the
	   definition of the relevant macro, is the token (we are
	   looking at) used.  That is the case in the introductory
	   comment of this function, where we print:

	       test.c:2:9: note: in definition of macro 'OPERATE'.

	   We print that "macro definition context" because the
	   diagnostic line (emitted by the call to
	   pp_ouput_formatted_text in diagnostic_report_diagnostic):

	       test.c:5:14: error: invalid operands to binary << (have ‘double’ and ‘int’)

	   does not point into the definition of the macro where the
	   token '<<' (that is an argument to the function-like macro
	   OPERATE) is used.  So we must "display" the line of that
	   macro definition context to the user somehow.

	   A contrario, when the first interesting diagnostic line
	   points into the definition of the macro, we don't need to
	   display any line for that macro definition in the trace
	   anymore, otherwise it'd be redundant.  */

        /* Okay, now here is what we want.  For each token resulting
           from macro expansion we want to show: 1/ where in the
           definition of the macro the token comes from; 2/ where the
           macro got expanded.  */

        /* Resolve the location iter->where into the locus 1/ of the
           comment above.  */
        location_t resolved_def_loc =
          linemap_resolve_location (line_table, iter->where,
                                    LRK_MACRO_DEFINITION_LOCATION, NULL);

	/* Don't print trace for locations that are reserved or from
	   within a system header.  */
        const line_map_ordinary *m = NULL;
        location_t l = 
          linemap_resolve_location (line_table, resolved_def_loc,
                                    LRK_SPELLING_LOCATION,  &m);
        if (l < RESERVED_LOCATION_COUNT || LINEMAP_SYSP (m))
          continue;
        
	/* We need to print the context of the macro definition only
	   when the locus of the first displayed diagnostic (displayed
	   before this trace) was inside the definition of the
	   macro.  */
        int resolved_def_loc_line = SOURCE_LINE (m, l);
        if (ix == 0 && saved_location_line != resolved_def_loc_line)
          {
            diagnostic_append_note (context, resolved_def_loc, 
                                    "in definition of macro %qs",
                                    linemap_map_get_macro_name (iter->map));
            /* At this step, as we've printed the context of the macro
               definition, we don't want to print the context of its
               expansion, otherwise, it'd be redundant.  */
            continue;
          }

        /* Resolve the location of the expansion point of the macro
           which expansion gave the token represented by def_loc.
           This is the locus 2/ of the earlier comment.  */
        location_t resolved_exp_loc =
          linemap_resolve_location (line_table,
                                    MACRO_MAP_EXPANSION_POINT_LOCATION (iter->map),
                                    LRK_MACRO_DEFINITION_LOCATION, NULL);

        diagnostic_append_note (context, resolved_exp_loc, 
                                "in expansion of macro %qs",
                                linemap_map_get_macro_name (iter->map));
      }
}

/*  This is a diagnostic finalizer implementation that is aware of
    virtual locations produced by libcpp.

    It has to be called by the diagnostic finalizer of front ends that
    uses libcpp and wish to get diagnostics involving tokens resulting
    from macro expansion.

    For a given location, if said location belongs to a token
    resulting from a macro expansion, this starter prints the context
    of the token.  E.g, for multiply nested macro expansion, it
    unwinds the nested macro expansions and prints them in a manner
    that is similar to what is done for function call stacks, or
    template instantiation contexts.  */
void
virt_loc_aware_diagnostic_finalizer (diagnostic_context *context,
				     diagnostic_info *diagnostic)
{
  maybe_unwind_expanded_macro_loc (context, diagnostic_location (diagnostic));
}

/* Default tree printer.   Handles declarations only.  */
bool
default_tree_printer (pretty_printer *pp, text_info *text, const char *spec,
		      int precision, bool wide, bool set_locus, bool hash,
		      bool *, const char **)
{
  tree t;

  /* FUTURE: %+x should set the locus.  */
  if (precision != 0 || wide || hash)
    return false;

  switch (*spec)
    {
    case 'E':
      t = va_arg (*text->args_ptr, tree);
      if (TREE_CODE (t) == IDENTIFIER_NODE)
	{
	  pp_identifier (pp, IDENTIFIER_POINTER (t));
	  return true;
	}
      break;

    case 'D':
      t = va_arg (*text->args_ptr, tree);
      if (VAR_P (t) && DECL_HAS_DEBUG_EXPR_P (t))
	t = DECL_DEBUG_EXPR (t);
      break;

    case 'F':
    case 'T':
      t = va_arg (*text->args_ptr, tree);
      break;

    default:
      return false;
    }

  if (set_locus)
    text->set_location (0, DECL_SOURCE_LOCATION (t), SHOW_RANGE_WITH_CARET);

  if (DECL_P (t))
    {
      const char *n = DECL_NAME (t)
        ? identifier_to_locale (lang_hooks.decl_printable_name (t, 2))
        : _("<anonymous>");
      pp_string (pp, n);
    }
  else
    dump_generic_node (pp, t, 0, TDF_SLIM, 0);

  return true;
}

/* Set the locations of call sites along the inlining stack corresponding
   to the DIAGNOSTIC location.  */

static void
set_inlining_locations (diagnostic_context *,
			diagnostic_info *diagnostic)
{
  location_t loc = diagnostic_location (diagnostic);
  tree block = LOCATION_BLOCK (loc);

  /* Count the number of locations in system headers.  When all are,
     warnings are suppressed by -Wno-system-headers.  Otherwise, they
     involve some user code, possibly inlined into a function in a system
     header, and are not treated as coming from system headers.  */
  unsigned nsyslocs = 0;

  /* Use a reference to the vector of locations for convenience.  */
  auto &ilocs = diagnostic->m_iinfo.m_ilocs;

  while (block && TREE_CODE (block) == BLOCK
	 && BLOCK_ABSTRACT_ORIGIN (block))
    {
      tree ao = BLOCK_ABSTRACT_ORIGIN (block);
      if (TREE_CODE (ao) == FUNCTION_DECL)
	{
	  if (!diagnostic->m_iinfo.m_ao)
	    diagnostic->m_iinfo.m_ao = block;

	  location_t bsloc = BLOCK_SOURCE_LOCATION (block);
	  ilocs.safe_push (bsloc);
	  if (in_system_header_at (bsloc))
	    ++nsyslocs;
	}
      else if (TREE_CODE (ao) != BLOCK)
	break;

      block = BLOCK_SUPERCONTEXT (block);
    }

  if (ilocs.length ())
    {
      /* When there is an inlining context use the macro expansion
	 location for the original location and bump up NSYSLOCS if
	 it's in a system header since it's not counted above.  */
      location_t sysloc = expansion_point_location_if_in_system_header (loc);
      if (sysloc != loc)
	{
	  loc = sysloc;
	  ++nsyslocs;
	}
    }
  else
    {
      /* When there's no inlining context use the original location
	 and set NSYSLOCS accordingly.  */
      nsyslocs = in_system_header_at (loc) != 0;
    }

  ilocs.safe_push (loc);

  /* Set if all locations are in a system header.  */
  diagnostic->m_iinfo.m_allsyslocs = nsyslocs == ilocs.length ();

  if (tree *ao = pp_ti_abstract_origin (&diagnostic->message))
    *ao = (tree)diagnostic->m_iinfo.m_ao;
}

/* Sets CONTEXT to use language independent diagnostics.  */
void
tree_diagnostics_defaults (diagnostic_context *context)
{
  diagnostic_starter (context) = default_tree_diagnostic_starter;
  diagnostic_finalizer (context) = default_diagnostic_finalizer;
  diagnostic_format_decoder (context) = default_tree_printer;
  context->print_path = default_tree_diagnostic_path_printer;
  context->make_json_for_path = default_tree_make_json_for_path;
  context->set_locations_cb = set_inlining_locations;
  context->m_client_data_hooks = make_compiler_data_hooks ();
}
