/* FUN_00500710 - 0x00500710 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00500710(void)

{
  int iVar1;
  int *unaff_EBX;
  int local_c [3];
  
  local_c[0] = 0;
  iVar1 = FUN_005002a0(local_c);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c[0] == 0) {
    *(undefined4 *)(*unaff_EBX + (*(uint *)(iVar1 + 0x1764) % (uint)unaff_EBX[2]) * 4) =
         *(undefined4 *)(iVar1 + 0x1760);
    FUN_005011c0();
    return 1;
  }
  *(undefined4 *)(local_c[0] + 0x1760) = *(undefined4 *)(iVar1 + 0x1760);
  FUN_005011c0();
  return 1;
}

