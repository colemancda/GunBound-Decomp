/* LoadReadyRoomSlotAvatar - 0x004431a0 in the original binary.
 *
 * Loads/composites a slot's worn avatar from the Ready-Room copy of the
 * avatarEquipped record at g_clientContext + 0x501fe + slot*8 (the copy State09
 * mirrors from the room record +0x458bc; four packed u16 part codes, high bit
 * of word 0 = gender). Applies the per-gender default table (+0x6aa662), then
 * calls the compositor LoadAvatarSprites (0x4141b0). Peer of LoadRoomSlotAvatar
 * (0x4dc5c0), which reads the room copy at +0x458bc instead; invoked from
 * State10_Loading_PreloadAssets. See FILEFORMATS.md "Avatar.xfs".
 *
 * Function IDENTITY is confirmed; the BODY is a raw/near-verbatim Ghidra port,
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
*
 * DROPPED REGISTER RECOVERED (2026-08-27): in_EAX is the ready-room SLOT
 * INDEX, and it is a literal 0..7 at the eight call sites -- `xor eax,eax`
 * then `mov eax,1` .. `mov eax,7`, all in State10_Loading_PreloadAssets.
 * The body agrees: it indexes `g_clientContext + 0x501fe + in_EAX * 8`, an
 * eight-entry table of stride 8, which is the ready-room's eight slots.
 *
 * The pairing needs no ordering assumption.  The eight calls are the bodies
 * of switch cases 0x46..0x4d, and each is gated on its own byte --
 * `*(char *)(g_clientContext + 0x5010d + N)` for N = 0..7 -- so the gate
 * offset moves in lockstep with the slot index.  Checked at both ends:
 * 0x441955 loads [ecx + 0x5010d] before the `xor eax,eax` site, and the
 * `mov eax,7` site is preceded by the 0x50114 gate.
 */
#include "ghidra_types.h"


void LoadReadyRoomSlotAvatar(int regEax)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int in_EAX = regEax;
  uint uVar5;
  
  uVar1 = *(ushort *)(g_clientContext + 0x501fe + in_EAX * 8);
  uVar5 = (uint)((uVar1 & 0x8000) != 0x8000);
  uVar2 = *(ushort *)(&DAT_006aa664 + uVar5 * 8 + g_clientContext);
  if (uVar2 == 0xffff) {
    uVar2 = *(ushort *)(g_clientContext + 0x50200 + in_EAX * 8);
  }
  uVar3 = *(ushort *)(&DAT_006aa666 + uVar5 * 8 + g_clientContext);
  if (uVar3 == 0xffff) {
    uVar3 = *(ushort *)(g_clientContext + 0x50202 + in_EAX * 8);
  }
  uVar4 = *(ushort *)(&DAT_006aa662 + uVar5 * 8 + g_clientContext);
  if (uVar4 == 0xffff) {
    uVar4 = uVar1;
  }
  uVar1 = *(ushort *)(&DAT_006aa668 + uVar5 * 8 + g_clientContext);
  if (uVar1 == 0xffff) {
    uVar1 = *(ushort *)(g_clientContext + 0x50204 + in_EAX * 8);
  }
  LoadAvatarSprites(uVar1 & 0x7fff,uVar4 & 0x7fff,uVar3 & 0x7fff,uVar2 & 0x7fff,0,in_EAX + 200000,
               in_EAX + 300000);
  return;
}

