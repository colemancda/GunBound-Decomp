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
 * FUN_004e77e0/FUN_004e7de0/FUN_004e6050 (all take &g_replayContext as
 * their context arg) plus the ~42 other DAT_00e5.../DAT_00e9... globals
 * that fell inside this range and are now offset-macros into this array
 * (see globals.h) instead of independent symbols, so param_N-relative
 * access and direct DAT_ access observe the same memory. Does NOT cover
 * the CRITICAL_SECTION at +0x45264 (DAT_00e9af44), which stays
 * independently declared/sized above - a real but pre-existing gap for
 * FUN_004e7de0's own use of that offset, not addressed by this change. */
unsigned char g_replayContext[0x454f9];

/* The named-texture-cache singleton (was the 1-byte DAT_00eb1bd8).
 * Constructed by InitTextureCache from the CRT static-initializer
 * 0x5429b0, destroyed via the atexit thunk FUN_00543950 ->
 * DestroyTextureCache. PreloadTexture registers textures by name
 * ("CharacterTexture1", "TagTexture", "TornadoTexture", ...),
 * FindTextureCacheEntryByName looks them up, FlushTextureCache
 * COM-Releases and frees everything. FlushTextureCache (whose `this`
 * Ghidra dropped as an uninitialised EBX - see its header) walks two
 * heap lists off +0x114 and +0x1b4, then zeroes an inline 15-entry
 * table at +0x401bc and a count at +0x401b8 - so the object extends to
 * at least 0x401fc bytes. 0x40200 covers every offset it touches.
 * Distinct from the small [0x20] sentinel-list container DAT_00ea0e18.
 * Before this sizing, &g_textureCache+0x401bc landed on whatever global
 * the linker placed next, and under the stricter (Lutris) wine the
 * dropped EBX was garbage and faulted outright. */
unsigned char g_textureCache[0x40200];

/* The input-event ring buffer (orig 0x795070), ONE contiguous 0x1808-byte
 * object: write cursor +0, read cursor +4, then three 0x200-entry x4 field
 * arrays at +8 / +0x808 / +0x1008 (msg / param1 / param2). The field names
 * g_inputEventQueueWriteIndex/ReadIndex/g_inputEventMsgQueue/Param1Queue/
 * Param2Queue are offset-macros into this in globals.h. Must be contiguous:
 * EnqueueInputEvent (the ring push, fed &this ring via conn+0x20 from the socket
 * receive path) accesses the whole object off the write cursor's address as
 * a base pointer. When the five were separate scattered globals, the pusher
 * wrote the event data next to the write cursor while the consumer read the
 * far-away MsgQueue symbol -> phantom (0,0,0) events -> spurious ServerSelect
 * quit. See globals.h's comment. */
unsigned char g_inputEventRing[0x1808];

/* The full-width/CJK bitmap-font glyph table (was the 1-byte DAT_005b3628).
 * 0x8000 double-byte codepoints x 0x18 bytes (12x16 1bpp cell) = 0xc0000
 * bytes; LoadBitmapFont reads exactly 0xc0000 from graphics.xfs's
 * "font.fnt" entry into it (orig 0x4eae91 `mov eax,0xc0000`), and
 * BlitRLESprite indexes it as &g_fullWidthFontGlyphs + ((hi & 0x7f)<<8 | lo) * 0x18
 * (max index 0x7fff -> last glyph at 0xbfff8, extent 0xc0000). This is the
 * companion of the ASCII table below; the two font reads are sequential.
 *
 * Note: many DAT_005f3xxx/DAT_006xxxxx "globals" have addresses inside this
 * range but are NOT sub-accesses of this buffer - they are Ghidra's
 * rendering of client-context arena OFFSETS (e.g. `mov [eax+0x5f3768],5`
 * with eax = g_clientContext becomes `*(&DAT_005f3768 + g_clientContext)`),
 * a distinct subsystem that never touches this symbol's storage. So unlike
 * g_replayContext this sizing needs no offset-macro reconciliation. */
