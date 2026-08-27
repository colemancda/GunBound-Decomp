/* FUN_004e7d60 - 0x004e7d60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * param_1 IS NOT AN ARGUMENT.  Ghidra typed this __thiscall and so modelled
 * ECX as param_1, but ECX is never read here: the `push ecx` at 0x004e7d60 is
 * MSVC's stack-allocation idiom (a four-byte `sub esp,4` written as a push),
 * and the slot it reserves is an OUT parameter that FUN_004e8a70 fills:
 *
 *   0x004e7dad  lea  eax, [esp+0xc]      <- &local
 *   0x004e7db3  call 0x4e8a70            <- writes through it
 *   0x004e7db8  mov  eax, [esp+0xc]      <- reads it back
 *   0x004e7dbc  cmp  eax, [esi+0x45234]
 *
 * so it is a local, and it is declared as one here.  It stays uninitialised
 * because FUN_004e8a70's own arguments are still dropped -- that call is an
 * open item in its own right -- but an uninitialised local is at least
 * honestly labelled, where an uninitialised PARAMETER invites a caller to
 * fill it with something plausible and wrong.
 *
 * The real inputs are EAX and one stack argument.  `ret 4` agrees, and the
 * entry reads them both directly:
 *   0x004e7d61  cmp word ptr [esp+8], 0xffff   <- the stack argument
 *   0x004e7d69  mov esi, eax                   <- regEax
 *
 * EAX is &g_replayContext at both call sites.  The stack argument is the value
 * the port was already passing (0xffff, 0xc302) -- but it was landing in the
 * phantom param_1, so the `== -1` test at the top read whatever the caller
 * left on the stack.  ApplyBattleActionToContext passes 0xffff precisely to
 * take that branch, and it was firing at random.
 */
#include "ghidra_types.h"


void __thiscall FUN_004e7d60(int param_2,int regEax)

{
  int param_1; /* NOT an argument - see the header */
  
  if (param_2 == -1) {
    FUN_004e8ad0(*(undefined4 *)(*(int *)(regEax + 0x45234) + 4));
    *(int *)(*(int *)(regEax + 0x45234) + 4) = *(int *)(regEax + 0x45234);
    *(undefined4 *)(regEax + 0x45238) = 0;
    *(undefined4 *)*(undefined4 *)(regEax + 0x45234) = *(undefined4 *)(regEax + 0x45234);
    *(int *)(*(int *)(regEax + 0x45234) + 8) = *(int *)(regEax + 0x45234);
    return;
  }
  FUN_004e8a70(regEax + 0x45230,(undefined4 *)&param_1,(ushort *)&param_2);
  if (param_1 != *(int *)(regEax + 0x45234)) {
    FUN_004e87b0(regEax + 0x45230,&param_2,param_1);
  }
  return;
}

