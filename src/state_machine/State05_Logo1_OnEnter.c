/* State05_Logo1_OnEnter - 0x004433f0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall State05_Logo1_OnEnter(int param_1)

{
  LoadSpriteSet(&DAT_00ea0e18,10000);
  *(undefined4 *)(param_1 + 4) = 0;
  PlayMusicTrack(0);
  return;
}

