/* Storage for the globals declared in globals.h. See that file's
 * header comment for status/caveats. */
#include "ghidra_types.h" /* winsock2.h before windows.h, WIN32_LEAN_AND_MEAN */
#include "globals.h"
#include "functions.h" /* HandleSocketEvent/NoOpMethod (PTR_FUN_005572e8 init) */

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
uint32_t DAT_0054cb00;
uint8_t DAT_0054cb78;
uint8_t DAT_0054cf78;
uint8_t DAT_0054d378;
uint8_t DAT_0054d778;
uint8_t DAT_0054db78;
uint8_t DAT_0054df78;
uint8_t DAT_0054e378;
uint8_t DAT_0054e778;
uint8_t DAT_0054eb78;
uint8_t DAT_0054ef78;
void * DAT_0054f378;
uint8_t DAT_0054f778;
uint8_t DAT_0054fb78;
uint8_t DAT_0054ff78;
uint8_t DAT_00550778;
uint8_t DAT_00550b78;
uint8_t DAT_00550f78;
uint8_t DAT_00551378;
uint8_t DAT_00551778;
/* Button-definition XFS extension ".epa" appended by AppendPersistentButtonName
 * (orig .data 0x551cac = bytes 2e 65 70 61 00). Our extraction left these
 * zero, so button-def filenames had no extension and OpenXFSEntryStream
 * failed for every button (empty named-state descriptors, invisible buttons).
 * Recovered from the original .data section (2026-07-18). */
uint32_t DAT_00551cac = 0x6170652e; /* ".epa" little-endian */
uint8_t DAT_00551cb0 = 0x00;        /* trailing NUL */
uint8_t DAT_00551cb1;
uint8_t DAT_00551e24;
uint16_t DAT_00551e34;
uint8_t DAT_00551e36;
uint8_t DAT_00551e78;
void * DAT_00551ecc;
uint8_t DAT_0055207c;
uint8_t DAT_00552084;
uint8_t DAT_00552218;
uint8_t DAT_00552728;
uint8_t DAT_0055275c;
void * DAT_00552788;
/* Registry value-name strings for the broker "IP"/"Port" settings
 * (HKCU\Software\Softnyx\GunBound) - were 1-byte placeholders (Ghidra
 * failed to recognize these two specifically as string literals, unlike
 * this same file's ~18 sibling s_*-prefixed registry value/key-name
 * strings, e.g. s_LastServer_00552884 a few lines below). With only 1
 * byte of storage, RegQueryValueExA's lpValueName read past the end into
 * whatever the linker placed next, never matching the real "IP"/"Port"
 * value names - so LoadClientSettingsFromRegistry.c's queries always
 * failed and DAT_005b2ad0/DAT_005b33e8 (the broker host/port
 * ServerSelect connects to) stayed at their zero-init default, live-
 * reproduced as BeginServerConnect always getting ip="" port=0 even with
 * the real registry values present. Recovered byte-for-byte from
 * orig/GunBound.gme's .data (file offset 0x151690-0x15169c). */
const char s_IP_00552898[] = "IP";
const char s_Port_00552890[] = "Port";
uint32_t DAT_00552c70;
uint8_t DAT_00552c74;
uint16_t DAT_00552c78;
uint8_t DAT_00552c7a;
uint16_t DAT_00552c7c;
uint16_t DAT_00552c80;
uint8_t DAT_00552d38;
uint8_t DAT_00552d60;
uint8_t DAT_00552d94;
uint8_t DAT_00552db4;
uint8_t DAT_00552de4;
uint8_t DAT_00552e14;
uint8_t DAT_00552e24;
uint8_t DAT_00552e30;
uint8_t DAT_00552e68;
uint8_t DAT_00552e90;
uint8_t DAT_00552ea4;
uint8_t DAT_00552ebc;
uint8_t DAT_00552ed4;
uint8_t DAT_00552ef0;
uint8_t DAT_00552f1c;
uint8_t DAT_00552f34;
uint8_t DAT_00552f4c;
uint8_t DAT_00552f64;
uint8_t DAT_00552f90;
uint8_t DAT_00552fac;
uint8_t DAT_00552fc8;
uint8_t DAT_00552fe4;
uint8_t DAT_00552ffc;
uint8_t DAT_00553018;
uint8_t DAT_0055303c;
uint8_t DAT_00553074;
uint8_t DAT_005530ac;
uint8_t DAT_005530cc;
uint8_t DAT_005530ec;
uint8_t DAT_0055310c;
uint8_t DAT_00553148;
uint8_t DAT_00553188;
uint8_t DAT_005531b4;
uint8_t DAT_005531e0;
uint8_t DAT_00553200;
uint8_t DAT_00553258;
uint8_t DAT_0055328c;
uint8_t DAT_005532bc;
uint8_t DAT_005532e4;
uint8_t DAT_005532fc;
uint8_t DAT_00553320;
uint8_t DAT_00553330;
uint8_t DAT_00553354;
uint8_t DAT_00553370;
uint8_t DAT_00553390;
uint8_t DAT_005533b0;
uint8_t DAT_005533d0;
uint8_t DAT_00553404;
uint8_t DAT_00553440;
uint8_t DAT_00553478;
uint8_t DAT_005534b4;
uint8_t DAT_005534cc;
uint8_t DAT_005534d4;
uint8_t DAT_00553508;
uint8_t DAT_00553554;
uint8_t DAT_00553570;
uint8_t DAT_00553588;
uint8_t DAT_005535a4;
uint8_t DAT_005535ac;
uint8_t DAT_005535b0;
uint8_t DAT_005535b8;
void * DAT_005535c0;
uint8_t DAT_005535c4;
uint8_t DAT_005535cc;
uint8_t DAT_005535d8;
uint8_t DAT_005535dc;
uint8_t DAT_005535e8;
uint16_t DAT_005535f0;
uint8_t DAT_005535f4;
uint16_t DAT_00553620;
uint16_t DAT_00553624;
uint8_t DAT_00553626;
uint32_t DAT_00553628;
uint8_t DAT_00553648;
uint32_t DAT_00553b68;
uint16_t DAT_00553b6c;
uint32_t DAT_00553b70;
uint16_t DAT_00553b74;
uint8_t DAT_00553b88;
uint8_t DAT_00553bcc;
uint8_t DAT_00553f90;
uint8_t DAT_00554060;
uint32_t DAT_005554f8;
uint8_t DAT_005554fc;
void * DAT_00555500;
uint16_t DAT_00555a14;
uint8_t DAT_00555a16;
uint16_t DAT_00555a18;
uint8_t DAT_00555a1a;
uint8_t DAT_00555c90;
uint8_t DAT_00556770;
uint32_t DAT_00556ae0;
uint16_t DAT_00556ae4;
uint8_t DAT_00557234;
uint32_t DAT_00557258;
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
 * sprite registry (DAT_00ea0e18) permanently empty (LoadSpriteSet always
 * returns 0), so nothing ever rendered - the black bring-up window. */
