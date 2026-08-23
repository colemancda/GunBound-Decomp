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
  
  if ((((g_clipMinY <= in_EAX) && (in_EAX <= g_clipMaxY)) && (g_clipMinX <= param_1 + param_3)
      ) && (param_1 <= g_clipMaxX)) {
    if (param_1 < g_clipMinX) {
      param_2 = param_2 + (g_clipMinX - param_1) * 2;
      param_3 = param_3 + (param_1 - g_clipMinX);
      param_1 = g_clipMinX;
    }
    if (g_clipMaxX < param_1 + param_3) {
      param_3 = (g_clipMaxX - param_1) + 1;
    }
    QueueCompositorSpan(param_1,param_1 + param_3,param_2,(int)&g_spriteDrawBatchPool);
  }
  return;
}

