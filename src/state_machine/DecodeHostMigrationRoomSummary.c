/* DecodeHostMigrationRoomSummary - 0x00425a30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00425a30 mean this function.)
 *
 * Evidence (HIGH, wire format from the reference server). Both callers
 * (State09_ReadyRoom_ProcessPacket and State11_InBattle_ProcessPacket)
 * call it only in the GB_OP_HOST_MIGRATION_NOTIFICATION arm, passing
 * payload + 1, i.e. past the leading master-slot byte. The reference
 * server's HostMigrationNotification struct is: masterSlot u8, name
 * (length-prefixed ASCII), map u8, settings u32, itemState u32, value0
 * u32, capacity u8. This function reads exactly that tail: the
 * length-prefixed string into ctx+0x44e64 (NUL-terminated), the map byte
 * to +0x44ef8, settings through EncodeOutgoingPacketField into +0x44efc,
 * itemState and value0 to +0x457a1 and +0x457a5, and the capacity byte to
 * +0x45124. State09 then reads +0x45124 and +0x44efc before calling
 * ApplyRoomSettings. The field meanings are the server struct's, matched
 * by position; they are not read off this body. "RoomSummary" rather than "RoomSettings": the packet also carries
 * the room title and capacity, and the master slot is read by the caller.
 */
#include "ghidra_types.h"


void DecodeHostMigrationRoomSummary(int param_1,byte *regEax)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  uVar2 = (uint)*regEax;
  pbVar4 = regEax + 1;
  pbVar5 = (byte *)(param_1 + 0x44e64);
  for (uVar3 = (uint)(*regEax >> 2); uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pbVar5 = *(undefined4 *)pbVar4;
    pbVar4 = pbVar4 + 4;
    pbVar5 = pbVar5 + 4;
  }
  for (uVar3 = uVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pbVar5 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    pbVar5 = pbVar5 + 1;
  }
  *(undefined1 *)(uVar2 + 0x44e64 + param_1) = 0;
  pbVar4 = regEax + 1 + uVar2;
  *(byte *)(param_1 + 0x44ef8) = *pbVar4;
  uVar1 = *(undefined4 *)(pbVar4 + 1);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x425a80
   * (`lea edi,[ebp+0x44efc]`, ebp = this file's own param_1, confirmed by
   * objdump of orig/GunBound.gme matching this file's own `param_1 +
   * 0x44e64`-style offsets): the cell is param_1+0x44efc. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x44efc, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined4 *)(param_1 + 0x457a1) = *(undefined4 *)(pbVar4 + 5);
  *(undefined4 *)(param_1 + 0x457a5) = *(undefined4 *)(pbVar4 + 9);
  *(byte *)(param_1 + 0x45124) = pbVar4[0xd];
  return;
}

