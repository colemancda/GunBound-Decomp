/* FUN_0040bee0 - 0x0040bee0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARG FIX (2026-09-20): __thiscall with 3 real params (ECX=`this`
 * + ret 8 = 2 stack dwords, disasm 0x40bee0-0x40bf8b) - a VC7
 * std::string::assign(const char*,size_t)-shaped helper (classic SSO
 * layout: +4 buffer/pointer, +0x14 length, +0x18 capacity, confirmed at
 * 0x40bee1 `mov ebx,ecx` then `[ebx+0x18]`/`[ebx+0x14]`/`[ebx+4]`). All 8
 * callers had NO prototype in functions.h and wrote only the (str,len)
 * pair, dropping `this` entirely - confirmed at the FUN_0040b9b0 call
 * site (0x40b9db `mov ecx,esi; call 0x40bee0` with esi = that function's
 * own `this`, pushed str=edx/len=eax first). The 7 exception-string
 * sites (FUN_00426460, FUN_005030a0, FUN_0040bae0, FUN_0040b600,
 * FUN_004e87b0, FUN_004e8b10, FUN_00443840) all build the same
 * `local_50`-based SEH exception object (each immediately followed by
 * `FUN_00409fd0(local_50)`), so `this` = `(int)local_50` there; the
 * 8th site (FUN_0040b9b0) threads its own `param_1` (a string ctor).
 */
#include "ghidra_types.h"


int __thiscall FUN_0040bee0(int param_1,undefined4 *param_2,uint param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  uVar4 = *(uint *)(param_1 + 0x18);
  if (uVar4 < 0x10) {
    puVar1 = (undefined4 *)(param_1 + 4);
  }
  else {
    puVar1 = *(undefined4 **)(param_1 + 4);
  }
  if (puVar1 <= param_2) {
    puVar1 = (undefined4 *)(param_1 + 4);
    puVar3 = puVar1;
    if (0xf < uVar4) {
      puVar3 = (undefined4 *)*puVar1;
    }
    if (param_2 < (undefined4 *)(*(int *)(param_1 + 0x14) + (int)puVar3)) {
      if (0xf < uVar4) {
        puVar1 = (undefined4 *)*puVar1;
      }
      /* DROPPED-ARG FIX (2026-09-21): FUN_0040b9f0 is a 4-arg __thiscall
         (this,srcObj,srcPos,count) - confirmed self-substring-assign at
         orig 0x40bf1f-0x40bf26 (`push ecx(len); push esi(offset); push
         ebx(this); mov ecx,ebx; call`), i.e. srcObj=this itself (the
         self-overlapping-assign safe path). The ported call dropped the
         srcObj argument entirely, shifting offset/len one slot left. */
      iVar2 = FUN_0040b9f0(param_1,param_1,(int)param_2 - (int)puVar1,param_3);
      return iVar2;
    }
  }
  if (param_3 == 0xffffffff) {
    FUN_00520291();
  }
  if (*(uint *)(param_1 + 0x18) < param_3) {
    FUN_0040bfd0(param_1,param_3,*(undefined4 *)(param_1 + 0x14));
  }
  else if (param_3 == 0) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    if (*(uint *)(param_1 + 0x18) < 0x10) {
      *(undefined1 *)(param_1 + 4) = 0;
      return param_1;
    }
    **(undefined1 **)(param_1 + 4) = 0;
    return param_1;
  }
  if (param_3 != 0) {
    if (*(uint *)(param_1 + 0x18) < 0x10) {
      puVar1 = (undefined4 *)(param_1 + 4);
    }
    else {
      puVar1 = *(undefined4 **)(param_1 + 4);
    }
    for (uVar4 = param_3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar1 = *param_2;
      param_2 = param_2 + 1;
      puVar1 = puVar1 + 1;
    }
    for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar1 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      puVar1 = (undefined4 *)((int)puVar1 + 1);
    }
    *(uint *)(param_1 + 0x14) = param_3;
    if (0xf < *(uint *)(param_1 + 0x18)) {
      *(undefined1 *)(*(int *)(param_1 + 4) + param_3) = 0;
      return param_1;
    }
    *(undefined1 *)(param_1 + 4 + param_3) = 0;
  }
  return param_1;
}

