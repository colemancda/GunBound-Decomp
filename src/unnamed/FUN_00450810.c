/* FUN_00450810 - 0x00450810 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): the slot-2 dispatch passes `this`, as in its sibling
 * TickActiveObjectLayers (0x4507d0). This is the same walk restricted to
 * layer keys 100001..189999 (`cmp eax,0x186a1 / jb` at 0x450823, `cmp
 * eax,0x2e630 / jae` at 0x45082a), and 0x450840-0x450844 is `mov eax,[esi]
 * / mov ecx,esi / call [eax+8]` with nothing pushed. The port dropped the
 * object; it now calls through ActiveObjectTickFn, __fastcall(this), the
 * form every carved slot-2 target of these classes uses.
 */
#include "ghidra_types.h"

/* Slot 2 is the object's 0-argument per-frame tick, a __thiscall in the
 * original (`mov ecx,esi / call [eax+8]`). Every carved slot-2 target of
 * the battle entity classes is ported __fastcall(this) (AnimateProjectileTick,
 * SimulateMobileFrame, TickJewelFrame, ...) or is a genuine C++ virtual
 * (CRiderEffect::Tick, CFlameEffect::Tick), and __fastcall(this) is
 * ABI-identical to __thiscall for a method with no stack arguments - the
 * same form TickActiveObjectRegistry uses for the widget registry. */
typedef void (__fastcall *ActiveObjectTickFn)(void *thisPtr);


void FUN_00450810(int regEbx)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(regEbx + 4) + 0x1c);
  if (iVar3 != *(int *)(regEbx + 4)) {
    do {
      if (100000 < *(uint *)(iVar3 + 4)) {
        if (189999 < *(uint *)(iVar3 + 4)) {
          return;
        }
        piVar2 = *(int **)(iVar3 + 0x10);
        cVar1 = *(char *)((int)piVar2 + 0x15);
        while (cVar1 == '\0') {
          (*(ActiveObjectTickFn *)(*piVar2 + 8))(piVar2);
          piVar2 = (int *)piVar2[4];
          cVar1 = *(char *)((int)piVar2 + 0x15);
        }
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
    } while (iVar3 != *(int *)(regEbx + 4));
  }
  return;
}

