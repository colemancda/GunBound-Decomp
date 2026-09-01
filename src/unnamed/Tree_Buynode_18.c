/* Tree_Buynode_18 - 0x00443b60 in the original binary.
 *
 * VC7 STL _Tree::_Buynode(), the zero-argument head/nil-node overload,
 * for the 0x18-byte-node instantiation Tree_Init_18 (0x443610) belongs
 * to - that already-named sole caller's header identifies this function
 * as "the _Buynode half" of its _Init.  The body is the library member
 * verbatim: allocate one 0x18-byte node, zero the three link fields
 * (the null guards are the placement-new artifacts of the library's
 * `new ((void*)&_Myleft(_Wherenode)) _Nodeptr(0)` sequence), set
 * _Color = _Black (1) at +0x14 and _Isnil = 0 at +0x15.  Tree_Init_18
 * then marks the node nil itself and self-links it as _Myhead.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 Tree_Buynode_18(void)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x18);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined4 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined4 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 5) = 1;
  *(undefined1 *)((int)puVar1 + 0x15) = 0;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

