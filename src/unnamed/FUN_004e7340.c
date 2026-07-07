/* FUN_004e7340 - 0x004e7340 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e7340(undefined4 param_1,uint param_2)

{
  uint *puVar1;
  char cVar2;
  int in_EAX;
  char *pcVar3;
  int iVar4;
  
  if ((int)param_2 < 8) {
    *(uint *)(in_EAX + 0x14c) = param_2;
    if (7 < param_2) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    puVar1 = (uint *)(in_EAX + 0x140 + (param_2 >> 5) * 4);
    *puVar1 = *puVar1 | 1 << ((byte)param_2 & 0x1f);
    *(undefined4 *)(in_EAX + 0x18 + param_2 * 4) = *(undefined4 *)(in_EAX + 0x150);
    *(undefined2 *)(in_EAX + 0x58 + param_2 * 2) = *(undefined2 *)(in_EAX + 0x158);
    *(undefined4 *)(in_EAX + 0x38 + param_2 * 4) = *(undefined4 *)(in_EAX + 0x154);
    *(undefined2 *)(in_EAX + 0x68 + param_2 * 2) = *(undefined2 *)(in_EAX + 0x15a);
    pcVar3 = (char *)(in_EAX + 0x15d);
    iVar4 = (in_EAX + (param_2 * 3 + 0xf) * 8) - (int)pcVar3;
    do {
      cVar2 = *pcVar3;
      pcVar3[iVar4] = cVar2;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    *(undefined1 *)(param_2 + 0x3c8 + in_EAX) = 0;
    *(undefined1 *)(param_2 + 0x3c0 + in_EAX) = 0;
    *(undefined4 *)(in_EAX + 0x454c4 + param_2 * 4) = 0xffffffff;
  }
  return;
}

