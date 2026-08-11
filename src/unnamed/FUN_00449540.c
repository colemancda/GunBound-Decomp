/* FUN_00449540 - 0x00449540 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SEH-PROLOGUE ARTIFACT FIX (2026-08-06): same bug class already fixed
 * in WidgetChildArray_Destroy.c / FUN_00443c20.c / FUN_0044fb40.c -
 * Ghidra's `unaff_FS_OFFSET` was an UNINITIALISED pointer the prologue
 * read and wrote through, faulting at entry (live: the next crash on
 * the AVATAR-click chain once the widget vtable was wired). The
 * original's `push -1 / push 0x53d8bb / mov fs:[0],esp` is a standard
 * MSVC exception frame; per the established idiom we don't reproduce
 * __try/__except frames in a bring-up port - stripped along with the
 * (write-only, SEH-unwind-only) `uStack_4` state marker and the
 * `uStack_10` return-address artifact.
 *
 * STORE-CATALOG RECOVERY (2026-08-11): this is the avatar-store catalog
 * loader - it scans the per-gender part tables via FUN_004240c0 (the
 * part-record loader) and fills the store's 9-slot item grid. All the
 * dropped-register holes recovered against the original disasm
 * (0x449540-0x449b40):
 *   - `partRecord[0x17d0]` is the frame-local part record at the
 *     original's frame+0x9c (`lea ecx,[esp+0x9c]` at 0x449606 feeds
 *     FUN_00425350, the record's 11-guard-cell ctor whose `this` Ghidra
 *     dropped; `lea esi,[esp+0xac]` right before the `call 0x4240c0`s
 *     at 0x4496e8/0x4497b9/0x4498e9 - esp+0xac at call time = the same
 *     frame+0x9c - and `lea esi,[esp+0x9c]` at 0x449a53 for the fourth).
 *     FUN_004254a0 at the end is the matching guard dtor on the same
 *     cell (0x449b11 `lea ecx,[esp+0x9c]`) - still argless here, out of
 *     this pass's scope.
 *   - The FIFTH FUN_004240c0 site (0x449adb) does NOT use the stack
 *     record: `mov edi,[esp+0x20]` (the auStack_1874 row cursor) /
 *     `lea esi,[edi-0x17a4]` - it reloads the part into the object's
 *     per-slot record (stride 0x17e4, text field at +0x17a4, matching
 *     FUN_00449b60/FUN_00449db0's per-slot layout at param_1+0x458).
 *   - `cStack_15b5` was the record's store-visibility flag: the orig
 *     reads `[esp+0x2d7]` = frame+0x9c+0x23b = partRecord[0x23b] (the
 *     byte FUN_004240c0 stores at outRecord+0x23b).
 *   - The 7 argless PeekPacketChecksumState() calls dropped their cells
 *     (EAX): the two per-gender per-category count-cell arrays at
 *     g_clientContext + param_2*0x224 + 0x5f4004 (female pass; lea at
 *     0x449699/0x44972a/0x44988f/0x44992b) and + 0x5f3774 (male pass;
 *     lea at 0x449764/0x4497fb), plus the record's own cell 0
 *     (0x449a6e `lea eax,[esp+0x9c]`) feeding the `%05d.img` icon-name
 *     sprintf. PeekPacketChecksumState's bring-up stub ignores args -
 *     behavior-neutral sweep pattern. */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_00449540(int param_1,undefined4 param_2)

