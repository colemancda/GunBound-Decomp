/* AppendBroadcastString - 0x004e6db0 in the original binary.
 *
 * Appends param_2 bytes from param_3 to the broadcast/turn-event
 * accumulation buffer at context+0x44dec, bumping the write cursor at
 * context+0x44fec. Two rep-movs (dwords then trailing bytes).
 *
 * RECOVERED (2026-07-19), verified with angr/capstone against the
 * original: the context base arrives in EAX. It is read before any
 * write - the third and fourth instructions of the function are
 *   0x4e6dbe  mov edi, dword ptr [eax + 0x44fec]     ; write cursor
 *   0x4e6dc4  lea edi, [edi + eax + 0x44dec]         ; destination
 * and the tail re-reads/updates it at 0x4e6ddc/0x4e6de6. Ghidra
 * emitted this as an uninitialised `in_EAX`, so the port copied into a
 * garbage pointer. Promoted to the trailing `context` parameter (the
 * repo's established idiom - see src/network/AllocCipherSchedule.c).
 *
 * All 6 call sites in the original pass the SAME global, 0xe55ce0 -
 * i.e. &g_replayContext (see src/globals_sized.c; the former 1-byte
 * DAT_00e55ce0):
 *   0x43e805: mov eax, 0xe55ce0    -> call at 0x43e80a
 *   0x47a920: mov eax, 0xe55ce0    -> call at 0x47a925
 *   0x4b9e23: mov eax, 0xe55ce0    -> call at 0x4b9e28
 *   0x4d3acc: mov eax, 0xe55ce0    -> call at 0x4d3ad1
 *   0x4d3b1f: mov eax, 0xe55ce0    -> call at 0x4d3b24
 *   0x4d67c6: mov eax, 0xe55ce0    -> call at 0x4d67cb
 * This is consistent with FUN_004e77e0/FUN_004e7b60/etc., which take
 * &g_replayContext as their own context argument and dereference the
 * same +0x44dec/+0x44fec fields.
 */
#include "ghidra_types.h"
#include "globals.h"
#include <windows.h>


void __fastcall AppendBroadcastString(undefined4 param_1,uint param_2,undefined4 *param_3,
                                     int context)

{
  int in_EAX;
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;

  in_EAX = context;
  uVar1 = ((int)param_2 < 0) - 1 & param_2;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x44fec) + 0x44dec + in_EAX);
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
  *(uint *)(in_EAX + 0x44fec) = *(int *)(in_EAX + 0x44fec) + param_2;
  return;
}

