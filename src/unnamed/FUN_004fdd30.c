/* FUN_004fdd30 - 0x004fdd30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004fdd30(undefined4 param_1,undefined4 param_2)

{
  char **ppcVar1;
  char *pcVar2;
  char *in_EAX;
  ulong uVar3;
  hostent *phVar4;
  char **ppcVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  
  uVar3 = inet_addr(in_EAX);
  if (uVar3 == 0xffffffff) {
    phVar4 = gethostbyname(in_EAX);
    if (phVar4 == (hostent *)0x0) {
      return 0;
    }
    ppcVar5 = phVar4->h_addr_list;
    uVar8 = 0;
    pcVar2 = *ppcVar5;
    while (pcVar2 != (char *)0x0) {
      ppcVar1 = ppcVar5 + 1;
      ppcVar5 = ppcVar5 + 1;
      uVar8 = uVar8 + 1;
      pcVar2 = *ppcVar1;
    }
    uVar6 = FUN_00504e90();
    uVar3 = *(ulong *)phVar4->h_addr_list[uVar6 % uVar8];
  }
  uVar7 = FUN_004fe5f0(uVar3,param_2);
  return uVar7;
}

