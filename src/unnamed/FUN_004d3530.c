/* FUN_004d3530 - 0x004d3530 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_004d3530(int param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *unaff_FS_OFFSET;
  int local_5464;
  undefined1 local_545c [8];
  undefined1 local_5454 [20];
  int local_5440;
  undefined1 local_5230 [20];
  int local_521c;
  undefined4 local_500c [5119];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005390e6;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4d354f;
  local_5464 = *(int *)(param_1 + 0x84d8);
  if (local_5464 < *(int *)(param_1 + 0x84d4)) {
    local_5464 = *(int *)(param_1 + 0x84d4);
  }
  if (*(int *)(param_1 + 0x84dc) != -1) {
    iVar5 = local_5464 - *(int *)(param_1 + 0x84dc);
    EncodePacketBlocks(*(undefined4 *)(param_1 + 0x84e8),*(undefined2 *)(param_1 + 0x44d8),local_500c,
                 0x5000);
    uVar6 = ((iVar5 + 5) / 0xc) * 0x10;
    puVar7 = local_500c;
    puVar8 = (undefined4 *)(*(int *)(param_1 + 0x84dc) + 0x44da + param_1);
    for (uVar3 = (((int)uVar6 < 0) - 1 & uVar6) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
    local_5464 = local_5464 + (uVar6 - (iVar5 + -6));
  }
  *(short *)(param_1 + 0x44d4) = (short)local_5464;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar5 + local_5464);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = EncodeChecksumDeltaMul(param_1 + 0x84,local_5454,0x343fd);
  local_4 = 0;
  EncodeChecksumDeltaAdd(uVar2,local_5230,0x269ec3);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  *(undefined2 *)(param_1 + 0x44d6) = uVar1;
  if (local_521c != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_545c);
  }
  local_4 = 0xffffffff;
  if (local_5440 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_545c);
  }
  SendSocketData(*(undefined4 *)(param_1 + 0x84e0),local_5464);
  *(undefined4 *)(param_1 + 0x84ec) = 0;
  *unaff_FS_OFFSET = local_c;
  return;
}

