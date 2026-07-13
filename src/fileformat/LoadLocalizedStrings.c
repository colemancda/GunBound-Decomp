/* LoadLocalizedStrings - 0x0043da00 in the original binary.
 *
 * Builds the localized UI-string table (g_localizedStringTable, param_1)
 * that GetLocalizedString later indexes. Opens graphics.xfs, finds the
 * "Language.txt" entry (FindXFSEntry), reads it a byte at a time
 * (ReadXFSEntryByte), and parses its "<id>\t<message>\r\n" lines into the
 * id -> string map. Called once from InitGame. This is the load half of
 * the text-localization subsystem; see ARCHITECTURE.md "Text
 * localization" and FILEFORMATS.md's Language.txt entry.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified
 * (the SEH frame and the line-parse loop's exact bounds are Ghidra-shaped).
 * See src/README.md's "Raw/verbatim ports" section for status.
 *
 * Dropped-register-arg fixes (confirmed against the 0x43da00 disassembly;
 * same class already fixed in rendering/LoadSpriteSet.c and the other
 * FindXFSEntry/ReadXFSEntry callers):
 *   - FindXFSEntry's real first arg is the XFS archive object, not the
 *     8-byte auStack_10750 (that's FindXFSEntry's *own* result buffer in
 *     the original scattered stack frame). Passes &g_xfsScratch, matching
 *     the OpenXFSArchive call two lines above and xfs.h's bring-up note.
 *   - ReadXFSEntry is a 5-arg function (readState, handle, flag, entry,
 *     lzhuf) - Ghidra's per-call-site decompile only resolved 2 of them
 *     here. handle/lzhuf recovered from g_xfsScratch+0x1040/+0x1048 (disasm:
 *     `mov eax,[esp+0x1858]` / `lea ecx,[esp+0x1860]` right before
 *     `call 0x4f0380`, with dl=1 and edi=the FindXFSEntry entry pointer).
 *   - ReadXFSEntryByte's 3rd arg (count) was dropped at both call sites;
 *     disasm shows `mov eax,0x1` immediately before both `call 0x4f06c0`s,
 *     i.e. count=1 (read one byte at a time, matching the function name).
 *   - FUN_004f0d70 (CloseXFSArchive) takes the archive `this` in ESI,
 *     already promoted to an explicit parameter in its own file; disasm
 *     shows `lea esi,[esp+0x818/0x824]` (the same stack-local-turned-
 *     g_xfsScratch archive) right before both calls here. Passes
 *     &g_xfsScratch, matching directx_init/ShutdownDirectDraw.c's fix.
 *   - FUN_0043dd40 (the map-insert helper for the id -> string entry) is
 *     a 3-arg call (id, table, message) - Ghidra's per-call-site decompile
 *     only resolved the one stack-passed arg (param_1/table) and dropped
 *     id/message entirely. Disasm at 0x43dc25-0x43dc2f shows `mov ecx,edi`
 *     (id) and `lea eax,[esp+0x1c]` (message, acStack_10f50) loaded right
 *     before `call 0x43dd40`, with param_1 pushed on the stack just above.
 *     FUN_0043dd40 itself promoted to match (its own `in_EAX` read for the
 *     message pointer was the same dropped-arg pattern).
 */
#include "xfs.h"
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 LoadLocalizedStrings(undefined4 param_1)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *unaff_FS_OFFSET;
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
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_00537bfb;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  uStack_1c = 0x43da26;
  local_3c = &PTR_FUN_005572dc;
  InitializeCriticalSection(&local_38);
  puVar6 = auStack_10710;
  for (iVar5 = 0x400; iVar5 != 0; iVar5 = iVar5 + -1) {
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
  iVar5 = FindXFSEntry(&g_xfsScratch,s_Language_txt_00554008);
  if (((iVar5 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) ||
     (uStack_10f54 = ReadXFSEntry(pvVar2,*(HANDLE *)(g_xfsScratch.bytes + 0x1040),1,iVar5,
                                   g_xfsScratch.bytes + 0x1048), uStack_10f54 == 0)) {
    if (local_f710 != -1) {
      FUN_004f0d70(&g_xfsScratch);
    }
    local_3c = &PTR_FUN_005572dc;
    DeleteCriticalSection(&local_38);
    *unaff_FS_OFFSET = local_14;
    return 0;
  }
  iVar5 = 0;
  bVar1 = false;
  iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55,1);
  iVar4 = uStack_10f54;
  do {
    if (iVar3 == 0) {
      FUN_004f1460();
      if (local_f710 != -1) {
        FUN_004f0d70(&g_xfsScratch);
      }
      local_3c = &PTR_FUN_005572dc;
      DeleteCriticalSection(&local_38);
      *unaff_FS_OFFSET = local_14;
      return 1;
    }
    if ((iVar5 == 0) && (cStack_10f55 == ';')) {
      bVar1 = true;
LAB_0043db71:
      acStack_10f50[iVar5] = cStack_10f55;
      iVar5 = iVar5 + 1;
    }
    else if (cStack_10f55 != '\r') {
      if (cStack_10f55 == '\t') {
        acStack_10f50[iVar5] = '\0';
        iVar4 = _atol(acStack_10f50);
        iVar5 = 0;
      }
      else if (cStack_10f55 == '\n') {
        if (bVar1) {
          iVar5 = 0;
          bVar1 = false;
          iVar4 = 0;
        }
        else {
          acStack_10f50[iVar5] = '\0';
          if (iVar4 != 0) {
            FUN_0043dd40(iVar4,param_1,acStack_10f50);
          }
          iVar5 = 0;
          iVar4 = 0;
        }
      }
      else {
        if (((cStack_10f55 != 'n') || (iVar5 < 2)) || (acStack_10f50[iVar5 + -1] != '\\'))
        goto LAB_0043db71;
        acStack_10f50[iVar5 + -1] = '\n';
      }
    }
    iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55,1);
  } while( true );
}

