/* FUN_00524ef0 - 0x00524ef0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00524ef0(undefined4 param_1,undefined4 param_2,uchar *param_3,uchar *param_4,size_t param_5,
                undefined4 param_6)

{
  uchar uVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uchar *puVar6;
  uchar local_180 [64];
  uchar local_140 [63];
  uchar auStack_101 [257];
  
  _sprintf((char *)local_140,&DAT_0056ae84,param_1);
  _sprintf((char *)local_180,&DAT_0056ae80,param_2);
  uVar4 = 0xffffffff;
  puVar6 = local_140;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    uVar1 = *puVar6;
    puVar6 = puVar6 + 1;
  } while (uVar1 != '\0');
  uVar5 = 0xffffffff;
  puVar6 = local_180;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    uVar1 = *puVar6;
    puVar6 = puVar6 + 1;
  } while (uVar1 != '\0');
  pcVar2 = (char *)FUN_00525070(param_6,auStack_101 + 1);
  iVar3 = __mbsnbicmp(local_140,auStack_101 + 1,~uVar4 - 1);
  while (iVar3 != 0) {
    if (*pcVar2 == '\0') goto LAB_00525045;
    pcVar2 = (char *)FUN_00525070(pcVar2,auStack_101 + 1);
    iVar3 = __mbsnbicmp(local_140,auStack_101 + 1,~uVar4 - 1);
  }
  pcVar2 = (char *)FUN_00525070(pcVar2,auStack_101 + 1);
  while (auStack_101[1] != '[') {
    iVar3 = __mbsnbicmp(local_180,auStack_101 + 1,~uVar5 - 1);
    if (iVar3 == 0) {
      uVar4 = 0xffffffff;
      puVar6 = local_180;
      goto code_r0x00525037;
    }
    if (*pcVar2 == '\0') break;
    pcVar2 = (char *)FUN_00525070(pcVar2,auStack_101 + 1);
  }
  goto LAB_00525045;
  while( true ) {
    uVar4 = uVar4 - 1;
    uVar1 = *puVar6;
    puVar6 = puVar6 + 1;
    if (uVar1 == '\0') break;
code_r0x00525037:
    if (uVar4 == 0) break;
  }
  param_3 = auStack_101 + ~uVar4;
LAB_00525045:
  __mbsnbcpy(param_4,param_3,param_5);
  uVar4 = 0xffffffff;
  param_4[param_5 - 1] = '\0';
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    uVar1 = *param_4;
    param_4 = param_4 + 1;
  } while (uVar1 != '\0');
  return ~uVar4 - 1;
}

