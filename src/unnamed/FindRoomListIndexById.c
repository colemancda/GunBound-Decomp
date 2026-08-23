/* FindRoomListIndexById - 0x0041c290 in the original binary.
 *
 * Linear search of the client's ROOM-ID TABLE for a given room id, returning
 * the room's index in the table, or -1 if it is not listed.
 *
 * The table is the one SendJoinRoomSelected and SendJoinRoomChecked already
 * document and index directly: the entry count is a byte at g_clientContext
 * + 0x44648, the ids are 4 bytes apart from + 0x44664, and the matching
 * 0x80-byte per-room record lives at + 0x4467c + index * 0x80.  Callers use
 * the returned index for exactly that: State03_GameRoomList_ProcessPacket
 * looks a room up and then writes the packet payload into its record.
 *
 * Named from that agreement rather than from this function alone - the
 * body only shows a count-prefixed array of 4-byte values searched by its
 * low 16 bits, which is not enough on its own to say what is being searched.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * BOTH REGISTER ARGUMENTS RECOVERED, and the call sites filled rather than
 * appended to.  `ret 0` means nothing arrives on the stack, so param_1 (ECX)
 * and ESI are the entire input; all seven call sites passed neither.
 *
 * ECX is g_clientContext at every site -- loaded straight from [0x5b3484] at
 * six of them and via EDI, which holds the same load, at the seventh.  That
 * agrees with the body, which only ever uses param_1 as an arena base
 * (param_1 + 0x44648, + 0x44664).
 *
 * ESI is 0 at every site, and is the key this searches for: the loop compares
 * (regEsi & 0xffff) against each entry.  A lookup whose key was whatever
 * happened to be in ESI is not a lookup.
 */
#include "ghidra_types.h"


int __fastcall FindRoomListIndexById(int param_1,uint regEsi)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = 0;
  if (*(byte *)(param_1 + 0x44648) != 0) {
    puVar2 = (uint *)(param_1 + 0x44664);
    do {
      if (*puVar2 == (regEsi & 0xffff)) {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar1 < (int)(uint)*(byte *)(param_1 + 0x44648));
  }
  return -1;
}

