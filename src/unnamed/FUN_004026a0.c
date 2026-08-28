/* FUN_004026a0 - 0x004026a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS IDENTIFIED, NOT YET APPLIED (2026-08-27).  There are
 * THREE, not the two the backlog tracks, and one of them takes a dropped
 * STORE with it:
 *
 *   EAX  the message string this strcpy's into the record.
 *   EBX  an object holding the record's sequence counter at +0x1be0, which
 *        the body reads and post-increments.
 *   ECX  a boolean, and its use is missing from the port entirely.  `test
 *        cl,cl` at 0x4026ac is the first instruction after the prologue, and
 *        0x4026ae-0x4026b9 (`sete cl / dec cl / and cl,5 / add cl,0x69 /
 *        mov [esp],cl`) writes 'n' when it is set and 'i' when it is clear
 *        into the byte just BELOW the string buffer.  Ghidra dropped both the
 *        register and the store, so the record's type character is never
 *        written at all.
 *
 * The record is contiguous: the char sits at frame A-0x120 and the string
 * starts at A-0x11f (`lea ecx,[esp+5]` at 0x4026bd, taken with only `push
 * esi` pending, not `push edi`).  Reproducing that faithfully means widening
 * `char local_127[31]` to a 32-byte array with the char at [0] and the string
 * copied to +1 -- the stack-side struct coalescing this tree already applies
 * to split contexts -- rather than adding a separate neighbouring local.
 *
 * SITE MAP.  Only 9 of the 14 binary call sites have a source counterpart:
 * 0x4039a0, 0x403d03, 0x403f16, 0x404125 and 0x404278 all fall in GAPS
 * between PROGRESS.csv entries, i.e. in code that is not ported.  Each of the
 * 9 lives in a different file and is pinned unambiguously by its own param_1
 * constant, so no site pairing is needed.  Resolved:
 *
 *   FUN_00402720  0x4028e9  eax=param_2  ebx=param_1      cl=1
 *   FUN_00402900  0x402ab6  eax=param_2  ebx=param_1      cl=1
 *   FUN_00402ad0  0x402cda  eax=regEax   ebx=param_1      cl=1
 *   FUN_00402cf0  0x402e49  eax=regEdi   ebx=param_1      cl=1
 *   FUN_00402e60  0x402fd5  eax=regEax   ebx=param_1      cl=1
 *   FUN_00403ae0  0x403bee  eax=param_2  ebx=param_1 - 8  cl=0
 *   FUN_00404330  0x404401  eax=param_2  ebx=param_1 - 8  cl=0
 *
 * (The two `param_1 - 8` callers are __thiscall and do `mov ebp,ecx` then
 * `lea ebx,[ebp-8]`; EBP is their `this`, not a frame pointer.)
 *
 * BLOCKED, which is why none of it is applied yet -- a real prototype would
 * turn the two unresolved sites into compile errors, and passing a plausible
 * wrong value at them is worse than passing nothing:
 *
 *   FUN_00403d20 0x403df8 - its EBX is (its own incoming ECX) - 8, and ECX is
 *     undeclared there.  Harmless to fix in itself, since the function has
 *     ZERO call sites in the ported tree; it is very likely __thiscall like
 *     its near-twin FUN_00404330, which Ghidra typed correctly.
 *   FUN_00404700 0x40487b - its EAX is that function's own undeclared live-in
 *     EDI.  Promoting it means fixing FUN_00404700's own three sites, and
 *     while two are easy (FUN_00402e60 passes its regEax; FUN_00403ae0 does
 *     `lea edi,[esp+0x2c]`), DispatchDirectLinkPacket's EDI is
 *     control-flow-dependent -- `mov edi,eax` at 0x4032d2 with later
 *     `lea edi,[ecx+1]` and `lea edi,[esi+8]` whose dominance over the call
 *     has to be settled first.
 *
 * Its own frame is ebp-relative after `and esp,0xfffffff8`: [ebp+8], [ebp+0xc]
 * and [ebp+0x10] are param_1, param_2 and param_3 (0x4026d4-0x4026da).
 */
#include "ghidra_types.h"


void FUN_004026a0(undefined4 param_1,undefined4 *param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  char *in_EAX;
  uint uVar3;
  int unaff_EBX;
  undefined4 *puVar4;
  char local_127 [31];
  int local_108;
  undefined4 local_104;
  undefined4 local_100 [63];
  
  iVar2 = -(int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[(int)(local_127 + iVar2)] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  local_108 = *(int *)(unaff_EBX + 0x1be0);
  *(int *)(unaff_EBX + 0x1be0) = local_108 + 1;
  local_104 = param_1;
  puVar4 = local_100;
  for (uVar3 = param_3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar4 = *param_2;
    param_2 = param_2 + 1;
    puVar4 = puVar4 + 1;
  }
  for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  FUN_004049a0(&local_108);
  return;
}

