/* LTO declarations.
   Please review: $(src-dir)/SPL-README for Licencing info. */

#ifndef LTO_H
#define LTO_H


/* A file.  */
struct lto_file
{
  /* The name of the file.  */
  const char *filename;
  /* The offset for the object inside an ar archive file (or zero).  */
  off_t offset;
};

/* In lto-lang.cc  */
extern const char *resolution_file_name;

/* In lto.cc  */
extern tree lto_eh_personality (void);
extern void lto_main (void);
extern void lto_read_all_file_options (void);

/* In lto-elf.c or lto-coff.c  */
extern lto_file *lto_obj_file_open (const char *filename, bool writable);
extern void lto_obj_file_close (lto_file *file);
struct lto_section_list;
extern htab_t lto_obj_build_section_table (lto_file *file, struct lto_section_list *list);
extern htab_t lto_obj_create_section_hash_table (void);
extern void lto_obj_begin_section (const char *name);
extern void lto_obj_append_data (const void *data, size_t len, void *block);
extern void lto_obj_end_section (void);
extern lto_file *lto_set_current_out_file (lto_file *file);
extern lto_file *lto_get_current_out_file (void);

extern int lto_link_dump_id, decl_merge_dump_id, partition_dump_id;

/* Hash table entry to hold the start offset and length of an LTO
   section in a .o file.  */
struct lto_section_slot
{
  const char *name;
  intptr_t start;
  size_t len;
  struct lto_section_slot *next;
};

/* A list of section slots */
struct lto_section_list
{
  struct lto_section_slot *first, *last;
};

extern unsigned int lto_option_lang_mask (void);

#endif /* LTO_H */
