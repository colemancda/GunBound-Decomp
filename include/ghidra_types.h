/* Compatibility typedefs for raw Ghidra decompiler output.
 *
 * Many functions under src/ are ported close to verbatim from Ghidra's
 * decompiler (see src/README.md's "Raw/verbatim ports" section) rather
 * than hand-cleaned - these typedefs let that output compile without
 * touching every individual `undefinedN`/`code`/`byte` occurrence.
 * Sizes match Ghidra's own conventions (undefinedN = N-byte blob of
 * unspecified signedness).
 */
#ifndef GB_GHIDRA_TYPES_H
#define GB_GHIDRA_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>

/* Ghidra emits Windows/CRT struct *tag* names bare (no `struct` keyword,
 * as C++ allows implicitly) even where only the tag - not a typedef of
 * the same name - exists. These re-expose the tag names as typedefs so
 * that verbatim-ported code compiles as plain C without editing every
 * call site. `_RTL_CRITICAL_SECTION`'s real Win32 typedef is
 * CRITICAL_SECTION; the rest are genuinely-bare tag names. */
typedef MSG tagMSG;
typedef WIN32_FIND_DATAA _WIN32_FIND_DATAA;
typedef struct tm tm;
typedef struct sockaddr sockaddr;
typedef CRITICAL_SECTION _RTL_CRITICAL_SECTION;
typedef FILETIME _FILETIME;
typedef struct hostent hostent;

typedef uint8_t undefined;
typedef uint8_t undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined3; /* not a real 3-byte type; Ghidra uses this
                               * for misaligned/partial reads - treated
                               * as 4 bytes here, may need a real fix
                               * per call site later. */
typedef uint32_t undefined4;
typedef uint64_t undefined8;
typedef uint32_t uint3;  /* same "not really 3 bytes" caveat as undefined3 */
typedef int32_t int3;
typedef uint8_t byte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef long long longlong;

/* Ghidra's placeholder type for "this is a code/function pointer" in
 * expressions like `(**(code **)(vtable + N))(...)`. void works because
 * only its address/call syntax is ever used, never its size. */
typedef void code;

/* MSVC calling-convention keywords Ghidra emits that GCC/Clang don't
 * recognize the same way on x86-64 (where the distinction is moot -
 * there's one calling convention). Defined away rather than requiring
 * per-file edits; revisit if a 32-bit x86 build ever needs the real
 * attributes back. */
#ifndef __thiscall
#define __thiscall
#endif
#ifndef __fastcall
#define __fastcall
#endif
#ifndef __cdecl
#define __cdecl
#endif

#endif