uint16_t DAT_0055751c = 0x4658;
uint32_t DAT_00557554;
uint8_t DAT_00557558;
uint32_t DAT_00557850;
uint32_t DAT_00557854;
uint8_t DAT_00557fb0;
uint8_t DAT_00557fb4;
uint8_t DAT_00557fb8;
uint8_t DAT_00557fbc;
uint8_t DAT_00557fc0;
uint8_t DAT_00557fc4;
uint8_t DAT_00557fc8;
uint8_t DAT_00557fcc;
uint8_t DAT_00557fd0;
uint8_t DAT_00557fd4;
uint8_t DAT_00557fec;
uint8_t DAT_00557ff0;
uint8_t DAT_00557ff4;
uint8_t DAT_00557ff8;
uint8_t DAT_00557ffc;
uint8_t DAT_00558000;
uint8_t DAT_00558004;
uint8_t DAT_00558008;
uint8_t DAT_0055800c;
uint8_t DAT_00558010;
uint8_t DAT_0055801c;
uint8_t DAT_00558020;
uint8_t DAT_00558028;
uint8_t DAT_0055802c;
uint8_t DAT_00558030;
uint8_t DAT_00558034;
uint8_t DAT_00558038;
uint8_t DAT_0055803c;
uint8_t DAT_00558040;
uint8_t DAT_00558054;
uint8_t DAT_00558064;
uint8_t DAT_005583e8;
uint8_t DAT_0055841c;
uint8_t DAT_00558458;
uint8_t DAT_00569e10;
uint8_t DAT_00569e2c;
uint8_t DAT_00569e48;
uint8_t DAT_00569e68;
uint32_t DAT_0056d108;
uint32_t g_cursorAnchorX;
uint32_t g_cursorAnchorY;
uint32_t DAT_0056d118;
const uint32_t DAT_0056d11c[11] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 1024};
uint8_t DAT_0056d350;
uint32_t DAT_0056d3d8;
uint32_t DAT_0056d3dc;
uint8_t DAT_0056d3e0;
uint8_t DAT_0056d400;
uint8_t DAT_0056d440;
void * DAT_0056d460;
uint32_t DAT_0056dbe8;
uint8_t DAT_0056dbf0;
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
uint8_t DAT_0056dc90;
uint8_t DAT_0056dc95;
uint8_t DAT_0056dc97;
uint8_t DAT_0056dc98;
uint8_t DAT_0056dc9a;
uint8_t DAT_0056dca0;
uint8_t DAT_0056dca5;
uint8_t DAT_0056dca7;
uint8_t DAT_0056dca8;
uint8_t DAT_0056dcaa;
uint8_t DAT_0056dd30;
uint8_t DAT_0056de30;
uint32_t DAT_0056df30;
uint32_t DAT_0056df34;
uint16_t DAT_00588f38;
uint32_t DAT_00588f3c;
uint16_t DAT_00588f40;
uint32_t DAT_00588f44;
/* Display-mode config, statically initialised in the original's .data
 * (0x588f48). InitDirectDraw's fullscreen path feeds these to SetDisplayMode
 * (800x600x16) and SetupZBuffer relies on the resulting 16-bit back buffer
 * to pick a matching Z-buffer format. The port had left them zero-init'd
 * (SetDisplayMode(0,0,0) -> 32-bit desktop mode -> no Z-format match ->
 * SetupZBuffer crash), and had DAT_00588f50/54 as uint8_t although they hold
 * floats (800.0/600.0) that the coordinate transforms in FUN_004eda*0 also
 * read. Values decoded from orig .data 0x588f48-0x588f60. */
uint32_t DAT_00588f48 = 60;    /* refresh rate (WinMain may overwrite) */
uint8_t DAT_00588f4c;
float DAT_00588f50 = 800.0f;   /* screen width  */
float DAT_00588f54 = 600.0f;   /* screen height */
uint32_t DAT_00588f60 = 16;    /* bit depth */
uint8_t DAT_00588f64;
void * DAT_0058b248;
uint8_t DAT_0058b8d6;
uint8_t DAT_0058bb04;
/* DAT_005a9068, DAT_005a9084: moved to globals_sized.c - both are
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
 * crt_shims_msvc.c's gb_init_atl_string_mgr, wired into gb_startup_init. */
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
 * DAT_005b2ad0's comment below for the live-reproduced sibling bug this
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
 * DAT_005b1ed0 sitting at exactly +0x160. DAT_005b1da2 (the old split-out
 * symbol for this buffer's own +0x32 offset, used by GameTick's RLE blit
 * loop) is folded into this array - see GameTick.c. */
uint8_t DAT_005b1d70[0x160];
/* DAT_005b1ed0 (Location)/DAT_005b2f68 (Screen, copy-fallback target for
 * the same value - see the copy loop right after both RegQueryValueExA
 * calls in LoadClientSettingsFromRegistry.c): both told 0x400 (1024)
 * bytes of real capacity (`local_14 = 0x400;`, unchanged across both
 * calls), matching the real gap to each one's next symbol exactly
 * (0x22d0-0x1ed0=0x400, 0x3368-0x2f68=0x400). Were 1-byte placeholders -
 * see DAT_005b2ad0's comment below for the live-reproduced sibling bug. */
uint8_t DAT_005b1ed0[0x400];
uint8_t DAT_005b22d0;
/* DAT_005b26d0 (GameBuddy Executable path): told 0x400 bytes
 * (`local_14 = 0x400;`), matching the real gap to the next symbol
 * (0x2ad0-0x26d0=0x400). Was a 1-byte placeholder. */
uint8_t DAT_005b26d0[0x400];
/* DAT_005b2ad0 (the broker "IP" registry value, the actual host
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
uint8_t DAT_005b2ad0[0x80];
/* DAT_005b2b50 (GameBuddy's own port, read via PTR_DAT_00552788): told
 * 4 bytes (`local_14 = 4;`, a DWORD), matching the real gap to the next
 * symbol (0x2b54-0x2b50=4). Was a 1-byte placeholder - same overflow
 * class as DAT_005b2ad0 above. */
uint32_t DAT_005b2b50;
uint32_t DAT_005b2b54;
uint32_t DAT_005b2b58;
uint32_t DAT_005b2b5c;
uint32_t DAT_005b2b60;
uint32_t DAT_005b2b64;
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
uint8_t DAT_005b2f68[0x400];
/* DAT_005b3368 (GameName): told 0x80 bytes (`local_14 = 0x80;`),
 * matching the real gap to the next symbol (0x33e8-0x3368=0x80). Was a
 * 1-byte placeholder. */
uint8_t DAT_005b3368[0x80];
/* DAT_005b33e8 (the broker "Port" registry value, paired with
 * DAT_005b2ad0 above): RegQueryValueExA reads it with `local_14 = 4;`
 * (a DWORD) but it was declared uint16_t (2 bytes) - a second, smaller
 * overflow in the exact same live-reproduced hang (see DAT_005b2ad0's
 * comment). Widened to match the real DWORD size. */
uint32_t DAT_005b33e8;
uint32_t DAT_005b33f0;
uint16_t DAT_005b33f4;
uint32_t DAT_005b3438;
uint16_t DAT_005b343c;
uint8_t DAT_005b3440;
uint32_t DAT_005b3480;
uint32_t g_clientContext;
uint32_t DAT_005b3488;
uint32_t DAT_005b3620;
/* g_fullWidthFontGlyphs (was DAT_005b3628, the full-width/CJK bitmap-font
 * glyph table) is sized to 0xc0000 in globals_sized.c - see the comment there. */
uint8_t DAT_005f2f38;
uint8_t DAT_005f2f40;
uint8_t DAT_005f2f58;
uint8_t DAT_005f3158;
uint8_t DAT_005f325c;
uint8_t DAT_005f32dc;
uint8_t DAT_005f375c;
uint8_t DAT_005f3760;
uint8_t DAT_005f376c;
uint8_t DAT_005f3770;
uint8_t DAT_005f3771;
uint8_t DAT_005f3772;
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
 * back by FUN_004f0230. Were lone uint32_t, so the 8-dword copy overflowed
 * 28 bytes into adjacent globals. */
uint32_t DAT_00677544[8];
uint32_t DAT_006777e8[8];
/* 0x8000-entry sqrt lookup table (32768 * 4 = 0x20000 bytes), filled by
 * FUN_004f1eb0 and read by FUN_004ed300. Was a lone uint32_t; its sibling
 * table DAT_006990c0 sits exactly 0x20000 bytes higher in the original
 * image, confirming the real size. Undersized, the fill loop wrote past
 * the end of the whole executable image and faulted. */
