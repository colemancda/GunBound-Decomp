/* FUN_00403f30 - 0x00403f30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00403f30(int param_1,undefined4 param_2)

{
  undefined2 local_18 [4];
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  short local_a;
  
  local_10 = *(undefined2 *)(DAT_005b3484 + 0x3f804);
  local_e = *(undefined2 *)(DAT_005b3484 + 0x41340);
  local_c = *(undefined2 *)(DAT_005b3484 + 0x44e60);
  local_18[0] = 0x12;
  local_a = (ushort)(byte)((byte)((ushort)local_c >> 8) ^ 0x6b) + (ushort)((byte)local_c ^ 0x69) +
            (ushort)(byte)((byte)((ushort)local_e >> 8) ^ 0x73) + (ushort)((byte)local_e ^ 0x6d) +
            (ushort)(byte)((byte)((ushort)local_10 >> 8) ^ 0x6f) + (ushort)((byte)local_10 ^ 99);
  if (*(int **)(param_1 + 0x1bd4) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x1bd4) + 0x18))(param_2,local_18,&DAT_00551cb1);
  }
  return;
}

