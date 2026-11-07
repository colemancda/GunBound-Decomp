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
 * g_valueGuardLock is the value-guard/packet-encode lock WinMain enters
 * before anything could have initialized it - see the .CRT$XCU hook in
 * src/cxx/crt_shims_msvc.c, which runs InitializeCriticalSection on
 * all three before the CRT calls WinMain. */
unsigned char g_valueGuardLock[24];
unsigned char DAT_005a9084[24];
/* 0xe9af44 is NOT separate storage: it is g_replayContext + 0x45264, inside
 * that struct's own 0x454f9 extent.  See globals.h - it is now an offset-macro
 * into g_replayContext, and crt_shims_msvc.c initialises it at that address. */

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

/* (FUN_004e77e0 in the note below is now BroadcastRingEvent.) */
/* The turn-event/replay-buffer context struct (was the 1-byte
 * DAT_00e55ce0). 0x454f9 bytes; established by cross-referencing every
 * offset dereferenced by FUN_004e84c0/FUN_004e7b60/FUN_004e80d0/
 * FUN_004e77e0/FUN_004e7de0/FUN_004e6050 (all take &g_replayContext as
 * their context arg) plus the ~42 other DAT_00e5.../DAT_00e9... globals
 * that fell inside this range and are now offset-macros into this array
 * (see globals.h) instead of independent symbols, so param_N-relative
 * access and direct DAT_ access observe the same memory. Does NOT cover
 * the CRITICAL_SECTION at +0x45264 (DAT_00e9af44), which IS inside it and
 * independently declared/sized above - a real but pre-existing gap for
 * FUN_004e7de0's own use of that offset, not addressed by this change. */
unsigned char g_replayContext[0x454f9];

/* ---- The 20 WinMain value-guard slot cells, all 0x224 ----------------
 * WinMain (0x40d8e0) encodes one opcode into each of these 20 cells via
 * `mov edi,<obj>; call 0x40a380`; the addresses and opcodes are the map in
 * winmain_bringup.h.  They are ordinary 0x224-byte CValueGuard cells in the
 * original, but globals.c had them as 1-byte (or 4-byte) scalars, which the
 * guard flip would turn into out-of-bounds reads AND writes - CValueGuard::Peek
 * re-encodes the cell it just read, touching bytes 4..0x17.  Sized here so the
 * externs in globals.h can stay `uint8_t` and every existing `&DAT_...` call
 * site keeps its `unsigned char *` type (the whole point of this TU).
 *
 * Verified 2026-08-16: no other symbol referenced anywhere in the tree falls
 * inside any of the 20 ranges EXCEPT one at exactly +0x14 in every single
 * case - that is the cell's own `tableHandle` word, which Ghidra named
 * separately because some code tests it directly (`if (DAT_00796ab4 != 0)`).
 * Those 20 alias globals are deliberately left as independent scalars: while
 * the key table is zeroed (winmain_bringup.c) every handle written is 0 and
 * the aliases stay 0 too, so the two views agree.  If the key table is ever
 * made real they must be unified onto <cell>+0x14. */
unsigned char DAT_00e525e8[0x224];   /* slot  0, opcode 0x118 */
unsigned char DAT_007947a0[0x224];   /* slot  1, opcode 0x0   */
unsigned char DAT_007a7690[0x224];   /* slot  2, opcode 0x2   */
unsigned char DAT_00e9bc68[0x224];   /* slot  3, opcode 0x4   */
unsigned char DAT_00e53c60[0x224];   /* slot  4, opcode 0x5   */
unsigned char DAT_00796cc8[0x224];   /* slot  5, opcode 0x8   */
unsigned char DAT_00e9ba40[0x224];   /* slot  6, opcode 0xa   */
unsigned char DAT_00794bf0[0x224];   /* slot  7, opcode 0xf   */
unsigned char DAT_00e55ab8[0x224];   /* slot  8, opcode 0x14  */
unsigned char DAT_007949c8[0x224];   /* slot  9, opcode 0x19  */
unsigned char DAT_00e9c110[0x224];   /* slot 10, opcode 0x1e  */
unsigned char DAT_00e9b818[0x224];   /* slot 11, opcode 0x32  */
unsigned char DAT_00e53470[0x224];   /* slot 12, opcode 0x46  */
unsigned char DAT_00794e48[0x224];   /* slot 13, opcode 0x50  */
unsigned char DAT_007a78b8[0x224];   /* slot 14, opcode 0x62  */
unsigned char DAT_00796aa0[0x224];   /* slot 15, opcode 0x64  */
unsigned char DAT_00e9c578[0x224];   /* slot 16, opcode 0xa0  */
unsigned char DAT_00e9c7a0[0x224];   /* slot 17, opcode 0xc8  */
unsigned char DAT_00e9c350[0x224];   /* slot 18, opcode 0x100 */
unsigned char DAT_00e9bed8[0x224];   /* slot 19, opcode 0x168 */

/* ---- Four 6-cell CValueGuard tables ---------------------------------
 * FUN_004ac260 / FUN_004ac330 / FUN_004ac400 / FUN_004ac4d0 each peek one
 * cell of their own table at `<index> * 0x224 + <base>`, where <index> is
 * the result of the peek immediately above (which Ghidra discarded).  The
 * bases are 0xcd8 = 6 * 0x224 apart, so each table is exactly six cells.
 * No symbol referenced anywhere in the tree falls inside any of the four
 * ranges (verified 2026-08-16); nothing declared them before, which is why
 * those four files were parked on the flip checklist. */
/* ADDENDUM: these four tables and the one at 0xe9cd30 are slices of ONE 30-cell array.
 * FUN_005438d0 destroys it as `_eh_vector_destructor_iterator_(0xe9cd30, 0x224, 0x1e, ...)`
 * (push 0x1e / push 0x224 / push 0xe9cd30 at 0x5438d5), and the five bases are exactly
 * 6 cells apart (0xe9cd30, 0xe9da08, 0xe9e6e0, 0xe9f3b8, 0xea0090).  FUN_004ac180 walks
 * from cell (n-1) of the first slice to `cmp ebp, 0xe9da08`, i.e. the end of that slice. */
