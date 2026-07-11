/* FUN_0043a670 - 0x0043a670 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043a670(void)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffffdb4;
  byte bVar1;
  int *piVar2;
  int iVar3;
  code *pcVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  int *piVar11;
  byte bVar12;
  code *pcVar13;
  int iVar14;
  undefined4 *unaff_FS_OFFSET;
  bool bVar15;
  char cVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined1 local_238 [28];
  int local_21c;
  undefined4 uStack_20;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053df6b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  piVar11 = *(int **)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar5 = piVar11[1];
  pcVar13 = (code *)EnterCriticalSection;
  if (uVar5 < 0x186a2) {
LAB_0043a6e0:
    if (uVar5 != 0x186a1) goto code_r0x0043a6e7;
    /* Ghidra also emitted a no-op store back to the EnterCriticalSection
     * import slot here ((code *)EnterCriticalSection = pcVar4) - a
     * function designator isn't an assignable lvalue in C, so the
     * self-store is dropped and only the load survives. */
    for (piVar2 = (int *)piVar11[4]; pcVar4 = (code *)EnterCriticalSection,
        piVar11 != piVar2; piVar2 = (int *)piVar2[4]) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      bVar12 = *(byte *)((int)piVar2 + 0x8bbd);
      bVar1 = *(byte *)((int)piVar2 + 0x8bbe);
      bVar15 = (byte)(bVar12 + bVar1 + -0x34) == *(char *)((int)piVar2 + 0x8bbf);
      if (!bVar15) {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (bVar15 && (bVar1 >> (bVar12 & 7) & 1) == 1) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(char *)(piVar2 + 0x22ea) = (char)iVar6;
        iVar6 = _rand();
        *(byte *)((int)piVar2 + 0x8ba9) = (byte)iVar6;
        bVar12 = ~('\x01' << (*(byte *)(piVar2 + 0x22ea) & 7)) & (byte)iVar6 |
                 '\0' << (*(byte *)(piVar2 + 0x22ea) & 7);
        *(byte *)((int)piVar2 + 0x8ba9) = bVar12;
        *(byte *)((int)piVar2 + 0x8baa) = bVar12 + (char)piVar2[0x22ea] + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(char *)((int)piVar2 + 0x8bb1) = (char)iVar6;
        iVar6 = _rand();
        *(byte *)((int)piVar2 + 0x8bb2) = (byte)iVar6;
        bVar12 = '\x01' << (*(byte *)((int)piVar2 + 0x8bb1) & 7);
        bVar12 = ~bVar12 & (byte)iVar6 | bVar12;
        *(byte *)((int)piVar2 + 0x8bb2) = bVar12;
        *(byte *)((int)piVar2 + 0x8bb3) = bVar12 + *(char *)((int)piVar2 + 0x8bb1) + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(char *)(piVar2 + 0x22ed) = (char)iVar6;
        iVar6 = _rand();
        *(byte *)((int)piVar2 + 0x8bb5) = (byte)iVar6;
        bVar12 = ~('\x01' << (*(byte *)(piVar2 + 0x22ed) & 7)) & (byte)iVar6 |
                 '\0' << (*(byte *)(piVar2 + 0x22ed) & 7);
        *(byte *)((int)piVar2 + 0x8bb5) = bVar12;
        *(byte *)((int)piVar2 + 0x8bb6) = bVar12 + (char)piVar2[0x22ed] + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      *(undefined2 *)(piVar2 + 0x2fef) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)(piVar2 + 0x2ff1) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)((int)piVar2 + 0xbfc5) = (byte)iVar6;
      bVar12 = ~('\x01' << (*(byte *)(piVar2 + 0x2ff1) & 7)) & (byte)iVar6 |
               '\0' << (*(byte *)(piVar2 + 0x2ff1) & 7);
      *(byte *)((int)piVar2 + 0xbfc5) = bVar12;
      *(byte *)((int)piVar2 + 0xbfc6) = bVar12 + (char)piVar2[0x2ff1] + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)((int)piVar2 + 0xbfc7) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)(piVar2 + 0x2ff2) = (byte)iVar6;
      bVar12 = *(byte *)((int)piVar2 + 0xbfc7) & 7;
      bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
      *(byte *)(piVar2 + 0x2ff2) = bVar12;
      *(byte *)((int)piVar2 + 0xbfc9) = bVar12 + *(char *)((int)piVar2 + 0xbfc7) + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)((int)piVar2 + 0xbfca) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)((int)piVar2 + 0xbfcb) = (byte)iVar6;
      bVar12 = *(byte *)((int)piVar2 + 0xbfca) & 7;
      bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
      *(byte *)((int)piVar2 + 0xbfcb) = bVar12;
      *(byte *)(piVar2 + 0x2ff3) = bVar12 + *(char *)((int)piVar2 + 0xbfca) + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)((int)piVar2 + 0xbfcd) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)((int)piVar2 + 0xbfce) = (byte)iVar6;
      bVar12 = *(byte *)((int)piVar2 + 0xbfcd) & 7;
      bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
      *(byte *)((int)piVar2 + 0xbfce) = bVar12;
      *(byte *)((int)piVar2 + 0xbfcf) = bVar12 + *(char *)((int)piVar2 + 0xbfcd) + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)(piVar2 + 0x2ff4) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)((int)piVar2 + 0xbfd1) = (byte)iVar6;
      bVar12 = ~('\x01' << (*(byte *)(piVar2 + 0x2ff4) & 7)) & (byte)iVar6 |
               '\0' << (*(byte *)(piVar2 + 0x2ff4) & 7);
      *(byte *)((int)piVar2 + 0xbfd1) = bVar12;
      *(byte *)((int)piVar2 + 0xbfd2) = bVar12 + (char)piVar2[0x2ff4] + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      piVar2[0x2ff8] = 0x60;
      *(undefined1 *)(piVar2 + 0x2ffa) = 1;
      piVar2[0x2ff7] = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 == 6) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(char *)((int)piVar2 + 0xbfbe) = (char)iVar6;
        iVar6 = _rand();
        *(byte *)((int)piVar2 + 0xbfbf) = (byte)iVar6;
        bVar12 = *(byte *)((int)piVar2 + 0xbfbe) & 7;
        bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
        *(byte *)((int)piVar2 + 0xbfbf) = bVar12;
        *(byte *)(piVar2 + 0x2ff0) = bVar12 + *(char *)((int)piVar2 + 0xbfbe) + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(char *)((int)piVar2 + 0xbfc1) = (char)iVar6;
        iVar6 = _rand();
        *(byte *)((int)piVar2 + 0xbfc2) = (byte)iVar6;
        bVar12 = *(byte *)((int)piVar2 + 0xbfc1) & 7;
        bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
        *(byte *)((int)piVar2 + 0xbfc2) = bVar12;
        *(byte *)((int)piVar2 + 0xbfc3) = bVar12 + *(char *)((int)piVar2 + 0xbfc1) + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      piVar2[0x2c2a] = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = (**(code **)(*piVar2 + 0x14))();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(uVar7);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pcVar13 = pcVar4;
    }
  }
