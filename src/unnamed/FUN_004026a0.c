/* FUN_004026a0 - 0x004026a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS RECOVERED (2026-08-28).  There are THREE, not the two
 * the backlog tracked, and one of them takes a dropped STORE with it:
 *
 *   EAX  the message string this strcpy's into the record.
 *   EBX  an object holding the record's sequence counter at +0x1be0, which
 *        the body reads and post-increments, and whose +0x1be4 is the tree
 *        RBTree_Insert inserts into.
 *   ECX  a boolean, and its use was missing from the port entirely.  `test
 *        cl,cl` at 0x4026ac is the first instruction after the prologue, and
 *        0x4026ae-0x4026b9 (`sete cl / dec cl / and cl,5 / add cl,0x69 /
 *        mov [esp],cl`) writes 'n' (0x6e) when it is set and 'i' (0x69) when
 *        it is clear into the byte just BELOW the string buffer.  Ghidra
 *        dropped both the register and the store, so the record's type
 *        character was never written at all.
 *
 * The record is contiguous and Ghidra's own naming proves where it starts.
 * `mov byte ptr [esp],cl` at 0x4026b9 writes the aligned frame base A, and
 * `lea ecx,[esp+5]` at 0x4026bd - with only `push esi` pending, not `push
 * edi` - is A+1, the string.  Ghidra models the `and esp,0xfffffff8` as -8
 * here, which is confirmed by `mov [esp+0x28],eax` at 0x4026dd landing on
 * its own local_108: that puts A at ebp-0x128 and the string at ebp-0x127,
 * exactly where Ghidra put local_127.  So the char is the byte Ghidra never
 * declared, and `char local_127[31]` becomes a 32-byte `local_128` with the
 * type char at [0] and the string copied to +1 - the same stack-side struct
 * coalescing this tree already applies to split contexts, and an exact fit
 * against the next declared local.
 *
 * The twin FUN_00404410 settles it beyond doubt: Ghidra modelled that copy
 * of this code completely, and it reads `local_120 = 0x69;` followed by a
 * strcpy into `local_11f` and an insert into `param_1 + 0x1be4` - the same
 * type char, the same +1 string, the same tree.
 *
 * SITE MAP.  Only 9 of the 14 binary call sites have a source counterpart:
 * 0x4039a0, 0x403d03, 0x403f16, 0x404125 and 0x404278 all fall in GAPS
 * between PROGRESS.csv entries, i.e. in code that is not ported.  Each of the
 * 9 lives in a different file and is pinned unambiguously by its own param_1
 * constant, so no site pairing was needed.  Resolved:
 *
 *   FUN_00402720  0x4028e9  eax=param_2  ebx=param_1      cl=1
 *   FUN_00402900  0x402ab6  eax=param_2  ebx=param_1      cl=1
 *   FUN_00402ad0  0x402cda  eax=regEax   ebx=param_1      cl=1
 *   FUN_00402cf0  0x402e49  eax=regEdi   ebx=param_1      cl=1
 *   FUN_00402e60  0x402fd5  eax=regEax   ebx=param_1      cl=1
 *   FUN_00403ae0  0x403bee  eax=param_2  ebx=param_1 - 8  cl=0
 *   FUN_00403d20  0x403df8  eax=param_2  ebx=param_1 - 8  cl=0
 *   FUN_00404330  0x404401  eax=param_2  ebx=param_1 - 8  cl=0
 *   FUN_00404700  0x40487b  eax=regEdi   ebx=param_1      cl=1
 *
 * (The three `param_1 - 8` callers are __thiscall and do `mov ebp,ecx` then
 * `lea ebx,[ebp-8]`; EBP is their `this`, not a frame pointer.)
 *
 * The last two rows were the blockers, and both were settled in the same
 * pass: FUN_00404700's EAX is that function's own live-in EDI, now its
 * declared regEdi, and FUN_00403d20 is __thiscall - confirmed not by
 * analogy but by the vtable at 0x00551ccc, which holds it at 0x00551cd4
 * between its two already-__thiscall twins FUN_00403ae0 and FUN_00404330.
 * Its `ret 0xc` also forced a re-slot there, so the name shift is real: what
 * that file now calls param_2 is the value this site passes in EAX.
 *
 * Its own frame is ebp-relative after `and esp,0xfffffff8`: [ebp+8], [ebp+0xc]
 * and [ebp+0x10] are param_1, param_2 and param_3 (0x4026d4-0x4026da).
 */
#include "ghidra_types.h"


void FUN_004026a0(undefined4 param_1,undefined4 *param_2,uint param_3,char *regEax,
                  int regEbx,char regCl)

{
  char cVar1;
  int iVar2;
  char *in_EAX = regEax;
  uint uVar3;
  int unaff_EBX = regEbx;
  undefined4 *puVar4;
  /* RECOVERED 2026-08-28: was `char local_127 [31]`. [0] is the record's
     type character, which Ghidra dropped along with the ECX it comes from;
     the string starts at [1]. Exact fit against local_108 above. */
  char local_128 [32];
  int local_108;
  undefined4 local_104;
  undefined4 local_100 [63];
  
  /* RECOVERED 2026-08-28, orig 0x4026ae-0x4026b9. */
  local_128[0] = (regCl == '\0') ? 'i' : 'n';
  iVar2 = -(int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[(int)(local_128 + 1 + iVar2)] = cVar1;
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
  /* RECOVERED 2026-08-28, orig 0x402703-0x40270d: EAX is the char+string
     record at the aligned frame base, EDI the tree at regEbx + 0x1be4. */
  RBTree_Insert(&local_108,local_128,(int *)(unaff_EBX + 0x1be4));
  return;
}

