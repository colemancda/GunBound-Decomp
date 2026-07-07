/* FUN_00415740 - 0x00415740 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00415740(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *_Memory;
  int *unaff_ESI;
  
  iVar1 = *unaff_ESI;
  if (iVar1 != unaff_ESI[5]) {
    FUN_004158a0(*(undefined4 *)(iVar1 + 0xc));
    FUN_004158a0(*(undefined4 *)(iVar1 + 0x10));
    thunk_FUN_004158f0();
    *(int *)(iVar1 + 0xc) = unaff_ESI[2];
    unaff_ESI[2] = iVar1;
    unaff_ESI[1] = unaff_ESI[1] + -1;
  }
  unaff_ESI[1] = 0;
  _Memory = (undefined4 *)unaff_ESI[3];
  while (_Memory != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)*_Memory;
    _free(_Memory);
    _Memory = puVar2;
  }
  unaff_ESI[3] = 0;
  unaff_ESI[2] = 0;
  *unaff_ESI = unaff_ESI[5];
  return;
}

