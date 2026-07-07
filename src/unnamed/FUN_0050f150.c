/* FUN_0050f150 - 0x0050f150 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __thiscall FUN_0050f150(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  uint in_EAX;
  
  puVar1 = *(undefined4 **)(param_1 + 4);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return in_EAX & 0xffffff00;
    }
    in_EAX = puVar1[2];
    puVar1 = (undefined4 *)*puVar1;
  } while ((((*(char *)(in_EAX + 0x1e) != '\0') || (param_2 <= *(int *)(in_EAX + 0x28))) ||
           (*(int *)(in_EAX + 0x30) + *(int *)(in_EAX + 0x28) <= param_2)) ||
          ((param_3 <= *(int *)(in_EAX + 0x2c) ||
           (in_EAX = *(int *)(in_EAX + 0x34) + *(int *)(in_EAX + 0x2c), (int)in_EAX <= param_3))));
  return CONCAT31((int3)(in_EAX >> 8),1);
}

