/* FUN_00534f8b - 0x00534f8b in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___mtold12
   
   Library: Visual Studio 2003 Release */

void ___mtold12(char *param_1,int param_2,uint *param_3)

{
  short sVar1;
  uint *puVar2;
  uint uVar3;
  uint local_14;
  uint local_10;
  uint local_c;
  undefined4 local_8;
  
  puVar2 = param_3;
  local_8 = DAT_0056bfd4;
  sVar1 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      ___shl_12(puVar2);
      ___shl_12(puVar2);
      ___add_12(puVar2,&local_14);
      ___shl_12(puVar2);
      local_14 = (uint)*param_1;
      local_10 = 0;
      local_c = 0;
      ___add_12(puVar2,&local_14);
      param_1 = param_1 + 1;
      param_3 = (uint *)((int)param_3 + -1);
    } while (param_3 != (uint *)0x0);
  }
  if (puVar2[2] == 0) {
    do {
      sVar1 = sVar1 + -0x10;
      uVar3 = puVar2[1] >> 0x10;
      puVar2[1] = *puVar2 >> 0x10 | puVar2[1] << 0x10;
      *puVar2 = *puVar2 << 0x10;
    } while (uVar3 == 0);
    puVar2[2] = uVar3;
  }
  while ((puVar2[2] & 0x8000) == 0) {
    ___shl_12(puVar2);
    sVar1 = sVar1 + -1;
  }
  *(short *)((int)puVar2 + 10) = sVar1;
  return;
}

