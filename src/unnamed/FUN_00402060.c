/* FUN_00402060 - 0x00402060 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00402060(undefined4 param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  ushort *puVar6;
  int local_4;
  
  puVar6 = (ushort *)(param_2 + 0xc18);
  *(undefined4 *)(param_2 + 0xc14) = 0;
  puVar4 = puVar6;
  for (iVar5 = 0x40; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar4[0] = 0xffff;
    puVar4[1] = 0xffff;
    puVar4 = puVar4 + 2;
  }
  local_4 = *(int *)(*(int *)(param_2 + 4) + 0x1c);
  if (local_4 != *(int *)(param_2 + 4)) {
    do {
      iVar5 = *(int *)(local_4 + 0x10);
      cVar1 = *(char *)(iVar5 + 0x15);
      while (cVar1 == '\0') {
        if (*(char *)(iVar5 + 0x30) == '\x12') {
          iVar3 = 0;
          if (0 < *(int *)(param_2 + 0xc14)) {
            puVar4 = puVar6;
            do {
              if (*puVar4 == *(ushort *)(iVar5 + 0x31)) break;
              iVar3 = iVar3 + 1;
              puVar4 = puVar4 + 1;
            } while (iVar3 < *(int *)(param_2 + 0xc14));
          }
          if (iVar3 == *(int *)(param_2 + 0xc14)) {
            *(undefined2 *)(param_2 + 0xc18 + iVar3 * 2) = *(undefined2 *)(iVar5 + 0x31);
            *(int *)(param_2 + 0xc14) = *(int *)(param_2 + 0xc14) + 1;
          }
        }
        iVar5 = *(int *)(iVar5 + 0x10);
        cVar1 = *(char *)(iVar5 + 0x15);
      }
      local_4 = *(int *)(local_4 + 0x1c);
    } while (local_4 != *(int *)(param_2 + 4));
  }
  iVar5 = 0;
  if (*(int *)(param_2 + 0xc14) != 1 && -1 < *(int *)(param_2 + 0xc14) + -1) {
    do {
      puVar4 = puVar6;
      iVar3 = iVar5;
      if (iVar5 < *(int *)(param_2 + 0xc14)) {
        do {
          uVar2 = *puVar6;
          if (*puVar4 < uVar2) {
            *puVar6 = *puVar4;
            *puVar4 = uVar2;
          }
          iVar3 = iVar3 + 1;
          puVar4 = puVar4 + 1;
        } while (iVar3 < *(int *)(param_2 + 0xc14));
      }
      iVar5 = iVar5 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar5 < *(int *)(param_2 + 0xc14) + -1);
  }
  return;
}

