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
 */
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
  OpenXFSArchive(auStack_10b50,1,0);
  iVar5 = FindXFSEntry(auStack_10750,s_Language_txt_00554008);
  if (((iVar5 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) ||
     (uStack_10f54 = ReadXFSEntry(iVar5,local_f708), uStack_10f54 == 0)) {
    if (local_f710 != -1) {
      FUN_004f0d70();
    }
    local_3c = &PTR_FUN_005572dc;
    DeleteCriticalSection(&local_38);
    *unaff_FS_OFFSET = local_14;
    return 0;
  }
  iVar5 = 0;
  bVar1 = false;
  iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55);
  iVar4 = uStack_10f54;
  do {
    if (iVar3 == 0) {
      FUN_004f1460();
      if (local_f710 != -1) {
        FUN_004f0d70();
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
            FUN_0043dd40(param_1);
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
    iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55);
  } while( true );
}

