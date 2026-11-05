/* TurnEventSet_BuyNode - 0x004e8e30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e8e30 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: It is the
 * five-argument _Tree::_Buynode of the std::set the TurnEventSet_* family
 * implements: operator_new(0x10) and, when it succeeds, stores _Left,
 * _Parent, _Right in dwords 0..2, the 16-bit key (copied from the pointer
 * argument) at +0xc, _Color at +0xe and _Isnil = 0 at +0xf, matching the
 * field offsets TurnEventSet_Find, TurnEventSet_IteratorIncrement and
 * TurnEventSet_RotateLeft read. Sole caller is
 * TurnEventSet_InsertRebalance, which passes (head, parent, head, key
 * pointer, color 0) and uses the returned node as the new leaf. The port's
 * return value is lost (declared void while the caller uses it), see the
 * report.
 */
#include "ghidra_types.h"


void TurnEventSet_BuyNode(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 *param_4,
                 undefined1 param_5)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x10);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    puVar1[1] = param_2;
    puVar1[2] = param_3;
    *(undefined2 *)(puVar1 + 3) = *param_4;
    *(undefined1 *)((int)puVar1 + 0xe) = param_5;
    *(undefined1 *)((int)puVar1 + 0xf) = 0;
  }
  return;
}

