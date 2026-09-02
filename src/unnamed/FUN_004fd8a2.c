/* FUN_004fd8a2 - 0x004fd8a2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * PHANTOM TWIN of FUN_004fd880 (2026-09-01).  0x4fd8a2 is only the post-guard
 * TAIL of the function at 0x4fd880; Ghidra decompiled it a second time as a
 * standalone routine.  It has zero callers (tools/count_call_args reports 0)
 * and shares the single FUN_00502500 call at 0x4fd945 with FUN_004fd880.c,
 * which is the real, complete model - fix them together.  The frame is
 * [count:u16][names][final 0x14 record]: EDX = frame base (&uStack00000004),
 * ECX = (cursor - frame base) + 0x14.  EBX = the `this`/session, stored from
 * ECX at the original 0x4fd892 `mov [esp],ecx` and reloaded for EBX at
 * 0x4fd92e `mov ebx,[esp+0x1c]`; this split-tail model cannot see ECX, so the
 * session is recovered below as the stack slot at the original frame origin
 * ([esp+0], 4 bytes below the count word).
 */
#include "ghidra_types.h"


void FUN_004fd8a2(void)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0x00000006;
  int iVar1;
  int iVar2;
  char *_Dest;
  uint uVar3;
  undefined2 uStack00000004;
  /* Recovered: the session `this` at the original frame origin [esp+0]; see
   * the header - invisible to this split-tail, real model is FUN_004fd880.c. */
  int in_stack_00000000;
  int in_stack_00001778;
  char *in_stack_0000177c;

  uStack00000004 = 0;
  if (*(int *)(in_stack_00001778 + 4) != 0) {
    uStack00000004 =
         (undefined2)((*(int *)(in_stack_00001778 + 8) - *(int *)(in_stack_00001778 + 4)) / 0x12);
  }
  _Dest = &stack0x00000006;
  iVar2 = 0;
  for (uVar3 = 0;
      (iVar1 = *(int *)(in_stack_00001778 + 4), iVar1 != 0 &&
      (uVar3 < (uint)((*(int *)(in_stack_00001778 + 8) - iVar1) / 0x12))); uVar3 = uVar3 + 1) {
    _strncpy(_Dest,(char *)(iVar2 + iVar1),0x10);
    _Dest = _Dest + 0x10;
    iVar2 = iVar2 + 0x12;
  }
  _strncpy(_Dest,in_stack_0000177c,0x14);
  /* opcode -> stack param, ECX = payload length, EDX = frame base
   * (&uStack00000004, the count word), EBX = session. */
  FUN_00502500((int)(_Dest + 0x14 - (char *)&uStack00000004),(undefined4 *)&uStack00000004,0x3004,
               in_stack_00000000);
  return;
}

