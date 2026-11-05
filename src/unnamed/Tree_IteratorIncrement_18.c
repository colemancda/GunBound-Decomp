/* Tree_IteratorIncrement_18 - 0x00443780 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00443780 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. VC7 STL _Tree::const_iterator::_Inc, the
 * in-order successor step, for the 0x18-byte-node instantiation that
 * Tree_Init_18 and Tree_Buynode_18 belong to. The node layout is fixed by
 * those two already-named neighbours (left +0, parent +4, right +8, colour
 * +0x14, isnil +0x15, sentinel head at tree + 4) and the body reads exactly
 * those fields: if the node is not nil, take the leftmost node of the right
 * subtree when there is one, else climb through parents while the node is
 * its parent's right child.
 *
 * The callers corroborate the role: the two range erasers FUN_00443680 and
 * FUN_00443700 (erase(first, last)) run it in their loop on a local copy of
 * the iterator (`lea edx,[esp+0x14]; call 0x443780` at 0x4436d0) and then
 * hand the node to the single-node erase at 0x443840, the library's
 * erase(first++) idiom; that erase calls it too. The code never touches the
 * value, so one body serves every 0x18-byte-node tree in the image (the two
 * range erasers differ only in the subtree destructor they call). Not to be
 * confused with RBTree_IteratorIncrement (0x405040), a different node
 * layout. The leading __fastcall parameter is a phantom; EDX holds the
 * address of the iterator, i.e. of the node pointer it updates.
 */
#include "ghidra_types.h"


void __fastcall Tree_IteratorIncrement_18(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  iVar2 = *param_2;
  if (*(char *)(iVar2 + 0x15) == '\0') {
    piVar3 = *(int **)(iVar2 + 8);
    if (*(char *)((int)piVar3 + 0x15) == '\0') {
      cVar1 = *(char *)(*piVar3 + 0x15);
      piVar4 = (int *)*piVar3;
      while (cVar1 == '\0') {
        cVar1 = *(char *)(*piVar4 + 0x15);
        piVar3 = piVar4;
        piVar4 = (int *)*piVar4;
      }
      *param_2 = (int)piVar3;
      return;
    }
    iVar2 = *(int *)(iVar2 + 4);
    cVar1 = *(char *)(iVar2 + 0x15);
    while ((cVar1 == '\0' && (*param_2 == *(int *)(iVar2 + 8)))) {
      *param_2 = iVar2;
      iVar2 = *(int *)(iVar2 + 4);
      cVar1 = *(char *)(iVar2 + 0x15);
    }
    *param_2 = iVar2;
  }
  return;
}

