/* FUN_0043c6a0 - 0x0043c6a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043c6a0(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  uVar4 = g_clientContext;
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ae1c;
  *unaff_FS_OFFSET = &local_c;
  iVar3 = GetPlayerRecordBySlot(uVar4);
  if (iVar3 != 0) {
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\0') {
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 != '\x01') {
        cVar2 = PeekPacketChecksumBool();
        iVar1 = iVar3 + 0x6744;
        if (cVar2 == '\x01') {
          uVar4 = FUN_0040a7d0(iVar1,local_89c,8);
          local_4 = 0;
          uVar5 = FUN_0040a4d0(&DAT_00796aa0);
          uVar4 = FUN_0040a8c0(uVar4,local_454,uVar5);
          local_4 = 1;
          FUN_0040afb0(uVar4);
          local_4 = 0;
          FUN_0040a2a0();
        }
        else {
          uVar4 = FUN_0040a7d0(iVar1,local_230,3);
          local_4 = 2;
          uVar5 = FUN_0040a4d0(&DAT_00796aa0);
          uVar4 = FUN_0040a8c0(uVar4,local_678,uVar5);
          local_4 = 3;
          FUN_0040afb0(uVar4);
          local_4 = 2;
          FUN_0040a2a0();
        }
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        cVar2 = FUN_0040b410(iVar3 + 0x6968,iVar1);
        if (cVar2 != '\0') {
          EncodeChecksumState(iVar1);
        }
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

