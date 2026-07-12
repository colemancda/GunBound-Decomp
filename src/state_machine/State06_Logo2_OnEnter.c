/* State06_Logo2_OnEnter - 0x00443280 in the original binary.
 *
 * LoadSpriteSet's 3rd arg (the sprite-set name) arrives via EAX (a
 * dropped register, matching its own file's documented "imgName...
 * arrived in EAX" note) - orig 0x44328c: `mov eax, 0x55557c` ->
 * "logomode2.img" (confirmed against src/cxx/State06_Logo2.cpp's own
 * header comment and State05_Logo1.cpp's already-correct sibling call
 * with "logomode.img"). Was silently dropped, leaving LoadSpriteSet
 * called with only 2 of its 3 arguments - the missing 3rd argument's
 * slot got read as garbage/whatever was in that register, which is
 * what caused the crash chased through this session's ddraw-clipper
 * investigation (LoadSpriteSet's internal FindXFSEntry/ReadXFSEntry
 * chain reading a garbage imgName pointer).
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


void __fastcall State06_Logo2_OnEnter(int param_1)

{
  LoadSpriteSet(&DAT_00ea0e18,10000,"logomode2.img");
  *(undefined4 *)(param_1 + 4) = 0;
  PlayMusicTrack(0,"logo2.mp3");
  return;
}