uint32_t DAT_006790c0[0x8000];
uint8_t DAT_0067e348;
uint8_t DAT_0067e3cd;
uint8_t DAT_0067e3ce;
uint8_t DAT_0067ec60;
uint8_t DAT_0067ec64;
uint8_t DAT_0067ec68;
/* DAT_0067ec70 is not a real global - it is arena offset 0x67ec70, now a
 * fixed-address offset-macro in globals.h (see the comment there). */
/* 0x8000-entry sqrt lookup table, sibling of DAT_006790c0 above - see its
 * comment. */
uint32_t DAT_006990c0[0x8000];
uint8_t DAT_0069ec74;
uint8_t DAT_006a6481;
uint8_t DAT_006a64a4;
uint8_t DAT_006a64a8;
uint8_t DAT_006a64ac;
uint8_t DAT_006a64bc;
uint8_t DAT_006a64c0;
uint8_t DAT_006a76fc;
int32_t g_nCameraScrollX;
int32_t g_nCameraScrollY;
uint8_t DAT_006a7758;
uint8_t DAT_006a7f91;
uint8_t DAT_006a7f92;
uint8_t DAT_006a9b6d;
uint8_t DAT_006a9b6e;
uint8_t DAT_006a9b70;
uint8_t DAT_006a9b71;
uint8_t DAT_006a9b73;
uint8_t DAT_006a9b74;
uint8_t DAT_006aa424;
uint8_t DAT_006aa44c;
uint8_t DAT_006aa47b;
uint8_t DAT_006aa47c;
uint8_t DAT_006aa5fc;
uint8_t DAT_006aa624;
uint8_t DAT_006aa626;
uint8_t DAT_006aa627;
uint8_t DAT_006aa629;
uint8_t DAT_006aa62a;
uint8_t DAT_006aa62b;
uint8_t DAT_006aa62c;
uint8_t DAT_006aa62d;
uint8_t DAT_006aa664;
uint8_t DAT_006aa666;
uint8_t DAT_006aa668;
uint8_t DAT_006aa66a;
uint8_t DAT_006aa66e;
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
uint8_t DAT_007933b8;
uint32_t DAT_007933bc;
uint32_t DAT_007933c0;
uint8_t DAT_007934c4;
uint32_t DAT_007934c8;
uint8_t DAT_007934cc;
uint32_t DAT_007934d8;
uint32_t DAT_007934e0;
uint32_t DAT_007934e4;
uint32_t DAT_007934e8;
uint32_t DAT_007934ec;
uint32_t DAT_007934f0;
uint32_t DAT_007934f4;
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
uint32_t DAT_0079352c;
uint32_t DAT_00793530;
uint32_t DAT_00793534;
uint32_t DAT_00793544;
uint8_t DAT_00793549;
uint8_t DAT_0079354a;
uint8_t DAT_0079354b;
int *DAT_0079354c;
int *DAT_00793550;
void **DAT_00793554;
int *DAT_00793558;
uint32_t DAT_0079355c;
uint32_t DAT_00793560;
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
uint32_t DAT_0079376c;
uint8_t DAT_00793770;
int *DAT_00793774;
uint32_t DAT_00793778;
uint32_t DAT_00793798;
uint32_t DAT_0079379c;
uint8_t DAT_007937a0;
uint8_t DAT_00793fa0;
uint8_t DAT_00794bf0;
uint8_t DAT_00794e14;
/* The input-event ring buffer (write/read cursors + 3 field arrays) is now
 * ONE contiguous object g_inputEventRing in globals_sized.c, reached through
 * the offset-macros in globals.h - see the comment there. The five fields
 * MUST be contiguous because EnqueueInputEvent walks the whole ring off the write
 * cursor's address. */
uint8_t DAT_00796878;
uint8_t DAT_00796aa0;
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
uint8_t DAT_00d9aa20;
uint8_t DAT_00d9aa24;
uint8_t DAT_00d9aa28;
uint8_t DAT_00d9aa2c;
uint8_t DAT_00d9aa30;
uint8_t DAT_00d9aa34;
uint8_t DAT_00d9aa35;
uint8_t DAT_00e525e8;
int *DAT_00e52814;
uint32_t DAT_00e52838;
uint32_t DAT_00e5283c;
uint8_t DAT_00e52858;
uint8_t DAT_00e52859;
uint8_t DAT_00e5285a;
uint8_t DAT_00e5285b;
uint8_t DAT_00e5285c;
uint8_t DAT_00e52864;
uint8_t DAT_00e52868;
uint8_t DAT_00e52e68;
int *DAT_00e5369c;
uint32_t DAT_00e536c0;
uint32_t DAT_00e536c4;
uint8_t DAT_00e536e4;
uint8_t DAT_00e536ec;
/* Zeroed backing for the three per-tick input/cursor timer blocks GameTick
 * updates every elapsed tick. In the original these are static singletons at
 * fixed addresses - the mouse DirectInput device (0xe53698), the keyboard
 * device (0xe52810), and the software-cursor animation object (0x7a7644) -
 * constructed by FUN_004ee270 / FUN_004edd70 / the cursor init. Those
 * constructors are bring-up-stubbed (they skip DirectInput acquisition, see
 * FUN_004ee270.c), so the singletons never exist and GameTick's literal-address
 * timer calls dereferenced unbacked memory and faulted. Each consumer only
 * decrements already-nonzero timer fields (FUN_004ee540 at +0x68..+0x84,
 * FUN_004ee0d0 at +0x258..+0x654) or is gated on an enable flag
 * (AdvanceSpriteAnimation on +0x20), so zeroed backing is a correct no-op for
 * the input-less logo path. Sized to cover each function's highest field read.
 *
 * KNOWN DIVERGENCE: the original devices' other fields are modelled as the
 * scattered separate globals around here (DAT_00e5369c, DAT_00e536c0, the
 * g_cursor* set, etc.); those do NOT alias into these arrays. Harmless while
 * no real input device is acquired. */
uint8_t g_mouseDeviceTimerBlock[0x88];
uint8_t g_keyboardDeviceTimerBlock[0x658];
uint8_t g_softwareCursorAnimBlock[0x38];
uint8_t DAT_00e53c24;
uint8_t DAT_00e53c28;
uint8_t DAT_00e53c2c;
uint8_t DAT_00e53c30;
uint8_t DAT_00e53c3c;
/* g_uiPanelManager was a 1-byte placeholder, but the code dereferences it as
 * a container object: FUN_0050f020/f1b0/f1f0/f150/f230 (WndProc's mouse/key
 * handlers) read its list head at +4, and PanelManager_* touch +4/+5/+8. With
 * only 1 byte of storage, those reads ran off the end into whatever global the
 * linker happened to place next and walked a garbage "widget list", jumping to
 * a junk vtable pointer (crash at eip=0xfff0e483 on the first WM_MOUSEMOVE).
 *
 * 2026-07-14: found + decompiled the REAL constructor (FUN_00507dc0,
 * .CRT$XCU-registered via FUN_00540dc0 - same hidden-static-initializer
 * pattern as g_clientContext's own FUN_00415d40). Confirms the true
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
 * incremental-resize idiom used for DAT_00e9be90/DAT_00f22650. Its `+4`
 * sentinel-list head is self-referencing-initialized in crt_shims_msvc.c's
 * gb_startup_init (same treatment as those two registries) - the other
 * ~25 callers' own offset requirements beyond this confirmed 0xf28-byte
 * lower bound are still untraced, so the struct may need to grow further
 * once those call sites are individually recovered. */
