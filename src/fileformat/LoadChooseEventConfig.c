/* LoadChooseEventConfig - 0x00409a10 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED ARGUMENT: Ghidra's decompile took this function as taking no
 * arguments, but the prologue at 0x409a2b (`push ecx`) saves an incoming
 * register argument to the stack before the security-cookie call, and
 * the disassembly shows it's read back at 0x409c35
 * (`mov esi,[ebp+0x8]`) right before the ParseChooseEventLine call at
 * 0x409c3c - i.e. this function forwards its own first argument into
 * ParseChooseEventLine as that callee's registry/event-table pointer.
 * The one real call site (entry/InitGame.c) already passes
 * `&DAT_00e9bea8` - a global also passed the same way elsewhere
 * (ui_widget/ParseChatSlashCommand.c's `FUN_00409c70(&DAT_00e9bea8)`) -
 * so it was being silently dropped on every call before this fix.
 *
 * FIXED (2026-07-15): the same class of XFS dropped-args already fixed
 * in LoadLocalizedStrings.c (this file's near-identical sibling), never
 * propagated here:
 *   - FindXFSEntry's real first arg is &g_xfsScratch, not auStack_10750
 *     (FindXFSEntry's own scratch result buffer).
 *   - ReadXFSEntry is 5-arg (readState, handle, flag, entry, lzhuf); only
 *     2 were supplied. handle/lzhuf come from g_xfsScratch+0x1040/+0x1048,
 *     matching every other ReadXFSEntry call site in the tree.
 *   - ReadXFSEntryByte's 3rd arg (count) was dropped at both call sites -
 *     count=1 (read one byte at a time), matching LoadLocalizedStrings.c.
 *   - FUN_004f0d70 (CloseXFSArchive) takes the archive `this` explicitly;
 *     both call sites here passed zero args - &g_xfsScratch, matching
 *     every other CloseXFSArchive call site.
 * Confirmed via:
 *   objdump -d -Mintel --start-address=0x409a10 --stop-address=0x409c40 \
 *     orig/GunBound.gme
 */
#include "xfs.h"
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 LoadChooseEventConfig(void *param_1)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  char cStack_10f55;
  undefined4 uStack_10f54;
  char acStack_10f50 [1024];
  undefined1 auStack_10b50 [1024];
  undefined1 auStack_10750 [8];
  undefined4 uStack_10748;
  undefined4 auStack_10710 [1024];
  int local_f710;
  undefined1 local_f70c;
  undefined1 local_f70b;
  undefined1 local_f708 [63180];
  undefined **local_3c;
  _RTL_CRITICAL_SECTION local_38;
  undefined4 uStack_1c;
  undefined4 local_c;

  local_c = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537bfb) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  uStack_1c = 0x409a36;
  local_3c = &PTR_FUN_005572dc;
  InitializeCriticalSection(&local_38);
  puVar5 = auStack_10710;
  for (iVar4 = 0x400; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  local_f710 = -1;
  local_f70c = 0;
  local_f70b = 1;
  uStack_10748 = 0;
  local_c = 0;
  BuildAssetPath(auStack_10b50,&DAT_005b1ed0,s_graphics_xfs_00551fdc,0);
  OpenXFSArchive(&g_xfsScratch,auStack_10b50,1,0);
  iVar4 = FindXFSEntry(&g_xfsScratch,s_ChooseEvent_txt_00551fcc);
  if (((iVar4 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) ||
     (uStack_10f54 = ReadXFSEntry(pvVar2,*(HANDLE *)(g_xfsScratch.bytes + 0x1040),1,iVar4,
                                   g_xfsScratch.bytes + 0x1048), uStack_10f54 == 0)) {
    if (local_f710 != -1) {
      FUN_004f0d70(&g_xfsScratch);
    }
    local_3c = &PTR_FUN_005572dc;
    DeleteCriticalSection(&local_38);
    return 0;
  }
  iVar4 = 0;
  bVar1 = false;
  iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55,1);
  do {
    if (iVar3 == 0) {
      CloseSpriteReadState();
      if (local_f710 != -1) {
        FUN_004f0d70(&g_xfsScratch);
      }
      local_3c = &PTR_FUN_005572dc;
      DeleteCriticalSection(&local_38);
      return 1;
    }
    if ((iVar4 == 0) && (cStack_10f55 == ';')) {
      bVar1 = true;
LAB_00409b81:
      acStack_10f50[iVar4] = cStack_10f55;
      iVar4 = iVar4 + 1;
    }
    else if (cStack_10f55 != '\r') {
      if (cStack_10f55 == '\t') {
        acStack_10f50[iVar4] = '\0';
        _atol(acStack_10f50);
        iVar4 = 0;
      }
      else if (cStack_10f55 == '\n') {
        if (bVar1) {
          iVar4 = 0;
          bVar1 = false;
        }
        else {
          if (iVar4 != 0) {
            acStack_10f50[iVar4] = '\0';
            ParseChooseEventLine(param_1, acStack_10f50, local_f710);
          }
          iVar4 = 0;
        }
      }
      else {
        if (((cStack_10f55 != 'n') || (iVar4 < 2)) || (acStack_10f50[iVar4 + -1] != '\\'))
        goto LAB_00409b81;
        acStack_10f50[iVar4 + -1] = '\n';
      }
    }
    iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55,1);
  } while( true );
}

