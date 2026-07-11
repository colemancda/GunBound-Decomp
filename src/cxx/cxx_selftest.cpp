/* Compile-time verification of the C++ reconstruction layer against the
 * layouts documented (and binary-confirmed) in ARCHITECTURE.md and
 * docs/widgets.md. This TU includes every header in src/cxx/ and asserts
 * the object sizes and field offsets, so one real-MSVC syntax check
 * validates the whole tree. Run it with:
 *
 *   tools/msvc-env/validate_cxx_selftest.sh   (MSVC 7.10 cl.exe /Zs, gb-msvc image)
 *
 * (32-bit clang can only validate the sizeof asserts - the GB_OFFSETOF
 * null-deref isn't a constant expression there, so the offset asserts need the
 * real-MSVC path above.)
 */
#include "gb_common.h"
#include "GameState.h"
#include "Widget.h"
#include "Protocol.h"
#include "ClientContext.h"
#include "ValueGuard.h"
#include "Mobile.h"
#include "Projectile.h"

/* --- CGameState hierarchy: confirmed allocation sizes ------------------ */
GB_STATIC_ASSERT(sizeof(CState01Title)       == 8,       state01_size);
GB_STATIC_ASSERT(sizeof(CState02ServerSelect)== 0x6c,    state02_size);
GB_STATIC_ASSERT(sizeof(CState03GameRoomList)== 0x294,   state03_size);
GB_STATIC_ASSERT(sizeof(CState05Logo1)       == 8,       state05_size);
GB_STATIC_ASSERT(sizeof(CState06Logo2)       == 8,       state06_size);
GB_STATIC_ASSERT(sizeof(CState07AvatarStore) == 0x34818, state07_size);
GB_STATIC_ASSERT(sizeof(CState09ReadyRoom)   == 0x78c,   state09_size);
GB_STATIC_ASSERT(sizeof(CState10Loading)     == 0x150,   state10_size);
GB_STATIC_ASSERT(sizeof(CState11InBattle)    == 0x2408,  state11_size);

/* --- CMobile: confirmed object size (CreateMobile's operator_new(0xd1d4)) --- */
GB_STATIC_ASSERT(sizeof(CMobile) == 0xd1d4, mobile_size);

/* --- CProjectile: confirmed base object size (shot spawners' operator_new(0x3f9c)) --- */
GB_STATIC_ASSERT(sizeof(CProjectile) == 0x3f9c, projectile_size);

/* --- Wire structures: PROTOCOL.md-confirmed layouts --------------------- */
GB_STATIC_ASSERT(sizeof(GbActionHeader) == 0x21,  actionheader_size);
GB_STATIC_ASSERT(sizeof(GbFirePayload)  == 0x1c,  firepayload_size);
GB_STATIC_ASSERT(sizeof(GbInventoryItem)== 0x9c,  invitem_size);

/* --- CWidget hierarchy: confirmed field offsets and sizes -------------- */
GB_STATIC_ASSERT(sizeof(CWidget)    == 0x38,  widget_size);
GB_STATIC_ASSERT(sizeof(CLabel)     == 0x40,  label_size);
GB_STATIC_ASSERT(sizeof(CEditBox)   == 0x140, editbox_size);
GB_STATIC_ASSERT(sizeof(CScrollBar) == 0x58,  scrollbar_size);
GB_STATIC_ASSERT(sizeof(CPanel)     == 0x90,  panel_size);
GB_STATIC_ASSERT(sizeof(CWorldListPanel) == 0x94, worldlist_size);
GB_STATIC_ASSERT(sizeof(CChannelUserListPanel) == 0x90, channeluser_size);
GB_STATIC_ASSERT(sizeof(CReadyRoomChatPanel)   == 0x90, readychat_size);
GB_STATIC_ASSERT(sizeof(CLobbyChatPanel)       == 0x94, lobbychat_size);
GB_STATIC_ASSERT(sizeof(CAvatarStorePanel)     == 0x9c, avatarstore_size);
GB_STATIC_ASSERT(sizeof(CEnterRoomNumberDialog) == 0x90, roomnodialog_size);
GB_STATIC_ASSERT(sizeof(CBuddyPanel)            == 0x94, buddy_size);
GB_STATIC_ASSERT(sizeof(CCreateRoomDialog)      == 0x9c, createroom_size);
GB_STATIC_ASSERT(sizeof(CStaticText)            == 0x53c, statictext_size);
GB_STATIC_ASSERT(sizeof(CChatLogPanel)          == 0x1050, chatlog_size);
GB_STATIC_ASSERT(sizeof(CPanelListNode)         == 0x0c, panelnode_size);

/* offset checks can't live in the class body (incomplete type there), so
 * they're functions-scope typedefs here */
