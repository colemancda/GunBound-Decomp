/* RenderInventoryItemDetail - 0x0044b900 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void RenderInventoryItemDetail(int param_1)

{
  char *pcVar1;
  uint uVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  byte bVar8;
  byte bVar9;
  undefined2 uVar10;
  code *pcVar11;
  uint uVar12;
  code *pcVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  undefined4 *unaff_FS_OFFSET;
  char local_190d;
  undefined4 local_190c;
  undefined4 local_188c;
  char local_1888 [14];
  ushort local_187a;
  byte local_1878;
  byte local_1877;
  uint local_1874;
  undefined1 local_1870 [676];
  char local_15cc [5564];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053d8bb;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x44b91f;
  FUN_00425350();
  local_4 = 0;
  cVar3 = PeekPacketChecksumBool();
  pcVar11 = (code *)LeaveCriticalSection;
  if (cVar3 != '\0') {
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') goto LAB_0044bdfe;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(byte *)(param_1 + 0x32c54) = (byte)iVar5;
    iVar5 = _rand();
    bVar9 = *(byte *)(param_1 + 0x32c54);
    *(byte *)(param_1 + 0x32c55) = (byte)iVar5;
    bVar8 = bVar9 & 7;
    bVar8 = ~('\x01' << bVar8) & (byte)iVar5 | '\0' << bVar8;
    *(byte *)(param_1 + 0x32c55) = bVar8;
    pcVar11 = (code *)LeaveCriticalSection;
    *(byte *)(param_1 + 0x32c56) = bVar8 + bVar9 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RemoveWidget();
    RemoveWidget();
    FUN_0040cdf0();
    FUN_0040cdf0();
  }
  pcVar13 = (code *)EnterCriticalSection;
  if ((g_stateChangeInProgress == 0) || (DAT_0079350c != '\x01')) {
    g_stateChangeInProgress = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    local_190d = iVar5 != 0;
    (*pcVar11)(&DAT_005a9068);
    if (local_190d != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      (*pcVar11)(&DAT_005a9068);
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      pcVar13 = (code *)EnterCriticalSection;
    }
    iVar5 = *(int *)(g_clientContext + 0x44bec);
    FUN_004f1c00();
    if (iVar5 == 0) {
      (*pcVar13)(&DAT_005a9068);
      iVar5 = _rand();
      *(char *)(param_1 + 0x32e63) = (char)iVar5;
      iVar5 = _rand();
      *(byte *)(param_1 + 0x32e64) = (byte)iVar5;
      bVar9 = *(byte *)(param_1 + 0x32e63) & 7;
      bVar9 = ~('\x01' << bVar9) & (byte)iVar5 | '\0' << bVar9;
      *(byte *)(param_1 + 0x32e64) = bVar9;
      *(byte *)(param_1 + 0x32e65) = bVar9 + *(char *)(param_1 + 0x32e63) + -0x34;
      (*pcVar11)(&DAT_005a9068);
      RemoveWidget();
      FUN_0044b720(param_1);
    }
    else {
      if (*(int *)(g_clientContext + 0x44bec) == 0) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      puVar14 = *(undefined4 **)(g_clientContext + 0x44be8);
      puVar15 = &local_188c;
      for (iVar5 = 0x27; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar15 = *puVar14;
        puVar14 = puVar14 + 1;
        puVar15 = puVar15 + 1;
      }
      RemoveInventoryItems();
      uVar2 = local_1874;
      uVar12 = local_1874 >> 0x10;
      FUN_00423e20(g_clientContext,uVar12 & 0xf);
      pcVar6 = local_1888;
      iVar5 = (param_1 + 0x32ef0) - (int)pcVar6;
      do {
        cVar3 = *pcVar6;
        pcVar6[iVar5] = cVar3;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      pcVar6 = local_15cc;
      *(uint *)(param_1 + 0x32e68) = (uVar12 & 0xf) << 1;
      iVar5 = (param_1 + 0x32e6c) - (int)pcVar6;
      do {
        cVar3 = *pcVar6;
        pcVar6[iVar5] = cVar3;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      iVar5 = *(int *)(param_1 + 0x32e68);
      if (iVar5 == 6) {
        iVar7 = -1;
      }
      else {
        iVar7 = 6 - (uint)((uVar2 & 0x8000) != 0);
      }
      *(int *)(param_1 + 0x32eec) = iVar7;
      if ((iVar5 != 6) && ((uVar2 & 0x8000) == 0)) {
        *(int *)(param_1 + 0x32e68) = iVar5 + 1;
      }
      _sprintf((char *)(param_1 + 0x32f10),s__04d__02d__02d_00555640,(uint)local_187a,
               (uint)local_1878,(uint)local_1877);
      puVar14 = (undefined4 *)(param_1 + 0x32f30);
      for (iVar5 = 0x18; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      RenderWrappedText((undefined4 *)(param_1 + 0x32f30),local_1870,0x20,0x1a,0x40,1);
      uVar10 = DAT_00555a14;
      uVar4 = DAT_00555a16;
      if (-1 < (char)(local_1874 >> 8)) {
        uVar10 = DAT_00555a18;
        uVar4 = DAT_00555a1a;
      }
      local_190c = (undefined *)CONCAT22(CONCAT11(SUBFIELD(local_190c,3,undefined1),uVar4),uVar10);
      switch(local_1874 >> 0x10 & 0xf) {
      case 0:
        pcVar6 = &local_190d;
        do {
          pcVar1 = pcVar6 + 1;
          pcVar6 = pcVar6 + 1;
        } while (*pcVar1 != '\0');
        *(undefined2 *)pcVar6 = DAT_00552c80;
        break;
      case 1:
        pcVar6 = &local_190d;
        do {
          pcVar1 = pcVar6 + 1;
          pcVar6 = pcVar6 + 1;
        } while (*pcVar1 != '\0');
        *(undefined2 *)pcVar6 = DAT_005535f0;
        break;
      case 2:
        pcVar6 = &local_190d;
        do {
          pcVar1 = pcVar6 + 1;
          pcVar6 = pcVar6 + 1;
        } while (*pcVar1 != '\0');
        *(undefined2 *)pcVar6 = DAT_00552c7c;
        break;
      case 3:
        local_190c = &DAT_00666d73;
      }
      _sprintf((char *)((int)&local_190c + 3),s__05d_img_00555a08,local_1874 & 0x7fff);
      LoadSpriteSet(&DAT_00ea0e18,40000);
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        CreateButtonWidget(&DAT_00e9be90,0,0x36,0x516,s_b_storewindow_confirm_00555a8c,0x14d,0x154,
                           0x4a,0x1a,1,0);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(byte *)(param_1 + 0x32e63) = (byte)iVar5;
      iVar5 = _rand();
      bVar9 = *(byte *)(param_1 + 0x32e63);
      *(byte *)(param_1 + 0x32e64) = (byte)iVar5;
      bVar8 = '\x01' << (bVar9 & 7);
      bVar8 = ~bVar8 & (byte)iVar5 | bVar8;
      *(byte *)(param_1 + 0x32e64) = bVar8;
      *(byte *)(param_1 + 0x32e65) = bVar8 + bVar9 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
  }
LAB_0044bdfe:
  local_4 = 0xffffffff;
  FUN_004254a0();
  *unaff_FS_OFFSET = local_c;
  return;
}

