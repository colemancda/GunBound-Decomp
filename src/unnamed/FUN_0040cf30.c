/* FUN_0040cf30 - 0x0040cf30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040cf30(undefined4 param_1,uint param_2,char param_3)

{
  uint uVar1;
  int in_EAX;
  int iVar2;
  uint unaff_ESI;
  
  iVar2 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
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
    if (uVar1 <= unaff_ESI) {
      while (uVar1 != unaff_ESI) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (unaff_ESI < uVar1) {
          return;
        }
      }
      *(uint *)(iVar2 + 0x448) = (uint)(param_3 == '\0');
    }
  }
  return;
}

