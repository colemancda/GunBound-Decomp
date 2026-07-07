/* FUN_004e6d10 - 0x004e6d10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e6d10(int param_1,undefined4 *param_2,int param_3,int param_4)

{
  undefined1 uVar1;
  int in_EAX;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = param_2;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)((int)param_2 + 2) = 0;
  *(undefined2 *)param_2 = 0x24;
  uVar1 = *(undefined1 *)(param_1 + 0x14c);
  *(undefined1 *)((int)param_2 + 7) = 0;
  *(undefined1 *)((int)param_2 + 5) = uVar1;
  *(char *)((int)param_2 + 6) = (char)in_EAX;
  *(undefined1 *)(param_2 + 2) = *(undefined1 *)(param_1 + 0x45204);
  *(char *)(param_1 + 0x45204) = *(char *)(param_1 + 0x45204) + '\x01';
  *(undefined4 *)((int)param_2 + 9) = *(undefined4 *)(param_1 + 0x15d);
  *(undefined4 *)((int)param_2 + 0xd) = *(undefined4 *)(param_1 + 0x161);
  *(undefined4 *)((int)param_2 + 0x11) = *(undefined4 *)(param_1 + 0x165);
  puVar3 = (undefined4 *)(param_1 + (in_EAX * 3 + 0xf) * 8);
  *(undefined4 *)((int)param_2 + 0x15) = *puVar3;
  *(undefined4 *)((int)param_2 + 0x19) = puVar3[1];
  *(undefined4 *)((int)param_2 + 0x1d) = puVar3[2];
  *(undefined2 *)((int)param_2 + 0x21) = param_3;
  *(char *)((int)param_2 + 0x23) = param_4;
  *(char *)(param_2 + 1) =
       *(char *)((int)param_2 + 0x22) + *(char *)(param_2 + 2) + param_4 +
       *(char *)((int)param_2 + 0x21) + -0x34;
  return;
}

