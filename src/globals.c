/* Storage for the globals declared in globals.h. See that file's
 * header comment for status/caveats. */
#include "ghidra_types.h" /* winsock2.h before windows.h, WIN32_LEAN_AND_MEAN */
#include "globals.h"
#include "functions.h" /* HandleSocketEvent/NoOpMethod (PTR_FUN_005572e8 init) */

int __cdecl _purecall(void); /* the CRT pure-virtual trap, 0x525acd; abstract-class vtable slots */

int32_t g_currentGameState;
int32_t g_pendingGameState;
char *g_gameStateVTableArray[16];
void *g_hDDrawDll;
char **g_pBackBufferSurface;
char **g_pClipper;
char **g_pD3DDevice7;
char **g_pDirect3D7;
char **g_pDirectDraw7;
char **g_pPrimarySurface;
char **g_pZBufferSurface;
uint8_t g_abBroadcastEventBuffer;
uint32_t g_dwBroadcastEventCursor;
float g_sineTable360[360];
uint8_t g_spriteVertexBuffer[0x10000];
uint32_t g_spriteVertexCount;
uint32_t g_stateChangeInProgress;
uint8_t g_stateChangeRequested;

uint8_t IMAGE_DOS_HEADER_00400000;

uint8_t DAT_0054b420;
uint8_t DAT_0054b438;
/* 0x54f378: real storage is g_aesTe4_1 in aes_tables.c - see globals.h. */
/* Button-definition XFS extension ".epa" appended by AppendPersistentButtonName
 * (orig .data 0x551cac = bytes 2e 65 70 61 00). Our extraction left these
 * zero, so button-def filenames had no extension and OpenXFSEntryStream
 * failed for every button (empty named-state descriptors, invisible buttons).
 * Recovered from the original .data section (2026-07-18). */
uint32_t g_buttonDefExt = 0x6170652e; /* ".epa" little-endian */
uint8_t g_buttonDefExtNul = 0x00;        /* trailing NUL */
uint8_t DAT_00551cb1;
/* 0x551e24: the 6-byte EUC-KR string bf ee bf b5 c6 c0 ("운영팀", the
 * operator team) + NUL, copied from the original .data. AppendChatLogEntry
 * and FUN_0041ef90 compare 7 bytes against it (`mov edi,0x551e24` at
 * 0x41ba1b / 0x41effe); the 0x403c0e.. sites push it. Was a zeroed byte. */
const char DAT_00551e24[] = "\xbf\xee\xbf\xb5\xc6\xc0";
uint16_t DAT_00551e34 = 0x203e; /* orig .data 0x551e34 */
uint8_t DAT_00551e36;
const char DAT_00551e78[] = "push"; /* mouse-press state name; was a zeroed 1-byte global (orig .data 0x551e78) */
/* 0x00551ecc: real storage is PTR_DAT_00551ecc below - see globals.h. */
/* DAT_0055207c: string bytes now in globals_sized.c (orig .data 0x55207c, 5 bytes) */
const char DAT_00552084[] = "edit"; /* Win32 EDIT-control class name for the hidden global chat-input control (FUN_0040c670's CreateWindowExA) - was a zeroed 1-byte global (orig .rdata 0x552084), same class of bug as DAT_00551e78 above. With the class name reading as an empty string, CreateWindowExA silently failed (ERROR_CANNOT_FIND_WND_CLASS -> NULL HWND), so the control never existed: SetFocus/SetWindowLongA/ImmDisableIME in FUN_0040c670 all silently no-op'd on a NULL HWND, keyboard focus stayed on the main window instead of the (nonexistent) edit control, and chat typing never worked. */
/* DAT_00552218: string bytes now in globals_sized.c (orig .data 0x552218, 3 bytes) */
/* DAT_00552728: string bytes now in globals_sized.c (orig .data 0x552728, 5 bytes) */
const char DAT_0055275c[] = "%02x"; /* orig .data 0x55275c (WinMain sscanf format), was a zeroed 1-byte global */
/* 0x00552788: real storage is PTR_DAT_00552788 below - see globals.h. */
/* Registry value-name strings for the broker "IP"/"Port" settings
 * (HKCU\Software\Softnyx\GunBound) - were 1-byte placeholders (Ghidra
 * failed to recognize these two specifically as string literals, unlike
 * this same file's ~18 sibling s_*-prefixed registry value/key-name
 * strings, e.g. s_LastServer_00552884 a few lines below). With only 1
 * byte of storage, RegQueryValueExA's lpValueName read past the end into
 * whatever the linker placed next, never matching the real "IP"/"Port"
 * value names - so LoadClientSettingsFromRegistry.c's queries always
 * failed and g_brokerHost/g_brokerPort (the broker host/port
 * ServerSelect connects to) stayed at their zero-init default, live-
 * reproduced as BeginServerConnect always getting ip="" port=0 even with
 * the real registry values present. Recovered byte-for-byte from
 * orig/GunBound.gme's .data (file offset 0x151690-0x15169c). */
const char s_IP_00552898[] = "IP";
const char s_Port_00552890[] = "Port";
uint32_t DAT_00552c70 = 0x7461642e; /* orig .data 0x552c70 */
uint8_t DAT_00552c74;
uint16_t DAT_00552c78 = 0x666d; /* orig .data 0x552c78 */
uint8_t DAT_00552c7a;
uint16_t DAT_00552c7c = 0x67; /* orig .data 0x552c7c */
uint16_t DAT_00552c80 = 0x62; /* orig .data 0x552c80 */
/* DAT_00552d38: string bytes now in globals_sized.c (orig .data 0x552d38, 32 bytes) */
/* DAT_00552d60: string bytes now in globals_sized.c (orig .data 0x552d60, 52 bytes) */
/* DAT_00552d94: string bytes now in globals_sized.c (orig .data 0x552d94, 32 bytes) */
/* DAT_00552db4: string bytes now in globals_sized.c (orig .data 0x552db4, 47 bytes) */
/* DAT_00552de4: string bytes now in globals_sized.c (orig .data 0x552de4, 45 bytes) */
/* DAT_00552e14: string bytes now in globals_sized.c (orig .data 0x552e14, 16 bytes) */
/* DAT_00552e24: string bytes now in globals_sized.c (orig .data 0x552e24, 9 bytes) */
/* DAT_00552e30: string bytes now in globals_sized.c (orig .data 0x552e30, 54 bytes) */
/* DAT_00552e68: string bytes now in globals_sized.c (orig .data 0x552e68, 39 bytes) */
/* DAT_00552e90: string bytes now in globals_sized.c (orig .data 0x552e90, 20 bytes) */
/* DAT_00552ea4: string bytes now in globals_sized.c (orig .data 0x552ea4, 22 bytes) */
/* DAT_00552ebc: string bytes now in globals_sized.c (orig .data 0x552ebc, 15 bytes) */
/* DAT_00552ed4: string bytes now in globals_sized.c (orig .data 0x552ed4, 27 bytes) */
/* DAT_00552ef0: string bytes now in globals_sized.c (orig .data 0x552ef0, 42 bytes) */
/* DAT_00552f1c: string bytes now in globals_sized.c (orig .data 0x552f1c, 15 bytes) */
/* DAT_00552f34: string bytes now in globals_sized.c (orig .data 0x552f34, 22 bytes) */
/* DAT_00552f4c: string bytes now in globals_sized.c (orig .data 0x552f4c, 22 bytes) */
/* DAT_00552f64: string bytes now in globals_sized.c (orig .data 0x552f64, 41 bytes) */
/* DAT_00552f90: string bytes now in globals_sized.c (orig .data 0x552f90, 17 bytes) */
/* DAT_00552fac: string bytes now in globals_sized.c (orig .data 0x552fac, 27 bytes) */
/* DAT_00552fc8: string bytes now in globals_sized.c (orig .data 0x552fc8, 25 bytes) */
/* DAT_00552fe4: string bytes now in globals_sized.c (orig .data 0x552fe4, 23 bytes) */
/* DAT_00552ffc: string bytes now in globals_sized.c (orig .data 0x552ffc, 20 bytes) */
/* DAT_00553018: string bytes now in globals_sized.c (orig .data 0x553018, 36 bytes) */
/* DAT_0055303c: string bytes now in globals_sized.c (orig .data 0x55303c, 53 bytes) */
/* DAT_00553074: string bytes now in globals_sized.c (orig .data 0x553074, 53 bytes) */
/* DAT_005530ac: string bytes now in globals_sized.c (orig .data 0x5530ac, 21 bytes) */
/* DAT_005530cc: string bytes now in globals_sized.c (orig .data 0x5530cc, 31 bytes) */
/* DAT_005530ec: string bytes now in globals_sized.c (orig .data 0x5530ec, 24 bytes) */
/* DAT_0055310c: string bytes now in globals_sized.c (orig .data 0x55310c, 60 bytes) */
/* DAT_00553148: string bytes now in globals_sized.c (orig .data 0x553148, 62 bytes) */
/* DAT_00553188: string bytes now in globals_sized.c (orig .data 0x553188, 41 bytes) */
/* DAT_005531b4: string bytes now in globals_sized.c (orig .data 0x5531b4, 41 bytes) */
/* DAT_005531e0: string bytes now in globals_sized.c (orig .data 0x5531e0, 24 bytes) */
/* DAT_00553200: string bytes now in globals_sized.c (orig .data 0x553200, 29 bytes) */
/* DAT_00553258: string bytes now in globals_sized.c (orig .data 0x553258, 40 bytes) */
/* DAT_0055328c: string bytes now in globals_sized.c (orig .data 0x55328c, 45 bytes) */
/* DAT_005532bc: string bytes now in globals_sized.c (orig .data 0x5532bc, 25 bytes) */
/* DAT_005532e4: string bytes now in globals_sized.c (orig .data 0x5532e4, 22 bytes) */
/* DAT_005532fc: string bytes now in globals_sized.c (orig .data 0x5532fc, 25 bytes) */
/* DAT_00553320: string bytes now in globals_sized.c (orig .data 0x553320, 15 bytes) */
/* DAT_00553330: string bytes now in globals_sized.c (orig .data 0x553330, 26 bytes) */
/* DAT_00553354: string bytes now in globals_sized.c (orig .data 0x553354, 27 bytes) */
/* DAT_00553370: string bytes now in globals_sized.c (orig .data 0x553370, 23 bytes) */
/* DAT_00553390: string bytes now in globals_sized.c (orig .data 0x553390, 30 bytes) */
/* DAT_005533b0: string bytes now in globals_sized.c (orig .data 0x5533b0, 22 bytes) */
/* DAT_005533d0: string bytes now in globals_sized.c (orig .data 0x5533d0, 52 bytes) */
/* DAT_00553404: string bytes now in globals_sized.c (orig .data 0x553404, 57 bytes) */
/* DAT_00553440: string bytes now in globals_sized.c (orig .data 0x553440, 53 bytes) */
/* DAT_00553478: string bytes now in globals_sized.c (orig .data 0x553478, 18 bytes) */
/* DAT_005534b4: string bytes now in globals_sized.c (orig .data 0x5534b4, 21 bytes) */
/* DAT_005534cc: string bytes now in globals_sized.c (orig .data 0x5534cc, 5 bytes) */
/* DAT_005534d4: string bytes now in globals_sized.c (orig .data 0x5534d4, 52 bytes) */
/* DAT_00553508: string bytes now in globals_sized.c (orig .data 0x553508, 47 bytes) */
/* DAT_00553554: string bytes now in globals_sized.c (orig .data 0x553554, 25 bytes) */
/* DAT_00553570: string bytes now in globals_sized.c (orig .data 0x553570, 5 bytes) */
/* DAT_00553588: string bytes now in globals_sized.c (orig .data 0x553588, 5 bytes) */
/* DAT_005535a4: string bytes now in globals_sized.c (orig .data 0x5535a4, 5 bytes) */
/* DAT_005535ac: string bytes now in globals_sized.c (orig .data 0x5535ac, 3 bytes) */
/* DAT_005535b0: string bytes now in globals_sized.c (orig .data 0x5535b0, 5 bytes) */
/* DAT_005535b8: string bytes now in globals_sized.c (orig .data 0x5535b8, 5 bytes) */
/* 0x005535c0: real storage is PTR_DAT_005535c0 below - see globals.h. */
/* DAT_005535c4: string bytes now in globals_sized.c (orig .data 0x5535c4, 5 bytes) */
/* DAT_005535cc: string bytes now in globals_sized.c (orig .data 0x5535cc, 2 bytes) */
/* DAT_005535d8: string bytes now in globals_sized.c (orig .data 0x5535d8, 3 bytes) */
/* DAT_005535dc: string bytes now in globals_sized.c (orig .data 0x5535dc, 3 bytes) */
/* DAT_005535e8: string bytes now in globals_sized.c (orig .data 0x5535e8, 5 bytes) */
/* DAT_005535f0: string bytes now in globals_sized.c (orig .data 0x5535f0, 2 bytes) */
/* DAT_005535f4: string bytes now in globals_sized.c (orig .data 0x5535f4, 3 bytes) */
uint16_t DAT_00553620 = 0x5d; /* orig .data 0x553620 */
uint16_t DAT_00553624 = 0x205d; /* orig .data 0x553624 */
uint8_t DAT_00553626;
uint32_t DAT_00553628 = 0x20205d; /* orig .data 0x553628 */
/* DAT_00553648: string bytes now in globals_sized.c (orig .data 0x553648, 3 bytes) */
/* 0x553b68 "fire1" and 0x553b70 "fire2": mobile state names, pushed as
 * pointers (push 0x553b68 at 0x47ceaa, mov eax,0x553b70 at 0x45ee45, ...).
 * Were zeroed uint32_t + uint16_t pairs; Ghidra split each string where
 * inlined strcpys read it as a dword and a word (0x43d109/0x43d111,
 * 0x4b7965/0x4b796c), so DAT_00553b6c / DAT_00553b74 are now views into
 * these arrays (globals.h). Bytes copied from the original .data. */
const char DAT_00553b68[8] = "fire1";
const char DAT_00553b70[8] = "fire2";
/* DAT_00553b88: string bytes now in globals_sized.c (orig .data 0x553b88, 5 bytes) */
/* DAT_00553bcc: string bytes now in globals_sized.c (orig .data 0x553bcc, 5 bytes) */
/* 0x553f90 "move": a mobile state name, pushed as a pointer (push 0x553f90
 * at 0x42bb8b and 11 more). Was a zeroed byte; bytes from the original. */
const char DAT_00553f90[] = "move";
/* DAT_00554060: string bytes now in globals_sized.c (orig .data 0x554060, 5 bytes) */
uint32_t DAT_005554f8 = 0x676d692e; /* orig .data 0x5554f8 */
uint8_t DAT_005554fc;
/* 0x00555500: real storage is PTR_DAT_00555500 below - see globals.h. */
const char s_loadstage_img_00555504[] = "loadstage.img";
uint16_t DAT_00555a14 = 0x6d73; /* orig .data 0x555a14 */
uint8_t DAT_00555a16;
uint16_t DAT_00555a18 = 0x6673; /* orig .data 0x555a18 */
uint8_t DAT_00555a1a;
/* DAT_00555c90: string bytes now in globals_sized.c (orig .data 0x555c90, 5 bytes) */
/* DAT_00556770: string bytes now in globals_sized.c (orig .data 0x556770, 5 bytes) */
uint32_t DAT_00556ae0 = 0x6d692e6c; /* orig .data 0x556ae0 */
uint16_t DAT_00556ae4 = 0x67; /* orig .data 0x556ae4 */
const char DAT_00557234[] = "%s%d"; /* orig .data 0x557234, was a zeroed 1-byte global */
uint32_t DAT_00557258 = 0x646e6c2e; /* orig .data 0x557258 */
uint8_t DAT_0055725c;
/* IID_IDirectInput8A. Passed as the REFIID to DirectInput8Create but was
 * declared uint8_t (1 byte); DirectInput8Create correctly rejected the
 * resulting garbage 16-byte IID with E_NOINTERFACE (0x80004002), leaving
 * DAT_00674f68 NULL. Decoded byte-for-byte from orig .data 0x5573c8-0x5573d7
 * - same bug/fix class as DAT_00f22504 (IID_IDirect3DHALDevice) earlier. */
GUID DAT_005573c8 = {0xbf798030, 0x483a, 0x4da2, {0xaa, 0x99, 0x5d, 0x64, 0xed, 0x36, 0x97, 0x00}};
/* OpenXFSArchive's expected header magic ("XF", matching the "XF"/"S2"
 * pair it itself writes at offsets 0/2 when creating a fresh empty
 * archive). Was zero-init BSS - nothing in .text ever writes it - but the
 * original binary's own .data has this as a compile-time constant (raw
 * bytes at the real address are 0x4658), not a runtime-constructed value,
 * same class as PTR_DAT_0056d460. Left at 0, every real archive's decoded
 * header magic (0x4658) failed to match, so OpenXFSArchive always fell
 * through to its "not found" cleanup path for every archive that
 * genuinely existed on disk - which for graphics.xfs silently left the
 * sprite registry (g_spriteRegistry) permanently empty (LoadSpriteSet always
 * returns 0), so nothing ever rendered - the black bring-up window. */
uint16_t DAT_0055751c = 0x4658;
/* Texture XFS extension ".xtf" appended by PreloadTexture (orig .data
 * 0x557554 = bytes 2e 78 74 66 00). Same zeroed-extraction trap as the
 * ".epa" button-def extension (g_buttonDefExt): without it PreloadTexture's
 * filenames had no extension and OpenXFSEntryStream failed for every
 * texture. Recovered from the original .data section (2026-07-18). */
uint32_t g_textureExt = 0x6674782e; /* ".xtf" little-endian */
uint8_t g_textureExtNul = 0x00;        /* trailing NUL */
float DAT_00557fb0 = 1.0f; /* orig .data 0x3f800000; only x87 DWORD operands reference it */
float DAT_00557fb4 = 0.0f; /* orig .data 0x00000000; only x87 DWORD operands reference it */
float DAT_00557fb8 = 0.5f; /* orig .data 0x3f000000; only x87 DWORD operands reference it */
float DAT_00557fbc = 0.0016666667f; /* orig .data 0x3ada740e; only x87 DWORD operands reference it */
float DAT_00557fc0 = 0.00125f; /* orig .data 0x3aa3d70a; only x87 DWORD operands reference it */
float DAT_00557fc4 = 63.0f; /* orig .data 0x427c0000; only x87 DWORD operands reference it */
float DAT_00557fc8 = 127.0f; /* orig .data 0x42fe0000; only x87 DWORD operands reference it */
float DAT_00557fcc = 192.0f; /* orig .data 0x43400000; only x87 DWORD operands reference it */
float DAT_00557fd0 = 128.0f; /* orig .data 0x43000000; only x87 DWORD operands reference it */
float DAT_00557fd4 = 255.0f; /* orig .data 0x437f0000; only x87 DWORD operands reference it */
float DAT_00557fec = -31.0f; /* orig .data 0xc1f80000; only x87 DWORD operands reference it */
float DAT_00557ff0 = 15.0f; /* orig .data 0x41700000; only x87 DWORD operands reference it */
float DAT_00557ff4 = 31.0f; /* orig .data 0x41f80000; only x87 DWORD operands reference it */
float DAT_00557ff8 = 32.0f; /* orig .data 0x42000000; only x87 DWORD operands reference it */
float DAT_00557ffc = -48.0f; /* orig .data 0xc2400000; only x87 DWORD operands reference it */
float DAT_00558000 = -32.0f; /* orig .data 0xc2000000; only x87 DWORD operands reference it */
float DAT_00558004 = -63.0f; /* orig .data 0xc27c0000; only x87 DWORD operands reference it */
float DAT_00558008 = 64.0f; /* orig .data 0x42800000; only x87 DWORD operands reference it */
float DAT_0055800c = -112.0f; /* orig .data 0xc2e00000; only x87 DWORD operands reference it */
float DAT_00558010 = -64.0f; /* orig .data 0xc2800000; only x87 DWORD operands reference it */
float DAT_0055801c = 0.00390625f; /* orig .data 0x3b800000; only x87 DWORD operands reference it */
float DAT_00558020 = -255.0f; /* orig .data 0xc37f0000; only x87 DWORD operands reference it */
float DAT_00558028 = -15.0f; /* orig .data 0xc1700000; only x87 DWORD operands reference it */
float DAT_0055802c = 48.0f; /* orig .data 0x42400000; only x87 DWORD operands reference it */
float DAT_00558030 = 7.0f; /* orig .data 0x40e00000; only x87 DWORD operands reference it */
float DAT_00558034 = 16.0f; /* orig .data 0x41800000; only x87 DWORD operands reference it */
float DAT_00558038 = -24.0f; /* orig .data 0xc1c00000; only x87 DWORD operands reference it */
float DAT_0055803c = -16.0f; /* orig .data 0xc1800000; only x87 DWORD operands reference it */
float DAT_00558040 = 0.125f; /* orig .data 0x3e000000; only x87 DWORD operands reference it */
float DAT_00558054 = 0.25f; /* orig .data 0x3e800000; only x87 DWORD operands reference it */
float DAT_00558064 = 0.328125f; /* orig .data 0x3ea80000; only x87 DWORD operands reference it */
uint8_t DAT_005583e8;
uint8_t DAT_0055841c;
uint8_t DAT_00558458;
uint8_t DAT_00569e10;
uint8_t DAT_00569e2c;
uint8_t DAT_00569e48;
uint8_t DAT_00569e68;
uint32_t DAT_0056d108 = 0xffffffff; /* orig .data 0x56d108: -1 = no state transition running (ProcessInputEventQueue gates on == -1) */
uint32_t g_cursorAnchorX = 400; /* orig .data 0x56d10c (screen centre) */
uint32_t g_cursorAnchorY = 300; /* orig .data 0x56d110 */
uint32_t g_serverWaitTicks = 0xffffffff;   /* was DAT_0056d118 - server-reply wait counter (PLEASE WAIT overlay); see globals.h */
const uint32_t DAT_0056d11c[11] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 1024};
/* DAT_0056d350: the 11-dword table indexed by the room-size byte is in globals_sized.c. */
uint32_t DAT_0056d3d8 = 0xffffffff; /* orig .data 0x56d3d8 */
uint32_t DAT_0056d3dc = 0xffffffff; /* orig .data 0x56d3dc */
uint8_t DAT_0056d3e0;
uint8_t DAT_0056d400;
/* DAT_0056d440: string bytes now in globals_sized.c (orig .data 0x56d440, 5 bytes) */
/* 0x0056d460: real storage is PTR_DAT_0056d460 below - see globals.h. */
uint32_t DAT_0056dbe8 = 0xffffffff; /* orig .data 0x56dbe8 */
/* DAT_0056dbf0 -> moved to globals_sized.c (the real 0xa0-byte AES login-key table) */
/* DAT_0056dc30: per-connection-type magic/key table (0x56dc30), indexed
 * [0..2] by InitConnectionObject's connection index. Was a 1-byte placeholder;
 * the ctor reads a full uint32 at [param_2*4], so an undersized global
 * fed garbage into each connection's +0x20c field. Recovered the real
 * 4 dwords verbatim from orig/GunBound.gme (0x56dc30-0x56dc3f); the next
 * symbol, the item shelf-icon table, starts right after at 0x56dc40. */
uint32_t DAT_0056dc30[4] = {0x8631607e, 0x8631607e, 0xa8c2f5d3, 0x8631607e};
/* Item shelf-icon table (0x56dc40) - 40 packed uint16 entries extracted verbatim
 * from the binary. Each entry: low byte = icon-pair index (frame = low*2, then -2
 * enabled / -1 disabled), high byte = 0x00/0xff selecting icon-sheet texture
 * 0x2713 / 0x2714. Indexed by the item ordinal = item-ownership bitmask bit
 * (Ctx_itemOwnedMask). Ordinals 0-10 are the battle items; identity recovered by
 * matching each entry to itemdata.dat's 0x30 field (tools/lzhuf/decode_item.py):
 *   0 Dual   1 Blood   2 Energy up 2   3 Energy up 1   4 Dual+   5 Change Wind
 *   6 Team Teleport   7 Bunge shot   8 Power up   9 Thunder   10 Teleport
 * Ordinals 11-39 are icon slots for items not defined in this build's itemdata. */
uint16_t g_awItemIconTable[40] = {
    0xff01, 0x0003, 0xff07, 0x0007, 0xff02, 0x000f, 0xff0b, 0x0001,
    0x0002, 0xff06, 0xff0a, 0xff04, 0xff05, 0x0006, 0xff08, 0xff09,
    0x0008, 0x0009, 0x0003, 0x000b, 0x000c, 0x000d, 0x000e, 0x0004,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0xff0a, 0x001d, 0x0005,
};
/* g_eventKeyBlock (was DAT_0056dc90..DAT_0056dcaa): the two 16-byte AES keys
 * for the UDP battle/replay event channel, at 0x56dc90 and 0x56dca0.
 *
 * (FUN_004e6160 below is ProcessUdpProbeDatagram's old symbol.)
 *
 * COALESCED + INITIALISED (2026-07-19). Ghidra split these two blocks into ten
 * separate one-byte DAT_ globals - only the bytes any function happens to poke
 * individually - which broke them TWICE:
 *   1. MSVC gives separate globals no guaranteed layout, but the original
 *      passes the block base to RijndaelSetKey with EDX=0x10, i.e. it reads a
 *      CONTIGUOUS 16 bytes (orig 0x4e6e56/0x4e6e5b: `mov edx,0x10` /
 *      `mov ecx,0x56dc90`, and 0x4e6f32/0x4e6f37 for 0x56dca0).
 *   2. The blocks are INITIALISED DATA in the original, not .bss - the port's
 *      zero-init byte globals lost the key material entirely. Bytes dumped
 *      straight from orig/GunBound.gme at 0x56dc90 (both blocks are identical):
 *        00 00 63 6f 6d 73 69 6b 00 00 d2 22 ea fa ee 3a   ("..comsik......:")
 * Backed by one 0x20-byte array here; the old DAT_ names are offset-macros in
 * globals.h (same technique as g_replayContext's fields), so every existing
 * per-byte read/write keeps working unchanged. The per-packet fields at +0,
 * +5, +7 and +0xa are overwritten per event by EncryptEventBroadcast /
 * FUN_004e7de0 / FUN_004e6160 before each key expansion; the rest is the
 * constant key. */