unsigned char g_guardCells[30 * 0x224];

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
 * Distinct from the small [0x20] sentinel-list container g_spriteRegistry.
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

/* CPanelManager's 0x100-byte scratch table. Its constructor (PanelManager_Construct,
 * orig 0x507dc0 - `mov ecx,0x40 / mov edi,0x7933c0 / rep stosd`) clears 0x40
 * dwords starting here; globals.c had it as a single uint32_t. */
unsigned char g_chatInputText[0x100];

/* CPanelManager's vtable (orig 0x557cfc, stored at +0 by its constructor
 * PanelManager_Construct). globals.c had it as a single zero-initialised `void *`, so
 * any dispatch past slot 0 read adjacent zeroed globals - PanelManager_
 * ClearAllFocus ends with `(**(code **)(*this + 0x18))()`, i.e. SLOT 6, which
 * therefore jumped to null as soon as State03's OnEnter reached
 * BuildLobbyChatPanel.
 *
 * Slot -> original address -> ported symbol:
 *   0  0x507e10  PanelManager_ScalarDtor
 *   1  0x50f020  PanelManager_DispatchMouseMove
 *   2  0x507ea0  PanelManager_DispatchMouseDown
 *   3  0x50f1b0  PanelManager_DispatchMouseUp
 *   4  0x50f1f0  PanelManager_DispatchRightMouseDown
 *   5  0x50f150  PanelManager_DispatchRightMouseUp
 *   6  0x507ed0  -> TextEntry_RestoreChatInput   (0x507ed0 is a stack-neutral thunk that
 *                 just `jmp 0x507e30`; that target uses only globals, no
 *                 `this`, so the existing no-argument dispatch is correct)
 *   7  0x50f230  PanelManager_DispatchKeyDown
 * Declared here with minimal prototypes and cast to void * - this TU
 * deliberately does not include globals.h/functions.h. */
extern void *PanelManager_ScalarDtor();
extern void  PanelManager_DispatchMouseMove();
extern void  PanelManager_DispatchMouseDown();
extern void  PanelManager_DispatchMouseUp();
extern void  PanelManager_DispatchRightMouseDown();
extern void  PanelManager_DispatchRightMouseUp();
extern void  TextEntry_RestoreChatInput();
extern void  PanelManager_DispatchKeyDown();

void *PTR_FUN_00557cfc[8] = {
    (void *)&PanelManager_ScalarDtor,
    (void *)&PanelManager_DispatchMouseMove,
    (void *)&PanelManager_DispatchMouseDown,
    (void *)&PanelManager_DispatchMouseUp,
    (void *)&PanelManager_DispatchRightMouseDown,
    (void *)&PanelManager_DispatchRightMouseUp,
    (void *)&TextEntry_RestoreChatInput,
    (void *)&PanelManager_DispatchKeyDown,
};

/* The launcher session blob (was the 1-byte DAT_005b3440 in globals.c).
 * WinMain sscanfs the launcher's 96-char hex token into it as 0x30 (48)
 * separate bytes - `_sscanf(_Src,"%02x",&DAT_005b3440 + iVar13)` for
 * iVar13 = 0..0x2f - and BuildSystemInfoBlob then reads it as three cipher
 * blocks at +0, +0x10 and +0x20. At one byte every launcher-driven run
 * overflowed it into whatever the linker placed next.
 * Sized 0x40: the next global in the original's address space is 0x5b3480,
 * and a scan of globals.h found no declared global inside
 * [0x5b3440, 0x5b3480), so unlike g_replayContext this needs no
 * offset-macro reconciliation. */
unsigned char DAT_005b3440[0x40];

/* The word-filter AtlArray header at 0xe9c9dc (was two independent scalars,
 * DAT_00e9c9dc and DAT_00e9c9e0). AtlArray_AppendCString (was
 * AppendWordFilterEntry; called once per parsed line
 * while LoadFourWordList/LoadSoundConfig load FourWord.txt/Sound.txt) takes this
 * object's address as a genuine `this` (ECX under the original's thiscall,
 * confirmed via objdump: `mov ecx,0xe9c9dc; call 0x415bc0`, then inside
 * that function `mov esi,ecx; ... [esi+0]` = data ptr, `[esi+4]` = count,
 * `[esi+8]` = capacity (checked against AtlArray_GrowBuffer's `this[2]`),
 * `[esi+0xc]` = the growth-hint AtlArray_GrowBuffer reads as `this[3]`) and
 * uses fixed byte offsets into it - so all four 4-byte fields need to be
 * genuinely contiguous, which plain top-level C globals don't guarantee.
 * +0 (DAT_00e9c9dc) and +4 (DAT_00e9c9e0) already had their own symbols -
 * CheckChatWordFilter.c/FUN_00543870.c read/free them directly as a data
 * pointer and a count - so they're kept as offset-macros into this blob
 * (see globals.h) rather than renamed; +8/+0xc were never referenced
 * anywhere in the port before AtlArray_AppendCString's call site got
 * fixed, so they never got their own DAT_ symbols from Ghidra. Sized
 * 0x10 - the whole
 * header, nothing more is read/written by any known caller. */
unsigned char g_wordFilterArrayHeader[0x10];

