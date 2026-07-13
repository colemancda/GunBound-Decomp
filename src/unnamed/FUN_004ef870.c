/* FUN_004ef870 - 0x004ef870 in the original binary.
 *
 * __beginthread thread-start thunk: the thread argument arrives via the
 * standard __cdecl stack slot ([esp+8], per __beginthread's ABI), but
 * Ghidra's decompile dropped it entirely instead of forwarding it to
 * AudioStreamThreadProc. Confirmed via objdump at 0x4ef870-0x4ef875
 * (`mov esi,[esp+8]` immediately before `call 0x4ef880`, with ESI never
 * reloaded inside AudioStreamThreadProc itself). Promoted to a real
 * parameter and forwarded.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ef870(void *unaff_ESI)

{
  AudioStreamThreadProc(unaff_ESI);
  return;
}

