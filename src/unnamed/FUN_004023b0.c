/* FUN_004023b0 - 0x004023b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004023b0(char *param_1)

{
  int iVar1;
  int unaff_EBX;
  int iVar2;
  char *_Str2;
  
  iVar2 = 0;
  if (0 < *(int *)(unaff_EBX + 0x15a8)) {
    _Str2 = (char *)(unaff_EBX + 0xf28);
    do {
      iVar1 = __stricmp(param_1,_Str2);
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      _Str2 = _Str2 + 0xd;
    } while (iVar2 < *(int *)(unaff_EBX + 0x15a8));
  }
  return -1;
}

