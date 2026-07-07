/* FUN_00450600 - 0x00450600 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00450600(int param_1)

{
  char cVar1;
  char *in_EAX;
  char *pcVar2;
  int iVar3;
  undefined4 *puVar4;
  
  pcVar2 = in_EAX;
  do {
    cVar1 = *pcVar2;
    pcVar2[(param_1 + 0x1d4) - (int)in_EAX] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  puVar4 = (undefined4 *)(param_1 + 0x44);
  for (iVar3 = 100; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  pcVar2 = in_EAX + 1;
  do {
    cVar1 = *in_EAX;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  FUN_0041b4b0((undefined4 *)(param_1 + 0x44),param_1 + 0x1d4,0x14,0xf,(int)in_EAX - (int)pcVar2,0);
  return;
}

