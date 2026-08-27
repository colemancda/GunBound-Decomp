/* FUN_0050cff0 - 0x0050cff0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050cff0(int *param_1,uint param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  int local_1c;
  int local_18;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053be70) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (param_2 < (uint)param_1[1]) {
    iVar1 = param_1[1];
    /* 0x50d036-0x50d044: `mov esi,[edi+4]` = iVar1, `mov ecx,[ebp+0x14];
       add ecx,esi` = param_4 + iVar1, edx = edi = param_1, eax = -1.  This
       is the `jb` target, i.e. the param_2 < param_1[1] arm. */
    AtlArray_SetCount_450(param_4 + iVar1,param_1,-1);
    local_18 = iVar1 * 0x450 + *param_1;
    if (param_4 != 0) {
      local_1c = param_4;
      do {
        FUN_00426810(local_18);
        local_18 = local_18 + 0x450;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
    _memmove((void *)((param_4 + param_2) * 0x450 + *param_1),(void *)(param_2 * 0x450 + *param_1),
             (iVar1 - param_2) * 0x450);
    local_8 = 0;
    FUN_0044c870(*param_1 + param_2 * 0x450,param_4);
  }
  else {
    /* 0x50d01e-0x50d02c (the fall-through arm): `mov eax,[ebp+0x14];
       lea esi,[ebx+eax]` = param_2 + param_4, edx = edi = param_1,
       eax = -1. */
    AtlArray_SetCount_450(param_2 + param_4,param_1,-1);
  }
  uVar2 = param_2 + param_4;
  local_8 = 0xffffffff;
  /* DROPPED BASES RECOVERED (2026-08-27): 0x50d0e0-0x50d0f0 is
     `mov esi,[ebp+0x14]; imul esi,esi,0x450; add esi,[edi]` with edi =
     param_1, then `mov ebx,[ebp+0x10]` = param_3.  [ebp+0x14] is the dead
     param_4 slot reused as this loop's counter (`mov [ebp+0x14],ebx` at
     0x50d0db seeds it from param_2), which is the counter the C already
     spells param_2. */
  for (; param_2 < uVar2; param_2 = param_2 + 1) {
    AtlArray_CopyElement_450(param_2 * 0x450 + *param_1,(int)param_3);
  }
  return;
}

