/* FUN_004e84c0 - 0x004e84c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e84c0(int param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  void *_Dst;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  bool bVar9;
  bool bVar10;
  int local_4;
  
  bVar10 = true;
  bVar2 = true;
  if (*(int *)(param_1 + 0x454a8) != 1 && -1 < *(int *)(param_1 + 0x454a8) + -1) {
    piVar1 = (int *)(param_1 + 0x454a4);
    local_4 = 0;
    uVar5 = 0;
    do {
      if ((*(uint *)(param_1 + 0x454a8) <= uVar5) ||
         (uVar6 = uVar5 + 1, *(uint *)(param_1 + 0x454a8) <= uVar6)) goto LAB_004e86e2;
      if (*(short *)(*piVar1 + 2 + local_4) == *(short *)(local_4 + 0x208 + *piVar1)) {
        uVar4 = *(uint *)(param_1 + 0x454a8);
        if (((uVar4 <= uVar5) || (uVar4 <= uVar6)) || (uVar4 <= uVar5)) goto LAB_004e86e2;
        iVar3 = *piVar1;
        uVar4 = (uint)*(ushort *)(local_4 + 2 + iVar3);
        bVar9 = true;
        pcVar7 = (char *)(local_4 + 5 + iVar3);
        pcVar8 = (char *)(local_4 + 0x20b + iVar3);
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar9 = *pcVar7 == *pcVar8;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        } while (bVar9);
        if (!bVar9) goto LAB_004e85b8;
        if (*(uint *)(param_1 + 0x454a8) < uVar6) goto LAB_004e86e2;
        iVar3 = (*(uint *)(param_1 + 0x454a8) - uVar5) + -1;
        if (iVar3 != 0) {
          _memmove((void *)(*piVar1 + local_4),(void *)(*piVar1 + local_4 + 0x206),iVar3 * 0x206);
        }
        *(int *)(param_1 + 0x454a8) = *(int *)(param_1 + 0x454a8) + -1;
        if ((bVar10) && (*(int *)(param_1 + 0x454a8) != 0)) {
          FUN_004e8f70(param_1 + 0x1b0);
        }
        bVar10 = false;
        uVar6 = uVar5;
      }
      else {
LAB_004e85b8:
        local_4 = local_4 + 0x206;
      }
      uVar5 = uVar6;
    } while ((int)uVar6 < *(int *)(param_1 + 0x454a8) + -1);
  }
  if (*(int *)(param_1 + 0x454b8) != 1 && -1 < *(int *)(param_1 + 0x454b8) + -1) {
    local_4 = 0;
    uVar5 = 0;
    do {
      if ((*(uint *)(param_1 + 0x454b8) <= uVar5) ||
         (uVar6 = uVar5 + 1, *(uint *)(param_1 + 0x454b8) <= uVar6)) goto LAB_004e86e2;
      iVar3 = *(int *)(param_1 + 0x454b4);
      if (*(short *)(local_4 + 2 + iVar3) == *(short *)(local_4 + 0x208 + iVar3)) {
        uVar4 = *(uint *)(param_1 + 0x454b8);
        if (((uVar4 <= uVar5) || (uVar4 <= uVar6)) || (uVar4 <= uVar5)) {
LAB_004e86e2:
                    /* WARNING: Subroutine does not return */
          FUN_004010c0(0x80070057);
        }
        uVar4 = (uint)*(ushort *)(local_4 + 2 + iVar3);
        bVar10 = true;
        pcVar7 = (char *)(local_4 + 5 + iVar3);
        pcVar8 = (char *)(iVar3 + 0x20b + local_4);
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar10 = *pcVar7 == *pcVar8;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        } while (bVar10);
        if (!bVar10) goto LAB_004e86ba;
        if (*(uint *)(param_1 + 0x454b8) < uVar6) goto LAB_004e86e2;
        iVar3 = (*(uint *)(param_1 + 0x454b8) - uVar5) + -1;
        if (iVar3 != 0) {
          _Dst = (void *)(*(int *)(param_1 + 0x454b4) + local_4);
          _memmove(_Dst,(void *)((int)_Dst + 0x206),iVar3 * 0x206);
        }
        *(int *)(param_1 + 0x454b8) = *(int *)(param_1 + 0x454b8) + -1;
        if ((bVar2) && (*(int *)(param_1 + 0x454b8) != 0)) {
          FUN_004e8f70(param_1 + 0x4529c);
        }
        bVar2 = false;
        uVar6 = uVar5;
      }
      else {
LAB_004e86ba:
        local_4 = local_4 + 0x206;
      }
      uVar5 = uVar6;
    } while ((int)uVar6 < *(int *)(param_1 + 0x454b8) + -1);
  }
  return;
}

