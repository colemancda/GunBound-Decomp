/* ConstructP2PPeerRecord - 0x004ff1a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, LIKELY (was FUN_004ff1a0).  The default constructor
 * of the value type of the 0xac-node string map - the record
 * FindP2PPeerRecord hands out at node+0x14.  StringMap_Insert_ac, the
 * map's CreateNode, runs it on the new node's value slot (`lea
 * edi,[ebp+0x14]; call 0x4ff1a0` at 0x5014ad-0x5014b4), and
 * UpsertP2PPeerRecord runs it on a stack temporary of the same type
 * before inserting into the peer table at +0x290.  It builds exactly
 * the members DestroyP2PPeerRecord tears down: two CAtlMaps through
 * HashMap_Construct at +0x20 and +0x50 - the +0x50 one is the
 * 0x1768-stride pending-send map RetransmitPendingP2PDatagrams walks,
 * the +0x20 one the 0x14-stride map CommP2PReceiveDatagram looks
 * sequence numbers up in - and the zeroed four-dword array header at
 * +0x80 (the 0x1750-stride queue UpsertP2PPeerRecord flushes).  It
 * returns the object in EAX (`mov eax,edi` at 0x4ff1fd), the usual
 * constructor return; the port is void and no caller reads it.  The
 * verb-first form matches ConstructCommP2POwner and the
 * Find/Upsert/HasP2PPeerRecord family rather than the scoping pass's
 * P2PPeerRecord_Construct.  LIKELY only because "peer record" is the
 * handle FindP2PPeerRecord (itself LIKELY) gave this type; the
 * constructor role is certain.
 *
 * EDI RECOVERED (2026-08-25): the object whose last four dwords (+0x80..+0x8c)
 * this clears.  At 0x5014b4 it is `lea edi,[ebp+0x14]` = the source's
 * puVar2 + 0x14; at 0x4fe90f it is `lea edi,[esp+0x2c]`, frame -0x9c in a
 * caller whose frame is 0xc8 -- a 0x90-byte object that caller never declared.
 */
#include "ghidra_types.h"


void ConstructP2PPeerRecord(int regEdi)

{
  
  HashMap_Construct(0xa,0x3f400000,0x3e800000,0x40100000,0x11,(undefined4 *)(regEdi + 0x20));
  HashMap_Construct(0xa,0x3f400000,0x3e800000,0x40100000,0x11,(undefined4 *)(regEdi + 0x50));
  *(undefined4 *)(regEdi + 0x80) = 0;
  *(undefined4 *)(regEdi + 0x84) = 0;
  *(undefined4 *)(regEdi + 0x88) = 0;
  *(undefined4 *)(regEdi + 0x8c) = 0;
  return;
}

