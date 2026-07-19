/* CState02ServerSelect - the server/channel select screen. Promoted
 * from src/state_machine/State02_ServerSelect_OnEnter.c (0x4e14b0).
 * Evidence: docs/screens/02_server_select.md. See src/cxx/README.md. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <string.h>
#include "GameState.h"
#include "Widget.h"
#include "ActiveObjects.h"

class CWorldListPanel;

extern "C" {
/* PlayMusicTrack's real signature - see State01_Title.cpp's header for
 * the full fix note (2026-07-13): the old `int PlayMusicTrack(int
 * trackId)` declaration here mismatched the real 2-argument cdecl
 * function at 0x4eea30 and would have silently read garbage for the
 * missing trackName argument. */
unsigned int PlayMusicTrack(unsigned int status, const char *trackName);
/* FIXED (2026-07-15): was declared without extern "C" - Panel.cpp's real
 * definition IS extern "C" (`extern "C" CWorldListPanel *
 * BuildWorldListPanel(void *manager)`), so this mismatched C++-mangled
 * declaration never resolved to it at link time. Also LoadSpriteSet was
 * declared __stdcall/2-arg (stale, pre-dating its cdecl/3-arg fix
 * elsewhere - see State05_Logo1.cpp's own header) and FUN_00402020 was
 * declared zero-arg/non-fastcall (real: __fastcall, 1 arg via ECX,
 * confirmed via angr disassembly of this file's own OnTick call site:
 * `mov ecx,0xe53e88; call 0x402020` - the literal is &DAT_00e53e88,
 * already declared correctly below). */
CWorldListPanel *BuildWorldListPanel(void *manager);
int LoadSpriteSet(void *container, int key, const char *imgName);
extern unsigned char DAT_00ea0e18[0x20];
extern int g_clientContext;
extern unsigned char DAT_0067ec70;
extern unsigned char g_uiPanelManager[0x1c];
void AppendPersistentButtonName(void *slot);
/* the flat 80-byte ButtonWidget factory (separate system, PLAN.md
 * Phase 1.6): (registry, ?, id, spriteBase, name, x, y, w, h,
 * enabledFlag, ?) */
void CreateButtonWidget(void *registry, int a, int id, int spriteBase,
                        const char *name, int x, int y, int w, int h,
                        int enabled, int b);
extern unsigned char DAT_00e9be90[0x20]; /* flat-ButtonWidget registry - sized, see globals.c */
extern const char s_b_server_exitgame_00557144[];
extern const char s_b_server_buddygame_00557170[];
extern const char s_b_server_choiceserver_00557158[];
void BeginServerConnect(void *target, int a, int connCtxBase);
extern unsigned char DAT_005b2ad0[0x80]; /* broker IP - sized, see globals.c */
extern unsigned int DAT_005b33e8;        /* broker Port - sized, see globals.c */
extern int DAT_005b2b64;                /* server count hint for the scroll seed */
extern unsigned int DAT_007934e4;       /* shared EDIT-control singleton (+8 = live flag) */
extern unsigned int DAT_007934e8;       /* double-buffered connection context */
extern unsigned int DAT_007934f4;       /* outgoing packet buffer base */
extern unsigned int DAT_007934f0;       /* per-connection context base */
void FUN_00405ba0(void);
extern unsigned int DAT_007934ec;       /* the other half of the double-buffered context */
extern unsigned int g_serverWaitTicks;
extern unsigned int DAT_00e9be94;
extern const char s_active_00551e58[];
extern const char s_ready_00551e80[];
void InvokeWidget(int widgetId, int enabled);
void ShowErrorDialog(int mode);
void SendOutgoingPacket(int channelCtx);  /* flush/send the pending channel-1 packet */
char PeekPacketChecksumBool(void);                /* mode check gating the page-offset source */
int SetGuardedBool(int value, int guardPtr);
void FUN_004d24f0(void);
int __fastcall FUN_00402020(int param_1); /* per-slot blink randomizer */
void FUN_00401650(int *slot);            /* flat-ButtonWidget per-slot destroy */
extern unsigned char DAT_0067ec74;      /* persistent button-name arena */
extern unsigned char DAT_0069ec74;
void FUN_00404410(void *arg);
extern unsigned char DAT_00e53e88[0xf28]; /* sized, see globals.c */
}

