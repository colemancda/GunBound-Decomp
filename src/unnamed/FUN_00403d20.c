/* FUN_00403d20 - 0x00403d20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CONVENTION CONFIRMED, AND RE-SLOTTED (2026-08-28).  This is __thiscall on
 * a pointer 8 bytes into the owner object, exactly like the twins
 * FUN_00403ae0 and FUN_00404330 that Ghidra typed correctly: `mov ebp,ecx`
 * at 0x403d2e reads ECX before 0x403d30 reloads ECX from g_clientContext,
 * and EBP is then used only as an object base -- `lea eax,[ebp-8]` at
 * 0x403d46, `lea ebx,[ebp+0x1bdc]` at 0x403d78, `lea ebx,[ebp-8]` at
 * 0x403df1.  It is a `this`, not a frame pointer.  ECX becomes param_1.
 * The binary settles it independently: this function's only xref is a
 * VTABLE SLOT at 0x00551cd4, in the same table that holds FUN_00403ae0 at
 * 0x00551ccc and FUN_00404330 at 0x00551ce8 -- the two twins.  It is a
 * virtual member function, reached by dispatch.
 *
 * `ret 0xc` at 0x403d58 and 0x403e04 says THREE stack arguments where the
 * port declared two, so this is a RE-SLOT, not an append.  Prologue depth is
 * 0x44 (`sub esp,0x38` plus three pushes), and both epilogues balance there
 * only because FUN_00426090 (`ret 4`), FUN_00404b00 (`ret 4`) and
 * FUN_004026a0 (`ret 0xc`) each clean their own pushes.  At that depth
 * `mov edi,[esp+0x48]` (0x403d26) is entry+4 = param_2, the 0x10-byte name
 * string.  `mov esi,[esp+0x4c]` (0x403d42, depth 0x44) and
 * `mov eax,[esp+0x50]` (0x403de5, depth 0x48 -- the `push ebx` save at
 * 0x403d72 is still pending) are the SAME slot, entry+8 = param_3, the
 * message pointer: UpdateBuddyStatus's ESI on one path, FUN_004026a0's second
 * argument on the other.  param_4 at entry+0xc is demanded by `ret 0xc` but
 * no instruction in the body reads it; it is declared to keep the list
 * honest and is deliberately unused.
 *
 * UpdateBuddyStatus takes all three of its arguments in registers here -- EAX =
 * param_1 - 8 (the owner base, `lea eax,[ebp-8]` 0x403d46), ECX = local_20
 * (`lea ecx,[esp+0x24]` 0x403d49) and ESI = param_3 -- and is still declared
 * with no parameters, so that call stays argless.  The sibling dispatcher
 * sets up the same register roles at 0x403606-0x40360d, where ESI is the
 * packet payload at packet+8 rather than a stack parameter.
 *
 * The re-slot cannot break a PORTED caller: there are none
 * (tools/count_call_args.py reports 0), and tools/callsite_regs.py finds no
 * direct call to 0x403d20 in the binary either -- its lone PROGRESS.csv
 * xref is the 0x00551cd4 vtable slot above.  The virtual callers that reach
 * it through that slot are all in unported code, and since `__thiscall`
 * erases to nothing under MSVC (include/ghidra_types.h) param_1 compiles as
 * a first STACK argument here, so a future porter of them must not assume
 * the positions mirror the original.  FUN_00426090's own dropped EAX
 * (`mov eax,edi` at 0x403d37) is a separate item.
 */
#include "ghidra_types.h"


void __thiscall FUN_00403d20(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  undefined1 local_38;
  char local_37 [23];
  undefined1 local_20 [32];
  
  cVar3 = FUN_00426090(local_20);
  if (cVar3 == '\x01') {
    UpdateBuddyStatus(param_1 + -8,(char *)local_20,(undefined1 *)param_3);
    return;
  }
  local_38 = 0x69;
  pcVar4 = param_2;
  do {
    cVar3 = *pcVar4;
    pcVar4[(int)(local_37 + -(int)param_2)] = cVar3;
    pcVar4 = pcVar4 + 1;
  } while (cVar3 != '\0');
  iVar5 = FUN_00404b00(&local_38,(int *)(param_1 + 0x1bdc));
  iVar2 = g_connectionContextA;
  if (iVar5 == 0) {
    *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x1022;
    *(undefined2 *)(iVar2 + 0x4d6) = 1;
    iVar5 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar5 + 2;
    puVar1 = (undefined4 *)(iVar5 + 0x4d2 + iVar2);
    *puVar1 = *(undefined4 *)param_2;
    puVar1[1] = *(undefined4 *)(param_2 + 4);
    puVar1[2] = *(undefined4 *)(param_2 + 8);
    puVar1[3] = *(undefined4 *)(param_2 + 0xc);
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 0x10;
    SendOutgoingPacket(iVar2);
  }
/* DROPPED-REG FIX 2026-08-28: FUN_004026a0's EAX/EBX/CL - see its header's site map. */
  FUN_004026a0(0x1001,param_3,0x18,param_2,param_1 + -8,'\0');
  return;
}

