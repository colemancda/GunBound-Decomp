/* FUN_004fd650 - 0x004fd650 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x5575e4 = SLOT 7 of the CommP2P owner vtable
 * 0x5575c8 (value 0x4fd650, read from the original .data). Extent 0x4fd650-0x4fd67a (42 bytes; `ret 4` at
 * 0x4fd677, then int3 padding).
 *
 * __thiscall, one stack word: `mov eax,ecx` at 0x4fd650 (EAX = this),
 * `mov ebx,[esp+8]` at 0x4fd662 at depth 4 (push ebx) = entry+4 = the
 * argument, `ret 4`. Body: if the session flag this+0x1a70 is clear,
 * return 0; otherwise relay a type-0xc053 message with no payload -
 * `mov edi,0xc053` (0x4fd66b), `push 0 / push 0` (the payload pointer and
 * length), EAX = this, EBX = the argument - through FUN_004fcf10. One of
 * the unported sites its header lists ("0x4fd670 mov edi,0xc053 at
 * 0x4fd66b in the fn 0x4fd650"). The returned AL is not proven (the
 * port of FUN_004fcf10 returns a constant 0), so it is passed through as
 * the callee gives it. Left unnamed. Erased __thiscall: `this` first.
 */
#include "ghidra_types.h"


char FUN_004fd650(int param_1,undefined4 param_2)

{
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  return (char)FUN_004fcf10(0,0,0xc053,(int *)param_1,param_2);
}
