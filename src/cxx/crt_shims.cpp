/* CRT/C++ runtime shims - bridge the raw ports' placeholder symbol
 * names to the real MSVC runtime, so the tree can link against
 * libcmt.lib without editing 270 call sites.
 *
 * Ghidra's decompiler renamed C++ operator new / operator delete to
 * the plain C identifiers `operator_new` / `operator_delete` (a valid
 * C name), which the raw ports call as `_operator_new`. The real
 * runtime exports the mangled `??2@YAPAXI@Z` / `??3@YAXPAX@Z`. These
 * one-line forwarders, compiled as C++ and exported with C linkage,
 * connect the two - a linker shim, not reimplementation. */
#include <stdlib.h>

extern "C" void *operator_new(unsigned int size)
{
    return ::operator new(size);
}

extern "C" void operator_delete(void *p)
{
    ::operator delete(p);
}
