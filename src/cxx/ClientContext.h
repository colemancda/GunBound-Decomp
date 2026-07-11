/* g_clientContext accessors - PLAN.md's "per-connection client context"
 * blob. This is a huge per-connection arena (the whole g_clientContext
 * region); rather than one giant struct, each subsystem gets a typed
 * view of the slice it owns, overlaid at a base pointer at the confirmed
 * absolute offsets. The server-list SoA is documented in
 * docs/screens/02_server_select.md.
 *
 * The SoA is an exact byte image of the arena region, so it is packed
 * and its internal offsets are machine-asserted in cxx_selftest.cpp
 * (they must equal the documented abs-offset minus 0x3f808). */
#ifndef GB_CXX_CLIENTCONTEXT_H
#define GB_CXX_CLIENTCONTEXT_H

#include "gb_common.h"
#include "ValueGuard.h"

extern "C" int g_clientContext;

#pragma pack(push, 1)
/* The 16-entry server list (structure-of-arrays), based at
 * g_clientContext+0x3f808. Overlay via ServerList_of(ctx). */
struct ServerListSoA {
    u8  count;                /* +0x000 (abs +0x3f808) */
    u8  onlineFlag[16];       /* +0x001 (abs +0x3f809) */
    u8  pad11;                /* +0x011 - 1-byte gap before serverId */
    u16 serverId[16];         /* +0x012 (abs +0x3f81a) */
    u8  regionOrType[16];     /* +0x032 (abs +0x3f83a) */
    char name[16][128];       /* +0x042 (abs +0x3f84a) */
    char desc[16][256];       /* +0x842 (abs +0x4004a) */
    u32 serverIp[16];         /* +0x1842 (abs +0x4104a) */
    u16 port[16];             /* +0x1882 (abs +0x4108a) */
    u16 unknownField2[16];    /* +0x18a2 (abs +0x410aa) */
    u16 currentPlayers[16];   /* +0x18c2 (abs +0x410ca) */
    u16 maxCapacity[16];      /* +0x18e2 (abs +0x410ea) - BIG-ENDIAN (network
                               * order): live read of slot 0 = 100 stored as
                               * bytes 00 64, i.e. a little-endian u16 read
                               * yields 0x6400/25600. Read as big-endian, or
                               * byte-swap, to get the real cap. (currentPlayers
                               * was 0 in every sample, so its order is still
                               * unconfirmed - assume the same.) */
    u8  animState[16];        /* +0x1902 (abs +0x4110a) */
};
#pragma pack(pop)

inline ServerListSoA *ServerList_of(int ctx)
{
    return reinterpret_cast<ServerListSoA *>(ctx + 0x3f808);
}

/* Other confirmed g_clientContext fields ServerSelect touches, by
 * absolute offset (not part of the SoA above). */
inline int  &Ctx_selectedServerId(int ctx) { return *reinterpret_cast<int *>(ctx + 0x3f804); }
inline char *Ctx_currentServerName(int ctx) { return reinterpret_cast<char *>(ctx + 0x3b8e8); }

/* Local account name. Confirmed by live debugger read in State 3: the ASCII
 * string "colemancda2" sits at ctx+0x2331c (a second copy 0x14 bytes later at
 * ctx+0x23330 - see the PeerEndpoint note below). */
inline char *Ctx_localUserName(int ctx) { return reinterpret_cast<char *>(ctx + 0x2331c); }

/* --- Lobby/channel user list (State 3) --------------------------------
 * The CChannelUserListPanel (vtable 0x557cac) roster. Found live at
 * ctx+0x41440 as name-inline records: "admin" at ctx+0x41445 and
 * "colemancda2" at ctx+0x41452 - a ~0xD-byte stride (only two users were
 * available to sample, so the exact record layout/stride is inferred, not
 * confirmed). NOTE: this is distinct from Ctx_roomPlayerName (+0x4467c),
 * which is the in-ROOM player array and read back EMPTY while in the channel. */
inline char *Ctx_channelUserName(int ctx, int slot) { return reinterpret_cast<char *>(ctx + 0x41445 + slot * 0xd); }

