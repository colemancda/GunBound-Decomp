/* FUN_00426030 - 0x00426030 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00426030(char *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar2 = FUN_00426780(local_4,local_8,local_c);
  if (iVar2 != 0) {
    puVar3 = (undefined4 *)FUN_004265c0();
    pcVar4 = (char *)*puVar3;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      *param_1 = cVar1;
      param_1 = param_1 + 1;
    } while (cVar1 != '\0');
    return 1;
  }
  return 0;
}

