/* CState03GameRoomList - the lobby / game-room-list screen. Promoted:
 * RenderRoomCard (0x42a220), its caller RenderRoomLabel (0x429810, the
 * vtable-slot-15 render hook), and CreateButtons (0x42aba0, the bottom-bar
 * button setup). Evidence: PROTOCOL.md "Per-room grid fields",
 * docs/screens/03_game_room_list.md. See src/cxx/README.md.
 *
 * This is the first handler to read entirely through ClientContext.h's
 * room-grid accessors - the payoff of the arena reconstruction. The
 * sprite/blit helpers take their arguments in registers (Ghidra shows
 * them arg-less), so those calls stay in the raw external-call shape;
 * this is a renderer, so the value is readability, not byte-matching. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "GameState.h"
#include "ClientContext.h"

extern "C" {
extern unsigned int DAT_0079352c;         /* "sprites loaded" gate */
extern void *PTR_DAT_00551ecc;            /* the "%d" room-number format string */
extern const char s__s__3d__3d__005536b8[]; /* "%s[%3d/%3d]" scoreboard/banner format */
extern unsigned char g_localizedStringTable; /* localized-string table base */
extern CRITICAL_SECTION DAT_005a9068;     /* the value-guard lock */
int  FindSpriteFrame(void);               /* resolves the current frame (args in regs) */
void BlitSprite16bpp(int x, int y);       /* hardware blit (frame in regs) */
void BlitSpriteClipped(int frame);        /* software blit */
void BlitRLESprite(int x, int color);
int  _sprintf(char *buf, const char *fmt, ...);
void BlitSpriteText(int x, const char *text, int a, int b); /* text prep */
void SetClipRect(void);                  /* text draw step */
int  PeekPacketChecksumState(void);       /* decode one value-guarded field */
void *GetLocalizedString(void *table, int id);

/* Extra room-grid bytes RenderRoomCard reads that aren't in the six
 * documented fields: +0x449b4 (a per-room presence/avatar flag) and
 * +0x44986 (the info dword's byte 2 - fullness bits live here). */
}
static inline u8 *Ctx_roomPresence(int ctx) { return reinterpret_cast<u8 *>(ctx + 0x449b4); }
static inline u8 *Ctx_roomInfoByte2(int ctx) { return reinterpret_cast<u8 *>(ctx + 0x44986); }

/* 0x42a220. Draw one room card (slot 0-5, 3x2 grid). Column
 * (slot % 3) sets the x band; the row (slot / 3) picks the left/right
 * half of the sheet and the base sprite bank. The card's background
 * frame shifts +2 when this slot is the join-selection (+0x04) or +1
 * when it's the hover (+0x08). Then each grid field selects its own
 * sprite: presence icon, flagA/flagB counters, the map thumbnail
 * (map + fullness*11), the status/ready badge, the lock icon, the
 * room number text, and the fullness bar. Every blit is gated on the
 * sprites-loaded flag and a live FindSpriteFrame; hardware vs software
 * path chosen by the frame's +0x18 byte. */
