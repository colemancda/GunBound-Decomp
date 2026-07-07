/* FUN_004e74c0 - 0x004e74c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e74c0(short param_1,int param_2,int param_3,short param_4,char *param_5)

{
  uint *puVar1;
  char cVar2;
  uint in_EAX;
  int iVar3;
  uint uVar4;
  int unaff_EDI;
  
  if ((int)in_EAX < 8) {
    if (7 < in_EAX) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    uVar4 = 1 << ((byte)in_EAX & 0x1f);
    iVar3 = (in_EAX >> 5) * 4;
    puVar1 = (uint *)(iVar3 + 0x140 + param_2);
    *puVar1 = *puVar1 | uVar4;
    puVar1 = (uint *)(iVar3 + 0x138 + param_2);
    *puVar1 = *puVar1 & ~uVar4;
    *(int *)(param_2 + 0x18 + in_EAX * 4) = unaff_EDI;
    *(short *)(param_2 + 0x58 + in_EAX * 2) = param_1;
    if ((unaff_EDI == param_3) && (param_1 == param_4)) {
      param_3 = -1;
    }
    *(int *)(param_2 + 0x38 + in_EAX * 4) = param_3;
    *(short *)(param_2 + 0x68 + in_EAX * 2) = param_4;
    *(undefined1 *)(in_EAX + 0x3c0 + param_2) = 0;
    *(undefined1 *)(in_EAX + 0x3c8 + param_2) = 0;
    *(undefined1 *)(in_EAX + 0x454e4 + param_2) = 0;
    iVar3 = (param_2 + (in_EAX * 3 + 0xf) * 8) - (int)param_5;
    do {
      cVar2 = *param_5;
      param_5[iVar3] = cVar2;
      param_5 = param_5 + 1;
    } while (cVar2 != '\0');
  }
  return;
}

