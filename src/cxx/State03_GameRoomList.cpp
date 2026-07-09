/* CState03GameRoomList - the lobby / game-room-list screen. Promoted
 * from src/state_machine/RenderRoomCard.c (0x42a220). Evidence:
 * PROTOCOL.md "Per-room grid fields", docs/screens/03_game_room_list.md.
 * See src/cxx/README.md.
 *
 * This is the first handler to read entirely through ClientContext.h's
 * room-grid accessors - the payoff of the arena reconstruction. The
 * sprite/blit helpers take their arguments in registers (Ghidra shows
 * them arg-less), so those calls stay in the raw external-call shape;
 * this is a renderer, so the value is readability, not byte-matching. */
#include "GameState.h"
#include "ClientContext.h"

extern "C" {
extern unsigned int DAT_0079352c;         /* "sprites loaded" gate */
extern void *PTR_DAT_00551ecc;            /* the "%d" room-number format string */
int  FindSpriteFrame(void);               /* resolves the current frame (args in regs) */
void BlitSprite16bpp(int x, int y);       /* hardware blit (frame in regs) */
void BlitSpriteClipped(int frame);        /* software blit */
void BlitRLESprite(int x, int color);
int  _sprintf(char *buf, const char *fmt, int arg);
void FUN_004ed9f0(int x, const char *text, int a, int b); /* text prep */
void FUN_004eadb0(void);                  /* text draw step */

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
