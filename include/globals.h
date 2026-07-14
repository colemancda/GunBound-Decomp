/* Global variable declarations for the raw-ported functions under
 * src/ (state_machine/, network/, rendering/, unnamed/, etc.).
 *
 * These are the DAT_<address>/_DAT_<address> globals and s_<name>_
 * <address> string-literal symbols Ghidra's decompiler references
 * directly. Numeric globals are typed from Ghidra's own inferred
 * type/size at each address - NOT hand-verified beyond that. Most are
 * almost certainly wrong at the semantic level (a `uint32_t` might
 * really be a signed int, a float bit-pattern, or a struct pointer) -
 * this just gets things declared and compiling. String literals ARE
 * their real extracted content (read directly from the binary's data
 * section), not placeholders. See src/README.md's "Global variables"
 * section for status and how these get promoted to real, well-typed
 * declarations as more of the binary gets understood.
 *
 * Ghidra sometimes references the same address under both `DAT_<addr>`
 * and `_DAT_<addr>` names (its convention for "the same memory
 * accessed at two different sizes/interpretations" - e.g. a struct's
 * base address vs. one of its fields at a nonzero offset happening to
 * coincide, or a wider vs. narrower read of the same bytes). Both
 * names are aliased to the same storage via #define since C can't
 * give one object two names with different types; the alias loses
 * that size/type distinction, which is a known simplification, not a
 * bug.
 */
#ifndef GB_GLOBALS_H
#define GB_GLOBALS_H

#include <stdint.h>

/* --- Named, documented globals (ARCHITECTURE.md) ---
 *
 * DirectDraw7/Direct3D7 COM interface pointers are declared `void *`
 * rather than their real IDirectDraw7 / IDirect3DDevice7 / etc. types -
 * this tree doesn't have the DirectX 7 COM interface definitions wired
 * in yet (a separate undertaking: either real d3d.h/ddraw.h headers or
 * hand-written vtable structs matching the confirmed vtable-offset
 * calls documented throughout ARCHITECTURE.md's rendering section).
 * Every raw-ported call site that uses one of these already casts
 * through `(**(code **)(*ptr + offset))(...)`-style vtable dispatch
 * anyway, which doesn't need the real type to compile - just to be
 * type-checked, which isn't happening yet either way. */
extern int32_t g_currentGameState;
extern int32_t g_pendingGameState;
/* char *, not void *: same reasoning as g_pD3DDevice7 and friends
 * below - call sites add byte offsets to a looked-up element
 * (`g_gameStateVTableArray[N] + offset`), which needs a complete,
 * byte-sized pointer type to be valid standard C (not just a gcc/
 * clang void* arithmetic extension) - found via a real-MSVC compile
 * sweep of src/state_machine/. */
extern char *g_gameStateVTableArray[16];
#define g_gameStateObjects g_gameStateVTableArray
extern void *g_hDDrawDll;
/* char ** rather than void **: raw-ported call sites dereference these
 * once and then add a byte offset to reach a vtable slot
 * (`*g_pD3DDevice7 + offset`), so they need to be a pointer-to-pointer
 * to compile at all (a plain void* can't be dereferenced), and the
 * dereferenced value needs to be a complete, byte-sized pointer type
 * for the `+ offset` to be valid, portable pointer arithmetic. `void*`
 * satisfied gcc/clang (which treat void* arithmetic as a nonstandard
 * "sizeof(void)==1" extension) but is a hard error under real MSVC
 * ("'void *': unknown size") - found via a real-MSVC compile sweep of
 * src/state_machine/. `char*` has the same one-byte-per-step
 * arithmetic gcc's extension gave us, but is valid standard C under
 * both compilers. */
extern char **g_pBackBufferSurface;
extern char **g_pClipper;
extern char **g_pD3DDevice7;
extern char **g_pDirect3D7;
extern char **g_pDirectDraw7;
extern char **g_pPrimarySurface;
extern char **g_pZBufferSurface;
extern uint8_t g_abBroadcastEventBuffer;
extern uint32_t g_dwBroadcastEventCursor;
extern uint8_t g_replayFileHandle;
extern float g_sineTable360[360];
extern uint8_t g_spriteVertexBuffer[0x10000];
extern uint32_t g_spriteVertexCount;
extern uint32_t g_stateChangeInProgress;
extern uint8_t g_stateChangeRequested;

/* --- Generic globals (unnamed, type inferred from Ghidra only) --- */

/* Ghidra's symbol for the PE image base (the DOS header at 0x400000).
 * Only its *address* is ever used (pointer comparisons against the
 * image base), so a one-byte marker object is enough - Ghidra's real
 * IMAGE_DOS_HEADER type isn't needed, keeping this header free of
 * windows.h dependencies. */
extern uint8_t IMAGE_DOS_HEADER_00400000;

extern uint8_t DAT_0054b420;
extern uint8_t DAT_0054b438;
extern uint32_t DAT_0054cb00;
extern uint8_t DAT_0054cb78;
extern uint8_t DAT_0054cf78;
extern uint8_t DAT_0054d378;
extern uint8_t DAT_0054d778;
extern uint8_t DAT_0054db78;
extern uint8_t DAT_0054df78;
extern uint8_t DAT_0054e378;
extern uint8_t DAT_0054e778;
extern uint8_t DAT_0054eb78;
extern uint8_t DAT_0054ef78;
extern void * DAT_0054f378;
#define _DAT_0054f378 DAT_0054f378
extern uint8_t DAT_0054f778;
extern uint8_t DAT_0054fb78;
extern uint8_t DAT_0054ff78;
extern uint8_t DAT_00550778;
extern uint8_t DAT_00550b78;
extern uint8_t DAT_00550f78;
extern uint8_t DAT_00551378;
extern uint8_t DAT_00551778;
extern uint32_t DAT_00551cac;
extern uint8_t DAT_00551cb0;
extern uint8_t DAT_00551cb1;
#define _DAT_00551cb1 DAT_00551cb1
extern uint8_t DAT_00551e24;
extern uint16_t DAT_00551e34;
extern uint8_t DAT_00551e36;
extern uint8_t DAT_00551e78;
extern void * DAT_00551ecc;
#define _DAT_00551ecc DAT_00551ecc
extern uint8_t DAT_0055207c;
extern uint8_t DAT_00552084;
extern uint8_t DAT_00552218;
extern uint8_t DAT_00552728;
extern uint8_t DAT_0055275c;
extern void * DAT_00552788;
#define _DAT_00552788 DAT_00552788
extern uint8_t DAT_00552890;
extern uint8_t DAT_00552898;
extern uint32_t DAT_00552c70;
extern uint8_t DAT_00552c74;
extern uint16_t DAT_00552c78;
extern uint8_t DAT_00552c7a;
extern uint16_t DAT_00552c7c;
extern uint16_t DAT_00552c80;
extern uint8_t DAT_00552d38;
extern uint8_t DAT_00552d60;
extern uint8_t DAT_00552d94;
extern uint8_t DAT_00552db4;
extern uint8_t DAT_00552de4;
extern uint8_t DAT_00552e14;
extern uint8_t DAT_00552e24;
extern uint8_t DAT_00552e30;
extern uint8_t DAT_00552e68;
extern uint8_t DAT_00552e90;
extern uint8_t DAT_00552ea4;
extern uint8_t DAT_00552ebc;
extern uint8_t DAT_00552ed4;
extern uint8_t DAT_00552ef0;
extern uint8_t DAT_00552f1c;
extern uint8_t DAT_00552f34;
extern uint8_t DAT_00552f4c;
extern uint8_t DAT_00552f64;
extern uint8_t DAT_00552f90;
extern uint8_t DAT_00552fac;
extern uint8_t DAT_00552fc8;
extern uint8_t DAT_00552fe4;
extern uint8_t DAT_00552ffc;
extern uint8_t DAT_00553018;
extern uint8_t DAT_0055303c;
extern uint8_t DAT_00553074;
extern uint8_t DAT_005530ac;
extern uint8_t DAT_005530cc;
extern uint8_t DAT_005530ec;
extern uint8_t DAT_0055310c;
extern uint8_t DAT_00553148;
extern uint8_t DAT_00553188;
extern uint8_t DAT_005531b4;
extern uint8_t DAT_005531e0;
extern uint8_t DAT_00553200;
extern uint8_t DAT_00553258;
extern uint8_t DAT_0055328c;
extern uint8_t DAT_005532bc;
extern uint8_t DAT_005532e4;
extern uint8_t DAT_005532fc;
extern uint8_t DAT_00553320;
extern uint8_t DAT_00553330;
extern uint8_t DAT_00553354;
extern uint8_t DAT_00553370;
extern uint8_t DAT_00553390;
extern uint8_t DAT_005533b0;
extern uint8_t DAT_005533d0;
extern uint8_t DAT_00553404;
extern uint8_t DAT_00553440;
extern uint8_t DAT_00553478;
extern uint8_t DAT_005534b4;
extern uint8_t DAT_005534cc;
extern uint8_t DAT_005534d4;
extern uint8_t DAT_00553508;
extern uint8_t DAT_00553554;
extern uint8_t DAT_00553570;
extern uint8_t DAT_00553588;
extern uint8_t DAT_005535a4;
extern uint8_t DAT_005535ac;
extern uint8_t DAT_005535b0;
extern uint8_t DAT_005535b8;
extern void * DAT_005535c0;
#define _DAT_005535c0 DAT_005535c0
extern uint8_t DAT_005535c4;
extern uint8_t DAT_005535cc;
extern uint8_t DAT_005535d8;
extern uint8_t DAT_005535dc;
extern uint8_t DAT_005535e8;
extern uint16_t DAT_005535f0;
extern uint8_t DAT_005535f4;
extern uint16_t DAT_00553620;
extern uint16_t DAT_00553624;
extern uint8_t DAT_00553626;
extern uint32_t DAT_00553628;
extern uint8_t DAT_00553648;
extern uint32_t DAT_00553b68;
extern uint16_t DAT_00553b6c;
extern uint32_t DAT_00553b70;
extern uint16_t DAT_00553b74;
extern uint8_t DAT_00553b88;
extern uint8_t DAT_00553bcc;
extern uint8_t DAT_00553f90;
extern uint8_t DAT_00554060;
extern uint32_t DAT_005554f8;
extern uint8_t DAT_005554fc;
extern void * DAT_00555500;
#define _DAT_00555500 DAT_00555500
extern uint16_t DAT_00555a14;
extern uint8_t DAT_00555a16;
extern uint16_t DAT_00555a18;
extern uint8_t DAT_00555a1a;
extern uint8_t DAT_00555c90;
extern uint8_t DAT_00556770;
extern uint32_t DAT_00556ae0;
extern uint16_t DAT_00556ae4;
extern uint8_t DAT_00557234;
extern uint32_t DAT_00557258;
extern uint8_t DAT_0055725c;
extern GUID DAT_005573c8; /* IID_IDirectInput8A - see globals.c */
extern uint16_t DAT_0055751c;
extern uint32_t DAT_00557554;
extern uint8_t DAT_00557558;
extern uint32_t DAT_00557850;
extern uint32_t DAT_00557854;
extern uint8_t DAT_00557fb0;
#define _DAT_00557fb0 DAT_00557fb0
extern uint8_t DAT_00557fb4;
#define _DAT_00557fb4 DAT_00557fb4
extern uint8_t DAT_00557fb8;
#define _DAT_00557fb8 DAT_00557fb8
extern uint8_t DAT_00557fbc;
#define _DAT_00557fbc DAT_00557fbc
extern uint8_t DAT_00557fc0;
#define _DAT_00557fc0 DAT_00557fc0
extern uint8_t DAT_00557fc4;
#define _DAT_00557fc4 DAT_00557fc4
extern uint8_t DAT_00557fc8;
#define _DAT_00557fc8 DAT_00557fc8
extern uint8_t DAT_00557fcc;
#define _DAT_00557fcc DAT_00557fcc
extern uint8_t DAT_00557fd0;
#define _DAT_00557fd0 DAT_00557fd0
extern uint8_t DAT_00557fd4;
#define _DAT_00557fd4 DAT_00557fd4
extern uint8_t DAT_00557fec;
#define _DAT_00557fec DAT_00557fec
extern uint8_t DAT_00557ff0;
#define _DAT_00557ff0 DAT_00557ff0
extern uint8_t DAT_00557ff4;
#define _DAT_00557ff4 DAT_00557ff4
extern uint8_t DAT_00557ff8;
#define _DAT_00557ff8 DAT_00557ff8
extern uint8_t DAT_00557ffc;
#define _DAT_00557ffc DAT_00557ffc
extern uint8_t DAT_00558000;
#define _DAT_00558000 DAT_00558000
extern uint8_t DAT_00558004;
#define _DAT_00558004 DAT_00558004
extern uint8_t DAT_00558008;
#define _DAT_00558008 DAT_00558008
extern uint8_t DAT_0055800c;
#define _DAT_0055800c DAT_0055800c
extern uint8_t DAT_00558010;
#define _DAT_00558010 DAT_00558010
extern uint8_t DAT_0055801c;
#define _DAT_0055801c DAT_0055801c
extern uint8_t DAT_00558020;
#define _DAT_00558020 DAT_00558020
extern uint8_t DAT_00558028;
#define _DAT_00558028 DAT_00558028
extern uint8_t DAT_0055802c;
#define _DAT_0055802c DAT_0055802c
extern uint8_t DAT_00558030;
#define _DAT_00558030 DAT_00558030
extern uint8_t DAT_00558034;
#define _DAT_00558034 DAT_00558034
extern uint8_t DAT_00558038;
#define _DAT_00558038 DAT_00558038
extern uint8_t DAT_0055803c;
#define _DAT_0055803c DAT_0055803c
extern uint8_t DAT_00558040;
#define _DAT_00558040 DAT_00558040
extern uint8_t DAT_00558054;
#define _DAT_00558054 DAT_00558054
extern uint8_t DAT_00558064;
#define _DAT_00558064 DAT_00558064
extern uint8_t DAT_005583e8;
extern uint8_t DAT_0055841c;
extern uint8_t DAT_00558458;
extern uint8_t DAT_00569e10;
extern uint8_t DAT_00569e2c;
extern uint8_t DAT_00569e48;
extern uint8_t DAT_00569e68;
extern uint32_t DAT_0056d108;
/* g_cursorAnchorX / g_cursorAnchorY (were DAT_0056d10c / DAT_0056d110) - the
 * on-screen cursor position: where GameTick blits the cursor sprite, and the
 * SetCursorPos snap-back anchor for FPS-style relative mouse. Maintained by
 * WndProc mouse handling. See ARCHITECTURE.md "custom cursor". */
