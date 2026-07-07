/* FUN_00439d90 - 0x00439d90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00439d90(undefined4 param_1,int param_2)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  int unaff_ESI;
  int *piVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x6b8);
    piVar4 = (int *)0x0;
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      piVar4 = (int *)FUN_004abb70(pvVar2);
    }
    local_4 = 0xffffffff;
    piVar4[0xe] = param_2;
    piVar4[0xf] = unaff_ESI;
    piVar4[0x10] = unaff_ESI;
    iVar3 = FindPreloadedTextureByName(&DAT_00553b88);
    piVar4[7] = iVar3;
    (**(code **)(*piVar4 + 4))(s_normal_00552230);
    RegisterActiveObject();
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

