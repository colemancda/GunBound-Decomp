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

/* The 20 value-guard ("packet-checksum-state") cells WinMain encodes, one per
 * EncodeOutgoingPacketField call. Each original call is
 * `mov edi,<obj>; call 0x40a380`; the objects are 0x224-byte globals in the
 * original (0xe525e8, 0x7947a0, ...). RETIRED 2026-08-16: the standalone
 * g_vgWinMainObjects backing that used to live here is gone - all 20 real
 * DAT_ globals are sized 0x224 in globals_sized.c and WinMain writes those, so
 * the cells it encodes are the cells the rest of the tree reads. */
#define GB_VG_SLOTS 20
#define GB_VG_OBJ_SIZE 0x224

/* Initialises the value-guard key-table backing store (the original's
 * DAT_0079376c, an anti-cheat XOR key table normally rand()-filled by the
 * value-guard subsystem - see ARCHITECTURE.md). Must run before WinMain's
 * EncodeOutgoingPacketField calls, which index this table. */
void WinMain_BringupInit(void);

#endif
