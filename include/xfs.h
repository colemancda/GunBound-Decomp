/* XFS archive object model - reconstructed from the register-artifact
 * ports under src/fileformat/ (OpenXFSArchive 0x4f0a50, FindXFSEntry
 * 0x4f0b90-ish, ReadXFSEntry 0x4f0380, ReadXFSEntryByte, DecodeXFSEntry
 * Block). Ghidra dropped the ESI 'this' pointer at every use of the
 * archive object; the promoted functions take it explicitly as
 * `XFSArchive *archive`.
 *
 * The object is 0x10740 bytes (max field offset 0x10730). Confirmed
 * field offsets from OpenXFSArchive's disassembly:
 *   +0x0000  u16 magic[2]         "XF","S2" (0x4658,0x3253)
 *   +0x0004  u32 blockCount       entry/block count (>>10 = full blocks)
 *   +0x0008  ...                  entry index (FindXFSEntry reads +8)
 *   +0x0040  void *blocks[]       decoded 0x20000-byte block pointers
 *   +0x1040  HANDLE hFile         file handle; -1 (0xffffffff) == closed.
 *                                 MUST be -1 before OpenXFSArchive or it
 *                                 early-returns 0x40001 ("already open").
 *   +0x1045  u8  writeFlag        the param_2 write flag
 *   +0x1048  ...                  LZHUF decode state (DecodeLZHUFBlock arg)
 *   +0x10730 u8  param3           the param_3 flag
 *
 * In the original the archive is a global singleton per data file
 * (graphics/avatar/sound) or a stack local opened-read-closed in one
 * function. Globals were constructed with hFile=-1 by a C++ static
 * initializer; the bring-up build reproduces that via the .CRT$XCU hook
 * in src/cxx/crt_shims_msvc.c (see XFS_CLOSED / xfs_archive_init).
 */
#ifndef GB_XFS_H
#define GB_XFS_H

#include <stdint.h>

#define XFS_OBJECT_SIZE  0x10740
#define XFS_OFF_HFILE    0x1040       /* HANDLE field, -1 when closed */
#define XFS_CLOSED       ((int)0xffffffff)

typedef struct XFSArchive {
    unsigned char bytes[XFS_OBJECT_SIZE];
} XFSArchive;

/* Set an archive object's handle field to "closed" so OpenXFSArchive
 * will actually open it. Call on a freshly-zeroed archive before the
 * first OpenXFSArchive (globals get this from the CRT startup hook). */
static __inline void xfs_archive_init(XFSArchive *a)
{
    *(int *)(a->bytes + XFS_OFF_HFILE) = XFS_CLOSED;
}

/* The per-data-file archive singletons (addresses from the original
 * binary; graphics.xfs = 0xf11dd0, read by LoadSpriteSet's
 * FindXFSEntry(&g_graphicsArchive, ...)). */
extern XFSArchive g_graphicsArchive;   /* 0x00f11dd0 - graphics.xfs (sprites) */

/* Bring-up scratch archive for the startup loaders whose archive was a
 * stack local (LoadLocalizedStrings/LoadChooseEventConfig/LoadGameData
 * Files/InitDirectSound/...). Those open-read-close within one function
 * and startup is sequential, so one shared object suffices for bring-up
 * until each loader is fully promoted to its own object. */
extern XFSArchive g_xfsScratch;

#endif /* GB_XFS_H */
