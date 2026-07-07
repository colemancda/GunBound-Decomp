/* EnumTextureFormatsCallback - 0x004ef8e0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 EnumTextureFormatsCallback(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((((param_1 != (undefined4 *)0x0) && ((param_1[1] & 0xe0000) == 0)) && (param_1[3] == 0x10)) &&
     (param_1[2] == 0)) {
    if ((param_1[1] & 1) == 0) {
      if (((param_1[7] == 0) && (param_1[4] == 0xf800)) &&
         ((param_1[5] == 0x7e0 && (param_1[6] == 0x1f)))) {
        puVar2 = &DAT_00677544;
        for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar2 = *param_1;
          param_1 = param_1 + 1;
          puVar2 = puVar2 + 1;
        }
      }
    }
    else if (((param_1[7] == 0xf000) && (param_1[4] == 0xf00)) &&
            ((param_1[5] == 0xf0 && (param_1[6] == 0xf)))) {
      puVar2 = &DAT_006777e8;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = *param_1;
        param_1 = param_1 + 1;
        puVar2 = puVar2 + 1;
      }
      return 1;
    }
  }
  return 1;
}

