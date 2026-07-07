/* Minimal <stdint.h> shim for building under period-correct MSVC 7.1
 * (Visual C++ Toolkit 2003) - Microsoft didn't ship a real <stdint.h>
 * until VS2010, but MSVC's own built-in integer types are fixed-width
 * on the x86 target this project builds for, so plain typedefs are
 * enough (no <limits.h>-based portability dance needed).
 *
 * Only covers what this project's own headers actually use
 * (lzhuf_internal.h, include/lzhuf.h, include/ghidra_types.h) - not a
 * general-purpose stdint.h replacement.
 *
 * Include path ordering matters: this directory must come before
 * include/ on the command line (/I include/msvc /I include) so this
 * shim is found instead of failing to locate a real <stdint.h>. Only
 * relevant for the MSVC 7.1 build - winelib/gcc already has a real
 * <stdint.h> and never sees this file.
 */
#ifndef GB_MSVC_STDINT_SHIM_H
#define GB_MSVC_STDINT_SHIM_H

typedef signed char        int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef __int64              int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned __int64     uint64_t;

#endif
