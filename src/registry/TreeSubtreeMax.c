/* TreeSubtreeMax - 0x0040bce0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the exact mirror of TreeSubtreeMin
 * (0x40bd00, same register convention, EAX = node): it follows the _Right
 * link (offset 8) until the _Isnil byte at +0x11 is set, where
 * TreeSubtreeMin follows _Left (offset 0). Sole caller is TreeErase, which
 * uses it on the other side of the same erase splice (the rightmost-of-
 * left-subtree update of the header's max pointer at +8, while
 * TreeSubtreeMin feeds the min pointer at +0).
 *
 * Return value: the port is void-returning although the binary leaves the
 * node in EAX; the same Ghidra void-return inconsistency TreeSubtreeMin
 * documents. Not changed here.
 */
#include "ghidra_types.h"


void TreeSubtreeMax(int regEax)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(regEax + 8);
  cVar1 = *(char *)(iVar2 + 0x11);
  while (cVar1 == '\0') {
    iVar2 = *(int *)(iVar2 + 8);
    cVar1 = *(char *)(iVar2 + 0x11);
  }
  return;
}

