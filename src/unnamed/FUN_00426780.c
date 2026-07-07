/* FUN_00426780 - 0x00426780 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00426780(uint *param_1,uint *param_2,undefined4 *param_3)

{
  uchar *puVar1;
  uchar uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int *in_EAX;
  uint uVar5;
  int iVar6;
  uchar *puVar7;
  uchar *unaff_EBX;
  
  uVar5 = 0;
  uVar2 = *unaff_EBX;
  puVar7 = unaff_EBX;
  while (uVar2 != '\0') {
    uVar5 = uVar5 * 0x21 + (int)(char)uVar2;
    puVar1 = puVar7 + 1;
    puVar7 = puVar7 + 1;
    uVar2 = *puVar1;
  }
  *param_2 = uVar5;
  *param_1 = uVar5 % (uint)in_EAX[2];
  if (*in_EAX != 0) {
    *param_3 = 0;
    puVar3 = (undefined4 *)0x0;
    puVar4 = *(undefined4 **)(*in_EAX + *param_1 * 4);
    while( true ) {
      if (puVar4 == (undefined4 *)0x0) {
        return (undefined4 *)0x0;
      }
      if ((puVar4[3] == *param_2) && (iVar6 = __mbscmp((uchar *)*puVar4,unaff_EBX), iVar6 == 0))
      break;
      puVar3 = puVar4;
      puVar4 = (undefined4 *)puVar4[2];
    }
    *param_3 = puVar3;
    return puVar4;
  }
  return (undefined4 *)0x0;
}

