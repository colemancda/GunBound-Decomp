/* ResolveObjectHandle - 0x00461c60 in the original binary.
 *
 * BRING-UP BYPASS (stubbed to a no-op): looks up a named entry (needle
 * string) in a table hanging off param_1+0x1c, via FindStringNoCase,
 * and records the match index / found-flag at param_1+0x24/+0x20/+0x34.
 *
 * The current signature is wrong: orig 0x461c60-0x461c6c shows
 * `mov esi, ecx` (this = ECX, i.e. __thiscall, not __fastcall) then
 * `mov ebx, [esp+0x10]` for the needle string - so this actually takes
 * TWO arguments (this, needle), with `this` entirely missing from both
 * this declaration and its sole caller (ChangeGameState.c). Recovering
 * `this` requires tracing what object sits at ECX across that whole
 * ChangeGameState call sequence (interacting with the equally-dropped
 * FindPreloadedTextureByName/g_cursorTexture "animated cursor object at
 * 0x7a7644" chain already documented in globals.h) - out of scope for
 * this bring-up pass. Not required for the server-list path: this is
 * mouse-cursor sprite/animation setup, purely cosmetic.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall ResolveObjectHandle(int param_1)

{
  (void)param_1;
  return;
}

