/* FUN_004f1770 - 0x004f1770 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Recovered the single dropped register argument on 2026-08-28: ESI is the
 * object pointer.
 *
 * The whole callee is 26 bytes at 0x4f1770. ESI is read before it is ever
 * written - the entry `push esi` at 0x4f1770 is a read, and 0x4f1771 `mov
 * dword ptr [esi],0x557534` stamps the class vtable through it - and ESI is
 * never written anywhere in the body, so it is a genuine argument. ECX and
 * EAX are phantoms: ECX's first touch is the write at 0x4f177c `mov
 * ecx,[esi+4]`, EAX's is the write at 0x4f1783 `mov eax,[ecx]`, and the EAX
 * returned by the 0x4f1777 call is dead. EDX, EBX, EDI and EBP are never
 * referenced.
 *
 * The entry `push esi` is NOT a prologue save. It is the pending push that
 * supplies the one stack argument of FUN_004f3060, which is `push ebp; mov
 * ebp,[esp+8]; ...; ret 4`. Two independent confirmations: that ret 4 proves
 * exactly one dword argument and the entry push is the only push on the path
 * to the call; and there is no pop esi or add esp,4 before the bare ret at
 * 0x4f1789, so the stack only balances if the callee popped it. Compare the
 * sibling constructor FUN_004f1750 at 0x4f1750, which has the genuine save
 * shape push esi ... pop esi; ret. Ghidra already rendered the push
 * correctly as FUN_004f3060(unaff_ESI), so there are no push-as-stack-store
 * fabrications to delete here.
 *
 * The callee declares no parameters and the binary passes no stack
 * arguments, so this is a clean append rather than a re-slot: nothing in the
 * existing list moves.
 *
 * Three ported call sites, matching the three binary CALL sites exactly.
 * FUN_004f3960 at 0x4f3963 passes ECX, which is the this pointer of that
 * thiscall scalar deleting destructor. FUN_005438f0 at 0x5438f6 passes the
 * literal 0xea0e18, which is g_spriteRegistry; 0x5425a0 constructs the same
 * address with mov eax,0xea0e18; call 0x4f1750 and then registers 0x5438f0
 * with atexit at 0x5253ad, so the two are a constructor and destructor pair.
 * FUN_00543960 at 0x543966 passes the literal 0xeb168c, which is
 * DAT_00eb168c; 0x5429d0 constructs it with mov eax,0xeb168c; call 0x4f3940
 * and registers 0x543960 with the same atexit, and that constructor is
 * already ported as FUN_004f3940((undefined4 *)&DAT_00eb168c).
 *
 * A full image scan also found three jmp 0x4f1770 at 0x537769, 0x53b681 and
 * 0x53bd91. All three are MSVC exception-unwind funclets in the tail of
 * .text, each of the form mov esi,[ebp+4]; add esi,<member offset>; jmp
 * 0x4f1770, for member subobjects at +0x85c (see FUN_004e38f0) and at
 * DAT_006a7f88 plus an index (see FUN_00418dc0). They are compiler-generated
 * cleanup code with no corresponding source statement, so they are correctly
 * absent from the source call count, and each one sets ESI and only ESI
 * before jumping - three further confirmations of the argument register.
 * Nothing in the image holds 0x4f1770 as data, so the function is in no
 * vtable and has no indirect callers.
 */
#include "ghidra_types.h"


void FUN_004f1770(undefined4 *regEsi)

{
  undefined4 *unaff_ESI = regEsi;
  
  *unaff_ESI = &PTR_FUN_00557534;
  FUN_004f3060(unaff_ESI);
  if ((undefined4 *)unaff_ESI[1] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)unaff_ESI[1])(1);
  }
  return;
}

