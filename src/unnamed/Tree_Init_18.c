/* Tree_Init_18 - 0x00443610 in the original binary.
 *
 * VC7 STL red-black tree (std::map's _Tree) _Init, for the 0x18-byte-node
 * instantiation - hence the _18 node-stride suffix, per the container
 * naming convention.  The behaviour is the library member verbatim:
 * allocate the sentinel head node via Tree_Buynode_18 (the _Buynode half -
 * operator_new(0x18), links zeroed, _Color black at +0x14), mark it nil
 * (+0x15 = 1), self-link its parent/left/right to itself, store it at
 * this+4 (_Myhead) and zero the size at this+8 (_Mysize).
 *
 * This is NOT the CValueGuard map's tree that TreeLowerBound (0x40b540)
 * and TreeFind (0x40b8c0) walk: that instantiation keeps a 4-byte _Myval
 * at +0xc with _Isnil at +0x11, while this one's _Myval is 8 bytes with
 * _Color/_Isnil at +0x14/+0x15 - a different node layout, so a different
 * template instantiation.
 *
 * DROPPED-REG FIX (2026-08-31): this arrives in ESI, promoted to
 * regEsi. Its only two binary callers are CRT static-initializer
 * thunks (0x541330 and 0x541350: `push esi / mov esi,<obj> / call /
 * atexit`), constructing two static map objects at 0xe9ca2c and
 * 0xe9ca38 that NO ported code references - so there is no C call
 * site to create and nothing to wire into the startup hook until a
 * consumer of those maps is ported.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void Tree_Init_18(int regEsi)

{
  int iVar1;
  
  iVar1 = Tree_Buynode_18();
  *(int *)(regEsi + 4) = iVar1;
  *(undefined1 *)(iVar1 + 0x15) = 1;
  *(int *)(*(int *)(regEsi + 4) + 4) = *(int *)(regEsi + 4);
  *(undefined4 *)*(undefined4 *)(regEsi + 4) = *(undefined4 *)(regEsi + 4);
  *(int *)(*(int *)(regEsi + 4) + 8) = *(int *)(regEsi + 4);
  *(undefined4 *)(regEsi + 8) = 0;
  return;
}

