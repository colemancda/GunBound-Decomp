/* CArray_Grow_206 - 0x004e8fc0 in the original binary.
 *
 * The same array growth as CArray_Grow_1750, at a 0x206-byte stride.
 *
 * EAX and ESI RECOVERED (2026-08-25): another vector grow, the same shape as
 * CArray_Grow_1750.  Every call site is `lea eax,[ebp+1]` (the requested capacity,
 * count + 1) with ESI the vector object, immediately after the caller has
 * compared the count against the capacity.
 */
#include "ghidra_types.h"


undefined4 CArray_Grow_206(uint regEax,int *regEsi)

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
    pvVar1 = _malloc(regEax * 0x206);
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
    pvVar1 = _malloc(uVar2 * 0x206);
    if (pvVar1 != (void *)0x0) {
      _memmove(pvVar1,(void *)*regEsi,regEsi[1] * 0x206);
      _free((void *)*regEsi);
      *regEsi = (int)pvVar1;
      regEsi[2] = uVar2;
      return 1;
    }
  }
  return 0;
}

