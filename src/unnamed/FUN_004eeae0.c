/* FUN_004eeae0 - 0x004eeae0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-26): the sound-channel index.  The body is 39 bytes:
 * bail if g_soundAvailable is clear; if ESI != -1, take g_soundChannels[ESI]
 * and call its vtable slot 3; then, only when ESI == 0, clear the byte at
 * 0x793568.  ESI is read before any write (`cmp esi,-1` is its first
 * reference), and -1 as a "no channel" sentinel plus the [table + esi*4]
 * indexing is what fixes it as the index rather than a pointer.
 */
#include "ghidra_types.h"


void FUN_004eeae0(int soundChannelIndex)

{
  
  if (g_soundAvailable != '\0') {
    if (soundChannelIndex != -1) {
      (**(code **)(**(int **)(g_soundChannels + soundChannelIndex * 4) + 0xc))();
    }
    if (soundChannelIndex == 0) {
      DAT_00793568 = 0;
    }
  }
  return;
}

