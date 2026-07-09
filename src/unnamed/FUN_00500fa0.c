/* FUN_00500fa0 - 0x00500fa0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00500fa0(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int in_EAX;
  undefined4 *unaff_EDI;
  
  FUN_00501510();
  puVar1 = *(undefined4 **)(in_EAX + 0x10);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar1[0xd] = 10;
    puVar1[2] = *unaff_EDI;
    puVar1[3] = unaff_EDI[1];
    puVar1[4] = unaff_EDI[2];
    puVar1[5] = unaff_EDI[3];
    puVar1[6] = unaff_EDI[4];
    puVar1[7] = unaff_EDI[5];
  }
  *(undefined4 *)(in_EAX + 0x10) = *puVar1;
  puVar1[1] = param_1;
  *puVar1 = param_2;
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + 1;
  return;
}

