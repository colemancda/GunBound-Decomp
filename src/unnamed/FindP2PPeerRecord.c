/* FindP2PPeerRecord - 0x004fe860 in the original binary.
 *
 * NAMED (2026-10-29), LIKELY: look a 16-char peer id up in the P2P peer
 * table at this+0x290 and, on a hit, hand back a pointer to its record.
 * The id is copied (capped at 0x10, NUL-terminated) into a local, the
 * table is searched with StringMap_Find_ac (0x4fe8a2; `mov eax,[esp+
 * 0x30]; add eax,0x290` = the first stack argument + 0x290), and on a
 * hit node+0x14 - the value slot - is stored through the second stack
 * argument and AL = 1; on a miss AL = 0.  `ret 8`.
 *
 * What the table is comes from outside: HasP2PPeerRecord (0x504bb0) is
 * the bool-only twin of this lookup on the same this+0x290 table, and
 * that header ties the table to the CCommP2P sub-object
 * (HashMap_Construct, InitCommP2PNotifyWindow).  What the record is
 * comes from the callers that use the pointer this returns:
 * FUN_004ff770 writes the sender's address and port into record+0/+4
 * and keeps per-peer maps at record+0x20 (IntMap_Lookup_14 /
 * IntMap_SetAt_14) and record+0x50 (IntMap_LookupPair_1768 /
 * IntMap_RemoveKey_1768); FUN_004fe8d0 calls StringMap_FindOrInsert_ac
 * on the same table when this misses and initialises the new record at
 * node+0x14; FUN_004fe110 feeds the record's fields to FUN_004feb00's
 * sockaddr.  LIKELY, like HasP2PPeerRecord, because no named consumer
 * spells out that these records are peers.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * THE ID POINTER IS STILL DROPPED - LEFT UNFIXED (2026-10-29).  The copy
 * loop reads the id through ESI (`mov dl,[ecx+esi]` at 0x4fe868), which
 * the port reads as the undeclared `unaff_ESI`, and functions.h still
 * declares this K&R `()`.  ESI is the caller's at every one of the 11
 * binary sites and no C site passes it; recovering it means a trailing
 * id parameter (as HasP2PPeerRecord's regEsi) and a per-site value, read
 * with tools/callsite_regs.py 0x4fe860 and checked against the
 * disassembly - several sites inherit ESI from earlier in the caller.
 */
#include "ghidra_types.h"


undefined4 FindP2PPeerRecord(undefined4 param_1,int *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int unaff_ESI;
  undefined1 local_1c [10];
  char local_12 [17];
  byte local_1;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + unaff_ESI) == '\0') break;
    bVar1 = bVar1 + 1;
    local_12[uVar2] = *(char *)(uVar2 + unaff_ESI);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  local_1 = bVar1;
  local_12[bVar1] = '\0';
  iVar3 = StringMap_Find_ac(local_12,(uint *)local_1c,(undefined4 *)&param_1,(int *)(param_1 + 0x290),
                       (uint *)(local_1c + 4));
  if (iVar3 != 0) {
    *param_2 = iVar3 + 0x14;
    return CONCAT31((int3)((uint)(iVar3 + 0x14) >> 8),1);
  }
  return 0;
}

