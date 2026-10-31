/* RenderAvatarListDragRow - 0x0050be20 in the original binary.
 *
 * The drag-ghost twin of RenderAvatarListRow (0x50ae40): the one binary
 * call site, 0x50ad3c in the store panel's uncarved slot-9 Update at
 * 0x50aa10, runs right after the 14-row loop and ONLY while the panel's
 * +0x94 slot is not -1 - the catalog index of the row being dragged,
 * which the mouse-up handler FUN_0050a320 consumes as the source of its
 * catalog-record reorder and resets to -1.  Call shape at
 * 0x50ad25-0x50ad3c: RenderAvatarListDragRow(panel, panel->m_x + 0x13,
 * [0x56d110]) - and 0x56d110 is g_cursorAnchorY, the live cursor Y.  So
 * this draws the dragged item's row contents (same equipped marker,
 * part code and category cells as the row renderer, on the record at
 * *(panel+0x94)*0x450) at the cursor's height while a drag is in
 * flight.
 *
 * NOT A LIVE-IN (2026-09-01 workflow triage): the backlog's unaff_EDI
 * row is a PHANTOM - the first EDI touch at 0x50be41 is a write that
 * dominates the function, and every later EDI read consumes an
 * in-function value (a cell pointer, or the [esp+0x10] counter Ghidra
 * mis-rendered as unaff_EDI). No signature change is correct here; the
 * fix class is rewriting the mis-rendered expressions, not promotion.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 36 argless PeekPacketChecksumState() calls (worklist 36:36).
 * Twin of RenderAvatarListRow with the state object's own slot arrays: frame
 * [esp+0x18] = local_84 = g_gameStateVTableArray[7] (written at 0x50be34,
 * `mov [esp+0x10],eax` two pushes deep - the older BlitRLESprite note
 * below that says the slot is never written missed the push depth; its
 * 4th arg is therefore local_84+0x331c4 (0x50c138) and is now passed).
 * Cells: g_clientContext + local_88 + 0x5f4ab8 (equipped array,
 * 0x50beae); the catalog record *(ctx+0x44e20) + *(param_1+0x94)*0x450 at
 * +0x22c (0x50bfbd/0x50c019/0x50c0f4); then eight 4-peek blocks on
 * local_84 + 0x33624/0x34520/0x33a6c/0x33c90/0x33eb4/0x340d8/0x33848/
 * 0x342fc (address order, confirmed by the BlitSpriteClipped ids 8..0x17
 * the C keeps; each block's follow-up peeks re-read EDI, which holds the
 * block's cell for the whole block).
 *
 * REWRITTEN FROM THE DISASSEMBLY (2026-10-31). As in RenderAvatarListRow,
 * Ghidra lost the frame after the BlitRLESprite call: the stat blocks
 * read unaff_EBX/unaff_EBP/unaff_ESI/unaff_EDI, unaff_retaddr, iStack_*
 * and stack0x artifacts, and every BlitSpriteText call passed 4 of its 7
 * arguments.  None is a live-in (EBX/EBP/ESI/EDI are pushed and written
 * first), so the fix is the frame, not a promotion.  After
 * `sub esp,0x8c` and the four pushes:
 *   [esp+0x10] col, the stat-column counter (2 at 0x50c14f)
 *   [esp+0x14] the column x, col*0x19 + x   (0x50c346 etc.)
 *   [esp+0x18] state = [0x5b3414]           (0x50be34, two pushes deep)
 *   [esp+0x1c] the sprintf buffer
 *   [esp+0xa0] panel, [esp+0xa4] x, [esp+0xa8] y  (ret 0xc at 0x50cd9e)
 * BlitSpriteText sites:
 *   0x50c2c7  ECX = x+0xa2, EBX = y+4, ESI = 0x1f4, (0x28, buf, 2, 6)
 *   0x50c450 0x50c5da 0x50c764 0x50c8ee 0x50ca78 0x50cc02 0x50cd8c
 *             ECX = x + col*0x19 + 0x70, EBX = y+4, ESI = 0x1f4,
 *             (0x28, buf, 2, 6)
 * The stats are RenderAvatarListRow's with the drag block's cells:
 * state+0x33624 (frames 9/8) then 0x34520, 0x33a6c, 0x33c90, 0x33eb4,
 * 0x340d8, 0x33848, 0x342fc (frames 0xa..0x17), and the item name is
 * BlitRLESprite(x+0x18, y+3, key, state+0x331c4).
 */

#include "ghidra_types.h"
#include <windows.h>


