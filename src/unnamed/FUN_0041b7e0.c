/* FUN_0041b7e0 - 0x0041b7e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0041b7e0(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(undefined4 *)(param_2 + 0x3b97c) = 0;
  *(undefined4 *)(param_2 + 0x3b980) = 0;
  puVar2 = (undefined4 *)(param_2 + 0x3b984);
  for (iVar1 = 0xe1; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3bd08);
  for (iVar1 = 500; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3c4d8);
  for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3c53c);
  for (iVar1 = 0xc80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3f73c);
  for (iVar1 = 0x32; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

