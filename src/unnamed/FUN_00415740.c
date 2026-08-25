/* FUN_00415740 - 0x00415740 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00415740(int *regEsi)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *_Memory;
  
  iVar1 = *regEsi;
  if (iVar1 != regEsi[5]) {
    FUN_004158a0(*(undefined4 *)(iVar1 + 0xc));
    FUN_004158a0(*(undefined4 *)(iVar1 + 0x10));
    thunk_FUN_004158f0();
    *(int *)(iVar1 + 0xc) = regEsi[2];
    regEsi[2] = iVar1;
    regEsi[1] = regEsi[1] + -1;
  }
  regEsi[1] = 0;
  _Memory = (undefined4 *)regEsi[3];
  while (_Memory != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)*_Memory;
    _free(_Memory);
    _Memory = puVar2;
  }
  regEsi[3] = 0;
  regEsi[2] = 0;
  *regEsi = regEsi[5];
  return;
}

