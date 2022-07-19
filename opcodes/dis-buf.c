/* Disassemble from a buffer, for GNU.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "sysdep.h"
#include "dis-asm.h"
#include <errno.h>
#include "opintl.h"

/* Get LENGTH bytes from info's buffer, at target address memaddr.
   Transfer them to myaddr.  */
int
buffer_read_memory (bfd_vma memaddr, bfd_byte *myaddr, unsigned int length, struct disassemble_info *info)
{
  unsigned int opb = info->octets_per_byte;
  size_t end_addr_offset = length / opb;
  size_t max_addr_offset = info->buffer_length / opb;
  size_t octets = (memaddr - info->buffer_vma) * opb;

  if (memaddr < info->buffer_vma
      || memaddr - info->buffer_vma > max_addr_offset
      || memaddr - info->buffer_vma + end_addr_offset > max_addr_offset
      || (info->stop_vma && (memaddr >= info->stop_vma
			     || memaddr + end_addr_offset > info->stop_vma)))
    /* Out of bounds.  Use EIO because GDB uses it.  */
    return EIO;
  memcpy (myaddr, info->buffer + octets, length);

  return 0;
}

/* Print an error message.  We can assume that this is in response to
   an error return from buffer_read_memory.  */

void
perror_memory (int status,
	       bfd_vma memaddr,
	       struct disassemble_info *info)
{
  if (status != EIO)
    /* Can't happen.  */
    info->fprintf_func (info->stream, _("Unknown error %d\n"), status);
  else
    {
      char buf[30];

      /* Actually, address between memaddr and memaddr + len was
	 out of bounds.  */
      sprintf_vma (buf, memaddr);
      info->fprintf_func (info->stream,
			  _("Address 0x%s is out of bounds.\n"), buf);
    }
}

/* This could be in a separate file, to save miniscule amounts of space
   in statically linked executables.  */

/* Just print the address is hex.  This is included for completeness even
   though both GDB and objdump provide their own (to print symbolic
   addresses).  */

void
generic_print_address (bfd_vma addr, struct disassemble_info *info)
{
  char buf[30];

  sprintf_vma (buf, addr);
  (*info->fprintf_func) (info->stream, "0x%s", buf);
}

/* Just return NULL.  */

asymbol *
generic_symbol_at_address (bfd_vma addr ATTRIBUTE_UNUSED,
			   struct disassemble_info *info ATTRIBUTE_UNUSED)
{
  return NULL;
}

/* Just return TRUE.  */

bool
generic_symbol_is_valid (asymbol * sym ATTRIBUTE_UNUSED,
			 struct disassemble_info *info ATTRIBUTE_UNUSED)
{
  return true;
}
