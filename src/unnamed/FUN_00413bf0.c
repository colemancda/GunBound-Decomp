/* FUN_00413bf0 - 0x00413bf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00413bf0(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  byte bVar7;
  int iVar8;
  byte *pbVar9;
  int iVar10;
  int local_8;
  
  iVar8 = DAT_007934e8;
  *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x4412;
  *(undefined4 *)(iVar8 + 0x44d0) = 6;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = DAT_007934e8;
  *(undefined2 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar5;
  *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 2;
  local_8 = 0;
  iVar10 = 0;
  do {
    if (*(char *)(DAT_005b3484 + 0x5010d + local_8) != '\0') {
      *(char *)(*(int *)(iVar8 + 0x44d0) + 0x4d0 + iVar8) = (char)local_8;
      *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = DAT_007934e8;
      *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar6;
      iVar8 = *(int *)(iVar3 + 0x44d0);
      *(int *)(iVar3 + 0x44d0) = iVar8 + 4;
      if (*(short *)(&DAT_006aa660 + DAT_005b3484) == -1) {
        *(undefined2 *)(iVar8 + 0x4d4 + iVar3) = 0;
      }
      else {
        *(ushort *)(iVar8 + 0x4d4 + iVar3) =
             (ushort)(*(char *)(DAT_005b3484 + 0x62155) ==
                     *(char *)(DAT_005b3484 + 0x50126 + local_8));
      }
      *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = DAT_007934e8;
      *(undefined2 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar5;
      *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = DAT_007934e8;
      *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar6;
      *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = DAT_007934e8;
      *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar6;
      iVar4 = DAT_005b3484;
      iVar3 = *(int *)(iVar8 + 0x44d0);
      *(int *)(iVar8 + 0x44d0) = iVar3 + 4;
      cVar1 = *(char *)(iVar4 + 0x62155);
      if (cVar1 == -1) {
        *(undefined1 *)(iVar3 + 0x4d4 + iVar8) = 2;
      }
      else {
        *(bool *)(iVar3 + 0x4d4 + iVar8) = cVar1 == *(char *)(iVar4 + 0x50126 + local_8);
      }
      *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 1;
    }
    local_8 = local_8 + 1;
    iVar10 = iVar10 + 0x224;
  } while (iVar10 < 0x1120);
  FUN_004d25e0();
  if (DAT_00793514 == '\0') {
    FUN_004d2680();
  }
  iVar8 = DAT_005b3484;
  pbVar9 = (byte *)(DAT_005b3484 + 0x62152);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = _rand();
  *pbVar9 = (byte)iVar10;
  iVar10 = _rand();
  bVar2 = *pbVar9;
  *(byte *)(iVar8 + 0x62153) = (byte)iVar10;
  bVar7 = '\x01' << (bVar2 & 7);
  bVar7 = ~bVar7 & (byte)iVar10 | bVar7;
  *(byte *)(iVar8 + 0x62153) = bVar7;
  *(byte *)(iVar8 + 0x62154) = bVar7 + bVar2 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

