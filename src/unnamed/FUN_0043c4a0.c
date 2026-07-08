/* FUN_0043c4a0 - 0x0043c4a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0043c4a0(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 < 0x186a5) {
    while (uVar1 != 0x186a4) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (0x186a4 < uVar1) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    while ((uVar1 <= param_2 && (uVar1 != param_2))) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar1 = *(uint *)(iVar2 + 8);
    }
  }
  return;
}

