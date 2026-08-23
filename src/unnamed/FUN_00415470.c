/* FUN_00415470 - 0x00415470 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS ANALYSED, NOT APPLIED.  `ret 0` puts nothing on the stack,
 * so param_1 (ECX) and param_2 (EDX) are registers, and EBX and EDI are two
 * more that Ghidra did not declare.  At the sole call site (0x004113c1):
 *
 *   ecx  PHANTOM   -- the entry writes it (`mov ecx,[edi]`) before any read
 *   edx  = esi, where esi = [esp + 0x10]     <- a caller stack local
 *   ebx  = 1
 *   edi  = <something> + 0x6a76f4            <- context-relative
 *
 * Blocked on param_2: its value lives in a caller spill slot, and naming a
 * spill needs a stack-depth model over the CFG that does not exist here (see
 * tools/guard_dominator_base.py, which resolves 0 of 49 such cases).
 *
 * NOT filled with the two known values alone: appending them puts EDI's value
 * in param_1 and EBX's in param_2, which is what an earlier pass on this
 * branch did before it was reverted.  Three of four arguments right is not
 * three quarters correct -- it is wrong, in a shape that looks recovered.
 */
#include "ghidra_types.h"


void __fastcall FUN_00415470(undefined4 param_1,int param_2)

{
  int iVar1;
  int unaff_EBX;
  int *unaff_EDI;
  
  if ((uint)unaff_EDI[1] < (uint)(param_2 + unaff_EBX)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (unaff_EDI[1] - param_2) - unaff_EBX;
  if (iVar1 != 0) {
    _memmove((void *)(*unaff_EDI + param_2 * 4),(void *)(*unaff_EDI + (param_2 + unaff_EBX) * 4),
             iVar1 * 4);
  }
  unaff_EDI[1] = unaff_EDI[1] - unaff_EBX;
  return;
}

