/* FUN_004f08a0 - 0x004f08a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004f08a0(undefined4 param_1,int param_2)

{
  uint uVar1;
  char cVar2;
  int in_EAX;
  uint uVar3;
  
  if (*(char *)(in_EAX + 0x1018) == '\0') {
    return 0;
  }
  uVar1 = *(uint *)(in_EAX + 0x1014);
  uVar3 = *(uint *)(*(int *)(in_EAX + 0x1004) + 0x78);
  if (uVar3 <= uVar1) {
    return 1;
  }
  if (uVar3 < uVar1 + param_2) {
    param_2 = uVar3 - uVar1;
  }
  if (*(int *)(*(int *)(in_EAX + 0x1004) + 0x70) != 1) {
    uVar3 = *(int *)(in_EAX + 0x100c) + param_2;
    if (0x1000 < uVar3) {
      while (uVar3 = uVar3 - 0x1000, 0x1000 < uVar3) {
        cVar2 = FUN_004f0650();
        if (cVar2 == '\0') {
          return 0;
        }
        *(int *)(in_EAX + 0x1014) = *(int *)(in_EAX + 0x1014) + 0x1000;
      }
      cVar2 = DecodeXFSEntryBlock();
      if (cVar2 == '\0') {
        return 0;
      }
      *(uint *)(in_EAX + 0x100c) = uVar3;
      *(uint *)(in_EAX + 0x1014) = *(int *)(in_EAX + 0x1014) + uVar3;
      return 1;
    }
    *(uint *)(in_EAX + 0x100c) = uVar3;
  }
  *(uint *)(in_EAX + 0x1014) = uVar1 + param_2;
  return 1;
}

