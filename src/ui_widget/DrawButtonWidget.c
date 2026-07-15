/* DrawButtonWidget - 0x00405ea0 in the original binary.
 *
 * ButtonWidget vtable slot 3 (draw). Reads the stored frame index (+0x30,
 * skipped if negative - the standard hidden-widget sentinel) and position
 * (+0x38/+0x3c), resolves via FindSpriteFrame, then dispatches to
 * BlitSprite16bpp or BlitSpriteClipped depending on the resolved frame's
 * clip flag (+0x18). Was previously untracked in PROGRESS.csv - added back
 * this pass, same as WorldListPanel_Draw earlier.
 *
 * FIXED (2026-07-15): FindSpriteFrame/BlitSprite16bpp/BlitSpriteClipped
 * were all called with dropped args here (this file predates their
 * project-wide promotion). Confirmed via angr disassembly at
 * 0x405ea0-0x405eea: container=&DAT_00ea0e18 (the standard sprite
 * registry, matching every other FindSpriteFrame call site),
 * outerKey=*(this+0x18) (m_spriteBase, loaded once into EDX and never
 * touched again - still live at both the BlitSprite16bpp and
 * BlitSpriteClipped calls below, matching the established "outerKey
 * inherited via EDX" convention), innerKey=frame (this+0x30, ESI).
 * BlitSprite16bpp/BlitSpriteClipped both then take (frame,x,y,outerKey)
 * with the same inherited outerKey.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"

void __fastcall DrawButtonWidget(int this)

{
  int x;
  int frame;
  int y;
  int outerKey;
  int record;

  x = *(int *)(this + 0x38);
  frame = *(int *)(this + 0x30);
  y = *(int *)(this + 0x3c);
  outerKey = *(int *)(this + 0x18);
  if ((DAT_0079352c != 0) && (-1 < frame)) {
    record = FindSpriteFrame((int)&DAT_00ea0e18,outerKey,frame);
    if (record != 0) {
      if (*(char *)(record + 0x18) == '\x01') {
        BlitSprite16bpp(frame,x,y,outerKey);
        return;
      }
      BlitSpriteClipped(frame,x,y,outerKey);
    }
  }
  return;
}
