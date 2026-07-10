/* CState03GameRoomList - the lobby / game-room-list screen. Promoted:
 * RenderRoomCard (0x42a220) and its caller RenderRoomLabel (0x429810,
 * the vtable-slot-15 render hook). Evidence: PROTOCOL.md "Per-room grid
 * fields", docs/screens/03_game_room_list.md. See src/cxx/README.md.
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
void FUN_004ed9f0(int x, const char *text, int a, int b); /* text prep */
void FUN_004eadb0(void);                  /* text draw step */
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
    FUN_004ed9f0(0x14, numText, 3, 0xb);
    FUN_004eadb0();
    BlitRLESprite(yBand + 0x44, 0xffff);
    FUN_004eadb0();

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
