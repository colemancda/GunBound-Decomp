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
 *
 * EBX and EDI RECOVERED, CALL RE-SLOTTED (2026-08-26).  CArray::RemoveAt over
 * 4-byte elements: EDI is the array (data at +0, count at +4), param_2 the
 * index, EBX the number of elements to remove.  It bounds-checks
 * index + count against the count and throws E_INVALIDARG, memmoves the tail
 * down, then shrinks the count -- RemoveAt's shape exactly.
 *
 * The source passed NOTHING to a two-parameter __fastcall, so this is a
 * re-slot.  ECX is a phantom (`mov ecx,[edi]` at the entry, written before any
 * read), so param_1 takes 0.  At the single site EDX is `mov esi,[esp+0x10];
 * mov edx,esi` with no pushes pending, which under WriteReplayEventRecord's
 * -0xd88 frame is local_d78 -- the very counter the line AFTER the call
 * decrements (`local_d78 = local_d78 - 1`).  EBX is the immediate 1: one
 * element.  EDI is g_clientContext + 0x6a76f4.
 */
#include "ghidra_types.h"


void __fastcall FUN_00415470(undefined4 param_1,int param_2,int regEbx,int *regEdi)

{
  int iVar1;
  
  if ((uint)regEdi[1] < (uint)(param_2 + regEbx)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (regEdi[1] - param_2) - regEbx;
  if (iVar1 != 0) {
    _memmove((void *)(*regEdi + param_2 * 4),(void *)(*regEdi + (param_2 + regEbx) * 4),
             iVar1 * 4);
  }
  regEdi[1] = regEdi[1] - regEbx;
  return;
}