/* Four objects that a dropped register argument pointed at, and which had no
 * declaration anywhere in the port.  Each was reached through an
 * uninitialised local -- `undefined4 *unaff_ESI;` -- so the writes below were
 * landing at whatever address the register happened to hold.  Recovering the
 * register is only half the fix; it has to point at something.
 *
 * Extents were bounded from the original rather than guessed.  A lower bound
 * comes from the highest field each callee touches; an upper bound comes from
 * the next address the binary uses as an OBJECT BASE (an address loaded into
 * a register, as opposed to dereferenced in place as [0xADDR], which is just
 * a field of the object already in progress).  Where the two meet, the size
 * is exact rather than generous.
 *
 * g_workerThreadBlock (0xe9c9c4, spans exactly to g_wordFilterArrayHeader):
 *   +0x0  vtable            WorkerThread_Shutdown stores &PTR_LAB_005520a4
 *   +0x4  thread handle     Shutdown.c waits on it (was DAT_00e9c9c8)
 *   +0x8  event handle      WorkerThread_Shutdown calls SetEvent on it (DAT_00e9c9cc)
 *   +0xc  stop flag         written as a single byte (DAT_00e9c9d0, and it
 *                           was already declared uint8_t - which is what
 *                           confirms the layout rather than merely fitting it)
 *   The upper three fields keep their DAT_ names as offset-macros, the same
 *   treatment g_wordFilterArrayHeader's fields get, so no existing user of
 *   those symbols changes.
 *
 * DAT_007a7644  0x1c : callee writes [1]..[3]; next object base is
 *                      g_cursorTexture at 0x7a7660.
 * DAT_00eb1a78  0x160: callee writes +0x15c; next object base is exactly
 *                      0x160 higher - an exact fit.
 * DAT_00f22518  0x138: callee writes [0x4c] (+0x134); next object base is
 *                      g_spriteDrawBatchPool, 0x138 higher.
 * DAT_00eb1698  0x3e0: its destructor reads +0x3d8; next object base is
 *                      DAT_00eb1a78, exactly 0x3e0 higher - an exact fit.
 *
 * Two more of these are NOT here.  0xe53698 and its neighbour DAT_00e5369c
 * sit in the region globals.c already flags as a KNOWN DIVERGENCE (the input
 * devices modelled as scattered separate globals), and the next object base
 * above it is 0x5a8 away, so its real extent is not established.  Guessing a
 * size there would trade a wild write for a silent overlap, which is harder
 * to find, not easier. */
unsigned char g_workerThreadBlock[0x18];
unsigned char DAT_007a7644[0x1c];
unsigned char DAT_00eb1a78[0x160];
unsigned char DAT_00eb1698[0x3e0];
unsigned char DAT_00f22518[0x138];

/* ---- Two 0x30-byte container-policy objects -------------------------
 * HashMap_Construct is that object's constructor and writes twelve fields
 * spanning +0x00..+0x2c through the base it receives in ESI.  The two
 * static-initialiser thunks FUN_00540f00 and FUN_00540f20 hand it these
 * globals (`mov eax,0x794e14` / `mov eax,0xe9bea8`, then call the
 * FUN_0040d180 wrapper), so each needs the full 0x30 bytes rather than
 * the 1- and 4-byte cells globals.c gave them.
 *
 * Both spans are clear, checked before resizing: nothing is declared
 * inside 0x794e14..0x794e44 (the next symbol, DAT_00794e48, is +0x34
 * away) and nothing inside 0xe9bea8..0xe9bed8 (DAT_00e9bea0/a4 are
 * BELOW it, and the next above, DAT_00e9bed8, sits at exactly +0x30 --
 * an exact fit, the same criterion used for the objects above).
 *
 * The externs in globals.h stay `uint8_t`, so every existing
 * `&DAT_00794e14` / `&DAT_00e9bea8` call site keeps its type. */
unsigned char DAT_00794e14[0x30];
unsigned char DAT_00e9bea8[0x30];

/* ---- The scene-transform scratch cluster at 0x5a9130..0x5a94c0 --------
 * Five 4x4 float matrices (0x40 each) and two quaternion scratches (0x10
 * each) that MultiplyMatrix4x4ToScratch/InPlace (0x4f1f50/0x4f2240),
 * SceneNode_BuildLocalTransform (0x4f3440), MultiplyQuaternionsToScratch
 * (0x4f3a60), QuaternionToRotationMatrix (0x4f3ba0),
 * SlerpQuaternionsToScratch (0x4f3c70) and the projection builder in
 * SceneNode_UpdateTransformAndCamera (0x4e9cc0) read and write as whole
 * objects.  globals.c had only
 * six interior dwords of these declared (DAT_005a9290/9350/94b0 + the
 * split fields beside them); DAT_005a9130, DAT_005a9250 and DAT_005a93f0
 * were not declared at all, which is what kept the matrix-multiply
 * operand registers deliberately unapplied (see the note in
 * MultiplyMatrix4x4ToScratch.c).  The interior split fields (92a4/92b8/
 * 92bc/92c8 inside 9290; 93e4/93e8/93ec inside 93e0; 94b4/94b8/94bc
 * inside 94b0) are float offset macros in globals.h now.  No other
 * declared global falls inside any of these extents. */
unsigned char DAT_005a9130[0x40] = {
    0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f}; /* identity matrix, as in the orig .data */
unsigned char DAT_005a9250[0x40] = {
    0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f}; /* identity matrix, as in the orig .data */
unsigned char DAT_005a9290[0x40] = {
    0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f}; /* identity matrix, as in the orig .data */
unsigned char DAT_005a9350[0x40] = {
    0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f}; /* identity matrix, as in the orig .data */
unsigned char DAT_005a93e0[0x10] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f}; /* identity quaternion (0,0,0,1.0f), as in the orig .data */
unsigned char DAT_005a93f0[0x40] = {
    0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f}; /* identity matrix, as in the orig .data */
unsigned char DAT_005a94b0[0x10] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0x3f}; /* identity quaternion (0,0,0,1.0f), as in the orig .data */

/* The DirectInput mouse/cursor singleton at 0xe53698 (was the 0x88-byte
 * g_mouseDeviceTimerBlock in globals.c, sized only to its GameTick timer
 * consumers). 0x5a8 is exact-fit: the constructor MouseDevice_Construct's highest
 * write is the byte at +0x5a4 and the next object (g_uiPanelManager,
 * 0xe53c40) sits 0x5a8 above the base. The formerly split-out fields
 * (DAT_00e5369c at +4, the cursor deltas at +0x28/+0x2c, +0x4c/+0x54,
 * the clamp-bound dwords at +0x58c..+0x598, g_cursorFreeMode at +0x5a4)
 * are offset macros in globals.h now. */
unsigned char g_mouseDeviceTimerBlock[0x5a8];

/* DirectInput enumerated-device table (0x674f70, 16 x 0x244) filled by
 * EnumInputDevicesCallback; count is g_dinputDeviceCount in globals.c. */
