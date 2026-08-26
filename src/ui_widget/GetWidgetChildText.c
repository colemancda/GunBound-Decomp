/* GetWidgetChildText - 0x0040cfe0 in the original binary.
 *
 * Two-level lookup in a widget registry, returning the found child's text.
 *
 * SetWidgetReadyState (0x406380) is the named twin: it opens with the same
 * `*(*(regEax + 4) + 0x1c)` entry, walks the same +0x1c list comparing +4
 * against a key, then descends through +0x10 and walks THAT list comparing
 * +8 against a second key -- an outer widget id and an inner child id.  The
 * only difference is what each does on arrival: the twin sets the child's
 * ready state, this one returns the child's +0x48.
 *
 * That +0x48 is the widget text buffer, and four already-named files say so
 * independently: InitTextBoxWidget zeroes a 0x400-byte buffer there and
 * documents the layout (+0x38 x, +0x3c y, +0x40 w, +0x44 h, +0x48
 * text[0x400]); CommitActiveTextInput writes GetWindowTextA into it;
 * SyncActiveTextInput reads it back; Widget_DrawSelf draws it.  All three
 * call sites here confirm it from the other end -- each copies a
 * NUL-terminated string out of the returned pointer.
 *
 * Returns 0 when either walk overshoots its key, so the lists are sorted
 * ascending and a miss is detectable; the callers do not check.
 *
 * ESI RECOVERED (2026-08-25): an immediate at all three sites -- 0 twice and 1
 * once.  The two FUN_00445450 sites are the pair that needed care: they are
 * adjacent source lines separated only by an inline string-copy loop, so that
 * loop's own `jne` is the only branch between them and neither call can be
 * reached without the other.  VA order is source order there, which makes the
 * first 0 and the second 1.
 */
#include "ghidra_types.h"


int __fastcall GetWidgetChildText(undefined4 param_1,uint widgetId,int regEax,uint childId)
{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while( true ) {
    if (widgetId < uVar1) {
      return 0;
    }
    if (uVar1 == widgetId) break;
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  iVar2 = *(int *)(iVar2 + 0x10);
  uVar1 = *(uint *)(iVar2 + 8);
  if (childId < uVar1) {
    return 0;
  }
  while (uVar1 != childId) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (childId < uVar1) {
      return 0;
    }
  }
  if (iVar2 == 0) {
    return 0;
  }
  return iVar2 + 0x48;
}

