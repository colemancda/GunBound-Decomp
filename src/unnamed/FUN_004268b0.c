/* FUN_004268b0 - 0x004268b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BOTH REGISTERS RECOVERED (2026-08-24, workflow-analysed, hand-checked).
 * An ATL-array grow: regEsi is the array header at g_clientContext + 0x44be8
 * (the caller computes it into piVar14 on the line above), regEax the
 * required capacity, current count + 1 (`lea eax,[edi+1]` where edi =
 * [ctx+0x44bec], which the source already holds in uVar11).  Straight-line
 * block, no jump lands between the loads and the call.
 */
#include "ghidra_types.h"


undefined4 FUN_004268b0(uint regEax,int *regEsi)

{
  void *pvVar1;
  uint uVar2;
  if (regEax <= (uint)regEsi[2]) {
    return 1;
  }
  uVar2 = regEsi[3];
  if (*regEsi == 0) {
    if (regEax < uVar2) {
      regEax = uVar2;
    }
    pvVar1 = _malloc(regEax * 0x9c);
    *regEsi = (int)pvVar1;
    if (pvVar1 != (void *)0x0) {
      regEsi[2] = regEax;
      return 1;
    }
  }
  else {
    if (uVar2 == 0) {
      uVar2 = (uint)regEsi[1] >> 3;
      if (uVar2 < 4) {
        uVar2 = 4;
      }
      else if (0x400 < uVar2) {
        uVar2 = 0x400;
      }
    }
    uVar2 = uVar2 + regEsi[2];
    if (uVar2 <= regEax) {
      uVar2 = regEax;
    }
    pvVar1 = _malloc(uVar2 * 0x9c);
    if (pvVar1 != (void *)0x0) {
      _memmove(pvVar1,(void *)*regEsi,regEsi[1] * 0x9c);
      _free((void *)*regEsi);
      *regEsi = (int)pvVar1;
      regEsi[2] = uVar2;
      return 1;
    }
  }
  return 0;
}

