/* MSVC-side CRT/allocator/intrinsic shims for the full-tree MSVC link
 * attempt (tools/msvc-env/_link_attempt.sh). Counterpart of the
 * winegcc-only crt_shims_c.c: the raw ports call Ghidra's renamed CRT
 * symbols (_free, _rand, __stricmp, ...) and a handful of decompiler
 * pseudo-ops (CONCAT*, LOCK, fsin, ...). Under MSVC the source names
 * decorate to exactly the symbols the objects reference, so plain C
 * definitions suffice - no asm() labels like the GCC version needs.
 *
 * Everything forwards to the real CRT/Win32 where one exists; EH and
 * ATL helpers are minimal stubs sufficient for a functional link.
 * Compiled only into the MSVC link attempt (guarded by _MSC_VER). */
#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN /* keep mmsystem.h out: we define a cdecl
                             * timeGetTime below (a raw port declares it
                             * without the stdcall prototype) */
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <process.h>

/* --- Ghidra-renamed CRT (source `_x` -> symbol `__x`) --- */
void  _free(void *p)                          { free(p); }
void *_malloc(unsigned int n)                 { return malloc(n); }

/* operator new/delete: the raw ports call Ghidra's C-symbol `operator_new`/
 * `operator_delete` (not the C++ `??2`/`??3` mangling), so define them as plain
 * cdecl here. C++ operator new is malloc-plus-throw-on-failure and every raw
 * call site null-checks the result, so malloc/free are behaviorally correct.
 * Counterpart of crt_shims_c.c's winegcc versions (that file is __WINE__-only). */
void *operator_new(unsigned int size)         { return malloc(size); }
void  operator_delete(void *p)                { free(p); }
void *_realloc(void *p, unsigned int n)       { return realloc(p, n); }
int   _rand(void)                             { return rand(); }
long  _atol(const char *s)                    { return atol(s); }
long  _clock(void)                            { return (long)clock(); }
double _fabs(double x)                        { return fabs(x); }
double _pow(double a, double b)               { return pow(a, b); }
void *_memmove(void *d, const void *s, unsigned int n) { return memmove(d, s, n); }
char *_strncpy(char *d, const char *s, unsigned int n) { return strncpy(d, s, n); }
struct tm *_localtime(const time_t *t)        { return localtime(t); }
void  _qsort(void *b, unsigned int n, unsigned int w, int (*c)(const void *, const void *)) { qsort(b, n, w, c); }
unsigned int _strftime(char *b, unsigned int n, const char *f, const struct tm *t) { return (unsigned int)strftime(b, n, f, t); }

unsigned int _fwrite(const void *p, unsigned int s, unsigned int n, FILE *f) { return (unsigned int)fwrite(p, s, n, f); }
unsigned int _fread(void *p, unsigned int s, unsigned int n, FILE *f)        { return (unsigned int)fread(p, s, n, f); }
int   _fclose(FILE *f)                        { return fclose(f); }
int   _fseek(FILE *f, long o, int w)          { return fseek(f, o, w); }
long  _ftell(FILE *f)                         { return ftell(f); }

int _sprintf(char *buf, const char *fmt, ...)
{
    int r; va_list ap;
    va_start(ap, fmt); r = vsprintf(buf, fmt, ap); va_end(ap);
    return r;
}
/* MSVC 7.1 has no vsscanf; forwarding a fixed number of pointer-sized
 * slots covers every raw-port call site (max seen: 4 outputs). */
