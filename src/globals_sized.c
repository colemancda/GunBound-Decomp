/* Real-extent storage for Ghidra globals whose address is used as a
 * larger object than the one-byte cell globals.c gives everything.
 * Kept in a separate TU that does NOT include globals.h: the externs
 * there stay `uint8_t`, every other TU keeps reading/writing byte 0
 * exactly as before, and the linker binds them to this storage (C
 * symbols carry no type). Sizes below are the object the address is
 * actually used as, not the original data-segment gap.
 *
 * When a new under-sized global bites, move its definition here from
 * globals.c and leave a pointer comment behind.
 */

/* The three static CRITICAL_SECTIONs (24 bytes on win32).
 * DAT_005a9068 is the value-guard/packet-encode lock WinMain enters
 * before anything could have initialized it - see the .CRT$XCU hook in
 * src/cxx/crt_shims_msvc.c, which runs InitializeCriticalSection on
 * all three before the CRT calls WinMain. */
unsigned char DAT_005a9068[24];
unsigned char DAT_005a9084[24];
unsigned char DAT_00e9af44[24];

/* The graphics.xfs archive singleton (was the 1-byte DAT_00f11dd0).
 * 0x10740 bytes; OpenXFSArchive stores the file handle at +0x1040 and
 * decoded blocks up to +0x10730. LoadSpriteSet reads sprites from it
 * via FindXFSEntry(&g_graphicsArchive, name). The startup hook in
 * crt_shims_msvc.c sets its handle to XFS_CLOSED before WinMain. */
#include "xfs.h"
XFSArchive g_graphicsArchive;
XFSArchive g_xfsScratch;

/* The localized UI-string map (was DAT_00796eec). LoadLocalizedStrings
 * builds the whole table at this address; 259 call sites pass
 * &g_localizedStringTable as the map base. 64 KB is generous - the
 * original segment gap is smaller. */
unsigned char g_localizedStringTable[0x10000];

/* The turn-event/replay-buffer context struct (was the 1-byte
 * DAT_00e55ce0). 0x454f9 bytes; established by cross-referencing every
 * offset dereferenced by FUN_004e84c0/FUN_004e7b60/FUN_004e80d0/
 * FUN_004e77e0/FUN_004e7de0/FUN_004e6050 (all take &DAT_00e55ce0 as
 * their context arg) plus the ~42 other DAT_00e5.../DAT_00e9... globals
 * that fell inside this range and are now offset-macros into this array
 * (see globals.h) instead of independent symbols, so param_N-relative
 * access and direct DAT_ access observe the same memory. Does NOT cover
 * the CRITICAL_SECTION at +0x45264 (DAT_00e9af44), which stays
 * independently declared/sized above - a real but pre-existing gap for
 * FUN_004e7de0's own use of that offset, not addressed by this change. */
unsigned char DAT_00e55ce0[0x454f9];

/* A sprite/frame-cache container singleton (was the 1-byte DAT_00eb1bd8).
 * FUN_004f46b0 (the container's free/reset method, whose `this` Ghidra
 * dropped as an uninitialised EBX - see src/unnamed/FUN_004f46b0.c) walks
 * two heap lists off +0x114 and +0x1b4, then zeroes an inline 15-entry
 * table at +0x401bc and a count at +0x401b8 - so the object extends to at
 * least 0x401fc bytes. 0x40200 covers every offset it touches. Distinct
 * from the small [0x20] sentinel-list container DAT_00ea0e18. Four call
 * sites (ShutdownDirectDraw, FUN_004e4220, State07_AvatarStore_OnExit x2)
 * pass &DAT_00eb1bd8; FUN_004f42f0 passes its own container argument.
 * Before this sizing, &DAT_00eb1bd8+0x401bc landed on whatever global the
 * linker placed next, and under the stricter (Lutris) wine the dropped
 * EBX was garbage and faulted outright. */
unsigned char DAT_00eb1bd8[0x40200];
