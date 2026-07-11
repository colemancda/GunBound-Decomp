/* FUN_0045f5d0 - 0x0045f5d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_0045f5d0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_ac8 [8];
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053a187;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = FUN_00406860();
  if (cVar1 != '\0') {
    *unaff_FS_OFFSET = local_c;
    return 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 < 1) {
    uVar3 = EncodeChecksumNegate(param_1 + 0x62f8,local_230);
    local_4 = 2;
    uVar3 = EncodeChecksumDeltaSub(uVar3,local_678,4);
    SUBFIELD(local_4,0,undefined1) = 3;
    EncodeChecksumDeltaDiv(uVar3,local_89c,10);
    SUBFIELD(local_4,0,undefined1) = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 3;
    if (local_888 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_ac8);
    }
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
    if (local_664 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_ac8);
    }
    local_4 = 0xffffffff;
    if (local_21c == 0) goto LAB_0045f7ff;
    ScrambleChecksumGuardBytes();
  }
  else {
    uVar3 = EncodeChecksumDeltaAdd(param_1 + 0x62f8,local_ac0,4);
    local_4 = 0;
    EncodeChecksumDeltaDiv(uVar3,local_454,10);
    SUBFIELD(local_4,0,undefined1) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
    if (local_440 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_ac8);
    }
    local_4 = 0xffffffff;
    if (local_aac == 0) goto LAB_0045f7ff;
    ScrambleChecksumGuardBytes();
  }
  FUN_0040b540(local_ac8);
LAB_0045f7ff:
  if (4 < iVar2) {
    iVar2 = 5;
  }
  *unaff_FS_OFFSET = local_c;
  return *(undefined4 *)(&DAT_005a960c + (iVar2 % 6) * 4);
}

