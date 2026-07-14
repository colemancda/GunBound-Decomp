/* The game-state transition spine - promoted from the raw C port
 * src/entry/ChangeGameState.c (0x4122f0). See src/cxx/README.md and
 * ARCHITECTURE.md "The game-state machine".
 *
 * The old state's OnExit (slot 8) and the new state's OnEnter (slot 7)
 * become real virtual calls here; the raw port's
 * (**(code **)(*obj + 0x20))() shape is exactly this dispatch with the
 * this-pointer dropped by the decompiler. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "GameState.h"

extern "C" {
extern int g_currentGameState;            /* 0x7934d0 */
extern unsigned int g_stateChangeInProgress; /* 0x793508 */
extern unsigned char g_stateChangeRequested; /* 0x7934d4 */
extern CGameState *g_gameStateVTableArray[16]; /* 0x5b33f8 (a.k.a. g_gameStateObjects);
                                                * declared char*[] in the C tree - the C++
                                                * layer types the elements for real */
extern int g_clientContext;
extern unsigned char DAT_00e55a45;
extern unsigned int DAT_00e9be98, DAT_00e9be9c, DAT_00e9c104;
extern unsigned int DAT_0056d108, DAT_007934d8;
extern unsigned char DAT_0067ec70;
extern unsigned char DAT_00e9be90[0x20], DAT_00e9c0fc[0x20]; /* the two active-object registries */
extern void *g_cursorTexture;
extern const char s_cursor_005524e8[];
extern const char s_normal_00552230[];

void SweepActiveObjectRegistry(void *registry);        /* active-object sweep (called twice, once per registry) */
void FUN_005098e0(int key);               /* destroy the UI panels registered under key */
void AppendPersistentButtonName(void *slot); /* per-slot register-arg index dropped by Ghidra */
void *FindPreloadedTextureByName(const char *name);
void ResolveNamedState(const char *cursorName);/* select the named cursor */
void FUN_005099b0(void);
void FUN_004f0320(void);
int __stdcall LoadSpriteSet(void *container, int key); /* .img name in EAX, .mp3 in EDI */
extern unsigned char DAT_00ea0e18[0x20];
/* the three out-of-line state constructors (Ghidra-flattened
 * __thiscall: storage in as first arg, object out) */
void *FUN_00443c20(void *storage);  /* CState07AvatarStore ctor */
void *State09_ReadyRoom_Construct(void *storage);  /* CState09ReadyRoom ctor */
void *FUN_004b3f90(void *storage);  /* CState11InBattle ctor */
}

/* The state-construction section of InitGame (0x40eaa0, interior) as
 * its own function: build all sixteen state objects - slots 0/15 are
 * plain base CGameState instances (vtable 0x553fb0, the null-object
 * pattern), the simple states are direct news whose inline field
 * inits live in the C++ default ctors, and the three big states go
 * through their out-of-line constructors - then preload the shared UI
 * sprite sets every screen's labels reference (button faces 500-800+,
 * the 0x259/0x25a scrollbar arrows, the 0x2bd-0x2bf buddy buttons,
 * the 0x2c6-0x2cb chat-window set...). Kept in InitGame's exact
 * order; slots 4, 8 and 12-14 are never constructed. */
void ConstructGameStates()
{
    g_gameStateVTableArray[0] = new CGameState();
    g_gameStateVTableArray[1] = new CState01Title();
    g_gameStateVTableArray[2] = new CState02ServerSelect();
    g_gameStateVTableArray[3] = new CState03GameRoomList();
    g_gameStateVTableArray[5] = new CState05Logo1();
    g_gameStateVTableArray[6] = new CState06Logo2();
    g_gameStateVTableArray[7] = (CGameState *)FUN_00443c20(operator new(0x34818));
    g_gameStateVTableArray[9] = (CGameState *)State09_ReadyRoom_Construct(operator new(0x78c));
    g_gameStateVTableArray[10] = new CState10Loading();
    g_gameStateVTableArray[11] = (CGameState *)FUN_004b3f90(operator new(0x2408));
    g_gameStateVTableArray[15] = new CGameState();
    static const int kSharedSpriteSets[] = {
        500, 600, 0x259, 0x25a, 0x262, 0x263, 0x264, 700,
        0x2bd, 0x2be, 0x2bf, 0x2c6, 0x2c7, 0x2c8, 0x2c9, 0x2ca, 0x2cb,
        800, 0x321, 0x322, 0x323, 900, 0x385, 0x38e, 0x398, 0,
    };
    for (int i = 0; i < (int)(sizeof(kSharedSpriteSets) / sizeof(int)); ++i) {
        LoadSpriteSet(&DAT_00ea0e18, kSharedSpriteSets[i]);
    }
}

/* 0x4122f0. Guarded transition: fire the old state's exit hook, tear
 * down per-screen UI (the key-10000 panel bucket and the active-object
 * sweeps), special-case QUIT (15) into PostQuitMessage, then reset the
 * nine persistent bottom-bar button-name slots and the cursor before
 * firing the new state's enter hook. A transition requested DURING the
 * enter hook (g_stateChangeRequested) suppresses the tail bookkeeping
 * so GameTick can dispatch the follow-up next frame. */
void ChangeGameState(int newStateId)
{
    if (newStateId == g_currentGameState || g_stateChangeInProgress != 0) {
        return;
    }
    DAT_00e55a45 = 0;
    g_gameStateVTableArray[g_currentGameState]->OnExit();
    SweepActiveObjectRegistry(DAT_00e9be90);
    DAT_00e9be98 = 0;
    DAT_00e9be9c = 0;
    DAT_00e9c104 = 0;
    SweepActiveObjectRegistry(DAT_00e9c0fc);
    FUN_005098e0(10000);
    if (newStateId == 0xf) {
        PostQuitMessage(0);
        return;
    }
    /* nine persistent button-name slots; the slot index rides in a
     * register the decompiler dropped, so the raw port shows nine
     * identical calls - kept literal */
    for (int i = 0; i < 9; ++i) {
        AppendPersistentButtonName((unsigned char *)&DAT_0067ec70 + g_clientContext);
    }
    g_cursorTexture = FindPreloadedTextureByName(s_cursor_005524e8);
    ResolveNamedState(s_normal_00552230);
    FUN_005099b0();
    g_gameStateVTableArray[newStateId]->OnEnter();
    g_currentGameState = newStateId;
    FUN_004f0320();
    if (g_stateChangeRequested != 0) {
        g_stateChangeRequested = 0;
        return;
    }
    DAT_0056d108 = 10;
    DAT_007934d8 = 0xffffffff;
}