extern uint32_t g_cursorAnchorX;
extern uint32_t g_cursorAnchorY;
extern uint32_t DAT_0056d118;
extern uint8_t DAT_0056d350;
extern uint32_t DAT_0056d3d8;
extern uint32_t DAT_0056d3dc;
extern uint8_t DAT_0056d3e0;
extern uint8_t DAT_0056d400;
extern uint8_t DAT_0056d440;
extern void * DAT_0056d460;
#define _DAT_0056d460 DAT_0056d460
extern uint32_t DAT_0056dbe8;
extern uint8_t DAT_0056dbf0;
extern uint8_t DAT_0056dc30;
extern uint16_t g_awItemIconTable[40];
extern uint8_t DAT_0056dc90;
#define _DAT_0056dc90 DAT_0056dc90
extern uint8_t DAT_0056dc95;
extern uint8_t DAT_0056dc97;
extern uint8_t DAT_0056dc98;
#define _DAT_0056dc98 DAT_0056dc98
extern uint8_t DAT_0056dc9a;
extern uint8_t DAT_0056dca0;
#define _DAT_0056dca0 DAT_0056dca0
extern uint8_t DAT_0056dca5;
extern uint8_t DAT_0056dca7;
extern uint8_t DAT_0056dca8;
#define _DAT_0056dca8 DAT_0056dca8
extern uint8_t DAT_0056dcaa;
extern uint8_t DAT_0056dd30;
extern uint8_t DAT_0056de30;
extern uint32_t DAT_0056df30;
extern uint32_t DAT_0056df34;
extern uint16_t DAT_00588f38;
#define _DAT_00588f38 DAT_00588f38
extern uint32_t DAT_00588f3c;
extern uint16_t DAT_00588f40;
extern uint32_t DAT_00588f44;
extern uint32_t DAT_00588f48;
extern uint8_t DAT_00588f4c;
extern float DAT_00588f50;
#define _DAT_00588f50 DAT_00588f50
extern float DAT_00588f54;
#define _DAT_00588f54 DAT_00588f54
extern uint32_t DAT_00588f60;
extern uint8_t DAT_00588f64;
extern void * DAT_0058b248;
#define _DAT_0058b248 DAT_0058b248
extern uint8_t DAT_0058b8d6;
/* Missing from the original scan (see src/README.md's "Global
 * variables" section for the known ~1159-address gap this was pulled
 * from) - added by hand since it was blocking FUN_0041eb80.c. */
extern uint8_t DAT_0058bb04;
extern uint8_t DAT_005a9068;
extern uint8_t DAT_005a9084;
extern uint32_t DAT_005b1444; /* ATL::CAtlStringMgr* singleton (holds the vtable ptr value) - see globals.c */
extern uint32_t DAT_005b15ac;
extern int *DAT_005b1c48; /* used dereferenced/indexed at call sites (FUN_0040c6f0) */
/* g_edgeCursors (was DAT_005b1c4c..DAT_005b1c6c) - a 9-element HCURSOR array
 * for the custom cursor: index 0 = normal, 1-8 = the eight screen-edge
 * directions. Selected by g_cursorDirection and applied via SetCursor on
 * WM_SETCURSOR (WndProc) and per-tick in-battle (the edge-scroll logic in
 * State11 slot 9). Loaded in an as-yet-unported cursor init. */
extern uint32_t g_edgeCursors[9];
extern uint8_t DAT_005b1c70;
extern uint8_t DAT_005b1cf0;
extern uint8_t DAT_005b1d70[0x160]; /* text-render/RLE scratch buffer - sized, see globals.c */
extern uint8_t DAT_005b1ed0;
extern uint8_t DAT_005b22d0;
extern uint8_t DAT_005b26d0;
extern uint8_t DAT_005b2ad0;
extern uint8_t DAT_005b2b50;
extern uint32_t DAT_005b2b54;
extern uint32_t DAT_005b2b58;
extern uint32_t DAT_005b2b5c;
extern uint32_t DAT_005b2b60;
extern uint32_t DAT_005b2b64;
extern uint32_t DAT_005b2b68;
extern uint8_t DAT_005b2f68;
extern uint8_t DAT_005b3368;
extern uint16_t DAT_005b33e8;
extern uint32_t DAT_005b33f0;
extern uint16_t DAT_005b33f4;
extern uint32_t DAT_005b3438;
extern uint16_t DAT_005b343c;
extern uint8_t DAT_005b3440;
extern uint32_t DAT_005b3480;
/* g_clientContext (was DAT_005b3484) - base ADDRESS of the main client
 * context arena: a ~1 MB block (offsets run past 0xeb000) constructed by
 * FUN_00415d40. Holds, among much else: the outgoing packet buffer
 * (+0x4d0 / length cursor +0x44d0), Winsock socket handles (+0x84e0),
 * critical sections, room/player/whisper state, and the server-list
 * structure-of-arrays populated by opcode 0x1102 (16-entry parallel arrays
 * starting at +0x3f808: count, onlineFlag, serverId, regionOrType, name,
 * desc, serverIp, port, currentPlayers, maxCapacity - see PROTOCOL.md).
 * Held as a uint32_t (raw address); call sites do `base + fixed_offset`.
 * There appear to be two such arenas double-buffered via DAT_007934ec /
 * DAT_007934e8 (swapped on server change); this handle tracks the active
 * one. Name is a defensible role label, not a verified original symbol. */
extern uint32_t g_clientContext;
extern uint32_t DAT_005b3488;
extern uint32_t DAT_005b3620;
extern uint8_t DAT_005b3628;
extern uint8_t DAT_005f2f38;
extern uint8_t DAT_005f2f3c;
extern uint8_t DAT_005f2f40;
extern uint8_t DAT_005f2f4c;
extern uint8_t DAT_005f2f50;
extern uint8_t DAT_005f2f58;
extern uint8_t DAT_005f3058;
extern uint8_t DAT_005f3158;
extern uint8_t DAT_005f3258;
extern uint8_t DAT_005f325c;
extern uint8_t DAT_005f32dc;
extern uint8_t DAT_005f375c;
extern uint8_t DAT_005f3760;
extern uint8_t DAT_005f3768;
extern uint8_t DAT_005f376c;
extern uint8_t DAT_005f3770;
extern uint8_t DAT_005f3771;
extern uint8_t DAT_005f3772;
extern uint8_t DAT_005f4894;
extern uint8_t DAT_00666d73;
extern uint8_t DAT_00673628;
extern int *DAT_00674f68; /* used dereferenced as a vtable-bearing ptr at call sites */
/* RECT{left,top,right,bottom} for PresentFrame's Blt - was 4 separate
 * uint8_t globals (DAT_006773b4/b8/bc/c0) with no guaranteed contiguous
 * layout; unified 2026-07-14, see globals.c/InitDirectDraw.c/PresentFrame.c */
extern int32_t g_presentDstRect[4];
extern uint32_t DAT_00677544[8]; /* DDPIXELFORMAT - see globals.c */
extern uint32_t DAT_006777e8[8]; /* DDPIXELFORMAT - see globals.c */
extern uint32_t DAT_006790c0[0x8000];
extern uint8_t DAT_0067e348;
extern uint8_t DAT_0067e3c8;
extern uint8_t DAT_0067e3cc;
extern uint8_t DAT_0067e3cd;
extern uint8_t DAT_0067e3ce;
extern uint8_t DAT_0067e3d0;
extern uint8_t DAT_0067e5f4;
extern uint8_t DAT_0067ec60;
extern uint8_t DAT_0067ec64;
extern uint8_t DAT_0067ec68;
extern uint8_t DAT_0067ec70;
extern uint8_t DAT_0067ec74;
extern uint32_t DAT_006990c0[0x8000];
extern uint8_t DAT_0069ec74;
extern uint8_t DAT_006a647c;
extern uint8_t DAT_006a6481;
extern uint8_t DAT_006a64a4;
extern uint8_t DAT_006a64a8;
extern uint8_t DAT_006a64ac;
extern uint8_t DAT_006a64b0;
extern uint8_t DAT_006a64b4;
extern uint8_t DAT_006a64b8;
extern uint8_t DAT_006a64bc;
extern uint8_t DAT_006a64c0;
extern uint8_t DAT_006a73c0;
extern uint8_t DAT_006a73c8;
extern uint8_t DAT_006a7670;
extern uint8_t DAT_006a76f4;
extern uint8_t DAT_006a76f8;
extern uint8_t DAT_006a76fc;
extern uint8_t DAT_006a7704;
extern uint8_t DAT_006a7708;
extern int32_t g_nCameraX;
extern int32_t g_nCameraY;
extern int32_t g_nCameraScrollX;
extern int32_t g_nCameraScrollY;
extern int32_t g_nCameraBoundX;
extern int32_t g_nCameraBoundY;
extern uint8_t DAT_006a773c;
extern uint8_t DAT_006a7740;
extern uint8_t DAT_006a7758;
extern uint8_t DAT_006a7f70;
extern uint8_t DAT_006a7f88;
extern uint8_t DAT_006a7f8c;
extern uint8_t DAT_006a7f90;
extern uint8_t DAT_006a7f91;
extern uint8_t DAT_006a7f92;
extern uint8_t DAT_006a81b8;
extern uint8_t DAT_006a8e90;
extern uint8_t DAT_006a9b6c;
extern uint8_t DAT_006a9b6d;
extern uint8_t DAT_006a9b6e;
extern uint8_t DAT_006a9b6f;
extern uint8_t DAT_006a9b70;
extern uint8_t DAT_006a9b71;
extern uint8_t DAT_006a9b72;
extern uint8_t DAT_006a9b73;
extern uint8_t DAT_006a9b74;
extern uint8_t DAT_006aa408;
extern uint8_t DAT_006aa41c;
extern uint8_t DAT_006aa424;
extern uint8_t DAT_006aa44c;
extern uint8_t DAT_006aa47b;
extern uint8_t DAT_006aa47c;
extern uint8_t DAT_006aa5fc;
extern uint8_t DAT_006aa600;
extern uint8_t DAT_006aa624;
extern uint8_t DAT_006aa625;
extern uint8_t DAT_006aa626;
extern uint8_t DAT_006aa627;
extern uint8_t DAT_006aa628;
extern uint8_t DAT_006aa629;
extern uint8_t DAT_006aa62a;
extern uint8_t DAT_006aa62b;
extern uint8_t DAT_006aa62c;
extern uint8_t DAT_006aa62d;
extern uint8_t DAT_006aa658;
extern uint8_t DAT_006aa660;
extern uint8_t DAT_006aa662;
extern uint8_t DAT_006aa664;
extern uint8_t DAT_006aa666;
extern uint8_t DAT_006aa668;
extern uint8_t DAT_006aa66a;
extern uint8_t DAT_006aa66e;
extern uint8_t DAT_006aa674;
extern uint8_t DAT_006aa67c;
extern uint8_t DAT_006aab04;
extern uint32_t DAT_006b90f8;
#define _DAT_006b90f8 DAT_006b90f8
extern uint32_t DAT_006b9100[0x400];
extern uint8_t DAT_006ba1fc;
extern uint8_t DAT_006ba244;
extern uint32_t DAT_00792190;
extern uint8_t DAT_00792194;
#define _DAT_00792194 DAT_00792194
extern uint8_t DAT_00792198;
#define _DAT_00792198 DAT_00792198
extern uint32_t DAT_007921b0[0x400];
extern uint16_t DAT_00793228;
extern uint8_t DAT_007933b8;
extern uint32_t DAT_007933bc;
extern uint32_t DAT_007933c0;
extern uint8_t DAT_007934c4;
extern uint32_t DAT_007934c8;
extern uint8_t DAT_007934cc;
extern uint8_t DAT_007934d8;
#define _DAT_007934d8 DAT_007934d8
extern uint32_t DAT_007934e0;
extern uint32_t DAT_007934e4;
extern uint32_t DAT_007934e8;
extern uint32_t DAT_007934ec;
extern uint32_t DAT_007934f0;
extern uint32_t DAT_007934f4;
extern uint8_t DAT_007934f8;
extern uint32_t DAT_007934fc;
extern uint32_t DAT_00793500;
/* g_frameCounter (was DAT_00793504) - running elapsed-frame counter, advanced
 * by GameTick each tick (`+= framesElapsed`). Drives frame-timed animation,
 * e.g. the replay cursor blink (`g_frameCounter % 0x14 < 10`). */
extern uint32_t g_frameCounter;
extern uint8_t DAT_0079350c;
extern uint8_t DAT_0079350d;
extern uint32_t g_cursorDirection;
/* g_valueGuardTamperFlag (was DAT_00793514) - sticky "value tampering
 * detected" flag for the anti-cheat value guard. Gameplay-critical values are
 * stored as (a,b,check) triples validated as check==(a+b-0x34)&0xff; any peek/
 * encode whose checksum fails sets this to 1. Set across the guard subsystem
 * (PeekPacketChecksumState, EncodeOutgoingPacketField, the FUN_00406xxx
 * cluster) and read by GameTick. */
extern uint8_t g_valueGuardTamperFlag;
extern uint8_t DAT_00793515;
extern uint8_t DAT_00793516;
extern uint8_t DAT_00793517;
extern uint8_t DAT_00793518;
#define _DAT_00793518 DAT_00793518
extern uint8_t DAT_0079351c;
#define _DAT_0079351c DAT_0079351c
extern uint8_t DAT_00793520;
extern uint8_t DAT_00793521;
extern uint8_t g_bBattleSessionActive;
extern uint8_t DAT_00793529;
extern uint8_t DAT_0079352a;
extern uint32_t DAT_0079352c;
extern uint32_t DAT_00793530;
extern uint32_t DAT_00793534;
extern uint32_t DAT_00793544;
extern uint8_t DAT_00793549;
extern uint8_t DAT_0079354a;
extern uint8_t DAT_0079354b;
extern int *DAT_0079354c; /* used dereferenced as a vtable-bearing ptr at call sites */
extern int *DAT_00793550; /* used dereferenced as a vtable-bearing ptr at call sites */
extern void **DAT_00793554; /* heap array of channel object ptrs: allocated
                             * (operator_new) and freed in InitDirectSound /
                             * FUN_004ee850, indexed by InitGame and others -
                             * a pointer, not a fixed [16] array */
extern int *DAT_00793558; /* used dereferenced as a vtable-bearing ptr at call sites */
extern uint32_t DAT_0079355c;
extern uint32_t DAT_00793560;
extern uint8_t DAT_00793568;
extern uint32_t DAT_007935e8;
extern uint32_t DAT_007935ec;
extern uint8_t DAT_00793610;
extern uint8_t DAT_00793611;
/* g_currentBlendMode (was DAT_00793614) - cached D3D7 alpha-blend mode, so the
 * sprite render paths only re-issue SetRenderState(SRCBLEND/DESTBLEND) on a
 * change. 1 = normal alpha (SRCALPHA/INVSRCALPHA), 2 = additive glow
 * (SRCALPHA/ONE); mirrored by _DAT_00792194. */
