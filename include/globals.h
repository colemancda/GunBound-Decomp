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
extern void *g_gameStateVTableArray[16];
#define g_gameStateObjects g_gameStateVTableArray
extern void *g_hDDrawDll;
/* void ** rather than void *: raw-ported call sites dereference these
 * once to reach the COM vtable pointer (`*g_pD3DDevice7 + offset`), so
 * they need to be a pointer-to-pointer to compile - a plain void*
 * can't be dereferenced at all. */
extern void **g_pBackBufferSurface;
extern void **g_pClipper;
extern void **g_pD3DDevice7;
extern void **g_pDirect3D7;
extern void **g_pDirectDraw7;
extern void **g_pPrimarySurface;
extern void **g_pZBufferSurface;
extern uint8_t g_replayEventBuffer;
extern uint32_t g_replayEventCursor;
extern uint8_t g_replayFileHandle;
extern float g_sineTable360[360];
extern uint8_t g_spriteVertexBuffer[0x10000];
extern uint32_t g_spriteVertexCount;
extern uint32_t g_stateChangeInProgress;
extern uint8_t g_stateChangeRequested;

/* --- Generic globals (unnamed, type inferred from Ghidra only) --- */

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
extern uint8_t DAT_005573c8;
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
extern uint32_t DAT_0056d10c;
extern uint32_t DAT_0056d110;
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
extern uint16_t DAT_0056dc40;
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
extern uint8_t DAT_00588f50;
#define _DAT_00588f50 DAT_00588f50
extern uint8_t DAT_00588f54;
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
extern uint32_t DAT_005b1444;
extern uint32_t DAT_005b15ac;
extern uint32_t DAT_005b1c48;
extern uint32_t DAT_005b1c4c;
extern uint8_t DAT_005b1c70;
extern uint8_t DAT_005b1cf0;
extern uint32_t DAT_005b1d70;
extern uint8_t DAT_005b1da2;
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
extern uint32_t DAT_005b3484;
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
extern uint8_t DAT_006773b4;
#define _DAT_006773b4 DAT_006773b4
extern uint8_t DAT_006773b8;
#define _DAT_006773b8 DAT_006773b8
extern uint8_t DAT_006773bc;
#define _DAT_006773bc DAT_006773bc
extern uint8_t DAT_006773c0;
#define _DAT_006773c0 DAT_006773c0
extern uint32_t DAT_00677544;
extern uint32_t DAT_006777e8;
extern uint32_t DAT_006790c0;
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
extern uint32_t DAT_006990c0;
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
extern uint8_t DAT_006a7710;
extern uint8_t DAT_006a7714;
extern uint8_t DAT_006a7718;
extern uint8_t DAT_006a771c;
extern uint8_t DAT_006a7720;
extern uint8_t DAT_006a7724;
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
extern uint8_t DAT_006b90f8;
#define _DAT_006b90f8 DAT_006b90f8
extern uint32_t DAT_006b9100;
extern uint8_t DAT_006ba1fc;
extern uint8_t DAT_006ba244;
extern uint32_t DAT_00792190;
extern uint8_t DAT_00792194;
#define _DAT_00792194 DAT_00792194
extern uint8_t DAT_00792198;
#define _DAT_00792198 DAT_00792198
extern uint32_t DAT_007921b0;
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
extern uint32_t DAT_00793504;
extern uint8_t DAT_0079350c;
extern uint8_t DAT_0079350d;
extern uint32_t DAT_00793510;
extern uint8_t DAT_00793514;
extern uint8_t DAT_00793515;
extern uint8_t DAT_00793516;
extern uint8_t DAT_00793517;
extern uint8_t DAT_00793518;
#define _DAT_00793518 DAT_00793518
extern uint8_t DAT_0079351c;
#define _DAT_0079351c DAT_0079351c
extern uint8_t DAT_00793520;
extern uint8_t DAT_00793521;
extern uint8_t DAT_00793522;
extern uint8_t DAT_00793529;
extern uint8_t DAT_0079352a;
extern uint32_t DAT_0079352c;
extern uint32_t DAT_00793530;
extern uint32_t DAT_00793534;
extern uint32_t DAT_00793544;
extern uint8_t DAT_00793549;
extern uint8_t DAT_0079354a;
extern uint8_t DAT_0079354b;
extern uint32_t DAT_0079354c;
extern uint32_t DAT_00793550;
extern void *DAT_00793554[16]; /* used as an array of pointers by InitGame - see src/entry/InitGame.c */
extern uint32_t DAT_00793558;
extern uint32_t DAT_0079355c;
extern uint32_t DAT_00793560;
extern uint8_t DAT_00793568;
extern uint32_t DAT_007935e8;
extern uint32_t DAT_007935ec;
extern uint8_t DAT_00793610;
extern uint8_t DAT_00793611;
extern uint32_t DAT_00793614;
extern uint8_t DAT_00793618;
#define _DAT_00793618 DAT_00793618
extern uint32_t DAT_00793634;
extern uint32_t DAT_00793640;
extern uint32_t DAT_0079364c;
extern uint32_t DAT_0079365c;
extern uint32_t DAT_00793660;
extern uint8_t DAT_00793664;
extern uint32_t DAT_0079376c;
extern uint8_t DAT_00793770;
extern uint32_t DAT_00793774;
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
extern uint8_t DAT_00796eec;
extern uint8_t DAT_007a7660;
#define _DAT_007a7660 DAT_007a7660
extern uint32_t DAT_007a7674;
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
extern uint8_t DAT_00e53c24;
#define _DAT_00e53c24 DAT_00e53c24
extern uint8_t DAT_00e53c28;
#define _DAT_00e53c28 DAT_00e53c28
extern uint8_t DAT_00e53c2c;
#define _DAT_00e53c2c DAT_00e53c2c
extern uint8_t DAT_00e53c30;
#define _DAT_00e53c30 DAT_00e53c30
extern uint8_t DAT_00e53c3c;
extern uint8_t DAT_00e53c40;
extern uint32_t DAT_00e53c44;
extern uint32_t DAT_00e53c48;
extern uint8_t DAT_00e53e88;
extern uint8_t DAT_00e55a45;
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
extern uint8_t DAT_00e9be90;
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
extern uint8_t DAT_00e9c0fc;
extern uint32_t DAT_00e9c104;
extern uint8_t DAT_00e9c108;
#define _DAT_00e9c108 DAT_00e9c108
extern uint32_t DAT_00e9c33c;
extern uint8_t DAT_00e9c344;
extern uint8_t DAT_00e9c348;
extern uint32_t DAT_00e9c9c8;
extern uint32_t DAT_00e9c9cc;
extern uint8_t DAT_00e9c9d0;
extern uint32_t DAT_00e9c9dc;
extern uint32_t DAT_00e9c9e0;
extern uint8_t DAT_00ea0e18;
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
extern uint8_t DAT_00f11dd0;
extern uint32_t DAT_00f11dd4;
extern uint8_t DAT_00f11de0;
#define _DAT_00f11de0 DAT_00f11de0
extern uint8_t DAT_00f12e14;
extern uint8_t DAT_00f12e18;
extern uint8_t DAT_00f22504;
extern uint32_t DAT_00f22650;
extern uint8_t DAT_00f23650;
#define _DAT_00f23650 DAT_00f23650
extern uint8_t DAT_00f23654;
#define _DAT_00f23654 DAT_00f23654
extern uint8_t DAT_00f23658;
#define _DAT_00f23658 DAT_00f23658
extern uint8_t DAT_00f2465c;

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
extern const char s_b_error_confirm_00552238[];
extern const char s_b_gamelist_avatar_00553760[];
extern const char s_b_gamelist_buddy_00553788[];
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
extern void *PTR_DAT_00563b40;
extern void *PTR_DAT_00568180;
extern void *PTR_DAT_00568800;
extern void *PTR_DAT_00568810;
extern void *PTR_DAT_0056d460;
extern void *PTR_DAT_0058b248;
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
extern void *PTR_FUN_005572e8;
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
extern void *PTR_LAB_00553fb0;
extern void *PTR_LAB_00553ff8;
extern void *PTR_LAB_00554000;
extern void *PTR_LAB_005572e0;
extern void *PTR_LAB_00557434;
extern void *PTR_LAB_005574cc;
extern void *PTR_LAB_005574e0;
extern void *PTR_LAB_005574e8;
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

#endif
