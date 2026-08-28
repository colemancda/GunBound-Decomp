/* RBTree_Insert - 0x004049a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): a red-black-tree insert (nodes carry the
 * colour byte at +0x104 and left/right/parent at +0x108/+0x10c/+0x110,
 * with FUN_00404c40 as the rotate). EAX is the key record being inserted
 * and EDI the tree; both are read before written, EDI first at 0x4049aa
 * as FUN_00404dd0's receiver.
 *
 * Both call sites hand over the same shape. FUN_004026a0 passes the
 * char-plus-string record at its aligned frame base and the tree at its
 * own regEbx + 0x1be4 (`lea eax,[esp+0xc]` / `lea edi,[ebx+0x1be4]` at
 * 0x402709/0x402703). FUN_00404410 passes &local_120 - the local whose
 * first byte its source already sets to 0x69, the same 'i' type
 * character - and the tree at param_1 + 0x1be4 (`lea eax,[esp+0x80]` at
 * 0x404691, depth E-0x1a0 pinned by `mov [esp+0xa4],0x2005` landing on
 * its own local_fc; `lea ebx,[ebp+0x1be4]` at 0x4045b1 with ebp =
 * [esp+0x194] = entry+4 behind `sub esp,0x18c` and one `push ebp`).
 *
 * NAMED (2026-08-28): the insert of a red-black tree, returning the node
 * it created. The identity does not rest on this body's control flow
 * alone - the two halves of the operation are split across two
 * functions, and the OTHER half settles the data structure from outside:
 *
 *   FUN_00404dd0, the callee on the first line, is the ordinary binary
 *   search-tree descent. It compares the key against each node's own key
 *   with __mbsicmp, steps to +0x108 or +0x10c by the sign of that
 *   comparison, stops when it reaches the sentinel the tree keeps at
 *   +0x14, links the new node into the parent's +0x108 or +0x10c and
 *   writes the parent back into the new node's +0x110. So +0x108 and
 *   +0x10c are left and right, +0x110 is parent, and tree+0 is the root
 *   while tree+0x14 is the nil sentinel.
 *
 *   FUN_00404c40 and FUN_00404cd0 are the two rotations, and their only
 *   other caller is FUN_00404e60 - the erase half of the same tree,
 *   which is what a red-black tree needs rotations for at all.
 *
 * What is left for this function is exactly CLRS's RB-INSERT-FIXUP over
 * the remaining field, the colour at +0x104: paint the new node red
 * (0x104 = 0), then while the parent is red, look at the uncle through
 * the grandparent's +0x108 / +0x10c, recolour parent and uncle black and
 * grandparent red when the uncle is red, otherwise rotate and recolour;
 * finish by forcing the root black and restoring root->parent = nil
 * (`*(*tree + 0x110) = tree[5]`, the last statement).
 *
 * The node is 0x114 bytes: a 0x104-byte payload whose first dword is
 * the key string pointer FUN_00404dd0 hands to __mbsicmp, then colour,
 * left, right, parent. No suffix, because this
 * is the only instantiation in the image - the rotations at 0x404c40 and
 * 0x404cd0 have exactly two callers between them, this and the erase -
 * and both of this function's own callers hand it the tree at +0x1be4 of
 * their object.
 */
#include "ghidra_types.h"


int RBTree_Insert(int param_1,undefined4 regEax,int *regEdi)

{
  int iVar1;
  undefined4 in_EAX = regEax;
  int iVar2;
  int iVar3;
  int iVar4;
  int *unaff_EDI = regEdi;
  
  iVar2 = FUN_00404dd0(unaff_EDI,(uchar *)in_EAX,param_1);
  *(undefined4 *)(iVar2 + 0x104) = 0;
  iVar4 = iVar2;
  if (iVar2 != *unaff_EDI) {
    do {
      iVar1 = *(int *)(iVar4 + 0x110);
      if (*(int *)(iVar1 + 0x104) != 0) break;
      iVar3 = *(int *)(*(int *)(iVar1 + 0x110) + 0x108);
      if (iVar1 == iVar3) {
        iVar3 = *(int *)(*(int *)(iVar1 + 0x110) + 0x10c);
        if ((iVar3 == 0) || (*(int *)(iVar3 + 0x104) != 0)) {
          if (iVar4 == *(int *)(iVar1 + 0x10c)) {
            FUN_00404c40();
            iVar4 = iVar1;
          }
          *(undefined4 *)(*(int *)(iVar4 + 0x110) + 0x104) = 1;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x110) + 0x110) + 0x104) = 0;
          FUN_00404cd0();
        }
        else {
LAB_00404a08:
          *(undefined4 *)(*(int *)(iVar4 + 0x110) + 0x104) = 1;
          *(undefined4 *)(iVar3 + 0x104) = 1;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x110) + 0x110) + 0x104) = 0;
          iVar4 = *(int *)(*(int *)(iVar4 + 0x110) + 0x110);
        }
      }
      else {
        if ((iVar3 != 0) && (*(int *)(iVar3 + 0x104) == 0)) goto LAB_00404a08;
        if (iVar4 == *(int *)(iVar1 + 0x108)) {
          FUN_00404cd0();
          iVar4 = iVar1;
        }
        *(undefined4 *)(*(int *)(iVar4 + 0x110) + 0x104) = 1;
        *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x110) + 0x110) + 0x104) = 0;
        FUN_00404c40();
      }
    } while (iVar4 != *unaff_EDI);
  }
  *(undefined4 *)(*unaff_EDI + 0x104) = 1;
  *(int *)(*unaff_EDI + 0x110) = unaff_EDI[5];
  return iVar2;
}

