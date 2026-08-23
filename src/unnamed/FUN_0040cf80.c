/* FUN_0040cf80 - 0x0040cf80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED AND ESI RECOVERED.  `ret 4` gives one stack argument,
 * so param_1 is ECX, param_2 is EDX and param_3 is the push.  ECX is a
 * PHANTOM (the entry writes it before any read), so it takes 0.  Both call
 * sites agree: push 0xe9c0fc -> param_3, edx = 0x2710 -> param_2, esi = 0.
 *
 * The port passed &g_activeObjectRegistry2 as param_1 -- the right value in the wrong
 * slot.  param_3 is the registry the tree walk starts from
 * (*(param_3 + 4) + 0x1c), which is what confirms the placement rather than
 * merely permitting it.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040cf80(undefined4 param_1,uint param_2,int param_3,uint regEsi)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(param_3 + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 <= regEsi) {
      while (uVar1 != regEsi) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (regEsi < uVar1) {
          return;
        }
      }
      if (*(int *)(param_3 + 8) != 0) {
        CommitActiveTextInput();
      }
      *(int *)(param_3 + 8) = iVar2;
      FUN_0040cc50();
    }
  }
  return;
}

