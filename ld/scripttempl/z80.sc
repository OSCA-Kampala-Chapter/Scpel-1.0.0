# Please review $(srcdir/SPL-README) for GNU licencing info.

if test "${OUTPUT_FORMAT}" = "elf32-z80"; then
  NO_REL_RELOCS=1
  NO_RELA_RELOCS=1
  NO_SMALL_DATA=1
  EMBEDDED=1
  ALIGNMENT=1
  . $srcdir/scripttempl/elf.sc
  return 0
fi

cat << EOF
/* Please review $(srcdir/SPL-README) for GNU licencing info. */

OUTPUT_FORMAT("${OUTPUT_FORMAT}")
OUTPUT_ARCH("${ARCH}")
SECTIONS
{
.isr :	{
	${RELOCATING+ __Labs = .;}
	*(.isr)
	*(isr)
	${RELOCATING+ __Habs = .;}
	}
.text :	{
	${RELOCATING+ __Ltext = .;}
	*(.text)
	*(text)
	${RELOCATING+ __Htext = .;}
	}
.data :	{
	${RELOCATING+ __Ldata = .;}
	*(.data)
	*(data)
	${RELOCATING+ __Hdata = .;}
	}
.bss :	{
	${RELOCATING+ __Lbss = .;}
	*(.bss)
	*(bss)
	${RELOCATING+ __Hbss = .;}
	}
}
EOF
