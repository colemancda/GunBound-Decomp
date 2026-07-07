/* FUN_005052b0 - 0x005052b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __fastcall FUN_005052b0(int param_1)

{
  undefined1 uVar1;
  int unaff_ESI;
  int unaff_EDI;
  
  uVar1 = 0;
  if ((((*(char *)(param_1 + 0x1e) == '\0') && (*(int *)(param_1 + 0x28) < unaff_ESI)) &&
      (unaff_ESI < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
     ((*(int *)(param_1 + 0x2c) < unaff_EDI &&
      (unaff_EDI < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))))) {
    uVar1 = 1;
  }
  return uVar1;
}