void CState03GameRoomList::RenderRoomCard(int slot)
{
    int ctx = g_clientContext;
    char numText[128];

    int xBand, bankBase;
    if (slot / 3 == 0) {
        xBand = 0x18;
        bankBase = 1;
    } else {
        xBand = 0x144;
        bankBase = 4;
    }
    int yBand = (slot % 3) * 0x3c;

    /* card background: +2 selected, +1 hovered */
    if (m_selectedRoom == slot) {
        bankBase += 2;
    } else if (m_hoveredRoom == slot) {
        bankBase += 1;
    }
    int frame;
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) {
            BlitSprite16bpp(xBand, yBand + 0x3a);
        } else {
            BlitSpriteClipped(bankBase);
        }
    }

    /* presence/avatar icon (+0x449b4) */
    if (Ctx_roomPresence(ctx)[slot] != 0 && DAT_0079352c != 0 &&
        (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) {
            BlitSprite16bpp(xBand + 0xb1, yBand + 0x42);
        } else {
            BlitSpriteClipped(0xe);
        }
    }

    /* flagA counter (+0x4499c) */
    u8 flagA = Ctx_roomFlagA(ctx)[slot];
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) {
            BlitSprite16bpp(xBand + 0xc3, yBand + 0x46);
        } else {
            BlitSpriteClipped(flagA + 10);
        }
    }

    /* flagB counter (+0x449a2) */
    u8 flagB = Ctx_roomFlagB(ctx)[slot];
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) {
            BlitSprite16bpp(xBand + 0xd2, yBand + 0x46);
        } else {
            BlitSpriteClipped(flagB + 10);
        }
    }

    /* map thumbnail: map + (info.byte2 & 3)*11 (+0x4497c / +0x44986) */
    u8 infoB2 = Ctx_roomInfoByte2(ctx)[slot * 4];
    u8 mapId = Ctx_roomMap(ctx)[slot];
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) {
            BlitSprite16bpp(xBand + 0x6a, yBand + 0x5b);
        } else {
            BlitSpriteClipped((infoB2 & 3) * 0xb + mapId);
        }
    }

    /* status/ready badge (+0x449a8): 7 = in-progress, 8 = ready
     * (flagA == flagB), 9 = waiting */
    int badge = 9;
    if (Ctx_roomStatus(ctx)[slot] == 0) {
        if (Ctx_roomFlagA(ctx)[slot] == Ctx_roomFlagB(ctx)[slot]) {
            badge = 8;
        }
    } else {
        badge = 7;
    }
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) {
            BlitSprite16bpp(xBand + 0x13, yBand + 0x55);
        } else {
            BlitSpriteClipped(badge);
        }
    }

    /* lock icon (+0x449ae) */
    if (Ctx_roomLock(ctx)[slot] != 0) {
        if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
            if (*(char *)(frame + 0x18) == 1) {
                int lockX = (slot / 3 != 0 ? 0xea - 0xfa : 0xea) + xBand;
                BlitSprite16bpp(lockX, yBand + 0x52);
            } else {
                BlitSpriteClipped(0xf);
            }
        }
    }

    /* room number text (local room-card id + 1) */
    _sprintf(numText, (const char *)&PTR_DAT_00551ecc, Ctx_roomCardIds(ctx)[slot * 2] + 1);
    BlitSpriteText(0x14, numText, 3, 0xb);
    SetClipRect();
    BlitRLESprite(yBand + 0x44, 0xffff);
    SetClipRect();

    /* fullness bar: info bits 18-19 (+0x44984) */
    u32 info = Ctx_roomInfo(ctx)[slot];
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) {
            BlitSprite16bpp(xBand + 0xb1, yBand + 0x5b);
            return;
        }
        BlitSpriteClipped(((info >> 0x12) & 3) + 10);
    }
}

/* One value-guarded read: the anti-tamper field decode runs under the
 * shared guard lock (0x5a9068). */
static int ReadGuardedField()
{
    EnterCriticalSection(&DAT_005a9068);
    int v = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    return v;
}

/* 0x429810, vtable slot 15 - the lobby's per-frame render hook (GameTick
 * calls it). Draws the two background layers, the channel banner
 * ("<name>[<a>/<b>]"), the four localized column headers, then every
 * occupied room card except the client's own. Blit positions are
 * register-passed (Ghidra shows them arg-less), so like RenderRoomCard
 * this is a readability reconstruction, not byte-matched. */
void CState03GameRoomList::RenderRoomLabel()
{
    int ctx = g_clientContext;
    char text[128];
    int frame;

    /* background layer 1 */
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) BlitSprite16bpp(0, 0); /* y in reg */
        else BlitSpriteClipped(0);
    }
    /* background layer 2 (frame index at ctx+0x23344) */
    u16 bgFrame = *(u16 *)(ctx + 0x23344);
    if (DAT_0079352c != 0 && (frame = FindSpriteFrame()) != 0) {
        if (*(char *)(frame + 0x18) == 1) BlitSprite16bpp(0xac, 9);
        else BlitSpriteClipped(bgFrame);
    }

    /* channel banner, only when a channel name is set (ctx+0x23313). Both
     * counters are value-guarded; original arg order is (name, b, a). */
    if (*(char *)(ctx + 0x23313) != 0) {
        int a = ReadGuardedField();
        int b = ReadGuardedField();
        _sprintf(text, s__s__3d__3d__005536b8, ctx + 0x23313, b, a);
        BlitRLESprite(9, 0xfd0f);
    }
    BlitRLESprite(0x17, 0xffff);

    /* four localized column headers, each labelled with a guarded count.
     * The walk-to-NUL after the sprintf is the inlined string-length pass
     * the RLE text blitter consumes (headers 1/2/4 have it, header 3 does
     * not - preserved from the original). */
    int v;
    v = ReadGuardedField();
    _sprintf(text, (const char *)GetLocalizedString(&g_localizedStringTable, 20000), v);
    { char *p = text; while (*p) ++p; }
    BlitRLESprite(9, 0xffff);

    v = ReadGuardedField();
    _sprintf(text, (const char *)GetLocalizedString(&g_localizedStringTable, 0x4e21), v);
    { char *p = text; while (*p) ++p; }
    BlitRLESprite(0x16, 0xffff);

    v = ReadGuardedField();
    _sprintf(text, (const char *)GetLocalizedString(&g_localizedStringTable, 0x4e22), v);
    BlitRLESprite(0x27, 0x1f3b);

    v = ReadGuardedField();
    _sprintf(text, (const char *)GetLocalizedString(&g_localizedStringTable, 0x4e23), v);
    { char *p = text; while (*p) ++p; }
    BlitRLESprite(0x27, 0xe703);

    /* every occupied room card except the client's own (this+0x124); the
     * room-present flags are the 6-int array at ctx+0x4464c. */
    int ownRoom = *(int *)((char *)this + 0x124);
    for (int slot = 0; slot < 6; ++slot) {
        if (*(int *)(ctx + 0x4464c + slot * 4) != 0 && slot != ownRoom) {
            RenderRoomCard(slot);
        }
    }
}

