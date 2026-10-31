/* RenderAvatarListRow - 0x0050ae40 in the original binary.
 *
 * Draws one row of the Avatar Store's 14-row item list - the same list
 * AvatarListRowHitTest (0x50cdb0) maps points into, and the name
 * follows that sibling and the RenderWorldListRow / RenderBuddyRow
 * pattern.  The one binary call site, 0x50ad16, is the `for (row = 0;
 * row < 0xe; row++)` loop at 0x50ad10-0x50ad1f inside the store
 * panel's uncarved slot-9 Update at 0x50aa10 (m_hidden check, then
 * Widget_DrawSelf, then this loop), with ECX = the row and EAX = the
 * panel; the row's y is panel m_y + 0x68 + row*0x11, the same 0x11
 * stride the hit-test uses.  Per row: the selection highlight (sprite
 * set 0x2712) when row == the guarded selected index at state+0x228,
 * the equipped marker (0x2713) for equipped-array matches, and the
 * 0x450-stride catalog record at pageBase(+0x454)+row - all the same
 * State07 fields AvatarListRowHitTest's header documents.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 37 argless PeekPacketChecksumState() calls (worklist 37:37).
 * Frame: [esp+0x20] = local_84 (g_gameStateVTableArray[7], then
 * rebased by param_1*0x17e4 at 0x50b1b2), [esp+0x1c] = local_88,
 * [esp+0x14] = local_90 (the 0x224-stride equipped-array cursor).  Cells:
 * local_84+0x228 (selected index, 0x50ae83); g_clientContext + local_90
 * + 0x5f4ab8 (equipped array, 0x50af2b); the store-catalog record
 * *(ctx+0x44e20) + (*(local_84+0x454)+param_1)*0x450 at +0x22c (part
 * code, 0x50b02d/0x50b08b/0x50b162 - same imul 0x450 as the bounds check
 * against ctx+0x44e24 right above each); then the per-slot cells
 * local_84+0xe1e0 / +0xf0dc, and six category blocks at local_84 +
 * 0xe628/0xe84c/0xea70/0xec94/0xe404/0xeeb8 (address order, confirmed by
 * the BlitSpriteClipped ids 0xc..0x17 the C keeps).  Within each block the
 * three follow-up peeks read frame[0x18], which holds that block's cell
 * pointer (0x50b4cc etc.), so all four get the same cell; the C's
 * `local_8c = ...`/`local_90 = local_88 + 0xe84c` lines are Ghidra's
 * garbled rendering of that pointer store and were left alone.
 *
 * REWRITTEN FROM THE DISASSEMBLY (2026-10-31). From 0x50b1bb on, Ghidra
 * lost the stack frame: the seven stat blocks read unaff_EBX/unaff_EBP/
 * unaff_ESI/unaff_EDI and a stack0x artifact, and every BlitSpriteText
 * call passed 4 of its 7 arguments (`BlitSpriteText(0x28,local_80,2,6)`,
 * so 2 landed in the string-pointer slot).  None of those registers is a
 * live-in: EBX/EBP/ESI/EDI are all written in the prologue
 * (0x50ae4a-0x50ae5c), so there was nothing to promote; the fix is the
 * frame.  After the four pushes the frame is
 *   [esp+0x10] rowY = m_y + 0x68 + row*0x11       (0x50ae77)
 *   [esp+0x14] col, the stat-column counter       (2 at 0x50b1c3)
 *   [esp+0x1c] x0   = m_x + 0x13                   (0x50ae73)
 *   [esp+0x20] state, rebased by row*0x17e4        (0x50b1b2)
 *   [esp+0x24] the sprintf buffer
 * and every BlitSpriteText site sets ECX/EBX/ESI before `call 0x4ed9f0`:
 *   0x50b32c  ECX = x0+0xa2, EBX = rowY+4, ESI = 0x1f4, (0x28, buf, 2, 6)
 *   0x50b4a5 0x50b639 0x50b7cb 0x50b954 0x50bae6 0x50bc78 0x50be01
 *             ECX = x0 + col*0x19 + 0x70, EBX = rowY+4, ESI = 0x1f4,
 *             (0x28, buf, 2, 6)
 * The stat blocks: state+0xe1e0 (setle at 0x50b207: frame 9 and the
 * negated value, else 8, sprite at x0+0x99) sets col = 1; then
 * state+0xf0dc, 0xe628, 0xe84c, 0xea70, 0xec94, 0xe404, 0xeeb8 in that
 * order, each drawn only when non-zero and col < 3 (`cmp ...,3 / jge`),
 * frame 0xa/0xc/0xe/0x10/0x12/0x14/0x16 when negative (setl) and the next
 * frame otherwise, sprite at (x0 + col*0x19 + 0x67, rowY+2), then
 * `dec` col.  All sprites use set 0x2713.  The part-code frame's +1
 * test is `test bh,bh / js` at 0x50b09d, bit 15 of the second peek; the
 * old C read an uninitialised extraout_AH there.
 */

#include "ghidra_types.h"
#include <windows.h>