extern uint32_t g_currentBlendMode;
extern uint8_t DAT_00793618;
#define _DAT_00793618 DAT_00793618
extern uint32_t DAT_00793634;
extern uint32_t DAT_00793640;
extern uint32_t DAT_0079364c;
/* g_frameTriangleCounter (was DAT_0079365c) - per-frame primitive counter, a
 * rendering stat. Reset to 0 once per frame in GameTick, then incremented by
 * g_spriteVertexCount just before every batched DrawPrimitive flush. */
extern uint32_t g_frameTriangleCounter;
extern uint32_t DAT_00793660;
extern uint8_t DAT_00793664;
extern uint32_t DAT_0079376c;
extern uint8_t DAT_00793770;
extern int *DAT_00793774; /* used dereferenced as a pointer at call sites */
extern uint32_t DAT_00793778;
extern uint32_t DAT_00793798;
extern uint32_t DAT_0079379c;
extern uint8_t DAT_007937a0;
extern uint8_t DAT_00793fa0;
extern uint8_t DAT_00794bf0;
extern uint8_t DAT_00794e14;
extern uint32_t DAT_00795070;
extern uint32_t DAT_00795074;
extern uint8_t DAT_00795078;
extern uint8_t DAT_00795878;
extern uint8_t DAT_00796078;
extern uint8_t DAT_00796878;
extern uint8_t DAT_00796aa0;
/* g_localizedStringTable (was DAT_00796eec) - the localized UI-string map,
 * an id -> string table built once by LoadLocalizedStrings from the
 * "Language.txt" entry in graphics.xfs, then read by GetLocalizedString.
 * All dialog/message text (error popups, MessageBoxA prompts) is looked up
 * here by numeric id. Its address (&g_localizedStringTable) is what both
 * functions take as the table handle. See ARCHITECTURE.md "Text
 * localization". */
extern uint8_t g_localizedStringTable;
/* g_cursorTexture (was DAT_007a7660) - actually field +0x1c of the animated-
 * cursor object at 0x7a7644: the cursor's anim descriptor, set by
 * FindPreloadedTextureByName("cursor") in ChangeGameState and read every tick
 * by AdvanceSpriteAnimation (as [obj+0x1c]). NOT write-only - only the store
 * is absolute; the reads are object-relative. See ARCHITECTURE.md "custom
 * cursor". */
extern uint8_t g_cursorTexture;
/* g_cursorFrame (was DAT_007a7674) - the current cursor sprite frame that
 * GameTick's draw passes to FindSpriteFrame/BlitSpriteClipped. It is field
 * +0x30 of the animated-cursor object at 0x7a7644, so AdvanceSpriteAnimation
 * writes it each tick as [obj+0x30] (no absolute reference to 0x7a7674 - which
 * is why a byte search saw only the read). CONFIRMED on the live client to
 * cycle 0..16 -> 0 each frame (a ~17-step keyframe cursor animation); it is
 * NOT a constant. See ARCHITECTURE.md "custom cursor". */
extern uint32_t g_cursorFrame;
extern uint8_t DAT_007a767c[0x10]; /* worker-thread control block - see globals.c */
extern uint8_t DAT_007a768c;
extern uint8_t DAT_00d9aa20;
extern uint8_t DAT_00d9aa24;
extern uint8_t DAT_00d9aa28;
extern uint8_t DAT_00d9aa2c;
extern uint8_t DAT_00d9aa30;
extern uint8_t DAT_00d9aa34;
extern uint8_t DAT_00d9aa35;
extern uint8_t DAT_00e525e8;
extern int *DAT_00e52814; /* used dereferenced as a vtable-bearing ptr at call sites */
extern uint32_t DAT_00e52838;
extern uint32_t DAT_00e5283c;
extern uint8_t DAT_00e52858;
extern uint8_t DAT_00e52859;
extern uint8_t DAT_00e5285a;
extern uint8_t DAT_00e5285b;
extern uint8_t DAT_00e5285c;
#define _DAT_00e5285c DAT_00e5285c
extern uint8_t DAT_00e52864;
extern uint8_t DAT_00e52868;
extern uint8_t DAT_00e52e68;
extern int *DAT_00e5369c; /* used dereferenced as a vtable-bearing ptr at call sites */
extern uint32_t DAT_00e536c0;
extern uint32_t DAT_00e536c4;
extern uint8_t DAT_00e536e4;
#define _DAT_00e536e4 DAT_00e536e4
extern uint8_t DAT_00e536ec;
/* Zeroed backing for GameTick's per-tick input/cursor timer blocks (mouse
 * 0xe53698, keyboard 0xe52810, cursor-anim 0x7a7644) - the DirectInput device
 * singletons are bring-up-stubbed and never constructed; see globals.c. */
extern uint8_t g_mouseDeviceTimerBlock[0x88];
extern uint8_t g_keyboardDeviceTimerBlock[0x658];
extern uint8_t g_softwareCursorAnimBlock[0x38];
extern uint8_t DAT_00e53c24;
#define _DAT_00e53c24 DAT_00e53c24
extern uint8_t DAT_00e53c28;
#define _DAT_00e53c28 DAT_00e53c28
extern uint8_t DAT_00e53c2c;
#define _DAT_00e53c2c DAT_00e53c2c
extern uint8_t DAT_00e53c30;
#define _DAT_00e53c30 DAT_00e53c30
extern uint8_t DAT_00e53c3c;
/* g_uiPanelManager (was DAT_00e53c40) - the global UI panel/dialog container
 * that screens attach dynamic panels to. Passed by address to the panel
 * builders/closers (BuildWorldListPanel, the lobby buddy panel BuildBuddyPanel,
 * the Create Room dialog BuildCreateRoomDialog, PanelManager_Unregister close, etc.). Typed
 * uint8_t by Ghidra but is really a container object; kept as-is until the
 * class is modeled. */
extern uint8_t g_uiPanelManager[16]; /* sized to real storage - see globals.c */
extern uint32_t DAT_00e53c44;
extern uint32_t DAT_00e53c48;
extern uint8_t DAT_00e53e88;
extern uint8_t DAT_00e55a45;
extern uint8_t DAT_00e55a46;
extern int *DAT_00e55a64; /* used dereferenced as a vtable-bearing ptr at call sites */
extern uint8_t DAT_00e55ab8;
extern uint8_t DAT_00e55ce0;
extern uint32_t DAT_00e55ce8;
extern uint32_t DAT_00e55cf4;
extern uint8_t DAT_00e55d58;
extern uint8_t DAT_00e55e18;
#define _DAT_00e55e18 DAT_00e55e18
extern uint8_t DAT_00e55e1c;
#define _DAT_00e55e1c DAT_00e55e1c
extern uint32_t DAT_00e55e20;
extern uint8_t DAT_00e55e28;
#define _DAT_00e55e28 DAT_00e55e28
extern uint8_t DAT_00e55e3c;
extern uint8_t DAT_00e560a0;
#define _DAT_00e560a0 DAT_00e560a0
extern uint8_t DAT_00e560a4;
#define _DAT_00e560a4 DAT_00e560a4
extern uint8_t DAT_00e560a8;
#define _DAT_00e560a8 DAT_00e560a8
extern uint8_t DAT_00e560ac;
#define _DAT_00e560ac DAT_00e560ac
extern uint8_t DAT_00e98ab8;
extern uint8_t DAT_00e98abc;
#define _DAT_00e98abc DAT_00e98abc
extern uint32_t DAT_00e98ac0;
extern uint8_t DAT_00e9aac0;
extern uint8_t DAT_00e9aac4;
#define _DAT_00e9aac4 DAT_00e9aac4
extern uint8_t DAT_00e9aac8;
#define _DAT_00e9aac8 DAT_00e9aac8
extern uint8_t DAT_00e9aacd;
extern uint8_t DAT_00e9aace;
extern uint8_t DAT_00e9aad0;
extern uint8_t DAT_00e9aad1;
extern uint8_t DAT_00e9aad2;
extern uint8_t DAT_00e9aad6;
extern uint8_t DAT_00e9aada;
extern uint8_t DAT_00e9aadc;
extern uint8_t DAT_00e9aae0;
extern uint8_t DAT_00e9aae4;
extern uint8_t DAT_00e9acd0;
#define _DAT_00e9acd0 DAT_00e9acd0
extern uint8_t DAT_00e9af10;
extern uint32_t DAT_00e9af14;
extern uint8_t DAT_00e9af18;
#define _DAT_00e9af18 DAT_00e9af18
extern uint8_t DAT_00e9af1c;
#define _DAT_00e9af1c DAT_00e9af1c
extern uint8_t DAT_00e9af44;
extern uint32_t DAT_00e9b188;
extern uint32_t DAT_00e9b198;
extern uint8_t DAT_00e9b1c4;
#define _DAT_00e9b1c4 DAT_00e9b1c4
extern uint8_t DAT_00e9b1c8;
#define _DAT_00e9b1c8 DAT_00e9b1c8
extern uint8_t DAT_00e9b1cc;
#define _DAT_00e9b1cc DAT_00e9b1cc
extern uint8_t DAT_00e9b1d0;
#define _DAT_00e9b1d0 DAT_00e9b1d0
extern uint8_t DAT_00e9b1d4;
#define _DAT_00e9b1d4 DAT_00e9b1d4
extern uint8_t DAT_00e9b1d8;
extern uint8_t DAT_00e9b4e8;
#define _DAT_00e9b4e8 DAT_00e9b4e8
extern uint8_t DAT_00e9b4ea;
extern uint8_t DAT_00e9b4fd;
extern uint8_t DAT_00e9b50a;
extern uint8_t DAT_00e9b58a;
extern uint8_t DAT_00e9b60a;
extern uint8_t DAT_00e9b68a;
extern uint8_t DAT_00e9b70a;
extern uint8_t DAT_00e9b78a;
extern uint8_t DAT_00e9b80a;
extern uint8_t DAT_00e9b80c;
#define _DAT_00e9b80c DAT_00e9b80c
extern uint8_t DAT_00e9b810;
#define _DAT_00e9b810 DAT_00e9b810
extern uint8_t DAT_00e9b818;
extern uint8_t DAT_00e9ba40;
extern uint8_t DAT_00e9be90[0x20]; /* sized to real storage - see globals.c */
extern uint32_t DAT_00e9be94;
extern uint8_t DAT_00e9be98;
#define _DAT_00e9be98 DAT_00e9be98
extern uint8_t DAT_00e9be9c;
#define _DAT_00e9be9c DAT_00e9be9c
extern uint8_t DAT_00e9bea0;
#define _DAT_00e9bea0 DAT_00e9bea0
extern uint8_t DAT_00e9bea4;
extern uint32_t DAT_00e9bea8;
extern uint8_t DAT_00e9bed8;
extern uint8_t DAT_00e9c0fc[0x20]; /* sized to real storage - see globals.c */
extern uint32_t DAT_00e9c104;
extern uint8_t DAT_00e9c108;
#define _DAT_00e9c108 DAT_00e9c108
extern uint8_t DAT_00e9c334[0x18]; /* worker-thread control block - see globals.c */
extern uint8_t DAT_00e9c344;
extern uint8_t DAT_00e9c348;
extern uint32_t DAT_00e9c9c8;
extern uint32_t DAT_00e9c9cc;
extern uint8_t DAT_00e9c9d0;
extern uint32_t DAT_00e9c9dc;
extern uint32_t DAT_00e9c9e0;
extern uint8_t DAT_00ea0e18[0x20]; /* global sprite registry - sentinel-list container, see globals.c */
extern uint32_t DAT_00ea0e1c;
extern uint32_t DAT_00ea0e28;
extern uint32_t DAT_00ea0e2c;
extern uint8_t DAT_00ea0e38;
#define _DAT_00ea0e38 DAT_00ea0e38
extern uint8_t DAT_00ea0e3c;
#define _DAT_00ea0e3c DAT_00ea0e3c
extern uint8_t DAT_00ea0e40;
#define _DAT_00ea0e40 DAT_00ea0e40
extern uint8_t DAT_00ea0e4c;
#define _DAT_00ea0e4c DAT_00ea0e4c
extern uint8_t DAT_00ea0e50;
#define _DAT_00ea0e50 DAT_00ea0e50
extern uint8_t DAT_00ea0e5c;
#define _DAT_00ea0e5c DAT_00ea0e5c
extern uint8_t DAT_00ea0e60;
#define _DAT_00ea0e60 DAT_00ea0e60
extern uint32_t DAT_00ea0e64;
extern uint32_t DAT_00ea0e70;
extern uint32_t DAT_00ea0e74;
extern uint8_t DAT_00ea0e80;
#define _DAT_00ea0e80 DAT_00ea0e80
extern uint8_t DAT_00ea0e84;
#define _DAT_00ea0e84 DAT_00ea0e84
extern uint8_t DAT_00ea0e88;
#define _DAT_00ea0e88 DAT_00ea0e88
extern uint8_t DAT_00ea0e94;
#define _DAT_00ea0e94 DAT_00ea0e94
extern uint8_t DAT_00ea0e98;
#define _DAT_00ea0e98 DAT_00ea0e98
extern uint8_t DAT_00ea0ea4;
#define _DAT_00ea0ea4 DAT_00ea0ea4
extern uint32_t DAT_00ea0ea8;
extern uint8_t DAT_00ea0eac;
#define _DAT_00ea0eac DAT_00ea0eac
extern uint32_t DAT_00ea0f54;
extern uint8_t DAT_00eb168c;
extern uint8_t DAT_00eb1bd8;
/* DAT_00f11dd0 promoted to XFSArchive g_graphicsArchive - see xfs.h */
extern uint32_t DAT_00f11dd4;
extern uint8_t DAT_00f11de0;
#define _DAT_00f11de0 DAT_00f11de0
extern uint8_t DAT_00f12e14;
extern uint8_t DAT_00f12e18;
extern GUID DAT_00f22504; /* IID_IDirect3DHALDevice - see globals.c */
extern uint32_t DAT_00f22650[0x803]; /* sprite-draw batch pool, 0x200c bytes - see globals.c */
extern uint8_t DAT_00f23650;
#define _DAT_00f23650 DAT_00f23650
extern uint8_t DAT_00f23654;
#define _DAT_00f23654 DAT_00f23654
extern uint8_t DAT_00f23658;
#define _DAT_00f23658 DAT_00f23658
extern int32_t g_nCompositorLayer;

/* --- String literals (real content extracted from the binary) --- */

