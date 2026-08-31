/* TreeFind - 0x0040b8c0 in the original binary.
 *
 * The VC7 STL _Tree::find of the CValueGuard guard-cell map: a
 * lower_bound descent (node key at +0xc, _Isnil at +0x11, head node at
 * map+4) followed by the check that turns lower_bound into find -
 * return the node only when `found != end && found->key <= key` (the
 * descent already guarantees found->key >= key), else return end (the
 * head node) through the out-iterator.  Library-shaped, so it takes the
 * library's member name, prefixed like its sibling TreeLowerBound
 * (0x40b540) in src/registry/ - the same map, the same node layout.
 *
 * The map identity is external: both binary call sites (0x40a300 in
 * PeekPacketChecksumState, 0x40a3f4 in EncodeOutgoingPacketField) load
 * ECX with the immediate 0x793770 = &g_valueGuardMap, the same object
 * 1179 of TreeLowerBound's 1180 sites pass in EAX.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the guard map's FIND - a lower_bound
 * descent over the same red-black tree as the (deliberately neutered)
 * TreeLowerBound at 0x40b540, but a DIFFERENT function: this one is
 * live, takes the map in its declared ECX param_1, the address of the
 * KEY in EBX and an OUT-ITERATOR slot in EAX, writes the found node
 * through *regEax, and verifies exact-match bounds (root check plus
 * key <= node key).
 *
 * Two binary sites, one ported: EncodeOutgoingPacketField at 0x40a3f4,
 * where the key is the param_1 slot the C reuses (`param_1 = iVar4;` on
 * the line above is the key store) and the out lands in the dead
 * scratch at entry-4 - the top half of local_8, the same scratch the
 * TreeLowerBound call above it uses. The other site, 0x40a300, is in
 * PeekPacketChecksumState, whose C is the deliberate bring-up rewrite
 * documented in its own header (the original's integrity re-check) -
 * nothing to edit there until that neuter is lifted.
 */
#include "ghidra_types.h"


void __fastcall TreeFind(int param_1,undefined4 **regEax,int *regEbx)

{
  undefined4 **in_EAX = regEax;
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *unaff_EBX = regEbx;
  
  puVar3 = *(undefined4 **)(param_1 + 4);
  if (*(char *)((int)puVar3[1] + 0x11) == '\0') {
    puVar1 = (undefined4 *)puVar3[1];
    do {
      if ((int)puVar1[3] < *unaff_EBX) {
        puVar2 = (undefined4 *)puVar1[2];
      }
      else {
        puVar2 = (undefined4 *)*puVar1;
        puVar3 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((int)puVar2 + 0x11) == '\0');
  }
  if ((puVar3 != *(undefined4 **)(param_1 + 4)) && ((int)puVar3[3] <= *unaff_EBX)) {
    *in_EAX = (undefined4 *)puVar3;
    return;
  }
  *in_EAX = *(undefined4 **)(param_1 + 4);
  return;
}