static void RenderAvatarListRow_Blit(int frame,int x,int y,int key)
{
  int sprite;

  if ((g_screenSurface != 0) &&
      (sprite = FindSpriteFrame((int)&g_spriteRegistry,key,frame), sprite != 0)) {
    if (*(char *)(sprite + 0x18) == '\x01') {
      BlitSprite16bpp(frame,x,y,key);
    }
    else {
      BlitSpriteClipped(frame,x,y,key);
    }
  }
}

static int RenderAvatarListRow_Peek(void *cell)
{
  int value;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  value = (int)PeekPacketChecksumState(cell);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return value;
}

void __fastcall RenderAvatarListRow(int param_1,int regEax)

{
  static const int statOffset[7] = {0xf0dc,0xe628,0xe84c,0xea70,0xec94,0xe404,0xeeb8};
  static const int statFrame[7] = {0xa,0xc,0xe,0x10,0x12,0x14,0x16};
  char *state;
  int rowY;
  int x0;
  int index;
  int off;
  int value;
  int frame;
  int col;
  int colX;
  int i;
  int negative;
  uint key;
  char buf[0x80];

  rowY = *(int *)(regEax + 0x2c) + 0x68 + param_1 * 0x11;
  x0 = *(int *)(regEax + 0x28) + 0x13;
  state = g_gameStateVTableArray[7];
  /* 0x50ae7b-0x50aeda: the selection highlight */
  if (param_1 == RenderAvatarListRow_Peek(state + 0x228)) {
    RenderAvatarListRow_Blit(1,x0,rowY,0x2712);
  }
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(state + 0x454) + param_1)) {
    return;
  }
  /* 0x50af10-0x50afe4: the equipped marker, four 0x224-stride cells */
  for (off = 0; off < 0x890; off = off + 0x224) {
    index = *(int *)(state + 0x454) + param_1;
    if (RenderAvatarListRow_Peek((void *)(g_clientContext + off + 0x5f4ab8)) == index) {
      RenderAvatarListRow_Blit(7,x0,rowY + 4,0x2713);
    }
  }
  /* 0x50afea-0x50b11c: the part-code frame */
  index = *(int *)(state + 0x454) + param_1;
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)index) {
    ThrowCxxException(0x80070057);
  }
  value = RenderAvatarListRow_Peek((void *)(*(int *)(g_clientContext + 0x44e20) + index * 0x450 + 0x22c));
  frame = (value >> 0x10 & 0xf) * 2;
  if (frame != 6) {
    index = *(int *)(state + 0x454) + param_1;
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)index) {
      ThrowCxxException(0x80070057);
    }
    value = RenderAvatarListRow_Peek((void *)(*(int *)(g_clientContext + 0x44e20) + index * 0x450 + 0x22c));
    if ((value & 0x8000) == 0) {
      frame = frame + 1;
    }
  }
  if (-1 < frame) {
    RenderAvatarListRow_Blit(frame,x0 + 6,rowY + 2,0x2713);
  }
  /* 0x50b11f-0x50b1b6: the item name */
  index = *(int *)(state + 0x454) + param_1;
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)index) {
    ThrowCxxException(0x80070057);
  }
  value = RenderAvatarListRow_Peek((void *)(*(int *)(g_clientContext + 0x44e20) + index * 0x450 + 0x22c));
  state = state + param_1 * 0x17e4;
  key = (-(uint)((value & 0x20000000) != 0x20000000) & 0x480d) + 0xb7f2;
  BlitRLESprite(x0 + 0x18,rowY + 3,key,(byte *)(state + 0xdd80));
  /* 0x50b1be-0x50b334: the first stat */
  col = 2;
  if (RenderAvatarListRow_Peek(state + 0xe1e0) != 0) {
    if (RenderAvatarListRow_Peek(state + 0xe1e0) <= 0) {
      RenderAvatarListRow_Blit(9,x0 + 0x99,rowY + 2,0x2713);
      value = -RenderAvatarListRow_Peek(state + 0xe1e0);
    }
    else {
      RenderAvatarListRow_Blit(8,x0 + 0x99,rowY + 2,0x2713);
      value = RenderAvatarListRow_Peek(state + 0xe1e0);
    }
    _sprintf(buf,(char *)&DAT_00555654,value);
    BlitSpriteText(x0 + 0xa2,0x28,(int)buf,2,6,rowY + 4,0x1f4);
    col = 1;
  }
  /* 0x50b33c-0x50be06: the other seven stats, right to left */
  for (i = 0; i < 7; i = i + 1) {
    if ((RenderAvatarListRow_Peek(state + statOffset[i]) != 0) && (col < 3)) {
      negative = RenderAvatarListRow_Peek(state + statOffset[i]) < 0;
      colX = col * 0x19 + x0;
      if (negative) {
        RenderAvatarListRow_Blit(statFrame[i],colX + 0x67,rowY + 2,0x2713);
        value = -RenderAvatarListRow_Peek(state + statOffset[i]);
      }
      else {
        RenderAvatarListRow_Blit(statFrame[i] + 1,colX + 0x67,rowY + 2,0x2713);
        value = RenderAvatarListRow_Peek(state + statOffset[i]);
      }
      _sprintf(buf,(char *)&DAT_00555654,value);
      BlitSpriteText(colX + 0x70,0x28,(int)buf,2,6,rowY + 4,0x1f4);
      col = col - 1;
    }
  }
  return;
}
