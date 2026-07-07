/* FUN_00402300 - 0x00402300 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00402300(int param_1,int param_2)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_10 = *(undefined4 *)(in_EAX + 0x10);
  local_c = *(undefined4 *)(in_EAX + 0x14);
  local_8 = *(undefined4 *)(in_EAX + 0x18);
  local_4 = 0;
  iVar2 = FUN_004259d0(&local_10);
  if (iVar2 == -1) {
    iVar2 = __stricmp((char *)(param_1 + 0x1bb0),(char *)&local_10);
    if (iVar2 != 0) {
      iVar2 = FUN_004023b0(&local_10);
      if (iVar2 == -1) {
        pcVar3 = (char *)&local_10;
        pcVar4 = (char *)(*(int *)(param_1 + 0x15a8) * 0xd + 0xf28 + param_1);
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
          *pcVar4 = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        *(int *)(param_1 + 0x15a8) = *(int *)(param_1 + 0x15a8) + 1;
      }
    }
    FUN_00402400(param_1,in_EAX + 0x20,param_2 + -0x20);
  }
  return;
}

