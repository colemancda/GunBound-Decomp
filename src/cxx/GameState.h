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
    /* Slots 10-17: NOT per-state extensions - the base ABI is a fixed
     * 18-slot vtable.  Proven 2026-08-18 by tools/vtable_census.py: the
     * shared null-object vtable 0x553fb0 (7 installs) and EVERY concrete
     * state vtable (03/07/09/10/11 dumped in docs/vtable_census.txt) are
     * 18 slots, with per-slot no-op defaults (slot 10 NoOpVirtual_A
     * 0x448430, the rest NoOpMethod 0x429800).  CState11InBattle's old
     * "State11-specific extensions" comment predated this. */
    virtual void AppendChatLine();                          /* slot 10 +0x28: append to the state's chat/status log.
                                                             * Shared impl 0x442240 in states 03+10; 0x4d7d70 state 09;
                                                             * 0x4c1b90 state 11 (remaps @#$%^&* to emoticon codes) */
    virtual void v11();                                     /* slot 11 +0x2c: no-op everywhere but state 11 (TickCounters) */
    virtual void v12();                                     /* slot 12 +0x30: no-op everywhere but state 11 */
    virtual void RenderLayerA();                            /* slot 13 +0x34: first render sublayer (09 roster, 07 store
                                                             * content; state 11 clears the effect render-targets here) */
    virtual void RenderLayerB();                            /* slot 14 +0x38: second sublayer (09 character preview,
                                                             * 07 avatar preview, 11 the full D3D scene) */
    virtual void RenderOverlay();                           /* slot 15 +0x3c: top overlay (03 room label, 10 render,
                                                             * 09 status overlay, 11 chat log) */
    virtual void v16();                                     /* slot 16 +0x40: no-op everywhere but state 11 (mode icons) */
    virtual void v17();                                     /* slot 17 +0x44: no-op in every dumped vtable */
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
    int m_highlightedSlot;   /* +0x08: selected server slot, -1 = none (set from
                              * RowHitTest). Live capture: row-click set it -1->0 */
    int m_selectedSlot;      /* +0x0c: tracks the selection alongside +0x08 - moved
                              * -1->0 in lockstep on the same row-click (live) */
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
                                                 * C-side vtable: vtable_State03_GameRoomList
                                                 * (renamed from the wrong
                                                 * vtable_State3_NetworkSession guess). */
public:
    CState03GameRoomList() : m_unk11c(0), m_unk288(1) {} /* InitGame's inline inits */

    void RenderRoomCard(int slot);              /* 0x42a220 - promoted, State03_GameRoomList.cpp
                                                 * (non-virtual helper; +0x04 = selected room,
                                                 * +0x08 = hovered room) */
    virtual void AppendChatLine();              /* slot 10: 0x442240 - the impl SHARED with state 10 */
    virtual void RenderOverlay();               /* slot 15: 0x429810 "RenderRoomLabel" - the per-frame
                                                 * render hook (GameTick calls it).  Promoted to the
                                                 * virtual now that the vtable is dumped (census
                                                 * 0x553670); body in State03_GameRoomList.cpp. */
    void CreateButtons();                       /* 0x42aba0 - build the 12 bottom-bar
                                                 * buttons (helper; void(void) in the
                                                 * original, called from OnEnter) */

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

/* Ready Room: full vtable 0x5569f8 (18 slots; every slot ported - see
 * docs/vtable_coverage.txt).  Overrides base slots 0-3, 5-10, 13-15;
 * notably the ONLY state overriding base slot 3 (OnActivate 0x4d54c0 -
 * the evidence for v3 being an activate/focus hook). */
