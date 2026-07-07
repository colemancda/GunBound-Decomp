/* FUN_00500900 - 0x00500900 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00500900(void)

{
  int iVar1;
  undefined4 *unaff_EBX;
  undefined1 local_c [12];
  
  iVar1 = FUN_005013c0(local_c);
  if (iVar1 == 0) {
    return 0;
  }
  *unaff_EBX = *(undefined4 *)(iVar1 + 4);
  unaff_EBX[1] = *(undefined4 *)(iVar1 + 8);
  return 1;
}