/* 0x4e14b0. Load the screen's sprite sets (10000/10001 + button faces
 * 1000-0x3ea and the 0x44c/0x44d tab faces), reset three persistent
 * button-name slots, create the three flat bottom-bar buttons
 * (exitgame / buddygame / choiceserver - the last starts disabled),
 * wipe the entire 16-entry server SoA arena at g_clientContext+0x3f808,
 * reset the state fields (uiDirty on, view mode All, scroll seeded
 * from DAT_005b2b64/16 or the previous server id/16), build the world
 * list panel, kick the async broker connect, tear down a leftover
 * connected socket from a previous session, start the channel music,
 * and reset the chat-log side. The SoA wipe uses memsets where the
 * original unrolls dword stores - same effect, byte-polish deferred
 * until the arena becomes a real struct. */
void CState02ServerSelect::OnEnter()
{
    /* image names recovered from the raw-C sibling
     * State02_ServerSelect_OnEnter.c, already verified/exercised on the
     * bring-up path. */
    LoadSpriteSet(&DAT_00ea0e18, 10000, "server_back.img");
    LoadSpriteSet(&DAT_00ea0e18, 0x2711, "server_list.img");
    LoadSpriteSet(&DAT_00ea0e18, 1000, "b_server_exitgame.img");
    LoadSpriteSet(&DAT_00ea0e18, 0x3e9, "b_server_buddygame.img");
    LoadSpriteSet(&DAT_00ea0e18, 0x3ea, "b_server_choiceserver.img");
    LoadSpriteSet(&DAT_00ea0e18, 0x44c, "b_server_all.img");
    LoadSpriteSet(&DAT_00ea0e18, 0x44d, "b_server_friend.img");
    for (int i = 0; i < 3; ++i) {
        AppendPersistentButtonName((unsigned char *)&DAT_0067ec70 + g_clientContext);
    }
    CreateButtonWidget(&DAT_00e9be90, 0, 0, 1000, s_b_server_exitgame_00557144,
                       0x28, 0x227, 0x6b, 0x2d, 1, 0);
    CreateButtonWidget(&DAT_00e9be90, 0, 1, 0x3e9, s_b_server_buddygame_00557170,
                       0xa3, 0x227, 0x6b, 0x2d, 1, 0);
    CreateButtonWidget(&DAT_00e9be90, 0, 2, 0x3ea, s_b_server_choiceserver_00557158,
                       0x199, 0x227, 0x6b, 0x2d, 0, 0);

    unsigned char *ctx = (unsigned char *)g_clientContext;
    m_highlightedSlot = -1;
    ctx[0x3f808] = 0;                       /* count */
    memset(ctx + 0x3f809, 0, 0x10);         /* onlineFlag[16] */
    memset(ctx + 0x3f81a, 0, 0x20);         /* serverId[16] */
    memset(ctx + 0x3f84a, 0, 0x800);        /* name[16][128] */
    memset(ctx + 0x4004a, 0, 0x1000);       /* desc[16][256] */
    memset(ctx + 0x4104a, 0, 0x40);         /* serverIp[16] */
    memset(ctx + 0x4108a, 0, 0x90);         /* port/unk2/players/maxCap[16] + animState */

    m_connecting = 0;
    m_sendHandshake = 0;
    m_uiDirty = 1;
    m_selectedSlot = -1;
    m_viewMode = 0;
    unsigned int page;
    if ((int)DAT_005b2b64 < 1) {
        int prev = *(int *)(ctx + 0x3f804);
        page = prev < 1 ? 0 : (unsigned int)((prev + ((prev >> 31) & 0xf)) >> 4);
    } else {
        page = (unsigned int)DAT_005b2b64 >> 4;
    }
    m_scrollA = (int)page;
    m_scrollOffset = (int)page;
    m_unk1c = 0;
    BuildWorldListPanel(&g_uiPanelManager);
    BeginServerConnect(&DAT_005b2ad0, DAT_005b33e8, (int)DAT_007934f0);
    m_wantInitialList = 1;
    *(unsigned char *)(DAT_007934e4 + 8) = 1;   /* show the shared EDIT overlay */
    /* leftover connected socket from a previous session: tear it down */
    if (*(char *)(DAT_007934e8 + 0x84e5) != 0) {
        int conn = *(int *)(DAT_007934e8 + 0x84e0);
        if (conn != 0) {
            *(int *)(conn + 0x22c) = 1;
            if (*(unsigned int *)(conn + 0x24) != 0xffffffff) {
                closesocket(*(SOCKET *)(conn + 0x24));
            }
            *(int *)(conn + 0x24) = -1;
            *(unsigned char *)(conn + 0x22a) = 0;
            *(unsigned char *)(DAT_007934e8 + 0x84e5) = 0;
        }
    }
    m_tickCounter = 0;
    PlayMusicTrack(1, "channel.mp3");
    bool haveBuffer = DAT_007934f4 != 0;
    m_inputEnabled = 0;
    *(int *)(ctx + 0x3f804) = -1;
    if (haveBuffer) {
        FUN_00405ba0();
        return;
    }
    FUN_00404410(&DAT_00e53e88);
}

