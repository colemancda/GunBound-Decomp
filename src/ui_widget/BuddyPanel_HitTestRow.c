/* BuddyPanel_HitTestRow - 0x00505ec0 in the original binary.
 *
 * NAMED (batch 36), LIKELY. Maps a point to a buddy-list row for the buddy
 * panel: ECX = x, EDX = the panel, ESI = y (see the dropped-register note
 * below). If x is inside the list column (panel x + 0xe .. + 0xae) and y
 * falls in one of seven 0x1d-pixel bands starting at panel y + 0x2d, it
 * returns the list scroll base DAT_00e54da8 plus the band index and also
 * stores that into panel +0x90 (the selected row); otherwise -1.
 *
 * Evidence is the callers. Its only two callers are CBuddyPanel's slot 2
 * (0x505c10, OnMouseDown, call at 0x505c2b) and slot 4 (0x505c90, HitTest,
 * call at 0x505c9f). OnMouseDown treats a non -1 result as the selection and
 * clears it on a press outside; HitTest feeds the result to
 * FindActiveObjectByIndex on the buddy record array and then raises or
 * opens that buddy's whisper window by name. No other panel calls it.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-10-30): the y coordinate arrives in ESI. It is
 * read at 0x505ee3/0x505ee7 (`cmp edi,esi` / `cmp esi,eax`, the band
 * test) and never written. The only two binary callers are CBuddyPanel's
 * slots 2 and 4, 0x505c2b and 0x505c9f, where ESI holds the y argument
 * (`mov esi,[esp+0x14]` at 0x505c17, `mov esi,[esp+0x10]` at 0x505c92).
 * Both were uncarved until this fix, so the port had no callers and read
 * an unassigned unaff_ESI. Promoted to a trailing parameter. ECX is x,
 * EDX the panel; the result is [0xe54da8] + the band index, or -1.
 */
#include "ghidra_types.h"


int __fastcall BuddyPanel_HitTestRow(int param_1,int param_2,int regEsi)

{
  int iVar1;
  int iVar2;
  int unaff_ESI = regEsi;
  
  if ((*(int *)(param_2 + 0x28) + 0xe < param_1) && (param_1 < *(int *)(param_2 + 0x28) + 0xae)) {
    iVar2 = 0;
    iVar1 = *(int *)(param_2 + 0x2c) + 0x4b;
    do {
      if ((iVar1 + -0x1e < unaff_ESI) && (unaff_ESI < iVar1)) {
        iVar2 = DAT_00e54da8 + iVar2;
        *(int *)(param_2 + 0x90) = iVar2;
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x1d;
    } while (iVar2 < 7);
  }
  return -1;
}