extern const char s_Acks_will_not_be_send_00552d04[];
extern const char s_AutoRefresh_00552818[];
extern const char s_AvataEffectTexture1_00556900[];
extern const char s_AvataEffectTexture2_005568ec[];
extern const char s_AvataTexture1_0055565c[];
extern const char s_AvataTexture2_00556914[];
extern const char s_Avatar_xfs_00553660[];
extern const char s_Background_00552800[];
extern const char s_BuddyIP_005527d4[];
extern const char s_BuddyPort_005527c8[];
extern const char s_BulletTexture1_00556880[];
extern const char s_BulletTexture2_00556870[];
extern const char s_ChannelName_005527e8[];
extern const char s_CharEffectTexture1_005568a4[];
extern const char s_CharEffectTexture2_00556890[];
extern const char s_CharacterTexture1_005568d8[];
extern const char s_CharacterTexture2_005568c4[];
extern const char s_ChooseEvent_txt_00551fcc[];
extern const char s_CrashTexture_00555b80[];
extern const char s_DirectDrawCreateEx_005574fc[];
extern const char s_DirectInput8Create_00557414[];
extern const char s_DirectSoundCreate8_005574ac[];
extern const char s_Effect3D_0055280c[];
extern const char s_EffectVolume_00552824[];
extern const char s_Executable_0055278c[];
extern const char s_Feel_ethereal_____00552d24[];
extern const char s_FirewallTexture_00555bb0[];
extern const char s_FlameTexture1_00556860[];
extern const char s_FlameTexture2_00556850[];
extern const char s_FlameTexture3_00556840[];
extern const char s_FlameTexture4_00556830[];
extern const char s_FlameTexture_d_00556778[];
extern const char s_FourWord_txt_00552c3c[];
extern const char s_GameName_005527f4[];
extern const char s_Game_Programmer___comsik_00553538[];
extern const char s_GunBound_00552748[];
extern const char s_JewelTexture_005567c0[];
extern const char s_Language_005527dc[];
extern const char s_Language_txt_00554008[];
extern const char s_LaserEffect_00556794[];
extern const char s_LastServer_00552884[];
extern const char s_LightningTexture_00555b9c[];
extern const char s_Lightning_00555b90[];
extern const char s_Location_00552878[];
extern const char s_MidiMode_00552840[];
extern const char s_MouseSpeed_0055284c[];
extern const char s_MusicVolume_00552834[];
extern const char s_Oh___It_s_CozY_here______00553498[];
extern const char s_RayonTexture1_00556820[];
extern const char s_RayonTexture2_00556810[];
extern const char s_RefreshRate_0055201c[];
extern const char s_RiderTexture_005567e0[];
extern const char s_STATIC_00557b50[];
extern const char s_Screen_00552870[];
extern const char s_Server___Game_buddy_Programmer___0055322c[];
extern const char s_ShootingMode_00552858[];
extern const char s_ShopURL_005527c0[];
extern const char s_SoftnyxGunBound_gme_00552764[];
extern const char s_Softnyx_00552754[];
extern const char s_Software_Softnyx_GameBuddy_0056d3bc[];
extern const char s_Software_Softnyx_GunBound_0056d3a0[];
extern const char s_Sound_txt_00557218[];
extern const char s_SpecialTexture1_00556800[];
extern const char s_SpecialTexture2_005567f0[];
extern const char s_System_CurrentControlSet_Service_00552040[];
extern const char s_TagTexture_005568b8[];
extern const char s_Template_0055273c[];
extern const char s_ThorTexture1_005567b0[];
extern const char s_ThorTexture2_005567a0[];
extern const char s_TornadoTexture_00555bc0[];
extern const char s_Version_00552868[];
extern const char s_WaterEffect_00556788[];
extern const char s_WeaterTexture_00557224[];
extern const char s_YesooriTexture_005567d0[];
extern const char s__04d__02d__02d_00555640[];
extern const char s__05d_img_00555a08[];
extern const char s__Y_m_d__H_M_005570bc[];
extern const char s___15s_00553590[];
extern const char s__cb_05d_img_00552200[];
extern const char s__cb_05dl_img_005521cc[];
extern const char s__cg_05d_img_005521f4[];
extern const char s__cg_05dl_img_005521bc[];
extern const char s__ch_05d_img_005521e8[];
extern const char s__ch_05dl_img_005521ac[];
extern const char s__d__d__d__d_00557138[];
extern const char s__dmoon_xes_0055674c[];
extern const char s__sADB_exe_00552730[];
extern const char s__s__3d__3d__005536b8[];
extern const char s__s_d_img_0055723c[];
extern const char s__s_s_07d_bmp_00552220[];
extern const char s__s_s____s_sv_005570ac[];
extern const char s_active_00551e58[];
extern const char s_avata_00553fa8[];
extern const char s_b_buddy_down_00552258[];
extern const char s_b_buddy_exit_00552248[];
extern const char s_b_buddy_up_00552268[];
extern const char s_b_error_confirm_00552238[];
extern const char s_b_gamelist_avatar_00553760[];
extern const char s_b_gamelist_buddy_00553788[];
extern const char s_b_gamelist_buddydown_005522a4[];
extern const char s_b_gamelist_buddyup_005522bc[];
extern const char s_b_gamelist_channeldown_00552274[];
extern const char s_b_gamelist_channelup_0055228c[];
extern const char s_b_gamelist_create_0055374c[];
extern const char s_b_gamelist_directgo_005536d0[];
extern const char s_b_gamelist_exit_0055379c[];
extern const char s_b_gamelist_friend_005536e4[];
extern const char s_b_gamelist_join_0055373c[];
extern const char s_b_gamelist_next_005536f8[];
extern const char s_b_gamelist_prev_00553708[];
extern const char s_b_gamelist_ranking_00553774[];
extern const char s_b_gamelist_viewall_00553728[];
extern const char s_b_gamelist_wait_00553718[];
extern const char s_b_play_all_0055412c[];
extern const char s_b_play_option_00554174[];
extern const char s_b_play_skip_00554138[];
extern const char s_b_play_tag_00554120[];
extern const char s_b_play_weapon1_00554164[];
extern const char s_b_play_weapon2_00554154[];
extern const char s_b_play_weapon3_00554144[];
extern const char s_b_ready_buddy_00556b40[];
extern const char s_b_ready_button_00556afc[];
extern const char s_b_ready_changeteam_00556b60[];
extern const char s_b_ready_character_00556b1c[];
extern const char s_b_ready_exit_00556b50[];
extern const char s_b_ready_option_00556b30[];
extern const char s_b_ready_ready_005570c8[];
extern const char s_b_ready_scroll_00556b0c[];
extern const char s_b_ready_startgame_005570d8[];
extern const char s_b_result_confirm_00554074[];
extern const char s_b_server_buddygame_00557170[];
extern const char s_b_server_choiceserver_00557158[];
extern const char s_b_server_exitgame_00557144[];
extern const char s_b_store_buddygame_00555764[];
extern const char s_b_store_buy_005556fc[];
extern const char s_b_store_cap_00555758[];
extern const char s_b_store_cashcharge_005556cc[];
extern const char s_b_store_cloth_00555748[];
extern const char s_b_store_down_005556e0[];
extern const char s_b_store_exit_00555778[];
extern const char s_b_store_flag_00555728[];
extern const char s_b_store_glasse_00555738[];
extern const char s_b_store_puton_00555708[];
extern const char s_b_store_up_005556f0[];
extern const char s_b_storewindow_confirm_00555a8c[];
extern const char s_bfire1_005569f0[];
extern const char s_bfire2_005569e8[];
extern const char s_bifire_005569d8[];
extern const char s_blash45_00552f2c[];
extern const char s_bsfire_005569e0[];
extern const char s_c__comsik_txt_00552778[];
extern const char s_characterdata_dat_0055364c[];
extern const char s_chuko_00553010[];
extern const char s_class_00552074[];
extern const char s_clear_00552cfc[];
extern const char s_comsik_00553578[];
extern const char s_cursor_005524e8[];
extern const char s_ddraw_dll_00557510[];
extern const char s_designer_00553220[];
extern const char s_dinput8_dll_00557428[];
extern const char s_disable_00551e68[];
extern const char s_display_00552028[];
extern const char s_driver_0055206c[];
extern const char s_dsound_dll_005574c0[];
extern const char s_enddream_0055348c[];
extern const char s_ethera_00552d58[];
extern const char s_event14__d_img_005554e8[];
extern const char s_event_d1800_img_00557248[];
extern const char s_flame_00553d2c[];
extern const char s_graphics_xfs_00551fdc[];
extern const char s_guide_005535e0[];
extern const char s_gunbound_ex__00552718[];
extern const char s_gunbound_exe_00552708[];
extern const char s_http___shop_gunbound_com_avatar__00552798[];
extern const char s_ifire_00553b60[];
extern const char s_itemdata_dat_0055362c[];
extern const char s_jaeyong_0055334c[];
extern const char s_jchlee75_005532d8[];
extern const char s_jewel_d_00553bd4[];
extern const char s_johnny5_005531f8[];
extern const char s_knightion_00553bdc[];
extern const char s_knights_00552ecc[];
extern const char s_laserion_00553be8[];
extern const char s_load_stage_02d_img_00557098[];
extern const char s_logging_00552cf4[];
extern const char s_loserii_00553104[];
extern const char s_loudall_00553580[];
extern const char s_message_005535d0[];
extern const char s_mf_05d_img_0055220c[];
extern const char s_mf_05dl_img_005521dc[];
extern const char s_modes__d__d__d_00552030[];
extern const char s_mouse_00551e70[];
extern const char s_mutelist_00553598[];
extern const char s_noack_00552d1c[];
extern const char s_normal_00552230[];
extern const char s_oorusa_00553388[];
extern const char s_pirania_00552fa4[];
extern const char s_ready_00551e80[];
extern const char s_reddragon_00553280[];
extern const char s_rider_00553f98[];
extern const char s_scjang_005530c4[];
extern const char s_select_00551e60[];
extern const char s_sfire_00553b78[];
extern const char s_shrduaakstpakstpaksakstp_00552cbc[];
extern const char s_shrduarhkswjs_00552cd8[];
extern const char s_shrduatlwkr_00552ce8[];
extern const char s_sound_xfs_005526fc[];
extern const char s_stage_d_mp3_005569c0[];
extern const char s_stage_dat_0055363c[];
extern const char s_tank_d_00553fa0[];
extern const char s_teleport1_005535f8[];
extern const char s_test_txt_00552c30[];
extern const char s_tnormal_00553604[];
extern const char s_twnormal_0055360c[];
extern const char s_unmove_00555c98[];
extern const char s_wmove_00555ca0[];
extern const char s_wnormal_00553618[];
extern const char s_yaong2_00553318[];
extern const char s_yesoori_005533c8[];

/* --- Named data symbols (vtables, PTR_DAT_/PTR_FUN_ pointer
 * variables) --- */