uint8_t DAT_00e53e88[0xf28];
uint8_t DAT_00e55a45;
uint8_t DAT_00e55a46;
int *DAT_00e55a64;
uint8_t DAT_00e55ab8;
/* g_replayContext (was DAT_00e55ce0): moved to globals_sized.c (0x454f9-byte struct - battle/replay turn-event buffer; real extent established via FUN_004e84c0/FUN_004e7b60/FUN_004e80d0/FUN_004e77e0/FUN_004e7de0/FUN_004e6050, all of which take &g_replayContext as their context arg; the ~42 other DAT_00e5.../DAT_00e9... globals formerly declared here in this offset range are now offset-macros into that storage - see globals.h). The CRITICAL_SECTION at +0x45264 (DAT_00e9af44) stays separately declared/sized; this array does not cover it. */
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
uint8_t DAT_00e9b818;
uint8_t DAT_00e9ba40;
/* DAT_00e9be90/DAT_00e9c0fc were 1-byte placeholders, but SweepActiveObjectRegistry's
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
 * DAT_00e9be94/98/9c/DAT_00e9bea0/a4/a8 and DAT_00e9c104/08 are separately-
 * declared globals with their OWN storage, read directly by ~15 other
 * already-ported files - they do NOT alias into this array. Harmless
 * while these registries are never actually populated with real widgets
 * (bring-up doesn't reach button creation yet); must be unified when the
 * real 32-byte struct is properly modeled. */
uint8_t DAT_00e9be90[0x20];
uint32_t DAT_00e9be94;
uint8_t DAT_00e9be98;
uint8_t DAT_00e9be9c;
uint8_t DAT_00e9bea0;
uint8_t DAT_00e9bea4;
uint32_t DAT_00e9bea8;
uint8_t DAT_00e9bed8;
uint8_t DAT_00e9c0fc[0x20];
uint32_t DAT_00e9c104;
uint8_t DAT_00e9c108;
/* Worker-thread control block for FUN_00415500/FUN_004156b0/FUN_004157b0:
 * +4 thread handle (uintptr_t), +8/+0xc two wait handles, +0x10 running flag.
 * Was completely undeclared (the raw ports take it via a dropped ESI
 * register). DAT_00e9c33c (a HANDLE SetEvent'd in Shutdown.c) is this same
 * struct's +8 field under its own Ghidra-assigned symbol - sized to absorb
 * it (0xe9c33c - 0xe9c334 = 8) rather than declare overlapping storage. */
uint8_t DAT_00e9c334[0x18];
uint8_t DAT_00e9c344;
uint8_t DAT_00e9c348;
uint32_t DAT_00e9c9c8;
uint32_t DAT_00e9c9cc;
uint8_t DAT_00e9c9d0;
uint32_t DAT_00e9c9dc;
uint32_t DAT_00e9c9e0;
/* The global sprite registry - the same 0x20-byte sentinel-node circular-list
 * container as the two active-object registries (DAT_00e9be90/DAT_00e9c0fc):
 * LoadSpriteSet/RegisterTankSprite/LoadAvatarSprites all populate it through
 * FUN_004f2f00 (the shared node allocator) and FindSpriteFrame walks it via the
 * same *(root+4) head / +0x1c outer-next idiom. Was a 1-byte placeholder, so
 * FindSpriteFrame ran off the end; sized to 0x20 and sentinel-initialised by
 * gb_startup_init (crt_shims_msvc.c) so an empty registry terminates cleanly
 * and inserts link correctly. See [[bringup-frontier-mouse-hittest]]. */
uint8_t DAT_00ea0e18[0x20];
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
uint32_t DAT_00f22650[0x803];
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
const char s_b_store_exit_00555778[] = "b_store_exit";
const char s_b_store_flag_00555728[] = "b_store_flag";
const char s_b_store_glasse_00555738[] = "b_store_glasse";
const char s_b_store_puton_00555708[] = "b_store_puton";
const char s_b_store_up_005556f0[] = "b_store_up";
const char s_b_storewindow_confirm_00555a8c[] = "b_storewindow_confirm";
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

void *PTR_DAT_0054f378;
void *PTR_DAT_00551ecc;
void *PTR_DAT_00551ed0;
void *PTR_DAT_00552788;
void *PTR_DAT_005535c0;
void *PTR_DAT_00553c9c;
void *PTR_DAT_00553ca8;
void *PTR_DAT_00555500;
void *PTR_DAT_00555650;
void *PTR_DAT_00555cc8;
void *PTR_DAT_00555e2c;
char *PTR_DAT_00563b40;
void *PTR_DAT_00568180;
void *PTR_DAT_00568800;
void *PTR_DAT_00568810;
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
void *PTR_FUN_00544b5c;
void *PTR_FUN_00544b68;
void *PTR_FUN_00544b74;
void *PTR_FUN_00551cb4;
void *PTR_FUN_00551cf0;
void *PTR_FUN_00551e88;
void *PTR_FUN_0055208c;
void *PTR_FUN_005520a0;
void *PTR_FUN_00555aa4;
void *PTR_FUN_00555ac4;
void *PTR_FUN_00555af8;
void *PTR_FUN_00555b18;
void *PTR_FUN_00555b38;
void *PTR_FUN_00555b54;
void *PTR_FUN_00555b68;
void *PTR_FUN_00555b7c;
void *PTR_FUN_00555bd0;
void *PTR_FUN_00555bf0;
void *PTR_FUN_00555c14;
void *PTR_FUN_00555c34;
void *PTR_FUN_00555c54;
void *PTR_FUN_00555c68;
void *PTR_FUN_00555ccc;
void *PTR_FUN_00555ce0;
void *PTR_FUN_00555cf4;
void *PTR_FUN_00555d14;
void *PTR_FUN_00555d34;
void *PTR_FUN_00555d54;
void *PTR_FUN_00555d74;
void *PTR_FUN_00555d98;
void *PTR_FUN_00555dac;
void *PTR_FUN_00555dcc;
void *PTR_FUN_00555dec;
void *PTR_FUN_00555e0c;
void *PTR_FUN_00555e30;
void *PTR_FUN_00555e54;
void *PTR_FUN_00555e74;
void *PTR_FUN_00555e88;
void *PTR_FUN_00555ea8;
void *PTR_FUN_00555ec8;
void *PTR_FUN_00555edc;
void *PTR_FUN_00555ef0;
void *PTR_FUN_00555f04;
void *PTR_FUN_00555f18;
void *PTR_FUN_00555f38;
void *PTR_FUN_00555f58;
void *PTR_FUN_00555f7c;
void *PTR_FUN_00555f9c;
void *PTR_FUN_00555fbc;
void *PTR_FUN_00555fdc;
void *PTR_FUN_00556008;
void *PTR_FUN_00556038;
void *PTR_FUN_00556058;
void *PTR_FUN_00556078;
void *PTR_FUN_00556098;
void *PTR_FUN_005560bc;
void *PTR_FUN_005560d0;
void *PTR_FUN_005560f0;
void *PTR_FUN_00556110;
void *PTR_FUN_00556160;
void *PTR_FUN_00556180;
void *PTR_FUN_00556194;
void *PTR_FUN_005561a8;
void *PTR_FUN_005561c8;
void *PTR_FUN_005561ec;
void *PTR_FUN_0055620c;
void *PTR_FUN_00556230;
void *PTR_FUN_00556250;
void *PTR_FUN_00556264;
void *PTR_FUN_00556284;
void *PTR_FUN_005562a8;
void *PTR_FUN_005562c8;
void *PTR_FUN_005562f4;
void *PTR_FUN_00556308;
void *PTR_FUN_0055631c;
void *PTR_FUN_00556340;
void *PTR_FUN_00556360;
void *PTR_FUN_00556380;
void *PTR_FUN_005563a8;
void *PTR_FUN_005563d0;
void *PTR_FUN_005563f0;
void *PTR_FUN_00556424;
void *PTR_FUN_00556448;
void *PTR_FUN_00556468;
void *PTR_FUN_00556488;
void *PTR_FUN_0055649c;
void *PTR_FUN_005564bc;
void *PTR_FUN_005564d0;
void *PTR_FUN_005564f0;
void *PTR_FUN_00556510;
void *PTR_FUN_00556524;
void *PTR_FUN_00556544;
void *PTR_FUN_00556558;
void *PTR_FUN_0055656c;
void *PTR_FUN_0055658c;
void *PTR_FUN_005565ac;
void *PTR_FUN_005565cc;
void *PTR_FUN_005565e4;
void *PTR_FUN_005565f8;
void *PTR_FUN_0055661c;
void *PTR_FUN_00556640;
void *PTR_FUN_00556660;
void *PTR_FUN_00556680;
void *PTR_FUN_005566a0;
void *PTR_FUN_005566c0;
void *PTR_FUN_00556a40;
void *PTR_FUN_005572dc;
/* Connection object's 2-entry vtable {HandleSocketEvent, NoOpMethod} -
 * decoded byte-for-byte from orig .data 0x5572e8-0x5572ef (values
 * 0x4e57c0, 0x429800). Only referenced by the connection-object family
 * (FUN_004e54e0.c/DestroyConnectionObject.c), unlike the widely-shared
 * PTR_FUN_005572dc immediately before it, so safe to type as a real
 * function-pointer array instead of a lone null placeholder. */
