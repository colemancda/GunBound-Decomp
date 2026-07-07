/* FUN_00525f26 - 0x00525f26 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00525f26(LPCSTR param_1)

{
  BOOL BVar1;
  ulong uVar2;
  
  BVar1 = DeleteFileA(param_1);
  if (BVar1 == 0) {
    uVar2 = GetLastError();
  }
  else {
    uVar2 = 0;
  }
  if (uVar2 != 0) {
    __dosmaperr(uVar2);
    return 0xffffffff;
  }
  return 0;
}

