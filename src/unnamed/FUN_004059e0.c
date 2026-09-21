/* FUN_004059e0 - 0x004059e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARG / EAX-FIRST FIX (2026-09-21). Disasm 0x4059e0-0x405a1a:
 * `ret 4` = 1 real stack argument, but the body ALSO reads a genuine
 * incoming EAX (Ghidra's `in_EAX`, never assigned by the callee before
 * use) - the base pointer whose `+0x2000` slot is both the write cursor
 * and the running length this function advances. ECX (the erstwhile
 * `param_1`) is pure scratch (`xor ecx,ecx; ...; dec ecx; and ecx,edx`) -
 * never a real incoming value - so it stays a phantom dummy, same idiom
 * as the __fastcall+dummy sites elsewhere in this tree. EDX (`param_2`,
 * the byte count) and the stack arg (`param_3`, the source buffer) were
 * already correctly declared. Only the base pointer was missing from the
 * signature entirely; promoted `in_EAX` to a real trailing parameter
 * (`param_4`, matching the EAX-first idiom used for InitTextBoxWidget /
 * BlitSpriteAttached in 6e574c4a). Both call sites (in
 * DispatchDirectLinkPacket.c) were passing only `param_3`, leaving
 * param_2 (length) and the base pointer wholly undefined - fixed to pass
 * the connection buffer `iVar4` as the base and the caller's own
 * null-terminator scan length (`pcVar6 - (char *)(param_1 + 8)`, which
 * includes the trailing NUL since the scan loop advances one past it) as
 * the length.
 */
#include "ghidra_types.h"


void __fastcall FUN_004059e0(undefined4 param_1,uint param_2,undefined4 *param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;

  uVar1 = ((int)param_2 < 0) - 1 & param_2;
  puVar3 = (undefined4 *)(*(int *)(param_4 + 0x2000) + param_4);
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = *param_3;
    param_3 = param_3 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar3 = *(undefined1 *)param_3;
    param_3 = (undefined4 *)((int)param_3 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  *(uint *)(param_4 + 0x2000) = *(int *)(param_4 + 0x2000) + param_2;
  return;
}

