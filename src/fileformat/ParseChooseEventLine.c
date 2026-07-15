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
      cVar1 = FUN_00500c00(param_1,param_1[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = FUN_00409d10(param_1,param_2,local_c);
  }
  *(undefined4 *)(iVar2 + 4) = param_3;
  return;
}

