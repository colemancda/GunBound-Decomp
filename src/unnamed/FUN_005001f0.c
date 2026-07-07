/* FUN_005001f0 - 0x005001f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_005001f0(void)

{
  uint in_EAX;
  void *pvVar1;
  uint uVar2;
  int *unaff_ESI;
  
  if (in_EAX <= (uint)unaff_ESI[2]) {
    return 1;
  }
  uVar2 = unaff_ESI[3];
  if (*unaff_ESI == 0) {
    if (in_EAX < uVar2) {
      in_EAX = uVar2;
    }
    pvVar1 = _malloc(in_EAX * 0x1750);
    *unaff_ESI = (int)pvVar1;
    if (pvVar1 != (void *)0x0) {
      unaff_ESI[2] = in_EAX;
      return 1;
    }
  }
  else {
    if (uVar2 == 0) {
      uVar2 = (uint)unaff_ESI[1] >> 3;
      if (uVar2 < 4) {
        uVar2 = 4;
      }
      else if (0x400 < uVar2) {
        uVar2 = 0x400;
      }
    }
    uVar2 = uVar2 + unaff_ESI[2];
    if (uVar2 <= in_EAX) {
      uVar2 = in_EAX;
    }
    pvVar1 = _malloc(uVar2 * 0x1750);
    if (pvVar1 != (void *)0x0) {
      _memmove(pvVar1,(void *)*unaff_ESI,unaff_ESI[1] * 0x1750);
      _free((void *)*unaff_ESI);
      *unaff_ESI = (int)pvVar1;
      unaff_ESI[2] = uVar2;
      return 1;
    }
  }
  return 0;
}

