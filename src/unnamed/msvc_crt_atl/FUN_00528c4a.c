/* FUN_00528c4a - 0x00528c4a in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00528c4a(LPCSTR param_1,byte param_2)

{
  DWORD DVar1;
  undefined4 *puVar2;
  
  DVar1 = GetFileAttributesA(param_1);
  if (DVar1 == 0xffffffff) {
    DVar1 = GetLastError();
    __dosmaperr(DVar1);
  }
  else {
    if (((DVar1 & 1) == 0) || ((param_2 & 2) == 0)) {
      return 0;
    }
    puVar2 = (undefined4 *)FUN_0052b6d4();
    *puVar2 = 0xd;
    puVar2 = (undefined4 *)FUN_0052b6dd();
    *puVar2 = 5;
  }
  return 0xffffffff;
}

