/* FUN_00409c70 - 0x00409c70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00409c70(void)

{
  int iVar1;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar1 = FUN_00426780(local_4,local_8,&stack0x00000004);
  if (iVar1 != 0) {
    return *(undefined4 *)(iVar1 + 4);
  }
  return 0xffffffff;
}

