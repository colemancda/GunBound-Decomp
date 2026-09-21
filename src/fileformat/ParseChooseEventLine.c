/* ParseChooseEventLine - 0x00409cb0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED ARGUMENTS: this function's sole caller
 * (fileformat/LoadChooseEventConfig.c) loads esi/eax/edi immediately
 * before the call at 0x409c35-0x409c3c - esi is LoadChooseEventConfig's
 * own first parameter (the event registry pointer), eax is the parsed
 * line buffer, and edi is LoadChooseEventConfig's open-XFS-handle local
 * (stored into the new entry's +4 field, matching the `*(iVar2+4) =
 * unaff_EDI` store below). Promoted to real parameters and the one call
 * site updated to match; see LoadChooseEventConfig.c's header comment
 * for how this was recovered.
 *
 * FIXED (2026-07-15): the FUN_00426780 hash-lookup call also dropped its
 * own 2 trailing args (table, key) - confirmed via angr that they are
 * this function's own param_1 (registry/table) and param_2 (line being
 * parsed, the lookup key), still live in EAX/EBX at the call (`mov
 * ebx,eax` at this function's own entry, never touched before `mov
 * eax,esi; call 0x426780`). See FUN_00426780.c's own header.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): the FUN_00409d10(param_1,param_2,
 * local_c) call was missing FUN_00409d10's own leading `this` (ECX) stack
 * arg. Orig 0x409cef-0x409cfa: `mov ecx,[esp+4]` (=local_c's VALUE) `push
 * ecx` (deepest push -> callee's LAST stack param), `mov ecx,[esp+0xc]`
 * (=the bucket-index int that FUN_00426780 wrote into `local_8`, i.e.
 * `*(int *)local_8`) `push ebx` (=this function's own param_2) `push esi`
 * (=this function's own param_1, closest push -> callee's FIRST stack
 * param) then `call 0x409d10` with ECX still holding the local_8 value -
 * FUN_00409d10 is `__thiscall`, so that local_8 value is the real ECX=
 * `this`/param_1, never pushed at all in the buggy call. The 3 args that
 * were already there land in the right positions once it's prepended
 * (param_1->callee param_2, param_2->callee param_3, local_c->callee
 * param_4), matching FUN_00409d10's own body: param_1(this) indexes a
 * bucket array, param_2 is the `int *` registry, param_3 feeds
 * ConstructStringFromText, param_4 is stored at the new node's +0xc.
 */
#include "ghidra_types.h"
#include <windows.h>


void ParseChooseEventLine(int *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];

  iVar2 = (int)FUN_00426780(local_8,&local_c,local_4,param_1,(uchar *)param_2);
  if (iVar2 == 0) {
    if (*param_1 == 0) {
      cVar1 = HashMap_InitHashTable(param_1,param_1[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = FUN_00409d10(*(int *)local_8,param_1,param_2,local_c);
  }
  *(undefined4 *)(iVar2 + 4) = param_3;
  return;
}