/* --- CreateButtons (0x42aba0) --------------------------------------- */
extern "C" {
extern unsigned char DAT_00e9be90[0x20];    /* the button-widget registry - sized, see globals.c */
void CreateButtonWidget(void *registry, int a, int id, int spriteBase,
                        const char *name, int x, int y, int w, int h,
                        int enabled, int b);
void RefreshGameRoomListControls(void);                     /* post-build fixup (unnamed) */
extern const char s_b_gamelist_exit_0055379c[];
extern const char s_b_gamelist_buddy_00553788[];
extern const char s_b_gamelist_ranking_00553774[];
extern const char s_b_gamelist_avatar_00553760[];
extern const char s_b_gamelist_create_0055374c[];
extern const char s_b_gamelist_join_0055373c[];
extern const char s_b_gamelist_viewall_00553728[];
extern const char s_b_gamelist_wait_00553718[];
extern const char s_b_gamelist_prev_00553708[];
extern const char s_b_gamelist_next_005536f8[];
extern const char s_b_gamelist_friend_005536e4[];
extern const char s_b_gamelist_directgo_005536d0[];
}

/* 0x42aba0 - create the lobby's 12 bottom-bar buttons: the six primary
 * actions along y=0x227 (exit/buddy/ranking/avatar/create/join) and six
 * secondary/navigation buttons along y=0xf6 (viewall/wait/prev/next/
 * friend/directgo). The command id is the raw slot index; the sprite-set
 * ids were preloaded by OnEnter. void(void) in the original. */
void CState03GameRoomList::CreateButtons()
{
    struct Btn { int id; int spriteBase; const char *name; int x, y, w, h; };
    static const Btn buttons[] = {
        { 0x0, 1000,  s_b_gamelist_exit_0055379c,     0x28,  0x227, 0x6b, 0x2d },
        { 0x1, 0x3e9, s_b_gamelist_buddy_00553788,    0xa3,  0x227, 0x6b, 0x2d },
        { 0x2, 0x3ea, s_b_gamelist_ranking_00553774,  0x11e, 0x227, 0x6b, 0x2d },
        { 0x3, 0x3eb, s_b_gamelist_avatar_00553760,   0x199, 0x227, 0x6b, 0x2d },
        { 0x4, 0x3ec, s_b_gamelist_create_0055374c,   0x214, 0x227, 0x6b, 0x2d },
        { 0x5, 0x3ed, s_b_gamelist_join_0055373c,     0x28f, 0x227, 0x6b, 0x2d },
        { 0xa, 0x44c, s_b_gamelist_viewall_00553728,  0x2a,  0xf6,  0x51, 0x21 },
        { 0xb, 0x44d, s_b_gamelist_wait_00553718,     0x83,  0xf6,  0x51, 0x21 },
        { 0xc, 0x44e, s_b_gamelist_prev_00553708,     0xf2,  0xf6,  0x31, 0x21 },
        { 0xd, 0x44f, s_b_gamelist_next_005536f8,     0x124, 0xf6,  0x31, 0x21 },
        { 0xe, 0x450, s_b_gamelist_friend_005536e4,   0x173, 0xf6,  0x51, 0x21 },
        { 0xf, 0x451, s_b_gamelist_directgo_005536d0, 0x1cc, 0xf6,  0x51, 0x21 },
    };
    for (int i = 0; i < 12; ++i) {
        const Btn &b = buttons[i];
        CreateButtonWidget(&DAT_00e9be90, 0, b.id, b.spriteBase, b.name,
                           b.x, b.y, b.w, b.h, 0, 0);
    }
    RefreshGameRoomListControls();
}