class CState09ReadyRoom : public CGameState {   /* size 0x78c; ctor State09_ReadyRoom_Construct */
public:
    /* base-slot overrides (census identities):
     *  slot 0  dtor            0x4d37f0  State09_ReadyRoom_Delete
     *  slot 1  ProcessPacket   0x4d38c0  State09_ReadyRoom_ProcessPacket
     *  slot 2  ProcessBattleAction 0x4d4ea0
     *  slot 3  v3              0x4d54c0  State09_ReadyRoom_OnActivate (the
     *          only state known to override base slot 3 - evidence for v3
     *          being an activate/focus hook)
     *  slot 4  v4              base default (CGameState_NoOpVirtual_B)
     *  slot 5  OnKeyInput      0x4d54e0  (PROGRESS name ..._OnCommand)
     *  slot 6  OnMouseInput    0x4d6210  (PROGRESS name ..._HandleChatInput)
     *  slot 7  OnEnter         0x4d6810
     *  slot 8  OnExit          0x4d7630
     *  slot 9  OnTick          0x4d7b20 */
    virtual void AppendChatLine();              /* slot 10: 0x4d7d70 AppendReadyRoomStatusMessage */
    virtual void RenderLayerA();                /* slot 13: 0x4d7db0 State09_ReadyRoom_RenderRosterAndItems */
    virtual void RenderLayerB();                /* slot 14: 0x4d90c0 State09_ReadyRoom_RenderCharacterPreview */
    virtual void RenderOverlay();               /* slot 15: 0x4d9ae0 State09_ReadyRoom_RenderStatusOverlay */
    /* slots 11/12/16/17 keep the base no-op defaults (census-confirmed) */

    u8 m_raw[0x78c - 4];                        /* field map not yet reconstructed */
};

class CState10Loading : public CGameState {     /* size 0x150; vtable 0x554018 (18 slots) */
public:
    virtual void OnKeyInput(int msg, int a, int b); /* 0x43e720 State10_Loading_HandleChatInput - promoted.
                                                 * CENSUS NOTE (2026-08-18): the vtable dump places 0x43e720
                                                 * at slot 6 (the OnMouseInput slot) with slot 5 = NoOp_A;
                                                 * this binding predates the dump - re-verify which slot the
                                                 * dispatcher really calls before relying on it. */
    virtual void OnExit();                      /* 0x43eff0 - promoted, State10_Loading.cpp */
    virtual void AppendChatLine();              /* slot 10: 0x442240 - the impl SHARED with state 03 */
    virtual void RenderOverlay();               /* slot 15: 0x442280 State10_Loading_Render */

    u8 m_raw[0x150 - 4];                        /* field map not yet reconstructed */
};

/* In-Battle: full vtable 0x5566d8 (18 slots - the shared base ABI, see
 * the CGameState slot 10-17 note; this state overrides all of 10-16). */
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
    virtual void AppendChatLine();              /* slot 10: 0x4c1b90 "ChatInputChar" - appends to the chat
                                                 * buffers, remaps '@#$%^&*' to emoticon codes 0x0a-0x10 */
    virtual void v11();                         /* slot 11: 0x4c1c90 TickCounters - small per-tick helper */
    virtual void v12();                         /* slot 12: 0x4c1d10 one-line delegate to RenderWeatherHazards */
    virtual void RenderLayerA();                /* slot 13: 0x4c1d30 ClearEffectTextures - per-frame Lock/zero/
                                                 * Unlock of the ~24 dynamic effect render-targets */
    virtual void RenderLayerB();                /* slot 14: 0x4c3020 State11_InBattle_Render (the D3D scene) */
    virtual void RenderOverlay();               /* slot 15: 0x4c8890 RenderChatLog - software-blit HUD chat
                                                 * overlay, color-coded by per-line message-type byte */
    virtual void v16();                         /* slot 16: 0x4caed0 RenderModeIcons */

    u8 m_raw[0x2408 - 4];                       /* chat history buffers live at +0x58b64 (sender, 9-byte
                                                 * stride) / +0x58bbe (text, 14-byte stride) RELATIVE TO
                                                 * g_clientContext, not this object - field map here is
                                                 * not yet reconstructed */
};

#endif /* GB_CXX_GAMESTATE_H */
