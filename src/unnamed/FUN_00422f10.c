/* FUN_00422f10 - 0x00422f10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED AND THE DROPPED REGISTER RECOVERED.  `ret 4` gives one
 * stack argument, so param_1 arrives in ECX and param_2 is the push; ESI is a
 * third input Ghidra left as a local.  All four call sites agree:
 *
 *   ecx = [ctx + 0x3f804]   -> param_1
 *   push [ctx + 0x44e60]    -> param_2   (via EDX at three sites, EAX at one)
 *   esi = [0x5b3484]        -> regEsi = g_clientContext
 *
 * The port had been passing *(g_clientContext + 0x44e60) as param_1.  That is
 * the right value in the wrong slot -- it belongs in param_2 -- so the two
 * fields were being written swapped, with param_2 taking whatever was in the
 * caller's stack.
 *
 * The body appends to three parallel arrays based at regEsi (+0x5f2f58,
 * +0x5f3058, +0x5f3158) with the count at +0x5f3258 and a hard cap of 0x40,
 * stamping GetTickCount()/1000 + 300 -- a five-minute expiry.
 */
#include "ghidra_types.h"


void __thiscall FUN_00422f10(undefined4 param_1,undefined4 param_2,int regEsi)

{
  DWORD DVar1;
  
  if (*(int *)(&DAT_005f3258 + regEsi) < 0x40) {
    *(undefined4 *)(&DAT_005f2f58 + *(int *)(&DAT_005f3258 + regEsi) * 4 + regEsi) = param_1;
    *(undefined4 *)(&DAT_005f3058 + *(int *)(&DAT_005f3258 + regEsi) * 4 + regEsi) = param_2;
    DVar1 = GetTickCount();
    *(uint *)(&DAT_005f3158 + *(int *)(&DAT_005f3258 + regEsi) * 4 + regEsi) =
         DVar1 / 1000 + 300;
    *(int *)(&DAT_005f3258 + regEsi) = *(int *)(&DAT_005f3258 + regEsi) + 1;
  }
  return;
}