extern void *PTR_DAT_0054f378;
extern void *PTR_DAT_00551ecc;
extern void *PTR_DAT_00551ed0;
extern void *PTR_DAT_00552788;
extern void *PTR_DAT_005535c0;
extern void *PTR_DAT_00553c9c;
extern void *PTR_DAT_00553ca8;
extern void *PTR_DAT_00555500;
extern void *PTR_DAT_00555650;
extern void *PTR_DAT_00555cc8;
extern void *PTR_DAT_00555e2c;
extern char *PTR_DAT_00563b40; /* char *, not void *: call sites do byte-offset arithmetic on it (see the g_pD3DDevice7 comment) */
extern void *PTR_DAT_00568180;
extern void *PTR_DAT_00568800;
extern void *PTR_DAT_00568810;
extern void *PTR_DAT_0056d460;
extern uint8_t g_abItemRecords[2492];
extern void *PTR_FUN_00544b5c;
extern void *PTR_FUN_00544b68;
extern void *PTR_FUN_00544b74;
extern void *PTR_FUN_00551cb4;
extern void *PTR_FUN_00551cf0;
extern void *PTR_FUN_00551e88;
extern void *PTR_FUN_0055208c;
extern void *PTR_FUN_005520a0;
extern void *PTR_FUN_00555aa4;
extern void *PTR_FUN_00555ac4;
extern void *PTR_FUN_00555af8;
extern void *PTR_FUN_00555b18;
extern void *PTR_FUN_00555b38;
extern void *PTR_FUN_00555b54;
extern void *PTR_FUN_00555b68;
extern void *PTR_FUN_00555b7c;
extern void *PTR_FUN_00555bd0;
extern void *PTR_FUN_00555bf0;
extern void *PTR_FUN_00555c14;
extern void *PTR_FUN_00555c34;
extern void *PTR_FUN_00555c54;
extern void *PTR_FUN_00555c68;
extern void *PTR_FUN_00555ccc;
extern void *PTR_FUN_00555ce0;
extern void *PTR_FUN_00555cf4;
extern void *PTR_FUN_00555d14;
extern void *PTR_FUN_00555d34;
extern void *PTR_FUN_00555d54;
extern void *PTR_FUN_00555d74;
extern void *PTR_FUN_00555d98;
extern void *PTR_FUN_00555dac;
extern void *PTR_FUN_00555dcc;
extern void *PTR_FUN_00555dec;
extern void *PTR_FUN_00555e0c;
extern void *PTR_FUN_00555e30;
extern void *PTR_FUN_00555e54;
extern void *PTR_FUN_00555e74;
extern void *PTR_FUN_00555e88;
extern void *PTR_FUN_00555ea8;
extern void *PTR_FUN_00555ec8;
extern void *PTR_FUN_00555edc;
extern void *PTR_FUN_00555ef0;
extern void *PTR_FUN_00555f04;
extern void *PTR_FUN_00555f18;
extern void *PTR_FUN_00555f38;
extern void *PTR_FUN_00555f58;
extern void *PTR_FUN_00555f7c;
extern void *PTR_FUN_00555f9c;
extern void *PTR_FUN_00555fbc;
extern void *PTR_FUN_00555fdc;
extern void *PTR_FUN_00556008;
extern void *PTR_FUN_00556038;
extern void *PTR_FUN_00556058;
extern void *PTR_FUN_00556078;
extern void *PTR_FUN_00556098;
extern void *PTR_FUN_005560bc;
extern void *PTR_FUN_005560d0;
extern void *PTR_FUN_005560f0;
extern void *PTR_FUN_00556110;
extern void *PTR_FUN_00556160;
extern void *PTR_FUN_00556180;
extern void *PTR_FUN_00556194;
extern void *PTR_FUN_005561a8;
extern void *PTR_FUN_005561c8;
extern void *PTR_FUN_005561ec;
extern void *PTR_FUN_0055620c;
extern void *PTR_FUN_00556230;
extern void *PTR_FUN_00556250;
extern void *PTR_FUN_00556264;
extern void *PTR_FUN_00556284;
extern void *PTR_FUN_005562a8;
extern void *PTR_FUN_005562c8;
extern void *PTR_FUN_005562f4;
extern void *PTR_FUN_00556308;
extern void *PTR_FUN_0055631c;
extern void *PTR_FUN_00556340;
extern void *PTR_FUN_00556360;
extern void *PTR_FUN_00556380;
extern void *PTR_FUN_005563a8;
extern void *PTR_FUN_005563d0;
extern void *PTR_FUN_005563f0;
extern void *PTR_FUN_00556424;
extern void *PTR_FUN_00556448;
extern void *PTR_FUN_00556468;
extern void *PTR_FUN_00556488;
extern void *PTR_FUN_0055649c;
extern void *PTR_FUN_005564bc;
extern void *PTR_FUN_005564d0;
extern void *PTR_FUN_005564f0;
extern void *PTR_FUN_00556510;
extern void *PTR_FUN_00556524;
extern void *PTR_FUN_00556544;
extern void *PTR_FUN_00556558;
extern void *PTR_FUN_0055656c;
extern void *PTR_FUN_0055658c;
extern void *PTR_FUN_005565ac;
extern void *PTR_FUN_005565cc;
extern void *PTR_FUN_005565e4;
extern void *PTR_FUN_005565f8;
extern void *PTR_FUN_0055661c;
extern void *PTR_FUN_00556640;
extern void *PTR_FUN_00556660;
extern void *PTR_FUN_00556680;
extern void *PTR_FUN_005566a0;
extern void *PTR_FUN_005566c0;
extern void *PTR_FUN_00556a40;
extern void *PTR_FUN_005572dc;
extern void *PTR_FUN_005572e8[2];
extern void *PTR_FUN_005572f0;
extern void *PTR_FUN_00557300;
extern void *PTR_FUN_0055745c;
extern void *PTR_FUN_00557484;
extern void *PTR_FUN_00557524;
extern void *PTR_FUN_00557528;
extern void *PTR_FUN_00557530;
extern void *PTR_FUN_00557534;
extern void *PTR_FUN_00557538;
extern void *PTR_FUN_00557550;
extern void *PTR_FUN_005575a8;
extern void *PTR_FUN_00557cfc;
extern void *PTR_FUN_00557f80;
extern void *PTR_FUN_005637cc;
extern void *PTR_FUN_005637d0;
extern void *PTR_FUN_00563a60;
extern void *PTR_FUN_00563aec;
extern void *PTR_FUN_00563da0;
extern void *PTR_FUN_00563da4;
extern void *PTR_FUN_00563da8;
extern void *PTR_FUN_0056d0f0;
extern void *PTR_LAB_0054b450;
extern void *PTR_LAB_0054b458;
extern void *PTR_LAB_00550378;
extern void *PTR_LAB_00551cb8;
extern void *PTR_LAB_00551cf4;
extern void *PTR_LAB_005520a4;
extern void *PTR_LAB_005520ac;
extern void *PTR_LAB_00553fb0[12];
extern void *PTR_LAB_00553ff8;
extern void *PTR_LAB_00554000;
extern void *PTR_LAB_005572e0;
extern void *PTR_LAB_00557434;
extern void *PTR_LAB_005574cc[7];
extern void *PTR_LAB_005574e0[4];
extern void *PTR_LAB_005574e8[5];
extern void *PTR_LAB_0055752c;
extern void *PTR_LAB_0055755c;
extern void *PTR_LAB_00557594;
extern void *PTR_LAB_00557598;
extern void *PTR_LAB_005575ac;
extern void *PTR_LAB_005575b8;
extern void *PTR_LAB_005575c8;
extern void *PTR_LAB_00557610;
extern void *PTR_LAB_00557654;
extern void *PTR_LAB_00557b94;
extern void *PTR_LAB_00557bbc;
extern void *PTR_LAB_00557be4;
extern void *PTR_LAB_00557c0c;
extern void *PTR_LAB_00557c34;
extern void *PTR_LAB_00557c5c;
extern void *PTR_LAB_00557c84;
extern void *PTR_LAB_00557cac;
extern void *PTR_LAB_00557cd4;
extern void *PTR_LAB_00557d28;
extern void *PTR_LAB_00557d50;
extern void *PTR_LAB_00557d78;
extern void *PTR_LAB_00557da0;
extern void *PTR_LAB_00557dc8;
extern void *PTR_LAB_00557df0;
extern void *PTR_LAB_00557e18;
extern void *PTR_LAB_00557e40;
extern void *PTR_LAB_00557e68;
extern void *PTR_LAB_00557e90;
extern void *PTR_LAB_00557eb8;
extern void *PTR_LAB_00557ee0;
extern void *PTR_LAB_00557f08;
extern void *PTR_LAB_00557f30;
extern void *PTR_LAB_00557f58;
extern void *PTR_LAB_00563ddc;
extern void *vtable_ButtonWidget[32];
extern void *vtable_State01_Title[32];
extern void *vtable_State02_ServerSelect[32];
extern void *vtable_State05_Logo1[32];
extern void *vtable_State06_Logo2[32];
extern void *vtable_State07_AvatarStore[32];
extern void *vtable_State09_ReadyRoom[32];
extern void *vtable_State10_Loading[32];
extern void *vtable_State11_InBattle[32];
extern void *vtable_State3_NetworkSession[32];


/* --- Code labels referenced by address --- 
 *
 * LAB_<address> symbols are .text code labels (mostly SEH/exception-
 * handler entry points pushed onto the FS:0 frame in function
 * prologues: `puStack_N = &LAB_...`). Only their *addresses* are ever
 * taken - never called or jumped to from C - so, like
 * IMAGE_DOS_HEADER_00400000, a one-byte marker object per label is
 * enough for the raw ports to compile. Generated from every unique
 * `&LAB_<address>` reference under src/. */
extern uint8_t LAB_00401000;
extern uint8_t LAB_00401060;
extern uint8_t LAB_005159d0;
extern uint8_t LAB_005282a8;
extern uint8_t LAB_0052847c;
extern uint8_t LAB_0052e890;
extern uint8_t LAB_0052e8db;
extern uint8_t LAB_005376d4;
extern uint8_t LAB_005376f9;
extern uint8_t LAB_00537710;
extern uint8_t LAB_00537728;
extern uint8_t LAB_0053776e;
extern uint8_t LAB_0053778b;
extern uint8_t LAB_005377d0;
extern uint8_t LAB_005377e0;
extern uint8_t LAB_005377f8;
extern uint8_t LAB_00537868;
extern uint8_t LAB_00537890;
extern uint8_t LAB_005378ab;
extern uint8_t LAB_005378c8;
extern uint8_t LAB_005378e8;
extern uint8_t LAB_00537922;
extern uint8_t LAB_00537938;
extern uint8_t LAB_0053795b;
extern uint8_t LAB_00537970;
extern uint8_t LAB_00537980;
extern uint8_t LAB_00537a24;
extern uint8_t LAB_00537a38;
extern uint8_t LAB_00537a58;
extern uint8_t LAB_00537a80;
extern uint8_t LAB_00537a95;
extern uint8_t LAB_00537aa5;
extern uint8_t LAB_00537abd;
extern uint8_t LAB_00537ad0;
extern uint8_t LAB_00537b24;
extern uint8_t LAB_00537b38;
extern uint8_t LAB_00537b5b;
extern uint8_t LAB_00537b7d;
extern uint8_t LAB_00537b98;
extern uint8_t LAB_00537bd8;
extern uint8_t LAB_00537bfb;
extern uint8_t LAB_00537c4e;
extern uint8_t LAB_00537c73;
extern uint8_t LAB_00537c93;
extern uint8_t LAB_00537cae;
extern uint8_t LAB_00537ce3;
extern uint8_t LAB_00537d13;
extern uint8_t LAB_00537d41;
extern uint8_t LAB_00537d71;
extern uint8_t LAB_00537d93;
extern uint8_t LAB_00537e85;
extern uint8_t LAB_00537eb1;
extern uint8_t LAB_0053804d;
extern uint8_t LAB_0053808f;
extern uint8_t LAB_005380ab;
extern uint8_t LAB_00538146;
extern uint8_t LAB_005381d6;
extern uint8_t LAB_00538258;
extern uint8_t LAB_005382e8;
extern uint8_t LAB_00538327;
extern uint8_t LAB_00538367;
extern uint8_t LAB_0053844c;
extern uint8_t LAB_0053852c;
extern uint8_t LAB_00538e36;
extern uint8_t LAB_00538e6a;
extern uint8_t LAB_00538f8c;
extern uint8_t LAB_00539066;
extern uint8_t LAB_005390bc;
extern uint8_t LAB_005390e6;
extern uint8_t LAB_0053910c;
extern uint8_t LAB_005391af;
extern uint8_t LAB_005391f4;
extern uint8_t LAB_00539270;
extern uint8_t LAB_005392af;
extern uint8_t LAB_00539344;
extern uint8_t LAB_005396ee;
extern uint8_t LAB_00539797;
extern uint8_t LAB_005397f2;
extern uint8_t LAB_00539826;
extern uint8_t LAB_00539864;
extern uint8_t LAB_005399d3;
extern uint8_t LAB_00539a17;
extern uint8_t LAB_00539a68;
extern uint8_t LAB_00539aad;
extern uint8_t LAB_00539b25;
extern uint8_t LAB_00539bef;
extern uint8_t LAB_00539d55;
extern uint8_t LAB_00539e53;
extern uint8_t LAB_00539e97;
extern uint8_t LAB_00539f08;
extern uint8_t LAB_00539ffe;
extern uint8_t LAB_0053a146;
extern uint8_t LAB_0053a187;
extern uint8_t LAB_0053a377;
extern uint8_t LAB_0053a482;
extern uint8_t LAB_0053a990;
extern uint8_t LAB_0053ab3b;
extern uint8_t LAB_0053ab71;
extern uint8_t LAB_0053abda;
extern uint8_t LAB_0053ac2d;
extern uint8_t LAB_0053ac45;
extern uint8_t LAB_0053ad09;
extern uint8_t LAB_0053add9;
extern uint8_t LAB_0053ae1c;
extern uint8_t LAB_0053ae9c;
extern uint8_t LAB_0053aed4;
extern uint8_t LAB_0053aef6;
extern uint8_t LAB_0053af21;
extern uint8_t LAB_0053af72;
extern uint8_t LAB_0053b030;
extern uint8_t LAB_0053b742;
extern uint8_t LAB_0053be60;
extern uint8_t LAB_0053be8b;
extern uint8_t LAB_0053becc;
extern uint8_t LAB_0053bf43;
extern uint8_t LAB_0053bf92;
extern uint8_t LAB_0053bfd2;
extern uint8_t LAB_0053c022;
extern uint8_t LAB_0053c03a;
extern uint8_t LAB_0053c0d4;
extern uint8_t LAB_0053c0f8;
extern uint8_t LAB_0053c152;
extern uint8_t LAB_0053c205;
extern uint8_t LAB_0053c218;
extern uint8_t LAB_0053c294;
extern uint8_t LAB_0053c429;
extern uint8_t LAB_0053c46d;
extern uint8_t LAB_0053c98e;
extern uint8_t LAB_0053ca83;
extern uint8_t LAB_0053ca9b;
extern uint8_t LAB_0053cb84;
extern uint8_t LAB_0053cbe0;
extern uint8_t LAB_0053cc82;
extern uint8_t LAB_0053cd43;
extern uint8_t LAB_0053ce11;
extern uint8_t LAB_0053ce62;
extern uint8_t LAB_0053cf2a;
extern uint8_t LAB_0053cf6e;
extern uint8_t LAB_0053cfc0;
extern uint8_t LAB_0053d10a;
extern uint8_t LAB_0053d19b;
extern uint8_t LAB_0053d1fe;
extern uint8_t LAB_0053d23c;
extern uint8_t LAB_0053d571;
extern uint8_t LAB_0053d8a0;
extern uint8_t LAB_0053d8bb;
extern uint8_t LAB_0053d96a;
extern uint8_t LAB_0053d9ba;
extern uint8_t LAB_0053db1e;
extern uint8_t LAB_0053ddcf;
extern uint8_t LAB_0053defa;
extern uint8_t LAB_0053df47;
extern uint8_t LAB_0053df6b;
extern uint8_t LAB_0053df96;
extern uint8_t LAB_0053dfcc;
extern uint8_t LAB_0053e001;
extern uint8_t LAB_0053e03c;
extern uint8_t LAB_0053e0d4;
extern uint8_t LAB_0053e1c3;
extern uint8_t LAB_0053e2f5;
extern uint8_t LAB_0053e36e;
extern uint8_t LAB_0053e429;
extern uint8_t LAB_0053e523;
extern uint8_t LAB_0053e757;
extern uint8_t LAB_0053e8c0;
extern uint8_t LAB_0053e9f5;
extern uint8_t LAB_0053eb25;
extern uint8_t LAB_0053ecf5;
extern uint8_t LAB_0053ee50;
extern uint8_t LAB_0053ef1b;
extern uint8_t LAB_0053ef67;
extern uint8_t LAB_0053f063;
extern uint8_t LAB_0053f194;
extern uint8_t LAB_0053f429;
extern uint8_t LAB_0053f605;
extern uint8_t LAB_0053f760;
extern uint8_t LAB_0053f853;
extern uint8_t LAB_0053f984;
extern uint8_t LAB_0053fb1c;
extern uint8_t LAB_0053fc80;
extern uint8_t LAB_0053fd98;
extern uint8_t LAB_0053fe59;
extern uint8_t LAB_0053ffd7;
extern uint8_t LAB_0054008a;
extern uint8_t LAB_005400f8;
extern uint8_t LAB_005401f3;
extern uint8_t LAB_00540324;
extern uint8_t LAB_005403ca;
extern uint8_t LAB_005404e4;
extern uint8_t LAB_0054061d;
extern uint8_t LAB_00540762;
extern uint8_t LAB_00540806;
extern uint8_t LAB_0054095a;
extern uint8_t LAB_00540a36;


/* Raw absolute-address accesses Ghidra could not attribute to a
 * named symbol (<t>Ram<address>, typed by the prefix: c=char,
 * d=double, s=short, u=undefined4). Marker storage so the raw
 * ports parse - never linked/run in this state. */
extern uint8_t cRam0055a4ac;
extern double dRam00548778;
extern double dRam00548788;
extern double dRam00548fd8;
extern double dRam00548fe8;
extern double dRam005490d8;
extern double dRam005490e8;
extern double dRam005490f8;
extern double dRam00549108;
extern double dRam00549118;
extern double dRam00549128;
extern double dRam00549138;
extern double dRam00549148;
extern double dRam00549158;
extern double dRam00549168;
extern double dRam00549178;
extern double dRam00549188;
extern int16_t sRamfffffffc;
extern uint32_t uRam0000020c;
extern uint32_t uRam00001e50;
extern uint32_t uRam005490a8;
extern uint32_t uRamfffffff8;


