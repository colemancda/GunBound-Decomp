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
    u16 maxCapacity[16];      /* +0x18e2 (abs +0x410ea) */
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
 * fully decoded, but the record shape (4x u32) is confirmed. */
struct PeerEndpoint {
    u32 addr;    /* +0x00 (abs +0x23330) */
    u32 field4;  /* +0x04 (abs +0x23334) */
    u32 field8;  /* +0x08 (abs +0x23338) */
    u8  flagC;   /* +0x0c (abs +0x2333c) - cleared per update */
};
inline PeerEndpoint *Ctx_peerEndpoint(int ctx) { return reinterpret_cast<PeerEndpoint *>(ctx + 0x23330); }

/* --- Per-player packet-checksum-state array --------------------------
 * PROTOCOL.md "Confirmed recurring structures": the 0x224-stride array
 * at +0xebef4 is per-player instances of the packet-checksum-state
 * object (indexed playerId * 0x224), reached by the checksum utility
 * family - NOT a gameplay slot struct. Exposed as an opaque
 * base+stride accessor; the object's own fields belong to the
 * checksum subsystem's own reconstruction. */
inline u8 *Ctx_checksumState(int ctx, int playerId) { return reinterpret_cast<u8 *>(ctx + 0xebef4 + playerId * 0x224); }

#endif /* GB_CXX_CLIENTCONTEXT_H */