/* 0x4e17f0. Destroy the screen's nine sprite buckets - for each
 * button-face base 1000/1001/1002, the base+9000, base and base+100
 * sets (the original inlines the same bucket walk nine times) - then
 * destroy the registered flat buttons, wipe the persistent
 * button-name arenas, and tear down the connection socket exactly as
 * OnEnter does for leftovers (this one off DAT_007934f0). */
void CState02ServerSelect::OnExit()
{
    for (unsigned int base = 1000; base < 1003; ++base) {
        ActiveObjects_DestroyBucket(base + 9000);
        ActiveObjects_DestroyBucket(base);
        ActiveObjects_DestroyBucket(base + 100);
    }
    int *buttonCount = (int *)((unsigned char *)&DAT_0067ec70 + g_clientContext);
    for (int i = 0; i < *buttonCount; ++i) {
        /* FIXED (2026-07-13): FUN_00401650 takes the per-slot record
         * pointer explicitly now - was silently dropped here (see that
         * file's own header for the objdump evidence). Slot i lives at
         * buttonCount+0x20004+i*0x18. */
        FUN_00401650((int *)((unsigned char *)buttonCount + 0x20004 + i * 0x18));
    }
    *buttonCount = 0;
    memset((unsigned char *)&DAT_0067ec74 + g_clientContext, 0, 0x20000);
    memset((unsigned char *)&DAT_0069ec74 + g_clientContext, 0, 0x6000);
    int conn = *(int *)(DAT_007934f0 + 0x84e0);
    if (conn != 0) {
        *(int *)(conn + 0x22c) = 1;
        if (*(unsigned int *)(conn + 0x24) != 0xffffffff) {
            closesocket(*(SOCKET *)(conn + 0x24));
        }
        *(int *)(conn + 0x24) = -1;
        *(unsigned char *)(conn + 0x22a) = 0;
        *(unsigned char *)(DAT_007934f0 + 0x84e5) = 0;
    }
}

/* Reflect the local player record onto the flat-registry connect
 * button: "active" while the record flag is set, else "ready"
 * (entries keyed 0 and 1, state 3/-1 only) - the same walk the
 * WorldListPanel handlers repeat; literal pending Phase 1.6. */
