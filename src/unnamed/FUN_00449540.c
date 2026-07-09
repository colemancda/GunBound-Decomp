/* FUN_00449540 - 0x00449540 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_00449540(int param_1,undefined4 param_2)

{
  char *pcVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 auVar8; /* Ghidra register slot; was undefined1 [4] */
  undefined4 uVar9;
  undefined2 uVar10;
  int iVar11;
  undefined1 uVar12;
  undefined2 *puVar13;
  int iVar14;
  undefined4 *puVar15;
  byte *pbVar16;
  uint uVar17;
  undefined2 *puVar18;
  undefined4 *unaff_FS_OFFSET;
  bool bVar19;
  int local_1878;
  undefined4 auStack_1874; /* Ghidra register slot; was undefined1 [4] */
  undefined4 uStack_1870;
  char cStack_15b5;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053d8bb;
  *unaff_FS_OFFSET = &uStack_c;
  uStack_10 = 0x44955f;
  puVar15 = (undefined4 *)(param_1 + 0x2d114);
  for (iVar11 = 0x10e; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar15 = 0;
    puVar15 = puVar15 + 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(param_1 + 0x44c) = param_2;
  *(undefined4 *)(param_1 + 0x450) = 0;
  uVar17 = 20000;
  local_1878 = 10;
  do {
    puVar15 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar5 = puVar15[1];
    if (uVar5 <= uVar17) {
LAB_004495d0:
      if (uVar5 != uVar17) goto code_r0x004495d2;
      puVar6 = (undefined4 *)puVar15[4];
      while (puVar6 != puVar15) {
        puVar7 = (undefined4 *)*puVar6;
        puVar6 = (undefined4 *)puVar6[4];
        (*(code *)*puVar7)(1);
      }
      puVar15[3] = puVar15;
      puVar15[4] = puVar15;
    }
LAB_004495fa:
    uVar17 = uVar17 + 1;
    local_1878 = local_1878 + -1;
  } while (local_1878 != 0);
  FUN_00425350();
  iVar11 = g_clientContext;
  iVar14 = 0;
  uStack_4 = 0;
  local_1878 = 0;
  pbVar16 = (byte *)(g_clientContext + 0x3b498);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar2 = *pbVar16;
  bVar3 = *(byte *)(iVar11 + 0x3b499);
  bVar19 = (byte)(bVar2 + bVar3 + -0x34) == *(char *)(iVar11 + 0x3b49a);
  if (!bVar19) {
    DAT_00793514 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar19 && (bVar3 >> (bVar2 & 7) & 1) == 1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar11) {
      auStack_1874 = (undefined4)(param_1 + 0x2e54c);
      do {
        FUN_004240c0(g_clientContext,1,param_2,iVar14);
        if (cStack_15b5 != '\0') {
          *(undefined1 *)(local_1878 + 0x2d54c + param_1) = 1;
          local_1878 = local_1878 + 1;
          *(short *)auStack_1874 = (short)iVar14;
          auStack_1874 = (undefined4)((int)auStack_1874 + 2);
        }
        iVar14 = iVar14 + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar11 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      } while (iVar14 < iVar11);
    }
  }
  iVar14 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0 < iVar11) {
    auStack_1874 = (undefined4)(param_1 + 0x2e54c + local_1878 * 2);
    do {
      FUN_004240c0(g_clientContext,0,param_2,iVar14);
      if (cStack_15b5 != '\0') {
        *(undefined1 *)(local_1878 + 0x2d54c + param_1) = 0;
        local_1878 = local_1878 + 1;
        *(short *)auStack_1874 = (short)iVar14;
        auStack_1874 = (undefined4)((int)auStack_1874 + 2);
      }
      iVar14 = iVar14 + 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar11 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    } while (iVar14 < iVar11);
  }
  iVar11 = g_clientContext;
  pbVar16 = (byte *)(g_clientContext + 0x3b498);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar2 = *pbVar16;
  bVar3 = *(byte *)(iVar11 + 0x3b499);
  bVar19 = (byte)(bVar2 + bVar3 + -0x34) != *(char *)(iVar11 + 0x3b49a);
  if (bVar19) {
    DAT_00793514 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar19 || (bVar3 >> (bVar2 & 7) & 1) != 1) {
    iVar14 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar11) {
      auStack_1874 = (undefined4)(param_1 + 0x2e54c + local_1878 * 2);
      do {
        FUN_004240c0(g_clientContext,1,param_2,iVar14);
        if (cStack_15b5 != '\0') {
          *(undefined1 *)(local_1878 + 0x2d54c + param_1) = 1;
          local_1878 = local_1878 + 1;
          *(short *)auStack_1874 = (short)iVar14;
          auStack_1874 = (undefined4)((int)auStack_1874 + 2);
        }
        iVar14 = iVar14 + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar11 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      } while (iVar14 < iVar11);
    }
  }
  *(int *)(param_1 + 0x2d110) = local_1878;
  local_1878 = param_1 + 0x2d114;
  auStack_1874 = (undefined4)(param_1 + 0x1bfc);
  iVar11 = 0;
  puVar13 = (undefined2 *)(param_1 + 0x2e54c);
  do {
    iVar14 = *(int *)(param_1 + 0x450);
    if (*(int *)(param_1 + 0x2d110) <= iVar11 + iVar14 * 9) break;
    cVar4 = *(char *)(param_1 + 0x2d54c + iVar11);
    uVar10 = DAT_00555a18;
    uVar12 = DAT_00555a1a;
    if (cVar4 == '\x01') {
      uVar10 = DAT_00555a14;
      uVar12 = DAT_00555a16;
    }
    SUBFIELD(uStack_1870,0,undefined3) = CONCAT12(uVar12,uVar10);
    switch(param_2) {
    case 0:
      puVar18 = (undefined2 *)(auStack_1874 + 3);
      do {
        pcVar1 = (char *)((int)puVar18 + 1);
        puVar18 = (undefined2 *)((int)puVar18 + 1);
      } while (*pcVar1 != '\0');
      *puVar18 = DAT_00552c80;
      break;
    case 1:
      puVar18 = (undefined2 *)(auStack_1874 + 3);
      do {
        pcVar1 = (char *)((int)puVar18 + 1);
        puVar18 = (undefined2 *)((int)puVar18 + 1);
      } while (*pcVar1 != '\0');
      *puVar18 = DAT_005535f0;
      break;
    case 2:
      puVar18 = (undefined2 *)(auStack_1874 + 3);
      do {
        pcVar1 = (char *)((int)puVar18 + 1);
        puVar18 = (undefined2 *)((int)puVar18 + 1);
      } while (*pcVar1 != '\0');
      *puVar18 = DAT_00552c7c;
      break;
    case 3:
      uStack_1870 = &DAT_00666d73;
    }
    FUN_004240c0(g_clientContext,CONCAT31((int3)((uint)iVar14 >> 8),cVar4 == '\x01'),param_2,*puVar13);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf((char *)((int)&uStack_1870 + 3),s__05d_img_00555a08,uVar9);
    FUN_004f1790(&DAT_00ea0e18,iVar11 + 20000);
    auVar8 = auStack_1874;
    FUN_004240c0(g_clientContext,*(char *)(param_1 + 0x2d54c + iVar11) == '\x01',param_2,*puVar13);
    RenderWrappedText(local_1878,auVar8,0x18,0x15,0x78,1);
    iVar11 = iVar11 + 1;
    auStack_1874 = (undefined4)((int)auVar8 + 0x17e4);
    local_1878 = local_1878 + 0x78;
    puVar13 = puVar13 + 1;
  } while (iVar11 < 9);
  uStack_4 = 0xffffffff;
  FUN_004254a0();
  *unaff_FS_OFFSET = uStack_c;
  return;
code_r0x004495d2:
  puVar15 = (undefined4 *)puVar15[7];
  uVar5 = puVar15[1];
  if (uVar17 < uVar5) goto LAB_004495fa;
  goto LAB_004495d0;
}

