/* FUN_004026a0 - 0x004026a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004026a0(undefined4 param_1,undefined4 *param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  char *in_EAX;
  uint uVar3;
  int unaff_EBX;
  undefined4 *puVar4;
  char local_127 [31];
  int local_108;
  undefined4 local_104;
  undefined4 local_100 [63];
  
  iVar2 = -(int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[(int)(local_127 + iVar2)] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  local_108 = *(int *)(unaff_EBX + 0x1be0);
  *(int *)(unaff_EBX + 0x1be0) = local_108 + 1;
  local_104 = param_1;
  puVar4 = local_100;
  for (uVar3 = param_3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar4 = *param_2;
    param_2 = param_2 + 1;
    puVar4 = puVar4 + 1;
  }
  for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  FUN_004049a0(&local_108);
  return;
}

