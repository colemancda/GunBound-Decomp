/* LoadFourWordList - 0x00415900 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * WRONG-ARCHIVE FIX (2026-07-29): FindXFSEntry was called with
 * `auStack_10750` - an 8-byte local buffer that's never written before
 * this call - instead of `&g_xfsScratch`, the archive OpenXFSArchive was
 * just opened into two lines above. Confirmed via objdump: the original
 * uses the SAME register (esi) for both the OpenXFSArchive and
 * FindXFSEntry calls (0x415912-0x41592c region); LoadChooseEventConfig.c
 * and LoadLocalizedStrings.c already get this right (both calls use
 * &g_xfsScratch), this file and the identical LoadSoundConfig.c did not.
 * With the wrong pointer, FindXFSEntry read `*(int*)(auStack_10750+8)` as
 * a garbage-nonzero "entry count" off uninitialised stack, entered its
 * binary search, and fed CompareXFSEntryName a NULL record pointer -
 * reproduced live as a page fault in CompareXFSEntryName on the main
 * thread during InitGame, independent of any user interaction.
 *
 * ReadXFSEntry/ReadXFSEntryByte DROPPED-ARGS FIX (2026-07-30): this file
 * never got the same migration LoadChooseEventConfig.c/LoadLocalizedStrings.c
 * (its near-identical siblings - same BuildAssetPath+OpenXFSArchive+
 * FindXFSEntry+read-loop shape) already went through. `ReadXFSEntry` is a
 * real 5-arg function - `(readState, handle, flag, entry, lzhuf)`,
 * returning the initialised readState - not the 2-arg void call this file
 * had (`ReadXFSEntry(iVar4, local_f708)`, passing the entry record as
 * readState and a dead 63180-byte stack buffer as nothing in particular).
 * `pvVar2` (the `operator_new(0x1024)` right above it) was always the real
 * readState buffer - already allocated, just never passed anywhere.
 * `ReadXFSEntryByte` likewise takes `(readState, outBuf, count)`, not the
 * `(entryRecord, outBuf)` this file called it with - so every "read" was
 * actually reading raw fields of the XFS entry record/TOC struct starting
 * from whatever `iVar4` pointed to, not real file bytes; for this entry
 * that memory ran long stretches of 0x00 with no CR/LF, so the line-buffer
 * loop below (LAB_00415a5e, itself unbounded even in the original - see
 * disasm at orig 0x415a5e, no bounds check there either) just kept writing
 * past `acStack_10f50[1024]` until it corrupted enough of the stack to
 * fault deep in unrelated code - what an earlier session misdiagnosed as
 * an unfixable wine `__chkstk` guard-page bug (the crash's simple .map
 * resolution pointed at this function but wasn't confirmed against the
 * actual faulting instruction). Fixed to match the sibling files' already-
 * objdump-verified pattern exactly: handle/lzhuf come from
 * g_xfsScratch.bytes+0x1040/+0x1048, flag=1, count=1. With this fix the
 * dead 63180-byte `local_f708` local (LoadChooseEventConfig.c keeps the
 * same dead local, unused, for the same reason) is no longer referenced at
 * all, so it's dropped rather than kept as inert stack padding - this
 * also removes the multi-page `__chkstk` prologue this function used to
 * need, which is a nice side effect but not why the crash is fixed.
 *
 * AppendWordFilterEntry CALL-SITE FIX (2026-07-30): `AppendWordFilterEntry(acStack_10f50)`
 * dropped that function's real `this` (the word-filter AtlArray header at
 * g_wordFilterArrayHeader, was DAT_00e9c9dc/DAT_00e9c9e0 - see
 * globals_sized.c) and passed the parsed line as if it were `this` instead
 * of the actual 2nd argument. See AppendWordFilterEntry.c's own header for the full
 * objdump-confirmed detail.
 *
 * CloseSpriteReadState/FUN_004f0d70 CALL-SITE FIX (2026-07-30): both were
 * still called with zero args here, matching CloseSpriteReadState.c's own
 * header ("NOT FIXED HERE" list includes this file). `archive` is
 * &g_xfsScratch for both - confirmed via objdump (orig 0x415a77-0x415a91):
 * CloseSpriteReadState's 2nd arg (edi) is the SAME register reused right
 * after as FUN_004f0d70/CloseXFSArchive's own archive arg, and every other
 * CloseXFSArchive call site in the tree (LoadChooseEventConfig.c,
 * LoadLocalizedStrings.c) already uses &g_xfsScratch - the only archive
 * this function ever opens. `readState` is this file's own read-state
 * cursor (same variable ReadXFSEntry/ReadXFSEntryByte already use).
 */
#include "xfs.h"
#include "ghidra_types.h"


undefined4 LoadFourWordList(void)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 readState;
  char cStack_10f51;
  char acStack_10f50 [1024];
  undefined1 auStack_10b50 [1024];
  undefined1 auStack_10750 [8];
  undefined4 uStack_10748;
  undefined4 auStack_10710 [1024];
  int local_f710;
  undefined1 local_f70c;
  undefined1 local_f70b;
  undefined **local_3c;
  _RTL_CRITICAL_SECTION local_38;
  undefined4 uStack_1c;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined4 local_c;

  local_c = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537bfb) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  uStack_1c = 0x415926;
  local_3c = &PTR_FUN_005572dc;
  InitializeCriticalSection(&local_38);
  puVar6 = auStack_10710;
  for (iVar4 = 0x400; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  local_f710 = -1;
  local_f70c = 0;
  local_f70b = 1;
  uStack_10748 = 0;
  local_c = 0;
  BuildAssetPath(auStack_10b50,&DAT_005b1ed0,s_graphics_xfs_00551fdc,0);
  OpenXFSArchive(&g_xfsScratch,auStack_10b50,1,0);
  iVar4 = FindXFSEntry(&g_xfsScratch,s_FourWord_txt_00552c3c);
  if (((iVar4 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) ||
     (readState = ReadXFSEntry(pvVar2,*(HANDLE *)(g_xfsScratch.bytes + 0x1040),1,iVar4,
                                g_xfsScratch.bytes + 0x1048), readState == 0)) {
    if (local_f710 != -1) {
      FUN_004f0d70(&g_xfsScratch);
    }
    local_3c = &PTR_FUN_005572dc;
    DeleteCriticalSection(&local_38);
    return 0;
  }
  iVar5 = 0;
  bVar1 = false;
  iVar3 = ReadXFSEntryByte(readState,&cStack_10f51,1);
  do {
    if (iVar3 == 0) {
      CloseSpriteReadState(readState,(int)&g_xfsScratch);
      if (local_f710 != -1) {
        FUN_004f0d70(&g_xfsScratch);
      }
      local_3c = &PTR_FUN_005572dc;
      DeleteCriticalSection(&local_38);
      return 1;
    }
    if ((iVar5 == 0) && (cStack_10f51 == ';')) {
      bVar1 = true;
LAB_00415a5e:
      acStack_10f50[iVar5] = cStack_10f51;
      iVar5 = iVar5 + 1;
    }
    else if (cStack_10f51 != '\r') {
      if (cStack_10f51 != '\n') goto LAB_00415a5e;
      if (bVar1) {
        bVar1 = false;
        iVar5 = 0;
      }
      else {
        acStack_10f50[iVar5] = '\0';
        AppendWordFilterEntry((int *)&g_wordFilterArrayHeader,acStack_10f50);
        iVar5 = 0;
      }
    }
    iVar3 = ReadXFSEntryByte(readState,&cStack_10f51,1);
  } while( true );
}
