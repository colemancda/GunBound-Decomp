/* FUN_00405360 - 0x00405360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX RECOVERED (2026-08-25): `mov ebx,ecx` at 0x404dd9, and its caller
 * FUN_00404dd0 is __thiscall, so ECX is that function's param_1.  The two
 * pushes before it (`push eax; push ebp`) are the declared stack arguments --
 * `ret 8` confirms two -- and the `push esi; push edi` above them belong to
 * the caller's own prologue, not to this call.
 */
#include "ghidra_types.h"


undefined4 * FUN_00405360(undefined4 param_1,undefined4 *param_2,undefined4 *regEbx)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a95) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (regEbx[2] == 0) {
    if (regEbx[5] == 0) {
      puVar1 = _malloc(0x114);
      regEbx[5] = puVar1;
      if (puVar1 == (undefined4 *)0x0) goto LAB_004053a0;
      for (iVar2 = 0x45; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar1 = 0;
        puVar1 = puVar1 + 1;
      }
      *(undefined4 *)(regEbx[5] + 0x104) = 1;
      *(undefined4 *)(regEbx[5] + 0x10c) = regEbx[5];
      *(undefined4 *)(regEbx[5] + 0x108) = *(undefined4 *)(regEbx[5] + 0x10c);
      *(undefined4 *)(regEbx[5] + 0x110) = *(undefined4 *)(regEbx[5] + 0x108);
      *regEbx = regEbx[5];
    }
    puVar1 = _malloc(regEbx[4] * 0x114 + 4);
    if (puVar1 == (undefined4 *)0x0) {
LAB_004053a0:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *puVar1 = regEbx[3];
    regEbx[3] = puVar1;
    iVar2 = regEbx[4];
    puVar1 = puVar1 + iVar2 * 0x45 + -0x44;
    if (-1 < iVar2 + -1) {
      do {
        puVar1[0x42] = regEbx[2];
        regEbx[2] = puVar1;
        puVar1 = puVar1 + -0x45;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  puVar1 = (undefined4 *)regEbx[2];
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    ConstructStringFromText(puVar1);
    puVar3 = puVar1;
    for (iVar2 = 0x40; puVar3 = puVar3 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *param_2;
      param_2 = param_2 + 1;
    }
    puVar1[0x41] = 1;
    puVar1[0x44] = 0;
  }
  regEbx[2] = *(undefined4 *)(regEbx[2] + 0x108);
  puVar1[0x41] = 0;
  puVar1[0x42] = regEbx[5];
  puVar1[0x43] = regEbx[5];
  puVar1[0x44] = regEbx[5];
  regEbx[1] = regEbx[1] + 1;
  return puVar1;
}

