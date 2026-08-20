/* FUN_00455b60 - 0x00455b60 in the original binary.
 *
 * No confirmed real name/purpose.  A two-level walk of the sprite/frame
 * registry rooted at DAT_00ea0e1c - the same root BlitSpriteAttached uses -
 * keyed by param_2 at the first level and param_5 at the second.
 *
 * ABI FIX (2026-08-19).  Ghidra marks this __fastcall, but ECX is written at
 * 0x455b6f before it is ever read, so param_1 is a PHANTOM; the real register
 * arguments are EDX (param_2, read at 0x455b72 `cmp ecx,edx`) and EAX
 * (0x455b65 `mov esi,eax`, Ghidra's `in_EAX`), plus 2 stack args.  EAX is not
 * expressible under MSVC, so `in_EAX` has been promoted to a real trailing
 * parameter (param_5) - the same trade documented for BlitSpriteAttached and
 * InitTextBoxWidget.  Callers pass 0 for param_1.
 *
 * Four of its six call sites are still in UNCARVED regions (0x488a38,
 * 0x488a6b, 0x4ae313, 0x4ae346 - other copies of the slot-3 publish logic);
 * only PublishProjectileTrackingState's two are ported, and both pass the
 * register arguments properly.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond this - not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


uint __fastcall FUN_00455b60(undefined4 param_1,uint param_2,int param_3,int param_4,uint param_5)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  
  uVar4 = *(uint *)(DAT_00ea0e1c + 0x1c);
  uVar10 = *(uint *)(uVar4 + 4);
  if (uVar10 <= param_2) {
    while (uVar10 != param_2) {
      uVar4 = *(uint *)(uVar4 + 0x1c);
      uVar10 = *(uint *)(uVar4 + 4);
      if (param_2 < uVar10) {
        return uVar4 & 0xffffff00;
      }
    }
    iVar1 = *(int *)(uVar4 + 0x10);
    uVar4 = *(uint *)(iVar1 + 8);
    while (uVar4 <= param_5) {
      if (uVar4 == param_5) {
        uVar10 = *(uint *)(iVar1 + 0x20);
        iVar5 = *(int *)(iVar1 + 0x28) + 0x30;
        uVar4 = uVar10 + iVar5;
        uVar8 = *(int *)(iVar1 + 0x2c) + 0x20;
        uVar2 = uVar4;
        if ((0 < (int)uVar4) && (iVar5 < 0x40)) {
          uVar2 = *(int *)(iVar1 + 0x24) + uVar8;
          if ((uVar2 != 0) && ((int)uVar8 < 0x40)) {
            uVar2 = -uVar8;
            puVar3 = (undefined4 *)
                     (*(int *)(iVar1 + 0x34) + uVar10 * (((int)uVar2 < 0) - 1 & uVar2) * 2);
            iVar7 = *(int *)(iVar1 + 0x24) - (uVar2 & ((int)uVar2 < 0) - 1);
            uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
            if (0x3f < (int)(iVar7 + uVar8)) {
              iVar7 = 0x3f - uVar8;
            }
            if (iVar5 < 0) {
              puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
              iVar5 = 0;
              uVar10 = uVar4;
            }
            if (0x3f < (int)(uVar10 + iVar5)) {
              uVar10 = 0x3f - iVar5;
            }
            if (0 < iVar7) {
              puVar6 = (undefined4 *)(uVar8 * param_4 + param_3 + iVar5 * 2);
              param_3 = iVar7;
              do {
                uVar2 = ((int)(uVar10 * 2) < 0) - 1 & uVar10 * 2;
                puVar9 = puVar3;
                puVar11 = puVar6;
                for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *puVar11 = *puVar9;
                  puVar9 = puVar9 + 1;
                  puVar11 = puVar11 + 1;
                }
                for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
                  *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
                  puVar9 = (undefined4 *)((int)puVar9 + 1);
                  puVar11 = (undefined4 *)((int)puVar11 + 1);
                }
                puVar3 = (undefined4 *)((int)puVar3 + *(int *)(iVar1 + 0x20) * 2);
                puVar6 = (undefined4 *)((int)puVar6 + param_4);
                param_3 = param_3 + -1;
              } while (param_3 != 0);
            }
            return CONCAT31((int3)((uint)puVar3 >> 8),1);
          }
        }
        return uVar2 & 0xffffff00;
      }
      iVar1 = *(int *)(iVar1 + 0x10);
      uVar4 = *(uint *)(iVar1 + 8);
    }
  }
  return uVar4 & 0xffffff00;
}

