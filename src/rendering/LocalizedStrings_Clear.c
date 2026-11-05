/* LocalizedStrings_Clear - 0x00415740 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00415740 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: the sole
 * caller is LocalizedStrings_Destruct (0x4154e0), which calls it with the
 * map in ESI before freeing the nil sentinel. It erases the tree from the
 * root through LocalizedStrings_EraseSubtree, frees the pool-block chain
 * at map+0xc (the blocks LocalizedStrings_BuyNode mallocs), and resets the
 * root to the nil sentinel at map+0x14. That is the destructor-time Clear
 * of the same map structure, the counterpart of the allocations in
 * BuyNode. Named by role and sole caller, not by a library member match.
 */
#include "ghidra_types.h"


void LocalizedStrings_Clear(int *regEsi)

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

