/* UpdateP2PPeerRecordIfChanged - 0x005039a0 in the original binary.
 *
 * NAMED (batch 35), LIKELY (was FUN_005039a0).  Applies one peer entry of a
 * 0x3fff peer-list update that carries addresses.  EAX = the 16-char id,
 * EDI = the engine object, stack = (ip, port, ip2) with the second port in
 * EBX.  It calls FindP2PPeerRecord; if the record exists, its first dword
 * is non-zero and all four address fields (+8, +0xc, +0x10, +0x14) already
 * equal the incoming ones, it only clears the pending flag record+0x1c and
 * returns (the "unchanged" arm); otherwise it falls through to
 * UpsertP2PPeerRecord with the incoming addresses.  The caller
 * (CommP2POwner_ProcessPacket, orig 0x502403) reaches it only when the
 * entry's flag byte at +0x10 is non-zero; the else arm of the same branch
 * calls RemoveP2PPeerRecord and drops the id from the secondary maps, so
 * the flag selects update versus remove.  The name covers the unchanged
 * shortcut: it avoids the full Upsert (and its datagram flush) when the
 * address is the same.  LIKELY, as for the other P2P peer helpers.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX, EDI, EBX RECOVERED (2026-08-31, correcting the 2026-08-25 pass).  At
 * the one site, 0x502403 in CommP2POwner_ProcessPacket, THREE pushes are pending, so
 * `lea eax,[esp+0x30]` (0x5023fd) is esp_b+0x24 = &local_496c itself -- the
 * 16-char id the branch just assembled, the string UpsertP2PPeerRecord's param_2
 * copy loop consumes -- not sa_data+10 (the 08-25 note missed the pushes).
 * EDI is loaded at 0x5023d9 from [esp+0x20] = local_4970 = param_1 - 0x2c8,
 * the engine object, matching the else-branch twin RemoveP2PPeerRecord(local_4970,
 * &local_496c); the [esp+0x14]=local_497c read at 0x50240c is the post-call
 * EDI RESTORE the 08-25 note mistook for the input.  EBX is `xor esi,esi /
 * mov si,[ebx]` (0x5023ee/0x5023f0) then `mov ebx,esi` (0x502401): the
 * zero-extended WORD at record+0x1b, the port of the second address pair,
 * landing word-wide in UpsertP2PPeerRecord's param_6.  Width settled: pass it as
 * (undefined4)*(ushort *)(rec + 0x1b).
 *
 * FindP2PPeerRecord ID RECOVERED (2026-10-29): the call at 0x5039ae dropped
 * ESI = `mov esi,eax` (0x5039a6) = regEax; witness: the same ESI is pushed
 * as UpsertP2PPeerRecord's id at 0x5039f4, ported as regEax.
 */
#include "ghidra_types.h"


void UpdateP2PPeerRecordIfChanged(int param_1,undefined4 param_2,int *param_3,undefined4 regEax,
                  undefined4 regEdi,undefined4 regEbx)

{
  int *piVar1;
  char cVar2;
  
  piVar1 = param_3;
  cVar2 = FindP2PPeerRecord(regEdi,(int *)&param_3,(char *)regEax);
  if ((((cVar2 != '\0') && (*param_3 != 0)) && (param_3[2] == param_1)) &&
     ((((short)param_3[3] == (short)param_2 && ((int *)param_3[4] == piVar1)) &&
      ((short)param_3[5] == (short)regEbx)))) {
    *(undefined1 *)(param_3 + 7) = 0;
    return;
  }
  UpsertP2PPeerRecord((undefined4 *)regEdi,(int)regEax,param_1,(short)param_2,(int)piVar1,(short)regEbx);
  return;
}

