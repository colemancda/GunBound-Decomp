/* QueueTextureRowSpan - 0x004eba80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-31): the y row Ghidra left as a read-before-
 * write `in_EAX` local is a real live-in - the only caller, the loop in
 * QueueTextureRegionSpans (0x4ebba1), sets `mov eax,edi` (the current
 * row) right before the call, alongside ECX=param_1 (x), EDX=param_2
 * (texture row pointer) and the pushed width param_3. Promoted to a
 * trailing regEax parameter per the repo's EAX-first convention.
 */
#include "ghidra_types.h"


void __fastcall QueueTextureRowSpan(int param_1,int param_2,int param_3,int regEax)

{
  if ((((g_clipMinY <= regEax) && (regEax <= g_clipMaxY)) && (g_clipMinX <= param_1 + param_3)
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

