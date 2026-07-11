/* RenderWindGaugeTick - 0x004c1c90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall RenderWindGaugeTick(int param_1)

{
  int iVar1;
  
  SetClipRect();
  iVar1 = g_clientContext;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  if ((&DAT_005f2f55)[iVar1] == '\x01') {
    DrawStageDecorationParallax(&DAT_006a7708 + iVar1);
  }
  DrawStageDecorationBase();
  SetClipRect();
  DrawWindGauge(&DAT_006a647c + g_clientContext);
  FlushCompositorLayer(1);
  return;
}