/* Ghidra switchD_<site>::switchdataD_<addr> jumptable symbols, renamed
 * with __ for :: (not C). Address-only markers like the LAB_ labels:
 * the raw ports index off &<symbol> and switch on the entries as
 * integers. */
extern uint8_t *switchD_0050fe76__switchdataD_0051008c;
extern uint8_t *switchD_0051392e__switchdataD_00514460;
#endif

/* Second pass: ~800 addresses missing from the original scan (see
 * this file's earlier note in the numeric-globals section) - found
 * while working through make winelib-syntax-check's FAIL list and
 * hitting a cluster of weapon-effect functions that all needed
 * dozens of these. Same caveats as the first pass: DAT_/_DAT_ are
 * generic uint32_t (real type/size not re-verified via Ghidra this
 * pass), string literals have real content extracted directly from
 * the binary via pefile's RVA-to-file-offset mapping. */
extern uint32_t DAT_00000006;
extern uint32_t DAT_00007f00;
extern uint32_t DAT_00544380;
extern uint32_t DAT_005443a0;
extern uint32_t DAT_005443a4;
extern uint32_t DAT_005443f4;
extern uint32_t DAT_005443fc;
extern uint32_t DAT_00544400;
extern uint32_t DAT_0054442c;
extern uint32_t DAT_005445b4;
extern uint32_t DAT_005445ec;
extern uint32_t DAT_005448e8;
extern uint32_t DAT_005448ec;
extern uint32_t DAT_00544968;
extern uint32_t DAT_0054496c;
extern uint32_t DAT_00544970;
extern uint32_t DAT_00544974;
extern uint32_t DAT_00544a88;
extern uint32_t DAT_0054b460;
extern uint32_t DAT_00551b78;
extern uint32_t DAT_00551b79;
extern uint32_t DAT_00551b7c;
extern uint32_t DAT_00551e2c;
extern uint32_t DAT_00551e30;
extern uint32_t DAT_00551ec4;
extern uint32_t DAT_00551ed4;
extern uint32_t DAT_00552c68;
extern uint32_t DAT_00553b90;
extern uint32_t DAT_00553bb4;
extern uint32_t DAT_00553bb8;
extern uint32_t DAT_00553bbc;
extern uint32_t DAT_00553bf4;
extern uint32_t DAT_00553bf8;
extern uint32_t DAT_00553c18;
extern uint32_t DAT_00553c1c;
extern uint32_t DAT_00553c90;
extern uint32_t DAT_00553c94;
extern uint32_t DAT_00553c98;
extern uint32_t DAT_00553ca0;
extern uint32_t DAT_00553ca4;
extern uint32_t DAT_00555654;
extern uint32_t DAT_00555b4c;
extern uint32_t DAT_00556980;
extern uint32_t DAT_00557318;
extern uint32_t DAT_0055731c;
extern uint32_t DAT_00557320;
extern uint32_t DAT_00557324;
extern uint32_t DAT_00557328;
extern uint32_t DAT_0055732c;
extern uint32_t DAT_00557330;
extern uint32_t DAT_00557334;
extern uint32_t DAT_00557660;
extern uint32_t DAT_00557664;
extern uint32_t DAT_00557948;
extern uint32_t DAT_0055794c;
extern uint32_t DAT_00557a40;
extern uint32_t DAT_00557a44;
extern uint32_t DAT_00557fd8;
extern uint32_t DAT_00563730;
extern uint32_t DAT_00563770;
extern uint32_t DAT_00563774;
extern uint32_t DAT_005637bc;
extern uint32_t DAT_005637c0;
extern uint32_t DAT_005637c4;
extern uint32_t DAT_005637c8;
extern uint32_t DAT_005637d4;
extern uint32_t DAT_005637e8;
extern uint32_t DAT_0056382c;
extern uint32_t DAT_005638ec;
extern uint32_t DAT_0056390c;
extern uint32_t DAT_00563a4c;
extern uint32_t DAT_00563ad8;
extern uint32_t DAT_00563afc;
extern uint32_t DAT_00563b44;
extern uint32_t DAT_00563b48;
extern uint32_t DAT_00563b4c;
extern uint32_t DAT_00563bcc;
extern uint32_t DAT_00563bec;
extern uint32_t DAT_00563c6c;
extern uint32_t DAT_00563cec;
extern uint32_t DAT_00563d0c;
extern uint32_t DAT_00563d8c;
extern uint32_t DAT_00563d90;
extern uint32_t DAT_00563d94;
extern uint32_t DAT_00563d98;
extern uint32_t DAT_00563df0;
extern uint32_t DAT_00563df4;
extern uint32_t DAT_00568100;
extern uint32_t DAT_00568101;
extern uint32_t DAT_00568184;
extern uint32_t DAT_00568188;
extern uint32_t DAT_00568318;
extern uint32_t DAT_00568654;
extern uint32_t DAT_005686d4;
extern uint32_t DAT_00568714;
extern uint32_t DAT_00568738;
extern uint32_t DAT_0056873c;
extern uint32_t DAT_00568740;
extern uint32_t DAT_00568744;
extern uint32_t DAT_00568748;
extern uint32_t DAT_0056874c;
extern uint32_t DAT_00568750;
extern uint32_t DAT_00568754;
extern uint32_t DAT_00568758;
extern uint32_t DAT_0056875c;
extern uint32_t DAT_00568760;
extern uint32_t DAT_00568764;
extern uint32_t DAT_00568768;
extern uint32_t DAT_0056876c;
extern uint32_t DAT_00568770;
extern uint32_t DAT_00568774;
extern uint32_t DAT_00568778;
extern uint32_t DAT_0056877c;
extern uint32_t DAT_00568798;
extern uint32_t DAT_0056879c;
extern uint32_t DAT_005687a0;
extern uint32_t DAT_005687a4;
extern uint32_t DAT_005687a8;
extern uint32_t DAT_005687ac;
extern uint32_t DAT_005687b0;
extern uint32_t DAT_005687b4;
extern uint32_t DAT_005687b8;
extern uint32_t DAT_005687fc;
extern uint32_t *DAT_0056881c; /* used dereferenced and assigned a uint32_t value at call sites */
extern uint32_t DAT_00568840;
extern uint32_t DAT_00568844;
extern uint32_t DAT_00568848;
extern uint32_t DAT_0056884c;
extern uint32_t DAT_00568850;
extern uint32_t DAT_00568854;
extern uint32_t DAT_00568858;
extern uint32_t DAT_0056885c;
extern uint32_t DAT_00568860;
extern uint32_t DAT_00568864;
extern uint32_t DAT_00568868;
extern uint32_t DAT_0056886c;
extern uint32_t DAT_00568870;
extern uint32_t DAT_00568874;
extern uint32_t DAT_00568878;
extern uint32_t DAT_0056887c;
extern uint32_t DAT_00568880;
extern uint32_t DAT_00568884;
extern uint32_t DAT_00568888;
extern uint32_t DAT_0056888c;
extern uint32_t DAT_00568890;
extern uint32_t DAT_00568894;
extern uint32_t DAT_00568898;
extern uint32_t DAT_0056889c;
extern uint32_t DAT_005688a0;
extern uint32_t DAT_005688b8;
extern uint32_t DAT_005688bc;
extern uint32_t DAT_005688c0;
extern uint32_t DAT_005688c4;
extern uint32_t DAT_005688c8;
extern uint32_t DAT_005688cc;
extern uint32_t DAT_005688d0;
extern uint32_t DAT_005688d4;
extern uint32_t DAT_005688d8;
extern uint32_t DAT_005688dc;
extern uint32_t DAT_005688e0;
extern uint32_t DAT_005688e4;
extern uint32_t DAT_005688e8;
extern uint32_t DAT_005688ec;
extern uint32_t DAT_005688f0;
extern uint32_t DAT_005688f4;
extern uint32_t DAT_005688f8;
extern uint32_t DAT_005688fc;
extern uint32_t DAT_00568900;
extern uint32_t DAT_00568904;
extern uint32_t DAT_00568908;
extern uint32_t DAT_0056890c;
extern uint32_t DAT_00568910;
extern uint32_t DAT_00568914;
extern uint32_t DAT_00568918;
extern uint32_t DAT_0056891c;
extern uint32_t DAT_00568920;
extern uint32_t DAT_00568924;
extern uint32_t DAT_00568928;
extern uint32_t DAT_0056892c;
extern uint32_t DAT_00568930;
extern uint32_t DAT_00568934;
extern uint32_t DAT_00568938;
extern uint32_t DAT_0056893c;
extern uint32_t DAT_00568940;
extern uint32_t DAT_00568944;
extern uint32_t DAT_00569144;
extern uint32_t DAT_00569344;
extern uint32_t DAT_00569348;
extern uint32_t DAT_00569b48;
extern uint32_t DAT_0056d468;
extern uint32_t DAT_00598e7e;
/* g_fullnessGaugeThresholds (was DAT_005a9050) - read-only percentage
 * breakpoints {1,10,30,60,100} that bucket a server/room occupancy percent
 * (currentPlayers*100/maxCapacity) into 6 fullness-gauge levels (0=empty ..
 * 5=full), selecting the F/E dial sprite in the WORLD LIST rows and the
 * lobby's per-room dial. Ghidra typed it as a scalar; it's really a 5-int
 * array (RenderWorldListRow indexes [0..4]). */
