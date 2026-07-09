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
 */
#include "GameState.h"
#include "ActiveObjects.h"

extern "C" {
int PlayMusicTrack(int trackId);              /* 0x4f2e40-family; raw decl: uint PlayMusicTrack() */
int __stdcall LoadSpriteSet(void *container, int key);
                                              /* RESOLVED: the sprite-set loader. Takes the .img
                                               * name in EAX ("titlemode.img" here - it registers
                                               * one frame object per frame under `key`) and the
                                               * music name in EDI ("title.mp3"), plus these two
                                               * callee-cleaned stack args. The EAX/EDI loads are
                                               * the only remaining byte-diff in OnEnter - not
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
    PlayMusicTrack(0);
}

/* 0x4e53b0 - destroy container bucket 10000 (the title screen's
 * sprite set); the walk is the shared ActiveObjects_DestroyBucket
 * inline, which every state OnExit inlines identically. */
void CState01Title::OnExit()
{
    ActiveObjects_DestroyBucket(10000);
}
