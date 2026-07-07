/* FUN_004240c0 - 0x004240c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004240c0(undefined4 param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  int unaff_ESI;
  undefined4 *puVar5;
  undefined2 *puVar6;
  undefined4 *puVar7;
  int local_108;
  undefined4 local_104;
  char local_100 [23];
  undefined1 local_e9;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  char local_c0 [63];
  undefined1 auStack_81 [2];
  undefined4 uStack_7f;
  
  puVar5 = &uStack_7f;
  for (iVar4 = 0x1f; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = 0;
  *(undefined1 *)((int)puVar5 + 2) = 0;
  stack0xffffff80 = CONCAT11((undefined1)uStack_7f,((param_2 == '\0') - 1U & 7) + 0x66);
  switch(param_3) {
  case 0:
    puVar6 = (undefined2 *)auStack_81;
    do {
      pcVar3 = (char *)((int)puVar6 + 1);
      puVar6 = (undefined2 *)((int)puVar6 + 1);
    } while (*pcVar3 != '\0');
    *puVar6 = DAT_00552c80;
    break;
  case 1:
    puVar6 = (undefined2 *)auStack_81;
    do {
      pcVar3 = (char *)((int)puVar6 + 1);
      puVar6 = (undefined2 *)((int)puVar6 + 1);
    } while (*pcVar3 != '\0');
    *puVar6 = DAT_005535f0;
    break;
  case 2:
    puVar6 = (undefined2 *)auStack_81;
    do {
      pcVar3 = (char *)((int)puVar6 + 1);
      puVar6 = (undefined2 *)((int)puVar6 + 1);
    } while (*pcVar3 != '\0');
    *puVar6 = DAT_00552c7c;
    break;
  case 3:
    stack0xffffff80 = DAT_00552c78;
    uStack_7f._1_1_ = DAT_00552c7a;
  }
  puVar5 = (undefined4 *)auStack_81;
  do {
    puVar7 = puVar5;
    puVar5 = (undefined4 *)((int)puVar7 + 1);
  } while (*(char *)((int)puVar7 + 1) != '\0');
  *(undefined4 *)((int)puVar7 + 1) = DAT_00552c70;
  *(undefined1 *)((int)puVar7 + 5) = DAT_00552c74;
  iVar4 = FUN_004f1390(0);
  uVar2 = 0;
  if (iVar4 != 0) {
    ReadXFSEntryByte(iVar4,&local_108);
    if ((int)(uint)param_4 < local_108) {
      FUN_004f08a0();
      ReadXFSEntryByte(iVar4,&local_104);
      FUN_004f1460();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_104);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pcVar3 = local_100;
      iVar4 = (unaff_ESI + 0x224) - (int)pcVar3;
      do {
        cVar1 = *pcVar3;
        pcVar3[iVar4] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      if (*(char *)(unaff_ESI + 0x236) < '\0') {
        *(undefined1 *)(unaff_ESI + 0x236) = 0;
      }
      *(undefined1 *)(unaff_ESI + 0x237) = 0;
      *(undefined1 *)(unaff_ESI + 0x23b) = local_e9;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_e8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_e4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_e0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_dc);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_d8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_d4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_d0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_cc);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_c8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_c4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pcVar3 = local_c0;
      iVar4 = (unaff_ESI + 0x17a4) - (int)pcVar3;
      do {
        cVar1 = *pcVar3;
        pcVar3[iVar4] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      if (*(char *)(unaff_ESI + 0x17cb) < '\0') {
        *(undefined1 *)(unaff_ESI + 0x17cb) = 0;
      }
      *(undefined1 *)(unaff_ESI + 0x17cc) = 0;
      return CONCAT31((int3)((uint)iVar4 >> 8),1);
    }
    uVar2 = FUN_004f1460();
  }
  return uVar2 & 0xffffff00;
}

