/* LoadRoomSlotAvatar - 0x004dc5c0 in the original binary.
 *
 * Loads/composites a room-slot player's worn avatar. Reads the slot's
 * avatarEquipped record at g_clientContext + 0x458bc + slot*8 (four packed u16
 * part codes; high bit of word 0 = gender), applies the per-gender default
 * table at +0x6aa662 (0xffff sentinel -> use the record's own words), then
 * calls the compositor LoadAvatarSprites (0x4141b0) with the four part codes.
 *
 * NOTE: previously mis-read (in PROTOCOL.md) as a "team-side spawn
 * position/camera setup" finalizer - +0x458bc is the avatar record, not
 * coordinates, and the &0x8000 bit is gender, not team side. See FILEFORMATS.md
 * "Avatar.xfs".
 *
 * Function IDENTITY is confirmed; the BODY is a raw/near-verbatim Ghidra port,
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void __fastcall LoadRoomSlotAvatar(int param_1)

{
  ushort uVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  short sVar5;
  ushort uVar6;
  
  uVar1 = *(ushort *)(g_clientContext + 0x458bc + param_1 * 8);
  uVar4 = (uint)((uVar1 & 0x8000) != 0x8000);
  if ((DAT_00793522 != '\0') && (*(short *)(&DAT_006aa660 + g_clientContext) != -1)) {
    sVar5 = *(short *)(&DAT_006aa668 + uVar4 * 8 + g_clientContext);
    if (sVar5 == -1) {
      sVar5 = *(short *)(g_clientContext + 0x458c2 + param_1 * 8);
    }
    sVar3 = *(short *)(&DAT_006aa666 + uVar4 * 8 + g_clientContext);
    if (sVar3 == -1) {
      sVar3 = *(short *)(g_clientContext + 0x458c0 + param_1 * 8);
    }
    uVar6 = *(ushort *)(&DAT_006aa662 + uVar4 * 8 + g_clientContext);
    if (*(ushort *)(&DAT_006aa662 + uVar4 * 8 + g_clientContext) == 0xffff) {
      uVar6 = uVar1;
    }
    sVar2 = *(short *)(&DAT_006aa664 + uVar4 * 8 + g_clientContext);
    if (sVar2 == -1) {
      sVar2 = *(short *)(g_clientContext + 0x458be + param_1 * 8);
    }
    LoadAvatarSprites(sVar2,uVar6,sVar3,sVar5,0,param_1 + 200000,param_1 + 300000);
    return;
  }
  LoadAvatarSprites(*(undefined2 *)(g_clientContext + 0x458be + param_1 * 8),uVar1,
               *(undefined2 *)(g_clientContext + 0x458c0 + param_1 * 8),
               *(undefined2 *)(g_clientContext + 0x458c2 + param_1 * 8),0,param_1 + 200000,
               param_1 + 300000);
  return;
}

