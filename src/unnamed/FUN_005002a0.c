/* FUN_005002a0 - 0x005002a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX, ESI and EDI RECOVERED (2026-08-25).  This is the second copy of the
 * chained hash-map FIND (the first is FUN_004ff130's family), and like it the
 * function returns more than it appears to: EDI is the key, ESI the address
 * of the caller's bucket-index slot, EAX the address of the slot the key is
 * stashed in, and the single pushed argument the predecessor node.
 *
 * The EAX slot is the subtle one.  At the two wrapper call sites the original
 * points it at the caller's OWN incoming parameter slot -- dead by then,
 * because the parameter has been cached in EBP -- and so the key overwrites
 * it.  A C port cannot spell that as &param_1 without corrupting param_1,
 * which the original keeps live in the register, so each wrapper declares a
 * local for it instead and the note there says so.
 */
#include "ghidra_types.h"


uint * __thiscall FUN_005002a0(int *param_1,undefined4 *param_2,uint *regEax,uint *regEsi,
                              uint regEdi)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  
  *regEax = regEdi;
  *regEsi = regEdi % (uint)param_1[2];
  if (*param_1 != 0) {
    *param_2 = 0;
    puVar1 = *(uint **)(*param_1 + *regEsi * 4);
    if (puVar1 != (uint *)0x0) {
      puVar3 = (uint *)0x0;
      do {
        puVar2 = puVar1;
        if ((puVar2[0x5d9] == *regEax) && (*puVar2 == regEdi)) {
          *param_2 = puVar3;
          return puVar2;
        }
        puVar1 = (uint *)puVar2[0x5d8];
        puVar3 = puVar2;
      } while ((uint *)puVar2[0x5d8] != (uint *)0x0);
    }
  }
  return (uint *)0x0;
}

