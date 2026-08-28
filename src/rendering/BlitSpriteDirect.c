/* BlitSpriteDirect - 0x0045b900 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Two-level sprite-registry blit: walks the list at DAT_00ea0e1c+0x1c
 * (next at node+0x1c) matching *(node+4) against the sprite-set id, then
 * walks that node's +0x10 chain (next at node+0x10) matching *(node+8)
 * against the second key, and rep-movs the located 16bpp frame into a
 * destination surface. Raw/near-verbatim port of Ghidra's decompiler
 * output beyond that - not hand-verified. See src/README.md's
 * "Raw/verbatim ports" section for status.
 *
 * ABI + RE-SLOT FIX (2026-08-28). The original takes TWO register
 * arguments plus ret 8 = 2 stack arguments, which is exactly the four
 * declared parameters once param_1 is understood as a phantom - the same
 * shape as its sibling BlitSpriteAttached (0x45b730), which shares this
 * registry. From the disassembly:
 * param_1 is a PHANTOM: ECX is written at 0x45b90e (mov ecx,[eax+4])
 * before it is ever read at 0x45b911 (cmp ecx,edx), and the
 * `sub esp,8` at entry is frame allocation, not a use - both
 * slots it reserves (entry-4, entry-8) are written at 0x45b964
 * and 0x45b97a before either is ever read.
 * param_2 = EDX, read before written at 0x45b911 - the OUTER key,
 * matched against *(node+4): the sprite-set id.
 * regEax  = EAX, read before written at 0x45b904 (mov esi,eax) - the
 * INNER key, matched against *(node+8). This was Ghidra's
 * unassigned `in_EAX`. It is the same CMobile +0x30 field that
 * BlitSpriteAttached takes as its own inner key; there is no
 * confirmed semantic name for it.
 * param_3 = stack arg 1, 0x45b9fa (mov esi,[esp+0x1c]) - the
 * destination pixel address.
 * param_4 = stack arg 2, 0x45b9f5 (imul ecx,[esp+0x20]) and 0x45ba32 -
 * the destination pitch in bytes, added to the destination
 * pointer once per scanline.
 * On the deepest path esp = entry-0x18 (sub esp,8; push esi 0x45b903;
 * push ebp 0x45b92c; push edi 0x45b955; push ebx 0x45b99b), so [esp+0x1c]
 * and [esp+0x20] are the only two slots that reach above the return
 * address; every other [esp+N] access - 0x45b964 and 0x45b9d7/0x45ba02/
 * 0x45ba0f at entry-4, 0x45b97a and 0x45b9b4 at entry-8 - lands inside
 * the entry `sub esp,8`. That is ret 8 exactly, with no third stack
 * argument. 0x45ba09 stores back into [esp+0x1c], which is the source's
 * own `param_3 = iVar7`.
 *
 * The mis-slotting was all on the caller side. All four sites - in
 * RenderMobile at 0x4629f5, 0x462a0e, 0x462cb5 and 0x462cfe - push the
 * destination address and the pitch and load EAX and EDX, but Ghidra
 * modelled the two PUSHES as the two __fastcall register slots. The C
 * therefore passed (dest, pitch) into param_1/param_2, pushed nothing at
 * all, and the callee's `ret 8` popped 8 bytes the caller never pushed.
 * Both arguments were re-slotted onto param_3/param_4 (the last push
 * before each call is stack arg 1 = param_3), the EDX sprite-set id was
 * supplied, and regEax was appended.
 *
 * regEax is *(this + 0x30) at all four sites (`mov eax,[ebp+0x30]` at
 * 0x4629ed, 0x462a0b, 0x462cb2 and 0x462cfb, immediately before or a few
 * instructions before each call). ebp holds RenderMobile's `this`: it is
 * set from ECX at 0x46291d and is not rewritten anywhere below 0x462d00,
 * which covers all four sites - it is re-based later by `add ebp,0xae15`
 * at 0x46359a and 0x4635dc, well past them. param_2 is *(this + 0x18)
 * (m_spriteId) at 0x4629f5 and 0x462cb5, and *(this + 0x904)
 * (m_spriteId2) at 0x462a0e and 0x462cfe.
 *
 * EAX is not expressible under MSVC, so the rebuild becomes ret 0xc
 * rather than ret 8, at the cost of that one argument no longer sitting
 * where the original put it - the same trade already accepted in
 * BlitSpriteAttached.c.
 */
#include "ghidra_types.h"


void __fastcall BlitSpriteDirect(undefined4 param_1,uint param_2,int param_3,int param_4,uint regEax)

{
  int iVar1;
  uint in_EAX = regEax;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  if (uVar8 <= param_2) {
    while (uVar8 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar8 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar8) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar8 <= in_EAX) {
      while (uVar8 != in_EAX) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar8 = *(uint *)(iVar2 + 8);
        if (in_EAX < uVar8) {
          return;
        }
      }
      iVar10 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x40;
      iVar1 = iVar10 + iVar5;
      uVar8 = *(int *)(iVar2 + 0x2c) + 0x70;
      if ((((0 < iVar1) && (iVar5 < 0x80)) && (*(int *)(iVar2 + 0x24) + uVar8 != 0)) &&
         ((int)uVar8 < 0x80)) {
        uVar4 = -uVar8;
        puVar3 = (undefined4 *)
                 (*(int *)(iVar2 + 0x34) + iVar10 * (((int)uVar4 < 0) - 1 & uVar4) * 2);
        iVar7 = *(int *)(iVar2 + 0x24) - (uVar4 & ((int)uVar4 < 0) - 1);
        uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
        if (0x7f < (int)(iVar7 + uVar8)) {
          iVar7 = 0x7f - uVar8;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar10 = iVar1;
        }
        if (0x7f < iVar10 + iVar5) {
          iVar10 = 0x7f - iVar5;
        }
        if (0 < iVar7) {
          puVar6 = (undefined4 *)(uVar8 * param_4 + param_3 + iVar5 * 2);
          param_3 = iVar7;
          do {
            uVar4 = (iVar10 * 2 < 0) - 1 & iVar10 * 2;
            puVar9 = puVar3;
            puVar11 = puVar6;
            for (uVar8 = uVar4 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            puVar3 = (undefined4 *)((int)puVar3 + *(int *)(iVar2 + 0x20) * 2);
            puVar6 = (undefined4 *)((int)puVar6 + param_4);
            param_3 = param_3 + -1;
          } while (param_3 != 0);
        }
      }
    }
  }
  return;
}

