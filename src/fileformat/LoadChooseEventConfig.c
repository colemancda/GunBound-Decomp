/* LoadChooseEventConfig - 0x00409a10 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 LoadChooseEventConfig(void)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
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
  OpenXFSArchive(auStack_10b50,1,0);
  iVar4 = FindXFSEntry(auStack_10750,s_ChooseEvent_txt_00551fcc);
  if (((iVar4 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) ||
     (uStack_10f54 = ReadXFSEntry(iVar4,local_f708), uStack_10f54 == 0)) {
    if (local_f710 != -1) {
      FUN_004f0d70();
    }
    local_3c = &PTR_FUN_005572dc;
    DeleteCriticalSection(&local_38);
    *unaff_FS_OFFSET = local_14;
    return 0;
  }
  iVar4 = 0;
  bVar1 = false;
  iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55);
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
            ParseChooseEventLine();
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
    iVar3 = ReadXFSEntryByte(uStack_10f54,&cStack_10f55);
  } while( true );
}

