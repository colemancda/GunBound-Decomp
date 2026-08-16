/* Wire structures - PLAN.md Phase 4. POD reconstructions of the
 * byte-level layouts PROTOCOL.md documents as confirmed; sizes and
 * offsets are machine-asserted in cxx_selftest.cpp. Packed: these are
 * exact wire images, not aligned in-memory structs.
 *
 * Deliberately NOT here: the DECODED server-list and room-slot data -
 * both are structure-of-arrays layouts inside g_clientContext (see
 * docs/screens/02_server_select.md "The server list" and
 * ARCHITECTURE.md "RoomPlayerSlot"), not wire structs; and the
 * channel-1 header, which is just ProcessPacket's three parameters.
 * The wire RECORDS those SoAs are parsed from are here (0x1102, 0x2103).
 *
 * Variable-length records (0x1102's two length-prefixed strings, 0x2103's
 * room name) are modeled as their fixed head and fixed tail with the
 * strings between - a single struct would misstate the layout. */
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

/* ---------------------------------------------------------------- */
/* Channel 1 wire records                                            */
/* ---------------------------------------------------------------- */

/* Opcode 0x1102 - one server/channel directory entry.  Variable length
 * (two length-prefixed, NOT NUL-terminated strings), so it is modeled as
 * a fixed head, the two strings, then a fixed 13-byte tail:
 *
 *     GbServerListEntryHead   (4 bytes)
 *     char name[head.nameLen]
 *     u8   descLen
 *     char desc[descLen]
 *     GbServerListEntryTail   (13 bytes)
 *
 * Confirmed against the parse loop in State02_ServerSelect_ProcessPacket.c
 * (the `htons(*(u_short *)(pbVar19 + 4))` tail read and its `pbVar19 + 0xd`
 * advance), which matches PROTOCOL.md's "Opcode 0x1102" field list. */
struct GbServerListEntryHead {
    u16 serverId;      /* +0x00 */
    u8  regionOrType;  /* +0x02: forced to 3 when the tail's onlineFlag is 0 */
    u8  nameLen;       /* +0x03: length of the name that follows */
};

struct GbServerListEntryTail {
    u32 serverIp;       /* +0x00: packed IPv4, formatted "%d.%d.%d.%d" at connect */
    u16 portBE;         /* +0x04: network byte order - client stores htons() of it */
    u16 unk06;          /* +0x06: raw copy, no byte swap */
    u16 currentPlayers; /* +0x08: compared against maxCapacity for the "full" test */
    u16 maxCapacity;    /* +0x0a */
    u8  onlineFlag;     /* +0x0c: 0 = offline/unavailable */
};

/* Opcode 0x2103 (payload[0] == 0, the bulk room-grid fill) - the fixed
 * per-room-slot tail that follows each entry's u16 roomNumber + length-
 * prefixed name.  Confirmed against State03_GameRoomList_ProcessPacket.c's
 * store sequence (+0x4497c / +0x44984 / +0x4499c / +0x449a2 / +0x449a8 /
 * +0x449ae off g_clientContext) and its `puVar11 + 9` advance. */
struct GbRoomGridEntryTail {
    u8  map;    /* +0x00 -> ctx+0x4497c: mode/map icon */
    u32 info;   /* +0x01 -> ctx+0x44984: bits 18-19 = fullness gauge */
    u8  flagA;  /* +0x05 -> ctx+0x4499c: small icon A */
    u8  flagB;  /* +0x06 -> ctx+0x449a2: small icon B */
    u8  status; /* +0x07 -> ctx+0x449a8: status icon 7/8/9 */
    u8  lock;   /* +0x08 -> ctx+0x449ae: private/password padlock */
};

/* Opcode 0x2110 - join room (outgoing).  Fixed 8 bytes, identical across
 * all three emitters (PROTOCOL.md "Opcode 0x2110"); unlike the room-create
 * request this carries no strings. */
