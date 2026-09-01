/* HasP2PSessionPeer - 0x00504790 in the original binary.
 *
 * NAMED 2026-09-01, LIKELY rather than certain.  Case-insensitive scan
 * (strnicmp, 0x10 chars) of the 0x12-stride peer-name roster whose
 * begin/end pointers sit at session+0x1aa4/+0x1aa8; returns 1 when the
 * name is listed, 0 otherwise.  What that roster is comes from outside
 * this body: FUN_00501770's receive arms maintain it through the SAME
 * begin/end pair addressed 0x2f4 higher (+0x17b0/+0x17b4) - the 0x3001
 * arm inserts a peer (with nick and address info) via FUN_00502750 and
 * the 0x3003 arm erases one after the identical strnicmp-by-name walk
 * via FUN_005027d0 - and SendBuddyNameMessage's header established that
 * base as the CBuddy2 messenger session object and reads the 0x3002/
 * 0x3003 exchange as "drop peer <name> from my session list".  So this
 * predicate reports whether a peer name is on the messenger session's
 * list.  "LIKELY" because the "session list" reading rests on that
 * header's analysis of unported dispatcher arms, not on a named
 * consumer.  Distinct from HasP2PPeerRecord (0x504bb0), which checks
 * the 0xac-record ADDRESS map at vtable-object+0x290, a different
 * container.  Sole caller is RequestP2PPeerByName (0x504880, vtable
 * slot 7 at 0x5575b0), which passes session = its own this - 0x2c.
 *
 * RECOVERED (2026-09-01): the prerequisite caller promotions landed in
 * the same batch as this note - the regEsi parameter below is live and
 * every site passes the verified value; see the commit for the chain.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 HasP2PSessionPeer(char *param_1,int regEsi)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar2 = 0;
  while( true ) {
    if (*(int *)(regEsi + 0x1aa4) == 0) {
      return 0;
    }
    if ((uint)((*(int *)(regEsi + 0x1aa8) - *(int *)(regEsi + 0x1aa4)) / 0x12) <= uVar3)
    break;
    iVar1 = __strnicmp((char *)(*(int *)(regEsi + 0x1aa4) + iVar2),param_1,0x10);
    if (iVar1 == 0) {
      return 1;
    }
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x12;
  }
  return 0;
}