unsigned char g_fullWidthFontGlyphs[0xc0000];

/* The ASCII bitmap-font glyph table (was the 1-byte DAT_00673628).
 * 256 glyphs x 12 bytes (6x12 1bpp cells) = 0xc00 bytes; BlitRLESprite
 * indexes it as &DAT_00673628 + char*0xc and BlitFontGlyphClipped reads
 * the 12 row-bytes. Populated at startup by LoadBitmapFont, which reads
 * 0x600 bytes (128 glyphs) from graphics.xfs's "font.fnt" entry. A
 * one-byte cell under-sized it, so char*0xc walked off the end into
 * adjacent globals. */
unsigned char DAT_00673628[0xc00];

/* g_loginKeyTable (was DAT_0056dbf0) - the AES login-key table the handshake
 * encrypts the username with: EncodeHandshakeBlock does
 * RijndaelSetKey(&DAT_0056dbf0 + idx*0x10, 0x10, 1, schedule) and the world
 * server decrypts `encryptedUsername` with the same fixed key (its `.login`).
 * RESTORED (2026-07-18) from the original .data at 0x56dbf0: the port declared
 * it as a single zeroed uint8_t, so the client expanded an ALL-ZERO key and
 * every login went out encrypted under it - the server therefore decoded the
 * same constant garbage username every run and answered badUsername (0x0010).
 * Same zeroed-.data-constant class as ".epa"/"%d"/"push". 10 x 16-byte slots
 * (the region runs up to the 0x56dc90 event-key block). */
const unsigned char DAT_0056dbf0[0xa0] = {
    0xff, 0xb3, 0xb3, 0xbe, 0xae, 0x97, 0xad, 0x83,
    0xb9, 0x61, 0x0e, 0x23, 0xa4, 0x3c, 0x2e, 0xb0,
    0xff, 0xb3, 0xb3, 0xbe, 0xae, 0x97, 0xad, 0x83,
    0xb9, 0x61, 0x0e, 0x23, 0xa4, 0x3c, 0x2e, 0xb0,
    0xa9, 0x27, 0x53, 0x04, 0x1b, 0xfc, 0xac, 0xe6,
    0x5b, 0x23, 0x38, 0x34, 0x68, 0x46, 0x03, 0x8c,
    0xff, 0xb3, 0xb3, 0xbe, 0xae, 0x97, 0xad, 0x83,
    0xb9, 0x61, 0x0e, 0x23, 0xa4, 0x3c, 0x2e, 0xb0,
    0x7e, 0x60, 0x31, 0x86, 0x7e, 0x60, 0x31, 0x86,
    0xd3, 0xf5, 0xc2, 0xa8, 0x7e, 0x60, 0x31, 0x86,
    0x01, 0xff, 0x03, 0x00, 0x07, 0xff, 0x07, 0x00,
    0x02, 0xff, 0x0f, 0x00, 0x0b, 0xff, 0x01, 0x00,
    0x02, 0x00, 0x06, 0xff, 0x0a, 0xff, 0x04, 0xff,
    0x05, 0xff, 0x06, 0x00, 0x08, 0xff, 0x09, 0xff,
    0x08, 0x00, 0x09, 0x00, 0x03, 0x00, 0x0b, 0x00,
    0x0c, 0x00, 0x0d, 0x00, 0x0e, 0x00, 0x04, 0x00,
    0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x13, 0x00,
    0x14, 0x00, 0x15, 0x00, 0x16, 0x00, 0x17, 0x00,
    0x18, 0x00, 0x19, 0x00, 0x1a, 0x00, 0x1b, 0x00,
    0x1c, 0x00, 0x0a, 0xff, 0x1d, 0x00, 0x05, 0x00,
};

/* CPanelManager's 0x100-byte scratch table. Its constructor (FUN_00507dc0,
 * orig 0x507dc0 - `mov ecx,0x40 / mov edi,0x7933c0 / rep stosd`) clears 0x40
 * dwords starting here; globals.c had it as a single uint32_t. */
unsigned char DAT_007933c0[0x100];