extern const uint32_t g_fullnessGaugeThresholds[5];
extern uint32_t DAT_005a9290;
extern uint32_t DAT_005a9350;
extern uint32_t DAT_005a94b0;
extern uint32_t DAT_005a9550;
extern uint32_t DAT_005a960c;
extern uint32_t DAT_005a9624;
extern uint32_t DAT_005a9640;
extern uint32_t DAT_005a965c;
extern uint8_t *DAT_005a9680; /* used dereferenced as a byte-stream cursor at call sites */
extern uint32_t DAT_005a9684;
extern uint32_t DAT_005a9688;
extern uint32_t DAT_005a9784;
extern uint32_t DAT_005a9884;
extern uint32_t DAT_005a9888;
extern uint32_t DAT_005a9988;
extern uint32_t DAT_005a9989;
extern uint32_t DAT_005a998a;
extern uint32_t DAT_005a99e8;
extern uint32_t DAT_005a99ec;
extern uint32_t DAT_005a99f0;
extern uint32_t DAT_005a99f4;
extern uint32_t DAT_005a99f8;
extern uint32_t DAT_005a9cf4;
extern uint32_t DAT_005a9cf6;
extern uint32_t DAT_005a9cf8;
extern uint32_t DAT_005ab4f4;
extern uint32_t DAT_005ab4fc;
extern uint32_t DAT_005ab500;
extern uint32_t DAT_005ab604;
extern uint32_t DAT_005ab608;
extern uint32_t DAT_005ab704;
extern uint32_t DAT_005ab708;
extern uint32_t DAT_005ab709;
extern uint32_t DAT_005ab70a;
extern uint32_t DAT_005ab88c;
extern uint32_t DAT_005ab890;
extern uint32_t DAT_005ab8d4;
extern uint32_t DAT_005ab8e0;
extern uint32_t DAT_005ab91c;
extern uint32_t DAT_005ab920;
extern uint32_t DAT_005aba28;
extern uint32_t DAT_005aba2c;
extern uint32_t DAT_005aba30;
extern uint32_t DAT_005aba34;
extern uint32_t DAT_005aba38;
extern uint32_t DAT_005ada38;
extern uint32_t DAT_005ada3c;
extern uint32_t DAT_005ae33c;
extern uint32_t DAT_005ae344;
extern uint32_t DAT_005ae348;
extern uint32_t DAT_005ae34c;
extern uint32_t DAT_005ae350;
extern uint32_t DAT_005ae358;
extern uint32_t DAT_005ae450;
extern uint32_t DAT_005ae740;
extern uint32_t DAT_005ae74c;
extern uint32_t DAT_005ae75c;
extern uint32_t DAT_005ae760;
extern uint32_t DAT_005ae7b0;
extern uint32_t DAT_005ae7cc;
extern uint32_t DAT_005ae7d0;
extern uint32_t DAT_005ae7dc;
extern uint32_t DAT_005ae7e0;
extern uint32_t DAT_005ae7e8;
extern uint32_t DAT_005ae7ec;
extern uint32_t DAT_005ae7f0;
extern uint32_t DAT_005ae7f8;
extern uint32_t DAT_005ae800;
extern uint32_t DAT_005ae804;
extern uint32_t DAT_005ae808;
extern uint32_t DAT_005ae80c;
extern uint32_t DAT_005ae810;
extern uint32_t DAT_005ae814;
extern uint32_t DAT_005ae818;
extern uint32_t DAT_005ae81c;
extern uint32_t DAT_005ae820;
extern uint32_t DAT_005ae824;
extern uint32_t DAT_005ae828;
extern uint32_t DAT_005ae82c;
extern uint32_t DAT_005ae830;
extern uint32_t DAT_005ae834;
extern uint32_t DAT_005ae838;
extern uint32_t DAT_005ae83c;
extern uint32_t DAT_005ae840;
extern uint32_t DAT_005ae844;
extern uint32_t DAT_005ae920;
extern uint32_t DAT_005ae924;
extern uint32_t DAT_005ae928;
extern uint32_t DAT_005ae92c;
extern uint32_t DAT_005ae930;
extern uint32_t DAT_005ae934;
extern uint32_t DAT_005ae93c;
extern uint32_t DAT_005ae940;
extern uint32_t DAT_005af140;
extern uint32_t DAT_005af144;
extern uint32_t DAT_005af944;
extern uint32_t DAT_005b0144;
extern uint32_t DAT_005b0148;
extern uint32_t DAT_005b01c4;
extern uint32_t DAT_005b01e4;
extern uint32_t DAT_005b01fc;
extern uint32_t DAT_005b05fc;
extern uint32_t DAT_005b0efc;
extern uint32_t DAT_005b12fc;
extern uint32_t DAT_005b137c;
extern uint32_t DAT_005b13fc;
extern uint32_t DAT_005c7fb8;
extern uint32_t DAT_005f2f44;
extern uint32_t DAT_005f2f48;
extern uint32_t DAT_005f2f54;
extern uint32_t DAT_005f2f55;
extern uint32_t DAT_005f3774;
extern uint32_t DAT_005f48a8;
extern uint32_t DAT_005f4ab4;
extern uint32_t DAT_005f4ab8;
extern uint32_t DAT_005f4cdc;
extern uint32_t DAT_005f4f00;
extern uint32_t DAT_005f5124;
extern uint32_t DAT_005f5348;
extern uint32_t DAT_00656369;
extern uint32_t DAT_0067e3e4;
extern uint32_t DAT_0067e5f0;
extern uint32_t DAT_0067e608;
extern uint32_t DAT_0067e814;
extern uint32_t DAT_0067e818;
extern uint32_t DAT_0067e82c;
extern uint32_t DAT_0067ea38;
extern uint32_t DAT_0067ea3c;
extern uint32_t DAT_0067ea50;
extern uint32_t DAT_0067ec5c;
extern uint32_t DAT_0067ec6c;
extern uint32_t DAT_006a4c74;
extern uint32_t DAT_006a4c78;
extern uint32_t DAT_006a6480;
extern uint32_t DAT_006a6484;
extern uint32_t DAT_006a6488;
extern uint32_t DAT_006a648c;
extern uint32_t DAT_006a648d;
extern uint32_t DAT_006a6490;
extern uint32_t DAT_006a6494;
extern uint32_t DAT_006a6498;
extern uint32_t DAT_006a6499;
extern uint32_t DAT_006a649c;
extern uint32_t DAT_006a64a0;
extern uint32_t DAT_006a64c4;
extern uint32_t DAT_006a76e0;
extern uint32_t DAT_006a76e4;
extern uint32_t DAT_006a76e8;
extern uint32_t DAT_006a76ec;
extern uint32_t DAT_006a7700;
extern uint32_t DAT_006a770c;
extern uint32_t DAT_006a772c;
extern uint32_t DAT_006a7730;
extern uint32_t DAT_006a7734;
extern uint32_t DAT_006a7736;
extern uint32_t DAT_006a7750;
extern uint32_t DAT_006a7754;
extern uint32_t DAT_006a7f6c;
extern uint32_t DAT_006a7f74;
extern uint32_t DAT_006a7f75;
extern uint32_t DAT_006a7f76;
extern uint32_t DAT_006a7f78;
extern uint32_t DAT_006a7f7c;
extern uint32_t DAT_006a7fa8;
extern uint32_t DAT_006a81b4;
extern uint32_t DAT_006a9b8c;
extern uint32_t DAT_006a9d98;
extern uint32_t DAT_006a9db0;
extern uint32_t DAT_006a9fbc;
extern uint32_t DAT_006a9fd4;
extern uint32_t DAT_006aa1e0;
extern uint32_t DAT_006aa1f8;
extern uint32_t DAT_006aa404;
extern uint32_t DAT_006aa40c;
extern uint32_t DAT_006aa410;
extern uint32_t DAT_006aa630;
extern uint32_t DAT_006aa678;
extern uint32_t DAT_006aa679;
extern uint32_t DAT_006aa67a;
extern uint32_t DAT_006aa690;
extern uint32_t DAT_006aa89c;
extern uint32_t DAT_006aa8b4;
extern uint32_t DAT_006aaac0;
extern uint32_t DAT_006aaac4;
extern uint32_t DAT_006aaafc;
extern uint32_t DAT_006aab00;
extern uint32_t DAT_007934c5;
extern uint32_t DAT_00793668;
extern uint32_t DAT_0079366c;
extern uint32_t DAT_00793670;
extern uint32_t DAT_0079371c;
extern uint32_t DAT_00793720;
extern uint32_t DAT_00793724;
extern uint32_t DAT_007949c8;
extern uint32_t DAT_00794e48;
extern uint32_t g_lastCursorDirection;
extern uint32_t DAT_00989680;
extern uint32_t DAT_00e54a9c;
extern uint32_t DAT_00e54aa0;
/* 0x2101 server-select selector-record table (see globals.c). */
extern uint32_t g_serverSelectRecordCount;   /* 0xe54ca4 */
extern uint8_t  g_serverSelectRecords[21 * 12]; /* 0xe54ca8, 12 bytes/record */
extern uint32_t DAT_00e54da8;
extern uint32_t DAT_00e55a34;
extern uint32_t DAT_00e55a54;
extern uint32_t DAT_00e55a58;
extern uint32_t DAT_00e9af60;
extern uint32_t DAT_00e9c578;
extern uint32_t DAT_00e9cd30;
extern uint32_t DAT_00f25840;
extern uint32_t DAT_00f25844;
extern uint32_t DAT_00f25848;
extern uint32_t DAT_00f2584c;
extern uint32_t DAT_00f25850;
extern uint32_t DAT_00f25854;
extern uint32_t DAT_00f25858;
extern uint32_t DAT_00f2585c;
extern uint32_t DAT_00f25860;
extern uint32_t DAT_00f25864;
extern uint32_t DAT_00f25868;
extern uint32_t DAT_00f2586c;
extern uint32_t DAT_00f25870;
extern uint32_t DAT_00f25874;
extern uint32_t DAT_00f25878;
extern uint32_t DAT_00f2587c;
extern uint32_t DAT_00f25880;
extern uint32_t DAT_00f258a4;
extern uint32_t DAT_00f258a8;
extern uint32_t DAT_00f258c0;
extern uint32_t DAT_00f258c4;
extern uint32_t DAT_00f258c8;
extern uint32_t DAT_00f258cc;
extern uint32_t DAT_00f258d0;
extern uint32_t DAT_00f258d4;
extern uint32_t DAT_00f258e0;
extern uint32_t DAT_00f258e4;
extern uint32_t DAT_00f258e8;
extern uint32_t DAT_00f25900;
extern uint32_t DAT_00f25904;
extern uint32_t DAT_00f25908;
extern uint32_t DAT_00f2590c;
extern uint32_t DAT_00f25910;
extern uint32_t DAT_00f25914;
extern uint32_t DAT_00f25918;
extern uint32_t DAT_00f2591c;
extern uint32_t DAT_00f25920;
extern uint32_t DAT_00f25924;
extern uint32_t DAT_00f25928;
extern uint32_t DAT_00f2592c;
extern uint32_t DAT_00f25930;
extern uint32_t DAT_00f25934;
extern uint32_t DAT_00f25938;
extern uint32_t DAT_00f2593c;
extern uint32_t DAT_00f25940;
extern uint32_t DAT_00f25944;
extern uint32_t DAT_00f25960;
extern uint32_t DAT_00f25964;
extern uint32_t DAT_00f25968;
extern uint32_t DAT_00f2596c;
extern uint32_t DAT_00f25970;
extern uint32_t DAT_00f25974;
extern uint32_t DAT_00f25978;
extern uint32_t DAT_00f2597c;
extern uint32_t DAT_00f25980;
extern uint32_t DAT_00f259b0;
extern uint32_t DAT_00f259b4;
extern uint32_t DAT_00f259b8;
extern uint32_t DAT_00f259bc;
extern uint32_t DAT_00f259c0;
extern uint32_t DAT_00f259c4;
extern uint32_t DAT_00f259c8;
extern uint32_t DAT_00f259cc;
extern uint32_t DAT_00f259d0;
extern uint32_t DAT_00f259e0;
extern uint32_t DAT_00f259e4;
extern uint32_t DAT_00f259e8;
extern uint32_t DAT_00f259ec;
extern uint32_t DAT_00f259f0;
extern uint32_t DAT_00f259f4;
extern uint32_t DAT_00f259f8;
extern uint32_t DAT_00f259fc;
extern uint32_t DAT_00f25a10;
extern uint32_t DAT_00f25a14;
extern uint32_t DAT_00f25a18;
extern uint32_t DAT_00f25a1c;
extern uint32_t DAT_00f25a20;
extern uint32_t DAT_00f25a24;
extern uint32_t DAT_00f25a28;
extern uint32_t DAT_00f25a2c;
extern uint32_t DAT_00f25a40;
extern uint32_t DAT_00f25a7c;
extern uint32_t DAT_00f25a80;
extern uint32_t DAT_00f25a84;
extern uint32_t DAT_00f25a88;
extern uint32_t DAT_00f25a9c;
extern uint32_t DAT_00f25aa0;
extern uint32_t DAT_00f25aa4;
extern uint32_t DAT_00f25aa8;
extern uint32_t DAT_00f25ab0;
extern uint32_t DAT_00f25ab4;
extern uint32_t DAT_00f25ac0;
extern uint32_t DAT_00f25b00;
extern uint32_t DAT_00f25b04;
extern uint32_t DAT_00f25b08;
extern uint32_t DAT_00f25b0c;
extern uint32_t DAT_00f25b10;
extern uint32_t DAT_00f25b14;
extern uint32_t DAT_00f25b18;
extern uint32_t DAT_00f25b1c;
extern uint32_t DAT_00f25b20;
extern uint32_t DAT_00f25b24;
extern uint32_t DAT_00f25b28;
extern uint32_t DAT_00f25b2c;
extern uint32_t DAT_00f25b30;
extern uint32_t DAT_00f25b34;
extern uint32_t DAT_00f25b38;
extern uint32_t DAT_00f25b3c;
extern uint32_t DAT_00f25b40;
extern uint32_t DAT_00f25b44;
extern uint32_t DAT_00f25b48;
extern uint32_t DAT_00f25b4c;
extern uint32_t DAT_00f25b50;
extern uint32_t DAT_00f25b54;
extern uint32_t DAT_00f25b58;
extern uint32_t DAT_00f25b5c;
extern uint32_t DAT_00f25b60;
extern uint32_t DAT_00f25b64;
extern uint32_t DAT_00f25b68;
extern uint32_t DAT_00f25b6c;
extern uint32_t DAT_00f25b70;
extern uint32_t DAT_00f25b74;
extern uint32_t DAT_00f25b78;
extern uint32_t DAT_00f25b7c;
extern uint32_t DAT_00f25b80;
extern uint32_t DAT_00f25b84;
extern uint32_t DAT_00f25b88;
extern uint32_t DAT_00f25b8c;
extern uint32_t DAT_00f25c20;
extern uint32_t DAT_00f25c24;
extern uint32_t DAT_00f25c28;
extern uint32_t DAT_00f25c2c;
extern uint32_t DAT_00f25c30;
extern uint32_t DAT_00f25c34;
extern uint32_t DAT_00f25c38;
extern uint32_t DAT_00f25c3c;
extern uint32_t DAT_00f25c40;
extern uint32_t DAT_00f25c44;
extern uint32_t DAT_00f25c48;
extern uint32_t DAT_00f25c4c;
extern uint32_t DAT_00f25d3c;
extern uint32_t DAT_00f25d40;
extern uint32_t DAT_00f25d44;
extern uint32_t DAT_00f25d98;
extern uint32_t DAT_00f25e00;
extern uint32_t DAT_00f25e04;
extern uint8_t *DAT_00f25e08; /* used dereferenced as a byte-stream cursor at call sites */
extern uint32_t DAT_00f25e0c;
extern uint32_t DAT_00f25e10;
extern uint32_t DAT_00f25e20;
extern uint32_t DAT_00f25e78;
extern uint32_t DAT_00f25ed0;
extern uint32_t DAT_00f25ee0;
extern uint32_t DAT_00f25ee4;
extern uint32_t DAT_00f25f00;
extern uint32_t DAT_00544360;
#define _DAT_00544360 DAT_00544360
extern uint32_t DAT_00544368;
#define _DAT_00544368 DAT_00544368
extern uint32_t DAT_00544370;
#define _DAT_00544370 DAT_00544370
extern uint32_t DAT_00544378;
#define _DAT_00544378 DAT_00544378
extern uint32_t DAT_005448d8;
#define _DAT_005448d8 DAT_005448d8
extern uint32_t DAT_005448e0;
#define _DAT_005448e0 DAT_005448e0
extern uint32_t DAT_00544aa8;
#define _DAT_00544aa8 DAT_00544aa8
extern uint32_t DAT_00544ab0;
#define _DAT_00544ab0 DAT_00544ab0
extern uint32_t DAT_00544ab8;
#define _DAT_00544ab8 DAT_00544ab8
extern uint32_t DAT_00544ac0;
#define _DAT_00544ac0 DAT_00544ac0
extern uint32_t DAT_00544ac8;
#define _DAT_00544ac8 DAT_00544ac8
extern uint32_t DAT_00544ad0;
#define _DAT_00544ad0 DAT_00544ad0
extern uint32_t DAT_00544ad8;
#define _DAT_00544ad8 DAT_00544ad8
extern uint32_t DAT_00544ae0;
#define _DAT_00544ae0 DAT_00544ae0
extern uint32_t DAT_00544ae8;
#define _DAT_00544ae8 DAT_00544ae8
extern uint32_t DAT_00544af0;
#define _DAT_00544af0 DAT_00544af0
extern uint32_t DAT_00544af8;
#define _DAT_00544af8 DAT_00544af8
extern uint32_t DAT_00544b00;
#define _DAT_00544b00 DAT_00544b00
extern uint32_t DAT_0054bb4c;
#define _DAT_0054bb4c DAT_0054bb4c
extern uint32_t DAT_0054c870;
#define _DAT_0054c870 DAT_0054c870
extern uint32_t DAT_00557fe4;
#define _DAT_00557fe4 DAT_00557fe4
extern uint32_t DAT_00558014;
#define _DAT_00558014 DAT_00558014
extern uint32_t DAT_00558018;
#define _DAT_00558018 DAT_00558018
extern uint32_t DAT_00558048;
#define _DAT_00558048 DAT_00558048
extern uint32_t DAT_00558068;
#define _DAT_00558068 DAT_00558068
extern uint32_t DAT_00558070;
#define _DAT_00558070 DAT_00558070
extern uint32_t DAT_00558078;
#define _DAT_00558078 DAT_00558078
extern uint32_t DAT_00563d9c;
#define _DAT_00563d9c DAT_00563d9c
extern uint32_t DAT_005687f8;
#define _DAT_005687f8 DAT_005687f8
extern uint32_t DAT_005688a4;
#define _DAT_005688a4 DAT_005688a4
extern uint32_t DAT_005688a8;
#define _DAT_005688a8 DAT_005688a8
extern uint32_t DAT_005688ac;
#define _DAT_005688ac DAT_005688ac
extern uint32_t DAT_005688b0;
#define _DAT_005688b0 DAT_005688b0
extern uint32_t DAT_005688b4;
#define _DAT_005688b4 DAT_005688b4
extern uint32_t DAT_00588f68;
#define _DAT_00588f68 DAT_00588f68
extern uint32_t DAT_00588f6c;
#define _DAT_00588f6c DAT_00588f6c
extern uint32_t DAT_00588f70;
#define _DAT_00588f70 DAT_00588f70
extern uint32_t DAT_00588f74;
#define _DAT_00588f74 DAT_00588f74
extern uint32_t DAT_005a90e0;
#define _DAT_005a90e0 DAT_005a90e0
extern uint32_t DAT_005a90e4;
#define _DAT_005a90e4 DAT_005a90e4
extern uint32_t DAT_005a90e8;
#define _DAT_005a90e8 DAT_005a90e8
extern uint32_t DAT_005a90ec;
#define _DAT_005a90ec DAT_005a90ec
extern uint32_t DAT_005a92a4;
#define _DAT_005a92a4 DAT_005a92a4
extern uint32_t DAT_005a92b8;
#define _DAT_005a92b8 DAT_005a92b8
extern uint32_t DAT_005a92bc;
#define _DAT_005a92bc DAT_005a92bc
extern uint32_t DAT_005a92c8;
#define _DAT_005a92c8 DAT_005a92c8
extern uint32_t DAT_005a93e0;
#define _DAT_005a93e0 DAT_005a93e0
extern uint32_t DAT_005a93e4;
#define _DAT_005a93e4 DAT_005a93e4
extern uint32_t DAT_005a93e8;
#define _DAT_005a93e8 DAT_005a93e8
extern uint32_t DAT_005a93ec;
#define _DAT_005a93ec DAT_005a93ec
#define _DAT_005a94b0 DAT_005a94b0
extern uint32_t DAT_005a94b4;
#define _DAT_005a94b4 DAT_005a94b4
extern uint32_t DAT_005a94b8;
#define _DAT_005a94b8 DAT_005a94b8
extern uint32_t DAT_005a94bc;
#define _DAT_005a94bc DAT_005a94bc
#define _DAT_005a9550 DAT_005a9550
extern uint32_t DAT_005a9554;
#define _DAT_005a9554 DAT_005a9554
extern uint32_t DAT_005a9558;
#define _DAT_005a9558 DAT_005a9558
extern uint32_t DAT_005a955c;
#define _DAT_005a955c DAT_005a955c
extern uint32_t DAT_005ab4f8;
#define _DAT_005ab4f8 DAT_005ab4f8
extern uint32_t DAT_005ab888;
#define _DAT_005ab888 DAT_005ab888
extern uint32_t DAT_005ab8d8;
#define _DAT_005ab8d8 DAT_005ab8d8
extern uint32_t DAT_005ae340;
#define _DAT_005ae340 DAT_005ae340
extern uint32_t DAT_005ae738;
#define _DAT_005ae738 DAT_005ae738
extern uint32_t DAT_005ae7f4;
#define _DAT_005ae7f4 DAT_005ae7f4
extern uint32_t DAT_005ae7fc;
#define _DAT_005ae7fc DAT_005ae7fc
#define _DAT_005ae92c DAT_005ae92c
extern uint32_t DAT_0079361c;
#define _DAT_0079361c DAT_0079361c
extern uint32_t DAT_00f25884;
#define _DAT_00f25884 DAT_00f25884
extern uint32_t DAT_00f25888;
#define _DAT_00f25888 DAT_00f25888
extern uint32_t DAT_00f2588c;
#define _DAT_00f2588c DAT_00f2588c
extern uint32_t DAT_00f25890;
#define _DAT_00f25890 DAT_00f25890
extern uint32_t DAT_00f25894;
#define _DAT_00f25894 DAT_00f25894
extern uint32_t DAT_00f25898;
#define _DAT_00f25898 DAT_00f25898
extern uint32_t DAT_00f2589c;
#define _DAT_00f2589c DAT_00f2589c
extern uint32_t DAT_00f258a0;
#define _DAT_00f258a0 DAT_00f258a0
extern uint32_t DAT_00f25a30;
#define _DAT_00f25a30 DAT_00f25a30
extern uint32_t DAT_00f25a44;
#define _DAT_00f25a44 DAT_00f25a44
extern uint32_t DAT_00f25a48;
#define _DAT_00f25a48 DAT_00f25a48
extern uint32_t DAT_00f25a4c;
#define _DAT_00f25a4c DAT_00f25a4c
extern uint32_t DAT_00f25a50;
#define _DAT_00f25a50 DAT_00f25a50
extern uint32_t DAT_00f25a54;
#define _DAT_00f25a54 DAT_00f25a54
extern uint32_t DAT_00f25a58;
#define _DAT_00f25a58 DAT_00f25a58
extern uint32_t DAT_00f25a5c;
#define _DAT_00f25a5c DAT_00f25a5c
extern uint32_t DAT_00f25a60;
#define _DAT_00f25a60 DAT_00f25a60
extern uint32_t DAT_00f25a64;
#define _DAT_00f25a64 DAT_00f25a64
extern uint32_t DAT_00f25a68;
#define _DAT_00f25a68 DAT_00f25a68
extern uint32_t DAT_00f25a6c;
#define _DAT_00f25a6c DAT_00f25a6c
extern uint32_t DAT_00f25a70;
#define _DAT_00f25a70 DAT_00f25a70
extern uint32_t DAT_00f25a74;
#define _DAT_00f25a74 DAT_00f25a74
extern uint32_t DAT_00f25a78;
#define _DAT_00f25a78 DAT_00f25a78
#define _DAT_00f25a7c DAT_00f25a7c
extern uint32_t DAT_00f25a8c;
#define _DAT_00f25a8c DAT_00f25a8c
extern uint32_t DAT_00f25a90;
#define _DAT_00f25a90 DAT_00f25a90
extern uint32_t DAT_00f25a94;
#define _DAT_00f25a94 DAT_00f25a94
extern uint32_t DAT_00f25a98;
#define _DAT_00f25a98 DAT_00f25a98
#define _DAT_00f25a9c DAT_00f25a9c
extern uint32_t DAT_00f25aac;
#define _DAT_00f25aac DAT_00f25aac
extern uint32_t DAT_00f25ab8;
#define _DAT_00f25ab8 DAT_00f25ab8
#define _DAT_00f25ac0 DAT_00f25ac0
extern uint32_t DAT_00f25ac4;
#define _DAT_00f25ac4 DAT_00f25ac4
extern uint32_t DAT_00f25ac8;
#define _DAT_00f25ac8 DAT_00f25ac8
extern uint32_t DAT_00f25acc;
#define _DAT_00f25acc DAT_00f25acc
extern uint32_t DAT_00f25ad0;
#define _DAT_00f25ad0 DAT_00f25ad0
extern uint32_t DAT_00f25ad4;
#define _DAT_00f25ad4 DAT_00f25ad4
extern uint32_t DAT_00f25ad8;
#define _DAT_00f25ad8 DAT_00f25ad8
extern uint32_t DAT_00f25adc;
#define _DAT_00f25adc DAT_00f25adc
extern uint32_t DAT_00f25ae0;
#define _DAT_00f25ae0 DAT_00f25ae0
extern uint32_t DAT_00f25ae4;
#define _DAT_00f25ae4 DAT_00f25ae4
extern uint32_t DAT_00f25ae8;
#define _DAT_00f25ae8 DAT_00f25ae8
extern uint32_t DAT_00f25aec;
#define _DAT_00f25aec DAT_00f25aec
extern uint32_t DAT_00f25af0;
#define _DAT_00f25af0 DAT_00f25af0
extern uint32_t DAT_00f25af4;
#define _DAT_00f25af4 DAT_00f25af4
extern uint32_t DAT_00f25af8;
#define _DAT_00f25af8 DAT_00f25af8
extern uint32_t DAT_00f25afc;
#define _DAT_00f25afc DAT_00f25afc
extern uint32_t DAT_00f25ee8;
#define _DAT_00f25ee8 DAT_00f25ee8
extern uint32_t DAT_00f25eec;
#define _DAT_00f25eec DAT_00f25eec
extern uint32_t DAT_00f25ef0;
#define _DAT_00f25ef0 DAT_00f25ef0
extern uint32_t DAT_00f25ef4;
#define _DAT_00f25ef4 DAT_00f25ef4
extern const char s_CBuddy2_Timer_Receiving_Window_00557b74[];
extern const char s_CCommEngine_Notify_Window_00557b58[];
extern const char s___8s___12s__3dP__6dG_00556720[];
extern const char s___d__d__00555c88[];
extern const char s__d__s_00556ae8[];
extern const char s_ani__02d_00553b98[];
extern const char s_b_option_cancel_005569b0[];
extern const char s_b_option_confirm_00556988[];
extern const char s_b_option_exitgame_0055699c[];
extern const char s_b_play_team_00554114[];
extern const char s_b_slot_cancel_005540d0[];
extern const char s_b_slot_retry_005540ec[];
extern const char s_b_slot_use_005540e0[];
extern const char s_b_storewindow_cancel_00555a30[];
extern const char s_b_storewindow_cash_00555a48[];
extern const char s_b_storewindow_cashcharge_00555a70[];
extern const char s_b_storewindow_gold_00555a5c[];
extern const char s_b_storewindow_yes_00555a1c[];
extern const char s_bombblast_xes_00553cb8[];
extern const char s_bombflame_00553cc8[];
extern const char s_bullet10n_00553ec0[];
extern const char s_bullet10p_00553db4[];
extern const char s_bullet10s_00553eb4[];
extern const char s_bullet11n_00553ea8[];
extern const char s_bullet11p_00553da8[];
extern const char s_bullet11s_00553e9c[];
extern const char s_bullet12p_00553d9c[];
extern const char s_bullet13n_00553e90[];
extern const char s_bullet13p_00553d90[];
extern const char s_bullet13s_00553e84[];
extern const char s_bullet14p_00553d84[];
extern const char s_bullet15n_00553e78[];
extern const char s_bullet15p_00553d78[];
extern const char s_bullet15s_00553e6c[];
extern const char s_bullet16n_00553e60[];
extern const char s_bullet16p_00553d6c[];
extern const char s_bullet16s_00553e54[];
extern const char s_bullet1n_00553f80[];
extern const char s_bullet1p_00553e20[];
extern const char s_bullet1s_00553f74[];
extern const char s_bullet2p_00553e14[];
extern const char s_bullet3n_00553f68[];
extern const char s_bullet3p_00553e08[];
extern const char s_bullet3s_00553f5c[];
extern const char s_bullet4n_00553f50[];
extern const char s_bullet4p_00553dfc[];
extern const char s_bullet4s_00553f44[];
extern const char s_bullet5n_00553f38[];
extern const char s_bullet5p_00553df0[];
extern const char s_bullet5s_00553f2c[];
extern const char s_bullet6n_00553f20[];
extern const char s_bullet6p_00553de4[];
extern const char s_bullet6s_00553f14[];
extern const char s_bullet7n_00553f08[];
extern const char s_bullet7p_00553dd8[];
extern const char s_bullet7s_00553efc[];
extern const char s_bullet8n_00553ef0[];
extern const char s_bullet8p_00553dcc[];
extern const char s_bullet8s_00553ee4[];
extern const char s_bullet9n_00553ed8[];
extern const char s_bullet9p_00553dc0[];
extern const char s_bullet9s_00553ecc[];
extern const char s_bulletevent1_00553e38[];
extern const char s_bulletevent1p_00553d50[];
extern const char s_bulletitem_00553d14[];
extern const char s_caseblast_xes_00553c68[];
extern const char s_caseflame_00553c78[];
extern const char s_change_00555af0[];
extern const char s_cnormal_00555ae8[];
extern const char s_crystal_00553bfc[];
extern const char s_damage_00555cc0[];
extern const char s_dropbomb_00553cd4[];
extern const char s_dropcase_00553c84[];
extern const char s_drophammer_00553cac[];
extern const char s_emotion1_00555cb4[];
extern const char s_emotion_d_00555ca8[];
extern const char s_flame10_d_00553d44[];
extern const char s_flame123_00553cec[];
extern const char s_flame73_00553c04[];
extern const char s_flame_d3_00553d60[];
extern const char s_flame_d_d_00553e48[];
extern const char s_flameevent1_00553e2c[];
extern const char s_itemblast_xes_00553cf8[];
extern const char s_itemcase_00553c38[];
extern const char s_itemflame_00553d08[];
extern const char s_jflame_d_00555ff0[];
extern const char s_knightflame_00553d20[];
extern const char s_lightningblast_xes_00553c44[];
extern const char s_lightningflame_00553c58[];
extern const char s_rayonevent1_00553c20[];
extern const char s_rayonmine_00553c2c[];
extern const char s_shield_005562ec[];
extern const char s_shock_00553b80[];
extern const char s_special_005563c8[];
extern const char s_srayonmine_00553c0c[];
extern const char s_ssflame11_00554ae4[];
extern const char s_ssflame12_005549c8[];
extern const char s_ssflame13_005548d8[];
extern const char s_ssflame1_00555410[];
extern const char s_ssflame2_00555320[];
extern const char s_ssflame3_00555248[];
extern const char s_ssflame4_00555170[];
extern const char s_ssflame6_00554fc0[];
extern const char s_ssflame7_00554e94[];
extern const char s_ssflame8_00554dd0[];
extern const char s_ssflame9_00554ce4[];
extern const char s_teleport2_005543cc[];
/* Renamed from Ghidra's literal symbol names (s_map_set<T>_too_long_
 * 00551fec / s_invalid_map_set<T>_iterator_00552000) - the embedded
 * `<T>` from these MSVC STL assertion-message strings makes the
 * literal name invalid as a C identifier (the preprocessor sees `<`/
 * `>` as operators, not identifier characters). Real content
 * extracted directly from the binary, same as every other s_* string
 * - "map/set<T> too long" and "invalid map/set<T> iterator"
 * respectively. */
