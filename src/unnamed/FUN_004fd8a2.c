/* FUN_004fd8a2 - 0x004fd8a2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fd8a2(void)

{
  int iVar1;
  int iVar2;
  char *_Dest;
  uint uVar3;
  undefined2 uStack00000004;
  int in_stack_00001778;
  char *in_stack_0000177c;
  
  uStack00000004 = 0;
  if (*(int *)(in_stack_00001778 + 4) != 0) {
    uStack00000004 =
         (undefined2)((*(int *)(in_stack_00001778 + 8) - *(int *)(in_stack_00001778 + 4)) / 0x12);
  }
  _Dest = &stack0x00000006;
  iVar2 = 0;
  for (uVar3 = 0;
      (iVar1 = *(int *)(in_stack_00001778 + 4), iVar1 != 0 &&
      (uVar3 < (uint)((*(int *)(in_stack_00001778 + 8) - iVar1) / 0x12))); uVar3 = uVar3 + 1) {
    _strncpy(_Dest,(char *)(iVar2 + iVar1),0x10);
    _Dest = _Dest + 0x10;
    iVar2 = iVar2 + 0x12;
  }
  _strncpy(_Dest,in_stack_0000177c,0x14);
  FUN_00502500(0x3004);
  return;
}

