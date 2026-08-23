/* FUN_004eeb30 - 0x004eeb30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eeb30(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  if ((g_soundAvailable != '\0') && (uVar2 = 1, 1 < g_soundChannelCount)) {
    do {
      piVar1 = *(int **)(g_secondarySoundBuffers + uVar2 * 4);
      (**(code **)(*piVar1 + 0x3c))(piVar1,(param_1 + -100) * 100);
      uVar2 = uVar2 + 1;
    } while (uVar2 < g_soundChannelCount);
  }
  return;
}

