/* FUN_00509730 - 0x00509730 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00509730(void)

{
  undefined4 *puVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  char *unaff_EBX;
  
  puVar1 = *(undefined4 **)(in_EAX + 4);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    iVar2 = puVar1[2];
    puVar1 = (undefined4 *)*puVar1;
  } while ((((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 0x4e21)) ||
           (*(int *)(iVar2 + 0x4c) != 0)) ||
          (iVar3 = __stricmp((char *)(iVar2 + 0x90),unaff_EBX), iVar3 != 0));
  return iVar2;
}

