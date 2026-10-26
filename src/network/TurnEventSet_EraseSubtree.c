/* TurnEventSet_EraseSubtree - 0x004e8ad0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), HIGH. TurnEventSet_Find.c's own header (src/network/)
 * already identifies this exact address by role: "0x4e8ad0 = the recursive
 * node destroy (_Erase)" in its list of the TurnEventSet family, and
 * separately: "either [watchdog] then inlines FUN_004e8ad0 plus the
 * _Myhead/_Mysize reset and empties the whole set" - i.e. recursively
 * freeing a subtree is how every "clear the whole set" site in this
 * family is built. ReleaseTurnEvent (0x4e7d60, named earlier in this
 * batch) independently confirms it: its 0xffff/clear() branch calls this
 * on the root's left child (`*(int *)(regEax + 0x45234) + 4`, i.e.
 * _Myhead->_Left) before resetting _Myhead/_Mysize - exactly the
 * recursive-free-then-reset shape a tree's clear() needs.
 *
 * NOT TreeEraseSubtree. This walks a DIFFERENT node shape than the
 * g_valueGuardMap family's tree helpers (see TreeEraseSubtree and
 * FUN_00443840's header, src/registry/): here node+0 is _Left, node+8 is
 * _Right (`param_1[2]`), node+0xf is _Isnil - the exact 0x10-byte,
 * ushort-keyed node TurnEventSet_Find.c's header documents for this
 * family, not the g_valueGuardMap tree's node layout. Per this tree's
 * instantiation-naming convention, it keeps the TurnEventSet_ prefix
 * rather than reusing TreeEraseSubtree's name.
 *
 * Recursively frees every non-nil right-subtree node (and, for each,
 * everything under its own left-child chain via the tail `while`), then
 * frees the node itself - a standard red-black tree node-destroy
 * recursion, called on a root/child pointer by every "clear the set"
 * site in this family (PumpBattleActions.c's two watchdog resets,
 * State10_Loading_OnEnter, State09_ReadyRoom_ProcessPacket,
 * State11_InBattle_OnExit, and ReleaseTurnEvent's clear() branch).
 */
#include "ghidra_types.h"


void TurnEventSet_EraseSubtree(int *param_1)

{
  char cVar1;
  int *piVar2;

  cVar1 = *(char *)((int)param_1 + 0xf);
  while (cVar1 == '\0') {
    TurnEventSet_EraseSubtree(param_1[2]);
    piVar2 = (int *)*param_1;
    _free(param_1);
    param_1 = piVar2;
    cVar1 = *(char *)((int)piVar2 + 0xf);
  }
  return;
}