void *PTR_FUN_005572e8[2] = { (void *)HandleSocketEvent, (void *)NoOpMethod };
void *PTR_FUN_005572f0;
void *PTR_FUN_00557300;
void *PTR_FUN_0055745c;
void *PTR_FUN_00557484;
/* LoadSpriteSet's per-entry sprite-object vtable slot 0 (dtor, called
 * from LoadSpriteSet.c on error via slot 0). Decoded from orig .data
 * 0x557524: FUN_004f14c0. Was a bare uninitialized global, so the dtor
 * call crashed on a null vtable. PTR_FUN_00557528/0x557530 immediately
 * after are separately-addressed vtables already used standalone
 * elsewhere (FUN_004f1750.c/FUN_004f2e40.c/FUN_004f2f00.c) - left
 * untouched, not part of this one. */
void *PTR_FUN_00557524 = (void *)FUN_004f14c0;
void *PTR_FUN_00557528;
void *PTR_FUN_00557530;
void *PTR_FUN_00557534;
void *PTR_FUN_00557538;
void *PTR_FUN_00557550;
void *PTR_FUN_005575a8;
void *PTR_FUN_00557cfc;
void *PTR_FUN_00557f80;
void *PTR_FUN_005637cc;
void *PTR_FUN_005637d0;
void *PTR_FUN_00563a60;
void *PTR_FUN_00563aec;
void *PTR_FUN_00563da0;
void *PTR_FUN_00563da4;
void *PTR_FUN_00563da8;
void *PTR_FUN_0056d0f0;
void *PTR_LAB_0054b450;
void *PTR_LAB_0054b458;
void *PTR_LAB_00550378;
void *PTR_LAB_00551cb8;
void *PTR_LAB_00551cf4;
void *PTR_LAB_005520a4;
void *PTR_LAB_005520ac;
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
void *PTR_LAB_00553ff8;
void *PTR_LAB_00554000;
void *PTR_LAB_005572e0;
void *PTR_LAB_00557434;
/* Real 7-slot vtable (was a bare scalar) - the DirectSound streaming
 * object's runtime vtable, installed via `*unaff_ESI = &PTR_LAB_005574cc`
 * at the end of FUN_004eebe0/FUN_004ef3a0 (see those files' header
 * comments). Slots recovered from orig .data at 0x5574cc-0x5574e8:
 * 0=NoOpMethodStdcall1 (0x4038b0), 1=PollSoundBufferPosition ("tick",
 * currently bring-up-bypassed to a no-op - see its own header), 2 is
 * un-cross-referenced address 0x4eed10, not yet wired to a real ported
 * function since nothing on the confirmed bring-up path calls it,
 * 3=FUN_004eef00 (0x4eef00, "stop/release channel" - called from
 * InitGame.c), 4=DecodeSoundBufferChunk (0x4eef80), 5=NoOpMethodStdcall1,
 * 6=NoOpMethod (0x429800, shared plain-ret no-op stub). */
void *PTR_LAB_005574cc[7] = {
  (void *)NoOpMethodStdcall1, (void *)PollSoundBufferPosition,
  (void *)0, (void *)FUN_004eef00, (void *)DecodeSoundBufferChunk,
  (void *)NoOpMethodStdcall1, (void *)NoOpMethod,
};
/* Same shape as PTR_LAB_005574cc but the FUN_004ef7e0-installed
 * bring-up vtable (set briefly during construction, before
 * FUN_004eebe0/FUN_004ef3a0 swap in PTR_LAB_005574e8 then
 * PTR_LAB_005574cc) - recovered from orig .data at 0x5574e0-0x5574ec:
 * 0/2=NoOpMethodStdcall1 (0x4038b0), 1=NoOpMethod (0x429800),
 * 3=PollSoundBufferPosition (0x4ef450). */
void *PTR_LAB_005574e0[4] = {
  (void *)NoOpMethodStdcall1, (void *)NoOpMethod,
  (void *)NoOpMethodStdcall1, (void *)PollSoundBufferPosition,
};
/* The runtime vtable for FUN_004ef3a0-constructed secondary-channel
 * objects (FUN_004ef3a0 itself keeps this vtable permanently, unlike
 * FUN_004eebe0's primary-channel object which swaps to
 * PTR_LAB_005574cc at the end of construction) - recovered from orig
 * .data at 0x5574e8-0x5574f8: 0=NoOpMethodStdcall1,
 * 1=PollSoundBufferPosition (currently bring-up-bypassed to a no-op),
 * 2 is un-cross-referenced address 0x4ef4c0, not yet wired to a real
 * ported function, 3=FUN_004ef5b0 (0x4ef5b0, "stop/release channel" -
 * called from InitGame.c, same role as PTR_LAB_005574cc's
 * FUN_004eef00 but for this object's own field layout), 4 is
 * un-cross-referenced address 0x4ef610. */
void *PTR_LAB_005574e8[5] = {
  (void *)NoOpMethodStdcall1, (void *)PollSoundBufferPosition,
  (void *)0, (void *)FUN_004ef5b0, (void *)0,
};
void *PTR_LAB_0055752c;
void *PTR_LAB_0055755c;
void *PTR_LAB_00557594;
void *PTR_LAB_00557598;
void *PTR_LAB_005575ac;
void *PTR_LAB_005575b8;
void *PTR_LAB_005575c8;
void *PTR_LAB_00557610;
void *PTR_LAB_00557654;
void *PTR_LAB_00557b94;
void *PTR_LAB_00557bbc;
void *PTR_LAB_00557be4;
void *PTR_LAB_00557c0c;
void *PTR_LAB_00557c34;
void *PTR_LAB_00557c5c;
void *PTR_LAB_00557c84;
void *PTR_LAB_00557cac;
void *PTR_LAB_00557cd4;
void *PTR_LAB_00557d28;
void *PTR_LAB_00557d50;
void *PTR_LAB_00557d78;
void *PTR_LAB_00557da0;
void *PTR_LAB_00557dc8;
void *PTR_LAB_00557df0;
void *PTR_LAB_00557e18;
void *PTR_LAB_00557e40;
void *PTR_LAB_00557e68;
void *PTR_LAB_00557e90;
void *PTR_LAB_00557eb8;
void *PTR_LAB_00557ee0;
void *PTR_LAB_00557f08;
void *PTR_LAB_00557f30;
void *PTR_LAB_00557f58;
void *PTR_LAB_00563ddc;
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
void __fastcall FUN_00429730(int param_1);
void __fastcall FUN_00448370(int param_1);
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
  (void *)FUN_00443540,
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
  (void *)FUN_00443da0,                                     /* 0  dtor 0x443da0 */
  (void *)State07_AvatarStore_ProcessPacket,                /* 1  0x4440c0 */
  (void *)CGameState_NoOpVirtual_B, (void *)CGameState_NoOpVirtual_B, /* 2-3 */
  (void *)FUN_004452c0,                                     /* 4  0x4452c0 (stub) */
  (void *)FUN_00445450,                                     /* 5  0x445450 - store window builder */
  (void *)FUN_004475c0,                                     /* 6  0x4475c0 (stub) */
  (void *)State07_AvatarStore_OnEnter,                      /* 7  0x447760 */
  (void *)State07_AvatarStore_OnExit,                       /* 8  0x448050 */
  (void *)FUN_00448370,                                     /* 9  0x448370 */
  (void *)CGameState_NoOpVirtual_A,                         /* 10 0x448430 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 11-12 0x429800 */
  (void *)FUN_00448440,                                     /* 13 0x448440 (stub) */
  (void *)FUN_00449050,                                     /* 14 0x449050 (stub) */
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
  (void *)FUN_0043e700,                                     /* 3  0x43e700 */
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
 * FUN_004b3f90, this state's constructor, at *param_1). Every slot
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
  (void *)FUN_004c1b90,                                     /* 10 0x4c1b90 */
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
  (void *)FUN_00429730,                                     /* 9  0x429730 */
  (void *)State10_Loading_AppendChatLine,                   /* 10 0x442240 (shared) */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 11-12 0x429800 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 13-14 0x429800 */
  (void *)State03_GameRoomList_RenderRoomLabel,             /* 15 0x429810 */
  (void *)NoOpMethod, (void *)NoOpMethod,                   /* 16-17 0x429800 */
};

