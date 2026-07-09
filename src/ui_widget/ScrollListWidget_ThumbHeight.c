/* ScrollListWidget_ThumbHeight - 0x0050e050 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int ScrollListWidget_ThumbHeight(void)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  
  if (0 < *(int *)(in_EAX + 0x38)) {
    iVar1 = (*(int *)(in_EAX + 0x3c) * *(int *)(in_EAX + 0x34)) / *(int *)(in_EAX + 0x38);
    iVar2 = 10;
    if (9 < iVar1) {
      iVar2 = iVar1;
    }
    return (iVar2 / 5) * 5;
  }
  return *(int *)(in_EAX + 0x34);
}