struct GbJoinRoomRequest {
    u16 opcode;      /* +0x00: 0x2110 */
    u16 roomNumber;  /* +0x02 */
    u32 payload;     /* +0x04: fixed field, not a variable-length name */
};

/* ---------------------------------------------------------------- */
/* Channel 2 action payloads (wire offset = 0x21 + member offset)     */
/* ---------------------------------------------------------------- */

/* Actions 0x8402 (aim relay) and 0x8406 (its alternate trigger) - the two
 * really do share one payload shape, which PROTOCOL.md asserted from the
 * send side; these offsets are the receive side, read identically in both
 * arms of State11_InBattle_ProcessBattleAction.c. */
struct GbAimRelayPayload {   /* wire offset = 0x21 + member offset */
    u16 angle;   /* +0x21: the mobile's +0x243 guard cell */
    u16 power;   /* +0x23: the mobile's +0x2cc guard cell */
    u8  flag;    /* +0x25: relayed as (flag == 1) */
};

/* Action 0x8006 - weapon-fire feedback sound.  Same first two fields as the
 * aim relay, then a 3-way variant selector and a flag; the selector picks
 * the bfire1/bfire2/bifire sample. */
struct GbFireFeedbackSoundPayload {
    u16 field21;  /* +0x21 */
    u16 field23;  /* +0x23 */
    u8  variant;  /* +0x25: 0/1/2 - drives the two SetGuardedBool tests */
    u8  flag;     /* +0x26: relayed as (flag == 1) */
};

/* Action 0x8500 - position relay.  Note the one-byte shift versus the aim
 * relay: this action's fields start at +0x22, not +0x21. */
struct GbPositionRelayPayload {
    u8  pad21;   /* +0x21: not read by the handler */
    u16 field22; /* +0x22 */
    u16 field24; /* +0x24 */
    u8  flag;    /* +0x26: relayed as (flag == 1) */
};

/* Action 0xc300 - turn/round start.  BeginNewTurn is handed `payload + 1`
 * (wire +0x22) and reads exactly these three fields; the turn counter seeds
 * g_clientContext+0xeba98 and the two shot parameters seed +0x5af88 and
 * +0x5b1ac - the pair every projectile spawner reads back. */
struct GbTurnStartPayload {
    u8  pad21;        /* +0x21: not read by BeginNewTurn */
    u16 turnCounter;  /* +0x22 -> ctx+0xeba98 (then incremented) */
    u8  shotParamA;   /* +0x24 -> ctx+0x5af88 */
    s16 shotParamB;   /* +0x25 -> ctx+0x5b1ac (read as a signed short) */
};

/* Action 0xc301 - turn timer + battle setup.  The setup block is EIGHT
 * 32-BIT WORDS (32 bytes), not the "8 shorts / 16 bytes" PROTOCOL.md used
 * to state: all three copy loops that fill the In-Battle object's +0x2302
 * array (State10_Loading_ProcessBattleAction.c, and State11's own 0xc301
 * and 0xc308 arms) iterate 8 times over `undefined4 *`.  Corrected in
 * PROTOCOL.md alongside this struct. */
struct GbTurnSetupPayload {
    u8  pad21;         /* +0x21: not read */
    u16 turnTimerMs;   /* +0x22 -> InBattle state +0x10a4; 60000 / 0xffff are sentinels */
    u32 setup[8];      /* +0x24..+0x43 -> InBattle state +0x2302 */
};

/* Action 0xc308 - mid-match update of the same setup block, without the
 * turn-timer write; its copy starts at the payload's first byte. */
struct GbWindUpdatePayload {
    u32 setup[8];      /* +0x21..+0x40 -> InBattle state +0x2302 */
};

#pragma pack(pop)

typedef unsigned int u32_check_protocol[(sizeof(u32) == 4) ? 1 : -1];

#endif /* GB_CXX_PROTOCOL_H */