static void RenderAvatarListDragRow_Blit(int frame,int x,int y,int key)
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

static int RenderAvatarListDragRow_Peek(void *cell)
{
  int value;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  value = (int)PeekPacketChecksumState(cell);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return value;
}

void RenderAvatarListDragRow(int param_1,int param_2,int param_3)

{
  static const int statOffset[7] = {0x34520,0x33a6c,0x33c90,0x33eb4,0x340d8,0x33848,0x342fc};
  static const int statFrame[7] = {0xa,0xc,0xe,0x10,0x12,0x14,0x16};
  char *state;
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

  state = g_gameStateVTableArray[7];
  /* 0x50be38-0x50be81: the highlight under the ghost */
  RenderAvatarListDragRow_Blit(1,param_2,param_3,0x2712);
  /* 0x50be92-0x50bf75: the equipped marker */
  for (off = 0; off < 0x890; off = off + 0x224) {
    index = *(int *)(param_1 + 0x94);
    if (RenderAvatarListDragRow_Peek((void *)(g_clientContext + off + 0x5f4ab8)) == index) {
      RenderAvatarListDragRow_Blit(7,param_2,param_3 + 4,0x2713);
    }
  }
  /* 0x50bf7b-0x50c0af: the part-code frame */
  index = *(int *)(param_1 + 0x94);
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)index) {
    ThrowCxxException(0x80070057);
  }
  value = RenderAvatarListDragRow_Peek((void *)(*(int *)(g_clientContext + 0x44e20) + index * 0x450 + 0x22c));
  frame = (value >> 0x10 & 0xf) * 2;
  if (frame != 6) {
    index = *(int *)(param_1 + 0x94);
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)index) {
      ThrowCxxException(0x80070057);
    }
    value = RenderAvatarListDragRow_Peek((void *)(*(int *)(g_clientContext + 0x44e20) + index * 0x450 + 0x22c));
    if ((value & 0x8000) == 0) {
      frame = frame + 1;
    }
  }
  if (-1 < frame) {
    RenderAvatarListDragRow_Blit(frame,param_2 + 6,param_3 + 2,0x2713);
  }
  /* 0x50c0b2-0x50c142: the item name */
  index = *(int *)(param_1 + 0x94);
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)index) {
    ThrowCxxException(0x80070057);
  }
  value = RenderAvatarListDragRow_Peek((void *)(*(int *)(g_clientContext + 0x44e20) + index * 0x450 + 0x22c));
  key = (-(uint)((value & 0x20000000) != 0x20000000) & 0x480d) + 0xb7f2;
  BlitRLESprite(param_2 + 0x18,param_3 + 3,key,(byte *)(state + 0x331c4));
  /* 0x50c14a-0x50c2cf: the first stat */
  col = 2;
  if (RenderAvatarListDragRow_Peek(state + 0x33624) != 0) {
    if (RenderAvatarListDragRow_Peek(state + 0x33624) <= 0) {
      RenderAvatarListDragRow_Blit(9,param_2 + 0x99,param_3 + 2,0x2713);
      value = -RenderAvatarListDragRow_Peek(state + 0x33624);
    }
    else {
      RenderAvatarListDragRow_Blit(8,param_2 + 0x99,param_3 + 2,0x2713);
      value = RenderAvatarListDragRow_Peek(state + 0x33624);
    }
    _sprintf(buf,DAT_00555654,value);
    BlitSpriteText(param_2 + 0xa2,0x28,(int)buf,2,6,param_3 + 4,0x1f4);
    col = 1;
  }
  /* 0x50c2d7-0x50cd91: the other seven stats */
  for (i = 0; i < 7; i = i + 1) {
    if ((RenderAvatarListDragRow_Peek(state + statOffset[i]) != 0) && (col < 3)) {
      negative = RenderAvatarListDragRow_Peek(state + statOffset[i]) < 0;
      colX = col * 0x19 + param_2;
      if (negative) {
        RenderAvatarListDragRow_Blit(statFrame[i],colX + 0x67,param_3 + 2,0x2713);
        value = -RenderAvatarListDragRow_Peek(state + statOffset[i]);
      }
      else {
        RenderAvatarListDragRow_Blit(statFrame[i] + 1,colX + 0x67,param_3 + 2,0x2713);
        value = RenderAvatarListDragRow_Peek(state + statOffset[i]);
      }
      _sprintf(buf,DAT_00555654,value);
      BlitSpriteText(colX + 0x70,0x28,(int)buf,2,6,param_3 + 4,0x1f4);
      col = col - 1;
    }
  }
  return;
}
