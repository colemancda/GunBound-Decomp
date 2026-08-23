/* FUN_004d34f0 - 0x004d34f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED AND EAX RECOVERED.  `ret 4` gives one stack argument,
 * so param_1 is ECX -- a PHANTOM, written by `mov ecx,edx` before any read --
 * param_2 is EDX and param_3 is the push.  Both call sites agree:
 *
 *   0x00410685  mov eax,[0x7934e8] / mov edx,esi / push edx / mov edx,0x10
 *   0x004106cd  lea eax,[esp+0x44] / push eax / mov eax,[0x7934e8] / mov edx,0x10
 *
 * The two push DIFFERENT registers for the same value: ESI at the first site
 * was loaded `lea esi,[esp+0x44]` at 0x00410642, the very stack local the
 * second site takes the address of inline.  So param_3 is &local_d44 at both,
 * which is the value the port was already passing -- in param_1's slot.
 *
 * Reading EDX at the CALL rather than at the PUSH makes the first site look
 * as though it passes 0x10 as the buffer pointer, because EDX is reloaded
 * with the length in between.  A pointer of value sixteen is the kind of
 * wrong answer that looks like an answer.
 *
 * The body copies param_2 bytes from param_3 to regEax + 0x44da +
 * *(regEax + 0x84d8) -- an append at a stored write offset -- so regEax is
 * the destination buffer object, and it was uninitialised.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004d34f0(undefined4 param_1,uint param_2,undefined4 *param_3,
                                   int regEax)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(regEax + 0x44da + *(int *)(regEax + 0x84d8));
  for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *param_3;
    param_3 = param_3 + 1;
    puVar2 = puVar2 + 1;
  }
  for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar2 = *(undefined1 *)param_3;
    param_3 = (undefined4 *)((int)param_3 + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  *(uint *)(regEax + 0x84d8) = *(int *)(regEax + 0x84d8) + param_2;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

