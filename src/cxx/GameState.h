/* CGameState - the game-state (screen) base class and its 16 concrete
 * states. Reconstruction of ARCHITECTURE.md "The `CGameState` base class
 * and virtual dispatch" / "The 16 game states"; see src/cxx/README.md for
 * conventions and confidence levels.
 *
 * CONFIRMED: the 10-slot base vtable order, slot roles 0/1/5/6/7/8/9, the
 * per-state object sizes, the null-object pattern for states 0/15, and
 * State11's full 18-slot vtable (dumped from 0x5566d8).
 * GUESSED: every name, single inheritance, slot 3/4 roles.
 */
#ifndef GB_CXX_GAMESTATE_H
#define GB_CXX_GAMESTATE_H

#include "gb_common.h"

/* The 16-slot state id space (g_gameStateVTableArray indices, 0x5b33f8).
 * Ids 4, 8 and 12-14 are never constructed; 0 and 15 share the trivial
 * null-object vtable (0x553fb0). */
enum GameStateId {
    STATE_NULL         = 0,   /* pre-init placeholder            */
    STATE_TITLE        = 1,   /* titlemode.img, title.mp3        */
    STATE_SERVER_SELECT= 2,   /* server_list.img, channel.mp3    */
    STATE_GAME_ROOM_LIST=3,   /* channel lobby                   */
    STATE_LOGO1        = 5,   /* logomode.img, logo.mp3          */
    STATE_LOGO2        = 6,   /* logomode2.img, logo2.mp3        */
    STATE_AVATAR_STORE = 7,   /* store_*.img                     */
    STATE_READY_ROOM   = 9,   /* pre-battle room                 */
    STATE_LOADING      = 10,  /* loadmode.img interstitial       */
    STATE_IN_BATTLE    = 11,  /* stage%d.mp3, the game itself    */
    STATE_QUIT         = 15   /* ChangeGameState(15) -> PostQuitMessage */
};

/* Abstract screen base. Objects are heap-allocated during InitGame
 * (0x40eaa0) and installed into g_gameStateVTableArray[16]; transitions go
 * through ChangeGameState (0x4122f0): old->OnExit() then new->OnEnter().
 * Declaration order below IS the confirmed binary vtable order. */
class CGameState {
public:
    virtual ~CGameState();                                  /* slot 0 +0x00: CGameState_ScalarDeletingDestructor 0x4e5320
                                                             * -> CGameState_BaseDestructor 0x426ac0 resets the vtable
                                                             * ptr to the shared null-object vtable 0x553fb0 */
    virtual void ProcessPacket(int payloadLen, u16 opcode,  /* slot 1 +0x04: per-screen protocol dispatcher; default is  */
                               u16 *payload);               /* the no-op CGameState_NoOpVirtual_A 0x448430               */
    virtual void ProcessBattleAction(int a, int b);         /* slot 2 +0x08: battle-action dispatcher where overridden
                                                             * (state 9 0x4d38c0-family, state 11 0x4b5460); no-op
                                                             * CGameState_NoOpVirtual_B 0x4fdef0 elsewhere */
    virtual void v3();                                      /* slot 3 +0x0c: role unconfirmed (usually NoOpVirtual_B) */
    virtual void v4();                                      /* slot 4 +0x10: role unconfirmed (usually NoOpVirtual_B) */
    virtual void OnKeyInput(int msg, int a, int b);         /* slot 5 +0x14: keyboard/chat/command dispatcher */
    virtual void OnMouseInput(int msg, int x, int y);       /* slot 6 +0x18: dispatches on Win32 mouse message codes */
    virtual void OnEnter();                                 /* slot 7 +0x1c: load .img/.mp3, build widget tree */
    virtual void OnExit();                                  /* slot 8 +0x20 */
    virtual void OnTick();                                  /* slot 9 +0x24: per-frame hook (render/timer) */
    /* subclasses append their own virtuals from slot 10 up */
};

