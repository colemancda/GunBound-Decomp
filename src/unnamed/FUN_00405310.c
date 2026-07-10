/* FUN_00405310 - 0x00405310 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* winegcc (functional-validation build) links all objects into one
 * image, where this thunk_FUN_00405320 collides with the identical
 * copy Ghidra also emitted in FUN_00405300.c (both original
 * thunks tail-jump to 0x405320). Keep FUN_00405300.c's as the one
 * definition; skip this redundant copy under winegcc. MSVC still
 * compiles it standalone for byte-matching (per-file objects never
 * collide there). */
#ifndef __WINE__
void __fastcall thunk_FUN_00405320(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(*param_1 + -0x10);
  piVar1 = (int *)(*param_1 + -4);
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*puVar3 + 4))(puVar3);
  }
  return;
}
#endif /* __WINE__ */