uint8_t g_eventKeyBlock[0x20] = {
    0x00, 0x00, 0x63, 0x6f, 0x6d, 0x73, 0x69, 0x6b,
    0x00, 0x00, 0xd2, 0x22, 0xea, 0xfa, 0xee, 0x3a,
    0x00, 0x00, 0x63, 0x6f, 0x6d, 0x73, 0x69, 0x6b,
    0x00, 0x00, 0xd2, 0x22, 0xea, 0xfa, 0xee, 0x3a,
};
/* DAT_0056dd30/DAT_0056de30 (the 256-byte LZHUF d_code/d_len tables)
 * live as lzhuf_d_code/lzhuf_d_len in src/lzhuf/lzhuf_tables.c now -
 * FUN_004ea6e0, their only user, indexes those directly. */
uint32_t g_clipMaxX = 799; /* orig .data 0x56df30 (full-screen clip) */
uint32_t g_clipMaxY = 599; /* orig .data 0x56df34 */
uint16_t DAT_00588f38 = 0x2; /* orig .data 0x588f38 */
uint32_t DAT_00588f3c = 0x5622; /* orig .data 0x588f3c */
uint16_t DAT_00588f40 = 0x10; /* orig .data 0x588f40 */
uint32_t DAT_00588f44 = 0x15888; /* orig .data 0x588f44 */
/* Display-mode config, statically initialised in the original's .data
 * (0x588f48). InitDirectDraw's fullscreen path feeds these to SetDisplayMode
 * (800x600x16) and SetupZBuffer relies on the resulting 16-bit back buffer
 * to pick a matching Z-buffer format. The port had left them zero-init'd
 * (SetDisplayMode(0,0,0) -> 32-bit desktop mode -> no Z-format match ->
 * SetupZBuffer crash), and had DAT_00588f50/54 as uint8_t although they hold
 * floats (800.0/600.0) that the coordinate transforms in FUN_004eda*0 also
 * read. Values decoded from orig .data 0x588f48-0x588f60. */
uint32_t DAT_00588f48 = 60;    /* refresh rate (WinMain may overwrite) */
uint8_t DAT_00588f4c = 0x1; /* orig .data 0x588f4c */
float DAT_00588f50 = 800.0f;   /* screen width  */
float DAT_00588f54 = 600.0f;   /* screen height */
uint32_t DAT_00588f60 = 16;    /* bit depth */
uint8_t DAT_00588f64 = 0x1; /* orig .data 0x588f64 */
void * DAT_0058b248;
/* DAT_0058b8d6: string bytes now in globals_sized.c (orig .data 0x58b8d6, 2 bytes) */
/* DAT_0058bb04: string bytes now in globals_sized.c (orig .data 0x58bb04, 2 bytes) */
/* g_valueGuardLock, DAT_005a9084: moved to globals_sized.c - both are
 * CRITICAL_SECTIONs, a one-byte cell under-sizes them */
/* DAT_005b1444 holds a pointer to the ATL::CAtlStringMgr vtable (real,
 * documented VS2003 ATL library object - see src/unnamed/msvc_crt_atl/
 * FUN_00520037.c's "public: __thiscall ATL::CAtlStringMgr::CAtlStringMgr
 * (IAtlMemMgr*)" and FUN_0052009c.c's "...CAtlStringMgr::Allocate(int,int)",
 * both Ghidra function-signature-matched against the real library).
 * GetLocalizedString.c and ~7 other files call its vtable slot 0xc
 * (GetNilString()) unconditionally on every lookup, computed as
 * `DAT_005b1444 + 0xc` directly - i.e. these raw ports treat DAT_005b1444's
 * VALUE as the vtable pointer itself (matching the original disassembly's
 * `mov eax,[0x5b1444]; call [eax+0xc]`), not as the CAtlStringMgr object's
 * own address (that's a SEPARATE register, ECX/"this", which every one of
 * these call sites also drops - harmless here since the real vtable methods
 * below don't need it, see crt_shims_msvc.c). Was always zero (nothing in
 * .text ever writes it - matches FUN_005439b1.c's own untouched
 * `DAT_005b1444 = &PTR_Allocate_00544b38;`, never called), so every
 * GetNilString() call faulted at NULL+0xc. Populated by
 * crt_shims_msvc.c's gb_init_atl_string_mgr, wired into gb_startup_init.
 * In the original 0x5b1444 is the manager OBJECT (vtable 0x544b38 at +0,
 * built by 0x520037 from the initializer at 0x543179), so this scalar is
 * its +0 word and &DAT_005b1444 is the manager: every CStringData header's
 * +0 must hold &DAT_005b1444 (see crt_shims_msvc.c). */
uint32_t DAT_005b1444;
uint32_t DAT_005b15ac;
int *DAT_005b1c48;
uint32_t g_edgeCursors[9];
/* DAT_005b1c70 (BuddyIP)/DAT_005b1cf0 (ChannelName): LoadClientSettings-
 * FromRegistry.c's own RegQueryValueExA calls tell these both 0x80 (128)
 * bytes of real capacity (`local_14 = 0x80;`), matching the real gap to
 * the next symbol in each case (0x1cf0-0x1c70=0x80, 0x1d70-0x1cf0=0x80) -
 * were 1-byte placeholders, so any real registry value longer than 1
 * byte overflowed into whatever the linker placed next. See
 * g_brokerHost's comment below for the live-reproduced sibling bug this
 * matches exactly. */
uint8_t DAT_005b1c70[0x80];
uint8_t DAT_005b1cf0[0x80];
/* The shared text-render/RLE-sprite scratch buffer (ShowErrorDialog/
 * ShowMessageDialog/ShowErrorDialogFmt's word-wrap target, GameTick's HUD RLE
 * blits - see those files' own comments). Was a lone uint32_t, so
 * ShowErrorDialog's own 0x160-byte zero-fill loop (0x57 dwords + a trailing
 * word) overran into whatever <common> global the linker placed next -
 * confirmed to corrupt DAT_005b1444 (the ATL string-manager vtable pointer)
 * in this build, causing GetLocalizedString to crash calling through a
 * zeroed vtable slot the very first time any of these dialogs fire. Sized to
 * 0x160 bytes: the real extent is independently confirmed three ways - the
 * 0x15e (350) zero-fill target, RenderWrappedText's own wrapWidth=0x15e
 * argument at every call site, and the original binary's next symbol
 * g_installPath sitting at exactly +0x160. DAT_005b1da2 (the old split-out
 * symbol for this buffer's own +0x32 offset, used by GameTick's RLE blit
 * loop) is folded into this array - see GameTick.c. */
uint8_t DAT_005b1d70[0x160];
/* g_installPath (Location)/g_screenPath (Screen, copy-fallback target for
 * the same value - see the copy loop right after both RegQueryValueExA
 * calls in LoadClientSettingsFromRegistry.c): both told 0x400 (1024)
 * bytes of real capacity (`local_14 = 0x400;`, unchanged across both
 * calls), matching the real gap to each one's next symbol exactly
 * (0x22d0-0x1ed0=0x400, 0x3368-0x2f68=0x400). Were 1-byte placeholders -
 * see g_brokerHost's comment below for the live-reproduced sibling bug. */
uint8_t g_installPath[0x400];
uint8_t DAT_005b22d0;
/* DAT_005b26d0 (GameBuddy Executable path): told 0x400 bytes
 * (`local_14 = 0x400;`), matching the real gap to the next symbol
 * (0x2ad0-0x26d0=0x400). Was a 1-byte placeholder. */
uint8_t DAT_005b26d0[0x400];
/* g_brokerHost (the broker "IP" registry value, the actual host
 * State02_ServerSelect_OnEnter's BeginServerConnect connects to) was a
 * 1-byte placeholder despite LoadClientSettingsFromRegistry.c telling
 * RegQueryValueExA it has 0x80 (128) bytes of real capacity
 * (`local_14 = 0x80;`) - matching the real gap to the next symbol
 * exactly (0x2b50-0x2ad0=0x80). LIVE-REPRODUCED: with a real "IP"
 * registry value present (e.g. "127.0.0.1"), the write overflowed this
 * 1-byte allocation into DAT_005b2b50/2b54 (the adjacent GameBuddy-port
 * and connection-object globals), corrupting them and hanging the very
 * first GameTick call (0 CPU usage - a genuine block, not a busy loop -
 * consistent with a corrupted synchronization/connection object).
 * Reproducing this needed a REAL non-empty registry value - previous
 * bring-up sessions never had HKCU\Software\Softnyx\GunBound populated
 * at all, so RegQueryValueExA always failed cleanly and this 1-byte
 * buffer was simply never written. */
uint8_t g_brokerHost[0x80];
/* DAT_005b2b50 (GameBuddy's own port, read via PTR_DAT_00552788): told
 * 4 bytes (`local_14 = 4;`, a DWORD), matching the real gap to the next
 * symbol (0x2b54-0x2b50=4). Was a 1-byte placeholder - same overflow
 * class as g_brokerHost above. */
uint32_t DAT_005b2b50;
uint32_t DAT_005b2b54;
uint32_t DAT_005b2b58;
uint32_t DAT_005b2b5c;
uint32_t DAT_005b2b60;
uint32_t g_lastServerIndex;
/* DAT_005b2b68 (ShopURL): registry read told 0x80 (128) bytes
 * (`local_14 = 0x80;`); its OWN fallback path (when no registry value
 * exists - the default "http://shop.gunbound.com/avatar/" case, which
 * is what every bring-up run without an explicit ShopURL value hits)
 * unconditionally copies 10 dwords = 40 bytes via `*puVar5 =
 * *(undefined4*)pcVar4; puVar5 = puVar5 + 1;`. Was declared `uint32_t`
 * (4 bytes) - the 40-byte fallback write alone already overflowed it on
 * every prior bring-up run, independent of any registry state; widened
 * to array form matching the registry read's own larger size hint. */
uint8_t DAT_005b2b68[0x80];
uint8_t g_screenPath[0x400];
/* DAT_005b3368 (GameName): told 0x80 bytes (`local_14 = 0x80;`),
 * matching the real gap to the next symbol (0x33e8-0x3368=0x80). Was a
 * 1-byte placeholder. */
uint8_t DAT_005b3368[0x80];
/* g_brokerPort (the broker "Port" registry value, paired with
 * g_brokerHost above): RegQueryValueExA reads it with `local_14 = 4;`
 * (a DWORD) but it was declared uint16_t (2 bytes) - a second, smaller
 * overflow in the exact same live-reproduced hang (see g_brokerHost's
 * comment). Widened to match the real DWORD size. */
uint32_t g_brokerPort;
uint32_t DAT_005b33f0;
uint16_t DAT_005b33f4;
uint32_t DAT_005b3424;
uint32_t DAT_005b3438;
uint16_t DAT_005b343c;
/* DAT_005b3440 (the launcher session blob) moved to globals_sized.c - it is
 * written as 0x30 bytes and read at +0x10/+0x20, so it cannot stay a 1-byte
 * scalar here. The extern in globals.h deliberately stays `uint8_t` (the
 * established sized-global idiom); see globals_sized.c for the derivation. */
uint32_t DAT_005b3480;
uint32_t g_clientContext;
uint32_t DAT_005b3488;
uint32_t g_screenPitch;
/* g_fullWidthFontGlyphs (was DAT_005b3628, the full-width/CJK bitmap-font
 * glyph table) is sized to 0xc0000 in globals_sized.c - see the comment there. */
uint8_t DAT_005f2f40;
uint8_t DAT_005f2f58;
uint8_t DAT_005f3158;
uint8_t DAT_005f325c;
uint8_t DAT_005f32dc;
uint8_t DAT_005f375c;
uint8_t DAT_005f3760;
uint8_t DAT_005f376c;
uint8_t DAT_00666d73;
/* DAT_00673628: the ASCII bitmap-font glyph table - promoted to the real
 * 0xc00-byte array in globals_sized.c (256 glyphs x 12 bytes). */
int *DAT_00674f68;
/* Was 4 separate uint8_t globals (DAT_006773b4/b8/bc/c0, 4 bytes apart in
 * the original binary) treated at every call site as one contiguous RECT
 * via (LPRECT)&DAT_006773b4 - but as 4 independent linker-placed symbols
 * they had no guaranteed relative layout, AND each 1-byte store silently
 * truncated the real LONG values being written (e.g. `_DAT_006773bc = 800`
 * really wrote 800 & 0xff = 32 into a single byte). This made PresentFrame's
 * Blt() source/dest rect garbage, which explains a real-hardware-confirmed
 * rendering pipeline (LockBackBuffer succeeds, sprite data found, blit
 * reached) never actually showing anything - the final present blt used a
 * corrupt rect. Unified into one real RECT-shaped array; see
 * InitDirectDraw.c/PresentFrame.c for the call sites. */
int32_t g_presentDstRect[4];
/* Two DDPIXELFORMAT slots (0x20 bytes = 8 dwords each): the 16-bit RGB and
 * DXT/FourCC texture formats matched by EnumTextureFormatsCallback and read
 * back by CreateTextureAtlasSurface. Were lone uint32_t, so the 8-dword copy overflowed
 * 28 bytes into adjacent globals. */
uint32_t DAT_00677544[8];
uint32_t DAT_006777e8[8];
/* 0x8000-entry sqrt lookup table (32768 * 4 = 0x20000 bytes), filled by
 * InitFastSqrtTables (was FUN_004f1eb0) and read by FUN_004ed300. Was a lone uint32_t; its sibling
 * table DAT_006990c0 sits exactly 0x20000 bytes higher in the original
 * image, confirming the real size. Undersized, the fill loop wrote past
 * the end of the whole executable image and faulted. */
uint32_t DAT_006790c0[0x8000];
uint8_t DAT_0067e348;
uint8_t DAT_0067ec60;
uint8_t DAT_0067ec64;
uint8_t DAT_0067ec68;
/* DAT_0067ec70 is not a real global - it is arena offset 0x67ec70, now a
 * fixed-address offset-macro in globals.h (see the comment there). */
/* 0x8000-entry sqrt lookup table, sibling of DAT_006790c0 above - see its
 * comment. */
uint32_t DAT_006990c0[0x8000];
/* DAT_0069ec74 is not a real global - it is arena offset 0x69ec74, now a
 * fixed-address offset-macro in globals.h (see the arena-offset note and
 * that macro's own 2026-07-31 comment - was a real global, the wild-
 * pointer bug behind the AVATAR-transition crash). */
uint8_t DAT_006a6481;
uint8_t DAT_006a64a4;
uint8_t DAT_006a64a8;
uint8_t DAT_006a64ac;
uint8_t DAT_006a64bc;
uint8_t DAT_006a64c0;
uint8_t DAT_006a76fc;
uint8_t DAT_006aa424;
uint8_t DAT_006aa47b;
uint8_t DAT_006aa47c;
uint8_t DAT_006aa624;
uint8_t DAT_006aa664;
uint8_t DAT_006aa666;
uint8_t DAT_006aa668;
uint8_t DAT_006aa674;
uint32_t DAT_006b90f8; /* holds a void* from AllocSpriteRegistryNode (was uint8_t, which
                        * truncated the pointer to 1 byte -> InitSpriteRegistryPool wrote
                        * through [byte+8] and faulted) */
/* 0x400-entry block table for the 12-byte-record pool (AllocSpriteRegistryNode alloc,
 * InitSpriteRegistryPool reset). Was a lone uint32_t, so the reset's 0x1000-byte zero
 * ran off the end and wiped adjacent globals (e.g. g_pBackBufferSurface). */
uint32_t DAT_006b9100[0x400];
uint8_t DAT_006ba1fc;
uint8_t DAT_006ba244;
uint32_t DAT_00792190;
uint8_t DAT_00792194;
uint8_t DAT_00792198;
/* 0x400-entry block table for the 0x80-byte-record pool (AllocTextureCacheNode alloc,
 * InitTextureCachePool reset) - the sibling of DAT_006b9100; same undersizing bug. */
uint32_t DAT_007921b0[0x400];
uint16_t DAT_00793228;
uint8_t g_chatInputActive;
uint32_t g_chatInputMaxLength;
/* g_chatInputText: moved to src/globals_sized.c - the CPanelManager ctor
 * (PanelManager_Construct, orig 0x507dc0) zeroes 0x40 DWORDS (0x100 bytes) from
 * here, so a one-dword cell would clobber ~0xfc bytes of neighbours. */
uint8_t DAT_007934c4;
uint32_t DAT_007934c8;
uint8_t DAT_007934cc;
uint32_t DAT_007934d8;
uint32_t DAT_007934e0;
uint32_t g_sharedTextInputControl;
uint32_t g_connectionContextA;
uint32_t g_connectionContextB;
uint32_t DAT_007934f0;
uint32_t g_directLinkConnection;
uint8_t DAT_007934f8;
uint32_t DAT_007934fc;
uint32_t DAT_00793500;
uint32_t g_frameCounter;
uint8_t DAT_0079350c;
uint8_t DAT_0079350d;
uint32_t g_cursorDirection;
uint8_t g_valueGuardTamperFlag;
uint8_t DAT_00793515;
uint8_t DAT_00793516;
uint8_t DAT_00793517;
uint8_t DAT_00793518;
uint8_t DAT_0079351c;
uint8_t DAT_00793520;
uint8_t DAT_00793521;
uint8_t g_bBattleSessionActive;
uint8_t DAT_00793529;
uint8_t DAT_0079352a;
uint32_t g_screenSurface;
uint32_t g_clipMinX;
uint32_t g_clipMinY;
uint32_t DAT_00793544;
uint32_t g_dinputDeviceCount; /* 0x793540 */
uint8_t g_soundAvailable;
uint8_t DAT_0079354a;
uint8_t DAT_0079354b;
int *g_directSound;
int *g_primarySoundBuffer;
void **g_soundChannels;
int *g_secondarySoundBuffers;
uint32_t g_soundWindow;
uint32_t g_soundChannelCount;
uint8_t DAT_00793568;
uint32_t DAT_007935e8;
uint32_t DAT_007935ec;
uint8_t DAT_00793610;
uint8_t DAT_00793611;
uint32_t g_currentBlendMode;
uint8_t DAT_00793618;
uint32_t DAT_00793634;
uint32_t DAT_00793640;
uint32_t DAT_0079364c;
uint32_t g_frameTriangleCounter;
uint32_t DAT_00793660;
uint8_t DAT_00793664;
uint32_t g_valueGuardKeyTable;
uint8_t g_valueGuardMap;
int *DAT_00793774;
uint32_t DAT_00793778;
uint32_t g_gameEventRingWriteIndex;
uint32_t g_gameEventRingReadIndex;
uint8_t g_gameEventTypeRing;
uint8_t g_gameEventDataRing;
/* DAT_00794bf0: moved to globals_sized.c (0x224 CValueGuard cell). */
/* DAT_00794e14: moved to globals_sized.c (0x30-byte container-policy object
 * that HashMap_Construct constructs through it). */
/* The input-event ring buffer (write/read cursors + 3 field arrays) is now
 * ONE contiguous object g_inputEventRing in globals_sized.c, reached through
 * the offset-macros in globals.h - see the comment there. The five fields
 * MUST be contiguous because EnqueueInputEvent walks the whole ring off the write
 * cursor's address. */
uint8_t DAT_00796878;
/* DAT_00796aa0: moved to globals_sized.c (0x224 CValueGuard cell). */
/* g_localizedStringTable: moved to globals_sized.c - the whole string
 * map lives at this address, not one byte */
uint8_t g_cursorTexture;
uint32_t g_cursorFrame;
/* Worker-thread control block for FUN_00415530/FUN_004156c0/FUN_00415810 -
 * same shape as DAT_00e9c334 above, but the running flag is at +0xc here.
 * Sized to 0x10 (not 0x20 like its sibling) since DAT_007a768c, the very
 * next declared global, is only 0x10 bytes higher (0x7a768c-0x7a767c). */
uint8_t DAT_007a767c[0x10];
uint8_t DAT_007a768c;
/* Standalone CValueGuard cell - see globals.h. */
/* DAT_007a7690: moved to globals_sized.c (0x224 CValueGuard cell). */
uint8_t DAT_00d9aa20;
uint8_t DAT_00d9aa24;
uint8_t DAT_00d9aa28;
uint8_t DAT_00d9aa2c;
uint8_t DAT_00d9aa30;
uint8_t DAT_00d9aa34;
uint8_t DAT_00d9aa35;
/* DAT_00e525e8: moved to globals_sized.c (0x224 CValueGuard cell). */
/* DAT_00e52814/38/3c/58-5c/64/68 and DAT_00e52e68 were split fields of
 * the keyboard singleton at 0xe52810 (+4, +0x28, +0x2c, +0x48..+0x4c,
 * +0x54, +0x58, +0x658). Users address g_keyboardDeviceTimerBlock now. */
/* DAT_00e5369c, g_cursorDeltaX/Y, DAT_00e536e4, DAT_00e536ec are fields
 * inside the coalesced g_mouseDeviceTimerBlock (offset macros in
 * globals.h; storage in globals_sized.c since 2026-09-01). */
/* Zeroed backing for the three per-tick input/cursor timer blocks GameTick
 * updates every elapsed tick. In the original these are static singletons at
 * fixed addresses - the mouse DirectInput device (0xe53698), the keyboard
 * device (0xe52810), and the software-cursor animation object (0x7a7644) -
 * constructed by MouseDevice_Construct / KeyboardDevice_Construct / the cursor init. The
 * Initialize methods (CreateDevice/Acquire) are bring-up-stubbed (they skip DirectInput acquisition, see
 * MouseDevice_Initialize.c), so the singletons never exist and GameTick's literal-address
 * timer calls dereferenced unbacked memory and faulted. Each consumer only
 * decrements already-nonzero timer fields (MouseDevice_TickButtonTimers at +0x68..+0x84,
 * KeyboardDevice_TickKeyTimers at +0x258..+0x654) or is gated on an enable flag
 * (AdvanceSpriteAnimation on +0x20), so zeroed backing is a correct no-op for
 * the input-less logo path. Sized to cover each function's highest field read.
 *
 * KNOWN DIVERGENCE: the original devices' other fields are modelled as the
 * scattered separate globals around here (DAT_00e5369c, g_cursorDeltaX, the
 * g_cursor* set, etc.); those do NOT alias into these arrays. Harmless while
 * no real input device is acquired. */
/* g_mouseDeviceTimerBlock moved to globals_sized.c, expanded 0x88 ->
 * 0x5a8: the full DirectInput mouse/cursor singleton, coalescing the
 * split fields around it; its constructor MouseDevice_Construct now runs from
 * the startup hook. The KNOWN DIVERGENCE above is resolved for the
 * mouse object, and (2026-10-30) for the keyboard object below; the
 * cursor-anim block is unchanged. */
/* Keyboard singleton, 0xe52810. 0xc5c is the proven extent: the poll
 * 0x4ede50 reads its record count as [esi+0xc58] (0x4ede63/0x4edf65) and
 * fills 0x40 x 0x14-byte records from +0x758 below it. The 4 bytes above,
 * 0xe5346c, have no reference anywhere in the image, and 0xe53470 is the
 * separate 0x224-byte CValueGuard cell DAT_00e53470 (WinMain guard slot 12,
 * `mov edi,0xe53470` at 0x40da56/0x5410a3), so the object is not
 * 0xe88 (the full gap to the mouse at 0xe53698). */
uint8_t g_keyboardDeviceTimerBlock[0xc5c];
uint8_t g_softwareCursorAnimBlock[0x38];
/* DAT_00e53c24/28/2c/30 are the cursor-bound dwords at
 * g_mouseDeviceTimerBlock+0x58c..+0x598 - offset macros in globals.h. */
/* Cursor mode flag: 1 = free/absolute (the software cursor's anchor tracks
 * the mouse), 0 = locked/relative (WndProc WM_MOUSEMOVE re-centers via
 * SetCursorPos and holds the anchor - battle aim mode). Only State11 (battle)
 * writes it (1=free, 0=aim; OnExit restores 1); it's a runtime-set BSS global
 * that nothing in the reconstruction initializes for the menus, so it
 * defaulted to 0 and the menu cursor was locked at (0,0). Default it to the
 * menu/free value 1 so the cursor tracks outside battle. (2026-07-18) */
/* g_cursorFreeMode is the byte at g_mouseDeviceTimerBlock+0x5a4 (macro
 * in globals.h). Its old hand-set `= 1` is retired: MouseDevice_Construct - the
 * original's own constructor, now run from the startup hook - writes
 * exactly that byte to 1. */
/* g_uiPanelManager was a 1-byte placeholder, but the code dereferences it as
 * a container object: PanelManager_DispatchMouseMove/f1b0/f1f0/f150/f230 (WndProc's mouse/key
 * handlers) read its list head at +4, and PanelManager_* touch +4/+5/+8. With
 * only 1 byte of storage, those reads ran off the end into whatever global the
 * linker happened to place next and walked a garbage "widget list", jumping to
 * a junk vtable pointer (crash at eip=0xfff0e483 on the first WM_MOUSEMOVE).
 *
 * 2026-07-14: found + decompiled the REAL constructor (PanelManager_Construct,
 * .CRT$XCU-registered via FUN_00540dc0 - same hidden-static-initializer
 * pattern as g_clientContext's own ClientContext_Constructor). Confirms the true
 * object layout and size:
 *   +0x00: vtable pointer (&PTR_FUN_00557cfc) - zero live callers ever
 *          dereference it (checked via a full-binary xref search), left
 *          zeroed rather than reconstructing an unused vtable.
 *   +0x04: list head (=0)      - PanelManager_Register's own "piVar1"
 *   +0x08: list tail (=0)      - PanelManager_Register's "in_EAX+8"
 *   +0x0c: (=0), unused by any currently-ported reader
 *   +0x10: chunk-list head (=0)   - PanelManager_GrowNodePool's "+0xc"
 *          (GrowNodePool/PrependNode's own "manager" param is this
 *          object's base+4, so their internal +0xc/+0x10/+0x14 map to
 *          this object's absolute +0x10/+0x14/+0x18)
 *   +0x14: free-list head (=0)    - GrowNodePool/PrependNode's "+0x10"
 *   +0x18: grow-count seed (=10)  - GrowNodePool/PrependNode's "+0x14";
 *          this is the field that was missing entirely before (object
 *          only sized to 16 bytes) - GrowNodePool only populates the
 *          free-list when this is nonzero, so on unsized/zeroed memory
 *          the free-list never grew and the first real PrependNode call
 *          unconditionally NULL-deref'd its head.
 * Real size 0x1c (28) bytes, sentinel/grow-count init in crt_shims_msvc.c's
 * gb_startup_init (gb_init_panel_manager). The KNOWN DIVERGENCE below
 * (Ghidra's split-out DAT_00e53c44/DAT_00e53c48 aliases) is unaffected by
 * this resize - still separate storage, not unified. */
