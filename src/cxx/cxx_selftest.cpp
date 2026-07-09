/* Compile-time verification of the C++ reconstruction layer against the
 * layouts documented (and binary-confirmed) in ARCHITECTURE.md and
 * docs/widgets.md. This TU includes every header in src/cxx/ and asserts
 * the object sizes and field offsets, so one real-MSVC syntax check
 * validates the whole tree:
 *
 *   docker exec gb-check wine 'Z:\opt\msvc7\bin\cl.exe' /c /nologo /Zs \
 *       'Z:\work\src\cxx\cxx_selftest.cpp'
 */
#include "gb_common.h"
#include "GameState.h"
#include "Widget.h"

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
}
