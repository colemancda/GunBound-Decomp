/* Tree_Max_18 - 0x00443be0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00443be0 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. VC7.1 STL _Tree::_Max for the 0x18-byte-node
 * instantiation (the Tree_Init_18 / Tree_Buynode_18 / Tree_Erase_18
 * family). Evidence from outside the body: Tree_Erase_18 is the
 * erase(iterator) whose library identity is documented in its header. Its
 * single call here, at 0x0044394d, passes the replacement node in EAX
 * (only when that node is not the nil head, i.e. byte +0x15 is zero) and
 * stores the returned EAX at 0x00443952 into head + 8, the cached
 * rightmost pointer. Following link +8 (right) until the next node is nil
 * is the subtree maximum. The ported body discards the result (void
 * return, dropped EAX), so the C source does not show the store; the
 * binary does. Node layout matches Tree_Erase_18's other accesses: links
 * at +0, +4, +8 and the nil flag byte at +0x15.
 */
#include "ghidra_types.h"


int Tree_Max_18(int regEax)

{
  char cVar1;
  int iVar2;
  
  /* Disasm 0x443be0: ecx = [eax+8]; while (!nil(ecx)) { eax = ecx; ecx = [eax+8]; }
     ret -- EAX is the node whose right link is nil (the subtree maximum). */
  iVar2 = *(int *)(regEax + 8);
  cVar1 = *(char *)(iVar2 + 0x15);
  while (cVar1 == '\0') {
    regEax = iVar2;
    iVar2 = *(int *)(regEax + 8);
    cVar1 = *(char *)(iVar2 + 0x15);
  }
  return regEax;
}
