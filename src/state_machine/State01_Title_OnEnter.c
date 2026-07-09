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
 * RESOLVED (2026-07-09, via a fresh headless-Ghidra decompile of
 * LoadSpriteSet plus reading the constants out of the binary): the two
 * "mystery" loads are real register arguments - EAX = 0x5572cc =
 * "titlemode.img" (the sprite-set name LoadSpriteSet looks up: it
 * loads that .img and registers one frame object per frame, vtable
 * 0x557524, under the given container key), and EDI = 0x5572c0 =
 * "title.mp3" (passed through to the music path). LoadSpriteSet is
 * indeed callee-cleans on its two stack args (container, key). The
 * remaining byte-diff on this function is exactly those two loads +
 * the edi save/restore, not expressible from C without the custom
 * convention; see src/cxx/State01_Title.cpp for the C++ promotion.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall State01_Title_OnEnter(int param_1)

{
  LoadSpriteSet(&DAT_00ea0e18,10000);
  *(undefined4 *)(param_1 + 4) = 0;
  PlayMusicTrack(0);
  return;
}

