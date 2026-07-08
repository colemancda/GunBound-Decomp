/* Minimal <stdbool.h> shim for building under period-correct MSVC 7.1
 * (Visual C++ Toolkit 2003) - Microsoft didn't ship <stdbool.h> until
 * VS2013 (C99 keywords). MSVC 7.1 has no native _Bool, so this falls
 * back to int, matching what the original compiler would have produced
 * for any hand-written C source using these macros (Ghidra's decompiler
 * output uses plain int/char for booleans anyway - this only exists so
 * ghidra_types.h's #include <stdbool.h> resolves).
 */
#ifndef GB_MSVC_STDBOOL_SHIM_H
#define GB_MSVC_STDBOOL_SHIM_H

#define bool int
#define true 1
#define false 0
#define __bool_true_false_are_defined 1

#endif
