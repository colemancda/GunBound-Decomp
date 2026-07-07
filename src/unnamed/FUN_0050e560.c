/* FUN_0050e560 - 0x0050e560 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050e560(undefined4 *param_1)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005378ab;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_LAB_00557f58;
  local_4 = 0;
  uVar4 = param_1[4];
  uVar2 = uVar4;
  while( true ) {
    uVar2 = uVar2 - 1;
    if ((int)uVar2 < 0) {
      if ((void *)param_1[3] != (void *)0x0) {
        _free((void *)param_1[3]);
      }
      *unaff_FS_OFFSET = local_c;
      return;
    }
    if ((uint)param_1[4] <= uVar2) break;
    pvVar1 = *(void **)(param_1[3] + uVar2 * 4);
    if (pvVar1 != (void *)0x0) {
      FUN_0050e560();
      _free(pvVar1);
    }
    if ((uint)param_1[4] < uVar4) break;
    iVar3 = (param_1[4] - uVar2) + -1;
    if (iVar3 != 0) {
      pvVar1 = (void *)(param_1[3] + uVar2 * 4);
      _memmove(pvVar1,(void *)((int)pvVar1 + 4),iVar3 * 4);
    }
    uVar4 = uVar4 - 1;
    param_1[4] = param_1[4] + -1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_004010c0(0x80070057);
}