LAB_0043a6b7:
  iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar5 = *(uint *)(iVar6 + 4);
  while( true ) {
    if (0x186a6 < uVar5) goto LAB_0043af1e;
    if (uVar5 == 0x186a6) break;
    iVar6 = *(int *)(iVar6 + 0x1c);
    uVar5 = *(uint *)(iVar6 + 4);
  }
  for (iVar3 = *(int *)(iVar6 + 0x10); iVar6 != iVar3; iVar3 = *(int *)(iVar3 + 0x10)) {
    (*pcVar13)(&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar18 = &DAT_005a9068;
    *(undefined4 *)(iVar3 + 0xaec) = 0;
    (*pcVar13)();
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar13)();
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar17 = &DAT_005a9068;
    (*pcVar13)();
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar13)(&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar8 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar13)(&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar13)(&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    cVar16 = (int)puVar18 < iVar8;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (cVar16 != '\0') {
      (*pcVar13)(&DAT_005a9068);
      iVar8 = PeekPacketChecksumState();
      cVar16 = iVar8 == 3;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (cVar16 != '\0') {
        (*pcVar13)(&DAT_005a9068);
        EncodeOutgoingPacketField(2);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
    }
    EncodeChecksumDeltaSub(iVar3 + 0x480,&stack0xfffffdb4,10);
    uStack_20 = 0;
    (*pcVar13)(&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar13)(&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar8) && (iVar14 = *(int *)(&g_nCameraBoundX + g_clientContext), iVar8 < iVar14)) {
      if ((int)puVar17 < 0) {
        puVar17 = (undefined *)0x0;
      }
      pcVar9 = (char *)((int)puVar17 * iVar14 + *(int *)(&DAT_006a773c + g_clientContext) + iVar8);
      for (; (int)puVar17 < *(int *)(&g_nCameraBoundY + g_clientContext); puVar17 = puVar17 + 1) {
        if (*pcVar9 != '\0') goto LAB_0043ae95;
        pcVar9 = pcVar9 + iVar14;
      }
    }
    puVar17 = (undefined *)0x2710;
LAB_0043ae95:
    (*pcVar13)(&DAT_005a9068);
    EncodeOutgoingPacketField(puVar17);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_21c != 0) {
      iVar8 = local_21c << 4;
      iVar14 = 0x10;
      do {
        iVar10 = _rand();
        *(char *)(iVar8 + DAT_0079376c) = (char)iVar10;
        iVar8 = iVar8 + 1;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
      TreeLowerBound(local_238);
      pcVar13 = (code *)EnterCriticalSection;
    }
  }
LAB_0043af1e:
  *unaff_FS_OFFSET = local_c;
  return;
code_r0x0043a6e7:
  piVar11 = (int *)piVar11[7];
  uVar5 = piVar11[1];
  if (0x186a1 < uVar5) goto LAB_0043a6b7;
  goto LAB_0043a6e0;
}

