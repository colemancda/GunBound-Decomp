/* FUN_005009b0 - 0x005009b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_005009b0(void)

{
  int iVar1;
  int *unaff_EBX;
  int local_c [3];
  
  local_c[0] = 0;
  iVar1 = FUN_005013c0(local_c);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c[0] == 0) {
    *(undefined4 *)(*unaff_EBX + (*(uint *)(iVar1 + 0x10) % (uint)unaff_EBX[2]) * 4) =
         *(undefined4 *)(iVar1 + 0xc);
    FUN_00501360();
    return 1;
  }
  *(undefined4 *)(local_c[0] + 0xc) = *(undefined4 *)(iVar1 + 0xc);
  FUN_00501360();
  return 1;
}

