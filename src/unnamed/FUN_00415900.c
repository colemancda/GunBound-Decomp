/* FUN_00415900 - 0x00415900 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 FUN_00415900(void)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  char cStack_10f51;
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
  OpenXFSArchive(auStack_10b50,1,0);
  iVar4 = FindXFSEntry(auStack_10750,s_FourWord_txt_00552c3c);
  if (((iVar4 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) ||
  /* ReadXFSEntry is void-returning - see src/fileformat/LoadChooseEventConfig.c's fix. */
     (ReadXFSEntry(iVar4,local_f708), iVar4 == 0)) {
    if (local_f710 != -1) {
      FUN_004f0d70();
    }
    local_3c = &PTR_FUN_005572dc;
    DeleteCriticalSection(&local_38);
    return 0;
  }
  iVar5 = 0;
  bVar1 = false;
  iVar3 = ReadXFSEntryByte(iVar4,&cStack_10f51);
  do {
    if (iVar3 == 0) {
      FUN_004f1460();
      if (local_f710 != -1) {
        FUN_004f0d70();
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
        FUN_00415bc0(acStack_10f50);
        iVar5 = 0;
      }
    }
    iVar3 = ReadXFSEntryByte(iVar4,&cStack_10f51);
  } while( true );
}