static void ConnectButtonFromPlayerRecord()
{
    int *rec;
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0 &&
        (rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), rec[2] == 0) &&
        (rec[9] == 3 || rec[9] == -1)) {
        ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(
            (char)rec[0x13] == 1 ? s_active_00551e58 : s_ready_00551e80);
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
        rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
        unsigned int k = (unsigned int)rec[2];
        while (k < 2) {
            if (k == 1) {
                if (rec[9] == 3 || rec[9] == -1) {
                    ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(
                        (char)rec[0x13] == 1 ? s_active_00551e58 : s_ready_00551e80);
                }
                break;
            }
            rec = (int *)rec[4];
            k = (unsigned int)rec[2];
        }
    }
}

/* 0x4e1960 (State02_ServerSelect_OnTick) - the per-frame tick, vtable slot 9. Four
 * jobs: (1) resolve a finished connect attempt - failure resets the
 * connect button and pops ShowErrorDialog(0), success arms the
 * handshake; (2) send the 0x1000 handshake the tick after connecting;
 * (3) once connected, send the initial 0x1100 page request OnEnter
 * armed (page = the saved scroll offset, or the channel-derived value
 * when PeekPacketChecksumBool says so) after clearing the per-slot errors;
 * (4) roll each listed server's blink animState. */
void CState02ServerSelect::OnTick()
{
    unsigned char *cfg = (unsigned char *)DAT_007934ec;
    ++m_tickCounter;
    if (m_connecting != 0 && *(char *)(cfg + 0x84e4) == 0) {
        if (*(char *)(cfg + 0x84e5) == 0) {
            g_serverWaitTicks = 0xffffffff;
            ConnectButtonFromPlayerRecord();
            InvokeWidget(2, m_highlightedSlot != -1);
            ShowErrorDialog(0);
            m_uiDirty = 1;
            if (PeekPacketChecksumBool() != 0) {
                SetGuardedBool(0,GB_GUARD_UNRECOVERED);
            }
            FUN_004d24f0();
            cfg = (unsigned char *)DAT_007934ec;
        } else {
            m_sendHandshake = 1;
        }
        m_connecting = 0;
    }
    if (m_sendHandshake != 0) {
        *(unsigned short *)(cfg + 0x4d4) = 0x1000;
        *(int *)(cfg + 0x44d0) = 6;
        SendOutgoingPacket((int)cfg);
        m_sendHandshake = 0;
    }
    unsigned char *ctx = (unsigned char *)DAT_007934f0;
    if (m_wantInitialList != 0 && *(char *)(ctx + 0x84e5) != 0) {
        m_wantInitialList = 0;
        for (int i = 0; i < 16; ++i) {
            m_slotError[i] = 0;
        }
        *(int *)(ctx + 0x44d0) = 6;
        *(unsigned short *)(ctx + 0x4d4) = 0x1100;
        *(unsigned char *)(ctx + 0x4d6) = 0;
        int cur = *(int *)(ctx + 0x44d0);
        *(int *)(ctx + 0x44d0) = cur + 1;
        *(unsigned char *)(ctx + 0x4d1 + cur) = 0;
        *(int *)(ctx + 0x44d0) += 1;
        if (PeekPacketChecksumBool() == 0) {
            *(unsigned short *)(ctx + 0x4d0 + *(int *)(ctx + 0x44d0)) =
                (unsigned short)m_scrollOffset;
        } else {
            *(unsigned short *)(ctx + 0x4d0 + *(int *)(ctx + 0x44d0)) =
                (unsigned short)(*(unsigned short *)((unsigned char *)g_clientContext + 0x3b96b) >> 4);
        }
        *(int *)(ctx + 0x44d0) += 2;
        SendOutgoingPacket((int)ctx);
    }
    unsigned char *gctx = (unsigned char *)g_clientContext;
    int count = (int)gctx[0x3f808];
    for (int i = 0; i < count; ++i) {
        gctx[0x4110a + i] = (unsigned char)FUN_00402020((int)&DAT_00e53e88);
    }
}
