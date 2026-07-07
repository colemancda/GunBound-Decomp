/* FUN_004ef610 - 0x004ef610 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004ef610(int param_1,int param_2)

{
  LPCRITICAL_SECTION lpCriticalSection;
  LONG *pLVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  LONG LVar6;
  uint uVar7;
  undefined4 unaff_EDI;
  uint uVar8;
  undefined4 *puVar9;
  LONG *pLVar10;
  char cStack_45;
  undefined1 local_24 [4];
  LPCRITICAL_SECTION local_20;
  undefined1 local_1c [4];
  _RTL_CRITICAL_SECTION local_18;
  
  if ((*(int *)(param_1 + 0x14) != 0) && (*(char *)(param_1 + 0x4c) != '\0')) {
    lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 0x20);
    EnterCriticalSection(lpCriticalSection);
    if (DAT_00793560 < *(uint *)(param_1 + 0x38)) {
      LeaveCriticalSection(lpCriticalSection);
      return;
    }
    piVar2 = *(int **)(DAT_00793558 + *(uint *)(param_1 + 0x38) * 4);
    pLVar1 = &local_18.LockCount;
    cStack_45 = (char)((uint)local_24 >> 0x18);
    local_20 = lpCriticalSection;
    iVar3 = (**(code **)(*piVar2 + 0x2c))(piVar2,(param_2 != 0) - 1 & DAT_00588f44,DAT_00588f44);
    if (iVar3 == 0) {
      if (*(int *)(param_1 + 0x14) != 0) {
        uVar4 = ReadXFSEntryByte(*(int *)(param_1 + 0x14),pLVar1);
        uVar8 = DAT_00588f44;
        iVar3 = 0;
        if (uVar4 != DAT_00588f44) {
          if (*(int *)(param_1 + 0x3c) == 0) {
            if (*(int *)(param_1 + 0x48) == 0) {
              uVar7 = DAT_00588f44 - uVar4;
              puVar9 = (undefined4 *)((int)pLVar1 + uVar4);
              uVar8 = uVar7 >> 2;
              if (DAT_00588f38 == 8) {
                uVar5 = 0x80808080;
              }
              else {
                uVar5 = 0;
              }
              for (; uVar8 != 0; uVar8 = uVar8 - 1) {
                *puVar9 = uVar5;
                puVar9 = puVar9 + 1;
              }
              for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                *(char *)puVar9 = (char)uVar5;
                puVar9 = (undefined4 *)((int)puVar9 + 1);
              }
              *(undefined4 *)(param_1 + 0x48) = 1;
            }
            else if (*(int *)(param_1 + 0x48) == 1) {
              uVar4 = DAT_00588f44 >> 2;
              pLVar10 = pLVar1;
              if (DAT_00588f38 == 8) {
                LVar6 = -0x7f7f7f80;
              }
              else {
                LVar6 = 0;
              }
              for (; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pLVar10 = LVar6;
                pLVar10 = pLVar10 + 1;
              }
              for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
                *(char *)pLVar10 = (char)LVar6;
                pLVar10 = (LONG *)((int)pLVar10 + 1);
              }
              *(undefined4 *)(param_1 + 0x48) = 2;
            }
            else {
              cStack_45 = '\x01';
            }
          }
          else {
            do {
              iVar3 = iVar3 + uVar4;
              uVar8 = uVar8 - uVar4;
              FUN_004f0960();
              ReadXFSEntryByte(*(undefined4 *)(param_1 + 0x14),&stack0xffffffd0);
              uVar4 = ReadXFSEntryByte(*(undefined4 *)(param_1 + 0x14),(int)pLVar1 + iVar3);
            } while (uVar4 != uVar8);
          }
        }
      }
      piVar2 = *(int **)(DAT_00793558 + *(int *)(param_1 + 0x38) * 4);
      (**(code **)(*piVar2 + 0x4c))(piVar2,pLVar1,unaff_EDI,0,local_1c);
      if (cStack_45 == '\0') {
        LeaveCriticalSection(&local_18);
        return;
      }
    }
    LeaveCriticalSection(&local_18);
    FUN_004eeae0();
  }
  return;
}

