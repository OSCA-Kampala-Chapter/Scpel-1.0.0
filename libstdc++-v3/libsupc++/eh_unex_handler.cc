// -*- C++ -*- std::unexpected handler
// Please review $(srcdir/SPL-README) for GNU licencing info.

#include "unwind-cxx.h"

/* The current installed user handler.  */
std::unexpected_handler __cxxabiv1::__unexpected_handler = std::terminate;