/* --- Room slots (States 3/9/10/11) - the 0x2105 per-player SoA ---------
 * The room's 8 occupant slots. NOT a single struct array but a set of
 * PARALLEL per-slot arrays (struct-of-arrays), all populated together by
 * State03_GameRoomList_ProcessPacket's 0x2105 ("room player list") handler
 * and read by State09/10/11. The roster persists Ready Room -> Loading ->
 * Battle. Names live at ctx+0x457f1 (0xD-byte records, name + a byte at +0xc);
 * State11_InBattle_OnEnter spawns a mobile (CreateMobile) for each slot whose
 * Ctx_roomSlotActive byte is nonzero. Live: colemancda2 @ slot 0, admin @
 * slot 1. Distinct from Ctx_roomPlayerName (+0x4467c), the lobby room-card
 * array (empty in a room).
 *
 * Per-slot SoA map (ctx-relative base, element stride, source byte in the
 * 0x2105 record; roles marked (?) are structurally certain but semantically
 * inferred - confirm against live dumps):
 *   +0x457f1  x0xD  char[12]  name          (pkt +1)
 *   +0x457fd  x0xD  u8        status/ready   zeroed on join (pkt: none) (?)
 *   +0x4585c  x4    u32       (pkt +0xd) (?)
 *   +0x4589c  x2    u16       (pkt +0x11) (?)
 *   +0x4587c  x4    u32       (pkt +0x13) -> roster/battle-player object (?)
 *   +0x458ac  x2    u16       (pkt +0x17) -> roster/battle-player object (?)
 *   +0x4590c  x1    u8        (pkt +0x1b) selection/position byte (?)
 *   +0x45914  x1    u8        (pkt +0x1c) ACTIVE/team - gates battle spawn
 *   +0x458bc  x8    u16[4]    (pkt +0x1d/+0x21) avatarEquipped - see below
 *   +0x4591c  x2    u16       (pkt +0x2d) mobile/avatar A (+4 bias, 0x17=rnd) (?)
 *   +0x4592c  x2    u16       (pkt +0x2f) mobile/avatar B (+4 bias, 0x17=rnd) (?)
 * The +0x4587c(u32) and +0x458ac(u16) travel with the name into the
 * roster/battle-player object (FUN_004e74c0). The name base and 0xD stride
 * are code-confirmed across State03/09/10/11. */
inline char *Ctx_roomSlotName(int ctx, int slot)   { return reinterpret_cast<char *>(ctx + 0x457f1 + slot * 0xd); }
inline u8   &Ctx_roomSlotStatus(int ctx, int slot) { return *reinterpret_cast<u8 *>(ctx + 0x457f1 + slot * 0xd + 0xc); }
/* Nonzero => slot participates in the match; State11_InBattle_OnEnter spawns a
 * mobile per active slot. Carries a small value (1/3 seen) that also encodes
 * team/role; the 0x2105 handler normalizes 3->1 for the local slot. */
inline u8   &Ctx_roomSlotActive(int ctx, int slot) { return *reinterpret_cast<u8 *>(ctx + 0x45914 + slot); }

/* avatarEquipped: the worn outfit as four packed u16 part codes (each: bit15 =
 * gender (1=male 'm', 0=female 'f'), bits0-14 = id into the {gender}{cat}.dat
 * part table - see FILEFORMATS.md "Avatar.xfs"). Word order RESOLVED (2026) from
 * ComposeAvatarSprites (0x4d1500): it builds each on-body sprite as
 * "%c{cat}%05d.img", reading the gender bit straight from the matching word -
 *   word0 (+0x00) = Body    ('b', %cb) - gender from +0x501fe
 *   word1 (+0x02) = Head    ('h', %ch) - gender from +0x50200
 *   word2 (+0x04) = Glasses ('g', %cg) - gender from +0x50202
 *   word3 (+0x06) = Flag    ('f') - NOT in the on-body composite, drawn separately
 * This confirms LoadRoomSlotAvatar's (0x4dc5c0) word1=head/word3=flag reading;
 * LoadReadyRoomSlotAvatar (0x4431a0) was the transposed raw port. Copied to
 * +0x501fe+slot*8 in the Ready Room; unpacked + composited by ComposeAvatarSprites
 * / LoadAvatarSprites (0x4141b0) into the AvataTexture render targets. */
inline u16 *Ctx_avatarEquipped(int ctx, int slot) { return reinterpret_cast<u16 *>(ctx + 0x458bc + slot * 8); }

