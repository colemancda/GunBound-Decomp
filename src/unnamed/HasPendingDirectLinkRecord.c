/* HasPendingDirectLinkRecord - 0x00403270 in the original binary.
 *
 * NAMED 2026-09-01, LIKELY rather than certain.  Builds the messenger
 * subsystem's composite key - a type character ('i' when param_1 is 0,
 * 'n' otherwise; the same ((flag==0)-1 & 5)+0x69 idiom FUN_004026a0's
 * header documents across the whole record family) followed by the name
 * regEax points at - and returns whether FUN_00404b00 finds it in the
 * name-keyed RB tree at owner+0x1be4.
 *
 * Why "pending record": the entries of that tree are created by
 * FUN_004026a0/FUN_00404410 with a direct-link opcode (0x1000/0x2005 -
 * DispatchDirectLinkPacket cases) and a sequence counter, and are
 * flushed-and-erased per name by FUN_00403170 through
 * DispatchDirectLinkPacket.  The one binary call site, 0x403c80 (in the
 * unported gap after FUN_00403ae0), is a send-if-absent guard: only
 * when this returns false does it queue opcode 0x1022 to the server
 * connection at [0x7934e8], and it then records the name via
 * FUN_004026a0(0x1000, ...).  "LIKELY" because that caller is unported
 * and the record semantics rest on unnamed siblings' headers; the
 * neutral "record" avoids deciding between queued-message and
 * outstanding-request readings.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


bool __fastcall HasPendingDirectLinkRecord(int param_1,int param_2,char *regEax)

{
  char cVar1;
  int iVar2;
  char local_18;
  char local_17 [23];
  
  local_18 = ((param_1 == '\0') - 1U & 5) + 0x69;
  iVar2 = -(int)regEax;
  do {
    cVar1 = *regEax;
    regEax[(int)(local_17 + iVar2)] = cVar1;
    regEax = regEax + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00404b00(&local_18,(int *)(param_2 + 0x1be4));
  return iVar2 != 0;
}

