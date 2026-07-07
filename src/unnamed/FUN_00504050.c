/* FUN_00504050 - 0x00504050 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00504050(undefined4 param_1,undefined4 param_2)

{
  int *in_EAX;
  int iVar1;
  int local_c;
  undefined1 local_8 [8];
  
  local_c = 0;
  iVar1 = FUN_00500ef0(param_2,local_8,&local_c);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c == 0) {
    *(undefined4 *)(*in_EAX + (*(uint *)(iVar1 + 0xa8) % (uint)in_EAX[2]) * 4) =
         *(undefined4 *)(iVar1 + 0xa4);
    FUN_00500e80();
    return 1;
  }
  *(undefined4 *)(local_c + 0xa4) = *(undefined4 *)(iVar1 + 0xa4);
  FUN_00500e80();
  return 1;
}