static void gb_widget_offset_checks()
{
    /* server-list SoA: internal offset must equal documented abs - 0x3f808 */
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, onlineFlag)  == 0x3f809 - 0x3f808, soa_online);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, serverId)    == 0x3f81a - 0x3f808, soa_srvid);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, regionOrType)== 0x3f83a - 0x3f808, soa_region);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, name)        == 0x3f84a - 0x3f808, soa_name);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, desc)        == 0x4004a - 0x3f808, soa_desc);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, serverIp)    == 0x4104a - 0x3f808, soa_ip);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, port)        == 0x4108a - 0x3f808, soa_port);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, currentPlayers) == 0x410ca - 0x3f808, soa_players);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, maxCapacity) == 0x410ea - 0x3f808, soa_maxcap);
    GB_STATIC_ASSERT(GB_OFFSETOF(ServerListSoA, animState)   == 0x4110a - 0x3f808, soa_anim);
    GB_STATIC_ASSERT(GB_OFFSETOF(PeerEndpoint, field8) == 0x23338 - 0x23330, peer_f8);
    GB_STATIC_ASSERT(GB_OFFSETOF(PeerEndpoint, flagC)  == 0x2333c - 0x23330, peer_flag);
    GB_STATIC_ASSERT(GB_OFFSETOF(CValueGuard, enc0)    == 0x04, vg_enc0);
    GB_STATIC_ASSERT(GB_OFFSETOF(CValueGuard, tableHandle) == 0x14, vg_handle);
    GB_STATIC_ASSERT(GB_OFFSETOF(CValueGuard, activeFlag)  == 0x220, vg_activeflag);
    GB_STATIC_ASSERT(sizeof(CValueGuard) == 0x224, vg_size);
    GB_STATIC_ASSERT(sizeof(GuardedBool) == 3,      guardedbool_size);
    GB_STATIC_ASSERT(GB_OFFSETOF(GbActionHeader, actionType) == 0x02, off_actiontype);
    GB_STATIC_ASSERT(GB_OFFSETOF(GbActionHeader, sourceSlot) == 0x05, off_srcslot);
    GB_STATIC_ASSERT(GB_OFFSETOF(GbFirePayload, shotData) == 0x2c - 0x21, off_shotdata);
    GB_STATIC_ASSERT(GB_OFFSETOF(GbInventoryItem, name) == 0x04, off_invname);
    GB_STATIC_ASSERT(GB_OFFSETOF(GbInventoryItem, expYear) == 0x12, off_expyear);
    GB_STATIC_ASSERT(GB_OFFSETOF(GbInventoryItem, displayField) == 0x18, off_invdisp);
    GB_STATIC_ASSERT(GB_OFFSETOF(GbInventoryItem, description) == 0x1c, off_invdesc);
    GB_STATIC_ASSERT(GB_OFFSETOF(CState02ServerSelect, m_slotError) == 0x28, off_sloterr);
    GB_STATIC_ASSERT(GB_OFFSETOF(CState02ServerSelect, m_connectingSlot) == 0x68, off_connslot);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_parent)     == 0x08, off_parent);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_children)   == 0x0c, off_children);
    GB_STATIC_ASSERT(sizeof(CAtlArray<CWidget *>) == 0x10, atlarray_size);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_children.m_nSize) == 0x10, off_childcount);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_hidden)     == 0x1e, off_hidden);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_id)         == 0x24, off_id);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_x)          == 0x28, off_x);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_y)          == 0x2c, off_y);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_width)      == 0x30, off_w);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWidget, m_height)     == 0x34, off_h);
    GB_STATIC_ASSERT(GB_OFFSETOF(CLabel, m_spriteId)    == 0x3c, off_sprite);
    GB_STATIC_ASSERT(GB_OFFSETOF(CEditBox, m_text)      == 0x38, off_text);
    GB_STATIC_ASSERT(GB_OFFSETOF(CEditBox, m_maxLen)    == 0x138, off_maxlen);
    GB_STATIC_ASSERT(GB_OFFSETOF(CScrollBar, m_total)   == 0x38, off_total);
    GB_STATIC_ASSERT(GB_OFFSETOF(CScrollBar, m_scrollPos)== 0x40, off_scrollpos);
    GB_STATIC_ASSERT(GB_OFFSETOF(CPanel, m_strings)     == 0x50, off_strings);
    GB_STATIC_ASSERT(GB_OFFSETOF(CWorldListPanel, m_unk90) == 0x90, off_unk90);

    /* CMobile: confirmed field offsets (InitMobile / CreateMobile / HandleFireInput) */
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_idBase)       == 0x04,   off_mob_id);
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_owner)        == 0x08,   off_mob_owner);
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_spriteId)     == 0x18,   off_mob_sprite);
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_tankTexture)  == 0x1c,   off_mob_tanktex);
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_avataTexture) == 0x54,   off_mob_avatatex);
    /* m_fireAngle/m_firePower removed: they were u8 at int-index 0x243/0x2cc
     * misread as byte offsets; the fields are CValueGuard objects at byte
     * 0x90c/0xb30 (see Mobile.h). */
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_spriteId2)    == 0x904,  off_mob_sprite2);
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_name)         == 0xae15, off_mob_name);
    GB_STATIC_ASSERT(GB_OFFSETOF(CMobile, m_type13Field)  == 0xbff0, off_mob_t13);

    /* CProjectile: confirmed field offsets (InitProjectile / the shot spawners) */
    GB_STATIC_ASSERT(GB_OFFSETOF(CProjectile, m_spriteId)  == 0x18,   off_proj_sprite);
    GB_STATIC_ASSERT(GB_OFFSETOF(CProjectile, m_texture)   == 0x1c,   off_proj_tex);
    GB_STATIC_ASSERT(GB_OFFSETOF(CProjectile, m_lifetime)  == 0x38,   off_proj_life);
    GB_STATIC_ASSERT(GB_OFFSETOF(CProjectile, m_subtype)   == 0x3f90, off_proj_subtype);
}