unsigned char g_dinputDeviceInstances[16 * 0x244];

/* ---- Initialised string cells (round 19, whole-tree nonzero-initial-value scan) ----
 * Each of these was a one-byte zero cell in globals.c although the original
 * object is a NUL-terminated string in .data that callers pass by address
 * (&DAT_x as a char*), so every such use saw an empty string. Bytes copied
 * verbatim from orig/GunBound.gme .data; the cell keeps its header extern
 * (uint8_t/uint32_t) and binds to this storage at link time. */
uint32_t DAT_005532bc[7] = {0xd7c5babd, 0xf6c1ccc0, 0xc8f8bf20, 0x202d20ad, 0x6c68636a, 0x35376565, 0x00000000}; /* EUC-KR+ASCII '........ .... - jchlee75' */
uint32_t DAT_005535e8[2] = {0x706c6568, 0x00000000}; /* ASCII 'help' */
uint32_t DAT_0056d440[2] = {0xffffffff, 0x00000000}; /* EUC-KR+ASCII '....' */
uint32_t DAT_00552e24[3] = {0xbabddac4, 0xbabdf0b8, 0x00000000}; /* EUC-KR+ASCII '........' */
uint32_t DAT_00553648[1] = {0x00006272}; /* ASCII 'rb' */
uint32_t DAT_005530ec[6] = {0xc720a5c0, 0xb1ceb7c1, 0xb8a1b7d7, 0x202d20d3, 0x65736f6c, 0x00696972}; /* EUC-KR+ASCII '.. .......... - loserii' */
uint32_t DAT_005535dc[1] = {0x00006f74}; /* ASCII 'to' */
uint32_t DAT_005530ac[6] = {0xf7beb5bf, 0xc4b6b82f, 0x20c3c6c9, 0x6373202d, 0x676e616a, 0x00000000}; /* EUC-KR+ASCII '........... - scjang' */
uint32_t DAT_00555c90[2] = {0x64616564, 0x00000000}; /* ASCII 'dead' */
uint32_t DAT_00551e2c[1] = {0x00000030}; /* ASCII '0' */
uint32_t DAT_00552db4[12] = {0xecbbeeb9, 0xbb20bbc0, 0x20dfbea9, 0xcfb4d5c7, 0x202ed9b4, 0xfcbaaab3, 0xb020f8c1, 0xc0adb0c7, 0xc7b520bb, 0xe2b1a3c3, 0xc7a7c020, 0x000020d8}; /* EUC-KR+ASCII '...... .... ....... ...... ...... ...... .... ' */
uint32_t DAT_0055310c[15] = {0xeebec4b4, 0xc2b4a1b0, 0xc6be202c, 0xc020cfb4, 0xb4a6c1cc, 0xc4b420c2, 0xf6b9eebe, 0xbf20b0b8, 0xb8aeb8ec, 0xd8c620a6, 0xc4c3b3b0, 0xedb0ceb5, 0x202d202e, 0xbf20afba, 0x00dfc1d5}; /* EUC-KR+ASCII '........, .... ...... ........ ...... ........... - .. ....' */
uint32_t DAT_00556980[2] = {0x67617264, 0x00000000}; /* ASCII 'drag' */
uint32_t DAT_00552728[2] = {0x6e65706f, 0x00000000}; /* ASCII 'open' */
uint32_t DAT_00552ef0[11] = {0xb8b1a9b4, 0xb920aab3, 0xb0b6c1ab, 0xb7b520c7, 0xbcfab920, 0xd6c020f6, 0xba20c2b4, 0x20e1b0f1, 0xa1b0d1c7, 0x2e2ef6c1, 0x0000002e}; /* EUC-KR+ASCII '...... ...... .. .... .... .... .........' */
uint32_t DAT_00552e30[14] = {0xedb0cfc7, 0xc0cdbd20, 0xbbb820ba, 0xd4b0203a, 0xbac0d3c0, 0xb9ebc320, 0x20ceb7cc, 0xe6b1f1c1, 0x20a7b620, 0xe5c0a1b0, 0xb9e7c020, 0xbfeebed5, 0x5e5e20e4, 0x0000002a}; /* EUC-KR+ASCII '.... .... ..: ...... ...... .... .. .... ........ ^^.' */
uint32_t DAT_00552e14[4] = {0xb5bfeebf, 0xc4202d20, 0xb8babdda, 0x00babdf0}; /* EUC-KR+ASCII '.... - ........' */
uint32_t DAT_00552f1c[4] = {0xaeb8fcb0, 0x62202d20, 0x6873616c, 0x00003534}; /* EUC-KR+ASCII '.... - blash45' */
uint32_t DAT_00552f34[6] = {0xceb5f0b8, 0xb5f0b820, 0xceba20ce, 0xc7b5dac0, 0xe4bfbcbc, 0x00000021}; /* EUC-KR+ASCII '.... .... ..........!' */
uint32_t DAT_00553bcc[2] = {0x706f7264, 0x00000000}; /* ASCII 'drop' */
uint32_t DAT_0058b8d6[1] = {0x00430043}; /* ASCII 'C' */
uint32_t DAT_00552d60[13] = {0xc5bddac0, 0xb020c7c0, 0xc0adb0c7, 0xbabd20ba, 0xceb7babd, 0xc5f6c120, 0xb4c3bdb5, 0x4f202ed9, 0xa1fea328, 0x3bfea3e4, 0x20272f29, 0xe3c7c0b4, 0x007ee3c7}; /* EUC-KR+ASCII "...... ...... ...... ......... O(......;).' ......~" */
uint32_t PTR_DAT_00552788[1] = {0x006e7572}; /* ASCII 'run' */
uint32_t DAT_0055328c[12] = {0xc020b9b9, 0xb0fdb5cc, 0xd9b420c9, 0xc5c3bd20, 0x20c2b4b0, 0xdfbec5b0, 0x20212121, 0xa1bffdc1, 0xba20aab3, 0xc1bbb3b8, 0x212121e0, 0x00000000}; /* EUC-KR+ASCII '.. ...... .. ...... ....!!! ...... ......!!!' */
uint32_t DAT_00553b88[2] = {0x726f6874, 0x00000000}; /* ASCII 'thor' */
uint32_t PTR_DAT_00555cc8[1] = {0x00656369}; /* ASCII 'ice' */
uint32_t DAT_00553354[7] = {0xc1202121, 0x20c7b0f1, 0xb7ecbf20, 0x5ee7b7ea, 0xc120205e, 0x20c7b0f1, 0x00002121}; /* EUC-KR+ASCII '!! ....  ......^^  .... !!' */
uint32_t DAT_00554060[2] = {0x6e6f6f6d, 0x00000000}; /* ASCII 'moon' */
uint32_t DAT_00552e90[5] = {0xe2c7babc, 0x6843203a, 0x69746f61, 0xe1ab2063, 0x003b2d5f}; /* EUC-KR+ASCII '....: Chaotic .._-;' */
uint32_t DAT_00553570[2] = {0xb0bfecb3, 0x00000000}; /* EUC-KR+ASCII '....' */
uint32_t DAT_005533b0[6] = {0xdac0f0b5, 0xc620cec0, 0x20e5c0c0, 0x4579202d, 0x724f4f53, 0x00000049}; /* EUC-KR+ASCII '...... .... - yESOOrI' */
uint32_t DAT_005531e0[6] = {0xc720a5c0, 0xb1ceb7c1, 0xb8a1b7d7, 0x202d20d3, 0x6e686f6a, 0x0035796e}; /* EUC-KR+ASCII '.. .......... - johnny5' */
uint32_t DAT_00552ea4[6] = {0xf7bef7c1, 0xc7b0203a, 0xeebfd9b9, 0xbf20e5b5, 0xc0b5bfee, 0x000000da}; /* EUC-KR+ASCII '....: ........ ......' */
uint32_t DAT_005533d0[13] = {0xccb9e7c0, 0xd9b4f8be, 0xbe20c2b4, 0xb8e2b1ea, 0xe8b520a6, 0xd9b4c2b4, 0xb820e9b8, 0x20ceb5f0, 0xc020a6c1, 0xc0f8b8df, 0xc1dab0cc, 0x54202ed2, 0x0020545f}; /* EUC-KR+ASCII '.......... ...... ........ .... .. ........... T_T ' */
uint32_t DAT_00552de4[12] = {0xc7c7bfc4, 0xc120a6b8, 0xbea9bfd9, 0xd5c720df, 0xd9b4cfb4, 0xe3b4202e, 0xa6b8e8b9, 0xbef7b220, 0x20dfbeee, 0xcfb4d5c7, 0x202ed9b4, 0x00000000}; /* EUC-KR+ASCII '...... ...... ....... ...... ...... ....... ' */
uint32_t DAT_00553390[8] = {0xfabcb9bf, 0x207ec6be, 0xc6bed2c7, 0xf6c1f6b9, 0xadbcb2b2, 0xa3b8ceba, 0x2e2ec5bc, 0x0000002e}; /* EUC-KR+ASCII '......~ .....................' */
uint32_t DAT_00552e68[10] = {0xa1c2afc6, 0xe7be203a, 0xfac1a1c4, 0xe9b8cfc7, 0xbea1c420, 0x20ccc0e0, 0xa1bfe8b9, 0xc0afb920, 0x5f2d20bd, 0x00003b2d}; /* EUC-KR+ASCII '....: .......... ...... .... .... -_-;' */
uint32_t PTR_DAT_00555e2c[1] = {0x00796c66}; /* ASCII 'fly' */
uint32_t DAT_00553370[6] = {0xe6b0e8b9, 0xc0f0b520, 0xb3ccc0da, 0x202d20ca, 0x75726f6f, 0x00006173}; /* EUC-KR+ASCII '.... ........ - oorusa' */
uint32_t DAT_00552d94[8] = {0xa1b0a6c1, 0xc0d5be20, 0x20ceb7b8, 0xdfbed8c7, 0x20d2c720, 0xe9b5cfc0, 0xcfb4d4c0, 0x002ed9b4}; /* EUC-KR+ASCII '.... ...... .... .. ...........' */
uint32_t DAT_00553508[12] = {0xccc0d1b5, 0xc4cbbe20, 0xc4deb4e1, 0xb0cfc7e1, 0xe7bb20d4, 0xb020c2b4, 0x20b5b5cd, 0xccb9e7c0, 0xbbc0d6c0, 0xb020cdb0, 0xb8f6c1b0, 0x00002cb8}; /* EUC-KR+ASCII '.... ............ .... .... .......... ......,' */
uint32_t DAT_00552ffc[5] = {0xf7beb5bf, 0xc4b6b82f, 0x20c3c6c9, 0x6863202d, 0x006f6b75}; /* EUC-KR+ASCII '........... - chuko' */
uint32_t DAT_0055207c[2] = {0x6d756e45, 0x00000000}; /* ASCII 'Enum' */
uint32_t DAT_00552ed4[7] = {0x7975cea8, 0x6fd8a820, 0xcda82077, 0xa820646e, 0x6c6c65df, 0x69d4a820, 0x00006867}; /* EUC-KR+ASCII '..uy ..ow ..nd ..ell ..igh' */
uint32_t DAT_00552f90[5] = {0xa8b0d1c3, 0x2d20b6b5, 0x72697020, 0x61696e61, 0x00000000}; /* EUC-KR+ASCII '...... - pirania' */
uint32_t DAT_00553b90[2] = {0x65726966, 0x00000000}; /* ASCII 'fire' */
uint32_t DAT_00552d38[8] = {0xd9b9f0b8, 0xb020cfc0, 0xbfd9b9c7, 0x20e5b5ee, 0xdfb9b3b0, 0x2d20dac0, 0x68746520, 0x00617265}; /* EUC-KR+ASCII '...... ........ ...... - ethera' */
uint32_t DAT_00552c68[2] = {0xfae6d1d2, 0x00000000}; /* EUC-KR+ASCII '....' */
uint32_t DAT_00553200[8] = {0xe4c6a8c8, 0xf6c1ccc0, 0xc0f0b520, 0xb3ccc0da, 0x202d20ca, 0x69736564, 0x72656e67, 0x00000000}; /* EUC-KR+ASCII '........ ........ - designer' */
uint32_t DAT_00553404[15] = {0xaec6f7c6, 0xcdbfa7b6, 0xb420c2b4, 0x20a5b8d9, 0xafc0dac0, 0xcdbfb5b5, 0xbccfbf20, 0xb8b5b5ba, 0xdfc320a6, 0xcfc7b8b1, 0xb820edb0, 0xbee9b5b8, 0xb4c0bdfa, 0x2ed9b4cf, 0x00000000}; /* EUC-KR+ASCII '.......... .... ........ ........ ........ .............' */
uint32_t DAT_005535c4[2] = {0x6b63696b, 0x00000000}; /* ASCII 'kick' */
uint32_t DAT_00553148[16] = {0xe9b5d7b1, 0xc720ccc0, 0xb4fabeb0, 0xbcbc20f8, 0xc7c0e8b0, 0xb5deb220, 0xd4c720b5, 0xbf20b2b2, 0x20aeb8ec, 0xa1bfe7b0, 0xb820adbc, 0xc1eebed6, 0x20e2b1b3, 0xaeb9a7b6, 0xd9b4ccc0, 0x0000002e}; /* EUC-KR+ASCII '...... ...... ...... .... .... .... ...... ........ .........' */
uint32_t DAT_00552fac[7] = {0xa1b7e5b5, 0xbac0efb0, 0x20d6bf20, 0xaeb8ccc0, 0xb3c8be20, 0xc1c0bfaa, 0x000021f6}; /* EUC-KR+ASCII '........ .. .... ........!' */
uint32_t DAT_00552f64[11] = {0xbac0b9b8, 0xb5ccc020, 0x20ccc0e9, 0xd3c0d4b0, 0xa1bfd3bc, 0xbd20adbc, 0xb7aec6ba, 0x20babdb9, 0xa8b2eec2, 0xa6b8e2b1, 0x00000000}; /* EUC-KR+ASCII '.... ...... .......... ........ ........' */
uint32_t DAT_00552fc8[7] = {0xccc0b0b0, 0xb8cfc720, 0xc6be20e9, 0xb520dbc5, 0xb4b3b8e5, 0x2ed9b4cf, 0x00000000}; /* EUC-KR+ASCII '.... .... .... .........' */
uint32_t DAT_005535f0[1] = {0x00000068}; /* ASCII 'h' */
uint32_t DAT_00556770[2] = {0x6d657469, 0x00000000}; /* ASCII 'item' */
uint32_t DAT_00553188[11] = {0xe9b5d7b1, 0xc820ccc0, 0xb8dac0a5, 0xbcbc20b8, 0xa1bff3bb, 0xbb20adbc, 0xc1f3b6e7, 0xd4b020f8, 0xb4c6be20, 0x2cf3b6cf, 0x00000000}; /* EUC-KR+ASCII '...... ...... ........ ...... .. ......,' */
uint32_t DAT_00553554[7] = {0xd3c0d4b0, 0xb7c1c720, 0xb7d7b1ce, 0x20d3b8a1, 0x6f63202d, 0x6b69736d, 0x00000000}; /* EUC-KR+ASCII '.... .......... - comsik' */
uint32_t DAT_00553258[10] = {0xf6b9adbc, 0xb0202620, 0x20d3c0d4, 0xf0b5f6b9, 0xb7c1c720, 0xb7d7b1ce, 0x20d3b8a1, 0x6572202d, 0x61726464, 0x006e6f67}; /* EUC-KR+ASCII '.... & .... .... .......... - reddragon' */
uint32_t DAT_00553018[9] = {0xc3bd3432, 0xb5b5a3b0, 0xbac7b020, 0x20d2c7fc, 0xc020f6bc, 0xb0bbc0d6, 0xb0b020cd, 0xcfb4c0bd, 0x002ed9b4}; /* EUC-KR+ASCII '24...... ...... .. ...... .........' */
uint32_t DAT_0054b460[1] = {0x00000020}; /* ASCII ' ' */
uint32_t DAT_005535a4[2] = {0x6574756d, 0x00000000}; /* ASCII 'mute' */
uint32_t DAT_0058bb04[1] = {0x00390039}; /* ASCII '9' */
uint32_t DAT_0055303c[14] = {0xcfc0b8b8, 0xb0e2b120, 0xe3c720a1, 0xf6c1d8c7, 0xba20c5bd, 0xc0e9b5d0, 0xedb020ba, 0xb920e2b1, 0x20f9c2dd, 0xadbce7bb, 0xbde5b520, 0x20edb0c3, 0xe9b8cfc7, 0x00000000}; /* EUC-KR+ASCII '.... .... ........ ...... .... .... .... ...... ....' */
uint32_t DAT_00553074[14] = {0xfcbac7b0, 0xbdadbf20, 0x20f7c8c9, 0xbcbccfc7, 0x2e2ee4bf, 0xbcd6c320, 0x20d1c7d2, 0xe7b7cfc7, 0x3220a1bf, 0xb0c3bd30, 0x20bac0a3, 0xbcbccfc7, 0x2e2ee4bf, 0x00000000}; /* EUC-KR+ASCII '.... ...... ........ ...... ...... 20...... ........' */
uint32_t DAT_00552ebc[4] = {0xb5bfeebf, 0x6b202d20, 0x6867696e, 0x00007374}; /* EUC-KR+ASCII '.... - knights' */
uint32_t DAT_00551e30[1] = {0x00000031}; /* ASCII '1' */
uint32_t DAT_00552fe4[6] = {0xa6c1f0be, 0xbf20aab3, 0x20c2b4f4, 0xa5b0a6c1, 0x2e2eccc0, 0x00002e2e}; /* EUC-KR+ASCII '...... .... ..........' */
uint32_t DAT_005535ac[1] = {0x00006f67}; /* ASCII 'go' */
uint32_t DAT_005530cc[8] = {0xa3b0f8bc, 0xb0f8bc20, 0x20a1bfa3, 0xb8c8c4c8, 0xb320a1b0, 0x20f6c1b2, 0xd4b0cabe, 0x00002e2e}; /* EUC-KR+ASCII '.... ...... ...... .... ......' */
uint32_t DAT_00553320[4] = {0x5f5e2876, 0x56292b5e, 0xc0eaba20, 0x00007ecc}; /* EUC-KR+ASCII 'v(^_^+)V ....~' */
uint32_t DAT_005535b8[2] = {0x74697571, 0x00000000}; /* ASCII 'quit' */
uint32_t DAT_005534cc[2] = {0x797a6f63, 0x00000000}; /* ASCII 'cozy' */
uint32_t DAT_00553330[7] = {0xafb8b3c4, 0xb520cdc5, 0xc0dac0f0, 0x20cab3cc, 0x616a202d, 0x6e6f7965, 0x00000067}; /* EUC-KR+ASCII '...... ........ - jaeyong' */
uint32_t DAT_00552218[1] = {0x00006277}; /* ASCII 'wb' */
uint32_t DAT_00553478[5] = {0xb9c8e2b1, 0x2d20dac0, 0x646e6520, 0x61657264, 0x0000006d}; /* EUC-KR+ASCII '...... - enddream' */
uint32_t PTR_DAT_005535c0[1] = {0x0079656b}; /* ASCII 'key' */
uint32_t DAT_005532fc[7] = {0xafb8b3c4, 0xb520cdc5, 0xc0dac0f0, 0x20cab3cc, 0x6179202d, 0x32676e6f, 0x00000000}; /* EUC-KR+ASCII '...... ........ - yaong2' */
uint32_t DAT_005534b4[6] = {0xe6b0e8b9, 0xc0f0b520, 0xb3ccc0da, 0x202d20ca, 0x797a6f63, 0x00000000}; /* EUC-KR+ASCII '.... ........ - cozy' */
uint32_t DAT_00552f4c[6] = {0xeebec4be, 0xedb0bbb3, 0xbae0c720, 0xc1d8c7b9, 0x7ee6b1f6, 0x0000007e}; /* EUC-KR+ASCII '........ ..........~~' */
uint32_t DAT_005531b4[11] = {0xbac0fec0, 0xc0c3bd20, 0x20a1bffd, 0xbac0d7c1, 0xb6e7bb20, 0xc0e9b5f7, 0xc6be20cc, 0xd9b4a7b8, 0xb020eebf, 0x2cbac0cd, 0x00000000}; /* EUC-KR+ASCII '.... ...... .... ........ ........ ....,' */
uint32_t DAT_005535cc[1] = {0x0000006d}; /* ASCII 'm' */
uint32_t DAT_005535f4[1] = {0x00002020}; /* ASCII '  ' */
uint32_t DAT_005534d4[13] = {0xdac0a5c8, 0xc720adbc, 0xbdedb0cf, 0xb0bac0cd, 0xcfc720c5, 0xadbce9b8, 0xb4e7bb20, 0xcdb020c2, 0xc020b5b5, 0xc0ccb9e7, 0xb0bbc0d6, 0xb0b020cd, 0x002ed9b4}; /* EUC-KR+ASCII '...... .......... ...... .... .... .......... .....' */
uint32_t DAT_00553440[14] = {0xb0a6c120, 0xc7b020a1, 0xeebfd9b9, 0xa6b8e5b5, 0xc0c3bd20, 0xb0cfc7db, 0x20c8b5d4, 0xafc0ccc0, 0xc520c2b4, 0xc0b8c5cf, 0xd4b020d3, 0xc8bed3c0, 0xadbca1bf, 0x00000000}; /* EUC-KR+ASCII ' .... .......... .......... ...... ...... ..........' */
uint32_t DAT_005535b0[2] = {0x74697865, 0x00000000}; /* ASCII 'exit' */
uint32_t DAT_005532e4[6] = {0xf0b8beb8, 0xc2b4babd, 0xb6eebe20, 0x20d4b0bb, 0xeebec9b0, 0x0000003f}; /* EUC-KR+ASCII '........ ...... ....?' */
uint32_t DAT_00553588[2] = {0x64756f6c, 0x00000000}; /* ASCII 'loud' */
uint32_t DAT_005535d8[1] = {0x0000f5bb}; /* EUC-KR+ASCII '..' */

