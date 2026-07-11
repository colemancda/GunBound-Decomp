/* FUN_00404700 - 0x00404700 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00404700(int param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 *unaff_EDI;
  undefined2 local_50 [4];
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  short local_42;
  undefined1 local_38;
  char acStack_37 [23];
  char local_20 [32];
  
  local_48 = *(undefined2 *)(g_clientContext + 0x3f804);
  local_46 = *(undefined2 *)(g_clientContext + 0x41340);
  local_44 = *(undefined2 *)(g_clientContext + 0x44e60);
  local_50[0] = 0x12;
  local_42 = (ushort)(byte)((byte)((ushort)local_44 >> 8) ^ 0x6b) + (ushort)((byte)local_44 ^ 0x69)
             + (ushort)(byte)((byte)((ushort)local_46 >> 8) ^ 0x73) +
             (ushort)((byte)local_46 ^ 0x6d) + (ushort)(byte)((byte)((ushort)local_48 >> 8) ^ 0x6f)
             + (ushort)((byte)local_48 ^ 99);
  cVar2 = FUN_00426030(local_20);
  if (cVar2 == '\x01') {
    if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x18))(local_20,local_50,&DAT_00551cb1);
      return;
    }
  }
  else {
    local_38 = 0x69;
    iVar3 = 0;
    do {
      pcVar1 = local_20 + iVar3;
      acStack_37[iVar3] = *pcVar1;
      iVar3 = iVar3 + 1;
    } while (*pcVar1 != '\0');
    iVar4 = FUN_00404b00(&local_38);
    iVar3 = DAT_007934e8;
    if (iVar4 == 0) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar3 + 0x4d4) = 0x1020;
      *(undefined4 *)(iVar3 + 0x4d6) = *unaff_EDI;
      *(undefined4 *)(iVar3 + 0x4da) = unaff_EDI[1];
      *(undefined4 *)(iVar3 + 0x4de) = unaff_EDI[2];
      iVar4 = *(int *)(iVar3 + 0x44d0);
      *(int *)(iVar3 + 0x44d0) = iVar4 + 0xc;
      *(undefined1 *)(iVar4 + 0x4dc + iVar3) = 0;
      *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 1;
      EncodePacketBody();
      SendOutgoingPacket();
    }
    FUN_004026a0(0x2005,local_50,0x18);
  }
  return;
}

