/* FUN_0040b940 - 0x0040b940 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


exception * __thiscall FUN_0040b940(exception *param_1,exception *param_2)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537868;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  exception__ctor(param_1,param_2);
  local_4 = 0;
  *(undefined ***)param_1 = &PTR_FUN_00544b5c;
  *(undefined4 *)(param_1 + 0x24) = 0xf;
  *(undefined4 *)(param_1 + 0x20) = 0;
  param_1[0x10] = (exception)0x0;
  FUN_0040b9f0(param_2 + 0xc,0,0xffffffff);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

