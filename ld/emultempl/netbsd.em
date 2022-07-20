# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

LDEMUL_BEFORE_PARSE=gldnetbsd_before_parse

fragment <<EOF
static void
gld${EMULATION_NAME}_before_parse (void);

static void
gldnetbsd_before_parse (void)
{
  gld${EMULATION_NAME}_before_parse ();
  link_info.common_skip_ar_symbols = bfd_link_common_skip_text;
}
EOF
