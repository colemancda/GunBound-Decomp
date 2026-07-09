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

#endif /* GB_CXX_CLIENTCONTEXT_H */
