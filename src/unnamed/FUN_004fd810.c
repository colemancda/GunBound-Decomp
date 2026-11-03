/* FUN_004fd810 - 0x004fd810 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x5575f0 = SLOT 10 of the CommP2P owner vtable 0x5575c8
 * (read from the original .data); the listener call
 * `call [edx+0x28]` in DeleteBuddyByNickname (0x28 = 10 * 4) reaches it.
 * Extent 0x4fd810-0x4fd87d (112 bytes; both exits `ret 4`).
 *
 * __thiscall, one stack word (`ret 4` at 0x4fd826 and 0x4fd87d): `mov
 * esi,ecx` (0x4fd814) = this; `mov ebp,[esp+0x20]` (0x4fd82b, depth 0x1c =
 * sub 0x10 + three pushes, so entry+4) is the 16-byte buddy id.
 * Body: if this+0x1a70 is clear return 0; strncpy the id into a 16-byte
 * local (the call at 0x4fd837 is the CRT 0x527360 = _strncpy, count
 * 0x10); send it with FUN_00502500 (ECX = 0x10 length, EDX = the local,
 * push 0x3002 opcode, EBX = this, exactly as FUN_004fd960's 0x3006 and
 * FUN_004fda50's 0x3010); if that fails return 0, else relay message type
 * 0xc043 with no payload - `mov edi,0xc043` (0x4fd866), `push 0 / push 0`,
 * EAX = this, EBX = the id - through FUN_004fcf10 and return 1. Left
 * unnamed. Erased __thiscall: `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


char FUN_004fd810(int param_1,char *param_2)

{
  char cVar1;
  char local_10 [16];

  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  _strncpy(local_10,param_2,0x10);
  cVar1 = (char)FUN_00502500(0x10,(undefined4 *)local_10,0x3002,param_1);
  if (cVar1 == '\0') {
    return 0;
  }
  FUN_004fcf10(0,0,0xc043,(int *)param_1,(undefined4)param_2);
  return 1;
}
