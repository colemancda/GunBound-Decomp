/* FUN_00504d80 - 0x00504d80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_00504d80(undefined4 param_1,int *param_2)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  if (*param_2 == 0x19) {
    puVar1 = (uint *)(param_2 + 1);
    iVar3 = 3;
    do {
      *puVar1 = *puVar1 >> 1 ^ param_2[(*puVar1 & 1) + 0x1a] ^ puVar1[7];
      puVar1[1] = puVar1[1] >> 1 ^ param_2[(puVar1[1] & 1) + 0x1a] ^ puVar1[8];
      puVar1[2] = puVar1[2] >> 1 ^ param_2[(puVar1[2] & 1) + 0x1a] ^ puVar1[9];
      puVar1[3] = puVar1[3] >> 1 ^ param_2[(puVar1[3] & 1) + 0x1a] ^ puVar1[10];
      puVar1[4] = puVar1[4] >> 1 ^ param_2[(puVar1[4] & 1) + 0x1a] ^ puVar1[0xb];
      puVar1[5] = puVar1[5] >> 1 ^ param_2[(puVar1[5] & 1) + 0x1a] ^ puVar1[0xc];
      puVar1 = puVar1 + 6;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar1 = (uint *)(param_2 + 0x13);
    iVar3 = 7;
    do {
      *puVar1 = *puVar1 >> 1 ^ param_2[(*puVar1 & 1) + 0x1a] ^ puVar1[-0x12];
      puVar1 = puVar1 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    *param_2 = 0;
  }
  uVar2 = param_2[*param_2 + 1] ^ (param_2[*param_2 + 1] & 0x56b64aU) << 7;
  uVar2 = uVar2 ^ (uVar2 & 0xffffb716) << 0xf;
  *param_2 = *param_2 + 1;
  return uVar2 >> 0x10 ^ uVar2;
}

