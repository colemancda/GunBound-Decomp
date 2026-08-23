/* FUN_004986a0 - 0x004986a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 14 argless PeekPacketChecksumState() calls.  Cells: the
 * globals 0xe9ba40 / 0xe9bed8 / 0x794bf0 / 0xe55ab8, the projectile's
 * own param_1 + 0x10 (`lea eax,[ebx+0x40]` at 0x498784 and the
 * frame-parked copies read at 0x498888 / 0x4989c9), and the delta
 * helpers' arg2 scratch cells - EncodeChecksumDeltaSub's local_89c
 * (0x498754 / 0x498819) and EncodeChecksumDeltaAdd's local_454
 * (0x498957), which the following Peek reads (the helpers return their
 * arg2, see tools/sweep_guard_instructions.md).
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
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539797;
  *unaff_FS_OFFSET = &local_c;
  if (*(char *)(param_1 + 0x3fc4) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)(&DAT_00e9bed8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = *(int *)(param_1 + 0x3fa4) + iVar1;
    iVar3 = iVar1 / iVar2;
    iVar1 = iVar1 % iVar2;
    *(int *)(param_1 + 0x3fa4) = iVar1;
    *(int *)(param_1 + 0x3fbc) = iVar1;
    goto LAB_00498b38;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(&DAT_00794bf0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x264,local_89c,uVar4);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState((void *)(local_89c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4987a9:
   * EDI/x = return of the 2nd PeekPacketChecksumState() above (iVar8), EAX/y
   * = return of the 1st (iVar7) - both discarded by Ghidra since it
   * mis-modeled this call's real ECX/EDX/EDI/EAX convention. */
  local_8a0 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar8,iVar7);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8b0,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(&DAT_00794bf0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x264,local_678,uVar4);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x40,local_89c,uVar4);
  SUBFIELD(local_4,0,undefined1) = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState((void *)(local_89c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4988aa:
   * EDI/x = return of the 2nd PeekPacketChecksumState() above (iVar8), EAX/y
   * = return of the 1st (iVar7) - both discarded by Ghidra, same convention
   * mismatch as the call above. */
  iVar3 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar8,iVar7);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    local_8b0[0] = (*(int *)(local_89c + 0x14));
    TreeLowerBound(local_8a8,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    local_8b0[0] = (*(int *)(local_678 + 0x14));
    TreeLowerBound(local_8a8,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(&DAT_00794bf0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x264,local_230,uVar4);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = EncodeChecksumDeltaAdd(param_1 + 0x40,local_454,local_8b0[0]);
  SUBFIELD(local_4,0,undefined1) = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState((void *)(local_454));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState((void *)(local_454));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4989eb:
   * EDI/x = local_8b0[0] (the PeekPacketChecksumState() return captured just
   * above); EAX/y = return of the PREVIOUS PeekPacketChecksumState() call
   * (iVar9, discarded by Ghidra). */
  iVar2 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),local_8b0[0],iVar9);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
  local_8b0[0] = (*(int *)(local_454 + 0x14));
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a8,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  local_8b0[0] = (*(int *)(local_230 + 0x14));
  if ((*(int *)(local_230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a8,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(&DAT_00e55ab8));
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

