/* FUN_005001f0 - 0x005001f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX and ESI RECOVERED (2026-08-25) from the single call site 0x4fede1 in
 * FUN_004fedd0: EAX is `lea eax,[edi+1]` where EDI = the vector's count
 * (uVar1), so the requested capacity is uVar1 + 1; ESI is the vector object
 * itself, which its caller now names regEax.  This is the grow half of the
 * push_back in FUN_004fedd0 -- element stride 0x1750, growth by an eighth
 * clamped to [4, 0x400].
 */
#include "ghidra_types.h"


undefined4 FUN_005001f0(uint regEax,int *regEsi)

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
    pvVar1 = _malloc(regEax * 0x1750);
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
    pvVar1 = _malloc(uVar2 * 0x1750);
    if (pvVar1 != (void *)0x0) {
      _memmove(pvVar1,(void *)*regEsi,regEsi[1] * 0x1750);
      _free((void *)*regEsi);
      *regEsi = (int)pvVar1;
      regEsi[2] = uVar2;
      return 1;
    }
  }
  return 0;
}

