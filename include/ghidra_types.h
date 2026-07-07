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

#include <stdint.h>

typedef uint8_t undefined;
typedef uint8_t undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined3; /* not a real 3-byte type; Ghidra uses this
                               * for misaligned/partial reads - treated
                               * as 4 bytes here, may need a real fix
                               * per call site later. */
typedef uint32_t undefined4;
typedef uint64_t undefined8;
typedef uint8_t byte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long ulong;

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
