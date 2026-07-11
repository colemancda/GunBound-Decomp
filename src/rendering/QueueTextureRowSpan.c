/* QueueTextureRowSpan - 0x004eba80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall QueueTextureRowSpan(int param_1,int param_2,int param_3)

{
  int in_EAX;
  
  if ((((DAT_00793534 <= in_EAX) && (in_EAX <= DAT_0056df34)) && (DAT_00793530 <= param_1 + param_3)
      ) && (param_1 <= DAT_0056df30)) {
    if (param_1 < DAT_00793530) {
      param_2 = param_2 + (DAT_00793530 - param_1) * 2;
      param_3 = param_3 + (param_1 - DAT_00793530);
      param_1 = DAT_00793530;
    }
    if (DAT_0056df30 < param_1 + param_3) {
      param_3 = (DAT_0056df30 - param_1) + 1;
    }
    QueueCompositorSpan(param_1,param_1 + param_3,param_2);
  }
  return;
}

