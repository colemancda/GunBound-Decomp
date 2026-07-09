/* FUN_00423e20 - 0x00423e20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_00423e20(undefined4 param_1,int param_2)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffff80;
  char cVar1;
  uint in_EAX;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  int unaff_ESI;
  undefined4 *puVar5;
  undefined2 *puVar6;
  undefined4 *puVar7;
  int local_108;
  uint local_104;
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
  stack0xffffff80 = CONCAT11((undefined1)uStack_7f,(-((in_EAX & 0x8000) != 0) & 7U) + 0x66);
  switch(param_2) {
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
    SUBFIELD(uStack_7f,1,undefined1) = DAT_00552c7a;
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
    if ((int)(in_EAX & 0x7fff) < local_108) {
      uVar2 = FUN_004f08a0();
      if ((char)uVar2 != '\0') {
        ReadXFSEntryByte(iVar4,&local_104);
        FUN_004f1460();
        uVar2 = local_104;
        if (local_104 == (in_EAX & 0x7fff)) {
          QueueOutgoingPacketField(local_104);
          pcVar3 = local_100;
          iVar4 = (unaff_ESI + 0x224) - (int)pcVar3;
          do {
            cVar1 = *pcVar3;
            pcVar3[iVar4] = cVar1;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          if ((*(byte *)(unaff_ESI + 0x236) & 0x80) != 0) {
            *(undefined1 *)(unaff_ESI + 0x236) = 0;
          }
          *(undefined1 *)(unaff_ESI + 0x237) = 0;
          *(undefined1 *)(unaff_ESI + 0x23b) = local_e9;
          QueueOutgoingPacketField(local_e8);
          QueueOutgoingPacketField(local_e4);
          QueueOutgoingPacketField(local_e0);
          QueueOutgoingPacketField(local_dc);
          QueueOutgoingPacketField(local_d8);
          QueueOutgoingPacketField(local_d4);
          QueueOutgoingPacketField(local_d0);
          QueueOutgoingPacketField(local_cc);
          QueueOutgoingPacketField(local_c8);
          QueueOutgoingPacketField(local_c4);
          pcVar3 = local_c0;
          iVar4 = (unaff_ESI + 0x17a4) - (int)pcVar3;
          do {
            cVar1 = *pcVar3;
            pcVar3[iVar4] = cVar1;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          if ((*(byte *)(unaff_ESI + 0x17cb) & 0x80) != 0) {
            *(undefined1 *)(unaff_ESI + 0x17cb) = 0;
          }
          *(undefined1 *)(unaff_ESI + 0x17cc) = 0;
          return CONCAT31((int3)((uint)pcVar3 >> 8),1);
        }
      }
    }
    else {
      uVar2 = FUN_004f1460();
    }
  }
  return uVar2 & 0xffffff00;
}

