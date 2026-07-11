/* FUN_004780e0 - 0x004780e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004780e0(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00537e85;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  *param_1 = &PTR_FUN_00555fdc;
  local_4 = 0x10;
  if (param_1[0x822] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0xf;
  if (param_1[0x799] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0xe;
  iVar2 = param_1[0x790];
  if (iVar2 != 0) {
    uVar3 = param_1[0x791];
    uVar6 = 0;
    if (uVar3 != 0) {
      do {
        iVar4 = *(int *)(iVar2 + uVar6 * 4);
        puVar5 = (undefined4 *)(iVar4 + -0x10);
        piVar1 = (int *)(iVar4 + -4);
        LOCK();
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 + -1 < 1) {
          (**(code **)(*(int *)*puVar5 + 4))(puVar5);
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < uVar3);
    }
    _free((void *)param_1[0x790]);
  }
  local_4 = 0xd;
  if (param_1[0x70c] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0xc;
  if (param_1[0x682] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0xb;
  if (param_1[0x5f9] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 10;
  if (param_1[0x570] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 9;
  if (param_1[0x4e7] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 8;
  if (param_1[0x45e] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 7;
  if (param_1[0x3d5] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 6;
  if (param_1[0x34a] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 5;
  if (param_1[0x2c1] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 4;
  if (param_1[0x237] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 3;
  if (param_1[0x1ae] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 2;
  if (param_1[0x125] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 1;
  if (param_1[0x9c] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0;
  if (param_1[0x13] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = uStack_c;
  return;
}

