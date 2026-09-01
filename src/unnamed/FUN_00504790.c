/* FUN_00504790 - 0x00504790 in the original binary.
 *
 * STILL-OPEN regEsi (2026-09-01 workflow triage, adversarially checked):
 * the engine arrives in ESI; the sole caller 0x504880 computes it as
 * `lea esi,[ecx-0x2c]` from its OWN dropped ECX this, which Ghidra
 * dead-coded entirely (FUN_00504880 is declared with no this and has
 * zero C callers - its consumers are uncarved or vtable-reached).
 * Prerequisite: promote FUN_00504880's regEcx first; then this site
 * becomes FUN_00504790(param_1, regEcx - 0x2c).
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00504790(char *param_1)

{
  int iVar1;
  int iVar2;
  int unaff_ESI;
  uint uVar3;
  
  uVar3 = 0;
  iVar2 = 0;
  while( true ) {
    if (*(int *)(unaff_ESI + 0x1aa4) == 0) {
      return 0;
    }
    if ((uint)((*(int *)(unaff_ESI + 0x1aa8) - *(int *)(unaff_ESI + 0x1aa4)) / 0x12) <= uVar3)
    break;
    iVar1 = __strnicmp((char *)(*(int *)(unaff_ESI + 0x1aa4) + iVar2),param_1,0x10);
    if (iVar1 == 0) {
      return 1;
    }
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x12;
  }
  return 0;
}

