/* FUN_00438410 - 0x00438410 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00438410(undefined4 param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  void *pvVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  char *pcVar9;
  undefined4 *puVar10;
  byte bVar11;
  uint uVar12;
  undefined4 *unaff_FS_OFFSET;
  bool bVar13;
  int local_94;
  char local_8c [128];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cf6e;
  *unaff_FS_OFFSET = &local_c;
  cVar3 = FUN_004065a0();
  if (cVar3 != '\0') goto LAB_004388b4;
  iVar8 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar12 = 0;
  while (uVar1 = *(uint *)(iVar8 + 4), iVar4 = iVar8, uVar1 < 0x186a7) {
    while (uVar1 != 0x186a6) {
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar1 = *(uint *)(iVar4 + 4);
      if (0x186a6 < uVar1) goto LAB_0043848e;
    }
    iVar4 = *(int *)(iVar4 + 0x10);
    bVar13 = *(uint *)(iVar4 + 8) == uVar12;
    if (uVar12 <= *(uint *)(iVar4 + 8) && !bVar13) break;
    while (!bVar13) {
      iVar4 = *(int *)(iVar4 + 0x10);
      bVar13 = *(uint *)(iVar4 + 8) == uVar12;
      if (uVar12 < *(uint *)(iVar4 + 8)) goto LAB_0043848e;
    }
    uVar12 = uVar12 + 1;
    if (7 < (int)uVar12) break;
  }
LAB_0043848e:
  if (uVar12 == 8) goto LAB_004388b4;
  uVar1 = uVar12 + 8;
  uVar2 = *(uint *)(iVar8 + 4);
  while (uVar2 < 0x7a121) {
    if (uVar2 == 500000) {
      puVar10 = *(undefined4 **)(iVar8 + 0x10);
      uVar2 = puVar10[2];
      if (uVar2 <= uVar1) goto LAB_004384c7;
      break;
    }
    iVar8 = *(int *)(iVar8 + 0x1c);
    uVar2 = *(uint *)(iVar8 + 4);
  }
  goto LAB_004384ed;
  while( true ) {
    puVar10 = (undefined4 *)puVar10[4];
    uVar2 = puVar10[2];
    if (uVar1 < uVar2) break;
LAB_004384c7:
    if (uVar2 == uVar1) {
      *(undefined4 *)(puVar10[3] + 0x10) = puVar10[4];
      *(undefined4 *)(puVar10[4] + 0xc) = puVar10[3];
      (**(code **)*puVar10)(1);
      break;
    }
  }
LAB_004384ed:
  pvVar5 = operator_new(0x2298);
  local_4 = 0;
  if (pvVar5 == (void *)0x0) {
    piVar6 = (int *)0x0;
  }
  else {
    piVar6 = (int *)FUN_00477bb0(pvVar5,uVar12);
  }
  local_4 = 0xffffffff;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  switch(param_3) {
  case 0:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = 300;
    break;
  case 1:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = 200;
    break;
  case 2:
  case 3:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    break;
  default:
    goto switchD_0043857e_default;
  }
  EncodeOutgoingPacketField(uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
switchD_0043857e_default:
  _sprintf(local_8c,s_jewel_d_00553bd4,param_3 + 1);
  iVar8 = FindPreloadedTextureByName(local_8c);
  piVar6[7] = iVar8;
  if (param_4 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = _rand();
    *(char *)(piVar6 + 0x706) = (char)iVar8;
    iVar8 = _rand();
    *(byte *)((int)piVar6 + 0x1c19) = (byte)iVar8;
    bVar11 = *(byte *)(piVar6 + 0x706) & 7;
    bVar11 = ~('\x01' << bVar11) & (byte)iVar8 | '\0' << bVar11;
    *(byte *)((int)piVar6 + 0x1c19) = bVar11;
    *(byte *)((int)piVar6 + 0x1c1a) = bVar11 + *(byte *)(piVar6 + 0x706) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < param_2) && (param_2 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar9 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + param_2);
      local_94 = 0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar9 != '\0') goto LAB_00438814;
          pcVar9 = pcVar9 + *(int *)(&DAT_006a7720 + g_clientContext);
          local_94 = local_94 + 1;
        } while (local_94 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    local_94 = 10000;
LAB_00438814:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(local_94);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (9000 < iVar8) {
      (**(code **)*piVar6)(1);
      goto LAB_004388b4;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar8 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (**(code **)(*piVar6 + 4))(s_normal_00552230);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = _rand();
    *(char *)(piVar6 + 0x706) = (char)iVar8;
    iVar8 = _rand();
    *(byte *)((int)piVar6 + 0x1c19) = (byte)iVar8;
    bVar11 = '\x01' << (*(byte *)(piVar6 + 0x706) & 7);
    bVar11 = ~bVar11 & (byte)iVar8 | bVar11;
    *(byte *)((int)piVar6 + 0x1c19) = bVar11;
    *(byte *)((int)piVar6 + 0x1c1a) = bVar11 + *(byte *)(piVar6 + 0x706) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (**(code **)(*piVar6 + 4))(&DAT_00553bcc);
    uVar12 = DAT_005b3480 * 0xda003 + 0x5703b11;
    DAT_005b3480 = DAT_005b3480 + (uVar12 * 0x61 + 0x61) % 0xf4241;
    if ((uVar12 & 1) != 0) {
      uVar12 = DAT_005b3480 * 0xda003 + 0x5703b11;
      DAT_005b3480 = DAT_005b3480 + (uVar12 * 0x61 + 0x61) % 0xf4241;
      GetLocalizedString(&DAT_00796eec,uVar12 % 10 + 0x803);
      FUN_004382d0();
    }
  }
  RegisterActiveObject();
LAB_004388b4:
  *unaff_FS_OFFSET = local_c;
  return;
}