int _sscanf(const char *buf, const char *fmt, ...)
{
    void *a[8]; int i; va_list ap;
    va_start(ap, fmt);
    for (i = 0; i < 8; i++) a[i] = va_arg(ap, void *);
    va_end(ap);
    return sscanf(buf, fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
}

/* --- Ghidra double-underscore names (source `__x` -> symbol `___x`);
 *     forward to the real single-underscore CRT function --- */
int    __stricmp(const char *a, const char *b)                      { return _stricmp(a, b); }
int    __strnicmp(const char *a, const char *b, unsigned int n)     { return _strnicmp(a, b, n); }
int    __mbscmp(const unsigned char *a, const unsigned char *b)     { return strcmp((const char *)a, (const char *)b); }
int    __mbsicmp(const unsigned char *a, const unsigned char *b)    { return _stricmp((const char *)a, (const char *)b); }
int    __memicmp(const void *a, const void *b, unsigned int n)      { return _memicmp(a, b, n); }
char  *__itoa(int v, char *buf, int radix)                          { return _itoa(v, buf, radix); }
FILE  *__fsopen(const char *p, const char *m, int sh)               { (void)sh; return fopen(p, m); }
void   __dosmaperr(unsigned long e)                                 { (void)e; }
unsigned long __beginthread(void (*f)(void *), unsigned int stack, void *arg) { return _beginthread(f, stack, arg); }
void   __endthread(void)                                            { _endthread(); }
unsigned __int64 __aulldiv(unsigned __int64 a, unsigned __int64 b)  { return b ? a / b : 0; }
void   __CxxThrowException_8(void *obj, void *info)                 { (void)obj; (void)info; /* no C++ EH here */ }

/* --- EH vector iterators / exception object helpers (stubs) --- */
void  _eh_vector_constructor_iterator_() {}
void  _eh_vector_destructor_iterator_()  {}
void *exception__ctor(void *thisp, void *arg) { (void)arg; return thisp; }
void  exception__dtor(void *thisp)            { (void)thisp; }

/* --- ATL helper --- */
void *ATL_CAtlBaseModule_GetHInstanceAt(int i) { (void)i; return 0; }

/* --- Ghidra decompiler pseudo-ops (function form, for the few TUs
 *     that don't include ghidra_intrinsics.h's macro versions) --- */
unsigned short CONCAT11(unsigned int hi, unsigned int lo) { return (unsigned short)(((hi & 0xff) << 8) | (lo & 0xff)); }
unsigned int   CONCAT13(unsigned int hi, unsigned int lo) { return ((hi & 0xff) << 24) | (lo & 0xffffff); }
unsigned int   CONCAT22(unsigned int hi, unsigned int lo) { return ((hi & 0xffff) << 16) | (lo & 0xffff); }
unsigned int   CONCAT31(unsigned int hi, unsigned int lo) { return ((hi & 0xffffff) << 8) | (lo & 0xff); }
void LOCK(void)   {}
void UNLOCK(void) {}

/* --- x87 float intrinsics (Ghidra names) --- */
double fsin(double x)  { return sin(x); }
double fcos(double x)  { return cos(x); }
double fptan(double x) { return tan(x); }
double SQRT(double x)  { return sqrt(x); }
double FID_conflict__cos(double x) { return cos(x); } /* Ghidra-renamed cos */

/* --- Startup hook: initialize the static CRITICAL_SECTIONs ---
 * WinMain's first act is EnterCriticalSection(&DAT_005a9068); in the
 * original binary a C++ static initializer set these up. Our ports
 * lost that, so register an initializer in the CRT's C-init table
 * (.CRT$XCU) - libcmt runs it before WinMain. Storage lives in
 * src/globals_sized.c. */
extern unsigned char DAT_005a9068[24], DAT_005a9084[24], DAT_00e9af44[24];
/* XFS archive singletons (src/globals_sized.c). The original binary
 * constructed these with hFile=-1 via a C++ static initializer; the
 * bring-up build sets it here so OpenXFSArchive will open them instead
 * of early-returning "already open". Offset 0x1040 = XFS_OFF_HFILE. */
extern unsigned char g_graphicsArchive[], g_xfsScratch[];
/* Flat-ButtonWidget registry roots (src/globals.c) - each is its own
 * embedded circular-list sentinel node. Every reader (FindActiveObjectAt's
 * mouse-hit-test family, SweepActiveObjectRegistry, DrawActiveObjectRegistry, FUN_004f2fb0's
 * insert, InvokeWidget - see globals.c's comment for the full list)
 * dereferences `*(registryRoot+4)` unconditionally with no null-check,
 * so an all-zero registry faults on the very first WM_MOUSEMOVE/
 * ChangeGameState before a single widget is ever created. The original
 * binary never writes these fields anywhere in .text either (confirmed
 * exhaustively via Ghidra's own cross-reference table - every direct
 * reference to this memory is a READ), so construction must happen via
 * a real C++ static initializer we don't have a raw port of; this hook
 * reproduces its necessary effect. Self-referencing every link field
 * (+4 key/head, +0xc/+0x10 inner prev/next, +0x18/+0x1c outer prev/
 * next) to the registry's own address makes an empty registry behave
 * exactly like Windows' LIST_ENTRY InitializeListHead: pointer-equality
 * termination (FindActiveObjectAt/SweepActiveObjectRegistry) sees next==head immediately,
 * and sorted-key termination (InvokeWidget, FUN_004f2f00's insert
 * search) sees the registry's own address read back as a node "key" -
 * a huge value versus any real widget id, so it always compares
 * greater and the search stops there too. Confirmed analytically
 * against InvokeWidget.c's already-fixed traversal (same idiom). */
static void gb_init_widget_registry(unsigned char *registry)
{
    *(int *)(registry + 0x04) = (int)registry;
    *(int *)(registry + 0x0c) = (int)registry;
    *(int *)(registry + 0x10) = (int)registry;
    *(int *)(registry + 0x18) = (int)registry;
    *(int *)(registry + 0x1c) = (int)registry;
}
extern unsigned char DAT_00e9be90[0x20], DAT_00e9c0fc[0x20], DAT_00ea0e18[0x20];
/* g_uiPanelManager (0xe53c40) - a genuine CPanelManager object, unlike
 * the three registries above (its list head/tail are meant to start
 * NULL, not self-referencing). Real field layout decompiled from its
 * own constructor (FUN_00507dc0, .CRT$XCU-registered) - see globals.c's
 * comment for the full breakdown. Only the grow-count seed at +0x18
 * needs an explicit non-zero init (=10, the constructor's own literal);
 * every other field the constructor sets is already 0, matching BSS. */
extern unsigned char g_uiPanelManager[0x1c];
static void gb_init_panel_manager(unsigned char *manager)
{
    *(int *)(manager + 0x18) = 10;
}
/* DAT_00e53e88 (chat-log/replay object, ~25 raw-ported callers - see
 * globals.c) uses the identical +4 head/+0x1c outer-next embedded-
 * sentinel-list shape as the three registries above: FUN_004022b0.c's
 * own recovered list-walk (`*(objBase+4)`, `iVar2+0x1c`) matches this
 * function's offsets exactly. Same treatment - self-referencing sentinel
 * init makes an empty list terminate immediately instead of dereferencing
 * zeroed BSS (`*(int*)(0+0x1c)`) the first time GameTick runs it. */
extern unsigned char DAT_00e53e88[0xf28];
/* KNOWN DIVERGENCE alias (src/globals.c): Ghidra split registry1's +4 head
 * pointer into its own uint32_t global instead of aliasing DAT_00e9be90+4, so
 * gb_init_widget_registry's write to the array never reaches it. Readers that
 * begin their list walk from this global rather than from the array base -
 * FUN_0041b6f0 does exactly that, `*(DAT_00e9be94 + 0x1c)` every tick - would
 * deref NULL. Point it at the registry base, the same value the +4 sentinel
 * field holds, so the walk enters the (empty, self-terminating) list. The
 * remaining split globals (DAT_00e9be98/9c/a0/a4 bytes, DAT_00e9c104/08) are
 * flag/focus fields, not node pointers, and correctly stay zero. */
extern unsigned int DAT_00e9be94;
/* Same KNOWN DIVERGENCE alias as DAT_00e9be94, for the global sprite
 * registry (DAT_00ea0e18): DAT_00ea0e1c is Ghidra's split-out copy of its +4
 * head pointer. ~40 raw-ported files (LoadAvatarSprites, ComposeAvatarSprites,
 * every State*_OnExit/ActiveObjects_DestroyBucket, DrawWindGauge, State11's
 * RenderHud, etc.) read `*(int *)(DAT_00ea0e1c + 0x1c)` directly, entering the
 * list from this global rather than the array base - left NULL, every one of
 * those would deref NULL+0x1c the first time any of them ran. */
extern unsigned int DAT_00ea0e1c;
extern unsigned int DAT_005b1444;

/* BlitSprite16bpp/BlitSpriteClipped's clip bounds. Confirmed via exhaustive
 * whole-binary disassembly search that ALL FOUR of these addresses are
 * written ONLY inside SetClipRect (0x4eadb0) - no other instruction in the
 * entire original .text writes them, and none of SetClipRect's ~25 real
 * call sites (all inside later UI: wind gauge, ready-room roster/status,
 * in-battle HUD, room list) are reachable during the logo screen (states
 * 5/6) or anywhere in InitGame/WinMain's startup path. Left at their BSS
 * zero-init default, State06_Logo2_Render's blit clips to a single visible
 * row (empirically confirmed live: DAT_0056df34=0 makes
 * `local_4 = (DAT_0056df34 - y) + 1` evaluate to 1 for y=0) instead of the
 * full 600-row logo image - the actual root cause of the black window
 * surviving even after LockBackBuffer/FindSpriteFrame/the blit call chain
 * and the present-frame RECT (see g_presentDstRect) were all confirmed
 * correct. The real original call site that establishes these before the
 * first logo render was NOT found (plausibly something in the .NET
 * Launcher-driven startup path this bring-up doesn't reproduce) - these are
 * empirically the right full-screen values (0,799 / 0,599), matching both
 * the 800x600 canvas everywhere else in this codebase (e.g. InitGame.c's
 * DAT_00e53c24 family) and SetClipRect's own >=800/>=600 fallback constants
 * (0x31f=799, 0x257=599). */
extern unsigned int DAT_00793530, DAT_0056df30, DAT_00793534, DAT_0056df34;

/* g_clientContext - see globals.h's own comment: a ~1MB+ arena built by
 * FUN_00415d40, whose only real caller (orig 0x540d30) is a tiny wrapper
 * with no other callers in the whole binary - almost certainly a hidden
 * CRT-level global-object static initializer (the same role this file's
 * own gb_init_cs_entry/.CRT$XCU hook plays), never reached by anything
 * Ghidra decompiled as regular WinMain/InitGame flow, so g_clientContext
 * stayed NULL for the entire bring-up. Confirmed live: GameTick's own
 * PeekPacketChecksumBool call sites (g_clientContext+0x6aa678,
 * +0x23310) crashed reading off a NULL-based address.
 *
 * NOT calling the real FUN_00415d40 here (484 lines, several more
 * unverified helper calls, C++ array-construction reflection
 * (_eh_vector_constructor_iterator_) - too much new untested surface for
 * a bring-up scaffold fix). Instead: give g_clientContext a real, safely
 * zeroed buffer sized past every offset referenced anywhere in the
 * ported tree (max seen: 0x6aa678), so every `g_clientContext + offset`
 * site across the whole codebase reads/writes real memory instead of
 * faulting. Additionally pre-seed the 2 GuardedBool cells GameTick
 * reads unconditionally every tick (see PeekPacketChecksumBool.c) with a
 * valid all-false encoding (checksum = byte0+byte1-0x34; {0,0x34,0}
 * satisfies that with bit0 of byte1 clear) so those two specific reads
 * don't spuriously trip g_valueGuardTamperFlag - this is exactly what
 * FUN_00415d40 itself does for the 0x23310 cell (see its own body,
 * lines ~444-450), just without running the rest of that function.
 * Real per-player CValueGuard cells (g_clientContext+0xebef4, see
 * ValueGuard.h) and everything else in the arena stay zeroed - not
 * needed for the bring-up's logo/title/server-select path. */
extern unsigned int g_clientContext;
#define GB_CLIENT_CONTEXT_ARENA_SIZE 0x700000u

static void gb_init_client_context(void)
{
    unsigned char *arena = (unsigned char *)calloc(1, GB_CLIENT_CONTEXT_ARENA_SIZE);
    if (arena == NULL) return;
    g_clientContext = (unsigned int)(void *)arena;
    arena[0x6aa678] = 0;
    arena[0x6aa679] = 0x34;
    arena[0x6aa67a] = 0;
    arena[0x23310] = 0;
    arena[0x23311] = 0x34;
    arena[0x23312] = 0;
}

/* ATL::CAtlStringMgr reconstruction (real, documented VS2003 ATL library
 * object - see globals.c's DAT_005b1444 comment; Ghidra function-signature-
 * matched src/unnamed/msvc_crt_atl/FUN_00520037.c/FUN_0052009c.c against the
 * real library). Every raw-ported call site invokes vtable slot 0xc
 * (GetNilString()) with zero pushed arguments and no ECX/"this" setup (a
 * dropped-register artifact shared by all ~8 call sites), so these
 * implementations are written to be self-sufficient - they operate on the
 * single hardcoded g_atlNilStringData singleton below rather than reading an
 * implicit "this", exactly reproducing GetNilString()'s real behavior
 * (AddRef the nil string, return it). Allocate/Reallocate/Clone match the
 * real ATL signatures for correctness if a future fix un-drops
 * LoadLocalizedStrings and real lookups start allocating; nothing in the
 * bring-up path reaches them today - the string table stays empty
 * (LoadLocalizedStrings is dropped for bring-up, see bringup_drop.txt), so
 * every GetLocalizedString() lookup takes the nil-string fallback. CStringData
 * layout (confirmed against FUN_0052009c.c's field writes): pStringMgr@+0,
 * nDataLength@+4, nAllocLength@+8, nRefs@+0xc, character data at +0x10. */
static unsigned int g_atlNilStringData[4 + 2];  /* header + 2 zeroed WCHARs */
static void *PTR_Allocate_00544b38[5];

static void *gb_atl_allocate(int nAllocLength, int nCharSize)
{
    unsigned int total = (unsigned int)(nAllocLength + 1) * (unsigned int)nCharSize;
    unsigned int *data = (unsigned int *)malloc(0x10 + total);
    if (data == NULL) return NULL;
    data[0] = (unsigned int)(void *)g_atlNilStringData;   /* pStringMgr - informational only */
    data[1] = 0;                          /* nDataLength */
    data[2] = (unsigned int)nAllocLength; /* nAllocLength */
    data[3] = 1;                          /* nRefs */
    return data;
}

static void gb_atl_free(void *pData)
{
    if (pData == g_atlNilStringData) return;   /* never free the immortal nil string */
    free(pData);
}

static void *gb_atl_reallocate(void *pData, int nAllocLength, int nCharSize)
{
    unsigned int total = (unsigned int)(nAllocLength + 1) * (unsigned int)nCharSize;
    unsigned int *data = (unsigned int *)realloc(pData, 0x10 + total);
    if (data == NULL) return NULL;
    data[2] = (unsigned int)nAllocLength;
    return data;
}

static void *gb_atl_get_nil_string(void)
{
    InterlockedIncrement((LONG *)&g_atlNilStringData[3]);
    return g_atlNilStringData;
}

static void *gb_atl_clone(void)
{
    return PTR_Allocate_00544b38;   /* single shared instance */
}

static void gb_init_atl_string_mgr(void)
{
    PTR_Allocate_00544b38[0] = (void *)gb_atl_allocate;
    PTR_Allocate_00544b38[1] = (void *)gb_atl_free;
    PTR_Allocate_00544b38[2] = (void *)gb_atl_reallocate;
    PTR_Allocate_00544b38[3] = (void *)gb_atl_get_nil_string;
    PTR_Allocate_00544b38[4] = (void *)gb_atl_clone;
    g_atlNilStringData[0] = (unsigned int)(void *)g_atlNilStringData;
    g_atlNilStringData[3] = 2;   /* nRefs starts at 2, matching real ATL - see globals.c */
    DAT_005b1444 = (unsigned int)(void *)PTR_Allocate_00544b38;
}

static void gb_startup_init(void)
{
    InitializeCriticalSection((LPCRITICAL_SECTION)DAT_005a9068);
    InitializeCriticalSection((LPCRITICAL_SECTION)DAT_005a9084);
    InitializeCriticalSection((LPCRITICAL_SECTION)DAT_00e9af44);
    gb_init_atl_string_mgr();
    *(int *)(g_graphicsArchive + 0x1040) = (int)0xffffffff;
    *(int *)(g_xfsScratch     + 0x1040) = (int)0xffffffff;
    gb_init_widget_registry(DAT_00e9be90);
    gb_init_widget_registry(DAT_00e9c0fc);
    gb_init_widget_registry(DAT_00ea0e18);   /* global sprite registry - same container */
    gb_init_widget_registry(DAT_00e53e88);   /* chat-log/replay object - same container */
    gb_init_panel_manager(g_uiPanelManager);
    DAT_00e9be94 = (unsigned int)DAT_00e9be90;
    DAT_00ea0e1c = (unsigned int)DAT_00ea0e18;
    DAT_00793530 = 0;
    DAT_0056df30 = 799;
    DAT_00793534 = 0;
    DAT_0056df34 = 599;
    gb_init_client_context();
}
/* data_seg, NOT #pragma section(...,read): VC7.1's linker keeps a
 * read-only .CRT$XCU out of the read-write .CRT group libcmt walks in
 * _cinit, so the hook silently never runs (verified empirically). */
#pragma data_seg(".CRT$XCU")
static void (*gb_init_cs_entry)(void) = gb_startup_init;
#pragma data_seg()

/* --- Win32 calls a raw port declares without the stdcall prototype
 *     (so the object references the cdecl symbol) --- */
/* Forward to winmm's REAL timeGetTime (stdcall _timeGetTime@0), resolved once
 * via GetProcAddress since this cdecl shim can't link against the decorated
 * import directly. GetTickCount() is NOT a substitute: it has coarser
 * resolution and under some wine prefixes barely advances, freezing the
 * GameTick 50 ms timer - the game stalled forever at Logo2 (uVar10 stayed 0,
 * confirmed by probe: 6 ms of GetTickCount over 320 ticks). winmm's own
 * timer advances correctly there. */
unsigned long timeGetTime(void)
{
    typedef unsigned long (__stdcall *fn_t)(void);
    static fn_t real;
    if (real == 0) {
        HMODULE h = LoadLibraryA("winmm.dll");
        if (h) real = (fn_t)GetProcAddress(h, "timeGetTime");
        if (real == 0) return GetTickCount();
    }
    return real();
}
void *ShellExecuteA(void *hwnd, const char *op, const char *file,
                    const char *params, const char *dir, int show)
{
    typedef void *(__stdcall *fn_t)(void *, const char *, const char *,
                                    const char *, const char *, int);
    HMODULE h = LoadLibraryA("shell32.dll");
    fn_t fn = h ? (fn_t)GetProcAddress(h, "ShellExecuteA") : 0;
    return fn ? fn(hwnd, op, file, params, dir, show) : 0;
}
#endif /* _MSC_VER */
