/* CValueGuard methods - the "packet-checksum utility family" promoted
 * to real methods of the guarded-value cell. Promoted from the raw C
 * ports under src/network/ (PeekPacketChecksumState 0x40a2e0,
 * EncodeOutgoingPacketField 0x40a470, EncodeChecksumState 0x40a4a0,
 * EncodeChecksumStateXored 0x40a440, AddToPacketChecksum 0x40aab0,
 * SubFromPacketChecksum 0x40aaf0, PacketChecksumEquals 0x40b270,
 * PacketChecksumNotEquals 0x40b2a0). See ValueGuard.h and
 * src/cxx/README.md.
 *
 * The whole family takes the cell in a register (the implicit "this")
 * - exactly what a C++ member function is. Promoting them turns the
 * raw ports' in_EAX/unaff_EDI cell pointer into a real `this`, which
 * is the single clearest demonstration of why this tree exists.
 *
 * Peek() and Encode() reach the process-global key-table registry
 * (DAT_0079376c key words, DAT_00793774 table pointer,
 * g_valueGuardTamperFlag); those globals belong to the guard registry,
 * not the cell, so they stay extern here. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "ValueGuard.h"

extern "C" {
CRITICAL_SECTION DAT_005a9068;      /* the family's shared lock */
unsigned char g_valueGuardTamperFlag;
int  DAT_0079376c;                  /* key-table base (16 bytes/entry) */
int *DAT_00793774;                  /* current key-table object ptr (integrity anchor) */
int  DAT_00793778;                  /* "encoding active" gate */
int  DAT_00793770;                  /* key-table registry root */
void ScrambleChecksumGuardBytes(void);            /* registry re-key step */
void TreeLowerBound(void *scratch);
void FUN_0040b600(void *root, void *field, int tableObj);
int *FUN_0040b8c0(void);            /* returns the live table object (see note below) */
}

/* 0x40a2e0. Decode the cell's protected value: XOR each of the four
 * stored copies with its key-table word; if all four agree, that's the
 * value (also re-appended to the outgoing packet). Any disagreement, or
 * a swapped key-table pointer, raises the tamper flag and returns 0.
 * (Ghidra models FUN_0040b8c0 as value-returning at this site - it is
 * actually void; the integrity read it guards is kept as documented.) */
u32 CValueGuard::Peek()
{
    u32 handle = tableHandle;
    if (handle != 0) {
        /* integrity check: the live table object's anchor word must
         * still equal DAT_00793774's - a swap means tampering */
        int *live = FUN_0040b8c0();
        if (live != 0 && *live != (int)DAT_00793774) {
            g_valueGuardTamperFlag = 1;
        }
    }
    u32 decoded[4];
    u32 *key = reinterpret_cast<u32 *>(handle * 0x10 + DAT_0079376c);
    u32 *enc = &enc0;
    for (int i = 0; i < 4; ++i) {
        decoded[i] = key[i] ^ enc[i];
        if (i != 0 && decoded[0] != decoded[i]) {
            g_valueGuardTamperFlag = 1;
            return 0;
        }
    }
    EncodeOutgoingPacketField(decoded[0]);
    return decoded[0];
}

/* 0x40a470. Re-obfuscate the cell with a fresh value AND fold that
 * value into the outgoing packet stream. Advances the cell's key-table
 * handle through the registry, then stores four XOR-encoded copies. */
void CValueGuard::EncodeOutgoingPacketField(u32 value)
{
    u32 v = value;
    if (tableHandle != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(0);
    }
    int newHandle = 0;
    if (DAT_00793778 != 0) {
        newHandle = *(int *)(*DAT_00793774 + 0xc);
        FUN_0040b600(&DAT_00793770, &value, (int)DAT_00793774);
    }
    tableHandle = (u32)newHandle;
    if (newHandle != 0) {
        int *live = FUN_0040b8c0();
        if (live != DAT_00793774) {
            g_valueGuardTamperFlag = 1;
        }
    }
    u32 *key = reinterpret_cast<u32 *>(newHandle * 0x10 + DAT_0079376c);
    enc0 = key[0] ^ v;
    enc1 = key[1] ^ v;
    enc2 = key[2] ^ v;
    enc3 = key[3] ^ v;
}

/* 0x40a4a0 EncodeChecksumState - push the current value to the wire. */
void CValueGuard::Encode()
{
    EnterCriticalSection(&DAT_005a9068);
    u32 v = Peek();
    EncodeOutgoingPacketField(v);
    LeaveCriticalSection(&DAT_005a9068);
}

/* 0x40a440 EncodeChecksumStateXored - push value XOR 0xeeaeaec0. The
 * raw port reads the value from EAX (a prior Peek left it there); as a
 * method we Peek explicitly. */
void CValueGuard::EncodeXored()
{
    EnterCriticalSection(&DAT_005a9068);
    u32 v = Peek();
    EncodeOutgoingPacketField(v ^ 0xeeaeaec0);
    LeaveCriticalSection(&DAT_005a9068);
}

/* 0x40aab0 AddToPacketChecksum - value += delta, re-encode. */
void CValueGuard::Add(int delta)
{
    EnterCriticalSection(&DAT_005a9068);
    u32 v = Peek();
    EncodeOutgoingPacketField(v + (u32)delta);
    LeaveCriticalSection(&DAT_005a9068);
}

/* 0x40aaf0 SubFromPacketChecksum - value -= delta, re-encode. */
void CValueGuard::Sub(int delta)
{
    EnterCriticalSection(&DAT_005a9068);
    u32 v = Peek();
    EncodeOutgoingPacketField(v - (u32)delta);
    LeaveCriticalSection(&DAT_005a9068);
}

/* 0x40b270 PacketChecksumEquals / 0x40b2a0 PacketChecksumNotEquals. */
bool CValueGuard::Equals(int other)
{
    EnterCriticalSection(&DAT_005a9068);
    u32 v = Peek();
    LeaveCriticalSection(&DAT_005a9068);
    return (int)v == other;
}

bool CValueGuard::NotEquals(int other)
{
    EnterCriticalSection(&DAT_005a9068);
    u32 v = Peek();
    LeaveCriticalSection(&DAT_005a9068);
    return (int)v != other;
}