/* --- Concrete states -----------------------------------------------------
 * Sizes are the confirmed heap allocations from ARCHITECTURE.md's state
 * table. States whose field maps aren't reconstructed yet carry an opaque
 * m_raw tail so sizeof() matches the binary allocation exactly (checked in
 * cxx_selftest.cpp). */

class CState01Title : public CGameState {       /* size 8; vtable_State01_Title */
public:
    virtual void OnEnter();                     /* 0x4e5370 - promoted, State01_Title.cpp */
    virtual void OnExit();                      /* 0x4e53b0 - promoted, State01_Title.cpp */

    int m_frameCounter;                         /* +0x04: the state's only field */
};

/* Server/Channel select. Field map from docs/screens/02_server_select.md
 * (offsets confirmed there); the server list itself is NOT in this
 * object - it is the 16-entry SoA at g_clientContext+0x3f808. */
class CState02ServerSelect : public CGameState {/* size 0x6c; ProcessPacket 0x4e02b0 */
public:
    CState02ServerSelect() : m_connectingSlot(-1) {} /* the only init InitGame does inline */

    virtual void OnEnter();  /* 0x4e14b0 - promoted, State02_ServerSelect.cpp */
    virtual void OnExit();   /* 0x4e17f0 - promoted, State02_ServerSelect.cpp */
    virtual void OnTick();   /* 0x4e1960 - promoted, State02_ServerSelect.cpp */

    u8  m_connecting;        /* +0x04: set while a connect attempt is in flight */
    u8  m_sendHandshake;     /* +0x05: connect succeeded - send the 0x1000
                              * handshake on the next tick */
    u8  m_uiDirty;           /* +0x06: UI-dirty/interactable flag - WorldListPanel's
                              * mouse handler gates row selection on it == 1 */
    u8  m_wantInitialList;   /* +0x07: set by OnEnter - the tick sends the first
                              * 0x1100 page request once the socket connects */
    int m_highlightedSlot;   /* +0x08: UI cursor, -1 = none (set from RowHitTest) */
    int m_unk0c;             /* +0x0c */
    u8  m_viewMode;          /* +0x10: 0 = all servers, 2 = friends (the world-list tabs) */
    u8  m_pad11[3];          /* +0x11 */
    int m_scrollA;           /* +0x14: scroll/paging (seeded from a global at OnEnter) */
    int m_scrollOffset;      /* +0x18: current page offset sent in the 0x1100 request */
    int m_unk1c;             /* +0x1c */
    int m_tickCounter;       /* +0x20 */
    u8  m_inputEnabled;      /* +0x24: set to (highlightedSlot != -1) on row click */
    u8  m_pad25[3];          /* +0x25 */
    int m_slotError[16];     /* +0x28: per-slot connect error codes 0x1d-0x20 */
    int m_connectingSlot;    /* +0x68: slot a connect is targeting, -1 = none */
};

class CState03GameRoomList : public CGameState {/* size 0x294; ProcessPacket 0x426ad0.
                                                 * The Ghidra project names its vtable
                                                 * vtable_State3_NetworkSession. */
public:
    CState03GameRoomList() : m_unk11c(0), m_unk288(1) {} /* InitGame's inline inits */

    void RenderRoomCard(int slot);              /* 0x42a220 - promoted, State03_GameRoomList.cpp
                                                 * (non-virtual helper; +0x04 = selected room,
                                                 * +0x08 = hovered room) */
    void RenderRoomLabel();                     /* 0x429810 - vtable slot 15, the per-frame
                                                 * render hook (GameTick calls it). Kept
                                                 * non-virtual like RenderRoomCard until
                                                 * State03's slots 10-15 are dumped. */

    int m_selectedRoom;                         /* +0x04: room slot under the join selection */
    int m_hoveredRoom;                          /* +0x08: room slot under the cursor */
    u8  m_rawA[0x11c - 0x0c];                   /* field map not yet reconstructed */
    int m_unk11c;                               /* +0x11c: starts 0 */
    u8  m_rawB[0x288 - 0x120];                  /* +0x120 */
    u8  m_unk288;                               /* +0x288: starts 1 */
    u8  m_rawC[0x294 - 0x289];                  /* +0x289 */
};

