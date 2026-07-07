/* FUN_004f42b0 - 0x004f42b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 * __fastcall FUN_004f42b0(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_2 = 0;
  *(undefined4 *)(param_2 + 0x110) = 0;
  *(undefined4 *)(param_2 + 0x114) = 0;
  *(undefined4 *)(param_2 + 0x118) = 0;
  *(undefined4 *)(param_2 + 0x1b4) = 0;
  *(undefined4 *)(param_2 + 0x401b8) = 0;
  puVar2 = (undefined4 *)(param_2 + 0x401bc);
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_2;
}

