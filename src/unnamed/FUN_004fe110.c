/* FUN_004fe110 - 0x004fe110 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): the 3 FUN_004feb00() calls here
 * (lines ~132/142/148, orig 0x4fe28b/0x4fe2ba/0x4fe2f0) were each missing
 * the callee's leading __thiscall arg. Disassembly of all 3 sites shows
 * `mov ecx,[ebp+0xc]` (= this function's own `param_3`) immediately
 * before every `call 0x4feb00`; the 4 already-present stack arguments
 * (param_2, &local_2eb8, &uStack_2ec8, local_2ecc[6]) were already
 * correctly positioned. See FUN_004feb00.c's header for the callee-side
 * evidence.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20, THIS function's own callers).
 * include/functions.h had no prototype for FUN_004fe110 itself either,
 * so its own callers compiled without argument-count checking. Its own
 * declared shape is CORRECT: genuinely __thiscall with param_1=ECX
 * ("this") plus 5 stack dwords (`ret 0x14` at the epilogue 0x4fe405 =
 * 0x14/4 = 5), matching all 6 existing formal parameters 1:1. All 3
 * callers (FUN_004fcf10.c, FUN_004fcf70.c, FUN_004fe8d0.c) were dropping
 * the ECX argument entirely - and two of the three also had one
 * already-present stack argument wrong, a separate pre-existing bug
 * (see each caller's own header for its call-site evidence). Fixed by
 * adding a real functions.h prototype and, at each call site, passing
 * the correct `this` value.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall
FUN_004fe110(undefined4 *param_1,int *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5,uint param_6)

{
  int iVar1;
  char cVar2;
  UINT_PTR UVar3;
  uint uVar4;
  undefined4 *puVar5;
  int *local_2ecc;
  undefined2 uStack_2ec8;
  undefined2 uStack_2ec6;
  undefined2 uStack_2ec4;
  undefined2 uStack_2ec2;
  undefined2 uStack_2ec0;
  undefined4 uStack_2ebe;
  undefined2 uStack_2eba;
  undefined4 local_2eb8;
  undefined4 local_2eb4;
  undefined4 local_2eb0;
  undefined2 local_2eac;
  ushort uStack_2eaa;
  undefined4 auStack_2ea8 [1487];
  __time32_t _Stack_176c;
  undefined1 auStack_1768 [5964];
  _FILETIME _Stack_1c;
  undefined4 uStack_14;
  undefined1 uStack_10;
  undefined4 uStack_c;
  
  uStack_c = 0x4fe120;
  if ((ushort)param_6 < 0x173b) {
    cVar2 = FUN_004fe860(param_2,&local_2ecc);
    uStack_2eaa = (ushort)param_6;
    if (cVar2 == '\0') {
      (**(code **)(*param_2 + 4))(param_3);
      if (cVar2 == '\0') {
        (**(code **)*param_2)(0,param_3,param_4,param_5,param_6,param_1);
        return 1;
      }
      cVar2 = FUN_004fe860(param_2,&local_2ecc);
      if (cVar2 == '\0') {
        FUN_004fe8d0(param_3,0,0,0,0);
        cVar2 = FUN_004fe860(param_2,&local_2ecc);
        if (cVar2 == '\0') {
          return 0;
        }
        local_2eb8 = *param_1;
        local_2eb0 = param_1[2];
        local_2eb4 = param_1[1];
        local_2eac = (undefined2)param_4;
        puVar5 = auStack_2ea8;
        for (uVar4 = (param_6 & 0xffff) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar5 = *param_5;
          param_5 = param_5 + 1;
          puVar5 = puVar5 + 1;
        }
        for (param_6 = param_6 & 3; param_6 != 0; param_6 = param_6 - 1) {
          *(undefined1 *)puVar5 = *(undefined1 *)param_5;
          param_5 = (undefined4 *)((int)param_5 + 1);
          puVar5 = (undefined4 *)((int)puVar5 + 1);
        }
        _Stack_176c = FID_conflict___time32((__time32_t *)0x0);
        CArray_Add_1750(&local_2eb8,(int *)(local_2ecc + 0x20));
        *(undefined1 *)(local_2ecc + 7) = 1;
        return 1;
      }
    }
    if ((char)local_2ecc[7] != '\0') {
      local_2eb8 = *param_1;
      local_2eb4 = param_1[1];
      local_2eb0 = param_1[2];
      local_2eac = (undefined2)param_4;
      puVar5 = auStack_2ea8;
      for (uVar4 = (param_6 & 0xffff) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar5 = *param_5;
        param_5 = param_5 + 1;
        puVar5 = puVar5 + 1;
      }
      for (param_6 = param_6 & 3; param_6 != 0; param_6 = param_6 - 1) {
        *(undefined1 *)puVar5 = *(undefined1 *)param_5;
        param_5 = (undefined4 *)((int)param_5 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
      _Stack_176c = FID_conflict___time32((__time32_t *)0x0);
      CArray_Add_1750(&local_2eb8,(int *)(local_2ecc + 0x20));
      return 1;
    }
    local_2eb4 = param_1[1];
    local_2eb8 = *param_1;
    uStack_2ec6 = 0;
    uStack_2ec4 = 0;
    uStack_2ec2 = 0;
    uStack_2ec0 = 0;
    uStack_2ebe = 0;
    uStack_2eba = 0;
    local_2eb0 = param_1[2];
    local_2eac = (undefined2)param_4;
    puVar5 = auStack_2ea8;
    for (uVar4 = (param_6 & 0xffff) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar5 = *param_5;
      param_5 = param_5 + 1;
      puVar5 = puVar5 + 1;
    }
    iVar1 = local_2ecc[6];
    for (param_6 = param_6 & 3; param_6 != 0; param_6 = param_6 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)param_5;
      param_5 = (undefined4 *)((int)param_5 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    local_2ecc[6] = iVar1 + 1;
    uStack_2ec8 = 2;
    iVar1 = *local_2ecc;
    if (iVar1 == 0) {
      iVar1 = local_2ecc[2];
      if (iVar1 != 0) {
        uStack_2ec4 = (undefined2)iVar1;
        uStack_2ec2 = (undefined2)((uint)iVar1 >> 0x10);
        uStack_2ec6 = (undefined2)local_2ecc[3];
        cVar2 = FUN_004feb00((char *)param_3,(int)param_2,(int)&local_2eb8,(sockaddr *)&uStack_2ec8,
                             local_2ecc[6]);
        if (cVar2 == '\0') {
          return 0;
        }
      }
      iVar1 = local_2ecc[4];
      if (iVar1 == 0) goto LAB_004fe2fc;
      uStack_2ec4 = (undefined2)iVar1;
      uStack_2ec2 = (undefined2)((uint)iVar1 >> 0x10);
      uStack_2ec6 = (undefined2)local_2ecc[5];
      cVar2 = FUN_004feb00((char *)param_3,(int)param_2,(int)&local_2eb8,(sockaddr *)&uStack_2ec8,
                             local_2ecc[6]);
    }
    else {
      uStack_2ec4 = (undefined2)iVar1;
      uStack_2ec2 = (undefined2)((uint)iVar1 >> 0x10);
      uStack_2ec6 = (undefined2)local_2ecc[1];
      cVar2 = FUN_004feb00((char *)param_3,(int)param_2,(int)&local_2eb8,(sockaddr *)&uStack_2ec8,
                             local_2ecc[6]);
    }
    if (cVar2 != '\0') {
LAB_004fe2fc:
      GetSystemTimeAsFileTime(&_Stack_1c);
      uStack_14 = 0;
      uStack_10 = 0;
      FUN_004fe590(0,(undefined4 *)auStack_1768,(undefined4 *)&local_2eb8);
      FUN_004fed40(local_2ecc + 0x14,auStack_1768,local_2ecc[6]);
      if (param_2[0xb0] == 0) {
        UVar3 = SetTimer((HWND)param_2[0xa3],0x14a,900,(TIMERPROC)0x0);
        param_2[0xb0] = UVar3;
      }
      return 1;
    }
  }
  return 0;
}