uint32_t DAT_00000006;
uint32_t DAT_00007f00;
uint32_t DAT_00544380;
uint32_t DAT_005443a0;
uint32_t DAT_005443a4;
uint32_t DAT_005443f4;
uint32_t DAT_005443fc;
uint32_t DAT_00544400;
uint32_t DAT_0054442c;
uint32_t DAT_005445b4;
uint32_t DAT_005445ec;
uint32_t DAT_005448e8;
uint32_t DAT_005448ec;
uint32_t DAT_00544968;
uint32_t DAT_0054496c;
uint32_t DAT_00544970;
uint32_t DAT_00544974;
uint32_t DAT_00544a88;
uint32_t DAT_0054b460;
uint32_t DAT_00551b78;
uint32_t DAT_00551b79;
uint32_t DAT_00551b7c;
uint32_t DAT_00551e2c;
uint32_t DAT_00551e30;
uint32_t DAT_00551ec4;
uint32_t DAT_00551ed4;
uint32_t DAT_00552c68;
uint32_t DAT_00553b90;
uint32_t DAT_00553bb4;
uint32_t DAT_00553bb8;
uint32_t DAT_00553bbc;
uint32_t DAT_00553bf4;
uint32_t DAT_00553bf8;
uint32_t DAT_00553c18;
uint32_t DAT_00553c1c;
uint32_t DAT_00553c90;
uint32_t DAT_00553c94;
uint32_t DAT_00553c98;
uint32_t DAT_00553ca0;
uint32_t DAT_00553ca4;
uint32_t DAT_00555654;
uint32_t DAT_00555b4c;
uint32_t DAT_00556980;
uint32_t DAT_00557318;
uint32_t DAT_0055731c;
uint32_t DAT_00557320;
uint32_t DAT_00557324;
uint32_t DAT_00557328;
uint32_t DAT_0055732c;
uint32_t DAT_00557330;
uint32_t DAT_00557334;
uint32_t DAT_00557660;
uint32_t DAT_00557664;
uint32_t DAT_00557948;
uint32_t DAT_0055794c;
uint32_t DAT_00557a40;
uint32_t DAT_00557a44;
uint32_t DAT_00557fd8;
uint32_t DAT_00563730;
uint32_t DAT_00563770;
uint32_t DAT_00563774;
uint32_t DAT_005637bc;
uint32_t DAT_005637c0;
uint32_t DAT_005637c4;
uint32_t DAT_005637c8;
uint32_t DAT_005637d4;
uint32_t DAT_005637e8;
uint32_t DAT_0056382c;
uint32_t DAT_005638ec;
uint32_t DAT_0056390c;
uint32_t DAT_00563a4c;
uint32_t DAT_00563ad8;
uint32_t DAT_00563afc;
uint32_t DAT_00563b44;
uint32_t DAT_00563b48;
uint32_t DAT_00563b4c;
uint32_t DAT_00563bcc;
uint32_t DAT_00563bec;
uint32_t DAT_00563c6c;
uint32_t DAT_00563cec;
uint32_t DAT_00563d0c;
uint32_t DAT_00563d8c;
uint32_t DAT_00563d90;
uint32_t DAT_00563d94;
uint32_t DAT_00563d98;
uint32_t DAT_00563df0;
uint32_t DAT_00563df4;
uint32_t DAT_00568100;
uint32_t DAT_00568101;
uint32_t DAT_00568184;
uint32_t DAT_00568188;
uint32_t DAT_00568318;
uint32_t DAT_00568654;
uint32_t DAT_005686d4;
uint32_t DAT_00568714;
uint32_t DAT_00568738;
uint32_t DAT_0056873c;
uint32_t DAT_00568740;
uint32_t DAT_00568744;
uint32_t DAT_00568748;
uint32_t DAT_0056874c;
uint32_t DAT_00568750;
uint32_t DAT_00568754;
uint32_t DAT_00568758;
uint32_t DAT_0056875c;
uint32_t DAT_00568760;
uint32_t DAT_00568764;
uint32_t DAT_00568768;
uint32_t DAT_0056876c;
uint32_t DAT_00568770;
uint32_t DAT_00568774;
uint32_t DAT_00568778;
uint32_t DAT_0056877c;
uint32_t DAT_00568798;
uint32_t DAT_0056879c;
uint32_t DAT_005687a0;
uint32_t DAT_005687a4;
uint32_t DAT_005687a8;
uint32_t DAT_005687ac;
uint32_t DAT_005687b0;
uint32_t DAT_005687b4;
uint32_t DAT_005687b8;
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
uint32_t DAT_00568944;
uint32_t DAT_00569144;
uint32_t DAT_00569344;
uint32_t DAT_00569348;
uint32_t DAT_00569b48;
uint32_t DAT_0056d468;
uint32_t DAT_00598e7e;
/* Real values read from the binary at 0x5a9050 (see globals.h). */
const uint32_t g_fullnessGaugeThresholds[5] = { 1, 10, 30, 60, 100 };
uint32_t DAT_005a9290;
uint32_t DAT_005a9350;
uint32_t DAT_005a94b0;
uint32_t DAT_005a9550;
uint32_t DAT_005a960c;
uint32_t DAT_005a9624;
uint32_t DAT_005a9640;
uint32_t DAT_005a965c;
uint8_t *DAT_005a9680;
uint32_t DAT_005a9684;
uint32_t DAT_005a9688;
uint32_t DAT_005a9784;
uint32_t DAT_005a9884;
uint32_t DAT_005a9888;
uint32_t DAT_005a9988;
uint32_t DAT_005a9989;
uint32_t DAT_005a998a;
uint32_t DAT_005a99e8;
uint32_t DAT_005a99ec;
uint32_t DAT_005a99f0;
uint32_t DAT_005a99f4;
uint32_t DAT_005a99f8;
uint32_t DAT_005a9cf4;
uint32_t DAT_005a9cf6;
uint32_t DAT_005a9cf8;
uint32_t DAT_005ab4f4;
uint32_t DAT_005ab4fc;
uint32_t DAT_005ab500;
uint32_t DAT_005ab604;
uint32_t DAT_005ab608;
uint32_t DAT_005ab704;
uint32_t DAT_005ab708;
uint32_t DAT_005ab709;
uint32_t DAT_005ab70a;
uint32_t DAT_005ab88c;
uint32_t DAT_005ab890;
uint32_t DAT_005ab8d4;
uint32_t DAT_005ab8e0;
uint32_t DAT_005ab91c;
uint32_t DAT_005ab920;
uint32_t DAT_005aba28;
uint32_t DAT_005aba2c;
uint32_t DAT_005aba30;
uint32_t DAT_005aba34;
uint32_t DAT_005aba38;
uint32_t DAT_005ada38;
uint32_t DAT_005ada3c;
uint32_t DAT_005ae33c;
uint32_t DAT_005ae344;
uint32_t DAT_005ae348;
uint32_t DAT_005ae34c;
uint32_t DAT_005ae350;
uint32_t DAT_005ae358;
uint32_t DAT_005ae450;
uint32_t DAT_005ae740;
uint32_t DAT_005ae74c;
uint32_t DAT_005ae75c;
uint32_t DAT_005ae760;
uint32_t DAT_005ae7b0;
uint32_t DAT_005ae7cc;
uint32_t DAT_005ae7d0;
uint32_t DAT_005ae7dc;
uint32_t DAT_005ae7e0;
uint32_t DAT_005ae7e8;
uint32_t DAT_005ae7ec;
uint32_t DAT_005ae7f0;
uint32_t DAT_005ae7f8;
uint32_t DAT_005ae800;
uint32_t DAT_005ae804;
uint32_t DAT_005ae808;
uint32_t DAT_005ae80c;
uint32_t DAT_005ae810;
uint32_t DAT_005ae814;
uint32_t DAT_005ae818;
uint32_t DAT_005ae81c;
uint32_t DAT_005ae820;
uint32_t DAT_005ae824;
uint32_t DAT_005ae828;
uint32_t DAT_005ae82c;
uint32_t DAT_005ae830;
uint32_t DAT_005ae834;
uint32_t DAT_005ae838;
uint32_t DAT_005ae83c;
uint32_t DAT_005ae840;
uint32_t DAT_005ae844;
uint32_t DAT_005ae920;
uint32_t DAT_005ae924;
uint32_t DAT_005ae928;
uint32_t DAT_005ae92c;
uint32_t DAT_005ae930;
uint32_t DAT_005ae934;
uint32_t DAT_005ae93c;
uint32_t DAT_005ae940;
uint32_t DAT_005af140;
uint32_t DAT_005af144;
uint32_t DAT_005af944;
uint32_t DAT_005b0144;
uint32_t DAT_005b0148;
uint32_t DAT_005b01c4;
uint32_t DAT_005b01e4;
uint32_t DAT_005b01fc;
uint32_t DAT_005b05fc;
uint32_t DAT_005b0efc;
uint32_t DAT_005b12fc;
uint32_t DAT_005b137c;
uint32_t DAT_005b13fc;
uint32_t DAT_005c7fb8;
uint32_t DAT_005f2f48;
uint32_t DAT_005f2f54;
uint32_t DAT_005f2f55;
uint32_t DAT_005f3774;
uint32_t DAT_005f48a8;
uint32_t DAT_005f4ab4;
uint32_t DAT_005f5348;
uint32_t DAT_00656369;
uint32_t DAT_0067e3e4;
uint32_t DAT_0067e5f0;
uint32_t DAT_0067e608;
uint32_t DAT_0067e814;
uint32_t DAT_0067e82c;
uint32_t DAT_0067ea38;
uint32_t DAT_0067ea50;
uint32_t DAT_0067ec5c;
uint32_t DAT_0067ec6c;
uint32_t DAT_006a4c74;
uint32_t DAT_006a4c78;
uint32_t DAT_006a6480;
uint32_t DAT_006a6484;
uint32_t DAT_006a6488;
uint32_t DAT_006a648c;
uint32_t DAT_006a648d;
uint32_t DAT_006a6490;
uint32_t DAT_006a6494;
uint32_t DAT_006a6498;
uint32_t DAT_006a6499;
uint32_t DAT_006a649c;
uint32_t DAT_006a64a0;
uint32_t DAT_006a76e0;
uint32_t DAT_006a76e4;
uint32_t DAT_006a76ec;
uint32_t DAT_006a7700;
uint32_t DAT_006a770c;
uint32_t DAT_006a772c;
uint32_t DAT_006a7730;
uint32_t DAT_006a7734;
uint32_t DAT_006a7736;
uint32_t DAT_006a7750;
uint32_t DAT_006a7754;
uint32_t DAT_006a7f6c;
uint32_t DAT_006a7f75;
uint32_t DAT_006a7f76;
uint32_t DAT_006a7fa8;
uint32_t DAT_006a81b4;
uint32_t DAT_006a9b8c;
uint32_t DAT_006a9d98;
uint32_t DAT_006a9db0;
uint32_t DAT_006a9fbc;
uint32_t DAT_006a9fd4;
uint32_t DAT_006aa1e0;
uint32_t DAT_006aa1f8;
uint32_t DAT_006aa404;
uint32_t DAT_006aa40c;
uint32_t DAT_006aa410;
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
uint32_t DAT_007949c8;
uint32_t DAT_00794e48;
uint32_t g_lastCursorDirection;
uint32_t DAT_00989680;
uint32_t DAT_00e54a9c;
uint32_t DAT_00e54aa0;
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
uint32_t DAT_00e54da8;
uint32_t DAT_00e55a34;
uint32_t DAT_00e55a54;
uint32_t DAT_00e55a58;
uint32_t DAT_00e9c578;
uint32_t DAT_00e9cd30;
uint32_t DAT_00f25840;
uint32_t DAT_00f25844;
uint32_t DAT_00f25848;
uint32_t DAT_00f2584c;
uint32_t DAT_00f25850;
uint32_t DAT_00f25854;
uint32_t DAT_00f25858;
uint32_t DAT_00f2585c;
uint32_t DAT_00f25860;
uint32_t DAT_00f25864;
uint32_t DAT_00f25868;
uint32_t DAT_00f2586c;
uint32_t DAT_00f25870;
uint32_t DAT_00f25874;
uint32_t DAT_00f25878;
uint32_t DAT_00f2587c;
uint32_t DAT_00f25880;
uint32_t DAT_00f258a4;
uint32_t DAT_00f258a8;
uint32_t DAT_00f258c0;
uint32_t DAT_00f258c4;
uint32_t DAT_00f258c8;
uint32_t DAT_00f258cc;
uint32_t DAT_00f258d0;
uint32_t DAT_00f258d4;
uint32_t DAT_00f258e0;
uint32_t DAT_00f258e4;
uint32_t DAT_00f258e8;
uint32_t DAT_00f25900;
uint32_t DAT_00f25904;
uint32_t DAT_00f25908;
uint32_t DAT_00f2590c;
uint32_t DAT_00f25910;
uint32_t DAT_00f25914;
uint32_t DAT_00f25918;
uint32_t DAT_00f2591c;
uint32_t DAT_00f25920;
uint32_t DAT_00f25924;
uint32_t DAT_00f25928;
uint32_t DAT_00f2592c;
uint32_t DAT_00f25930;
uint32_t DAT_00f25934;
uint32_t DAT_00f25938;
uint32_t DAT_00f2593c;
uint32_t DAT_00f25940;
uint32_t DAT_00f25944;
uint32_t DAT_00f25960;
uint32_t DAT_00f25964;
uint32_t DAT_00f25968;
uint32_t DAT_00f2596c;
uint32_t DAT_00f25970;
uint32_t DAT_00f25974;
uint32_t DAT_00f25978;
uint32_t DAT_00f2597c;
uint32_t DAT_00f25980;
uint32_t DAT_00f259b0;
uint32_t DAT_00f259b4;
uint32_t DAT_00f259b8;
uint32_t DAT_00f259bc;
uint32_t DAT_00f259c0;
uint32_t DAT_00f259c4;
uint32_t DAT_00f259c8;
uint32_t DAT_00f259cc;
uint32_t DAT_00f259d0;
uint32_t DAT_00f259e0;
uint32_t DAT_00f259e4;
uint32_t DAT_00f259e8;
uint32_t DAT_00f259ec;
uint32_t DAT_00f259f0;
uint32_t DAT_00f259f4;
uint32_t DAT_00f259f8;
uint32_t DAT_00f259fc;
uint32_t DAT_00f25a10;
uint32_t DAT_00f25a14;
uint32_t DAT_00f25a18;
uint32_t DAT_00f25a1c;
uint32_t DAT_00f25a20;
uint32_t DAT_00f25a24;
uint32_t DAT_00f25a28;
uint32_t DAT_00f25a2c;
uint32_t DAT_00f25a40;
uint32_t DAT_00f25a7c;
uint32_t DAT_00f25a80;
uint32_t DAT_00f25a84;
uint32_t DAT_00f25a88;
uint32_t DAT_00f25a9c;
uint32_t DAT_00f25aa0;
uint32_t DAT_00f25aa4;
uint32_t DAT_00f25aa8;
uint32_t DAT_00f25ab0;
uint32_t DAT_00f25ab4;
uint32_t DAT_00f25ac0;
uint32_t DAT_00f25b00;
uint32_t DAT_00f25b04;
uint32_t DAT_00f25b08;
uint32_t DAT_00f25b0c;
uint32_t DAT_00f25b10;
uint32_t DAT_00f25b14;
uint32_t DAT_00f25b18;
uint32_t DAT_00f25b1c;
uint32_t DAT_00f25b20;
uint32_t DAT_00f25b24;
uint32_t DAT_00f25b28;
uint32_t DAT_00f25b2c;
uint32_t DAT_00f25b30;
uint32_t DAT_00f25b34;
uint32_t DAT_00f25b38;
uint32_t DAT_00f25b3c;
uint32_t DAT_00f25b40;
uint32_t DAT_00f25b44;
uint32_t DAT_00f25b48;
uint32_t DAT_00f25b4c;
uint32_t DAT_00f25b50;
uint32_t DAT_00f25b54;
uint32_t DAT_00f25b58;
uint32_t DAT_00f25b5c;
uint32_t DAT_00f25b60;
uint32_t DAT_00f25b64;
uint32_t DAT_00f25b68;
uint32_t DAT_00f25b6c;
uint32_t DAT_00f25b70;
uint32_t DAT_00f25b74;
uint32_t DAT_00f25b78;
uint32_t DAT_00f25b7c;
uint32_t DAT_00f25b80;
uint32_t DAT_00f25b84;
uint32_t DAT_00f25b88;
uint32_t DAT_00f25b8c;
uint32_t DAT_00f25c20;
uint32_t DAT_00f25c24;
uint32_t DAT_00f25c28;
uint32_t DAT_00f25c2c;
uint32_t DAT_00f25c30;
uint32_t DAT_00f25c34;
uint32_t DAT_00f25c38;
uint32_t DAT_00f25c3c;
uint32_t DAT_00f25c40;
uint32_t DAT_00f25c44;
uint32_t DAT_00f25c48;
uint32_t DAT_00f25c4c;
uint32_t DAT_00f25d3c;
uint32_t DAT_00f25d40;
uint32_t DAT_00f25d44;
uint32_t DAT_00f25d98;
uint32_t DAT_00f25e00;
uint32_t DAT_00f25e04;
uint8_t *DAT_00f25e08;
uint32_t DAT_00f25e0c;
uint32_t DAT_00f25e10;
uint32_t DAT_00f25e20;
uint32_t DAT_00f25e78;
uint32_t DAT_00f25ed0;
uint32_t DAT_00f25ee0;
uint32_t DAT_00f25ee4;
uint32_t DAT_00f25f00;
uint32_t DAT_00544360;
uint32_t DAT_00544368;
uint32_t DAT_00544370;
uint32_t DAT_00544378;
uint32_t DAT_005448d8;
uint32_t DAT_005448e0;
uint32_t DAT_00544aa8;
uint32_t DAT_00544ab0;
uint32_t DAT_00544ab8;
uint32_t DAT_00544ac0;
uint32_t DAT_00544ac8;
uint32_t DAT_00544ad0;
uint32_t DAT_00544ad8;
uint32_t DAT_00544ae0;
uint32_t DAT_00544ae8;
uint32_t DAT_00544af0;
uint32_t DAT_00544af8;
uint32_t DAT_00544b00;
uint32_t DAT_0054bb4c;
uint32_t DAT_0054c870;
uint32_t DAT_00557fe4;
uint32_t DAT_00558014;
uint32_t DAT_00558018;
uint32_t DAT_00558048;
uint32_t DAT_00558068;
uint32_t DAT_00558070;
uint32_t DAT_00558078;
uint32_t DAT_00563d9c;
uint32_t DAT_005687f8;
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
uint32_t DAT_005a92a4;
uint32_t DAT_005a92b8;
uint32_t DAT_005a92bc;
uint32_t DAT_005a92c8;
uint32_t DAT_005a93e0;
uint32_t DAT_005a93e4;
uint32_t DAT_005a93e8;
uint32_t DAT_005a93ec;
uint32_t DAT_005a94b4;
uint32_t DAT_005a94b8;
uint32_t DAT_005a94bc;
uint32_t DAT_005a9554;
uint32_t DAT_005a9558;
uint32_t DAT_005a955c;
uint32_t DAT_005ab4f8;
uint32_t DAT_005ab888;
uint32_t DAT_005ab8d8;
uint32_t DAT_005ae340;
uint32_t DAT_005ae738;
uint32_t DAT_005ae7f4;
uint32_t DAT_005ae7fc;
uint32_t DAT_0079361c;
uint32_t DAT_00f25884;
uint32_t DAT_00f25888;
uint32_t DAT_00f2588c;
uint32_t DAT_00f25890;
uint32_t DAT_00f25894;
uint32_t DAT_00f25898;
uint32_t DAT_00f2589c;
uint32_t DAT_00f258a0;
uint32_t DAT_00f25a30;
uint32_t DAT_00f25a44;
uint32_t DAT_00f25a48;
uint32_t DAT_00f25a4c;
uint32_t DAT_00f25a50;
uint32_t DAT_00f25a54;
uint32_t DAT_00f25a58;
uint32_t DAT_00f25a5c;
uint32_t DAT_00f25a60;
uint32_t DAT_00f25a64;
uint32_t DAT_00f25a68;
uint32_t DAT_00f25a6c;
uint32_t DAT_00f25a70;
uint32_t DAT_00f25a74;
uint32_t DAT_00f25a78;
uint32_t DAT_00f25a8c;
uint32_t DAT_00f25a90;
uint32_t DAT_00f25a94;
uint32_t DAT_00f25a98;
uint32_t DAT_00f25aac;
uint32_t DAT_00f25ab8;
uint32_t DAT_00f25ac4;
uint32_t DAT_00f25ac8;
uint32_t DAT_00f25acc;
uint32_t DAT_00f25ad0;
uint32_t DAT_00f25ad4;
uint32_t DAT_00f25ad8;
uint32_t DAT_00f25adc;
uint32_t DAT_00f25ae0;
uint32_t DAT_00f25ae4;
uint32_t DAT_00f25ae8;
uint32_t DAT_00f25aec;
uint32_t DAT_00f25af0;
uint32_t DAT_00f25af4;
uint32_t DAT_00f25af8;
uint32_t DAT_00f25afc;
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
void *PTR_s_101blast_xes_0056d2b4;
void *PTR_s_11blast_xes_0056d290;
void *PTR_s_121blast_xes_0056d33c;
void *PTR_s_12blast_xes_0056d310;
void *PTR_s_142blast_xes_0056d344;
void *PTR_s_151blast_xes_0056d2c8;
void *PTR_s_72blast_xes_0056d2e8;
void *PTR_s_72blast_xes_0056d328;
void *PTR_s_92blast_xes_0056d2f0;
void *PTR_s_92blast_xes_0056d330;

/* Code-label address markers - see globals.h. */
uint8_t LAB_00401000;
uint8_t LAB_00401060;
uint8_t LAB_005159d0;
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
uint8_t *switchD_0050fe76__switchdataD_0051008c;
uint8_t *switchD_0051392e__switchdataD_00514460;
