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
 * Returns the node in EAX (verified at 0x40bce0 and the caller's store at
 * 0x40b712); TreeErase stores it at head+8.
 */
#include "ghidra_types.h"


int TreeSubtreeMax(int regEax)

{
  char cVar1;
  int iVar2;
  
  /* Disasm 0x40bce0: ecx = [eax+8]; while (!nil(ecx)) { eax = ecx; ecx = [eax+8]; }
     ret -- EAX is the rightmost non-nil node (the arg itself if its right is nil). */
  iVar2 = *(int *)(regEax + 8);
  cVar1 = *(char *)(iVar2 + 0x11);
  while (cVar1 == '\0') {
    regEax = iVar2;
    iVar2 = *(int *)(regEax + 8);
    cVar1 = *(char *)(iVar2 + 0x11);
  }
  return regEax;
}

