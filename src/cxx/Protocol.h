/* Wire structures - PLAN.md Phase 4. POD reconstructions of the
 * byte-level layouts PROTOCOL.md documents as confirmed; sizes and
 * offsets are machine-asserted in cxx_selftest.cpp. Packed: these are
 * exact wire images, not aligned in-memory structs.
 *
 * Deliberately NOT here: the server-list and room-slot data - both are
 * structure-of-arrays layouts inside g_clientContext (see
 * docs/screens/02_server_select.md "The server list" and
 * ARCHITECTURE.md "RoomPlayerSlot"), not wire structs; and the
 * channel-1 header, which is just ProcessPacket's three parameters. */
#ifndef GB_CXX_PROTOCOL_H
#define GB_CXX_PROTOCOL_H

#include "gb_common.h"

#pragma pack(push, 1)

/* Channel 2 ("battle action") fixed header - precedes every action's
 * payload on every screen implementing the channel (PROTOCOL.md
 * "Channel 2 header"). */
struct GbActionHeader {
    u16 unk00;        /* +0x00: not yet decoded */
    u16 actionType;   /* +0x02: the dispatch value (ProcessBattleAction's switch) */
    u8  unk04;        /* +0x04 */
    u8  sourceSlot;   /* +0x05: source player slot, validated 0-7 */
    u8  unk06[0x1b];  /* +0x06..+0x20: not yet decoded */
    /* +0x21: action-specific payload begins */
};

/* Action 0x8403 (Fire) payload - header-relative offsets from
 * PROTOCOL.md's field-by-field confirmation. The eight shorts at
 * +0x2c are the server-resolved shot block (the client sends only
 * angle+power; trajectories are server-computed). */
struct GbFirePayload {            /* wire offset = 0x21 + member offset */
    u16 lead;         /* +0x21: queued first, relayed verbatim */
    u16 angle;        /* +0x23: angle-like; fed to EncodeChecksumState */
    u8  flag25;       /* +0x25 */
    u8  flag26;       /* +0x26: drives SetGuardedBool(x == 1,GB_GUARD_UNRECOVERED) */
    u16 num27;        /* +0x27 */
    u16 num29;        /* +0x29 */
    u8  firedByte;    /* +0x2b: copied into the firer's record, not relayed */
    u16 shotData[8];  /* +0x2c..+0x3b: the server-resolved shot block */
    u8  flag3c;       /* +0x3c */
    /* +0x3d: trailing data (consumed by FUN_0043d780) */
};

/* Avatar Store opcode 0x6002 - the in-memory inventory item the handler
 * decodes each wire entry into (0x9c bytes, array at DAT_005b3484+0x44be8;
 * ARCHITECTURE.md "InventoryItem"). Field roles decoded (2026) from
 * RenderInventoryItemDetail (0x44b900), the owned-item detail renderer.
 * Wire entry = this same 0x1c-byte fixed head then a length-prefixed blob:
 * the wire time_t at +0x10 is parsed to y/m/d (not stored raw), and the blob
 * (length byte at wire +0x18, bytes from +0x19) lands at +0x1c. */
struct GbInventoryItem {
    u32  id0;          /* +0x00: item id; tracked as running min/max, checksum-fed */
    char name[12];     /* +0x04: item NAME (inline ASCII; drawn in the detail panel) */
    u16  pad10;        /* +0x10: the wire time_t low half; not stored (parsed to y/m/d) */
    u16  expYear;      /* +0x12: tm_year + 1900 (from the wire time_t at +0x10) */
    u8   expMonth;     /* +0x14: tm_mon + 1 */
    u8   expDay;       /* +0x15: tm_mday */
    u16  pad16;        /* +0x16 */
    u32  displayField; /* +0x18: packed display attrs -
                        *   bits 0-14 : icon sprite id -> "%05d.img" (& 0x7fff)
                        *   bit 8      : rarity/color select (name text color)
                        *   bit 15     : gender/variant
                        *   bits 16-19 : category (0-3; selects an icon-suffix sprite) */
    char description[0x80]; /* +0x1c: item DESCRIPTION text (the "blob"; wrapped
                        * and drawn via RenderWrappedText). Length-prefixed on the
                        * wire (byte at wire +0x18, up to 0x80 bytes). */
};

#pragma pack(pop)

typedef unsigned int u32_check_protocol[(sizeof(u32) == 4) ? 1 : -1];

#endif /* GB_CXX_PROTOCOL_H */
