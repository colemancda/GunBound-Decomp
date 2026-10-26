/* ValueGuardMap_Destructor - 0x0040a1c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Tears down the whole CValueGuard guard-cell registry anchored on
 * g_valueGuardMap: frees the key-table buffer (`*param_1`, i.e. the
 * buffer g_valueGuardKeyTable at 0x79376c points at), erases the map's
 * node range via TreeEraseRange (called with `(int)(puVar1 + 1)` =
 * param_1+4 = &g_valueGuardMap as the container), then frees and
 * zeroes DAT_00793774 (param_1+8, the "current key-table object"
 * pointer) and zeroes DAT_00793778 (param_1+0xc, the "encoding active"
 * gate). The container identity is external: its only caller is
 * FUN_005431b0, an atexit destructor thunk that passes
 * &g_valueGuardKeyTable (0x79376c) - exactly 4 bytes before
 * g_valueGuardMap (0x793770), matching this function's own
 * `puVar1 + 1` offset into the same static object. g_valueGuardMap's
 * own header comment already calls it "the key-table registry root",
 * i.e. this destroys the registry the map anchors, not the map's node
 * storage alone.
 */
#include "ghidra_types.h"


void ValueGuardMap_Destructor(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;

  puVar1 = param_1;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537b5b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  local_4 = 0;
  _free((void *)*param_1);
  local_4 = 0xffffffff;
  TreeEraseRange((undefined4 *)&param_1,(int *)*(undefined4 *)puVar1[2],(int *)puVar1[2],(int)(puVar1 + 1));
  _free((void *)puVar1[2]);
  puVar1[2] = 0;
  puVar1[3] = 0;
  return;
}

