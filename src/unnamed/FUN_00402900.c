/* FUN_00402900 - 0x00402900 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00402900(int param_1,char *param_2)

{
  undefined2 *puVar1;
  char cVar2;
  char *in_EAX;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined1 local_38;
  char local_37 [23];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  cVar2 = FUN_00426030(&local_20);
  puVar1 = DAT_007934f4;
  if (cVar2 == '\x01') {
    if (DAT_007934f4 != (undefined2 *)0x0) {
      *(undefined4 *)(DAT_007934f4 + 0x1000) = 4;
      puVar1[1] = 0xa112;
      *(undefined4 *)(puVar1 + 2) = local_20;
      *(undefined4 *)(puVar1 + 4) = local_1c;
      *(undefined4 *)(puVar1 + 6) = local_18;
      *(undefined4 *)(puVar1 + 8) = local_14;
      iVar8 = *(int *)(puVar1 + 0x1000);
      *(int *)(puVar1 + 0x1000) = iVar8 + 0x10;
      pcVar4 = in_EAX;
      do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar2 != '\0');
      uVar5 = (int)pcVar4 - (int)(in_EAX + 1);
      uVar6 = ((int)uVar5 < 0) - 1 & uVar5;
      pcVar4 = (char *)((int)puVar1 + iVar8 + 0x10);
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar4 = *(undefined4 *)in_EAX;
        in_EAX = in_EAX + 4;
        pcVar4 = pcVar4 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar4 = *in_EAX;
        in_EAX = in_EAX + 1;
        pcVar4 = pcVar4 + 1;
      }
      iVar8 = *(int *)(puVar1 + 0x1000) + uVar5;
      *(int *)(puVar1 + 0x1000) = iVar8;
      *puVar1 = (short)iVar8;
      SendSocketData(*(undefined4 *)(puVar1 + 0x1002),iVar8);
      return;
    }
    if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x10))(&local_20,0);
      FUN_004024f0(param_1,in_EAX);
      return;
    }
  }
  else {
    local_38 = 0x6e;
    pcVar4 = param_2;
    do {
      cVar2 = *pcVar4;
      pcVar4[(int)(local_37 + -(int)param_2)] = cVar2;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    iVar3 = FUN_00404b00(&local_38);
    iVar8 = DAT_007934e8;
    if (iVar3 == 0) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar8 + 0x4d4) = 0x1020;
      *(undefined4 *)(iVar8 + 0x4d6) = *(undefined4 *)param_2;
      *(undefined4 *)(iVar8 + 0x4da) = *(undefined4 *)(param_2 + 4);
      *(undefined4 *)(iVar8 + 0x4de) = *(undefined4 *)(param_2 + 8);
      iVar3 = *(int *)(iVar8 + 0x44d0);
      *(int *)(iVar8 + 0x44d0) = iVar3 + 0xc;
      *(undefined1 *)(iVar3 + 0x4dc + iVar8) = 0;
      *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 1;
      EncodePacketBody();
      SendOutgoingPacket();
    }
    pcVar4 = in_EAX;
    do {
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    FUN_004026a0(2,in_EAX,pcVar4 + (1 - (int)(in_EAX + 1)));
  }
  return;
}