uint8_t g_uiPanelManager[0x1c];
uint32_t DAT_00e53c44;
uint32_t DAT_00e53c48;
/* DAT_00e53e88 was a 1-byte placeholder despite ~25 callers (chat log,
 * replay recording, ProcessPacket handlers across several states) passing
 * its address opaquely to helper functions. FUN_004022b0.c's own recovered
 * fix confirms a hard lower bound: it walks a `+4`-rooted sentinel list
 * and writes an int count to `+0xf24`, so real storage must cover at
 * least 0xf28 bytes - sized to that confirmed minimum, matching the same
 * incremental-resize idiom used for g_activeObjectRegistry/g_spriteDrawBatchPool. Its `+4`
 * sentinel-list head is self-referencing-initialized in crt_shims_msvc.c's
 * gb_startup_init (same treatment as those two registries) - the other
 * ~25 callers' own offset requirements beyond this confirmed 0xf28-byte
 * lower bound are still untraced, so the struct may need to grow further
 * once those call sites are individually recovered. */
/* DAT_00e54a9c/aa0/da8, DAT_00e55a34/45/46/54/58/64: now offset-macros into
 * DAT_00e53e88 - see the note on it below. */
/* (FUN_00401ee0 in the note below is now RemoveDirectLinkBuddyNode.) */
/* (FUN_00402300 in the note below is now ProcessIncomingWhisper.) */
/* (FUN_00402cf0 in the note below is now DeleteBuddyByNickname.) */
/* Resized 0xf28 -> 0x1bf0 (2026-08-24).  Wiring FUN_00402300's `this` to this
 * object made its writes at +0xf28.., +0x15a8 and +0x1bb0 reachable, and
 * FUN_00402cf0 / FUN_00401ee0 / RBTree_RemoveNode already read +0x15b0, +0x1bdc
 * and +0x1be4.  Nine globals that Ghidra had declared separately lie INSIDE
 * that extent -- one of them (DAT_00e54da8, +0xf20) inside even the old size
 * -- and are now offset-macros into this storage (see globals.h), so a write
 * through the object and a read through the field name see the same byte.
 * 0x1bf0 stops short of the CValueGuard cell at +0x1c30 (DAT_00e55ab8). */
uint8_t DAT_00e53e88[0x1bf0];
/* DAT_00e55ab8: moved to globals_sized.c (0x224 CValueGuard cell). */
/* (FUN_004e77e0 in the note below is now BroadcastRingEvent.) */
/* g_replayContext (was DAT_00e55ce0): moved to globals_sized.c (0x454f9-byte struct - battle/replay turn-event buffer; real extent established via FUN_004e84c0/FUN_004e7b60/FUN_004e80d0/FUN_004e77e0/FUN_004e7de0/FUN_004e6050, all of which take &g_replayContext as their context arg; the ~42 other DAT_00e5.../DAT_00e9... globals formerly declared here in this offset range are now offset-macros into that storage - see globals.h). The CRITICAL_SECTION at +0x45264 (DAT_00e9af44) IS covered by this array -- 0x45264 < 0x454f9 -- and is now an offset-macro into it rather than separate storage; this comment previously asserted the opposite. */
/* DAT_00e9af44: moved to globals_sized.c (CRITICAL_SECTION) */
uint8_t DAT_00e9b4e8;
uint8_t DAT_00e9b4ea;
uint8_t DAT_00e9b4fd;
uint8_t DAT_00e9b50a;
uint8_t DAT_00e9b58a;
uint8_t DAT_00e9b60a;
uint8_t DAT_00e9b68a;
uint8_t DAT_00e9b70a;
uint8_t DAT_00e9b78a;
uint8_t DAT_00e9b80a;
uint8_t DAT_00e9b80c;
uint8_t DAT_00e9b810;
/* DAT_00e9b818: moved to globals_sized.c (0x224 CValueGuard cell). */
/* DAT_00e9ba40: moved to globals_sized.c (0x224 CValueGuard cell). */
/* g_activeObjectRegistry/g_activeObjectRegistry2 were 1-byte placeholders, but SweepActiveObjectRegistry's
 * header (and InvokeWidget.c's already-fixed traversal) established these
 * are two independent 32-byte "8-word" flat-ButtonWidget registry roots -
 * each doubling as its own embedded circular-list sentinel node (self-
 * referencing link fields, same design FUN_004f2f00's real node ctor uses
 * for every OTHER node it allocates). With only 1 byte of storage, every
 * reader (FindActiveObjectAt/HandleActiveObjectMouseMove/HandleActiveObjectMouseDown/HandleActiveObjectMouseUp/
 * HandleBackgroundActiveObjectMouseDown/SweepActiveObjectRegistry/DrawActiveObjectRegistry/FUN_004f2fb0/InvokeWidget - all
 * of which read `*(registryRoot+4)` unconditionally, no null-check) ran
 * off the end into whatever followed and dereferenced garbage, crashing
 * on the very first WM_MOUSEMOVE. Sized to 0x20 bytes; gb_startup_init
 * (crt_shims_msvc.c) self-references the link fields so an empty registry
 * reads as a valid, correctly-terminating circular list - see its comment
 * for which fields and why (this mirrors the g_uiPanelManager fix above).
 *
 * KNOWN DIVERGENCE (same pattern as g_uiPanelManager/DAT_00e53c44 above):
 * DAT_00e9be94/DAT_00e9bea4/a8 are separately-
 * declared globals with their OWN storage, read directly by ~15 other
 * already-ported files - they do NOT alias into this array. Harmless
 * while these registries are never actually populated with real widgets
 * (bring-up doesn't reach button creation yet); must be unified when the
 * real 32-byte struct is properly modeled. */
uint8_t g_activeObjectRegistry[0x20];
uint32_t DAT_00e9be94;
/* DAT_00e9be98/9c are g_activeObjectRegistry+8/+0xc (hover and cache
 * slots ChangeGameState clears at 0x412330/0x412335); no separate storage. */
/* DAT_00e9bea0 is g_activeObjectRegistry+0x10 (the ring pointer InitGame
 * stores at 0x40ed16); no separate storage. */
uint8_t DAT_00e9bea4;
/* DAT_00e9bea8: moved to globals_sized.c (0x30-byte container-policy object
 * that HashMap_Construct constructs through it). */
/* DAT_00e9bed8: moved to globals_sized.c (0x224 CValueGuard cell). */
uint8_t g_activeObjectRegistry2[0x20];
/* DAT_00e9c104 is g_activeObjectRegistry2+8, the focused text box
 * (SyncActiveTextInput's [eax+8]); no separate storage. */
/* DAT_00e9c108 is g_activeObjectRegistry2+0xc (the ring pointer InitGame
 * stores at 0x40ed1b); no separate storage. */
/* Worker-thread control block for WorkerThread_Start/WorkerThreadProcThunk/WorkerThreadEventLoop:
 * +4 thread handle (uintptr_t), +8/+0xc two wait handles, +0x10 running flag.
 * Was completely undeclared (the raw ports take it via a dropped ESI
 * register). DAT_00e9c33c (a HANDLE SetEvent'd in Shutdown.c) is this same
 * struct's +8 field under its own Ghidra-assigned symbol - sized to absorb
 * it (0xe9c33c - 0xe9c334 = 8) rather than declare overlapping storage. */
uint8_t DAT_00e9c334[0x14];
/* DAT_00e9c344 is this block's +0x10 RUNNING FLAG, now an offset-macro into
 * it (see globals.h) rather than separate storage.  DAT_00e9c348 (+0x14) is
 * NOT part of the block -- it is the InterlockedExchange'd window-active flag
 * used by WndProc/InitGame/UpdateDeviceAcquisition -- so the array is sized
 * 0x14 to stop short of it rather than 0x18. */
uint8_t DAT_00e9c348;
/* DAT_00e9c9c8/cc/d0 are now offset-macros into g_workerThreadBlock;
 * their storage lives in globals_sized.c. */
/* DAT_00e9c9dc/DAT_00e9c9e0: the word-filter AtlArray header's data-ptr and
 * count fields - now offset-macros into g_wordFilterArrayHeader in
 * globals_sized.c (see that file's comment), not independent storage. */
/* The global sprite registry - the same 0x20-byte sentinel-node circular-list
 * container as the two active-object registries (g_activeObjectRegistry/g_activeObjectRegistry2):
 * LoadSpriteSet/RegisterTankSprite/LoadAvatarSprites all populate it through
 * FUN_004f2f00 (the shared node allocator) and FindSpriteFrame walks it via the
 * same *(root+4) head / +0x1c outer-next idiom. Was a 1-byte placeholder, so
 * FindSpriteFrame ran off the end; sized to 0x20 and sentinel-initialised by
 * gb_startup_init (crt_shims_msvc.c) so an empty registry terminates cleanly
 * and inserts link correctly. See [[bringup-frontier-mouse-hittest]]. */
uint8_t g_spriteRegistry[0x20];
uint32_t DAT_00ea0e1c;
uint32_t DAT_00ea0e28;
uint32_t DAT_00ea0e2c;
uint8_t DAT_00ea0e38;
uint8_t DAT_00ea0e3c;
uint8_t DAT_00ea0e40;
uint8_t DAT_00ea0e4c;
uint8_t DAT_00ea0e50;
uint8_t DAT_00ea0e5c;
uint8_t DAT_00ea0e60;
uint32_t DAT_00ea0e64;
uint32_t DAT_00ea0e70;
uint32_t DAT_00ea0e74;
uint8_t DAT_00ea0e80;
uint8_t DAT_00ea0e84;
uint8_t DAT_00ea0e88;
uint8_t DAT_00ea0e94;
uint8_t DAT_00ea0e98;
uint8_t DAT_00ea0ea4;
uint32_t DAT_00ea0ea8;
uint8_t DAT_00ea0eac;
uint32_t DAT_00ea0f54;
uint8_t DAT_00eb168c;
/* DAT_00eb1bd8: the named-texture-cache singleton - promoted to the real
 * 0x40200-byte g_textureCache in globals_sized.c (a one-byte cell under-
 * sized it; FlushTextureCache zeroes a table at +0x401bc). */
/* DAT_00f11dd0: the graphics.xfs archive singleton - promoted to the
 * real 0x10740-byte XFSArchive g_graphicsArchive in globals_sized.c
 * (a one-byte cell here under-sized it; OpenXFSArchive reads +0x1040). */
uint32_t DAT_00f11dd4;
uint8_t DAT_00f11de0;
uint8_t DAT_00f12e14;
uint8_t DAT_00f12e18;
/* IID_IDirect3DHALDevice. In the original this is a BSS global populated at
 * startup by a small init routine (0x542900) that copies it in from a
 * separate .data constant; here it's just given the GUID value directly.
 * Was declared uint8_t (1 byte), so CreateDevice/EnumZBufferFormats - which
 * take &DAT_00f22504 as a 16-byte REFCLSID - read 15 bytes of adjacent
 * memory as part of the "GUID" and (since nothing ever wrote the real
 * value) actually passed an all-zero CLSID. */
GUID DAT_00f22504 = {0x84e63de0, 0x46aa, 0x11cf, {0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e}};
/* The sprite-draw batch pool. Its first 0x400 entries are the page-pointer
 * table cleared at the end of InitDirectDraw and freed by ShutdownDirectDraw/
 * FUN_00543970 (both loop 0..0xfff). But FUN_004e9070 (the per-frame pool
 * reset, called from GameTick) also accesses this same base register-relative
 * well past 0x1000: +0x1000 write index, +0x1004 u16, +0x1008 entry count, and
 * a 0x400-entry output-pointer array at +0x100c..+0x200b (piVar5). Those live
 * in the original as one contiguous 0x200c-byte structure (next symbol is at
 * 0xf2465c = base+0x200c); Ghidra mislabelled the control words and the output
 * array's head as the separate globals DAT_00f23650/54/58 and g_nCompositorLayer
 * just below, which do NOT alias into a [0x400] array. Sized to the real 0x803
 * words so every base-relative access lands in backed, zeroed storage: the
 * count reads 0 until FUN_004e93e0 queues a batch, so FUN_004e9070's loop is a
 * clean no-op on the logo path instead of reading an out-of-bounds garbage
 * count and running the output writes off the end. (Was a lone uint32_t, then
 * [0x400] - each prior size still ran the code's higher accesses off the end.) */
uint32_t g_spriteDrawBatchPool[0x803];
uint8_t DAT_00f23650;
uint8_t DAT_00f23654;
uint8_t DAT_00f23658;
int32_t g_nCompositorLayer;
const char s_Acks_will_not_be_send_00552d04[] = "Acks will not be send";
const char s_AutoRefresh_00552818[] = "AutoRefresh";
const char s_AvataEffectTexture1_00556900[] = "AvataEffectTexture1";
const char s_AvataEffectTexture2_005568ec[] = "AvataEffectTexture2";
const char s_AvataTexture1_0055565c[] = "AvataTexture1";
const char s_AvataTexture2_00556914[] = "AvataTexture2";
const char s_Avatar_xfs_00553660[] = "Avatar.xfs";
const char s_Background_00552800[] = "Background";
const char s_BuddyIP_005527d4[] = "BuddyIP";
const char s_BuddyPort_005527c8[] = "BuddyPort";
const char s_BulletTexture1_00556880[] = "BulletTexture1";
const char s_BulletTexture2_00556870[] = "BulletTexture2";
const char s_ChannelName_005527e8[] = "ChannelName";
const char s_CharEffectTexture1_005568a4[] = "CharEffectTexture1";
const char s_CharEffectTexture2_00556890[] = "CharEffectTexture2";
const char s_CharacterTexture1_005568d8[] = "CharacterTexture1";
const char s_CharacterTexture2_005568c4[] = "CharacterTexture2";
const char s_ChooseEvent_txt_00551fcc[] = "ChooseEvent.txt";
const char s_CrashTexture_00555b80[] = "CrashTexture";
const char s_DirectDrawCreateEx_005574fc[] = "DirectDrawCreateEx";
const char s_DirectInput8Create_00557414[] = "DirectInput8Create";
const char s_DirectSoundCreate8_005574ac[] = "DirectSoundCreate8";
const char s_Effect3D_0055280c[] = "Effect3D";
const char s_EffectVolume_00552824[] = "EffectVolume";
const char s_Executable_0055278c[] = "Executable";
const char s_Feel_ethereal_____00552d24[] = "Feel ethereal...!";
const char s_FirewallTexture_00555bb0[] = "FirewallTexture";
const char s_FlameTexture1_00556860[] = "FlameTexture1";
const char s_FlameTexture2_00556850[] = "FlameTexture2";
const char s_FlameTexture3_00556840[] = "FlameTexture3";
const char s_FlameTexture4_00556830[] = "FlameTexture4";
const char s_FlameTexture_d_00556778[] = "FlameTexture%d";
const char s_FourWord_txt_00552c3c[] = "FourWord.txt";
const char s_GameName_005527f4[] = "GameName";
const char s_Game_Programmer___comsik_00553538[] = "Game Programmer - comsik";
const char s_GunBound_00552748[] = "GunBound";
const char s_JewelTexture_005567c0[] = "JewelTexture";
const char s_Language_005527dc[] = "Language";
const char s_Language_txt_00554008[] = "Language.txt";
const char s_LaserEffect_00556794[] = "LaserEffect";
const char s_LastServer_00552884[] = "LastServer";
const char s_LightningTexture_00555b9c[] = "LightningTexture";
const char s_Lightning_00555b90[] = "Lightning";
const char s_Location_00552878[] = "Location";
const char s_MidiMode_00552840[] = "MidiMode";
const char s_MouseSpeed_0055284c[] = "MouseSpeed";
const char s_MusicVolume_00552834[] = "MusicVolume";
const char s_Oh___It_s_CozY_here______00553498[] = "Oh~! It's CozY here ^-^*";
const char s_RayonTexture1_00556820[] = "RayonTexture1";
const char s_RayonTexture2_00556810[] = "RayonTexture2";
const char s_RefreshRate_0055201c[] = "RefreshRate";
const char s_RiderTexture_005567e0[] = "RiderTexture";
const char s_STATIC_00557b50[] = "STATIC";
const char s_Screen_00552870[] = "Screen";
const char s_Server___Game_buddy_Programmer___0055322c[] = "Server & Game buddy Programmer - reddragon";
const char s_ShootingMode_00552858[] = "ShootingMode";
const char s_ShopURL_005527c0[] = "ShopURL";
const char s_SoftnyxGunBound_gme_00552764[] = "SoftnyxGunBound.gme";
const char s_Softnyx_00552754[] = "Softnyx";
const char s_Software_Softnyx_GameBuddy_0056d3bc[] = "Software\\Softnyx\\GameBuddy";
const char s_Software_Softnyx_GunBound_0056d3a0[] = "Software\\Softnyx\\GunBound";
const char s_Sound_txt_00557218[] = "Sound.txt";
const char s_SpecialTexture1_00556800[] = "SpecialTexture1";
const char s_SpecialTexture2_005567f0[] = "SpecialTexture2";
const char s_System_CurrentControlSet_Service_00552040[] = "System\\CurrentControlSet\\Services\\Class\\%s";
const char s_TagTexture_005568b8[] = "TagTexture";
const char s_Template_0055273c[] = "Template";
const char s_ThorTexture1_005567b0[] = "ThorTexture1";
const char s_ThorTexture2_005567a0[] = "ThorTexture2";
const char s_TornadoTexture_00555bc0[] = "TornadoTexture";
const char s_Version_00552868[] = "Version";
const char s_WaterEffect_00556788[] = "WaterEffect";
const char s_WeaterTexture_00557224[] = "WeaterTexture";
const char s_YesooriTexture_005567d0[] = "YesooriTexture";
const char s__04d__02d__02d_00555640[] = "%04d-%02d-%02d";
const char s__05d_img_00555a08[] = "%05d.img";
const char s__Y_m_d__H_M_005570bc[] = "%Y%m%d %H%M";
const char s___15s_00553590[] = "%-15s";
const char s__cb_05d_img_00552200[] = "%cb%05d.img";
const char s__cb_05dl_img_005521cc[] = "%cb%05dl.img";
const char s__cg_05d_img_005521f4[] = "%cg%05d.img";
const char s__cg_05dl_img_005521bc[] = "%cg%05dl.img";
const char s__ch_05d_img_005521e8[] = "%ch%05d.img";
const char s__ch_05dl_img_005521ac[] = "%ch%05dl.img";
const char s__d__d__d__d_00557138[] = "%d.%d.%d.%d";
const char s__dmoon_xes_0055674c[] = "%dmoon.xes";
const char s__sADB_exe_00552730[] = "%sADB.exe";
const char s__s__3d__3d__005536b8[] = "%s[%3d/%3d]";
const char s__s_d_img_0055723c[] = "%s%d.img";
const char s__s_s_07d_bmp_00552220[] = "%s%s%07d.bmp";
const char s__s_s____s_sv_005570ac[] = "%s%s - %s.sv";
const char s_active_00551e58[] = "active";
const char s_avata_00553fa8[] = "avata";
const char s_b_buddy_down_00552258[] = "b_buddy_down";
const char s_b_buddy_exit_00552248[] = "b_buddy_exit";
const char s_b_buddy_up_00552268[] = "b_buddy_up";
const char s_b_error_confirm_00552238[] = "b_error_confirm";
const char s_b_gamelist_avatar_00553760[] = "b_gamelist_avatar";
const char s_b_gamelist_buddy_00553788[] = "b_gamelist_buddy";
const char s_b_gamelist_buddydown_005522a4[] = "b_gamelist_buddydown";
const char s_b_gamelist_buddyup_005522bc[] = "b_gamelist_buddyup";
const char s_b_gamelist_channeldown_00552274[] = "b_gamelist_channeldown";
const char s_b_gamelist_channelup_0055228c[] = "b_gamelist_channelup";
const char s_b_gamelist_create_0055374c[] = "b_gamelist_create";
const char s_b_gamelist_directgo_005536d0[] = "b_gamelist_directgo";
const char s_b_gamelist_exit_0055379c[] = "b_gamelist_exit";
const char s_b_gamelist_friend_005536e4[] = "b_gamelist_friend";
const char s_b_gamelist_join_0055373c[] = "b_gamelist_join";
const char s_b_gamelist_next_005536f8[] = "b_gamelist_next";
const char s_b_gamelist_prev_00553708[] = "b_gamelist_prev";
const char s_b_gamelist_ranking_00553774[] = "b_gamelist_ranking";
const char s_b_gamelist_viewall_00553728[] = "b_gamelist_viewall";
const char s_b_gamelist_wait_00553718[] = "b_gamelist_wait";
const char s_b_play_all_0055412c[] = "b_play_all";
const char s_b_play_option_00554174[] = "b_play_option";
const char s_b_play_skip_00554138[] = "b_play_skip";
const char s_b_play_tag_00554120[] = "b_play_tag";
const char s_b_play_weapon1_00554164[] = "b_play_weapon1";
const char s_b_play_weapon2_00554154[] = "b_play_weapon2";
const char s_b_play_weapon3_00554144[] = "b_play_weapon3";
const char s_b_ready_buddy_00556b40[] = "b_ready_buddy";
const char s_b_ready_button_00556afc[] = "b_ready_button";
const char s_b_ready_changeteam_00556b60[] = "b_ready_changeteam";
const char s_b_ready_character_00556b1c[] = "b_ready_character";
const char s_b_ready_exit_00556b50[] = "b_ready_exit";
const char s_b_ready_option_00556b30[] = "b_ready_option";
const char s_b_ready_ready_005570c8[] = "b_ready_ready";
const char s_b_ready_scroll_00556b0c[] = "b_ready_scroll";
const char s_b_ready_startgame_005570d8[] = "b_ready_startgame";
const char s_b_result_confirm_00554074[] = "b_result_confirm";
const char s_b_server_buddygame_00557170[] = "b_server_buddygame";
const char s_b_server_choiceserver_00557158[] = "b_server_choiceserver";
const char s_b_server_exitgame_00557144[] = "b_server_exitgame";
const char s_b_store_buddygame_00555764[] = "b_store_buddygame";
const char s_b_store_buy_005556fc[] = "b_store_buy";
const char s_b_store_cap_00555758[] = "b_store_cap";
const char s_b_store_cashcharge_005556cc[] = "b_store_cashcharge";
const char s_b_store_cloth_00555748[] = "b_store_cloth";
const char s_b_store_down_005556e0[] = "b_store_down";
const char s_b_store_dry_00555690[] = "b_store_dry";
const char s_b_store_event01_005556bc[] = "b_store_event01";
const char s_b_store_event02_005556ac[] = "b_store_event02";
const char s_b_store_exit_00555778[] = "b_store_exit";
const char s_b_store_exitem_00555718[] = "b_store_exitem";
const char s_b_store_flag_00555728[] = "b_store_flag";
const char s_b_store_gift_00555680[] = "b_store_gift";
const char s_b_store_glasse_00555738[] = "b_store_glasse";
const char s_b_store_puton_00555708[] = "b_store_puton";
const char s_b_store_sell_0055569c[] = "b_store_sell";
const char s_b_store_up_005556f0[] = "b_store_up";
const char s_b_storewindow_confirm_00555a8c[] = "b_storewindow_confirm";
const char s_b_storewindow_no_0055566c[] = "b_storewindow_no";
const char s_bfire1_005569f0[] = "bfire1";
const char s_bfire2_005569e8[] = "bfire2";
const char s_bifire_005569d8[] = "bifire";
const char s_blash45_00552f2c[] = "blash45";
const char s_bsfire_005569e0[] = "bsfire";
const char s_c__comsik_txt_00552778[] = "c:\\comsik.txt";
const char s_characterdata_dat_0055364c[] = "characterdata.dat";
const char s_chuko_00553010[] = "chuko";
const char s_class_00552074[] = "class";
const char s_clear_00552cfc[] = "clear";
const char s_comsik_00553578[] = "comsik";
const char s_cursor_005524e8[] = "cursor";
const char s_ddraw_dll_00557510[] = "ddraw.dll";
const char s_designer_00553220[] = "designer";
const char s_dinput8_dll_00557428[] = "dinput8.dll";
const char s_disable_00551e68[] = "disable";
const char s_display_00552028[] = "display";
const char s_driver_0055206c[] = "driver";
const char s_dsound_dll_005574c0[] = "dsound.dll";
const char s_enddream_0055348c[] = "enddream";
const char s_ethera_00552d58[] = "ethera";
const char s_event14__d_img_005554e8[] = "event14-%d.img";
const char s_event_d1800_img_00557248[] = "event%d1800.img";
const char s_flame_00553d2c[] = "flame";
const char s_graphics_xfs_00551fdc[] = "graphics.xfs";
const char s_guide_005535e0[] = "guide";
const char s_gunbound_ex__00552718[] = "gunbound.ex_";
const char s_gunbound_exe_00552708[] = "gunbound.exe";
const char s_http___shop_gunbound_com_avatar__00552798[] = "http://shop.gunbound.com/avatar_web.asp";
const char s_ifire_00553b60[] = "ifire";
const char s_itemdata_dat_0055362c[] = "itemdata.dat";
const char s_jaeyong_0055334c[] = "jaeyong";
const char s_jchlee75_005532d8[] = "jchlee75";
const char s_jewel_d_00553bd4[] = "jewel%d";
const char s_johnny5_005531f8[] = "johnny5";
const char s_knightion_00553bdc[] = "knightion";
const char s_knights_00552ecc[] = "knights";
const char s_laserion_00553be8[] = "laserion";
const char s_load_stage_02d_img_00557098[] = "load_stage%02d.img";
const char s_logging_00552cf4[] = "logging";
const char s_loserii_00553104[] = "loserii";
const char s_loudall_00553580[] = "loudall";
const char s_message_005535d0[] = "message";
const char s_mf_05d_img_0055220c[] = "mf%05d.img";
const char s_mf_05dl_img_005521dc[] = "mf%05dl.img";
const char s_modes__d__d__d_00552030[] = "modes\\%d\\%d,%d";
const char s_mouse_00551e70[] = "mouse";
const char s_mutelist_00553598[] = "mutelist";
const char s_noack_00552d1c[] = "noack";
const char s_normal_00552230[] = "normal";
const char s_oorusa_00553388[] = "oorusa";
const char s_pirania_00552fa4[] = "pirania";
const char s_ready_00551e80[] = "ready";
const char s_reddragon_00553280[] = "reddragon";
const char s_rider_00553f98[] = "rider";
const char s_scjang_005530c4[] = "scjang";
const char s_select_00551e60[] = "select";
const char s_sfire_00553b78[] = "sfire";
const char s_shrduaakstpakstpaksakstp_00552cbc[] = "shrduaakstpakstpaksakstp";
const char s_shrduarhkswjs_00552cd8[] = "shrduarhkswjs";
const char s_shrduatlwkr_00552ce8[] = "shrduatlwkr";
const char s_sound_xfs_005526fc[] = "sound.xfs";
const char s_stage_d_mp3_005569c0[] = "stage%d.mp3";
const char s_stage_dat_0055363c[] = "stage.dat";
const char s_tank_d_00553fa0[] = "tank%d";
const char s_teleport1_005535f8[] = "teleport1";
const char s_test_txt_00552c30[] = "test.txt";
const char s_tnormal_00553604[] = "tnormal";
const char s_twnormal_0055360c[] = "twnormal";
const char s_unmove_00555c98[] = "unmove";
const char s_wmove_00555ca0[] = "wmove";
const char s_wnormal_00553618[] = "wnormal";
const char s_yaong2_00553318[] = "yaong2";
const char s_yesoori_005533c8[] = "yesoori";