{
  char *pcVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 auVar8; /* Ghidra register slot; was undefined1 [4] */
  undefined4 uVar9;
  undefined2 uVar10;
  int iVar11;
  undefined1 uVar12;
  undefined2 *puVar13;
  int iVar14;
  undefined4 *puVar15;
  byte *pbVar16;
  uint uVar17;
  undefined2 *puVar18;
  bool bVar19;
  int local_1878;
  undefined4 auStack_1874; /* Ghidra register slot; was undefined1 [4] */
  undefined4 uStack_1870;
  /* The frame-local part record (orig frame+0x9c, extent: name at
   * +0x224..0x237, flag +0x23b, guard cells to +0x1580, desc at
   * +0x17a4..+0x17cc) - see the 2026-08-11 header note. */
  undefined1 partRecord [0x17d0];

  puVar15 = (undefined4 *)(param_1 + 0x2d114);
  for (iVar11 = 0x10e; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar15 = 0;
    puVar15 = puVar15 + 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x44958b
   * (`lea edi,[esi+4]`, esi = this file's own param_1, confirmed by
   * objdump of orig/GunBound.gme matching this file's own `param_1 +
   * 0x2d114`-style offsets): the cell is param_1+4. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 4, 0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(param_1 + 0x44c) = param_2;
  *(undefined4 *)(param_1 + 0x450) = 0;
  uVar17 = 20000;
  local_1878 = 10;
  do {
    puVar15 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar5 = puVar15[1];
    if (uVar5 <= uVar17) {
LAB_004495d0:
      if (uVar5 != uVar17) goto code_r0x004495d2;
      puVar6 = (undefined4 *)puVar15[4];
      while (puVar6 != puVar15) {
        puVar7 = (undefined4 *)*puVar6;
        puVar6 = (undefined4 *)puVar6[4];
        (*(code *)*puVar7)(1);
      }
      puVar15[3] = puVar15;
      puVar15[4] = puVar15;
    }
LAB_004495fa:
    uVar17 = uVar17 + 1;
    local_1878 = local_1878 + -1;
  } while (local_1878 != 0);
  FUN_00425350((int)partRecord);
  iVar11 = g_clientContext;
  iVar14 = 0;
  local_1878 = 0;
  pbVar16 = (byte *)(g_clientContext + 0x3b498);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar2 = *pbVar16;
  bVar3 = *(byte *)(iVar11 + 0x3b499);
  bVar19 = (byte)(bVar2 + bVar3 + -0x34) == *(char *)(iVar11 + 0x3b49a);
  if (!bVar19) {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar19 && (bVar3 >> (bVar2 & 7) & 1) == 1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar11 = PeekPacketChecksumState((void *)(g_clientContext + (int)param_2 * 0x224 + 0x5f4004));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar11) {
      auStack_1874 = (undefined4)(param_1 + 0x2e54c);
      do {
        FUN_004240c0(g_clientContext,1,param_2,iVar14,(int)partRecord);
        if (partRecord[0x23b] != '\0') {
          *(undefined1 *)(local_1878 + 0x2d54c + param_1) = 1;
          local_1878 = local_1878 + 1;
          *(short *)auStack_1874 = (short)iVar14;
          auStack_1874 = (undefined4)((int)auStack_1874 + 2);
        }
        iVar14 = iVar14 + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar11 = PeekPacketChecksumState((void *)(g_clientContext + (int)param_2 * 0x224 + 0x5f4004));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      } while (iVar14 < iVar11);
    }
  }
  iVar14 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar11 = PeekPacketChecksumState((void *)(g_clientContext + (int)param_2 * 0x224 + 0x5f3774));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0 < iVar11) {
    auStack_1874 = (undefined4)(param_1 + 0x2e54c + local_1878 * 2);
    do {
      FUN_004240c0(g_clientContext,0,param_2,iVar14,(int)partRecord);
      if (partRecord[0x23b] != '\0') {
        *(undefined1 *)(local_1878 + 0x2d54c + param_1) = 0;
        local_1878 = local_1878 + 1;
        *(short *)auStack_1874 = (short)iVar14;
        auStack_1874 = (undefined4)((int)auStack_1874 + 2);
      }
      iVar14 = iVar14 + 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar11 = PeekPacketChecksumState((void *)(g_clientContext + (int)param_2 * 0x224 + 0x5f3774));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    } while (iVar14 < iVar11);
  }
  iVar11 = g_clientContext;
  pbVar16 = (byte *)(g_clientContext + 0x3b498);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar2 = *pbVar16;
  bVar3 = *(byte *)(iVar11 + 0x3b499);
  bVar19 = (byte)(bVar2 + bVar3 + -0x34) != *(char *)(iVar11 + 0x3b49a);
  if (bVar19) {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar19 || (bVar3 >> (bVar2 & 7) & 1) != 1) {
    iVar14 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar11 = PeekPacketChecksumState((void *)(g_clientContext + (int)param_2 * 0x224 + 0x5f4004));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar11) {
      auStack_1874 = (undefined4)(param_1 + 0x2e54c + local_1878 * 2);
      do {
        FUN_004240c0(g_clientContext,1,param_2,iVar14,(int)partRecord);
        if (partRecord[0x23b] != '\0') {
          *(undefined1 *)(local_1878 + 0x2d54c + param_1) = 1;
          local_1878 = local_1878 + 1;
          *(short *)auStack_1874 = (short)iVar14;
          auStack_1874 = (undefined4)((int)auStack_1874 + 2);
        }
        iVar14 = iVar14 + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar11 = PeekPacketChecksumState((void *)(g_clientContext + (int)param_2 * 0x224 + 0x5f4004));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      } while (iVar14 < iVar11);
    }
  }
  *(int *)(param_1 + 0x2d110) = local_1878;
  local_1878 = param_1 + 0x2d114;
  auStack_1874 = (undefined4)(param_1 + 0x1bfc);
  iVar11 = 0;
  puVar13 = (undefined2 *)(param_1 + 0x2e54c);
  do {
    iVar14 = *(int *)(param_1 + 0x450);
    if (*(int *)(param_1 + 0x2d110) <= iVar11 + iVar14 * 9) break;
    cVar4 = *(char *)(param_1 + 0x2d54c + iVar11);
    uVar10 = DAT_00555a18;
    uVar12 = DAT_00555a1a;
    if (cVar4 == '\x01') {
      uVar10 = DAT_00555a14;
      uVar12 = DAT_00555a16;
    }
    SUBFIELD(uStack_1870,0,undefined3) = CONCAT12(uVar12,uVar10);
    switch(param_2) {
    case 0:
      puVar18 = (undefined2 *)(auStack_1874 + 3);
      do {
        pcVar1 = (char *)((int)puVar18 + 1);
        puVar18 = (undefined2 *)((int)puVar18 + 1);
      } while (*pcVar1 != '\0');
      *puVar18 = DAT_00552c80;
      break;
    case 1:
      puVar18 = (undefined2 *)(auStack_1874 + 3);
      do {
        pcVar1 = (char *)((int)puVar18 + 1);
        puVar18 = (undefined2 *)((int)puVar18 + 1);
      } while (*pcVar1 != '\0');
      *puVar18 = DAT_005535f0;
      break;
    case 2:
      puVar18 = (undefined2 *)(auStack_1874 + 3);
      do {
        pcVar1 = (char *)((int)puVar18 + 1);
        puVar18 = (undefined2 *)((int)puVar18 + 1);
      } while (*pcVar1 != '\0');
      *puVar18 = DAT_00552c7c;
      break;
    case 3:
      uStack_1870 = &DAT_00666d73;
    }
    FUN_004240c0(g_clientContext,CONCAT31((int3)((uint)iVar14 >> 8),cVar4 == '\x01'),param_2,*puVar13,
                 (int)partRecord);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState((void *)partRecord);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf((char *)((int)&uStack_1870 + 3),s__05d_img_00555a08,uVar9);
    LoadSpriteSet(&DAT_00ea0e18,iVar11 + 20000);
    auVar8 = auStack_1874;
    /* Fifth part-load reloads into the OBJECT's per-slot record, not the
     * stack one: orig 0x449acf-0x449ad4 `mov edi,[esp+0x20]` (= this row's
     * auStack_1874 text cursor) / `lea esi,[edi-0x17a4]`. */
    FUN_004240c0(g_clientContext,*(char *)(param_1 + 0x2d54c + iVar11) == '\x01',param_2,*puVar13,
                 (int)auVar8 - 0x17a4);
    RenderWrappedText(local_1878,auVar8,0x18,0x15,0x78,1);
    iVar11 = iVar11 + 1;
    auStack_1874 = (undefined4)((int)auVar8 + 0x17e4);
    local_1878 = local_1878 + 0x78;
    puVar13 = puVar13 + 1;
  } while (iVar11 < 9);
  FUN_004254a0();
  return;
code_r0x004495d2:
  puVar15 = (undefined4 *)puVar15[7];
  uVar5 = puVar15[1];
  if (uVar17 < uVar5) goto LAB_004495fa;
  goto LAB_004495d0;
}

