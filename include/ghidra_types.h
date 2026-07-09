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
#include <ddraw.h>
#include <d3d.h>
#include <imm.h>

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
typedef OSVERSIONINFOA _OSVERSIONINFOA;
/* imm.h's COMPOSITIONFORM tag; WIN32_LEAN_AND_MEAN keeps windows.h
 * from pulling imm.h in, so include it explicitly for the typedef. */
typedef COMPOSITIONFORM tagCOMPOSITIONFORM;
typedef struct hostent hostent;
/* MSVC CRT's C++ `exception` class, referenced by a couple of raw-
 * ported functions. `char`, not an opaque struct: Ghidra sizes
 * unknown classes as 1 byte, so raw ports do byte-offset arithmetic
 * (`param_1 + 0x24`) and 1-byte stores (`param_1[0x10] =
 * (exception)0x0`) straight through `exception *`, which needs a
 * complete 1-byte type to parse. Real layout still unknown/unneeded.
 * Its ctor/dtor call sites (`exception::exception` /
 * `exception::~exception` in Ghidra) are renamed exception__ctor /
 * exception__dtor - `::` isn't C. */
typedef char exception;
/* ATL's CAtlBaseModule class - opaque, only ever a cast pointer type.
 * Ghidra's ATL::CAtlBaseModule::GetHInstanceAt call sites are renamed
 * ATL_CAtlBaseModule_GetHInstanceAt (:: is not C); the real body lives
 * in the excluded msvc_crt_atl tree. */
typedef struct CAtlBaseModule CAtlBaseModule;
HMODULE ATL_CAtlBaseModule_GetHInstanceAt();
exception * exception__ctor();
void exception__dtor();
/* Ghidra types registry-API results as LSTATUS, a typedef newer
 * Windows SDKs added to winreg.h; MSVC 7.1's Platform SDK predates it.
 * Same underlying type (LONG) as the RegXxx return values. */
typedef LONG LSTATUS;

/* Ghidra infers `__time32_t` (the 32-bit time_t used by later MSVC
 * CRTs, once the 32/64-bit time_t split existed) for `time()` call
 * sites, even though this project's actual target - MSVC 7.1 (Visual
 * C++ Toolkit 2003), confirmed via tools/msvc-env/ - predates that
 * split and has no such type in its own <time.h>. `FID_conflict___time32`
 * is Ghidra's renamed CRT `_time32`/`time()` implementation (real body
 * in the excluded src/unnamed/msvc_crt_atl/ tree, never actually
 * linkable) - redirected to the real libc `time()` here instead, which
 * is what it always was under the hood. Found via a real-MSVC compile
 * sweep of src/state_machine/ (12 files use one or both of these). */
typedef long __time32_t;
#define FID_conflict___time32(p) time((time_t *)(p))

/* Ghidra's type for the x87 80-bit extended-precision format (FLD
 * TBYTE etc.). MSVC's long double is really 64-bit, but these raw
 * ports only need the arithmetic to parse/compile; exact x87
 * semantics are a hand-verification concern. */
typedef long double float10;

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
typedef int8_t sbyte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef long long longlong;

/* Ghidra's placeholder type for "this is a code/function pointer" in
 * expressions like `(**(code **)(vtable + N))(...)`. Must be a real
 * function type, not `void` - `code **` dereferenced twice needs to
 * yield something callable. A plain `void` typedef looks equivalent at
 * a glance (both untyped/sizeless) but silently breaks every call
 * site: `**(void **)x` is a `void` value, and calling a `void` value is
 * a hard error, not just a warning.
 *
 * Deliberately `code()`, the classic K&R "unspecified argument count/
 * types" form, not `code(void)`. The latter looked more "correct" (an
 * explicit empty parameter list) but is actually a real C prototype
 * that strictly takes zero arguments - call sites with real arguments
 * then fail with "too many arguments to function", since these vtable
 * calls have every different signature depending on which slot's being
 * invoked. `code()` imposes no such constraint.
 *
 * Returns `int`, not `void`: Ghidra freely assigns/casts these calls'
 * results (`iVar4 = (**(code **)...)();`), and MSVC 7.1 makes using a
 * void call result a hard error (C2120 "'void' illegal with all
 * types", C2069 "cast of 'void' term to non-'void'"). An int return
 * keeps every such site legal C while call sites that ignore the
 * result are unaffected. */
typedef int code();

/* Ghidra's `X._<off>_<size>_` storage-subfield notation (a <size>-byte
 * access at byte offset <off> into X's storage) isn't C. Raw-ported
 * call sites are rewritten as SUBFIELD(X, <off>, undefined<size>),
 * which is a real lvalue usable for both reads and writes. The 3-byte
 * case inherits the undefined3 typedef's documented caveat: it really
 * touches 4 bytes, which may need a per-site fix once a function gets
 * hand-verified. */
#define SUBFIELD(x, off, ty) (*(ty *)((uint8_t *)&(x) + (off)))

/* MSVC calling-convention keywords Ghidra emits that GCC/Clang don't
 * recognize the same way on x86-64 (where the distinction is moot -
 * there's one calling convention). Defined away rather than requiring
 * per-file edits - but ONLY for non-MSVC compilers, and only
 * __fastcall/__cdecl even then. Real MSVC (used for true byte-matching
 * builds against a real 32-bit x86 target - see tools/msvc-env/)
 * understands these as first-class keywords that genuinely affect
 * codegen (register- vs. stack-passed arguments); erasing them there
 * was a real, previously-undetected bug - confirmed via a real
 * compile-and-disassemble comparison of State01_Title_OnEnter
 * (declared __fastcall) that silently produced cdecl-convention object
 * code (stack-passed args at [ebp+8]) instead of fastcall's ECX-passed
 * first argument, because this block erased the keyword
 * unconditionally.
 *
 * __thiscall stays erased even under real MSVC, for a different
 * reason: it's a C++-only keyword there ("nonstandard extension...
 * reserved for future use" - a hard error, not a warning - in MSVC's C
 * mode), and this whole tree compiles as plain C. functions.h declares
 * many __thiscall functions (Ghidra's guess that they're C++ member
 * functions in the original binary, `this` passed as the first
 * parameter), so erasing __thiscall is required just to make any
 * single file's #include chain compile under real MSVC at all - a
 * known, real accuracy gap for those specific functions (their true
 * calling convention won't byte-match until this is solved some other
 * way, e.g. compiling as C++ instead) rather than something fixed
 * here. */
#ifndef __thiscall
#define __thiscall
#endif
#ifndef _MSC_VER
#ifndef __fastcall
#define __fastcall
#endif
#ifndef __cdecl
#define __cdecl
#endif
#endif

/* Every raw-ported .c file includes this header first, so pull in the
 * DAT_<address>/g_* global declarations here too rather than adding a
 * second #include to every one of those files. */
#include "globals.h"

/* Same reasoning as globals.h, but for cross-file function calls -
 * see include/functions.h's own header comment. */
#include "functions.h"

#endif
