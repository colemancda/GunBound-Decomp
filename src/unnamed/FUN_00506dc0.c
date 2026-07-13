/* FUN_00506dc0 - 0x00506dc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BlitRLESprite's 4th arg (rleData) and 1st arg (this/param_1) were
 * dropped in the raw port (in_EAX and a bare `0` respectively). objdump
 * at this call site (0x506df9) shows:
 *   mov ecx,[esi+0x28] / add ecx,0x18   -> ECX/param_1 (this)
 *   mov ecx,[esi+0x2c] / add ecx,0x10 ; push ecx  -> param_2 (x), already
 *                                         present in the raw port
 *   push 0xffff                         -> param_3 (color), already present
 *   mov eax,edi  (edi = esi+0x90, loaded earlier and reused from the
 *                 DrawFontString call just above)   -> rleData
 * The same `param_1+0x90` pointer and the same `*(param_1+0x28)+0x18`
 * "this" value also feed the preceding DrawFontString call (0x4eb510),
 * matching that call's own dropped in_EAX argument - i.e. this function
 * draws a label string at a fixed widget-relative position via
 * DrawFontString, then blits an RLE glyph/icon using the same string
 * pointer and cursor position immediately after.
 */
#include "ghidra_types.h"


void __fastcall FUN_00506dc0(int param_1)

{
  Widget_DrawSelf(param_1);
  DrawFontString(*(int *)(param_1 + 0x2c) + 0x10,0);
  BlitRLESprite(*(int *)(param_1 + 0x28) + 0x18,*(int *)(param_1 + 0x2c) + 0x10,0xffff,
                (byte *)(param_1 + 0x90));
  return;
}

