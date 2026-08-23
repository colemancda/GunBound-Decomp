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
 * EDI remains open: it is the widget key, and it genuinely varies (7 distinct
 * values across the 13 sites), so it needs a per-site witness rather than
 * this treatment.
 */
#include "ghidra_types.h"


undefined4 __fastcall SetWidgetReadyState(undefined4 param_1,uint param_2,int param_3,int regEax)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint unaff_EDI;
  
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
      if (param_3 == '\0') {
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

