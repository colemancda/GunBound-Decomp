/* CValueGuard - GunBound's anti-tamper protected-value cell, the state
 * object behind the "packet-checksum" utility family (ARCHITECTURE.md
 * "Packet-checksum utility family"). Reconstructed from
 * PeekPacketChecksumState (0x40a2e0), EncodeOutgoingPacketField
 * (0x40a470) and the Encode/Add/Sub wrappers. See src/cxx/README.md.
 *
 * NOT actually a checksum - it's a value-obfuscation cell (the classic
 * GunBound client-side anti-cheat): the real value is stored FOUR
 * times, each XOR-encoded with a different word of a rotating key
 * table (DAT_0079376c, indexed by a per-cell table handle at +0x14).
 * Reads verify the four copies agree and that the key-table pointer
 * hasn't been swapped (DAT_00793774); any mismatch sets the global
 * tamper flag g_valueGuardTamperFlag. Every "EncodeOutgoingPacketField"
 * both re-obfuscates the cell AND appends it to the outgoing packet -
 * so the wire checksum and the in-memory guard share one mechanism.
 *
 * The array at g_clientContext+0xebef4 (0x224/player) is per-player
 * instances of this cell; the standalone encode targets in the network
 * handlers (+0x2e718, +0x39258, ... in State02's address-report tail)
 * are individual cells of the same type. All cells are accessed with
 * the cell pointer in a register (EAX/EDI) - the family's implicit
 * "this" - so the C++ methods are __fastcall-ish; modeled as free
 * functions taking the cell explicitly until the register convention
 * is byte-matched. */
#ifndef GB_CXX_VALUEGUARD_H
#define GB_CXX_VALUEGUARD_H

#include "gb_common.h"

#pragma pack(push, 1)
struct CValueGuard {
    u32 unk00;      /* +0x00 */
    u32 enc0;       /* +0x04: value ^ keyTable[handle][0] */
    u32 enc1;       /* +0x08: value ^ keyTable[handle][1] */
    u32 enc2;       /* +0x0c: value ^ keyTable[handle][2] */
    u32 enc3;       /* +0x10: value ^ keyTable[handle][3] */
    u32 tableHandle;/* +0x14: rotating key-table index (0 = uninitialized) */
    /* +0x18.. the guard's own integrity-tracking fields (a pointer at
     * +0x18 compared against DAT_00793774 on read); left opaque here,
     * as the guard-registry side isn't reconstructed yet. */

    /* The "packet-checksum utility family" as methods (promoted in
     * ValueGuard.cpp) - each takes the cell in a register in the
     * original, i.e. is really a member of this cell. */
    u32  Peek();                                 /* 0x40a2e0 */
    void EncodeOutgoingPacketField(u32 value);   /* 0x40a470 */
    void Encode();                               /* 0x40a4a0 */
    void EncodeXored();                          /* 0x40a440 */
    void Add(int delta);                         /* 0x40aab0 */
    void Sub(int delta);                         /* 0x40aaf0 */
    bool Equals(int other);                      /* 0x40b270 */
    bool NotEquals(int other);                   /* 0x40b2a0 */
};
#pragma pack(pop)

/* Per-player checksum-state cell array (0x224 stride) - the cell is
 * the head of each 0x224-byte per-player slot. */
static const int GB_CHECKSUM_STRIDE = 0x224;

#endif /* GB_CXX_VALUEGUARD_H */
