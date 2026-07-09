/* FUN_00426620 - 0x00426620 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __thiscall FUN_00426620(undefined4 param_1,int *param_2,char *param_3)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffffd4;
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_20 [4];
  int local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537a80;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_14 = &stack0xffffffd4;
  iVar2 = FUN_00426780(&local_1c,&local_18,local_20);
  if (iVar2 == 0) {
    if ((*param_2 == 0) && (cVar1 = FUN_00500c00(param_2,param_2[2],1), cVar1 == '\0')) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
    iVar2 = FUN_00426960(param_2,param_1,local_18);
    local_8 = 0;
    iVar4 = iVar2 + 4;
    pcVar3 = param_3;
    local_1c = iVar2;
    if (param_3 != (char *)0x0) {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
  }
  else {
    iVar4 = iVar2 + 4;
    pcVar3 = param_3;
    if (param_3 != (char *)0x0) {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
  }
  FUN_004056c0(iVar4,param_3);
  *unaff_FS_OFFSET = local_10;
  return iVar2;
}

