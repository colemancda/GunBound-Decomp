/* CArray_Add_1750 - 0x004fedd0 in the original binary.
 *
 * CArray::Add for the 0x1750-byte-record array: reserve one more element
 * through CArray_Grow_1750, copy the caller's record into the slot with
 * CArray_CopyElement_1750, bump the count, and return the index the element
 * landed at.
 *
 * SIGNATURE COMPLETED (2026-08-25).  Two things were missing at once:
 *
 *   - `ret 4` says there is one stack parameter, but Ghidra declared the
 *     function `(void)`.  Both call sites in FUN_004fe110 were already
 *     passing it (`lea eax,[esp+0x20]; push eax` = &local_2eb8); only the
 *     definition was short, so the value fell through to `mov edx,[esp+0xc]`
 *     at 0x4fee02 and was handed to CArray_CopyElement_1750 as its EDX.
 *   - EAX is the vector object.  At 0x4fe1ea it is `lea eax,[ebx+0x80]` and
 *     at 0x4fe3f5 `lea eax,[esi+0x80]`, and both EBX (0x4fe186) and ESI
 *     (0x4fe3dc) are loaded from the SAME caller slot [esp+0xc], the
 *     local FUN_004fe860 fills = local_2ecc.  So both sites pass the same
 *     expression and no site pairing was needed.
 *
 * The body is a std::vector-style push_back: reserve one more element, then
 * copy the caller's record into slot uVar1 at stride 0x1750.
 */
#include "ghidra_types.h"


uint CArray_Add_1750(undefined4 *param_1,int *regEax)

{
  uint uVar1;
  char cVar2;
  
  uVar1 = regEax[1];
  if ((uint)regEax[2] <= uVar1) {
    cVar2 = CArray_Grow_1750(uVar1 + 1,regEax);
    if (cVar2 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  if (uVar1 * 0x1750 + *regEax != 0) {
    CArray_CopyElement_1750(0,param_1,(undefined4 *)(uVar1 * 0x1750 + *regEax));
  }
  regEax[1] = regEax[1] + 1;
  return uVar1;
}

