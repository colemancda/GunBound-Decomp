/* State01_Title_OnEnter - 0x004e5370 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * Real-MSVC byte-comparison done on this function (see
 * tools/msvc-env/README.md for the pipeline): compiled with /O2 and
 * disassembled against the original's 49 bytes at 0x4e5370.
 * Structurally near-identical after fixing a real project-wide bug
 * this comparison found - include/ghidra_types.h was erasing
 * __fastcall unconditionally, including under real MSVC (where it's a
 * meaningful keyword, not just a Ghidra-ism), silently turning every
 * __fastcall-declared function's real build into __cdecl. Fixed there;
 * this function's object code now correctly receives param_1 via ECX
 * (symbol decorated `@State01_Title_OnEnter@4`, matching fastcall's
 * mangling) instead of a stack argument.
 *
 * Two residual differences, not yet resolved: the original also saves/
 * restores edi and loads two extra constants (`mov eax,0x5572cc`,
 * `mov edi,0x5572c0`) this function's own decompilation doesn't show;
 * and the original never cleans the stack after its call to
 * FUN_004f1790 (no `add esp,8`), while a normal __cdecl call would.
 * That strongly suggests FUN_004f1790 is actually callee-cleans-stack
 * (__stdcall or __fastcall, not __cdecl as currently declared) and
 * probably takes more real parameters than the 2 modeled here - the
 * two mystery constant loads are plausible candidates for extra
 * arguments. Not investigated further this pass; a real fix needs
 * FUN_004f1790 itself decompiled and byte-compared the same way.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall State01_Title_OnEnter(int param_1)

{
  FUN_004f1790(&DAT_00ea0e18,10000);
  *(undefined4 *)(param_1 + 4) = 0;
  FUN_004eea30(0);
  return;
}