const char PTR_DAT_00551ecc[] = "%3d"; /* orig .data 0x551ecc, was a zeroed void * */
const char PTR_DAT_00551ed0[] = "%5d"; /* orig .data 0x551ed0, was a zeroed void * */
/* PTR_DAT_00552788: string bytes now in globals_sized.c (orig .data 0x552788, 4 bytes) */
/* PTR_DAT_005535c0: string bytes now in globals_sized.c (orig .data 0x5535c0, 4 bytes) */
void * PTR_DAT_00553c9c = (void *)0x736578; /* orig .data 0x553c9c */
void * PTR_DAT_00553ca8 = (void *)0x656d61; /* orig .data 0x553ca8 */
const char PTR_DAT_00555500[] = "p%s"; /* orig .data 0x555500, was a zeroed void * */
const char PTR_DAT_00555650[] = "%8d"; /* orig .data 0x555650, was a zeroed void * */
/* PTR_DAT_00555cc8: string bytes now in globals_sized.c (orig .data 0x555cc8, 4 bytes) */
/* PTR_DAT_00555e2c: string bytes now in globals_sized.c (orig .data 0x555e2c, 4 bytes) */
/* statically initialised to 0x5a99f4 in the original .data (0x563b40); every code ref is a load */
char *PTR_DAT_00563b40 = (char *)g_mpegScaleTab;
/* Table-pointer records at 0x568800 (36-point set) and 0x568810 (12-point set): three float table pointers each and a pad
 * word (raw 0xf25900 0xf25960 0xf259a0 0 | 0xf258c0 0xf258e0 0xf25a30 0). FUN_00519ef0 reads them through
 * FUN_0051c660 / FUN_0051c670 and fills the tables, so the pointers must be set before it runs. */
void *g_mpegImdctLongTabs[4] = { g_mpegImdctLongCos0, g_mpegImdctLongCos1, g_mpegImdctLongCos2, 0 };
void *g_mpegImdctShortTabs[4] = { g_mpegImdctShortCos0, g_mpegImdctShortCos1, &DAT_00f25a30, 0 };
/* GetLocalizedString's not-found fallback return value. Was zero-init
 * (BSS), but the original binary's own .data has this as a COMPILE-TIME
 * CONSTANT (not runtime-constructed): raw bytes at the original address
 * 0x54b460 are `20 00 00 00 ...` - the single-space C string " " (strlen
 * stops at the first NUL, byte 1) - so no static initializer is missing
 * here, just a literal init. Was NULL, so RenderWrappedText's strlen scan
 * over GetLocalizedString's returned pointer faulted on every not-found
 * lookup (always, since LoadLocalizedStrings - and hence the string table -
 * never populates in bring-up). */
void *PTR_DAT_0056d460 = " ";
/* 100 x 0x9bc (2492) item records; itemdata.dat loaded here. See FindItemRecordByIcon. */
uint8_t g_abItemRecords[2492];  /* one record; array is up to 100 x 0x9bc, see FindItemRecordByIcon */
void *PTR_FUN_00544b5c[2] = { /* orig .data 0x544b5c */
    (void *)FUN_0040a080,
    0 /* [1] 0x40a030 not ported */
};
void *PTR_FUN_00544b68[2] = { /* orig .data 0x544b68 */
    (void *)FUN_0040a080,
    0 /* [1] 0x40a030 not ported */
};
void *PTR_FUN_00544b74[2] = { /* orig .data 0x544b74 */
    (void *)FUN_0040a080,
    0 /* [1] 0x40a030 not ported */
};
/* The direct-link roster node's vtable (orig .data 0x551cb4): one slot,
 * 0x40ca00 (DeletePoisonedBaseObject); 0x551cb8 right after it is a
 * separately installed vtable (`mov [ebp+8],0x551cb8` at 0x401948).
 * UpsertDirectLinkBuddyNode (0x401d9d) and EnsureChatLogPanelForPeer
 * (0x402636) stamp it. Was a lone NULL, so slot 0 called null. */
void *PTR_FUN_00551cb4 = (void *)DeletePoisonedBaseObject;
/* One-slot vtables of the active-object registry container family (orig
 * .data, all filled 2026-11-03; each was a lone NULL `void *`). Every one
 * is the class's scalar-deleting destructor, a raw-C port of a __thiscall
 * (this first, then the delete flag):
 *   0x551cf0 -> 0x401a50  (derived; ctor 0x401910 stamps it at 0x401941)
 *   0x551e88 -> 0x405f20  (g_activeObjectRegistry; ctor 0x405f00, 0x405f13)
 *   0x5520a0 -> 0x40cd60  (g_activeObjectRegistry2; ctor 0x40cd40, 0x40cd48)
 *   0x555b7c -> 0x4f3960  (battle entity registry; 0x416865, 0x4e3837)
 *   0x557528 -> 0x4f3960  (g_spriteRegistry; ctor 0x4f1750, 0x4f1758)
 *   0x557534 -> 0x4f2ea0  (the base; ActiveObjectRegistry_BaseConstructor)
 *   0x557550 -> 0x4f3960  (DAT_00eb168c; ctor 0x4f3940, 0x4f3948)
 *   0x557530 -> 0x4f2e20  (the layer node; 0x4f2e68 and 0x4f2f23)
 * The containers are globals or embedded members, destroyed by direct
 * calls, so only the layer node's slot is dispatched (the container
 * destructors and FUN_004f3060 delete layers through it with `this`). */
void *PTR_FUN_00551cf0 = (void *)FUN_00401a50;
void *PTR_FUN_00551e88 = (void *)FUN_00405f20;
/* The text box's vtable (orig .data 0x55208c, 5 slots; InitTextBoxWidget
 * stamps it). Was a lone NULL `void *`, so every slot read past it. Its
 * objects are the only nodes of g_activeObjectRegistry2, whose dispatchers
 * call C++-style (`this` in ECX): SweepActiveObjectRegistry slot 0
 * __fastcall(this, dummy, flag), DrawActiveObjectRegistry slot 3
 * __fastcall(this), RemoveTextBoxWidget slot 0. Slots from the original:
 *   0 0x40ca00 DeletePoisonedBaseObject - via the ECX adapter
 *              TextBoxWidget_ScalarDelete
 *   1 0x461c60 ResolveNamedState - AvatarWidget_SetNamedState, the same
 *              adapter PTR_FUN_00555b38 uses for this target
 *   2 0x429800 NoOpMethod
 *   3 0x40ca20 the text box's draw, TextBoxWidget_Draw (carved 2026-10-31,
 *              __fastcall(this), the shape DrawActiveObjectRegistry
 *              dispatches)
 *   4 0x429800 NoOpMethod */
