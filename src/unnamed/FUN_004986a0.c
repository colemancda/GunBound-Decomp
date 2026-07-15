/* FUN_004986a0 - 0x004986a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004986a0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *unaff_FS_OFFSET;
  int local_8b0 [2];
  undefined1 local_8a8 [8];
  int local_8a0;
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
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539797;
  *unaff_FS_OFFSET = &local_c;
  if (*(char *)(param_1 + 0x3fc4) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = *(int *)(param_1 + 0x3fa4) + iVar1;
    iVar3 = iVar1 / iVar2;
    iVar1 = iVar1 % iVar2;
    *(int *)(param_1 + 0x3fa4) = iVar1;
    *(int *)(param_1 + 0x3fbc) = iVar1;
    goto LAB_00498b38;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x264,local_89c,uVar4);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4987a9:
   * EDI/x = return of the 2nd PeekPacketChecksumState() above (iVar8), EAX/y
   * = return of the 1st (iVar7) - both discarded by Ghidra since it
   * mis-modeled this call's real ECX/EDX/EDI/EAX convention. */
  local_8a0 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar8,iVar7);
  local_4 = 0xffffffff;
  if (local_888 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8b0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x264,local_678,uVar4);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x40,local_89c,uVar4);
  SUBFIELD(local_4,0,undefined1) = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4988aa:
   * EDI/x = return of the 2nd PeekPacketChecksumState() above (iVar8), EAX/y
   * = return of the 1st (iVar7) - both discarded by Ghidra, same convention
   * mismatch as the call above. */
  iVar3 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar8,iVar7);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  if (local_888 != 0) {
    ScrambleChecksumGuardBytes();
    local_8b0[0] = local_888;
    TreeLowerBound(local_8a8);
  }
  local_4 = 0xffffffff;
  if (local_664 != 0) {
    ScrambleChecksumGuardBytes();
    local_8b0[0] = local_664;
    TreeLowerBound(local_8a8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x264,local_230,uVar4);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = EncodeChecksumDeltaAdd(param_1 + 0x40,local_454,local_8b0[0]);
  SUBFIELD(local_4,0,undefined1) = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4989eb:
   * EDI/x = local_8b0[0] (the PeekPacketChecksumState() return captured just
   * above); EAX/y = return of the PREVIOUS PeekPacketChecksumState() call
   * (iVar9, discarded by Ghidra). */
  iVar2 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),local_8b0[0],iVar9);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
  local_8b0[0] = local_440;
  if (local_440 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a8);
  }
  local_4 = 0xffffffff;
  local_8b0[0] = local_21c;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = iVar1 + local_8a0;
  if (iVar1 < iVar3) {
    iVar5 = local_8a0;
    iVar6 = local_8a0;
    if (iVar2 <= iVar1) {
      if (iVar2 < iVar1) {
        iVar3 = local_8a0 * 2 - iVar2;
      }
      goto LAB_00498abd;
    }
  }
  else {
LAB_00498abd:
    iVar5 = iVar3;
    iVar6 = iVar2;
    if ((iVar1 < iVar2) && (iVar3 < iVar1)) {
      iVar6 = local_8a0 * 2 - iVar3;
    }
  }
  iVar3 = 0x14;
  for (iVar6 = iVar6 - iVar5;
      (((iVar3 < -0x7f || (0x80 < iVar3)) || (iVar6 < -0x7f)) || (0x80 < iVar6)); iVar6 = iVar6 / 2)
  {
    iVar3 = iVar3 / 2;
  }
  iVar2 = (int)*(short *)(&DAT_00598e7e + (iVar6 * 0x100 + iVar3) * 2);
  *(int *)(param_1 + 0x3fa4) = iVar2;
  if (0x10e < iVar2) {
    iVar2 = iVar2 + -0x168;
  }
  *(int *)(param_1 + 0x3fa4) = -iVar2;
  iVar3 = -iVar2;
  if (*(int *)(param_1 + 0x3fa8) != 0) {
    iVar3 = iVar2;
  }
  *(int *)(param_1 + 0x3fbc) = iVar3;
LAB_00498b38:
  *unaff_FS_OFFSET = local_c;
  return iVar3;
}

