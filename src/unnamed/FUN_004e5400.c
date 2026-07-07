/* FUN_004e5400 - 0x004e5400 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e5400(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4) + 1;
  *(int *)(param_1 + 4) = iVar1;
  if (iVar1 == 0x3c) {
    g_pendingGameState = 2;
    g_stateChangeRequested = 1;
    ChangeGameState(2);
  }
  return;
}