/* The 16-byte key EncodeHandshakeBlock is called with in
 * CommP2POwner_ProcessPacket (&DAT_00551b7c); orig .data 0x551b7c =
 * 2c 45 92 6c f3 39 66 42 b6 70 d0 06 a1 fa 81 82 (the dword after it,
 * 0x13 at 0x551b8c, is a separate object).  It was a zero dword. */
uint32_t DAT_00551b7c[4] = {0x6c92452c, 0x426639f3, 0x06d070b6, 0x8281faa1};

/* ---- Hash-table prime lists (round 19) ----
 * HashMap_PickSize / IntMap_RemoveAll_14 / StringMap_RemoveAll_1c/_28 index four
 * identical 61-entry tables (17,23,29,37,41,53,...,0xcb2ff9, 0xffffffff end marker)
 * through (&DAT_x)[i] and &DAT_(x+4)[i]: the port had each as two unrelated zero
 * dwords, so every "pick a prime >= n" loop read zeros. The second name of each pair
 * is now an element-1 macro in globals.h. Values copied from orig .data. */
uint32_t DAT_00557660[61] = {0x11, 0x17, 0x1d, 0x25, 0x29, 0x35, 0x43, 0x53, 0x67, 0x83, 0xa3, 0xd3, 0x101, 0x14b, 0x199, 0x209, 0x287, 0x335, 0x407, 0x50b, 0x65b, 0x805, 0xa1f, 0xcb3, 0x1003, 0x142f, 0x1979, 0x2011, 0x285b, 0x32cf, 0x401b, 0x50b7, 0x65a1, 0x8003, 0xa153, 0xcb35, 0x10001, 0x1428b, 0x19661, 0x2001d, 0x28529, 0x32cc3, 0x40003, 0x50a2f, 0x65993, 0x80015, 0xa1453, 0xcb323, 0x100007, 0x1428b3, 0x19661f, 0x200011, 0x285151, 0x32cbff, 0x40000f, 0x50a28d, 0x659801, 0x800009, 0xa14521, 0xcb2ff9, 0xffffffff};
uint32_t DAT_00557850[62] = {0x11, 0x17, 0x1d, 0x25, 0x29, 0x35, 0x43, 0x53, 0x67, 0x83, 0xa3, 0xd3, 0x101, 0x14b, 0x199, 0x209, 0x287, 0x335, 0x407, 0x50b, 0x65b, 0x805, 0xa1f, 0xcb3, 0x1003, 0x142f, 0x1979, 0x2011, 0x285b, 0x32cf, 0x401b, 0x50b7, 0x65a1, 0x8003, 0xa153, 0xcb35, 0x10001, 0x1428b, 0x19661, 0x2001d, 0x28529, 0x32cc3, 0x40003, 0x50a2f, 0x65993, 0x80015, 0xa1453, 0xcb323, 0x100007, 0x1428b3, 0x19661f, 0x200011, 0x285151, 0x32cbff, 0x40000f, 0x50a28d, 0x659801, 0x800009, 0xa14521, 0xcb2ff9, 0xffffffff, 0x0};
uint32_t DAT_00557948[62] = {0x11, 0x17, 0x1d, 0x25, 0x29, 0x35, 0x43, 0x53, 0x67, 0x83, 0xa3, 0xd3, 0x101, 0x14b, 0x199, 0x209, 0x287, 0x335, 0x407, 0x50b, 0x65b, 0x805, 0xa1f, 0xcb3, 0x1003, 0x142f, 0x1979, 0x2011, 0x285b, 0x32cf, 0x401b, 0x50b7, 0x65a1, 0x8003, 0xa153, 0xcb35, 0x10001, 0x1428b, 0x19661, 0x2001d, 0x28529, 0x32cc3, 0x40003, 0x50a2f, 0x65993, 0x80015, 0xa1453, 0xcb323, 0x100007, 0x1428b3, 0x19661f, 0x200011, 0x285151, 0x32cbff, 0x40000f, 0x50a28d, 0x659801, 0x800009, 0xa14521, 0xcb2ff9, 0xffffffff, 0x0};
uint32_t DAT_00557a40[61] = {0x11, 0x17, 0x1d, 0x25, 0x29, 0x35, 0x43, 0x53, 0x67, 0x83, 0xa3, 0xd3, 0x101, 0x14b, 0x199, 0x209, 0x287, 0x335, 0x407, 0x50b, 0x65b, 0x805, 0xa1f, 0xcb3, 0x1003, 0x142f, 0x1979, 0x2011, 0x285b, 0x32cf, 0x401b, 0x50b7, 0x65a1, 0x8003, 0xa153, 0xcb35, 0x10001, 0x1428b, 0x19661, 0x2001d, 0x28529, 0x32cc3, 0x40003, 0x50a2f, 0x65993, 0x80015, 0xa1453, 0xcb323, 0x100007, 0x1428b3, 0x19661f, 0x200011, 0x285151, 0x32cbff, 0x40000f, 0x50a28d, 0x659801, 0x800009, 0xa14521, 0xcb2ff9, 0xffffffff};

