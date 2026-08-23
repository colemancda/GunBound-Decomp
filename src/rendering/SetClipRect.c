/* SetClipRect - 0x004eadb0 in the original binary.
 *
 * Sets the current draw clip rectangle from two arbitrary corner points
 * (x1,y1)-(x2,y2), min/max-sorting each axis internally and clamping to
 * the 800x600 screen (g_clipMinX/793534 = clip min x/y,
 * g_clipMaxX/0056df34 = clip max x/y). Has ~23 real call sites across
 * the UI/HUD render paths (wind gauge, ready-room roster/status, in-
 * battle HUD, room list, chat/edit-box screens) - flagged since session 5
 * as needing its own dedicated recovery pass, done here (2026-07-15).
 *
 * FIXED: all 4 corner values were dropped registers - x1 (param_1, ECX,
 * __fastcall's 1st arg - the only one Ghidra kept), x2 (in_EAX), y1
 * (unaff_ESI), y2 (unaff_EDI). Recovered per call site via an angr
 * backward register-write scan (ECX/EAX treated as caller-saved/opaque
 * across an intervening call, ESI/EDI as callee-saved/traceable through
 * one) - see each call site's own comment for its specific values.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified beyond the above. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall SetClipRect(int x1, int x2, int y1, int y2)

{
  int iVar1;
  int iVar2;

  iVar1 = x1;
  if (x2 <= x1) {
    iVar1 = x2;
  }
  if (iVar1 < 0) {
    g_clipMinX = 0;
LAB_004eadd7:
    iVar2 = x1;
    iVar1 = g_clipMinX;
    if (x1 <= x2) goto LAB_004eaddd;
  }
  else {
    g_clipMinX = x2;
    iVar1 = x1;
    if (x2 <= x1) goto LAB_004eadd7;
LAB_004eaddd:
    g_clipMinX = iVar1;
    iVar2 = x2;
  }
  if (iVar2 < 800) {
    g_clipMaxX = x1;
    if (x1 <= x2) {
      g_clipMaxX = x2;
    }
  }
  else {
    g_clipMaxX = 799;
  }
  iVar1 = y2;
  if (y1 <= y2) {
    iVar1 = y1;
  }
  if (iVar1 < 0) {
    g_clipMinY = 0;
LAB_004eae2a:
    iVar2 = y2;
    iVar1 = g_clipMinY;
    if (y1 < y2) goto LAB_004eae32;
  }
  else {
    g_clipMinY = y1;
    iVar1 = y2;
    if (y1 <= y2) goto LAB_004eae2a;
  }
  g_clipMinY = iVar1;
  iVar2 = y1;
LAB_004eae32:
  if (iVar2 < 600) {
    g_clipMaxY = y2;
    if (y2 <= y1) {
      g_clipMaxY = y1;
    }
    return;
  }
  g_clipMaxY = 599;
  return;
}

