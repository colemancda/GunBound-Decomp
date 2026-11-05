/* Tree_Min_18 - 0x00443c00 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00443c00 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. VC7.1 STL _Tree::_Min for the 0x18-byte-node
 * instantiation (the Tree_Init_18 / Tree_Buynode_18 / Tree_Erase_18
 * family). Evidence from outside the body: Tree_Erase_18 is the
 * erase(iterator) whose library identity is documented in its header. Its
 * single call here, at 0x0044392a, passes the replacement node in EAX
 * (only when that node is not the nil head, i.e. byte +0x15 is zero) and
 * stores the returned EAX at 0x0044392f into head + 0, the cached leftmost
 * pointer. Following link +0 (left) until the next node is nil is the
 * subtree minimum. The ported body discards the result (void return,
 * dropped EAX), so the C source does not show the store; the binary does.
 * Node layout matches Tree_Erase_18's other accesses: links at +0, +4, +8
 * and the nil flag byte at +0x15.
 */
#include "ghidra_types.h"


void Tree_Min_18(int *regEax)

{
  char cVar1;
  int *piVar2;
  
  piVar2 = (int *)*regEax;
  cVar1 = *(char *)((int)piVar2 + 0x15);
  while (cVar1 == '\0') {
    piVar2 = (int *)*piVar2;
    cVar1 = *(char *)((int)piVar2 + 0x15);
  }
  return;
}