void *PTR_FUN_0055208c[5] = {
  (void *)TextBoxWidget_ScalarDelete,
  (void *)AvatarWidget_SetNamedState,
  (void *)NoOpMethod,
  (void *)TextBoxWidget_Draw,
  (void *)NoOpMethod,
};
void *PTR_FUN_005520a0 = (void *)FUN_0040cd60;   /* see 0x551cf0 above */
void *PTR_FUN_00555aa4[8] = { /* orig .data 0x555aa4 */
    (void *)DeleteShot1_Bullet7,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot_Bullet7n_9s_7p_9p,
    (void *)DetonateShot1_Bullet7,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555ac4[9] = { /* orig .data 0x555ac4 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet1,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet1_5_6_12_13_15
};
void *PTR_FUN_00555af8[8] = { /* orig .data 0x555af8 */
    (void *)Mobile00_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile00_MainAction
};
void *PTR_FUN_00555b18[8] = { /* orig .data 0x555b18 */
    (void *)DeleteSuperShot_Bullet10,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet10,
    (void *)IsProjectileInLandBounds
};
/* The State07-embedded avatar-preview widget's vtable (orig .data
 * 0x555b38, 5 slots; the constructor FUN_0044fb40 stamps it and
 * State07_AvatarStore_OnEnter dispatches slot 1 with a state name).
 * Was a lone NULL `void *`, so every slot read 0 - the AVATAR click
 * crashed calling NULL out of slot 1 (live 2026-08-06). Slots decoded
 * byte-for-byte from the original: 0x44fc90 (scalar deleting dtor),
 * 0x461c60 (ResolveNamedState - adapter below keeps the bring-up
 * bypass), 0x44fcb0 (per-frame update), 0x429800 x2 (no-ops). */
void *PTR_FUN_00555b38[5] = {
  (void *)FUN_0044fc90,
  (void *)AvatarWidget_SetNamedState,   /* 0x461c60, see functions.h */
  (void *)FUN_0044fcb0,
  (void *)NoOpMethod, (void *)NoOpMethod,
};
void *PTR_FUN_00555b54[5] = { /* orig .data 0x555b54 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)FUN_0044fd70,
    (void *)FUN_0044fff0,
    (void *)NoOpMethod
};
void *PTR_FUN_00555b68[5] = { /* orig .data 0x555b68 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)NoOpMethod,
    (void *)NoOpMethod,
    (void *)NoOpMethod
};
void *PTR_FUN_00555b7c = (void *)FUN_004f3960;   /* see 0x551cf0 above */
void *PTR_FUN_00555bd0[8] = { /* orig .data 0x555bd0 */
    (void *)FUN_00451380,
    (void *)ResolveNamedState,
    (void *)FUN_00452bf0,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)FUN_004513b0,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_00555bf0[9] = { /* orig .data 0x555bf0 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    0 /* [2] 0x453f30 not ported */,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet6,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet1_5_6_12_13_15
};
void *PTR_FUN_00555c14[8] = { /* orig .data 0x555c14 */
    (void *)Mobile05_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile05_MainAction
};
void *PTR_FUN_00555c34[8] = { /* orig .data 0x555c34 */
    (void *)DeleteProjectile,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555c54[5] = { /* orig .data 0x555c54 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x458ae0 not ported */,
    0 /* [3] 0x458b00 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00555c68[8] = { /* orig .data 0x555c68 */
    (void *)DeleteMobile,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)CGameState_NoOpVirtual_B
};
void *PTR_FUN_00555ccc[5] = { /* orig .data 0x555ccc */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x464250 not ported */,
    0 /* [3] 0x464280 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00555ce0[5] = { /* orig .data 0x555ce0 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)TickCrashParticleBurst,
    0 /* [3] 0x464390 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00555cf4[8] = { /* orig .data 0x555cf4 */
    (void *)CrystalShot_ScalarDtor,
    (void *)ResolveNamedState,
    0 /* [2] 0x465470 not ported */,
    (void *)NoOpMethod,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555d14[8] = { /* orig .data 0x555d14 */
    (void *)DeleteShot2_Bullet9,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot_Bullet7n_9s_7p_9p,
    (void *)DetonateShot2_Bullet9,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_00555d34[8] = { /* orig .data 0x555d34 */
    (void *)Mobile08_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile08_MainAction
};
void *PTR_FUN_00555d54[8] = { /* orig .data 0x555d54 */
    (void *)Mobile15_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile15_MainAction
};
void *PTR_FUN_00555d74[9] = { /* orig .data 0x555d74 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x488880 PublishProjectileTrackingStateFacing, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet16,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet16
};
void *PTR_FUN_00555d98[5] = { /* orig .data 0x555d98 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x468660 not ported */,
    0 /* [3] 0x4686b0 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00555dac[8] = { /* orig .data 0x555dac */
    (void *)DeleteShot2_Bullet1,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot2_Bullet1,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555dcc[8] = { /* orig .data 0x555dcc */
    (void *)DropBombProjectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateDropBombProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555dec[8] = { /* orig .data 0x555dec */
    (void *)DropCaseProjectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateDropCaseProjectile,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateDropCaseProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555e0c[8] = { /* orig .data 0x555e0c */
    (void *)Shot_Type13_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateShot_Type13,
    0 /* [3] 0x488880 PublishProjectileTrackingStateFacing, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot_Type13,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555e30[9] = { /* orig .data 0x555e30 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet3_5_14,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet14
};
void *PTR_FUN_00555e54[8] = { /* orig .data 0x555e54 */
    (void *)Mobile13_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)Mobile13_ComputeGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile13_MainAction
};
void *PTR_FUN_00555e74[5] = { /* orig .data 0x555e74 */
    (void *)DeleteLightningHazard,
    (void *)ResolveNamedState,
    (void *)TickWeatherHazardFrame,
    (void *)RenderLightningHazard,
    (void *)TickWeatherHazardLifetime
};
void *PTR_FUN_00555e88[8] = { /* orig .data 0x555e88 */
    (void *)DeleteShot1_Bullet9_16,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot1_Bullet9_16,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555ea8[8] = { /* orig .data 0x555ea8 */
    (void *)DeletePrimaryShot_Bullet14,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    (void *)NoOpMethod,
    (void *)NoOpMethod,
    (void *)SimulatePrimaryShot_Bullet14,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555ec8[5] = { /* orig .data 0x555ec8 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)FUN_004711f0,
    0 /* [3] 0x471240 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00555edc[5] = { /* orig .data 0x555edc */
    (void *)DeleteFirewallHazard,
    (void *)ResolveNamedState,
    (void *)TickWeatherHazardFrame,
    (void *)RenderFirewallHazard,
    (void *)TickWeatherHazardLifetime
};
void *PTR_FUN_00555ef0[5] = { /* orig .data 0x555ef0 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)TickFlameEffect,
    0 /* [3] 0x471d00 DrawFlameEffect, no prototype/cxx */,
    (void *)NoOpMethod
};
void *PTR_FUN_00555f04[5] = { /* orig .data 0x555f04 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x471dc0 not ported */,
    0 /* [3] 0x471df0 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00555f18[8] = { /* orig .data 0x555f18 */
    (void *)Mobile12_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile12_MainAction
};
void *PTR_FUN_00555f38[8] = { /* orig .data 0x555f38 */
    (void *)DeleteShot2_Bullet11,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot2_Bullet11,
    (void *)DetonateShot2_Bullet11,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555f58[9] = { /* orig .data 0x555f58 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet2_8_11,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet11
};
void *PTR_FUN_00555f7c[8] = { /* orig .data 0x555f7c */
    (void *)Mobile10_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile10_MainAction
};
void *PTR_FUN_00555f9c[8] = { /* orig .data 0x555f9c */
    (void *)DeleteItemShot,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot_Bullet8n_8s_Item,
    (void *)DetonateItemShot,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_00555fbc[8] = { /* orig .data 0x555fbc */
    (void *)ItemCase_ScalarDtor,
    (void *)ResolveNamedState,
    0 /* [2] 0x477920 not ported */,
    (void *)FUN_00477930,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00555fdc[5] = { /* orig .data 0x555fdc */
    (void *)DeleteJewel,
    (void *)ResolveNamedState,
    (void *)TickJewelFrame,
    (void *)RenderJewel,
    (void *)NoOpMethod
};
void *PTR_FUN_00556008[8] = { /* orig .data 0x556008 */
    (void *)KnightFlameShot_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateKnightFlameShot,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556038[8] = { /* orig .data 0x556038 */
    (void *)Mobile14_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile14_MainAction
};
void *PTR_FUN_00556058[8] = { /* orig .data 0x556058 */
    (void *)DeletePrimaryShot_Bullet15,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonatePrimaryShot_Bullet15,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_00556078[8] = { /* orig .data 0x556078 */
    (void *)KnightIon_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateKnightIon,
    0 /* [3] 0x47dc00 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556098[9] = { /* orig .data 0x556098 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet15,
    (void *)IsProjectileInLandBounds,
    (void *)ExplodeSuperShot_Bullet1_5_6_12_13_15
};
void *PTR_FUN_005560bc[5] = { /* orig .data 0x5560bc */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)TickFlameEffect,
    0 /* [3] 0x47ead0 DrawSuperFlameEffect, no prototype/cxx */,
    (void *)NoOpMethod
};
void *PTR_FUN_005560d0[8] = { /* orig .data 0x5560d0 */
    (void *)FUN_0047eb90,
    (void *)ResolveNamedState,
    0 /* [2] 0x47ebc0 not ported */,
    0 /* [3] 0x47f1c0 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_005560f0[8] = { /* orig .data 0x5560f0 */
    (void *)Mobile09_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile09_MainAction
};
void *PTR_FUN_00556110[8] = { /* orig .data 0x556110 */
    (void *)LaserIon_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateLaserIon,
    0 /* [3] 0x4810c0 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556160[8] = { /* orig .data 0x556160 */
    (void *)DeletePrimaryShot_Bullet10,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonatePrimaryShot_Bullet10,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_00556180[5] = { /* orig .data 0x556180 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x481e80 not ported */,
    0 /* [3] 0x481ef0 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00556194[5] = { /* orig .data 0x556194 */
    (void *)DeleteLightningStrike,
    (void *)ResolveNamedState,
    0 /* [2] 0x4a6aa0 not ported */,
    (void *)RenderLightningStrike,
    (void *)NoOpMethod
};
void *PTR_FUN_005561a8[8] = { /* orig .data 0x5561a8 */
    (void *)DeleteShot1_Bullet8,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot_Bullet8n_8s_Item,
    (void *)DetonateShot1_Bullet8,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_005561c8[9] = { /* orig .data 0x5561c8 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet2_8_11,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet8
};
void *PTR_FUN_005561ec[8] = { /* orig .data 0x5561ec */
    (void *)Mobile07_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile07_MainAction
};
void *PTR_FUN_0055620c[9] = { /* orig .data 0x55620c */
    (void *)DeleteSuperShot_Bullet13,
    (void *)ResolveNamedState,
    0 /* [2] 0x488780 not ported */,
    0 /* [3] 0x488880 PublishProjectileTrackingStateFacing, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateSuperShot_Bullet13,
    (void *)DetonateSuperShot_Bullet13,
    (void *)IsProjectileInLandBounds,
    (void *)ExplodeSuperShot_Bullet1_5_6_12_13_15
};
void *PTR_FUN_00556230[8] = { /* orig .data 0x556230 */
    (void *)Mobile01_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile01_MainAction
};
void *PTR_FUN_00556250[5] = { /* orig .data 0x556250 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)TickCrashParticleAlphaBlend_2e632,
    0 /* [3] 0x4894b0 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00556264[8] = { /* orig .data 0x556264 */
    (void *)Mobile04_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile04_MainAction
};
void *PTR_FUN_00556284[9] = { /* orig .data 0x556284 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateSuperShot_Bullet3,
    0 /* [3] 0x488880 PublishProjectileTrackingStateFacing, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateSuperShot_Bullet3,
    (void *)DetonateSuperShot_Bullet3_5_14,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet3
};
void *PTR_FUN_005562a8[8] = { /* orig .data 0x5562a8 */
    (void *)Mobile02_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile02_MainAction
};
void *PTR_FUN_005562c8[9] = { /* orig .data 0x5562c8 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet2_8_11,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet2
};
void *PTR_FUN_005562f4[5] = { /* orig .data 0x5562f4 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x48dbd0 not ported */,
    0 /* [3] 0x48dc40 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00556308[5] = { /* orig .data 0x556308 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x48dd10 not ported */,
    0 /* [3] 0x48dd80 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_0055631c[9] = { /* orig .data 0x55631c */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet3_5_14,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet1_5_6_12_13_15
};
void *PTR_FUN_00556340[8] = { /* orig .data 0x556340 */
    (void *)SuperCrystalShot_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)FUN_00490780,
    (void *)NoOpMethod,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556360[8] = { /* orig .data 0x556360 */
    (void *)DeleteSuperShot_Bullet9,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot_Bullet7n_9s_7p_9p,
    (void *)DetonateSuperShot_Bullet9,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_00556380[10] = { /* orig .data 0x556380 */
    (void *)DeleteSuperMine,
    (void *)ResolveNamedState,
    (void *)AnimateSuperMine,
    0 /* [3] 0x499d50 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperMine,
    0 /* [9] 0x492f50 not ported */
};
void *PTR_FUN_005563a8[8] = { /* orig .data 0x5563a8 */
    (void *)DeleteShot2_Bullet3,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot2_Bullet3,
    (void *)DetonateShot2_Bullet3,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_005563d0[8] = { /* orig .data 0x5563d0 */
    (void *)DeleteShot2_Bullet7,
    (void *)ResolveNamedState,
    0 /* [2] 0x497730 not ported */,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot2_Bullet7,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_005563f0[10] = { /* orig .data 0x5563f0 */
    (void *)DeleteMine,
    (void *)ResolveNamedState,
    (void *)AnimateMine,
    0 /* [3] 0x499d50 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeMine,
    0 /* [9] 0x499930 not ported */
};
void *PTR_FUN_00556424[9] = { /* orig .data 0x556424 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot_Bullet7n_9s_7p_9p,
    (void *)DetonateSuperShot_Bullet7,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    0 /* [8] 0x49c050 not ported */
};
void *PTR_FUN_00556448[8] = { /* orig .data 0x556448 */
    (void *)Mobile06_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile06_MainAction
};
void *PTR_FUN_00556468[8] = { /* orig .data 0x556468 */
    (void *)Shot_Type9_ScalarDtor,
    (void *)ResolveNamedState,
    0 /* [2] 0x49cc70 not ported */,
    0 /* [3] 0x47f1c0 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot_Type9,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556488[5] = { /* orig .data 0x556488 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)TickCrashParticleAdditive_556488,
    0 /* [3] 0x49e4c0 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_0055649c[8] = { /* orig .data 0x55649c */
    (void *)DeleteShot2_Bullet13,
    (void *)ResolveNamedState,
    (void *)AnimateShot2_Bullet13,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot2_Bullet13,
    (void *)DetonateShot2_Bullet13,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_005564bc[5] = { /* orig .data 0x5564bc */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x4a2920 TickRiderEffect, no prototype/cxx */,
    0 /* [3] 0x4a2a00 DrawRiderEffect, no prototype/cxx */,
    (void *)NoOpMethod
};
void *PTR_FUN_005564d0[8] = { /* orig .data 0x5564d0 */
    (void *)DeletePrimaryShot_Bullet4,
    (void *)ResolveNamedState,
    (void *)AnimatePrimaryShot_Bullet4,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonatePrimaryShot_Bullet4,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_005564f0[8] = { /* orig .data 0x5564f0 */
    (void *)DeleteShot2_Bullet2,
    (void *)ResolveNamedState,
    0 /* [2] 0x4a6200 not ported */,
    0 /* [3] 0x4a6840 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot2_Bullet2,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556510[5] = { /* orig .data 0x556510 */
    (void *)DeleteProjectileLightningHazard,
    (void *)ResolveNamedState,
    0 /* [2] 0x4a6aa0 not ported */,
    (void *)RenderProjectileLightningHazard,
    (void *)NoOpMethod
};
void *PTR_FUN_00556524[8] = { /* orig .data 0x556524 */
    (void *)DeleteShot2_Bullet8,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateShot_Bullet8n_8s_Item,
    (void *)DetonateShot2_Bullet8,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556544[5] = { /* orig .data 0x556544 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)TickCrashParticleAlphaBlend,
    0 /* [3] 0x4aa6c0 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_00556558[5] = { /* orig .data 0x556558 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    (void *)TickButtonAnimation,
    0 /* [3] 0x4aa760 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_0055656c[8] = { /* orig .data 0x55656c */
    (void *)BlastEffect_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateBlastEffect,
    (void *)NoOpMethod,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_0055658c[8] = { /* orig .data 0x55658c */
    (void *)FUN_004aac80,
    (void *)ResolveNamedState,
    0 /* [2] 0x4aacb0 not ported */,
    (void *)FUN_004aacd0,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateProjectile,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_005565ac[8] = { /* orig .data 0x5565ac */
    (void *)DeleteShot2_Bullet16,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x488880 PublishProjectileTrackingStateFacing, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot2_Bullet16,
    (void *)IsProjectileInLandBounds
};
void *PTR_FUN_005565cc[5] = { /* orig .data 0x5565cc */
    (void *)DeleteThor,
    (void *)ResolveNamedState,
    0 /* [2] 0x4abda0 not ported */,
    0 /* [3] 0x4abf60 not ported */,
    (void *)NoOpMethod
};
void *PTR_FUN_005565e4[5] = { /* orig .data 0x5565e4 */
    (void *)DeleteTornadoHazard,
    (void *)ResolveNamedState,
    (void *)TickTornadoHazardFrame,
    (void *)RenderTornadoHazard,
    (void *)TickTornadoHazardLifetime
};
void *PTR_FUN_005565f8[9] = { /* orig .data 0x5565f8 */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateSuperShot_Bullet4,
    0 /* [3] 0x4ae1a0 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet4,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet4
};
void *PTR_FUN_0055661c[9] = { /* orig .data 0x55661c */
    (void *)Projectile_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)AnimateProjectileTick,
    0 /* [3] 0x458690 PublishProjectileTrackingState, no prototype/cxx */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateSuperShot_Bullet12,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */,
    (void *)ExplodeSuperShot_Bullet1_5_6_12_13_15
};
void *PTR_FUN_00556640[8] = { /* orig .data 0x556640 */
    (void *)Mobile11_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile11_MainAction
};
void *PTR_FUN_00556660[8] = { /* orig .data 0x556660 */
    (void *)DeleteShot2_Bullet12,
    (void *)ResolveNamedState,
    0 /* [2] 0x4b1050 not ported */,
    0 /* [3] 0x4b30e0 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot2_Bullet12,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_00556680[8] = { /* orig .data 0x556680 */
    (void *)DeleteShot1_Bullet12,
    (void *)ResolveNamedState,
    0 /* [2] 0x4b2aa0 not ported */,
    0 /* [3] 0x4b30e0 not ported */,
    (void *)NoOpMethod,
    (void *)SimulateProjectileFrame,
    (void *)DetonateShot1_Bullet12,
    0 /* [7] 0x458850 IsProjectileInBounds, no prototype/cxx */
};
void *PTR_FUN_005566a0[8] = { /* orig .data 0x5566a0 */
    (void *)Mobile03_ScalarDtor,
    (void *)ResolveNamedState,
    (void *)SimulateMobileFrame,
    (void *)RenderMobile,
    (void *)NoOpMethod,
    (void *)ComputeMobileGroundY,
    (void *)State11_InBattle_HandleFireInput,
    (void *)Mobile03_MainAction
};
void *PTR_FUN_005566c0[24] = { /* orig .data 0x5566c0 */
    (void *)DeletePoisonedBaseObject,
    (void *)ResolveNamedState,
    0 /* [2] 0x4b3ce0 not ported */,
    0 /* [3] 0x4b3d50 not ported */,
    (void *)NoOpMethod,
    0,
    (void *)State11_InBattle_Delete,
    (void *)State11_InBattle_ProcessPacket,
    (void *)State11_InBattle_ProcessBattleAction,
    (void *)CGameState_NoOpVirtual_B,
    (void *)CGameState_NoOpVirtual_B,
    (void *)State11_InBattle_HandleKeyInput,
    (void *)State11_InBattle_HandleMouseInput,
    (void *)State11_InBattle_OnEnter,
    (void *)State11_InBattle_OnExit,
    (void *)State11_InBattle_OnTick,
    (void *)State11_InBattle_AppendChatLine,
    (void *)RenderWindGaugeTick,
    (void *)State11_InBattle_RenderWeatherHazards,
    (void *)State11_InBattle_ClearEffectTextures,
    (void *)State11_InBattle_Render,
    (void *)State11_InBattle_RenderHud,
    (void *)State11_InBattle_RenderModeIcons,
    (void *)NoOpMethod
};
/* The room-slot objects' vtable (orig .data 0x556a40, 5 slots; stamped
 * by State09_ReadyRoom_OnEnter on the 0x38-byte objects at state+0x6fc,
 * one per room slot). Was a lone NULL `void *`. These objects are only
 * dispatched by State09's own loops, which dispatch the paired avatar
 * widget at +0x700 (PTR_FUN_00555b38) in the same statements, so each
 * slot here takes the convention of the matching 0x555b38 slot:
 *   0 0x40ca00 DeletePoisonedBaseObject (cdecl this, flag - like
 *              FUN_0044fc90; State09_ReadyRoom_OnExit 0x4d7b01)
 *   1 0x461c60 ResolveNamedState - AvatarWidget_SetNamedState
 *              (__fastcall + dummy EDX)
 *   2 0x4d3750 FUN_004d3750 (__fastcall this - like FUN_0044fcb0;
 *              State09_ReadyRoom_OnTick 0x4d7d0f)
 *   3 0x429800 NoOpMethod
 *   4 0x429800 NoOpMethod */
void *PTR_FUN_00556a40[5] = {
  (void *)DeletePoisonedBaseObject,
  (void *)AvatarWidget_SetNamedState,
  (void *)FUN_004d3750,
  (void *)NoOpMethod, (void *)NoOpMethod,
};
/* The critical-section lock object's vtable (orig .data 0x5572dc): one
 * slot, 0x4e5430 (FUN_004e5430: reinstall 0x5572dc at 0x4e5437,
 * DeleteCriticalSection(this+4), free if flag & 1, `ret 4`), a raw-C port
 * of a __thiscall scalar-deleting destructor. 27 stores of 0x5572dc in the
 * image, every one next to an InitializeCriticalSection (0x54417c) or
 * DeleteCriticalSection (0x544104) call on the CRITICAL_SECTION at +4 of a
 * stack local or an embedded member, so it is never deleted through the
 * slot; filled 2026-11-03 so the table is no longer null. */
void *PTR_FUN_005572dc = (void *)FUN_004e5430;
/* Connection object's 2-entry vtable {HandleSocketEvent, NoOpMethod} -
 * decoded byte-for-byte from orig .data 0x5572e8-0x5572ef (values
 * 0x4e57c0, 0x429800). Only referenced by the connection-object family
 * (ConstructConnectionObject.c/DestroyConnectionObject.c), unlike the widely-shared
 * PTR_FUN_005572dc immediately before it, so safe to type as a real
 * function-pointer array instead of a lone null placeholder. */
void *PTR_FUN_005572e8[2] = { (void *)HandleSocketEvent, (void *)NoOpMethod };
void *PTR_FUN_005572f0[4] = { /* orig .data 0x5572f0 */
    (void *)ReplayContext_ScalarDeletingDestructor,
    (void *)UdpProbeWorkerThread,
    (void *)NoOpMethod,
    (void *)NoOpMethod
};
/* Vtable of the 0x308-byte scene-node subclass FUN_004e3810 allocates for
 * the stage registry's +0x30 member (and FUN_004e9b30 / the 0xe9b1e0 static
 * stamp). Slots read from the original .data 0x557300: 0 0x4e9b80 (scalar
 * deleting dtor), 1 0x4e9bb0 (uncarved), 2 0x429800 (NoOpMethod), 3
 * 0x4e9cc0 SceneNode_UpdateTransformAndCamera, 4 0x4f38a0
 * SceneNode_UpdateWorldViewProjection, 5 0x4f3910. Only slot 0 is wired so
 * far (FUN_004e38f0 deletes through it); was a lone NULL. 2026-11-03. */
void *PTR_FUN_00557300 = (void *)FUN_004e9b80;
void *PTR_FUN_0055745c[10] = { /* orig .data 0x55745c */
    (void *)CInputDevice_ScalarDeletingDestructor,
    (void *)KeyboardDevice_Initialize,
    (void *)CInputDevice_Release,
    0 /* [3] 0x4ede50 not ported */,
    0 /* [4] 0x4ee060 not ported */,
    0 /* [5] 0x4edd00 not ported */,
    0 /* [6] 0x4ee080 not ported */,
    0 /* [7] 0x4ee0a0 not ported */,
    (void *)CGameState_NoOpVirtual_B,
    (void *)KeyboardDevice_TickKeyTimers
};
void *PTR_FUN_00557484[10] = { /* orig .data 0x557484 */
    (void *)CInputDevice_ScalarDeletingDestructor,
    (void *)MouseDevice_Initialize,
    (void *)CInputDevice_Release,
    (void *)MouseDevice_Poll,
    (void *)CGameState_NoOpVirtual_B,
    0 /* [5] 0x4edd00 not ported */,
    0 /* [6] 0x4ee500 not ported */,
    0 /* [7] 0x4ee520 not ported */,
    (void *)CGameState_NoOpVirtual_B,
    (void *)MouseDevice_TickButtonTimers
};
/* LoadSpriteSet's per-entry sprite-object vtable slot 0 (dtor, called
 * from LoadSpriteSet.c on error via slot 0). Decoded from orig .data
 * 0x557524: FUN_004f14c0. Was a bare uninitialized global, so the dtor
 * call crashed on a null vtable. PTR_FUN_00557528/0x557530 immediately
 * after are separately-addressed vtables already used standalone
 * elsewhere (FUN_004f1750.c/ActiveObjectRegistry_BaseConstructor.c/FUN_004f2f00.c) - left
 * untouched, not part of this one. */
void *PTR_FUN_00557524 = (void *)SpriteFrame_ScalarDtor;
void *PTR_FUN_00557528 = (void *)FUN_004f3960;   /* see 0x551cf0 above */
void *PTR_FUN_00557530 = (void *)FUN_004f2e20;
void *PTR_FUN_00557534 = (void *)ActiveObjectRegistry_BaseScalarDtor;
void *PTR_FUN_00557538[6] = { /* orig .data 0x557538 */
    (void *)SceneNode_ScalarDtor,
    (void *)NoOpMethodStdcall1,
    (void *)NoOpMethod,
    (void *)SceneNode_UpdateTransform,
    (void *)SceneNode_UpdateWorldViewProjection,
    0 /* [5] 0x4f3910 not ported */
};
void *PTR_FUN_00557550 = (void *)FUN_004f3960;   /* see 0x551cf0 above */
void *PTR_FUN_005575a8 = (void *)CommP2POwner_ProcessPacket;   /* see 0x557594 */
/* PTR_FUN_00557cfc: moved to src/globals_sized.c - it is the CPanelManager
 * VTABLE (8 slots), not a lone pointer. See that file. */
void *PTR_FUN_00557f80[11] = { /* orig .data 0x557f80 */
    (void *)PanelManager_BaseScalarDtor,
    (void *)PanelManager_DispatchMouseMove,
    (void *)PanelManager_BaseDispatchMouseDown,
    (void *)PanelManager_DispatchMouseUp,
    (void *)PanelManager_DispatchRightMouseDown,
    (void *)PanelManager_DispatchRightMouseUp,
    (void *)NoOpMethod,
    (void *)PanelManager_DispatchKeyDown,
    (void *)PanelManager_DispatchKeyUp,
    (void *)PanelManager_Update,
    0 /* [10] 0x50f320 not ported */
};
/* Layer I/II synthesis drivers: 30 words, index col + (downsample + eightBit*3) * 5 with col
 * 0 mono, 1 stereo, 2 mix down, 3 first channel, 4 second channel. Raw words 5168d0 516930
 * 5169e0 516a40 516aa0 | 516b10 516b70 516c20 516c80 516ce0 | 516d50 516db0 516e60 516ec0 516f20 |
 * 516f80 516fe0 517090 5170f0 517150 | 5171c0 517220 5172d0 517330 517390 | 517400 517460
 * 517510 517570 5175d0. The runtime variable PTR_FUN_005637cc starts as slot 0. */
void *PTR_FUN_005637cc = (void *)SynthesizeMpeg16FullMono;
void *PTR_FUN_005637d0 = (void *)DecodeMpegLayerIISamples;   /* initial word, set per frame by DecodeMpegAudioFrame */
void *PTR_FUN_00563a60[30] = {
  (void *)SynthesizeMpeg16FullMono, (void *)SynthesizeMpeg16FullStereo, (void *)SynthesizeMpeg16FullMixDown,
  (void *)SynthesizeMpeg16FullFirstChannel, (void *)SynthesizeMpeg16FullSecondChannel, (void *)SynthesizeMpeg16HalfMono,
  (void *)SynthesizeMpeg16HalfStereo, (void *)SynthesizeMpeg16HalfMixDown, (void *)SynthesizeMpeg16HalfFirstChannel,
  (void *)SynthesizeMpeg16HalfSecondChannel, (void *)SynthesizeMpeg16QuarterMono, (void *)SynthesizeMpeg16QuarterStereo,
  (void *)SynthesizeMpeg16QuarterMixDown, (void *)SynthesizeMpeg16QuarterFirstChannel, (void *)SynthesizeMpeg16QuarterSecondChannel,
  (void *)SynthesizeMpeg8FullMono, (void *)SynthesizeMpeg8FullStereo, (void *)SynthesizeMpeg8FullMixDown,
  (void *)SynthesizeMpeg8FullFirstChannel, (void *)SynthesizeMpeg8FullSecondChannel, (void *)SynthesizeMpeg8HalfMono,
  (void *)SynthesizeMpeg8HalfStereo, (void *)SynthesizeMpeg8HalfMixDown, (void *)SynthesizeMpeg8HalfFirstChannel,
  (void *)SynthesizeMpeg8HalfSecondChannel, (void *)SynthesizeMpeg8QuarterMono, (void *)SynthesizeMpeg8QuarterStereo,
  (void *)SynthesizeMpeg8QuarterMixDown, (void *)SynthesizeMpeg8QuarterFirstChannel, (void *)SynthesizeMpeg8QuarterSecondChannel,
};
/* Frame decoders by header layer bits (raw words 50f8b0 514fa0 50f8b0 5133c0). Bits 00 is reserved
 * in ISO 11172-3; the original maps it to the Layer II decoder like bits 10. */
void *PTR_FUN_00563aec[4] = {
  (void *)DecodeMpegLayerIISamples, (void *)DecodeMpegLayerIIIDispatch,
  (void *)DecodeMpegLayerIISamples, (void *)DecodeMpegLayerISamples,
};
void *PTR_FUN_00563da0 = (void *)MpegPolyphase16FullInterleaved;   /* initial 0x517690 */
void *PTR_FUN_00563da4 = (void *)SynthesizeMpegLayerIIIStereo;   /* initial 0x514cc0 */
/* Word 0 is the active Layer III sample decoder (initial 0x514fc0), words 1..12 the polyphase
 * drivers, indexed outChannels(1|2) + (downsample + eightBit*3) * 2. Raw words 514fc0 517630
 * 517690 517760 5177c0 517880 5178e0 5179a0 517a00 517ac0 517b20 517be0 517c40. */
void *PTR_FUN_00563da8[13] = {
  (void *)DecodeMpegLayerIIISamples,
  (void *)MpegPolyphase16Full, (void *)MpegPolyphase16FullInterleaved,
  (void *)MpegPolyphase16Half, (void *)MpegPolyphase16HalfInterleaved,
  (void *)MpegPolyphase16Quarter, (void *)MpegPolyphase16QuarterInterleaved,
  (void *)MpegPolyphase8Full, (void *)MpegPolyphase8FullInterleaved,
  (void *)MpegPolyphase8Half, (void *)MpegPolyphase8HalfInterleaved,
  (void *)MpegPolyphase8Quarter, (void *)MpegPolyphase8QuarterInterleaved,
};
/* PTR_FUN_0056d0f0: the lazily-bound ATL code-page getter cell. Its initial value in the
 * original .data is 0x401070 = AtlGetThreadACPThunk itself (which rebinds it on the first
 * call, see that file); it was NULL here, so CString_LoadStringFromInstance's first
 * `(*PTR_FUN_0056d0f0)()` called address 0. */
void *PTR_FUN_0056d0f0 = (void *)AtlGetThreadACPThunk;
void *PTR_LAB_0054b450[2] = { /* orig .data 0x54b450 */
    (void *)NoOpMethodStdcall1,
    (void *)NoOpMethod
};
void *PTR_LAB_0054b458[2] = { /* orig .data 0x54b458 */
    (void *)NoOpMethodStdcall1,
    (void *)FUN_00401200
};
void *PTR_LAB_00550378[1] = { /* orig .data 0x550378 */
    0 /* [0] 0x520000 not ported */
};
/* The messenger's notify interface (orig .data 0x551cb8, 14 slots, read
 * from the original; was a lone NULL). The messenger object stamps it at
 * +8 (0x401948) and hands it to CreateCommP2POwner, which stores it as
 * the session handler the owner dispatches to (DispatchP2PMessage,
 * CommP2POwner_OnConnectionClosed). All slots __thiscall (erased: this
 * first). Slots 2, 4 and 13 are the original's shared `ret 4` stub
 * 0x4038b0; the port uses the cdecl no-op NoOpMethod instead because the
 * C callers are cdecl (a `ret 4` stdcall callee would unbalance them).
 *  0 403880 (always true, ret 0x14)  1 403890  2 4038b0  3 4038c0
 *  4 4038b0  5 403ae0  6 403c00  7 403d20  8 403f30  9 403e10
 * 10 403ff0 11 404140 12 404330 13 4038b0. Filled 2026-11-03. */
void *PTR_LAB_00551cb8[14] = {
  (void *)MessengerNotify_AcceptMessage, (void *)MessengerNotify_OnSessionClosed, (void *)NoOpMethod,
  (void *)FUN_004038c0, (void *)NoOpMethod, (void *)FUN_00403ae0,
  (void *)MessengerNotify_OnWhisper, (void *)MessengerNotify_OnBuddyStatus, (void *)MessengerNotify_OnStatusQuery,
  (void *)MessengerNotify_OnBuddyRequest, (void *)MessengerNotify_OnBuddyAnswer, (void *)FUN_00404140,
  (void *)MessengerNotify_OnBuddyDelete, (void *)NoOpMethod,
};
void *PTR_LAB_00551cf4[14] = { /* orig .data 0x551cf4 */
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall
};
void *PTR_LAB_005520a4[2] = { /* orig .data 0x5520a4 */
    (void *)NoOpMethodStdcall1,
    (void *)NoOpMethod
};
void *PTR_LAB_005520ac[2] = { /* orig .data 0x5520ac */
    (void *)NoOpMethodStdcall1,
    (void *)FUN_004153b0
};
/* CGameState's shared "null object" vtable (states 0/pre-init and 15/quit
 * - see ARCHITECTURE.md's CGameState vtable table). Decoded byte-for-byte
 * from orig .data 0x553fb0-0x553fdb (12 x 4-byte slots). Slot 0 (scalar-
 * deleting destructor, orig 0x43d8f0) isn't ported yet and is never
 * called on the startup/logo/server-list path - pointed at NoOpMethod as
 * a safe placeholder, not a value-guard/checksum concern. Slots 1/5/6/10
 * = CGameState_NoOpVirtual_A (0x448430); slots 2/3/4 =
 * CGameState_NoOpVirtual_B (0x4fdef0); slots 7/8/9/11 = NoOpMethod
 * (0x429800) - includes OnEnter(+0x1c)/OnExit(+0x20), matching "a
 * null-object pattern for the two states that need no real enter/exit
 * behavior" already noted in ARCHITECTURE.md. */
void *PTR_LAB_00553fb0[12] = {
  (void *)NoOpMethod,             /* slot 0: dtor (not ported; unused here) */
  (void *)CGameState_NoOpVirtual_A,
  (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_A,
  (void *)CGameState_NoOpVirtual_A,
  (void *)NoOpMethod,             /* slot 7: OnEnter */
  (void *)NoOpMethod,             /* slot 8: OnExit */
  (void *)NoOpMethod,
  (void *)CGameState_NoOpVirtual_A,
  (void *)NoOpMethod,
};
void *PTR_LAB_00553ff8[2] = { /* orig .data 0x553ff8 */
    (void *)NoOpMethodStdcall1,
    (void *)NoOpMethod
};
void *PTR_LAB_00554000[2] = { /* orig .data 0x554000 */
    (void *)NoOpMethodStdcall1,
    0 /* [1] 0x43d950 not ported */
};
void *PTR_LAB_005572e0[2] = { /* orig .data 0x5572e0 */
    (void *)NoOpMethodStdcall1,
    (void *)NoOpMethod
};
void *PTR_LAB_00557434[10] = { /* orig .data 0x557434 */
    0 /* [0] 0x4edcb0 not ported */,
    0 /* [1] 0x4edcd0 not ported */,
    (void *)NoOpMethod,
    (void *)NoOpMethod,
    (void *)CGameState_NoOpVirtual_B,
    0 /* [5] 0x4edd00 not ported */,
    0 /* [6] 0x4edcd0 not ported */,
    0 /* [7] 0x4edcd0 not ported */,
    (void *)CGameState_NoOpVirtual_B,
    (void *)NoOpMethod
};
/* Real 7-slot vtable (was a bare scalar) - the DirectSound streaming
 * object's runtime vtable, installed via `*unaff_ESI = &PTR_LAB_005574cc`
 * at the end of MusicChannel_Construct/SoundChannel_Construct (see those files' header
 * comments). Slots recovered from orig .data at 0x5574cc-0x5574e8:
 * 0=NoOpMethodStdcall1 (0x4038b0), 1=PollSoundBufferPosition ("tick",
 * currently bring-up-bypassed to a no-op - see its own header), 2 is
 * un-cross-referenced address 0x4eed10, not yet wired to a real ported
 * function since nothing on the confirmed bring-up path calls it,
 * 3=MusicChannel_Stop (0x4eef00, "stop/release channel" - called from
 * InitGame.c), 4=DecodeSoundBufferChunk (0x4eef80), 5=NoOpMethodStdcall1,
 * 6=NoOpMethod (0x429800, shared plain-ret no-op stub). */
void *PTR_LAB_005574cc[7] = {
  (void *)NoOpMethodStdcall1, (void *)PollSoundBufferPosition,
  (void *)0, (void *)MusicChannel_Stop, (void *)DecodeSoundBufferChunk,
  (void *)NoOpMethodStdcall1, (void *)NoOpMethod,
};
/* Same shape as PTR_LAB_005574cc but the SoundChannel_ConstructBase-installed
 * bring-up vtable (set briefly during construction, before
 * MusicChannel_Construct/SoundChannel_Construct swap in PTR_LAB_005574e8 then
 * PTR_LAB_005574cc) - recovered from orig .data at 0x5574e0-0x5574ec:
 * 0/2=NoOpMethodStdcall1 (0x4038b0), 1=NoOpMethod (0x429800),
 * 3=PollSoundBufferPosition (0x4ef450). */
void *PTR_LAB_005574e0[4] = {
  (void *)NoOpMethodStdcall1, (void *)NoOpMethod,
  (void *)NoOpMethodStdcall1, (void *)PollSoundBufferPosition,
};
/* The runtime vtable for SoundChannel_Construct-constructed secondary-channel
 * objects (SoundChannel_Construct itself keeps this vtable permanently, unlike
 * MusicChannel_Construct's primary-channel object which swaps to
 * PTR_LAB_005574cc at the end of construction) - recovered from orig
 * .data at 0x5574e8-0x5574f8: 0=NoOpMethodStdcall1,
 * 1=PollSoundBufferPosition (currently bring-up-bypassed to a no-op),
 * 2 is un-cross-referenced address 0x4ef4c0, not yet wired to a real
 * ported function, 3=SoundChannel_Stop (0x4ef5b0, "stop/release channel" -
 * called from InitGame.c, same role as PTR_LAB_005574cc's
 * MusicChannel_Stop but for this object's own field layout), 4 is
 * un-cross-referenced address 0x4ef610. */
void *PTR_LAB_005574e8[5] = {
  (void *)NoOpMethodStdcall1, (void *)PollSoundBufferPosition,
  (void *)0, (void *)SoundChannel_Stop, (void *)0,
};
/* The base-object vtable (orig .data 0x55752c): one slot, 0x4f2df0, the
 * scalar-deleting destructor carved as FUN_004f2df0. Destructors put it
 * back as their last step (ScrubObjectVtable, FUN_004f2e10, ...). Was a
 * lone NULL. Filled 2026-11-03. */
void *PTR_LAB_0055752c = (void *)FUN_004f2df0;
void *PTR_LAB_0055755c[4] = { /* orig .data 0x55755c */
    0 /* [0] 0x4f47b0 not ported */,
    (void *)_purecall,
    (void *)NoOpMethod,
    (void *)NoOpMethod
};
/* The CommP2P owner's +0x2f4 packet-handler sub-object: base vtable
 * 0x557594 (stamped at 0x4fd128) and derived 0x5575a8 (stamped over it at
 * 0x4fd147, again in the destructor at 0x4fd26c). One slot each in the
 * original .data: 0x525acd (_purecall, the MSVC CRT's pure-virtual trap)
 * and 0x501770 (CommP2POwner_ProcessPacket). CommP2POwner_ReassemblePackets
 * already dispatches the slot as cdecl (this, frame, len). Both were lone
 * NULLs; filled 2026-11-03. */
void *PTR_LAB_00557594 = (void *)_purecall;
void *PTR_LAB_00557598[4] = { /* orig .data 0x557598 */
    (void *)_purecall,
    (void *)CGameState_NoOpVirtual_B,
    (void *)CGameState_NoOpVirtual_B,
    (void *)CGameState_NoOpVirtual_B
};
void *PTR_LAB_005575ac[3] = { /* orig .data 0x5575ac */
    0 /* [0] 0x504800 not ported */,
    (void *)RequestP2PPeerByName,
    0 /* [2] 0x5048d0 not ported */
};
void *PTR_LAB_005575b8[4] = { /* orig .data 0x5575b8 */
    0 /* [0] 0x501750 not ported */,
    0 /* [1] 0x501640 not ported */,
    (void *)CommP2POwner_OnConnectionClosed,
    (void *)CGameState_NoOpVirtual_B
};
/* The CommP2P owner's primary vtable (orig .data 0x5575c8, 17 slots, read
 * from the original; was a lone NULL). ConstructCommP2POwner/Destroy stamp
 * it at owner+0 and the client context's +0x1bdc listener calls through
 * it. All slots are __thiscall (erased to cdecl, this first in raw C):
 *  0 AddRef 4fd3b0   1 Release 4fd3c0      2 4fd3e0 (map find)
 *  3 4fd470 Connect  4 4fd510 text sender  5 4fd680   6 4fd590
 *  7 4fd650          8 4fd730 (+0x20)      9 4fd7c0 (+0x24)
 * 10 4fd810 (+0x28) 11 4fd880  12 4fd960  13 4fda50  14 4fd9c0
 * 15 4fdb40         16 4fdba0.  Filled 2026-11-03. */
void *PTR_LAB_005575c8[17] = {
  (void *)CommP2POwner_AddRef, (void *)CommP2POwner_Release, (void *)FUN_004fd3e0,
  (void *)CommP2POwnerConnect, (void *)CommP2POwner_SendText, (void *)FUN_004fd680,
  (void *)CommP2POwner_SendBuddyStatus, (void *)CommP2POwner_SendStatusQuery, (void *)CommP2POwner_SendBuddyRequest,
  (void *)CommP2POwner_SendBuddyAnswer, (void *)CommP2POwner_SendBuddyDelete, (void *)FUN_004fd880,
  (void *)FUN_004fd960, (void *)FUN_004fda50, (void *)FUN_004fd9c0,
  (void *)FUN_004fdb40, (void *)FUN_004fdba0,
};
void *PTR_LAB_00557610[17] = { /* orig .data 0x557610 */
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall
};
void *PTR_LAB_00557654[3] = { /* orig .data 0x557654 */
    (void *)_purecall,
    (void *)_purecall,
    (void *)_purecall
};
void *PTR_LAB_00557b94;
void *PTR_LAB_00557bbc[10] = { /* orig .data 0x557bbc */
    0 /* [0] 0x50e860 Widget_SetFocus, no prototype/cxx */,
    0 /* [1] 0x50e3a0 Widget_OnDragMove, PARITY-cxx-Widget.cpp */,
    0 /* [2] 0x505430 HandlePanelMouseDown, PARITY-cxx-Panel.cpp */,
    0 /* [3] 0x50e4c0 Widget_OnMouseUp, no prototype/cxx */,
    0 /* [4] 0x50e9c0 Widget_HitTest, PARITY-cxx-Widget.cpp */,
    0 /* [5] 0x50ea50 Widget_DispatchKeyToChildren, PARITY-cxx-Widget.cpp */,
    0 /* [6] 0x50eab0 Widget_DispatchMouseToChildren, PARITY-cxx-Widget.cpp */,
    0 /* [7] 0x50eb10 Widget_OnCommandDefault, PARITY-cxx-Widget.cpp */,
    0 /* [8] 0x50e520 Widget_DrawChildren, PARITY-cxx-Widget.cpp */,
    (void *)Widget_DrawSelf
};
void *PTR_LAB_00557be4;
void *PTR_LAB_00557c34;
void *PTR_LAB_00557c84;
void *PTR_LAB_00557cac;
void *PTR_LAB_00557cd4;
void *PTR_LAB_00557da0;
void *PTR_LAB_00557df0;
void *PTR_LAB_00557e90;
void *PTR_LAB_00557eb8;
void *PTR_LAB_00557ee0;
void *PTR_LAB_00557f08;
void *PTR_LAB_00557f30;
void *PTR_LAB_00557f58[10] = { /* orig .data 0x557f58 */
    0 /* [0] 0x50e860 Widget_SetFocus, no prototype/cxx */,
    0 /* [1] 0x50e870 Widget_MouseMoveChildren, PARITY-cxx-Widget.cpp */,
    0 /* [2] 0x50e8e0 Widget_MouseDownChildren, PARITY-cxx-Widget.cpp */,
    0 /* [3] 0x50e950 Widget_MouseUpChildren, PARITY-cxx-Widget.cpp */,
    0 /* [4] 0x50e9c0 Widget_HitTest, PARITY-cxx-Widget.cpp */,
    0 /* [5] 0x50ea50 Widget_DispatchKeyToChildren, PARITY-cxx-Widget.cpp */,
    0 /* [6] 0x50eab0 Widget_DispatchMouseToChildren, PARITY-cxx-Widget.cpp */,
    0 /* [7] 0x50eb10 Widget_OnCommandDefault, PARITY-cxx-Widget.cpp */,
    0 /* [8] 0x50e520 Widget_DrawChildren, PARITY-cxx-Widget.cpp */,
    (void *)Widget_DrawChildrenDeep
};
/* Layer III channel synthesis drivers (raw words 514b60 514cc0 514de0 514b60 514c10), same
 * mono/stereo/mix down/first/second columns as PTR_FUN_00563a60. */
void *PTR_LAB_00563ddc[5] = {
  (void *)SynthesizeMpegLayerIIIFirstChannel, (void *)SynthesizeMpegLayerIIIStereo,
  (void *)SynthesizeMpegLayerIIIMixDown, (void *)SynthesizeMpegLayerIIIFirstChannel,
  (void *)SynthesizeMpegLayerIIISecondChannel,
};
void *vtable_ButtonWidget[32];
/* Full-prototype redeclarations for the vtable initializers below.
 * functions.h deliberately declares these K&R-empty (so unmigrated
 * callers keep compiling), but a K&R __fastcall reference decorates as
 * @Name@0 while the real definitions export @Name@4 - taking the
 * address through the K&R decl silently binds the vtable slot to a
 * bring-up auto-stub instead of the real function (caught 2026-07-16
 * via a stub-list diff: 17 real, already-ported methods showed up as
 * NEW stubs). A prototype composes fine with the earlier K&R decl and
 * makes the reference decorate correctly. */
void __fastcall State03_GameRoomList_OnTick(int param_1);
void __fastcall State07_AvatarStore_OnTick(int param_1);
void __fastcall RenderWindGaugeTick(int param_1);
void __fastcall State03_GameRoomList_OnEnter(int *param_1);
void __fastcall State03_GameRoomList_RenderRoomLabel(int param_1);
void __fastcall State07_AvatarStore_OnEnter(int param_1);
void __fastcall State09_ReadyRoom_OnEnter(int param_1);
void __fastcall State09_ReadyRoom_OnExit(int param_1);
void __fastcall State09_ReadyRoom_OnTick(int param_1);
void __fastcall State09_ReadyRoom_RenderCharacterPreview(int param_1);
void __fastcall State09_ReadyRoom_RenderRosterAndItems(int param_1);
void __fastcall State09_ReadyRoom_RenderStatusOverlay(int param_1);
void __fastcall State11_InBattle_OnEnter(int param_1);
void __fastcall State11_InBattle_OnExit(int param_1);
void __fastcall State11_InBattle_OnTick(int *param_1);
void __fastcall State11_InBattle_RenderHud(int param_1);
void __fastcall State11_InBattle_RenderModeIcons(int param_1);
/* Per-state CGameState vtables (see ARCHITECTURE.md's "CGameState base
 * class and virtual dispatch" table for the slot layout: 0=dtor,
 * 1=ProcessPacket, 2-4=other no-op virtuals, 5=keyboard dispatch,
 * 6=mouse dispatch, 7=OnEnter, 8=OnExit, 9=OnTick/cursor-update). These
 * were declared as zero-initialized [32] arrays but never populated
 * anywhere - every virtual call through them read a null entry. Slots
 * confirmed (real functions already in src/) are wired below; slots
 * whose target isn't ported yet, and aren't reachable on the startup/
 * logo/title/server-select path, are pointed at NoOpMethod as a
 * placeholder (matching the null-object idiom PTR_LAB_00553fb0 already
 * uses for the same purpose). All addresses decoded byte-for-byte from
 * the original binary's .data section at each state's vtable location. */
void *vtable_State01_Title[32] = {
  (void *)NoOpMethod, /* dtor: shared 0x4e5320, not yet ported */
  (void *)CGameState_NoOpVirtual_A, (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_B, (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_A,
  (void *)State01_Title_HandleKeyInput, /* slot 6 mouse/key dispatch: 0x4e5340 */
  (void *)State01_Title_OnEnter, (void *)State01_Title_OnExit,
  (void *)State01_Title_OnTick,
  /* Slots 10-17, recovered from the original's real vtable in .data at
   * 0x557278 (found by scanning .data for this state's own OnEnter/OnExit/
   * OnTick addresses - same reconstruction gap and technique as
   * vtable_State06_Logo2 below). Slot 15 is the only real one here (shared
   * with State05_Logo1 - see RenderScreenBackdrop.c); without it GameTick's
   * render call through slot 15 (+0x3c) hit a null pointer once the game
   * actually reached Title, exactly like State06 did before its own fix. */
  (void *)CGameState_NoOpVirtual_A,                        /* 10 +0x28: 0x448430 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 11-12 +0x2c/+0x30 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 13-14 +0x34/+0x38 */
  (void *)RenderScreenBackdrop,                            /* 15 +0x3c: 0x443570 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 16-17 +0x40/+0x44 */
};
void *vtable_State02_ServerSelect[32] = {
  (void *)NoOpMethod, /* dtor: shared 0x4e5320, not yet ported */
  (void *)State02_ServerSelect_ProcessPacket,
  (void *)CGameState_NoOpVirtual_B,
  (void *)State02_ServerSelect_OnTopButton, /* slot 3: 0x4e1200 - top-button click dispatcher */
  (void *)CGameState_NoOpVirtual_B,
  (void *)State02_ServerSelect_OnCommand, /* slot 5: 0x4e1170 - click/action handler (server connect) */
  (void *)State02_ServerSelect_HandleKeyInput, /* slot 6 keydown: 0x4e1430 - Enter = connect */
  (void *)State02_ServerSelect_OnEnter, (void *)State02_ServerSelect_OnExit,
  (void *)State02_ServerSelect_OnTick,
  /* Slots 10-17, recovered from the original's real vtable in .data at
   * 0x5570f0 (found by scanning for this state's own OnEnter address,
   * 0x4e14b0 - same reconstruction gap/technique as vtable_State06_Logo2/
   * State01_Title/State05_Logo1 above). Slot 15 is the shared
   * RenderScreenBackdrop again - without it GameTick's render call
   * crashed the instant the game actually reached server select. */
  (void *)CGameState_NoOpVirtual_A,                        /* 10 +0x28: 0x448430 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 11-12 +0x2c/+0x30 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 13-14 +0x34/+0x38 */
  (void *)RenderScreenBackdrop,                            /* 15 +0x3c: 0x443570 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 16-17 +0x40/+0x44 */
};
void *vtable_State05_Logo1[32] = {
  (void *)NoOpMethod, /* dtor: shared 0x4e5320, not yet ported */
  (void *)CGameState_NoOpVirtual_A, (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_B, (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_A,
  (void *)NoOpMethod, /* slot 6 mouse dispatch: 0x4433c0, not yet ported */
  (void *)State05_Logo1_OnEnter, (void *)State05_Logo1_OnExit,
  (void *)State05_Logo1_OnTick,
  /* Slots 10-17, recovered from the original's real vtable in .data at
   * 0x555590 - same reconstruction gap/technique as vtable_State06_Logo2
   * below and vtable_State01_Title above (slot 15 shared with it, see
   * RenderScreenBackdrop.c). State05 isn't reached by WinMain's bring-up
   * path (which jumps straight to state 6), but fixed for consistency. */
  (void *)CGameState_NoOpVirtual_A,                        /* 10 +0x28: 0x448430 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 11-12 +0x2c/+0x30 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 13-14 +0x34/+0x38 */
  (void *)RenderScreenBackdrop,                            /* 15 +0x3c: 0x443570 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 16-17 +0x40/+0x44 */
};
void *vtable_State06_Logo2[32] = {
  (void *)NoOpMethod, /* dtor: shared 0x4e5320, not yet ported */
  (void *)CGameState_NoOpVirtual_A, (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_B, (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_A,
  (void *)State06_Logo2_HandleKeyInput, /* slot 6 mouse/key dispatch: 0x4433c0 */
  (void *)State06_Logo2_OnEnter, (void *)State06_Logo2_OnExit,
  (void *)State06_Logo2_OnTick,
  /* Slots 10-17, recovered from the original's real vtable in .data at
   * 0x555528 (the reconstruction above only ever populated slots 0-9, so
   * GameTick's render call through slot 15 (+0x3c) hit a null pointer and
   * nothing ever drew). Slot 15 is the only real one here; the rest are the
   * two shared no-op stubs (0x448430 = CGameState_NoOpVirtual_A,
   * 0x429800 = NoOpMethod). */
  (void *)CGameState_NoOpVirtual_A,                        /* 10 +0x28: 0x448430 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 11-12 +0x2c/+0x30 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 13-14 +0x34/+0x38 */
  (void *)State06_Logo2_Render,                            /* 15 +0x3c: 0x443360 */
  (void *)NoOpMethod, (void *)NoOpMethod,                  /* 16-17 +0x40/+0x44 */
};
/* Real 18-slot vtable - dumped from orig .rdata at 0x5555f8 (the
 * address FUN_00443c20, this state's constructor, stores at *param_1;
 * same whole-table dump technique as vtable_State10_Loading below).
 * Populated 2026-07-16 session 15: Shutdown's per-state destructor loop
 * (`(**(code**)*g_gameStateVTableArray[N])(1)`) crashed at EIP=0 on the
 * first state whose vtable was still an all-NULL placeholder array.
 * Slots 4/5/6/9/13/14 target not-yet-ported functions - declared as
 * externs so the bring-up link auto-stubs them (session-12 precedent). */
void *vtable_State07_AvatarStore[32] = {
  (void *)State07_AvatarStore_Delete,                       /* 0  dtor 0x443da0 */
  (void *)State07_AvatarStore_ProcessPacket,                /* 1  0x4440c0 */
  (void *)CGameState_NoOpVirtual_B, (void *)CGameState_NoOpVirtual_B, /* 2-3 */
  (void *)FUN_004452c0,                                     /* 4  0x4452c0 (stub) */
  (void *)State07_AvatarStore_OnCommand,                    /* 5  0x445450 */
  (void *)FUN_004475c0,                                     /* 6  0x4475c0 */
  (void *)State07_AvatarStore_OnEnter,                      /* 7  0x447760 */
  (void *)State07_AvatarStore_OnExit,                       /* 8  0x448050 */
  (void *)State07_AvatarStore_OnTick,                       /* 9  0x448370 */
  (void *)CGameState_NoOpVirtual_A,                         /* 10 0x448430 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 11-12 0x429800 */
  (void *)State07_AvatarStore_RenderStoreContent,           /* 13 0x448440 */
  (void *)State07_AvatarStore_RenderAvatarPreview,          /* 14 0x449050 */
  (void *)NoOpMethod, (void *)NoOpMethod, (void *)NoOpMethod, /* 15-17 0x429800 */
};
/* Real 18-slot vtable - dumped from orig .rdata at 0x5569f8 (stored by
 * State09_ReadyRoom_Construct at *param_1). Every slot already ported. */
void *vtable_State09_ReadyRoom[32] = {
  (void *)State09_ReadyRoom_Delete,                         /* 0  0x4d37f0 */
  (void *)State09_ReadyRoom_ProcessPacket,                  /* 1  0x4d38c0 */
  (void *)State09_ReadyRoom_ProcessBattleAction,            /* 2  0x4d4ea0 */
  (void *)State09_ReadyRoom_OnActivate,                     /* 3  0x4d54c0 */
  (void *)CGameState_NoOpVirtual_B,                         /* 4  0x4fdef0 */
  (void *)State09_ReadyRoom_OnCommand,                      /* 5  0x4d54e0 */
  (void *)State09_ReadyRoom_HandleChatInput,                /* 6  0x4d6210 */
  (void *)State09_ReadyRoom_OnEnter,                        /* 7  0x4d6810 */
  (void *)State09_ReadyRoom_OnExit,                         /* 8  0x4d7630 */
  (void *)State09_ReadyRoom_OnTick,                         /* 9  0x4d7b20 */
  (void *)AppendReadyRoomStatusMessage,                     /* 10 0x4d7d70 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 11-12 0x429800 */
  (void *)State09_ReadyRoom_RenderRosterAndItems,           /* 13 0x4d7db0 */
  (void *)State09_ReadyRoom_RenderCharacterPreview,         /* 14 0x4d90c0 */
  (void *)State09_ReadyRoom_RenderStatusOverlay,            /* 15 0x4d9ae0 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 16-17 0x429800 */
};
/* Real 18-slot vtable - dumped directly from orig .rdata at 0x554018
 * (see ARCHITECTURE.md's "State10_Loading's render slot" section for
 * the slot-10/15 writeup; the rest confirmed this pass via the same
 * whole-binary vtable dump technique used for State11's table below).
 * Slots 18-31 are unused padding beyond the object's real vtable
 * (18 confirmed real entries, same as every other state's table). */
void *vtable_State10_Loading[32] = {
  (void *)CGameState_ScalarDeletingDestructor,             /* 0  0x4e5320 */
  (void *)State10_Loading_ProcessPacket,                   /* 1  0x43e280 */
  (void *)State10_Loading_ProcessBattleAction,              /* 2  0x43e440 */
  (void *)State10_Loading_OnGameEvent,                      /* 3  0x43e700 */
  (void *)CGameState_NoOpVirtual_B,                         /* 4  0x4fdef0 */
  (void *)CGameState_NoOpVirtual_A,                         /* 5  0x448430 */
  (void *)State10_Loading_HandleChatInput,                  /* 6  0x43e720 */
  (void *)State10_Loading_OnEnter,                          /* 7  0x43e840 */
  (void *)State10_Loading_OnExit,                           /* 8  0x43eff0 */
  (void *)State10_Loading_PreloadAssets,                    /* 9  0x43f0e0 */
  (void *)State10_Loading_AppendChatLine,                   /* 10 0x442240 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 11-12 0x429800 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 13-14 0x429800 */
  (void *)State10_Loading_Render,                           /* 15 0x442280 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 16-17 0x429800 */
};
/* Real 18-slot vtable - dumped from orig .rdata at 0x5566d8 (stored by
 * State11_InBattle_Construct, this state's constructor, at *param_1). Every slot
 * already ported; slot 12 is the weather-hazard render documented in
 * State11_InBattle_RenderWeatherHazards.c (that file's "unpopulated
 * bring-up placeholder" caveat is resolved by this initializer). */
void *vtable_State11_InBattle[32] = {
  (void *)State11_InBattle_Delete,                          /* 0  0x4b4060 */
  (void *)State11_InBattle_ProcessPacket,                   /* 1  0x4b4100 */
  (void *)State11_InBattle_ProcessBattleAction,             /* 2  0x4b5460 */
  (void *)CGameState_NoOpVirtual_B, (void *)CGameState_NoOpVirtual_B, /* 3-4 */
  (void *)State11_InBattle_HandleKeyInput,                  /* 5  0x4b82b0 */
  (void *)State11_InBattle_HandleMouseInput,                /* 6  0x4b97d0 */
  (void *)State11_InBattle_OnEnter,                         /* 7  0x4bb730 */
  (void *)State11_InBattle_OnExit,                          /* 8  0x4bcd00 */
  (void *)State11_InBattle_OnTick,                          /* 9  0x4bd8b0 */
  (void *)State11_InBattle_AppendChatLine,                  /* 10 0x4c1b90 */
  (void *)RenderWindGaugeTick,                              /* 11 0x4c1c90 */
  (void *)State11_InBattle_RenderWeatherHazards,            /* 12 0x4c1d10 */
  (void *)State11_InBattle_ClearEffectTextures,             /* 13 0x4c1d30 */
  (void *)State11_InBattle_Render,                          /* 14 0x4c3020 */
  (void *)State11_InBattle_RenderHud,                       /* 15 0x4c8890 */
  (void *)State11_InBattle_RenderModeIcons,                 /* 16 0x4caed0 */
  (void *)NoOpMethod,                                       /* 17 0x429800 */
};
/* Real 18-slot vtable - dumped from orig .rdata at 0x553670 (the
 * address the original InitGame stores into the state-3 object at
 * 0x40ed93). The dump proves state 3 is the GAME ROOM LIST state - the
 * slots point straight at the State03_GameRoomList_* methods - so the
 * old "NetworkSession" guess name was wrong (renamed 2026-07-16;
 * vtable_State3_NetworkSession was this same array). Slot 10 is the
 * shared chat-line appender first named in State10's table. */
void *vtable_State03_GameRoomList[32] = {
  (void *)CGameState_ScalarDeletingDestructor,              /* 0  0x4e5320 */
  (void *)State03_GameRoomList_ProcessPacket,               /* 1  0x426ad0 */
  (void *)CGameState_NoOpVirtual_B, (void *)CGameState_NoOpVirtual_B,
  (void *)CGameState_NoOpVirtual_B,                         /* 2-4 0x4fdef0 */
  (void *)State03_GameRoomList_OnCommand,                   /* 5  0x4285c0 */
  (void *)State03_GameRoomList_HandleMouseInput,            /* 6  0x428b90 */
  (void *)State03_GameRoomList_OnEnter,                     /* 7  0x428d00 */
  (void *)State03_GameRoomList_OnExit,                      /* 8  0x429480 */
  (void *)State03_GameRoomList_OnTick,                      /* 9  0x429730 */
  (void *)State10_Loading_AppendChatLine,                   /* 10 0x442240 (shared) */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 11-12 0x429800 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 13-14 0x429800 */
  (void *)State03_GameRoomList_RenderRoomLabel,             /* 15 0x429810 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 16-17 0x429800 */
};

uint32_t DAT_00000006;
uint32_t DAT_00007f00;
int g_mpegLayer3SampleRateTab[8] = { /* orig .data 0x544380..0x54439f (index (sampleRateIdx + 4 * headerID) * 4 bytes: 22050,24000,16000,pad | 44100,48000,32000,pad) */
  0x5622, 0x5dc0, 0x3e80, 1,
  0xac44, 0xbb80, 0x7d00, 1,
};
int g_mpegSfBandTab[333] = { /* orig .data 0x5443a0..0x5448d3; 9 rows of 37: [0, 22 long band ends, 0, 13 short band ends]; row = sampleRateIdx + 3 * version (0=MPEG-2, 1=MPEG-1, 2=MPEG-2.5); next object is the double 0.5 at 0x5448d8 */
  0, 6, 0xc, 0x12, 0x18, 0x1e, 0x24, 0x2c, 0x36, 0x42, 0x50, 0x60, 0x74, 0x8c, 0xa8, 0xc8, 0xee, 0x11c, 0x150, 0x18c, 0x1d0, 0x20a, 0x240, 0, 4, 8, 0xc, 0x12, 0x18, 0x20, 0x2a, 0x38, 0x4a, 0x64, 0x84, 0xae, 0xc0,
  0, 6, 0xc, 0x12, 0x18, 0x1e, 0x24, 0x2c, 0x36, 0x42, 0x50, 0x60, 0x72, 0x88, 0xa2, 0xc2, 0xe8, 0x116, 0x14c, 0x18a, 0x1d0, 0x21c, 0x240, 0, 4, 8, 0xc, 0x12, 0x1a, 0x24, 0x30, 0x3e, 0x50, 0x68, 0x88, 0xb4, 0xc0,
  0, 6, 0xc, 0x12, 0x18, 0x1e, 0x24, 0x2c, 0x36, 0x42, 0x50, 0x60, 0x74, 0x8c, 0xa8, 0xc8, 0xee, 0x11c, 0x150, 0x18c, 0x1d0, 0x20a, 0x240, 0, 4, 8, 0xc, 0x12, 0x1a, 0x24, 0x30, 0x3e, 0x50, 0x68, 0x86, 0xae, 0xc0,
  0, 4, 8, 0xc, 0x10, 0x14, 0x18, 0x1e, 0x24, 0x2c, 0x34, 0x3e, 0x4a, 0x5a, 0x6e, 0x86, 0xa2, 0xc4, 0xee, 0x120, 0x156, 0x1a2, 0x240, 0, 4, 8, 0xc, 0x10, 0x16, 0x1e, 0x28, 0x34, 0x42, 0x54, 0x6a, 0x88, 0xc0,
  0, 4, 8, 0xc, 0x10, 0x14, 0x18, 0x1e, 0x24, 0x2a, 0x32, 0x3c, 0x48, 0x58, 0x6a, 0x80, 0x9c, 0xbe, 0xe6, 0x114, 0x14a, 0x180, 0x240, 0, 4, 8, 0xc, 0x10, 0x16, 0x1c, 0x26, 0x32, 0x40, 0x50, 0x64, 0x7e, 0xc0,
  0, 4, 8, 0xc, 0x10, 0x14, 0x18, 0x1e, 0x24, 0x2c, 0x36, 0x42, 0x52, 0x66, 0x7e, 0x9c, 0xc2, 0xf0, 0x128, 0x16c, 0x1c0, 0x226, 0x240, 0, 4, 8, 0xc, 0x10, 0x16, 0x1e, 0x2a, 0x3a, 0x4e, 0x68, 0x8a, 0xb4, 0xc0,
  0, 6, 0xc, 0x12, 0x18, 0x1e, 0x24, 0x2c, 0x36, 0x42, 0x50, 0x60, 0x74, 0x8c, 0xa8, 0xc8, 0xee, 0x11c, 0x150, 0x18c, 0x1d0, 0x20a, 0x240, 0, 4, 8, 0xc, 0x12, 0x1a, 0x24, 0x30, 0x3e, 0x50, 0x68, 0x86, 0xae, 0xc0,
  0, 6, 0xc, 0x12, 0x18, 0x1e, 0x24, 0x2c, 0x36, 0x42, 0x50, 0x60, 0x74, 0x8c, 0xa8, 0xc8, 0xee, 0x11c, 0x150, 0x18c, 0x1d0, 0x20a, 0x240, 0, 4, 8, 0xc, 0x12, 0x1a, 0x24, 0x30, 0x3e, 0x50, 0x68, 0x86, 0xae, 0xc0,
  0, 0xc, 0x18, 0x24, 0x30, 0x3c, 0x48, 0x58, 0x6c, 0x84, 0xa0, 0xc0, 0xe8, 0x118, 0x150, 0x190, 0x1dc, 0x236, 0x238, 0x23a, 0x23c, 0x23e, 0x240, 0, 8, 0x10, 0x18, 0x24, 0x34, 0x48, 0x60, 0x7c, 0xa0, 0xa2, 0xa4, 0xa6, 0xc0,
};
int g_mpegSlenTab[32] = { /* orig .data 0x5448e8..0x544967; 16 (slen1, slen2) pairs indexed by scalefac_compress; next object is g_mpegLsfSfbTab */
  0, 0,
  0, 1,
  0, 2,
  0, 3,
  3, 0,
  1, 1,
  1, 2,
  1, 3,
  2, 1,
  2, 2,
  2, 3,
  3, 1,
  3, 2,
  3, 3,
  4, 2,
  4, 3,
};
int g_mpegLsfSfbTab[72] = { /* orig .data 0x544968..0x544a87; 18 rows of 4 (nr_of_sfb) = 6 types * 3 modes; ends at DAT_00544a88 */
  6, 5, 5, 5,
  3, 3, 3, 3,
  6, 3, 3, 3,
  6, 5, 7, 3,
  3, 3, 4, 2,
  6, 3, 4, 2,
  0xb, 0xa, 0, 0,
  6, 6, 0, 0,
  6, 3, 6, 0,
  7, 7, 7, 0,
  4, 4, 4, 0,
  6, 5, 4, 0,
  6, 6, 6, 3,
  4, 3, 3, 2,
  6, 4, 3, 2,
  8, 8, 5, 0,
  5, 4, 3, 0,
  6, 6, 3, 0,
};
float DAT_00544a88[8] = { -0.6f, -0.535f, -0.33f, -0.185f, -0.095f, -0.041f, -0.0142f, -0.0037f }; /* orig .data 0x544a88..0x544aa7 */
/* DAT_0054b460: string bytes now in globals_sized.c (orig .data 0x54b460, 2 bytes) */
/* 0x551b78: the SHA-1 padding bytes Sha1Final reads (80 00 00 00; orig .data).
 * DAT_00551b79 is the byte after it (offset macro in globals.h): Sha1Final
 * walks pbVar5 from DAT_00551b78 (case 1) or DAT_00551b79 (case 0) across
 * both, so they must be one contiguous object - it was two separate zero
 * dwords, which also left the 0x80 terminator byte out of every digest. */
/* The four 61-entry hash-table prime lists at 0x557660/0x557850/0x557948/0x557a40 are in
 * globals_sized.c (each was a pair of unrelated zero dwords - the table was all zero). */
uint32_t DAT_00551b78 = 0x80;
/* DAT_00551b7c (the 16-byte handshake key): storage in globals_sized.c. */
/* DAT_00551e2c: string bytes now in globals_sized.c (orig .data 0x551e2c, 2 bytes) */
/* DAT_00551e30: string bytes now in globals_sized.c (orig .data 0x551e30, 2 bytes) */
const char DAT_00551ec4[] = "%+5d"; /* orig .data 0x551ec4, was a zeroed uint32_t */
/* "%d" - the row-index sprintf format in RenderWorldListRow (the world
 * list's per-row number prefix, rendered via BlitSpriteText). Zeroed by our
 * extraction like the .epa/.xtf extension constants, so the number formatted
 * to nothing and never drew. Restored from the original .data (0x551ed4 =
 * 25 64 00 00). Safe now that DrawFontString (the row's name-shadow pass,
 * which this "1" used to fault into) is a documented no-op - see
 * DrawFontString.c. (2026-07-18) */
uint32_t g_rowIndexFormat = 0x00006425; /* "%d" little-endian */
/* DAT_00552c68: string bytes now in globals_sized.c (orig .data 0x552c68, 5 bytes) */
/* DAT_00553b90: string bytes now in globals_sized.c (orig .data 0x553b90, 5 bytes) */
uint32_t DAT_00553bb4 = 0x6d616c66; /* orig .data 0x553bb4 */
uint32_t DAT_00553bb8 = 0x33343165; /* orig .data 0x553bb8 */
uint32_t DAT_00553bbc;
uint32_t DAT_00553bf4 = 0x6d616c66; /* orig .data 0x553bf4 */
uint32_t DAT_00553bf8 = 0x323965; /* orig .data 0x553bf8 */
uint32_t DAT_00553c18 = 0x6d616c66; /* orig .data 0x553c18 */
uint32_t DAT_00553c1c = 0x323765; /* orig .data 0x553c1c */
uint32_t DAT_00553c90 = 0x6d6d6168; /* orig .data 0x553c90 */
uint32_t DAT_00553c94 = 0x6c627265; /* orig .data 0x553c94 */
uint32_t DAT_00553c98 = 0x2e747361; /* orig .data 0x553c98 */
uint32_t DAT_00553ca0 = 0x6d6d6168; /* orig .data 0x553ca0 */
uint32_t DAT_00553ca4 = 0x6c667265; /* orig .data 0x553ca4 */
const char DAT_00555654[] = "%02d"; /* orig .data 0x555654, was a zeroed uint32_t */
/* "look" - the avatar-preview widget's blink/idle state name (orig .data
 * 0x555b4c; sat immediately after the 0x555b38 vtable). Was a bare
 * 4-byte uint32_t: as a string, "look" needs 5 bytes - the NUL was
 * whatever the linker placed next. */
char DAT_00555b4c[8] = "look";
/* DAT_00556980: string bytes now in globals_sized.c (orig .data 0x556980, 5 bytes) */
uint32_t DAT_00557318 = 0x6f1d2b61; /* orig .data 0x557318 */
uint32_t DAT_0055731c = 0x11cfd5a0; /* orig .data 0x55731c */
uint32_t DAT_00557320 = 0x4544c7bf; /* orig .data 0x557320 */
uint32_t DAT_00557324 = 0x5453; /* orig .data 0x557324 */
uint32_t DAT_00557328 = 0x6f1d2b60; /* orig .data 0x557328 */
uint32_t DAT_0055732c = 0x11cfd5a0; /* orig .data 0x55732c */
uint32_t DAT_00557330 = 0x4544c7bf; /* orig .data 0x557330 */
uint32_t DAT_00557334 = 0x5453; /* orig .data 0x557334 ("ST") */
uint32_t DAT_00557fd8;
uint32_t DAT_00563730[16] = { 0x40, 0x40, 0x40, 0x40, 0x8, 0x10, 0x18, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20 };
uint32_t DAT_00563770 = 0x6; /* orig .data initial value */
uint32_t DAT_00563774[18] = { 0x0, 0x5, 0x7, 0x9, 0xa, 0xc, 0xf, 0x12, 0x15, 0x18, 0x1b, 0x1e, 0x21, 0x24, 0x27, 0x2a, 0x2d, 0x30 };
uint32_t g_mpegBandCount[4] = { 3, 8, 12, 7 }; /* orig .data 0x5637bc..0x5637cb (rewritten per frame) */
unsigned char g_mpegBandSelTab[192] = { /* orig .data 0x56382c..0x5638eb, read only */
  1, 255, 255, 255, 2, 255, 2, 0, 0, 0, 1, 1, 1, 1, 1, 255,
  0, 255, 255, 255, 2, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255,
  1, 255, 255, 255, 3, 255, 3, 0, 0, 0, 1, 1, 1, 1, 1, 255,
  1, 255, 255, 255, 2, 255, 2, 0, 0, 0, 1, 1, 1, 1, 1, 255,
  0, 255, 255, 255, 2, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255,
  1, 255, 255, 255, 3, 255, 3, 0, 0, 0, 1, 1, 1, 1, 1, 255,
  1, 255, 255, 255, 2, 255, 2, 0, 0, 0, 1, 1, 1, 1, 1, 255,
  0, 255, 255, 255, 2, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255,
  1, 255, 255, 255, 3, 255, 3, 0, 0, 0, 1, 1, 1, 1, 1, 255,
  1, 2, 2, 0, 0, 0, 1, 1, 1, 1, 1, 255, 255, 255, 255, 255,
  0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255,
  1, 3, 3, 0, 0, 0, 1, 1, 1, 1, 1, 255, 255, 255, 255, 255
};
uint32_t g_mpegSampleRateTab[8] = { 22050, 24000, 16000, 1, 44100, 48000, 32000, 1 }; /* orig .data 0x5638ec..0x56390b */
unsigned char g_mpegAllocSrcTab[320] = { /* orig .data 0x56390c..0x563a4b, read only */
  0, 1, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 17,
  0, 1, 2, 3, 4, 5, 6, 17, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 17,
  0, 1, 2, 3, 4, 5, 6, 17, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
unsigned char g_mpegBandCountTab[20] = { /* orig .data 0x563a4c..0x563a5f, read only */
  3, 8, 12, 4, 3, 8, 12, 7, 2, 0, 6, 0, 2, 0, 10, 0,
  4, 0, 7, 19
};
uint32_t DAT_00563ad8[5] = { 1, 2, 1, 1, 1 };
uint32_t DAT_00563afc = 0x1; /* orig .data initial value */
uint32_t DAT_00563b00[16] = { 0, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10 };
uint32_t DAT_00563b44 = 0x20; /* orig .data initial value */
uint32_t DAT_00563b48 = 0x1; /* orig .data initial value */
int g_mpegLayer2NbalTab[5] = { /* orig .data 0x5637d4..0x5637e7; Layer II allocation field widths per subband group (4 used, loop bound 0x10 bytes); next object is g_mpegLayer2LevelTab */
  4, 4, 3, 2, 0,
};
int g_mpegLayer2LevelTab[17] = { /* orig .data 0x5637e8..0x56382b; 17 quantiser level counts 3,5,7,9,15..65535, the fill loop in DecodeMpegAudioFrame runs 0x44 bytes and the next object is the byte table at 0x56382c */
  3, 5, 7, 9, 0xf, 0x1f, 0x3f, 0x7f, 0xff,
  0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff, 0xffff,
};
int g_mpegBitrateTabL2[32] = { /* orig .data 0x563b4c..0x563bcb; Layer II bitrates in kbps, index headerID * 16 + bitrateIdx; ends where g_mpegFrameRateTab starts */
  0, 8, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0,
  0, 0x20, 0x30, 0x38, 0x40, 0x50, 0x60, 0x70, 0x80, 0xa0, 0xc0, 0xe0, 0x100, 0x140, 0x180, 0,
};
int g_mpegFrameRateTab[8] = { /* orig .data 0x563bcc..0x563beb; sample rate / 100 (negative = reserved), index (sampleRateIdx + 4 * headerID); ends where g_mpegBitrateTabL1 starts */
  0x1b9, 0x1e0, 0x140, -999, 0x372, 0x3c0, 0x280, -999,
};
int g_mpegBitrateTabL1[32] = { /* orig .data 0x563bec..0x563c6b; Layer I bitrates in kbps, index headerID * 16 + bitrateIdx */
  0, 0x20, 0x30, 0x38, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xe0, 0x100, 0,
  0, 0x20, 0x40, 0x60, 0x80, 0xa0, 0xc0, 0xe0, 0x100, 0x120, 0x140, 0x160, 0x180, 0x1a0, 0x1c0, 0,
};
int g_mpegBitrateTabL3[32] = { /* orig .data 0x563c6c..0x563ceb; Layer III bitrates in kbps, index headerID * 16 + bitrateIdx */
  0, 8, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0,
  0, 0x20, 0x28, 0x30, 0x38, 0x40, 0x50, 0x60, 0x70, 0x80, 0xa0, 0xc0, 0xe0, 0x100, 0x140, 0,
};
int g_mpegL3RateTab[8] = { /* orig .data 0x563cec..0x563d0b; same eight sample-rate / 100 values as g_mpegFrameRateTab, read by the Layer III header paths */
  0x1b9, 0x1e0, 0x140, -999, 0x372, 0x3c0, 0x280, -999,
};
int g_mpegL3BitrateTab[32] = { /* orig .data 0x563d0c..0x563d8b; Layer III bitrates in kbps again (frame-size path), ends at DAT_00563d8c */
  0, 8, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0,
  0, 0x20, 0x28, 0x30, 0x38, 0x40, 0x50, 0x60, 0x70, 0x80, 0xa0, 0xc0, 0xe0, 0x100, 0x140, 0,
};
int g_mpegPretab[44] = { /* orig .data 0x563df4..0x563ea3; [2][22] pretab rows indexed preflag * 22 + sfb, ends where the Huffman descriptor array at 0x563ea8 begins */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 2, 0,
};
uint32_t DAT_00563d8c = 0x240; /* orig .data initial value */
uint32_t DAT_00563d90 = 0x240; /* orig .data initial value */
uint32_t DAT_00563d94 = 0x240; /* orig .data initial value */
uint32_t DAT_00563d98 = 0x20; /* orig .data initial value */
uint32_t DAT_00563df0 = 0x1; /* orig .data initial value */
/* The window table is ONE 264-float object (see globals.h); DAT_00568654/5686d4/568714 are
 * interior macros into it, so the walkers' pointer arithmetic stays inside it. */
float DAT_00568318[264] = { /* orig .data 0x568318..0x568737; the MP3 synthesis window MpegSynthWindow16Full and its 11 clones walk */
  0.0f, 0.000442504999f, -0.00325012207f, 0.00700378418f, -0.0310821515f, 0.07862854f,
  -0.100311279f, 0.572036743f, -1.14498901f, -0.572036743f, -0.100311279f, -0.07862854f,
  -0.0310821515f, -0.00700378418f, -0.00325012207f, -0.000442504999f, 1.52590001e-05f, 0.000473021995f,
  -0.00332641602f, 0.00791931245f, -0.0305175763f, 0.0841827393f, -0.090927124f, 0.600219727f,
  -1.14428711f, -0.543823242f, -0.108856201f, -0.073059082f, -0.0314788818f, -0.00611877395f,
  -0.00317382789f, -0.00039672901f, 1.52590001e-05f, 0.000534058025f, -0.00338745094f, 0.00886535645f,
  -0.0297851544f, 0.0897064209f, -0.0806884766f, 0.628295898f, -1.14221191f, -0.515609741f,
  -0.116577141f, -0.0675201416f, -0.0317382812f, -0.0052947998f, -0.00308227492f, -0.000366210996f,
  1.52590001e-05f, 0.000579833984f, -0.003433228f, 0.00984191895f, -0.0288848877f, 0.0951690674f,
  -0.0695953369f, 0.656219482f, -1.13876343f, -0.487472534f, -0.123474121f, -0.06199646f,
  -0.0318450928f, -0.00448608398f, -0.00299072289f, -0.000320435007f, 1.52590001e-05f, 0.000625610002f,
  -0.00346374488f, 0.010848999f, -0.0278015137f, 0.100540161f, -0.0576171838f, 0.683914185f,
  -1.13392639f, -0.459472656f, -0.129577637f, -0.0565338098f, -0.0318145752f, -0.003723145f,
  -0.00289916992f, -0.000289916992f, 1.52590001e-05f, 0.000686645973f, -0.00347900391f, 0.0118865967f,
  -0.0265350342f, 0.105819702f, -0.0447845459f, 0.71131897f, -1.12774658f, -0.431655884f,
  -0.134887695f, -0.0511322021f, -0.0316619873f, -0.00300598098f, -0.00279235793f, -0.000259399007f,
  1.52590001e-05f, 0.000747681013f, -0.00347900391f, 0.0129394522f, -0.0250854492f, 0.110946655f,
  -0.0310821515f, 0.738372803f, -1.120224f, -0.404083252f, -0.139450073f, -0.0458374023f,
  -0.0313873291f, -0.00233459496f, -0.00268554711f, -0.000244141003f, 3.05180001e-05f, 0.000808715995f,
  -0.00346374488f, 0.0140228262f, -0.0234222412f, 0.115921021f, -0.0165100098f, 0.765029907f,
  -1.1113739f, -0.376800537f, -0.143264771f, -0.0406341553f, -0.0310058575f, -0.00169372605f,
  -0.00257873489f, -0.000213623003f, 3.05180001e-05f, 0.000885009998f, -0.00341796898f, 0.01512146f,
  -0.0215759277f, 0.120697014f, -0.001068115f, 0.791213989f, -1.10121155f, -0.349868774f,
  -0.146362305f, -0.0355529785f, -0.0305328369f, -0.00109863305f, -0.00245666504f, -0.000198363996f,
  3.05180001e-05f, 0.000961304002f, -0.00337219192f, 0.0162353516f, -0.01953125f, 0.125259399f,
  0.0152282706f, 0.816864014f, -1.08978271f, -0.323318481f, -0.148773193f, -0.0306091309f,
  -0.0299377423f, -0.000549315999f, -0.00234985398f, -0.000167847f, 3.05180001e-05f, 0.00103759801f,
  -0.00328064011f, 0.0173492432f, -0.0172576904f, 0.129562378f, 0.0323791504f, 0.841949463f,
  -1.07711792f, -0.297210693f, -0.150497437f, -0.0258178711f, -0.0292816143f, -3.05180001e-05f,
  -0.00224304199f, -0.000152588007f, 4.57759998e-05f, 0.00111389195f, -0.00317382789f, 0.0184631348f,
  -0.0148010245f, 0.133590698f, 0.0503540039f, 0.866363525f, -1.06321716f, -0.271591187f,
  -0.151596069f, -0.0211791992f, -0.0285339355f, 0.000442504999f, -0.00212097191f, -0.000137329f,
  4.57759998e-05f, 0.00120544399f, -0.00305175805f, 0.0195770264f, -0.0121154794f, 0.137298584f,
  0.0691680908f, 0.890090942f, -1.04815674f, -0.246505737f, -0.152069092f, -0.016708374f,
  -0.0277252197f, 0.000869750977f, -0.00201415992f, -0.00012207f, 6.10349998e-05f, 0.00129699695f,
  -0.0028839109f, 0.020690918f, -0.00923156645f, 0.140670776f, 0.0887756348f, 0.91305542f,
  -1.03193665f, -0.221984863f, -0.15196228f, -0.0124206534f, -0.02684021f, 0.00126647903f,
  -0.00190734898f, -0.000106811996f, 6.10349998e-05f, 0.00138855004f, -0.0027008059f, 0.0217895508f,
  -0.0061340332f, 0.143676758f, 0.109161377f, 0.935195923f, -1.01461792f, -0.198059082f,
  -0.151306152f, -0.00831604004f, -0.0259094238f, 0.00161743199f, -0.00178527797f, -0.000106811996f,
  7.62940035e-05f, 0.001480103f, -0.00248718308f, 0.022857666f, -0.00282287598f, 0.146255493f,
  0.130310059f, 0.956481934f, -0.996246338f, -0.174789429f, -0.150115967f, -0.00439453078f,
  -0.0249328595f, 0.00193786598f, -0.00169372605f, -9.15530036e-05f, -0.00158691395f, -0.0239105206f,
  -0.148422241f, -0.976852417f, 0.152206421f, 0.000686645973f, -0.00222778297f, 7.62940035e-05f
};
float DAT_00568738;
float DAT_0056873c;
float DAT_00568740;
float DAT_00568744;
float DAT_00568748;
float DAT_0056874c;
float DAT_00568750;
float DAT_00568754;
float DAT_00568758;
float DAT_0056875c;
float DAT_00568760;
float DAT_00568764;
float DAT_00568768;
float DAT_0056876c;
float DAT_00568770;
float DAT_00568774;
float DAT_00568778;
float DAT_0056877c;
float DAT_00568798;
float DAT_0056879c;
float DAT_005687a0;
float DAT_005687a4;
float DAT_005687a8;
float DAT_005687ac;
float DAT_005687b0;
float DAT_005687b4;
float DAT_005687b8;
uint32_t DAT_005687fc;
uint32_t *DAT_0056881c;
uint32_t DAT_00568840;
uint32_t DAT_00568844;
uint32_t DAT_00568848;
uint32_t DAT_0056884c;
uint32_t DAT_00568850;
uint32_t DAT_00568854;
uint32_t DAT_00568858;
uint32_t DAT_0056885c;
uint32_t DAT_00568860;
uint32_t DAT_00568864;
uint32_t DAT_00568868;
uint32_t DAT_0056886c;
uint32_t DAT_00568870;
uint32_t DAT_00568874;
uint32_t DAT_00568878;
uint32_t DAT_0056887c;
uint32_t DAT_00568880;
uint32_t DAT_00568884;
uint32_t DAT_00568888;
uint32_t DAT_0056888c;
uint32_t DAT_00568890;
uint32_t DAT_00568894;
uint32_t DAT_00568898;
uint32_t DAT_0056889c;
uint32_t DAT_005688a0;
uint32_t DAT_005688b8;
uint32_t DAT_005688bc;
uint32_t DAT_005688c0;
uint32_t DAT_005688c4;
uint32_t DAT_005688c8;
uint32_t DAT_005688cc;
uint32_t DAT_005688d0;
uint32_t DAT_005688d4;
uint32_t DAT_005688d8;
uint32_t DAT_005688dc;
uint32_t DAT_005688e0;
uint32_t DAT_005688e4;
uint32_t DAT_005688e8;
uint32_t DAT_005688ec;
uint32_t DAT_005688f0;
uint32_t DAT_005688f4;
uint32_t DAT_005688f8;
uint32_t DAT_005688fc;
uint32_t DAT_00568900;
uint32_t DAT_00568904;
uint32_t DAT_00568908;
uint32_t DAT_0056890c;
uint32_t DAT_00568910;
uint32_t DAT_00568914;
uint32_t DAT_00568918;
uint32_t DAT_0056891c;
uint32_t DAT_00568920;
uint32_t DAT_00568924;
uint32_t DAT_00568928;
uint32_t DAT_0056892c;
uint32_t DAT_00568930;
uint32_t DAT_00568934;
uint32_t DAT_00568938;
uint32_t DAT_0056893c;
uint32_t DAT_00568940;
uint32_t DAT_00569344;
/* The four MPEG synthesis index tables walked byte-wise by MpegSynthWindow16Full and its 11 clones
 * (see include/globals.h): each is a permutation of 0..n-1 in the original image. */
uint32_t g_synthIdxTab0[512] = { /* orig .data 0x568944..0x569143: a permutation of 0..511 */
  64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
  80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
  96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
  112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
  128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
  144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
  176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
  192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
  208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
  224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
  256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271,
  272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287,
  288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303,
  304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319,
  320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335,
  336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351,
  352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367,
  368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383,
  384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399,
  400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415,
  416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431,
  432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447,
  448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463,
  464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479,
  480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495,
  496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
};
uint32_t g_synthIdxTab1[128] = { /* orig .data 0x569144..0x569343: a permutation of 0..127 */
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
  64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
  80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
  96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
  112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};
uint32_t g_synthIdxTab2[512] = { /* orig .data 0x569348..0x569b47: a permutation of 0..511 */
  64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
  80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
  96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
  112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
  128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
  144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
  176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
  192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
  208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
  224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
  256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271,
  272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287,
  288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303,
  304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319,
  320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335,
  336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351,
  352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367,
  368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383,
  384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399,
  400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415,
  416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431,
  432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447,
  448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463,
  464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479,
  480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495,
  496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
};
uint32_t g_synthIdxTab3[128] = { /* orig .data 0x569b48..0x569d47: a permutation of 0..127 */
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
  64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
  80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
  96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
  112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};
uint32_t DAT_0056d468;
uint32_t DAT_00598e7e;
/* Real values read from the binary at 0x5a9050 (see globals.h). */
const uint32_t g_fullnessGaugeThresholds[5] = { 1, 10, 30, 60, 100 };
/* DAT_005a9290, DAT_005a9350 (4x4 float matrices, 0x40) and DAT_005a94b0
 * (quaternion scratch, 0x10) moved to globals_sized.c - real extents for
 * the scene-transform cluster. */
uint32_t DAT_005a9550;
uint32_t DAT_005a960c;
uint32_t DAT_005a9624;
uint32_t DAT_005a9640;
uint32_t g_tt800Mag01[2] = { 0x00000000u, 0x8ebfd028u }; /* initialised in the image at 0x5a965c */
uint8_t *DAT_005a9680;
float g_mpegSbScaleTab[64]; /* 0x5a9684..0x5a9783: per-subband scale, runtime-filled each frame; next object is g_mpegAllocTab. DAT_005a9688 is the odd-channel view (element 1) */
uint32_t g_mpegAllocTab[64]; /* runtime-filled on every DecodeMpegAudioFrame call before any read */
uint32_t DAT_005a9884;
float g_mpegPow2Tab[64]; /* runtime-filled (orig 0x5a9888 is past the raw image, zero-fill) */
int8_t g_mpegTriple3Tab[96]; /* runtime-filled once (orig 0x5a9988 is past the raw image) */
uint32_t DAT_005a99e8;
uint32_t DAT_005a99ec;
uint32_t DAT_005a99f0;
float g_mpegScaleTab[192]; /* runtime-filled (orig 0x5a99f4, three rows of 64) */
int16_t g_mpegTriple9Tab[3072]; /* runtime-filled once (orig 0x5a9cf4 is past the raw image) */
uint32_t DAT_005ab4f4;
uint32_t DAT_005ab4fc;
uint32_t DAT_005ab500;
int g_mpegSbAllocTab[64]; /* 0x5ab604..0x5ab703: per-subband allocation, runtime-filled each frame; next object is DAT_005ab704. DAT_005ab608 is the odd-channel view (element 1) */
uint32_t DAT_005ab704;
int8_t g_mpegTriple5Tab[384]; /* runtime-filled once (orig 0x5ab708 is past the raw image) */
float g_mpegLevelRecipTab[18]; /* 0x5ab88c..0x5ab8d3: element 0 is never written (allocation 0), elements 1..17 = 2.0 / level count, filled by DecodeMpegAudioFrame; next object is DAT_005ab8d4 */
uint32_t DAT_005ab8d4;
float g_mpegReciprocalTab[16]; /* 0x5ab8dc..0x5ab91b: element 0 never written, elements 1..15 = 2.0 / (2^n - 1) filled once by SetupMpegLayerIDecoder from 0x5ab8e0; next object is g_mpegSbAllocList */
int g_mpegSbAllocList[67]; /* 0x5ab91c..0x5aba27: allocation list (two sentinels after the last subband), runtime-filled each frame; next object is DAT_005aba28. DAT_005ab920 is the odd-channel view (element 1) */
uint32_t DAT_005aba28;
uint32_t DAT_005aba2c;
uint32_t DAT_005aba30;
uint32_t DAT_005aba34;
uint8_t g_mpegBitReservoir[0x2000];
uint32_t DAT_005ada38;
uint32_t g_mpegImdctOut[0x240];
uint32_t DAT_005ae33c;
uint32_t DAT_005ae344;
uint32_t DAT_005ae348;
uint32_t DAT_005ae34c;
uint32_t DAT_005ae350;
uint8_t g_mpegGranuleInfo[0x3e0];
uint8_t g_mpegBlockState[0x70];
uint32_t g_mpegLsfIntensityTab[7];
uint32_t g_mpegBandLimit[4];
uint32_t DAT_005ae7dc;
uint32_t DAT_005ae7e0;
uint32_t DAT_005ae7e8;
uint32_t DAT_005ae7ec;
uint32_t DAT_005ae7f0;
uint32_t g_mpegSideInfoWords[2];
uint32_t g_mpegChannelInfo[72]; /* runtime state (orig 0x5ae800 is past the raw image) */
uint32_t DAT_005ae920;
uint32_t DAT_005ae924;
uint32_t DAT_005ae928;
uint32_t DAT_005ae92c;
uint32_t DAT_005ae930;
uint32_t DAT_005ae934;
uint32_t DAT_005ae938;
uint32_t DAT_005ae93c;
uint32_t g_mpegSynthFifoB[0x200];
uint32_t DAT_005af140;
uint32_t g_mpegSynthFifoA[0x200];
uint8_t g_mpegIntensityLsfTab[0x800];
uint8_t g_mpegIntensityRatioTab[0x80];
uint8_t g_mpegSubblockGainTab[0x20];
uint8_t g_mpegGlobalGainTab[0x418];
float g_mpegShortBlockScratch[576]; /* runtime scratch (orig 0x5b05fc is past the raw image) */
uint8_t g_mpegScalefactorGainTab[0x400];
uint8_t g_mpegPow43Tab[0x100];
uint32_t DAT_005b13fc;
uint32_t DAT_005c7fb8;
uint32_t DAT_005f3774;
uint32_t DAT_005f48a8;
uint32_t DAT_005f4ab4;
uint32_t DAT_005f5348;
uint32_t DAT_00656369;
uint32_t DAT_0067e5f0;
uint32_t DAT_0067e608;
uint32_t DAT_0067e814;
uint32_t DAT_0067e82c;
uint32_t DAT_0067ea38;
uint32_t DAT_0067ec5c;
uint32_t DAT_0067ec6c;
uint32_t DAT_006a4c74;
uint32_t DAT_006a4c78;
uint32_t DAT_006a7700;
uint32_t DAT_006a7fa8;
uint32_t DAT_006a81b4;
uint32_t DAT_006a9d98;
uint32_t DAT_006a9db0;
uint32_t DAT_006a9fbc;
uint32_t DAT_006a9fd4;
uint32_t DAT_006aa1e0;
uint32_t DAT_006aa1f8;
uint32_t DAT_006aa404;
uint32_t DAT_006aa630;
uint32_t DAT_006aa678;
uint32_t DAT_006aa679;
uint32_t DAT_006aa67a;
uint32_t DAT_006aa690;
uint32_t DAT_006aa89c;
uint32_t DAT_006aa8b4;
uint32_t DAT_006aaac0;
uint32_t DAT_006aaac4;
uint32_t DAT_007934c5;
uint32_t DAT_00793668;
uint32_t DAT_0079366c;
uint32_t DAT_00793670;
uint32_t DAT_0079371c;
uint32_t DAT_00793720;
uint32_t DAT_00793724;
/* DAT_007949c8: moved to globals_sized.c (0x224 CValueGuard cell). */
/* DAT_00794e48: moved to globals_sized.c (0x224 CValueGuard cell). */
uint32_t g_lastCursorDirection;
uint32_t DAT_00989680;
/* --- 0x2101 server-select selector-record table ---
 * Standalone global (not the server-list SoA, which lives in g_clientContext
 * at +0x3f808). Records are 12 bytes each; the emit path in
 * State-3 dispatch (State03_GameRoomList_OnCommand, opcode 0x2101) copies one record verbatim
 * into the send buffer, indexing g_serverSelectRecords + idx*0xc.
 * Ghidra mistyped the base as uint32_t, but the idx*0xc math is byte
 * arithmetic, so this is a byte array. The three u32 fields per record are
 * not yet named - the populator (server-list receive path) is unported.
 * Sized to the 0x100 bytes between 0xe54ca8 and the next symbol
 * (0xe54da8) = 21 whole 12-byte records max. */
uint32_t g_serverSelectRecordCount;         /* 0xe54ca4 - count/valid flag */
uint8_t  g_serverSelectRecords[21 * 12];    /* 0xe54ca8 - record[0] == old DAT_00e54ca8/cac/cb0 */
/* DAT_00e9c578: moved to globals_sized.c (0x224 CValueGuard cell). */
uint32_t g_tt800State[25]; /* runtime-seeded on first use (orig 0xf25840 is past the raw image) */
uint32_t DAT_00f258a4;
uint32_t DAT_00f258a8;
float g_mpegCosTab[31]; /* runtime-filled by InitMpegSynthesisTables (orig 0xf25a40 is past the raw image) */
float g_mpegImdctLongCos0[18]; /* runtime-filled by FUN_00519ef0 through the table records at 0x568800/0x568810 (orig 0xf25900 is past the raw image) */
float g_mpegImdctLongCos1[9]; /* runtime-filled by FUN_00519ef0 through the table records at 0x568800/0x568810 (orig 0xf25960 is past the raw image) */
float g_mpegImdctLongCos2[36]; /* runtime-filled by FUN_00519ef0 through the table records at 0x568800/0x568810 (orig 0xf259a0 is past the raw image) */
float g_mpegImdctShortCos0[6]; /* runtime-filled by FUN_00519ef0 through the table records at 0x568800/0x568810 (orig 0xf258c0 is past the raw image) */
float g_mpegImdctShortCos1[3]; /* runtime-filled by FUN_00519ef0 through the table records at 0x568800/0x568810 (orig 0xf258e0 is past the raw image) */
float g_mpegAntialiasTab[16]; /* runtime-filled by InitMpegLayerIIITables via GetMpegAntialiasCsCaTable (orig 0xf25ac0 is past the raw image); ends at g_mpegImdctWinTab */
float g_mpegImdctWinTab[144]; /* runtime-filled by InitMpegImdctWindows (orig 0xf25b00 is past the raw image); ends at g_mpegBandStartTab */
uint32_t g_mpegBandStartTab[35]; /* runtime-filled once per frame header (orig 0xf25d40 is past the raw image) */
uint32_t DAT_00f25e00;
uint32_t DAT_00f25e04;
uint8_t *DAT_00f25e08;
uint8_t *DAT_00f25e0c;
uint8_t *DAT_00f25e10;
uint32_t g_mpegBandWidthTab[35]; /* runtime-filled once per frame header (orig 0xf25e20 is past the raw image) */
uint32_t DAT_00f25ed0;
uint32_t DAT_00f25ee0;
uint32_t DAT_00f25ee4;
uint32_t g_mpegSynthBuf[2304]; /* runtime-zeroed by SetupMpegLayerIIIDecoder (orig 0xf25f00 is past the raw image) */
double DAT_00544360 = 65536.0; /* orig .data 0x40f0000000000000; only x87 QWORD operands reference it */
double DAT_00544368 = 3.0; /* orig .data 0x4008000000000000; only x87 QWORD operands reference it */
float DAT_00544370 = 2.0f; /* orig .data 0x40000000; only x87 DWORD operands reference it */
double DAT_00544378 = 2.0; /* orig .data 0x4000000000000000; only x87 QWORD operands reference it */
double DAT_005448d8 = 0.5; /* orig .data 0x3fe0000000000000; only x87 QWORD operands reference it */
double DAT_005448e0 = 4.0; /* orig .data 0x4010000000000000; only x87 QWORD operands reference it */
double DAT_00544aa8 = 1.0; /* orig .data 0x3ff0000000000000 */
double DAT_00544ab0 = -2.0; /* orig .data 0xc000000000000000; only x87 QWORD operands reference it */
double DAT_00544ab8 = -0.5; /* orig .data 0xbfe0000000000000; only x87 QWORD operands reference it */
double DAT_00544ac0 = 0.25; /* orig .data 0x3fd0000000000000; only x87 QWORD operands reference it */
double DAT_00544ac8 = 6.0; /* orig .data 0x4018000000000000; only x87 QWORD operands reference it */
double DAT_00544ad0 = 18.0; /* orig .data 0x4032000000000000; only x87 QWORD operands reference it */
double DAT_00544ad8 = 12.0; /* orig .data 0x4028000000000000; only x87 QWORD operands reference it */
double DAT_00544ae0 = 36.0; /* orig .data 0x4042000000000000; only x87 QWORD operands reference it */
double DAT_00544ae8 = 24.0; /* orig .data 0x4038000000000000; only x87 QWORD operands reference it */
double DAT_00544af0 = 72.0; /* orig .data 0x4052000000000000; only x87 QWORD operands reference it */
double DAT_00544af8 = -0.25; /* orig .data 0xbfd0000000000000; only x87 QWORD operands reference it */
float DAT_00544b00 = 0.5f; /* orig .data 0x3f000000; only x87 DWORD operands reference it */
float DAT_0054bb4c = 4e-05f; /* orig .data 0x3827c5ac; only x87 DWORD operands reference it */
float DAT_0054c870 = 1e-5f; /* orig .data 0x54c870 = 0x3727c5ac; used only via x87 fcomp/fadd */
float DAT_00557fe4 = 0.001f; /* orig .data 0x3a83126f; only x87 DWORD operands reference it */
float DAT_00558014 = 8192.0f; /* orig .data 0x46000000; only x87 DWORD operands reference it */
float DAT_00558018 = -8192.0f; /* orig .data 0xc6000000; only x87 DWORD operands reference it */
double DAT_00558048 = 90.0; /* orig .data 0x4056800000000000; only x87 QWORD operands reference it */
float DAT_00558068 = 0.248f; /* orig .data 0x3e7df3b6; only x87 DWORD operands reference it */
double DAT_00558070 = 0.06977777928113937; /* orig .data 0x3fb1dcf4e0000000; only x87 QWORD operands reference it */
double DAT_00558078 = 1000.0; /* orig .data 0x408f400000000000; only x87 QWORD operands reference it */
uint32_t DAT_00563d9c = 0x20; /* orig .data initial value */
float DAT_005687f8 = 0.5f; /* orig .data 0x3f000000; only x87 DWORD fmul operands reference it */
uint32_t DAT_005688a4;
uint32_t DAT_005688a8;
uint32_t DAT_005688ac;
uint32_t DAT_005688b0;
uint32_t DAT_005688b4;
uint32_t DAT_00588f68;
uint32_t DAT_00588f6c;
uint32_t DAT_00588f70;
uint32_t DAT_00588f74;
uint32_t DAT_005a90e0;
uint32_t DAT_005a90e4;
uint32_t DAT_005a90e8;
uint32_t DAT_005a90ec;
/* DAT_005a92a4/b8/bc/c8 are fields inside DAT_005a9290 (+0x14/+0x28/+0x2c/
 * +0x38), DAT_005a93e0..ec and DAT_005a94b4..bc fields inside the sized
 * DAT_005a93e0/DAT_005a94b0 quaternions - all offset macros in globals.h
 * over the storage in globals_sized.c now. */
uint32_t DAT_005a9554;
uint32_t DAT_005a9558;
uint32_t DAT_005a955c;
uint32_t DAT_005ab4f8;
uint32_t DAT_005ab888;
uint32_t DAT_005ab8d8;
uint32_t DAT_005ae340;
uint32_t DAT_005ae738;
uint32_t DAT_005ae7f4;
uint32_t DAT_0079361c;
float DAT_00f25a30; /* the one-element short-block table (third pointer of the 0x568810 record) */
uint32_t DAT_00f25ee8;
uint32_t DAT_00f25eec;
uint32_t DAT_00f25ef0;
uint32_t DAT_00f25ef4;
const char s_CBuddy2_Timer_Receiving_Window_00557b74[] = "CBuddy2 Timer Receiving Window";
const char s_CCommEngine_Notify_Window_00557b58[] = "CCommEngine Notify Window";
const char s___8s___12s__3dP__6dG_00556720[] = "    %-8s %-12s              %3dP    %6dG";
const char s___d__d__00555c88[] = "[%d/%d]";
const char s__d__s_00556ae8[] = "%d %s";
const char s_ani__02d_00553b98[] = "ani_%02d";
const char s_b_option_cancel_005569b0[] = "b_option_cancel";
const char s_b_option_confirm_00556988[] = "b_option_confirm";
const char s_b_option_exitgame_0055699c[] = "b_option_exitgame";
const char s_b_play_team_00554114[] = "b_play_team";
const char s_b_slot_cancel_005540d0[] = "b_slot_cancel";
const char s_b_slot_retry_005540ec[] = "b_slot_retry";
const char s_b_slot_use_005540e0[] = "b_slot_use";
const char s_b_storewindow_cancel_00555a30[] = "b_storewindow_cancel";
const char s_b_storewindow_cash_00555a48[] = "b_storewindow_cash";
const char s_b_storewindow_cashcharge_00555a70[] = "b_storewindow_cashcharge";
const char s_b_storewindow_gold_00555a5c[] = "b_storewindow_gold";
const char s_b_storewindow_yes_00555a1c[] = "b_storewindow_yes";
const char s_bombblast_xes_00553cb8[] = "bombblast.xes";
const char s_bombflame_00553cc8[] = "bombflame";

/* The button hover/push sound-name table (was undeclared g_buttonSoundNameTable).
 * AcquireSoundChannel's dropped-EDI arg (see that file's own header)
 * reads `*(char**)(g_buttonSoundNameTable + m_unk48*8)` - a flat array of 2
 * {selectSound, pushSound} string-pointer pairs, recovered from the
 * original's real .data (orig VA 0x56d0f8-0x56d10f): index 0 =
 * {"bselect1.xes","bpush1.xes"}, index 1 = {"bselect2.xes","bpush2.xes"}.
 * Every State03_GameRoomList button passes CreateButtonWidget's arg11
 * (m_unk48) as literal 0, so in practice every lobby button hover always
 * selects index 0 - "bselect1.xes". */
const char s_bselect1_xes_00551eb4[] = "bselect1.xes";
const char s_bpush1_xes_00551ea8[] = "bpush1.xes";
const char s_bselect2_xes_00551e98[] = "bselect2.xes";
const char s_bpush2_xes_00551e8c[] = "bpush2.xes";
const char *g_buttonSoundNameTable[4] = {
    s_bselect1_xes_00551eb4, s_bpush1_xes_00551ea8,
    s_bselect2_xes_00551e98, s_bpush2_xes_00551e8c,
};

const char s_bullet10n_00553ec0[] = "bullet10n";
const char s_bullet10p_00553db4[] = "bullet10p";
const char s_bullet10s_00553eb4[] = "bullet10s";
const char s_bullet11n_00553ea8[] = "bullet11n";
const char s_bullet11p_00553da8[] = "bullet11p";
const char s_bullet11s_00553e9c[] = "bullet11s";
const char s_bullet12p_00553d9c[] = "bullet12p";
const char s_bullet13n_00553e90[] = "bullet13n";
const char s_bullet13p_00553d90[] = "bullet13p";
const char s_bullet13s_00553e84[] = "bullet13s";
const char s_bullet14p_00553d84[] = "bullet14p";
const char s_bullet15n_00553e78[] = "bullet15n";
const char s_bullet15p_00553d78[] = "bullet15p";
const char s_bullet15s_00553e6c[] = "bullet15s";
const char s_bullet16n_00553e60[] = "bullet16n";
const char s_bullet16p_00553d6c[] = "bullet16p";
const char s_bullet16s_00553e54[] = "bullet16s";
const char s_bullet1n_00553f80[] = "bullet1n";
const char s_bullet1p_00553e20[] = "bullet1p";
const char s_bullet1s_00553f74[] = "bullet1s";
const char s_bullet2p_00553e14[] = "bullet2p";
const char s_bullet3n_00553f68[] = "bullet3n";
const char s_bullet3p_00553e08[] = "bullet3p";
const char s_bullet3s_00553f5c[] = "bullet3s";
const char s_bullet4n_00553f50[] = "bullet4n";
const char s_bullet4p_00553dfc[] = "bullet4p";
const char s_bullet4s_00553f44[] = "bullet4s";
const char s_bullet5n_00553f38[] = "bullet5n";
const char s_bullet5p_00553df0[] = "bullet5p";
const char s_bullet5s_00553f2c[] = "bullet5s";
const char s_bullet6n_00553f20[] = "bullet6n";
const char s_bullet6p_00553de4[] = "bullet6p";
const char s_bullet6s_00553f14[] = "bullet6s";
const char s_bullet7n_00553f08[] = "bullet7n";
const char s_bullet7p_00553dd8[] = "bullet7p";
const char s_bullet7s_00553efc[] = "bullet7s";
const char s_bullet8n_00553ef0[] = "bullet8n";
const char s_bullet8p_00553dcc[] = "bullet8p";
const char s_bullet8s_00553ee4[] = "bullet8s";
const char s_bullet9n_00553ed8[] = "bullet9n";
const char s_bullet9p_00553dc0[] = "bullet9p";
const char s_bullet9s_00553ecc[] = "bullet9s";
const char s_bulletevent1_00553e38[] = "bulletevent1";
const char s_bulletevent1p_00553d50[] = "bulletevent1p";
const char s_bulletitem_00553d14[] = "bulletitem";
const char s_caseblast_xes_00553c68[] = "caseblast.xes";
const char s_caseflame_00553c78[] = "caseflame";
const char s_change_00555af0[] = "change";
const char s_cnormal_00555ae8[] = "cnormal";
const char s_crystal_00553bfc[] = "crystal";
const char s_damage_00555cc0[] = "damage";
const char s_dropbomb_00553cd4[] = "dropbomb";
const char s_dropcase_00553c84[] = "dropcase";
const char s_drophammer_00553cac[] = "drophammer";
const char s_emotion1_00555cb4[] = "emotion1";
const char s_emotion_d_00555ca8[] = "emotion%d";
const char s_flame10_d_00553d44[] = "flame10%d";
const char s_flame123_00553cec[] = "flame123";
const char s_flame73_00553c04[] = "flame73";
const char s_flame_d3_00553d60[] = "flame%d3";
const char s_flame_d_d_00553e48[] = "flame%d%d";
const char s_flameevent1_00553e2c[] = "flameevent1";
const char s_itemblast_xes_00553cf8[] = "itemblast.xes";
const char s_itemcase_00553c38[] = "itemcase";
const char s_itemflame_00553d08[] = "itemflame";
const char s_jflame_d_00555ff0[] = "jflame%d";
const char s_knightflame_00553d20[] = "knightflame";
const char s_lightningblast_xes_00553c44[] = "lightningblast.xes";
const char s_lightningflame_00553c58[] = "lightningflame";
const char s_rayonevent1_00553c20[] = "rayonevent1";
const char s_rayonmine_00553c2c[] = "rayonmine";
const char s_shield_005562ec[] = "shield";
const char s_shock_00553b80[] = "shock";
const char s_special_005563c8[] = "special";
const char s_srayonmine_00553c0c[] = "srayonmine";
const char s_ssflame11_00554ae4[] = "ssflame11";
const char s_ssflame12_005549c8[] = "ssflame12";
const char s_ssflame13_005548d8[] = "ssflame13";
const char s_ssflame1_00555410[] = "ssflame1";
const char s_ssflame2_00555320[] = "ssflame2";
const char s_ssflame3_00555248[] = "ssflame3";
const char s_ssflame4_00555170[] = "ssflame4";
const char s_ssflame6_00554fc0[] = "ssflame6";
const char s_ssflame7_00554e94[] = "ssflame7";
const char s_ssflame8_00554dd0[] = "ssflame8";
const char s_ssflame9_00554ce4[] = "ssflame9";
const char s_teleport2_005543cc[] = "teleport2";
const char s_map_set_T_too_long_00551fec[] = "map/set<T> too long";
const char s_invalid_map_set_T_iterator_00552000[] = "invalid map/set<T> iterator";
const char s_CCommP2P_Notify_Window_00557b34[] = "CCommP2P<> Notify Window";
const char s_invalid_bitset_N_position_00552c4c[] = "invalid bitset<N> position";
const char s_vector_T_too_long_00557260[] = "vector<T> too long";

/* Code-label address markers - see globals.h. */
uint8_t LAB_00401000;
uint8_t LAB_00401060;
uint8_t LAB_005282a8;
uint8_t LAB_0052847c;
uint8_t LAB_0052e890;
uint8_t LAB_0052e8db;
uint8_t LAB_005376d4;
uint8_t LAB_005376f9;
uint8_t LAB_00537710;
uint8_t LAB_00537728;
uint8_t LAB_0053776e;
uint8_t LAB_0053778b;
uint8_t LAB_005377d0;
uint8_t LAB_005377e0;
uint8_t LAB_005377f8;
uint8_t LAB_00537868;
uint8_t LAB_00537890;
uint8_t LAB_005378ab;
uint8_t LAB_005378c8;
uint8_t LAB_005378e8;
uint8_t LAB_00537922;
uint8_t LAB_00537938;
uint8_t LAB_0053795b;
uint8_t LAB_00537970;
uint8_t LAB_00537980;
uint8_t LAB_00537a24;
uint8_t LAB_00537a38;
uint8_t LAB_00537a58;
uint8_t LAB_00537a80;
uint8_t LAB_00537a95;
uint8_t LAB_00537aa5;
uint8_t LAB_00537abd;
uint8_t LAB_00537ad0;
uint8_t LAB_00537b24;
uint8_t LAB_00537b38;
uint8_t LAB_00537b5b;
uint8_t LAB_00537b7d;
uint8_t LAB_00537b98;
uint8_t LAB_00537bd8;
uint8_t LAB_00537bfb;
uint8_t LAB_00537c4e;
uint8_t LAB_00537c73;
uint8_t LAB_00537c93;
uint8_t LAB_00537cae;
uint8_t LAB_00537ce3;
uint8_t LAB_00537d13;
uint8_t LAB_00537d41;
uint8_t LAB_00537d71;
uint8_t LAB_00537d93;
uint8_t LAB_00537e85;
uint8_t LAB_00537eb1;
uint8_t LAB_0053804d;
uint8_t LAB_0053808f;
uint8_t LAB_005380ab;
uint8_t LAB_00538146;
uint8_t LAB_005381d6;
uint8_t LAB_00538258;
uint8_t LAB_005382e8;
uint8_t LAB_00538327;
uint8_t LAB_00538367;
uint8_t LAB_0053844c;
uint8_t LAB_0053852c;
uint8_t LAB_00538e36;
uint8_t LAB_00538e6a;
uint8_t LAB_00538f8c;
uint8_t LAB_00539066;
uint8_t LAB_005390bc;
uint8_t LAB_005390e6;
uint8_t LAB_0053910c;
uint8_t LAB_005391af;
uint8_t LAB_005391f4;
uint8_t LAB_00539270;
uint8_t LAB_005392af;
uint8_t LAB_00539344;
uint8_t LAB_005396ee;
uint8_t LAB_00539797;
uint8_t LAB_005397f2;
uint8_t LAB_00539826;
uint8_t LAB_00539864;
uint8_t LAB_005399d3;
uint8_t LAB_00539a17;
uint8_t LAB_00539a68;
uint8_t LAB_00539aad;
uint8_t LAB_00539b25;
uint8_t LAB_00539bef;
uint8_t LAB_00539d55;
uint8_t LAB_00539e53;
uint8_t LAB_00539e97;
uint8_t LAB_00539f08;
uint8_t LAB_00539ffe;
uint8_t LAB_0053a146;
uint8_t LAB_0053a187;
uint8_t LAB_0053a377;
uint8_t LAB_0053a482;
uint8_t LAB_0053a990;
uint8_t LAB_0053ab3b;
uint8_t LAB_0053ab71;
uint8_t LAB_0053abda;
uint8_t LAB_0053ac2d;
uint8_t LAB_0053ac45;
uint8_t LAB_0053ad09;
uint8_t LAB_0053add9;
uint8_t LAB_0053ae1c;
uint8_t LAB_0053ae9c;
uint8_t LAB_0053aed4;
uint8_t LAB_0053aef6;
uint8_t LAB_0053af21;
uint8_t LAB_0053af72;
uint8_t LAB_0053b030;
uint8_t LAB_0053b742;
uint8_t LAB_0053be60;
uint8_t LAB_0053be8b;
uint8_t LAB_0053becc;
uint8_t LAB_0053bf43;
uint8_t LAB_0053bf92;
uint8_t LAB_0053bfd2;
uint8_t LAB_0053c022;
uint8_t LAB_0053c03a;
uint8_t LAB_0053c0d4;
uint8_t LAB_0053c0f8;
uint8_t LAB_0053c152;
uint8_t LAB_0053c205;
uint8_t LAB_0053c218;
uint8_t LAB_0053c294;
uint8_t LAB_0053c429;
uint8_t LAB_0053c46d;
uint8_t LAB_0053c98e;
uint8_t LAB_0053ca83;
uint8_t LAB_0053ca9b;
uint8_t LAB_0053cb84;
uint8_t LAB_0053cbe0;
uint8_t LAB_0053cc82;
uint8_t LAB_0053cd43;
uint8_t LAB_0053ce11;
uint8_t LAB_0053ce62;
uint8_t LAB_0053cf2a;
uint8_t LAB_0053cf6e;
uint8_t LAB_0053cfc0;
uint8_t LAB_0053d10a;
uint8_t LAB_0053d19b;
uint8_t LAB_0053d1fe;
uint8_t LAB_0053d23c;
uint8_t LAB_0053d571;
uint8_t LAB_0053d8a0;
uint8_t LAB_0053d8bb;
uint8_t LAB_0053d96a;
uint8_t LAB_0053d9ba;
uint8_t LAB_0053db1e;
uint8_t LAB_0053ddcf;
uint8_t LAB_0053defa;
uint8_t LAB_0053df47;
uint8_t LAB_0053df6b;
uint8_t LAB_0053df96;
uint8_t LAB_0053dfcc;
uint8_t LAB_0053e001;
uint8_t LAB_0053e03c;
uint8_t LAB_0053e0d4;
uint8_t LAB_0053e1c3;
uint8_t LAB_0053e2f5;
uint8_t LAB_0053e36e;
uint8_t LAB_0053e429;
uint8_t LAB_0053e523;
uint8_t LAB_0053e757;
uint8_t LAB_0053e8c0;
uint8_t LAB_0053e9f5;
uint8_t LAB_0053eb25;
uint8_t LAB_0053ecf5;
uint8_t LAB_0053ee50;
uint8_t LAB_0053ef1b;
uint8_t LAB_0053ef67;
uint8_t LAB_0053f063;
uint8_t LAB_0053f194;
uint8_t LAB_0053f429;
uint8_t LAB_0053f605;
uint8_t LAB_0053f760;
uint8_t LAB_0053f853;
uint8_t LAB_0053f984;
uint8_t LAB_0053fb1c;
uint8_t LAB_0053fc80;
uint8_t LAB_0053fd98;
uint8_t LAB_0053fe59;
uint8_t LAB_0053ffd7;
uint8_t LAB_0054008a;
uint8_t LAB_005400f8;
uint8_t LAB_005401f3;
uint8_t LAB_00540324;
uint8_t LAB_005403ca;
uint8_t LAB_005404e4;
uint8_t LAB_0054061d;
uint8_t LAB_00540762;
uint8_t LAB_00540806;
uint8_t LAB_0054095a;
uint8_t LAB_00540a36;

/* Raw absolute-address access markers - see globals.h. */
uint8_t cRam0055a4ac;
double dRam00548778;
double dRam00548788;
double dRam00548fd8;
double dRam00548fe8;
double dRam005490d8;
double dRam005490e8;
double dRam005490f8;
double dRam00549108;
double dRam00549118;
double dRam00549128;
double dRam00549138;
double dRam00549148;
double dRam00549158;
double dRam00549168;
double dRam00549178;
double dRam00549188;
int16_t sRamfffffffc;
uint32_t uRam0000020c;
uint32_t uRam00001e50;
uint32_t uRam005490a8;
uint32_t uRamfffffff8;

/* Jumptable markers - see globals.h. */
uint32_t switchD_0050fe76__switchdataD_0051008c[5] = { /* orig .text 0x51008c..0x51009f (jump table; the case labels of ReadMpegLayerIIScalefactors are these original addresses; the caller bounds the index below 5) */
  0x50fe7d, 0x50feec, 0x50ff7d, 0x50ffe8, 0x510074,
};
uint32_t switchD_0051392e__switchdataD_00514460[32] = { /* orig .text 0x514460..0x5144df (jump table; the case labels of ReadMpegLayerISubbandSamples are these original addresses; the caller loops while the index is below 0x20; code starts at 0x5144e0) */
  0x513935, 0x513941, 0x5139a7, 0x513a10, 0x513a79, 0x513ae1, 0x513b4a, 0x513bb3,
  0x513c1b, 0x513c87, 0x513cf3, 0x513d5e, 0x513dca, 0x513e36, 0x513ea1, 0x513f0d,
  0x513f21, 0x513f6c, 0x513fb9, 0x514006, 0x514053, 0x5140a0, 0x5140ed, 0x51413a,
  0x51418a, 0x5141da, 0x51422a, 0x51427a, 0x5142f3, 0x514369, 0x51444a, 0x514407,
};

/* see include/globals.h - shared scratch for unrecovered guarded-bool sites */
unsigned char g_guardScratchUnrecovered[4];
