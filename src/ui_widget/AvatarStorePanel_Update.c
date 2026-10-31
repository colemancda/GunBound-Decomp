/* AvatarStorePanel_Update - 0x0050aa10 in the original binary.
 *
 * CAvatarStorePanel's slot 9 (Update): the word at 0x557eb8+0x24 is
 * 0x50aa10, in place of CPanel's Widget_DrawSelf (0x5054b0).
 * find_vtable_refs.py finds it only there, and callsite_regs.py finds no
 * direct calls. CARVED 2026-10-30 from the disassembly; Ghidra never
 * carved it, so there was no decompile to start from. 1071 bytes,
 * `mov ebp,ecx` at 0x50aa17, plain `ret` (no stack arguments), so it is
 * __fastcall(this) here, the shape of the other ported panel Update
 * bodies (ChatLogPanel_Update, LobbyChatPanel_Update).
 *
 *   0x50aa19 m_hidden (+0x1e) set -> return
 *   0x50aa28 [0x5b3414] = g_gameStateVTableArray[7], the store state
 *   0x50aa34 call 0x5054b0                 ; Widget_DrawSelf, ECX = this
 *   0x50aa53 sprintf(buf, "%3d", [ctx+0x44e24])   ; catalog record count
 *   0x50aa7a call 0x4ed9f0                 ; BlitSpriteText: ECX = m_x+0xc1,
 *            EBX = m_y+0xb, ESI = 0x1f4, stack (0, buf, 3, 8)
 *   0x50aa7f..0x50ab2a three 8-entry tables built on the stack:
 *            x offsets  78 78 78 b1 78 b1 b1 b1   ([esp+0x5c])
 *            y offsets  22 55 33 33 44 44 55 22   ([esp+0x3c])
 *            frames     08 14 0c 0e 10 12 16 0a   ([esp+0x1c])
 *   0x50ab40 for i in 0..7 (EDI), x = m_x + xoff[i] (EBX),
 *            y = m_y + yoff[i] (EBP):
 *     the guarded count at state + 0x31488 + i*0x224 (PeekPacketChecksumState,
 *     EAX cell, under g_valueGuardLock):
 *       i == 0: frame = (count <= 0) ? 9 : 8         (setle, 0x50ab7e)
 *       i  > 0: frame = frames[i] + (count < 0)      (setl 0x50ac36, inc 0x50ac81)
 *     if g_screenSurface ([0x79352c]) and frame >= 0 (i > 0 only, 0x50ac56)
 *     and FindSpriteFrame(0xea0e18, 0x2713, frame) (EAX/EDX/ESI):
 *       +0x18 == 1 -> BlitSprite16bpp(frame, x, y, 0x2713)  (EAX, push y, push x, EDX)
 *       else       -> BlitSpriteClipped(frame, x, y, 0x2713) (push, ECX, EAX, EDX)
 *     then the same cell is peeked again, sprintf(buf, "%02d", abs(count))
 *     (cdq/xor/sub at 0x50acc3) and BlitSpriteText: ECX = x+0x14,
 *     EBX = y, ESI = 0x1f4, stack (0x28, buf, 2, 6)
 *   0x50ad10 for row in 0..13: call 0x50ae40, ECX = row, EAX = this
 *            (RenderAvatarListRow)
 *   0x50ad25 if +0x94 != -1: push [0x56d110] / push m_x+0x13 / push this /
 *            call 0x50be20 (RenderAvatarListDragRow, ret 0xc)
 *   0x50ad5a peek ctx + 0x4111c; if bit 0x10 set -> return
 *   0x50ad75 +0x98 = (+0x98 + 1) % 0x28; if the result >= 0x14 -> return
 *   0x50ad93 if g_screenSurface: the walk at 0x50ada0-0x50adf6 is
 *            FindSpriteFrame(0xea0e18, 0x2712, 2) inlined (the same
 *            outer-key/+0x1c, inner-key/+0x10 walk as 0x4f30c0, returning
 *            on a miss), then BlitSprite16bpp(2, 0x292, 0x23, 0x2712) or
 *            BlitSpriteClipped(2, 0x292, 0x23, 0x2712) by the frame's +0x18
 *
 * So it draws the store panel's frame, the catalog count, the eight
 * category tabs with their item counts (each tab's sprite moves to its
 * next frame when its count is negative), the 14 list rows and the
 * drag ghost, and blinks the 0x2712/2 marker at (0x292, 0x23) on a
 * 40-tick cycle (20 on, 20 off) unless bit 0x10 of the guarded flags at
 * ctx+0x4111c is set.
 *
 * WIRED (2026-10-31) as CAvatarStorePanel::Update in src/cxx/Panel.cpp.
 * It was held back on 2026-10-30 because RenderAvatarListRow (0x50ae40)
 * and RenderAvatarListDragRow (0x50be20) passed BlitSpriteText 4 of its
 * 7 arguments and read unaff_ register artifacts. Both were rewritten
 * from the disassembly first. Every callee this makes live was checked:
 * Widget_DrawSelf, BlitSpriteText, FindSpriteFrame, BlitSprite16bpp,
 * BlitSpriteClipped, BlitRLESprite (and its glyph plotters FUN_004eaeb0
 * and BlitFontGlyphClipped), PeekPacketChecksumState and the two row
 * renderers all take their register arguments as parameters, and
 * tools/dropped_reg_backlog.py lists none of them.
 *
 * The two format strings are the original's .data strings, "%3d" at
 * 0x551ecc (PTR_DAT_00551ecc) and "%02d" at 0x555654 (DAT_00555654).
 * Until 2026-10-31 the port's storage for both was zeroed, so this body
 * used literals.
 *
 * NAMED 2026-10-31, CERTAIN (was FUN_0050aa10). The vtable word above
 * is the evidence: 0x557eb8 is stored only by BuildAvatarStorePanel (at
 * 0x509ea5), its slots 4, 7 and 8 are the already-named
 * AvatarStorePanel_HitTest / _OnCommand / _Draw, and slot 9 is
 * CWidget::Update. Same <Panel>_Update form as ChatLogPanel_Update and
 * CreateRoomDialog_Update.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall AvatarStorePanel_Update(int this_)

{
  static const int tabX[8] = {0x78,0x78,0x78,0xb1,0x78,0xb1,0xb1,0xb1};
  static const int tabY[8] = {0x22,0x55,0x33,0x33,0x44,0x44,0x55,0x22};
  static const int tabFrame[8] = {8,0x14,0xc,0xe,0x10,0x12,0x16,10};
  int state;
  int i;
  int x;
  int y;
  int count;
  int frame;
  int sprite;
  char negative;
  uint flags;
  char buf[0x80];

  if (*(char *)(this_ + 0x1e) != '\0') {
    return;
  }
  state = (int)g_gameStateVTableArray[7];
  Widget_DrawSelf(this_);
  _sprintf(buf,PTR_DAT_00551ecc,*(int *)(g_clientContext + 0x44e24));
  BlitSpriteText(*(int *)(this_ + 0x28) + 0xc1,0,(int)buf,3,8,*(int *)(this_ + 0x2c) + 0xb,0x1f4);
  for (i = 0; i < 8; i = i + 1) {
    x = *(int *)(this_ + 0x28) + tabX[i];
    y = *(int *)(this_ + 0x2c) + tabY[i];
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    count = (int)PeekPacketChecksumState((void *)(state + 0x31488 + i * 0x224));
    if (i == 0) {
      negative = count <= 0;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      frame = negative ? 9 : 8;
    }
    else {
      negative = count < 0;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      frame = tabFrame[i];
      if (negative) {
        frame = frame + 1;
      }
    }
    if ((g_screenSurface != 0) && ((i == 0) || (-1 < frame)) &&
        (sprite = FindSpriteFrame((int)&g_spriteRegistry,0x2713,frame), sprite != 0)) {
      if (*(char *)(sprite + 0x18) == '\x01') {
        BlitSprite16bpp(frame,x,y,0x2713);
      }
      else {
        BlitSpriteClipped(frame,x,y,0x2713);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    count = (int)PeekPacketChecksumState((void *)(state + 0x31488 + i * 0x224));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (count < 0) {
      count = -count;
    }
    _sprintf(buf,DAT_00555654,count);
    BlitSpriteText(x + 0x14,0x28,(int)buf,2,6,y,0x1f4);
  }
  for (i = 0; i < 0xe; i = i + 1) {
    RenderAvatarListRow(i,this_);
  }
  if (*(int *)(this_ + 0x94) != -1) {
    RenderAvatarListDragRow(this_,*(int *)(this_ + 0x28) + 0x13,g_cursorAnchorY);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  flags = PeekPacketChecksumState((void *)(g_clientContext + 0x4111c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((flags & 0x10) != 0) {
    return;
  }
  *(int *)(this_ + 0x98) = (*(int *)(this_ + 0x98) + 1) % 0x28;
  if (0x13 < *(int *)(this_ + 0x98)) {
    return;
  }
  if (g_screenSurface == 0) {
    return;
  }
  sprite = FindSpriteFrame((int)&g_spriteRegistry,0x2712,2);
  if (sprite == 0) {
    return;
  }
  if (*(char *)(sprite + 0x18) == '\x01') {
    BlitSprite16bpp(2,0x292,0x23,0x2712);
  }
  else {
    BlitSpriteClipped(2,0x292,0x23,0x2712);
  }
  return;
}
