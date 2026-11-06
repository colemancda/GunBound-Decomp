/* AddP2PPeerRecordIfMissing - 0x00503a10 in the original binary.
 *
 * NAMED (batch 35), LIKELY (was FUN_00503a10).  Create-if-absent for the P2P
 * peer table: EAX = the 16-char peer id, EDI = the engine object
 * (CommP2POwner_ProcessPacket's this - 0x2c8).  It asks FindP2PPeerRecord
 * (0x4fe860) first; only on a miss does it call UpsertP2PPeerRecord
 * (0x4fe8d0) with four zero address fields, look the record up again, and
 * set record+0x1c = 1.  UpsertP2PPeerRecord's header documents record+0x1c
 * as the pending flag that an upsert clears, and that zero pushes create an
 * "address-less record"; this call re-arms the flag, so the record is a
 * placeholder awaiting an address.  Both callers in
 * CommP2POwner_ProcessPacket call it immediately after pushing the
 * packet's peer id onto the roster vectors (Vector_PushBack_12 at
 * owner+0x17ac), once per listed peer.  Counterpart of
 * UpdateP2PPeerRecordIfChanged (the address-carrying entries) and
 * RemoveP2PPeerRecord.  LIKELY because FindP2PPeerRecord and the record
 * layout are themselves LIKELY.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX and EDI RECOVERED (2026-08-25), both sites in CommP2POwner_ProcessPacket under its
 * -0x4990 frame constant: EAX is &local_48f0 / &local_496c and EDI the value
 * at -0x4970 / iVar7 - 0x2c8.  The second site is pinned by the line above it,
 * `iVar7 = local_497c`, which is the very slot EBX is loaded from.
 *
 * FindP2PPeerRecord ID RECOVERED (2026-10-29): both calls (0x503a1a,
 * 0x503a39) dropped ESI = `mov esi,eax` (0x503a12) = regEax, preserved
 * across UpsertP2PPeerRecord (which saves/restores ESI); witness: the same ESI
 * is pushed as UpsertP2PPeerRecord's id at 0x503a2b, ported as regEax.
 *
 * UpsertP2PPeerRecord `this` RECOVERED (2026-10-29): the call at 0x503a2e dropped
 * ECX = `mov ecx,edi` (0x503a2c) = regEdi, the same EDI pushed as
 * FindP2PPeerRecord's map at 0x503a19.  Pushes are ESI (= regEax, the id)
 * then four zeros, so the call is now (regEdi, regEax, 0, 0, 0, 0).
 */
#include "ghidra_types.h"


void AddP2PPeerRecordIfMissing(undefined4 regEax,undefined4 regEdi)

{
  char cVar1;
  int local_4;
  
  cVar1 = FindP2PPeerRecord(regEdi,&local_4,(char *)regEax);
  if (cVar1 == '\0') {
    UpsertP2PPeerRecord((undefined4 *)regEdi,(int)regEax,0,0,0,0);
    cVar1 = FindP2PPeerRecord(regEdi,&local_4,(char *)regEax);
    if (cVar1 != '\0') {
      *(undefined1 *)(local_4 + 0x1c) = 1;
    }
  }
  return;
}

