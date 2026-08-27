/* SetWidgetReadyState - 0x00406380 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED, not merely appended.  `ret 4` gives one stack
 * argument, and the entry writes ECX (`mov ecx,[eax+4]`) before ever reading
 * it, so param_1 is a PHANTOM.  The real inputs are EAX (the widget
 * registry), EDX, one stack slot (the ready state), and EDI (the widget key).
 *
 * The port had been passing the ready state as that phantom param_1 and
 * omitting everything else.  An earlier pass here recovered EAX correctly but
 * APPENDED it, which put &g_activeObjectRegistry into param_2 -- an unrelated parameter
 * -- at all 13 call sites.  Nothing diagnosed that, because functions.h still
 * declared this K&R-empty, and a K&R prototype accepts any argument list; the
 * value looked recovered and was in the wrong slot.  The declaration is now a
 * real prototype, so the compiler enforces the arity from here on.
 *
 * Re-slotting needed no pairing of binary sites to source sites, which is
 * what makes it safe despite the caller being a switch full of shared tails
 * reached by goto (where VA order is emphatically not source order).  Every
 * value required was already determined: EAX is 0xe9be90 at all 13 sites,
 * EDX is 0 at all 13, the ready state is the argument the port already
 * passed, and the phantom takes 0 because nothing reads it.
 *
 * EDI needed the opposite treatment -- it genuinely varies across the sites,
 * so each one had to carry its own witness.  That is what the next paragraph
 * records; it is no longer open.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EDI is the WIDGET KEY the
 * registry walk compares against each widget's key at +8.  It is genuinely
 * live-in -- EDI appears in this function only as `cmp eax,edi` at 0x4063a3
 * and 0x4063af, read twice and written never.
 *
 * The 13 call sites pair without any ordering assumption, because Ghidra's
 * LAB_ names ARE the binary addresses: LAB_00445629, LAB_0044563c and
 * LAB_004457e7 sit exactly on `mov edi,0xb`, `mov edi,0xc` and `mov edi,0xd`.
 * The rest are separated by unique neighbouring constants -- the four
 * FUN_00449540(param_1, 0/1/2/3) calls above them -- and each run of
 * back-to-back calls in one basic block takes consecutive keys.
 *
 * The keys form one contiguous family, which is what cross-checks the two
 * non-literal sites: RefreshTeamSlotHighlights passes `iVar3 + 0x64` under a
 * `while (iVar3 < 0xe)` loop, i.e. 0x64..0x71, then 0x72 at its next site;
 * and State09_ReadyRoom_OnCommand passes param_4 from inside
 * `if (param_4 < 100) return 0; if (param_4 < 0x72)`, i.e. the same
 * 0x64..0x71 band.
 */
#include "ghidra_types.h"


undefined4 __fastcall SetWidgetReadyState(undefined4 param_1,uint param_2,int param_3,int regEax,uint regEdi)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint unaff_EDI = regEdi;
  
  iVar2 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        /* Ghidra emitted a bare `return;` in a value-returning function;
         * MSVC falls through with whatever's in EAX, gcc 14 rejects it
         * (-Wreturn-mismatch). This path's result is unused by callers -
         * return 0 to satisfy both toolchains without inventing a value. */
        return 0;
      }
    }
    piVar3 = *(int **)(iVar2 + 0x10);
    uVar1 = piVar3[2];
    if (uVar1 <= unaff_EDI) {
      while (uVar1 != unaff_EDI) {
        piVar3 = (int *)piVar3[4];
        uVar1 = piVar3[2];
        if (unaff_EDI < uVar1) {
          /* Ghidra emitted a bare `return;` in a value-returning function;
           * MSVC falls through with whatever's in EAX, gcc 14 rejects it
           * (-Wreturn-mismatch). This path's result is unused by callers -
           * return 0 to satisfy both toolchains without inventing a value. */
          return 0;
        }
      }
      *(undefined1 *)(piVar3 + 0x13) = 0;
      /* LOW BYTE ONLY (2026-08-27): 0x4063b7 is `mov al,byte ptr [esp+8]`
         followed by `test al,al`, so the original tests only param_3's low
         byte.  Comparing the full int diverges for any value whose low byte
         is zero but which is itself non-zero; no current caller passes one,
         but the cast costs nothing and removes the trap. */
      if ((char)param_3 == '\0') {
        if (piVar3[9] != 3) {
          (**(code **)(*piVar3 + 4))(s_ready_00551e80);
          /* Ghidra emitted a bare `return;` in a value-returning function;
           * MSVC falls through with whatever's in EAX, gcc 14 rejects it
           * (-Wreturn-mismatch). This path's result is unused by callers -
           * return 0 to satisfy both toolchains without inventing a value. */
          return 0;
        }
      }
      else if (piVar3[9] != 3) {
        (**(code **)(*piVar3 + 4))(s_active_00551e58);
        *(undefined1 *)(piVar3 + 0x13) = 1;
      }
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

