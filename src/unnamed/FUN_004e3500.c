/* FUN_004e3500 - 0x004e3500 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 FUN_004e3500(undefined4 param_1)

{
  char *pcVar1;
  bool bVar2;
  bool bVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *unaff_FS_OFFSET;
  char cStack_11351;
  char acStack_11350 [1024];
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
  uStack_1c = 0x4e3526;
  local_3c = &PTR_FUN_005572dc;
  InitializeCriticalSection(&local_38);
  puVar8 = auStack_10710;
  for (iVar6 = 0x400; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  local_f710 = -1;
  local_f70c = 0;
  local_f70b = 1;
  uStack_10748 = 0;
  local_c = 0;
  BuildAssetPath(auStack_10b50,&DAT_005b1ed0,s_graphics_xfs_00551fdc,0);
  OpenXFSArchive(auStack_10b50,1,0);
  iVar6 = FindXFSEntry(auStack_10750,s_Sound_txt_00557218);
  if (((iVar6 == 0) || (pvVar4 = operator_new(0x1024), pvVar4 == (void *)0x0)) ||
     (iVar6 = ReadXFSEntry(iVar6,local_f708), iVar6 == 0)) {
    if (local_f710 != -1) {
      FUN_004f0d70();
    }
    local_3c = &PTR_FUN_005572dc;
    DeleteCriticalSection(&local_38);
    *unaff_FS_OFFSET = local_14;
    return 0;
  }
  bVar2 = false;
  iVar7 = 0;
  bVar3 = false;
  iVar5 = ReadXFSEntryByte(iVar6,&cStack_11351);
  do {
    if (iVar5 == 0) {
      FUN_004f1460();
      if (local_f710 != -1) {
        FUN_004f0d70();
      }
      local_3c = &PTR_FUN_005572dc;
      DeleteCriticalSection(&local_38);
      *unaff_FS_OFFSET = local_14;
      return 1;
    }
    if ((iVar7 == 0) && (cStack_11351 == ';')) {
      bVar3 = true;
LAB_004e3667:
      acStack_11350[iVar7] = cStack_11351;
      iVar7 = iVar7 + 1;
    }
    else if (cStack_11351 != '\r') {
      if (cStack_11351 == '\t') {
        acStack_11350[iVar7] = '\0';
        iVar7 = 0;
        do {
          pcVar1 = acStack_11350 + iVar7;
          acStack_10f50[iVar7] = *pcVar1;
          iVar7 = iVar7 + 1;
        } while (*pcVar1 != '\0');
        iVar7 = 0;
        bVar2 = true;
      }
      else {
        if (cStack_11351 != '\n') goto LAB_004e3667;
        if (bVar3) {
          iVar7 = 0;
          bVar3 = false;
          bVar2 = false;
        }
        else {
          acStack_11350[iVar7] = '\0';
          if (bVar2) {
            FUN_00426620(param_1,acStack_11350);
          }
          iVar7 = 0;
          bVar2 = false;
        }
      }
    }
    iVar5 = ReadXFSEntryByte(iVar6,&cStack_11351);
  } while( true );
}

