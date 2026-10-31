/* ItemDescriptionTooltip_Update - 0x00506dc0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_00506dc0). Slot 9 (Update, +0x24) of vtable
 * 0x557c5c, which only BuildItemDescriptionTooltip installs; slot 9 is
 * the one every other panel class fills with Widget_DrawSelf or its own
 * *_Update (LobbyChatPanel_Update, CreateRoomDialog_Update), and this
 * body opens with that same Widget_DrawSelf call before drawing the
 * string at +0x90 - the item name BuildItemDescriptionTooltip copies
 * there from FindItemRecordByIcon. CItemDescriptionTooltip::Update in
 * src/cxx/Panel.cpp forwards here.
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
 *
 * WIRED (2026-10-30): slot 9 of vtable 0x557c5c. BuildItemDescriptionTooltip
 * now lives in src/cxx/Panel.cpp and builds a C++ CItemDescriptionTooltip,
 * whose Update forwards here with `this` in ECX.
 */
#include "ghidra_types.h"


void __fastcall ItemDescriptionTooltip_Update(int param_1)

{
  Widget_DrawSelf(param_1);
  /* RE-SLOT + dropped EAX (objdump @0x506dc9-0x506de0): x/ECX =
   * `mov ecx,[esi+0x28] / add ecx,0x18`, y = `mov eax,[esi+0x2c] / add
   * eax,0x10` (pushed), colour = 0, string = EAX = edi = param_1 + 0x90
   * (`lea edi,[esi+0x90]`) - exactly the values this file's own header
   * already traced for the BlitRLESprite on the next line. */
  DrawFontString(*(int *)(param_1 + 0x28) + 0x18,*(int *)(param_1 + 0x2c) + 0x10,0,
                 (char *)(param_1 + 0x90));
  BlitRLESprite(*(int *)(param_1 + 0x28) + 0x18,*(int *)(param_1 + 0x2c) + 0x10,0xffff,
                (byte *)(param_1 + 0x90));
  return;
}

