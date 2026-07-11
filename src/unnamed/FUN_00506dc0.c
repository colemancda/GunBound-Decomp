/* FUN_00506dc0 - 0x00506dc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00506dc0(int param_1)

{
  Widget_DrawSelf();
  DrawFontString(*(int *)(param_1 + 0x2c) + 0x10,0);
  BlitRLESprite(*(int *)(param_1 + 0x2c) + 0x10,0xffff);
  return;
}

