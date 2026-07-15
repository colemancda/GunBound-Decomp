/* RenderWindGaugeTick - 0x004c1c90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-15): both SetClipRect calls dropped all 4 corner args -
 * see that file's own header for the recovery method. Values recovered
 * via angr at 0x4c1ca6/0x4c1ce9.
 */
#include "ghidra_types.h"


void __fastcall RenderWindGaugeTick(int param_1)

{
  int iVar1;

  SetClipRect(0, 0x31f, 0x22d, 0x26);
  iVar1 = g_clientContext;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  if ((&DAT_005f2f55)[iVar1] == '\x01') {
    DrawStageDecorationParallax(&DAT_006a7708 + iVar1);
  }
  DrawStageDecorationBase();
  SetClipRect(0, 0x31f, 0x257, 0);
  DrawWindGauge(&DAT_006a647c + g_clientContext);
  FlushCompositorLayer(1);
  return;
}

