/* FindDirectLinkBuddyIndexByName - 0x00401c50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence: sibling of FindDirectLinkBuddyNode (0x401bb0), which does the
 * same walk over the container's list-of-trees (list head at +4, inner
 * pointer at +0x10, sentinel flag byte at +0x15, name at node + 0x21)
 * but returns the node. This one returns the node's ordinal, counted
 * across the whole walk, or -1. Its only caller, RemoveDirectLinkBuddyNode
 * (0x401efd), calls FindDirectLinkBuddyNode first, then this with the same
 * name, and uses the result to compact the container's parallel 0x7f-entry
 * array at +0x15ac/+0x15b0 around that slot (`if (index < 0x7f)` shift the
 * tail down by one) before unlinking and freeing the node. So the ordinal
 * is the buddy's slot number in that parallel array. Comparison is
 * _stricmp, so it is case-insensitive.
 *
 * Both args are stack args (ret 8): the container and the name. The
 * caller already passes both.
 */
#include "ghidra_types.h"


int FindDirectLinkBuddyIndexByName(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  iVar4 = 0;
  if (iVar5 != *(int *)(param_1 + 4)) {
    do {
      iVar2 = *(int *)(iVar5 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        iVar3 = __stricmp((char *)(iVar2 + 0x21),param_2);
        if (iVar3 == 0) {
          return iVar4;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        iVar4 = iVar4 + 1;
        cVar1 = *(char *)(iVar2 + 0x15);
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
    } while (iVar5 != *(int *)(param_1 + 4));
  }
  return -1;
}