class CState05Logo1 : public CGameState {       /* size 8 */
public:
    virtual void OnEnter();                     /* 0x4433f0 - promoted, State05_Logo1.cpp */
    virtual void OnExit();                      /* 0x443430 - promoted, State05_Logo1.cpp */

    int m_frameCounter;                         /* +0x04 (same shape as Title) */
};

class CState06Logo2 : public CGameState {       /* size 8 */
public:
    virtual void OnEnter();                     /* 0x443280 - promoted, State06_Logo2.cpp */
    virtual void OnExit();                      /* 0x4432c0 - promoted, State06_Logo2.cpp */

    int m_frameCounter;                         /* +0x04 */
};

class CState07AvatarStore : public CGameState { /* size 0x34818; ctor FUN_00443c20 */
public:
    u8 m_raw[0x34818 - 4];                      /* includes an 8 x 0x224 per-avatar
                                                 * slot array (placement not yet mapped) */
};

class CState09ReadyRoom : public CGameState {   /* size 0x78c; ctor FUN_004d3770 */
public:
    u8 m_raw[0x78c - 4];                        /* field map not yet reconstructed */
};

class CState10Loading : public CGameState {     /* size 0x150 */
public:
    virtual void OnKeyInput(int msg, int a, int b); /* 0x43e720 State10_Loading_HandleChatInput - promoted */
    virtual void OnExit();                      /* 0x43eff0 - promoted, State10_Loading.cpp */

    u8 m_raw[0x150 - 4];                        /* field map not yet reconstructed */
};

/* In-Battle: the one state whose FULL vtable is confirmed (18 slots,
 * dumped from vtable_State11_InBattle 0x5566d8). Slots 10-17 are
 * State11-specific extensions, appended after the base's 10. */
class CState11InBattle : public CGameState {    /* size 0x2408; ctor 0x4b3f90 */
public:
    /* base-slot overrides (binding documented in ARCHITECTURE.md):
     *  slot 0  dtor            0x4b4060
     *  slot 1  ProcessPacket   0x4b4100  State11_InBattle_ProcessPacket
     *  slot 2  ProcessBattleAction 0x4b5460
     *  slot 5  OnKeyInput      0x4b82b0  chat/keyboard dispatcher
     *  slot 6  OnMouseInput    0x4b97d0
     *  slot 7  OnEnter         0x4bb730
     *  slot 8  OnExit          0x4bcd00
     *  slot 9  OnTick          0x4bd8b0  cursor/camera-scroll + per-tick bookkeeping */
    virtual void ChatInputChar(int ch);         /* slot 10 +0x28: 0x4c1b90 appends to the chat buffers,
                                                 * remaps '@#$%^&*' to emoticon control codes 0x0a-0x10 */
    virtual void TickCounters();                /* slot 11 +0x2c: 0x4c1c90 small per-tick helper */
    virtual void UpdateActiveObjectSlot();      /* slot 12 +0x30: 0x4c1d10 one-line delegate to FUN_004508a0 */
    virtual void ClearEffectTextures();         /* slot 13 +0x34: 0x4c1d30 per-frame Lock/zero/Unlock of the
                                                 * ~24 dynamic effect render-targets */
    virtual void Render();                      /* slot 14 +0x38: 0x4c3020 State11_InBattle_Render (D3D scene) */
    virtual void RenderChatLog();               /* slot 15 +0x3c: 0x4c8890 software-blit HUD chat overlay,
                                                 * color-coded by per-line message-type byte */
    virtual void RenderModeIcons();             /* slot 16 +0x40: 0x4caed0 */
    virtual void v17();                         /* slot 17 +0x44: 0x429800 genuine per-state no-op */

    u8 m_raw[0x2408 - 4];                       /* chat history buffers live at +0x58b64 (sender, 9-byte
                                                 * stride) / +0x58bbe (text, 14-byte stride) RELATIVE TO
                                                 * g_clientContext, not this object - field map here is
                                                 * not yet reconstructed */
};

#endif /* GB_CXX_GAMESTATE_H */
