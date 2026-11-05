/* TurnEventSet_BuyHead - 0x004e8e70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e8e70 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: The zero-
 * argument overload of the same _Tree::_Buynode: operator_new(0x10), links
 * zeroed, _Color = 1 (0xe) and _Isnil = 0 (0xf is later forced to 1 by the
 * caller). FUN_004e5e00 (the owner constructor) stores the result at set +
 * 0x45234 and then immediately sets node + 0xf = 1 and points _Left,
 * _Parent and _Right at itself, the empty-set sentinel head whose +0xf
 * byte the other TurnEventSet_* routines test.
 */
#include "ghidra_types.h"


undefined4 TurnEventSet_BuyHead(void)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x10);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined4 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined4 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)((int)puVar1 + 0xe) = 1;
  *(undefined1 *)((int)puVar1 + 0xf) = 0;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

