/* FUN_004e7d60 - 0x004e7d60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004e7d60(int param_1,int param_2)

{
  int in_EAX;
  
  if (param_2 == -1) {
    FUN_004e8ad0(*(undefined4 *)(*(int *)(in_EAX + 0x45234) + 4));
    *(int *)(*(int *)(in_EAX + 0x45234) + 4) = *(int *)(in_EAX + 0x45234);
    *(undefined4 *)(in_EAX + 0x45238) = 0;
    *(undefined4 *)*(undefined4 *)(in_EAX + 0x45234) = *(undefined4 *)(in_EAX + 0x45234);
    *(int *)(*(int *)(in_EAX + 0x45234) + 8) = *(int *)(in_EAX + 0x45234);
    return;
  }
  FUN_004e8a70();
  if (param_1 != *(int *)(in_EAX + 0x45234)) {
    FUN_004e87b0(in_EAX + 0x45230,&param_2,param_1);
  }
  return;
}

