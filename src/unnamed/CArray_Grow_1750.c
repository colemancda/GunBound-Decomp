/* CArray_Grow_1750 - 0x005001f0 in the original binary.
 *
 * Growth for an MFC-shaped dynamic array of 0x1750-byte records.  The object
 * is the CArray layout exactly -- data at +0, count at +4, capacity at +8,
 * growBy at +0xc -- and the growth rule is CArray::SetSize's to the letter:
 * when growBy is zero, use count/8 clamped to [4, 1024].  Returns 0 when the
 * allocation fails, which is what its callers turn into E_OUTOFMEMORY.
 *
 * EAX and ESI RECOVERED (2026-08-25) from the single call site 0x4fede1 in
 * CArray_Add_1750: EAX is `lea eax,[edi+1]` where EDI = the vector's count
 * (uVar1), so the requested capacity is uVar1 + 1; ESI is the vector object
 * itself, which its caller now names regEax.  This is the grow half of the
 * push_back in CArray_Add_1750 -- element stride 0x1750, growth by an eighth
 * clamped to [4, 0x400].
 */
#include "ghidra_types.h"


undefined4 CArray_Grow_1750(uint regEax,int *regEsi)

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

