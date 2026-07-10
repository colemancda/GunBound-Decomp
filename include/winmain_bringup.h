/* winmain_bringup.h - launch bring-up scaffolding for the WinMain startup path.
 *
 * NOT part of the original binary. This exists only to let the MSVC-recompiled
 * exe execute WinMain's real startup sequence far enough to be observed under a
 * debugger, while the tree-wide dropped-register-parameter sweep (see
 * src/README.md) is still outstanding. Everything here is clearly scoped to the
 * WinMain path and documented against the real binary it was recovered from.
 */
#ifndef GB_WINMAIN_BRINGUP_H
#define GB_WINMAIN_BRINGUP_H

/* 20 distinct value-guard ("packet-checksum-state") objects, one per
 * EncodeOutgoingPacketField call in WinMain. Each original call is
 * `mov edi,<obj>; call 0x40a380`; the objects are 0x224-byte globals in the
 * original (0xe525e8, 0x7947a0, ...). We provide correctly-sized standalone
 * backing here rather than resizing the 20 individual DAT_ globals, since their
 * encoded contents are unread before the first rendered frame. GB_VG_* index
 * the slots in WinMain's call order. */
#define GB_VG_SLOTS 20
#define GB_VG_OBJ_SIZE 0x224

extern unsigned char g_vgWinMainObjects[GB_VG_SLOTS][GB_VG_OBJ_SIZE];

/* Initialises the value-guard key-table backing store (the original's
 * DAT_0079376c, an anti-cheat XOR key table normally rand()-filled by the
 * value-guard subsystem - see ARCHITECTURE.md). Must run before WinMain's
 * EncodeOutgoingPacketField calls, which index this table. */
void WinMain_BringupInit(void);

#endif
