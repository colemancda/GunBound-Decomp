/* FUN_0043e150 - 0x0043e150 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DEFINITION COMPLETED AND ESI RECOVERED (2026-08-25).  `ret 8`: two stack
 * arguments -- the node key and value FUN_0043e0f0 already pushed -- against
 * a definition declaring one.  ESI is the map object, FUN_0043e0f0's own ECX
 * parameter, unchanged between that function's entry `mov esi,ecx` and this
 * call.
 */
#include "ghidra_types.h"


undefined4 * FUN_0043e150(undefined4 param_1,undefined4 param_2,undefined4 *regEsi)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a95;
  *unaff_FS_OFFSET = &local_c;
  if (regEsi[2] == 0) {
    if (regEsi[5] == 0) {
      puVar1 = _malloc(0x18);
      regEsi[5] = puVar1;
      if (puVar1 == (undefined4 *)0x0) goto LAB_0043e189;
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1[2] = 0;
      puVar1[3] = 0;
      puVar1[4] = 0;
      puVar1[5] = 0;
      *(undefined4 *)(regEsi[5] + 8) = 1;
      *(undefined4 *)(regEsi[5] + 0x10) = regEsi[5];
      *(undefined4 *)(regEsi[5] + 0xc) = *(undefined4 *)(regEsi[5] + 0x10);
      *(undefined4 *)(regEsi[5] + 0x14) = *(undefined4 *)(regEsi[5] + 0xc);
      *regEsi = regEsi[5];
    }
    puVar1 = _malloc(regEsi[4] * 0x18 + 4);
    if (puVar1 == (undefined4 *)0x0) {
LAB_0043e189:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *puVar1 = regEsi[3];
    regEsi[3] = puVar1;
    iVar2 = regEsi[4];
    puVar1 = puVar1 + iVar2 * 6 + -5;
    if (-1 < iVar2 + -1) {
      do {
        puVar1[3] = regEsi[2];
        regEsi[2] = puVar1;
        puVar1 = puVar1 + -6;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  puVar1 = (undefined4 *)regEsi[2];
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    ConstructStringFromText(puVar1 + 1);
    puVar1[2] = 1;
    puVar1[5] = 0;
  }
  regEsi[2] = *(undefined4 *)(regEsi[2] + 0xc);
  puVar1[2] = 0;
  puVar1[3] = regEsi[5];
  puVar1[4] = regEsi[5];
  puVar1[5] = regEsi[5];
  regEsi[1] = regEsi[1] + 1;
  *unaff_FS_OFFSET = local_c;
  return puVar1;
}

