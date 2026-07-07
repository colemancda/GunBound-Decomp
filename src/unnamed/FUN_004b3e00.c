/* FUN_004b3e00 - 0x004b3e00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004b3e00(void)

{
  int in_EAX;
  int iVar1;
  
  if (*(char *)(in_EAX + 0x322) != '\0') {
    iVar1 = *(int *)(in_EAX + 0x328) + *(int *)(in_EAX + 0x324);
    *(int *)(in_EAX + 0x328) = iVar1;
    if ((iVar1 == 600) && (*(int *)(in_EAX + 0x324) == -10)) {
      *(undefined4 *)(in_EAX + 0x324) = 0;
    }
    if ((*(int *)(in_EAX + 0x328) == 800) && (*(int *)(in_EAX + 0x324) == 10)) {
      *(undefined4 *)(in_EAX + 0x324) = 0;
      *(undefined1 *)(in_EAX + 0x322) = 0;
    }
  }
  return;
}

