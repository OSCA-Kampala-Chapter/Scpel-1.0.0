/* Modeling API uses and misuses via state machines.
   Please review: $(src-dir)/SPL-README for Licencing info. */

#ifndef GCC_ANALYZER_SM_H
#define GCC_ANALYZER_SM_H

/* Utility functions for use by state machines.  */

namespace ana {

class state_machine;
class sm_context;
class pending_diagnostic;

extern bool any_pointer_p (tree expr);
extern bool any_pointer_p (const svalue *sval);

/* An abstract base class for a state machine describing an API.
   Manages a set of state objects, and has various virtual functions
   for pattern-matching on statements.  */

class state_machine : public log_user
{
public:
  /* States are represented by immutable objects, owned by the state
     machine.  */
  class state
  {
  public:
    state (const char *name, unsigned id) : m_name (name), m_id (id) {}
    virtual ~state () {}

    const char *get_name () const { return m_name; }
    virtual void dump_to_pp (pretty_printer *pp) const;
    virtual json::value *to_json () const;

    unsigned get_id () const { return m_id; }

  private:
    const char *m_name;
    unsigned m_id;
  };
  typedef const state_machine::state *state_t;

  state_machine (const char *name, logger *logger);
  virtual ~state_machine () {}

  /* Should states be inherited from a parent region to a child region,
     when first accessing a child region?
     For example we should inherit the taintedness of a subregion,
     but we should not inherit the "malloc:non-null" state of a field
     within a heap-allocated struct.  */
  virtual bool inherited_state_p () const = 0;

  /* A vfunc for more general handling of inheritance.  */
  virtual state_t
  alt_get_inherited_state (const sm_state_map &,
			   const svalue *,
			   const extrinsic_state &) const
  {
    return NULL;
  }

  virtual state_machine::state_t get_default_state (const svalue *) const
  {
    return m_start;
  }

  const char *get_name () const { return m_name; }

  state_t get_state_by_name (const char *name) const;

  /* Return true if STMT is a function call recognized by this sm.  */
  virtual bool on_stmt (sm_context *sm_ctxt,
			const supernode *node,
			const gimple *stmt) const = 0;

  virtual void on_phi (sm_context *sm_ctxt ATTRIBUTE_UNUSED,
		       const supernode *node ATTRIBUTE_UNUSED,
		       const gphi *phi ATTRIBUTE_UNUSED,
		       tree rhs ATTRIBUTE_UNUSED) const
  {
  }

  virtual void on_condition (sm_context *sm_ctxt ATTRIBUTE_UNUSED,
			     const supernode *node ATTRIBUTE_UNUSED,
			     const gimple *stmt ATTRIBUTE_UNUSED,
			     const svalue *lhs ATTRIBUTE_UNUSED,
			     enum tree_code op ATTRIBUTE_UNUSED,
			     const svalue *rhs ATTRIBUTE_UNUSED) const
  {
  }

  /* Return true if it safe to discard the given state (to help
     when simplifying state objects).
     States that need leak detection should return false.  */
  virtual bool can_purge_p (state_t s) const = 0;

  /* Called when VAR leaks (and !can_purge_p).  */
  virtual pending_diagnostic *on_leak (tree var ATTRIBUTE_UNUSED) const
  {
    return NULL;
  }

  /* Return true if S should be reset to "start" for values passed (or reachable
     from) calls to unknown functions.  IS_MUTABLE is true for pointers as
     non-const, false if only passed as const-pointers.

     For example, in sm-malloc.cc, an on-stack ptr doesn't stop being
     stack-allocated when passed to an unknown fn, but a malloc-ed pointer
     could be freed when passed to an unknown fn (unless passed as "const").  */
  virtual bool reset_when_passed_to_unknown_fn_p (state_t s ATTRIBUTE_UNUSED,
						  bool is_mutable) const
  {
    return is_mutable;
  }

  void validate (state_t s) const;

  void dump_to_pp (pretty_printer *pp) const;

  json::object *to_json () const;

  state_t get_start_state () const { return m_start; }

protected:
  state_t add_state (const char *name);
  state_t add_custom_state (state *s)
  {
    m_states.safe_push (s);
    return s;
  }

  unsigned alloc_state_id () { return m_next_state_id++; }

private:
  DISABLE_COPY_AND_ASSIGN (state_machine);

  const char *m_name;

  /* States are owned by the state_machine.  */
  auto_delete_vec<state> m_states;

