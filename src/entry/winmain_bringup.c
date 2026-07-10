/* winmain_bringup.c - see include/winmain_bringup.h. Launch-only scaffolding for
 * the WinMain startup path; not part of the original binary. */
#include "ghidra_types.h"   /* pulls in globals.h (DAT_0079376c) */
#include "winmain_bringup.h"

/* Address->slot map, recovered from the real binary's WinMain (0x40d8e0), each
 * `push <opcode>; mov edi,<obj>; call 0x40a380`:
 *   [ 0] 0xe525e8 (0x118)  [ 1] 0x7947a0 (0)     [ 2] 0x7a7690 (2)
 *   [ 3] 0xe9bc68 (4)      [ 4] 0xe53c60 (5)     [ 5] 0x796cc8 (8)
 *   [ 6] 0xe9ba40 (0xa)    [ 7] 0x794bf0 (0xf)   [ 8] 0xe55ab8 (0x14)
 *   [ 9] 0x7949c8 (0x19)   [10] 0xe9c110 (0x1e)  [11] 0xe9b818 (0x32)
 *   [12] 0xe53470 (0x46)   [13] 0x794e48 (0x50)  [14] 0x7a78b8 (0x62)
 *   [15] 0x796aa0 (0x64)   [16] 0xe9c578 (0xa0)  [17] 0xe9c7a0 (0xc8)
 *   [18] 0xe9c350 (0x100)  [19] 0xe9bed8 (0x168)                        */
unsigned char g_vgWinMainObjects[GB_VG_SLOTS][GB_VG_OBJ_SIZE];

/* The value-guard XOR key table. EncodeOutgoingPacketField reads 16-byte rows
 * from DAT_0079376c indexed by the (startup-zero) counter DAT_00793778, so only
 * row 0 is touched on the WinMain path; 256 rows is generous headroom. Zeroed
 * (not rand()-filled) - fine for reaching a frame since the encoded values are
 * unread before then. */
static unsigned char g_vgKeyTable[256 * 16];

void WinMain_BringupInit(void)
{
  DAT_0079376c = (uint32_t)(uintptr_t)g_vgKeyTable;
}
