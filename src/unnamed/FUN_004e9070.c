/* FUN_004e9070 - 0x004e9070 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-13): `unaff_ESI` is a dropped register, not garbage -
 * confirmed via objdump that it arrives unchanged (no prior MOV to ESI,
 * `ret` with no operand). Sole caller is GameTick at 0x413440:
 * `mov esi,0xf22650; call 0x4e9070` - a fixed literal, already declared
 * as `DAT_00f22650` (a sprite-cache-slot table, see ShutdownDirectDraw.c/
 * InitDirectDraw.c uses of the same global) - hardcoded rather than
 * threading a parameter through, matching InvokeWidget's registry-base
 * precedent.
 */
#include "ghidra_types.h"


void FUN_004e9070(void)

{
  void *pvVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  int base;
  int *piVar5;
  int local_4;

  base = (int)DAT_00f22650;
  *(undefined4 *)(base + 0x1000) = 0;
  local_4 = 0;
  if (0 < *(int *)(base + 0x1008)) {
    piVar5 = (int *)(base + 0x100c);
    do {
      uVar2 = *(uint *)(base + 0x1000);
      iVar4 = (int)(uVar2 + ((int)uVar2 >> 0x1f & 0x3ffU)) >> 10;
      uVar2 = uVar2 & 0x800003ff;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xfffffc00) + 1;
      }
      if (*(int *)(base + iVar4 * 4) == 0) {
        pvVar1 = operator_new(0x4000);
        *(void **)(base + iVar4 * 4) = pvVar1;
      }
      *(int *)(base + 0x1000) = *(int *)(base + 0x1000) + 1;
      puVar3 = (undefined2 *)(uVar2 * 0x10 + *(int *)(base + iVar4 * 4));
      *piVar5 = (int)puVar3;
      *puVar3 = 0;
      *(undefined2 *)(*piVar5 + 2) = *(undefined2 *)(base + 0x1004);
      *(undefined1 *)(*piVar5 + 4) = 0;
      *(undefined4 *)(*piVar5 + 8) = 0;
      *(undefined4 *)(*piVar5 + 0xc) = 0;
      local_4 = local_4 + 1;
      piVar5 = piVar5 + 1;
    } while (local_4 < *(int *)(base + 0x1008));
  }
  return;
}