/* The 11-dword table at 0x56d350 indexed by the room-size byte at
 * g_clientContext+0x44ef8 (ApplyRoomSettings divides a checksum by an entry:
 * `iVar3 % iVar1`, so the all-zero port table divided by zero).  Values are the
 * original's: 2,2,1,2,2,1,2,2,2,2,2 (the dwords after it are unrelated). */
uint32_t DAT_0056d350[11] = {2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2};

/* ---- The blast-effect filename pointer table at 0x56d290 (round 19) ----
 * 48 char* entries (3 rows of 16, row = effect family): SpawnBlastEffect /
 * SpawnPrimaryShot / FUN_00432320 read (&PTR_s_11blast_xes_0056d290)[row * 0x10 + col], and
 * SpawnMine / SpawnShot_Type13 read single slots by value.  The port had ten
 * separate NULL pointer cells (one per Ghidra label inside the table), so the
 * indexed reads ran off the first cell into whatever followed and the single
 * reads gave NULL.  The other nine names are slot macros in globals.h.  The
 * original entries point into a string pool at 0x55289c..0x5529b4 (repeats
 * share a string); string literals stand in for the pool. */
void *PTR_s_11blast_xes_0056d290[48] = {
    (void *)"11blast.xes",
    (void *)"22blast.xes",
    (void *)"31blast.xes",
    (void *)"42blast.xes",
    (void *)"51blast.xes",
    (void *)"62blast.xes",
    (void *)"71blast.xes",
    (void *)"82blast.xes",
    (void *)"91blast.xes",
    (void *)"101blast.xes",
    (void *)"111blast.xes",
    (void *)"121blast.xes",
    (void *)"132blast.xes",
    (void *)"142blast.xes",
    (void *)"151blast.xes",
    (void *)"91blast.xes",
    (void *)"12blast.xes",
    (void *)"22blast.xes",
    (void *)"32blast.xes",
    (void *)"42blast.xes",
    (void *)"52blast.xes",
    (void *)"62blast.xes",
    (void *)"72blast.xes",
    (void *)"82blast.xes",
    (void *)"92blast.xes",
    (void *)"101blast.xes",
    (void *)"112blast.xes",
    (void *)"121blast.xes",
    (void *)"132blast.xes",
    (void *)"142blast.xes",
    (void *)"151blast.xes",
    (void *)"22blast.xes",
    (void *)"12blast.xes",
    (void *)"22blast.xes",
    (void *)"31blast.xes",
    (void *)"42blast.xes",
    (void *)"51blast.xes",
    (void *)"62blast.xes",
    (void *)"72blast.xes",
    (void *)"82blast.xes",
    (void *)"92blast.xes",
    (void *)"101blast.xes",
    (void *)"112blast.xes",
    (void *)"121blast.xes",
    (void *)"11blast.xes",
    (void *)"142blast.xes",
    (void *)"151blast.xes",
    (void *)"23blast.xes"
};
