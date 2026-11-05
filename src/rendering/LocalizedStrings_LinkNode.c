/* LocalizedStrings_LinkNode - 0x0043e0f0 in the original binary.
 * (Historical notes below: FUN_0043de70 is now LocalizedStrings_Insert.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0043e0f0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: the only
 * caller is LocalizedStrings_Insert (0x43de70), which runs the red-black
 * rebalance on the node this returns. It takes a node from
 * LocalizedStrings_BuyNode for the (id, message) pair, descends from the
 * root comparing the id against each node key to find the parent, stores
 * the parent at node+0x14, and hangs the node as the left (+0xc) or right
 * (+0x10) child, or makes it the root. That is exactly the 'link before
 * rebalance' half of a tree insert whose rebalance half lives in the
 * caller.
 *
 * REGISTERS RECOVERED (2026-08-25).  Inserts a (key, value) node into the
 * localized-string map param_1 (ECX): regEbx is the signed id key the tree
 * walk compares (`cmp ebx,[node]` / jl), regEax the string value; both are
 * FUN_0043de70's pass-through ECX/EAX.  FUN_0043e150 allocates the node from
 * the two.
 */
#include "ghidra_types.h"


void __fastcall LocalizedStrings_LinkNode(int *param_1,int regEbx,undefined4 regEax)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  iVar3 = LocalizedStrings_BuyNode(regEbx,regEax,(undefined4 *)param_1);
  piVar2 = (int *)*param_1;
  piVar1 = (int *)0x0;
  while (piVar2 != (int *)param_1[5]) {
    piVar1 = piVar2;
    if ((regEbx < *piVar2) || (regEbx == *piVar2)) {
      piVar2 = (int *)piVar2[3];
    }
    else {
      piVar2 = (int *)piVar2[4];
    }
  }
  *(int **)(iVar3 + 0x14) = piVar1;
  if (piVar1 != (int *)0x0) {
    if ((*piVar1 <= regEbx) && (regEbx != *piVar1)) {
      piVar1[4] = iVar3;
      return;
    }
    piVar1[3] = iVar3;
    return;
  }
  *param_1 = iVar3;
  return;
}