  unsigned m_next_state_id;

protected:
  /* Must be inited after m_next_state_id.  */
  state_t m_start;
};

/* Abstract base class for state machines to pass to
   sm_context::on_custom_transition for handling non-standard transitions
   (e.g. adding a node and edge to simulate registering a callback and having
   the callback be called later).  */

class custom_transition
{
public:
  virtual ~custom_transition () {}
  virtual void impl_transition (exploded_graph *eg,
				exploded_node *src_enode,
				int sm_idx) = 0;
};

/* Abstract base class giving an interface for the state machine to call
   the checker engine, at a particular stmt.  */

class sm_context
{
public:
  virtual ~sm_context () {}

  /* Get the fndecl used at call, or NULL_TREE.
     Use in preference to gimple_call_fndecl (and gimple_call_addr_fndecl),
     since it can look through function pointer assignments and
     other callback handling.  */
  virtual tree get_fndecl_for_call (const gcall *call) = 0;

  /* Get the old state of VAR at STMT.  */
  virtual state_machine::state_t get_state (const gimple *stmt,
					    tree var) = 0;
  virtual state_machine::state_t get_state (const gimple *stmt,
					    const svalue *) = 0;
  /* Set the next state of VAR to be TO, recording the "origin" of the
     state as ORIGIN.
     Use STMT for location information.  */
  virtual void set_next_state (const gimple *stmt,
			       tree var,
			       state_machine::state_t to,
			       tree origin = NULL_TREE) = 0;
  virtual void set_next_state (const gimple *stmt,
			       const svalue *var,
			       state_machine::state_t to,
			       tree origin = NULL_TREE) = 0;

  /* Called by state_machine in response to pattern matches:
     if VAR is in state FROM, transition it to state TO, potentially
     recording the "origin" of the state as ORIGIN.
     Use NODE and STMT for location information.  */
  void on_transition (const supernode *node ATTRIBUTE_UNUSED,
		      const gimple *stmt,
		      tree var,
		      state_machine::state_t from,
		      state_machine::state_t to,
		      tree origin = NULL_TREE)
  {
    state_machine::state_t current = get_state (stmt, var);
    if (current == from)
      set_next_state (stmt, var, to, origin);
  }

  void on_transition (const supernode *node ATTRIBUTE_UNUSED,
		      const gimple *stmt,
		      const svalue *var,
		      state_machine::state_t from,
		      state_machine::state_t to,
		      tree origin = NULL_TREE)
  {
    state_machine::state_t current = get_state (stmt, var);
    if (current == from)
      set_next_state (stmt, var, to, origin);
  }

  /* Called by state_machine in response to pattern matches:
     issue a diagnostic D using NODE and STMT for location information.  */
  virtual void warn (const supernode *node, const gimple *stmt,
		     tree var, pending_diagnostic *d) = 0;
  virtual void warn (const supernode *node, const gimple *stmt,
		     const svalue *var, pending_diagnostic *d) = 0;

  /* For use when generating trees when creating pending_diagnostics, so that
     rather than e.g.
       "double-free of '<unknown>'"
     we can print:
       "double-free of 'inbuf.data'".  */
  virtual tree get_diagnostic_tree (tree expr)
  {
    return expr;
  }
  virtual tree get_diagnostic_tree (const svalue *) = 0;

  virtual state_machine::state_t get_global_state () const = 0;
  virtual void set_global_state (state_machine::state_t) = 0;

  /* A vfunc for handling custom transitions, such as when registering
     a signal handler.  */
  virtual void on_custom_transition (custom_transition *transition) = 0;

  /* If STMT is an assignment known to assign zero to its LHS, return
     the LHS.
     Otherwise return NULL_TREE.  */
  virtual tree is_zero_assignment (const gimple *stmt) = 0;

  virtual path_context *get_path_context () const
  {
    return NULL;
  }

  /* Are we handling an external function with unknown side effects?  */
  virtual bool unknown_side_effects_p () const { return false; }

  virtual const program_state *get_old_program_state () const = 0;
  virtual const program_state *get_new_program_state () const = 0;

protected:
  sm_context (int sm_idx, const state_machine &sm)
  : m_sm_idx (sm_idx), m_sm (sm) {}

  int m_sm_idx;
  const state_machine &m_sm;
};


/* The various state_machine subclasses are hidden in their respective
   implementation files.  */

extern void make_checkers (auto_delete_vec <state_machine> &out,
			   logger *logger);

extern state_machine *make_malloc_state_machine (logger *logger);
extern state_machine *make_fileptr_state_machine (logger *logger);
extern state_machine *make_taint_state_machine (logger *logger);
extern state_machine *make_sensitive_state_machine (logger *logger);
extern state_machine *make_signal_state_machine (logger *logger);
extern state_machine *make_pattern_test_state_machine (logger *logger);
extern state_machine *make_va_list_state_machine (logger *logger);

} // namespace ana

#endif /* GCC_ANALYZER_SM_H */
