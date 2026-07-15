/* FUN_00402720 - 0x00402720 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
 * its 3 real args and dropped the buffer ("this") entirely - same bug as
 * FUN_00405ba0.c's own already-fixed SendSocketData call, which shares
 * this exact object shape (DAT_007934f4, connObj at +0x2004, write
 * cursor at +0x2000). Confirmed via angr disassembly at 0x4027d0-0x4027e8:
 * `mov ecx,eax` (buffer, this) / `push ecx` where ecx=[eax+0x2004]
 * (connection object, param_2) / `push ecx` where ecx=the just-computed
 * new cursor (length, param_3 - already held in iVar9).
 */
#include "ghidra_types.h"


void FUN_00402720(int param_1,char *param_2,char *param_3)

{
  undefined2 *puVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
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
      puVar1[1] = 0xa110;
      *(undefined4 *)(puVar1 + 2) = local_20;
      *(undefined4 *)(puVar1 + 4) = local_1c;
      *(undefined4 *)(puVar1 + 6) = local_18;
      *(undefined4 *)(puVar1 + 8) = local_14;
      iVar9 = *(int *)(puVar1 + 0x1000);
      *(int *)(puVar1 + 0x1000) = iVar9 + 0x10;
      pcVar4 = param_3;
      do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar2 != '\0');
      uVar5 = (int)pcVar4 - (int)(param_3 + 1);
      uVar6 = ((int)uVar5 < 0) - 1 & uVar5;
      pcVar4 = param_3;
      pcVar8 = (char *)(iVar9 + 0x10 + (int)puVar1);
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar8 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar8 = pcVar8 + 1;
      }
      iVar9 = *(int *)(puVar1 + 0x1000) + uVar5;
      *(int *)(puVar1 + 0x1000) = iVar9;
      *puVar1 = (short)iVar9;
      SendSocketData((char *)puVar1,*(undefined4 *)((char *)puVar1 + 0x2004),iVar9);
      FUN_004024f0(param_1,param_3);
      return;
    }
    if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x10))(&local_20,0,param_3);
      FUN_004024f0(param_1,param_3);
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
    iVar9 = DAT_007934e8;
    if (iVar3 == 0) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar9 + 0x4d4) = 0x1020;
      *(undefined4 *)(iVar9 + 0x4d6) = *(undefined4 *)param_2;
      *(undefined4 *)(iVar9 + 0x4da) = *(undefined4 *)(param_2 + 4);
      *(undefined4 *)(iVar9 + 0x4de) = *(undefined4 *)(param_2 + 8);
      iVar3 = *(int *)(iVar9 + 0x44d0);
      *(int *)(iVar9 + 0x44d0) = iVar3 + 0xc;
      *(undefined1 *)(iVar3 + 0x4dc + iVar9) = 0;
      *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 1;
      EncodePacketBody(0,iVar9);
      SendOutgoingPacket(iVar9);
    }
    pcVar4 = param_3;
    do {
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    FUN_004026a0(0,param_3,pcVar4 + (1 - (int)(param_3 + 1)));
  }
  return;
}