extern const char s_map_set_T_too_long_00551fec[];
extern const char s_invalid_map_set_T_iterator_00552000[];
/* Renamed from Ghidra's literal s_CCommP2P<>_Notify_Window_00557b34 -
 * the embedded `<>` makes the literal name invalid as a C identifier
 * (same reasoning as the map/set<T> strings above). Real content
 * extracted from the binary: "CCommP2P<> Notify Window". */
extern const char s_CCommP2P_Notify_Window_00557b34[];
/* Same <>-stripping rename as above: Ghidra's literal names embed <N>/
 * <T> from the MSVC STL assertion strings. Real content extracted
 * from the binary. */
extern const char s_invalid_bitset_N_position_00552c4c[];
extern const char s_vector_T_too_long_00557260[];
extern void *PTR_s_101blast_xes_0056d2b4;
extern void *PTR_s_11blast_xes_0056d290;
extern void *PTR_s_121blast_xes_0056d33c;
extern void *PTR_s_12blast_xes_0056d310;
extern void *PTR_s_142blast_xes_0056d344;
extern void *PTR_s_151blast_xes_0056d2c8;
extern void *PTR_s_72blast_xes_0056d2e8;
extern void *PTR_s_72blast_xes_0056d328;
extern void *PTR_s_92blast_xes_0056d2f0;
extern void *PTR_s_92blast_xes_0056d330;
