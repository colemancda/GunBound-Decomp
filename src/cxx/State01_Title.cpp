/* CState01Title - Title screen methods, promoted from the raw C ports
 * src/state_machine/State01_Title_OnEnter.c (0x4e5370) and
 * State01_Title_OnExit.c (0x4e53b0). See src/cxx/README.md.
 *
 * The raw OnEnter port was already byte-compared against the original
 * (see its header comment): Ghidra typed it __fastcall(int) because a
 * __thiscall method with no extra arguments is register-identical
 * (this/param_1 in ECX) - as a real C++ member function the convention
 * is finally exact, decoration included.
 *
 * Dependencies on not-yet-promoted code stay as extern "C" declarations
 * against the raw-port symbols (functions.h's K&R prototypes can't be
 * included from C++ - an empty () means zero-args here). LoadSpriteSet's
 * true convention is suspect (see the OnEnter raw port's byte-comparison
 * notes: the original never cleans the stack after it, so it's likely
 * callee-cleans with more real parameters); declared minimally here, to
 * be revisited when LoadSpriteSet itself is promoted.
 *
 * FIXED (2026-07-13): PlayMusicTrack's declaration here was previously
 * `int PlayMusicTrack(int trackId)` with a stray "0x4f2e40-family" note -
 * that address is an unrelated object constructor (confirmed via
 * decompile: it initializes a vtable pointer and a linked list, nothing
 * to do with audio), and the 1-argument signature doesn't match the
 * real PlayMusicTrack at 0x4eea30 either. Since both are plain cdecl
 * (no name mangling), the old declaration would have linked against the
 * real 2-argument PlayMusicTrack and silently read garbage for the
 * missing 2nd stack slot. PlayMusicTrack's real signature is
 * `uint PlayMusicTrack(uint status, byte *trackName)` (see
 * src/unnamed/PlayMusicTrack.c) - a normal 2-argument cdecl function
 * once its own dropped-register bug was fixed, so no custom-convention
 * workaround is needed here. Call site now matches
 * State01_Title_OnEnter.c's own `PlayMusicTrack(0,"title.mp3")`.
 */
#include "GameState.h"
#include "ActiveObjects.h"

extern "C" {
unsigned int PlayMusicTrack(unsigned int status, const char *trackName);
int __stdcall LoadSpriteSet(void *container, int key);
                                              /* RESOLVED: the sprite-set loader. Takes the .img
                                               * name in EAX ("titlemode.img" here - it registers
                                               * one frame object per frame under `key`) and the
                                               * music name in EDI ("title.mp3"), plus these two
                                               * callee-cleaned stack args. The EAX load is the
                                               * only remaining byte-diff in OnEnter - not
                                               * expressible from C++ without the custom
                                               * convention. */
}

/* 0x4e5370 - reset the frame counter, start the title music, and prime
 * the active-object container bucket 10000 (the title screen's widgets
 * register under that key; OnExit destroys the same bucket). */
void CState01Title::OnEnter()
{
    LoadSpriteSet(&DAT_00ea0e18, 10000);
    m_frameCounter = 0;
    PlayMusicTrack(0, "title.mp3");
}

/* 0x4e53b0 - destroy container bucket 10000 (the title screen's
 * sprite set); the walk is the shared ActiveObjects_DestroyBucket
 * inline, which every state OnExit inlines identically. */
void CState01Title::OnExit()
{
    ActiveObjects_DestroyBucket(10000);
}
