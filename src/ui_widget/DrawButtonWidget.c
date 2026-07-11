/* DrawButtonWidget - 0x00405ea0 in the original binary.
 *
 * ButtonWidget vtable slot 3 (draw). Reads the stored frame index (+0x30,
 * skipped if negative - the standard hidden-widget sentinel) and position
 * (+0x38/+0x3c), resolves via FindSpriteFrame, then dispatches to
 * BlitSprite16bpp or BlitSpriteClipped depending on the resolved frame's
 * clip flag (+0x18). Was previously untracked in PROGRESS.csv - added back
 * this pass, same as WorldListPanel_Draw earlier.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"

void __fastcall DrawButtonWidget(int this)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;

  uVar1 = *(undefined4 *)(this + 0x38);
  iVar2 = *(int *)(this + 0x30);
  uVar3 = *(undefined4 *)(this + 0x3c);
  if ((DAT_0079352c != 0) && (-1 < iVar2)) {
    iVar4 = FindSpriteFrame();
    if (iVar4 != 0) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar1,uVar3);
        return;
      }
      BlitSpriteClipped(iVar2);
    }
  }
  return;
}