/* --- Room list (State 3) arena ----------------------------------------
 * The lobby's 6 room-card slots (3x2 grid). Per PROTOCOL.md
 * ("Per-room grid fields" + "RoomPlayerSlot"), the per-slot data is
 * NOT one contiguous struct - it's several parallel arrays each keyed
 * by room slot, so these are base-offset accessors, not a struct. The
 * six grid fields (bulk-filled by 0x2103, per-field by 0x21f3-0x21f7)
 * each live in their own array; the doc pins the bases but not the
 * per-array stride, so the array bases are exposed and the caller
 * indexes. */
inline u8  *Ctx_roomMap(int ctx)    { return reinterpret_cast<u8  *>(ctx + 0x4497c); } /* 1B/room */
inline u32 *Ctx_roomInfo(int ctx)   { return reinterpret_cast<u32 *>(ctx + 0x44984); } /* 4B/room; bits 18-19 = fullness */
inline u8  *Ctx_roomFlagA(int ctx)  { return reinterpret_cast<u8  *>(ctx + 0x4499c); } /* 1B/room; also equipped-item count */
inline u8  *Ctx_roomFlagB(int ctx)  { return reinterpret_cast<u8  *>(ctx + 0x449a2); }
inline u8  *Ctx_roomStatus(int ctx) { return reinterpret_cast<u8  *>(ctx + 0x449a8); }
inline u8  *Ctx_roomLock(int ctx)   { return reinterpret_cast<u8  *>(ctx + 0x449ae); }

/* RoomPlayerSlot storage (opcode 0x2105) - the per-player display data,
 * also parallel arrays. The 0x80-byte name buffer is the only
 * fixed-stride one confirmed; the rest are mirrored into the state
 * object on receipt (see ARCHITECTURE.md "RoomPlayerSlot"). */
inline char *Ctx_roomPlayerName(int ctx, int slot) { return reinterpret_cast<char *>(ctx + 0x4467c + slot * 0x80); }

/* Local room-card array the join path reads the target room's ID from
 * (0x2104 outgoing; ARCHITECTURE.md). */
inline u16 *Ctx_roomCardIds(int ctx) { return reinterpret_cast<u16 *>(ctx + 0x44664); }

/* The inventory item array (Avatar Store 0x6002; GbInventoryItem in
 * Protocol.h), 16 x 0x9c at +0x44be8. */
inline void *Ctx_inventory(int ctx) { return reinterpret_cast<void *>(ctx + 0x44be8); }

/* --- Peer/relay endpoint record (State 2 address-report path) ---------
 * Written from the 0x101f-family address-report packet (State02's
 * ProcessPacket tail) and handed to FUN_005204f0. Four dwords; the
 * flag byte at +0x0c is cleared on each update. Field meanings not
 * fully decoded, but the record shape (4x u32) is confirmed.
 *
 * WARNING - live inspection in State 3 shows this region holding the ASCII
 * account name ("colemancda2": addr="cole", field4="manc", field8="da2\0"),
 * i.e. a second copy of Ctx_localUserName, NOT a 4-dword IP endpoint. Either
 * the region is reused after login or the address-report interpretation is
 * misattributed - the "PeerEndpoint" shape needs re-confirmation. */
struct PeerEndpoint {
    u32 addr;    /* +0x00 (abs +0x23330) - name[0..3], e.g. "cole" */
    u32 field4;  /* +0x04 (abs +0x23334) - name[4..7], e.g. "manc" */
    u32 field8;  /* +0x08 (abs +0x23338) - name[8..11], e.g. "da2\0" */
    u8  flagC;   /* +0x0c (abs +0x2333c) - cleared per update */
};
inline PeerEndpoint *Ctx_peerEndpoint(int ctx) { return reinterpret_cast<PeerEndpoint *>(ctx + 0x23330); }

/* --- Per-player packet-checksum-state array --------------------------
 * PROTOCOL.md "Confirmed recurring structures": the 0x224-stride array
 * at +0xebef4 is per-player instances of the packet-checksum-state
 * object (indexed playerId * 0x224), reached by the checksum utility
 * family - NOT a gameplay slot struct. Exposed as an opaque
 * base+stride accessor; the object's own fields belong to the
 * checksum subsystem's own reconstruction (ValueGuard.h). */
inline CValueGuard *Ctx_checksumState(int ctx, int playerId) { return reinterpret_cast<CValueGuard *>(ctx + 0xebef4 + playerId * GB_CHECKSUM_STRIDE); }

#endif /* GB_CXX_CLIENTCONTEXT_H */
