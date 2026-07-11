/* CalculateAngleFromDelta - 0x004f1f10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall CalculateAngleFromDelta(int param_1)

{
  int in_EAX;
  
  for (; (((in_EAX < -0x7f || (0x80 < in_EAX)) || (param_1 < -0x7f)) || (0x80 < param_1));
      param_1 = param_1 / 2) {
    in_EAX = in_EAX / 2;
  }
  return (int)*(short *)(&DAT_00598e7e + (param_1 * 0x100 + in_EAX) * 2);
}

