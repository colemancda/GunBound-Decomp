/* CState01Title - Title screen methods, promoted from the raw C ports
 * src/state_machine/State01_Title_OnEnter.c (0x4e5370) and
 * State01_Title_OnExit.c (0x4e53a0). See src/cxx/README.md.
 *
 * The raw OnEnter port was already byte-compared against the original
 * (see its header comment): Ghidra typed it __fastcall(int) because a
 * __thiscall method with no extra arguments is register-identical
 * (this/param_1 in ECX) - as a real C++ member function the convention
 * is finally exact, decoration included.
 *
 * Dependencies on not-yet-promoted code stay as extern "C" declarations
 * against the raw-port symbols (functions.h's K&R prototypes can't be
 * included from C++ - an empty () means zero-args here). FUN_004f1790's
 * true convention is suspect (see the OnEnter raw port's byte-comparison
 * notes: the original never cleans the stack after it, so it's likely
 * callee-cleans with more real parameters); declared minimally here, to
 * be revisited when FUN_004f1790 itself is promoted.
 */
#include "GameState.h"

extern "C" {
int PlayMusicTrack(int trackId);              /* 0x4f2e40-family; raw decl: uint PlayMusicTrack() */
int __stdcall FUN_004f1790(void *container, int key);
                                              /* active-object container lookup/prep. __stdcall here
                                               * (diverging from the raw C decl): the original's
                                               * OnEnter does NOT clean the stack after this call -
                                               * byte-compared at 0x4e5383. It also loads 0x5572cc
                                               * into EAX and 0x5572c0 into EDI first (register args
                                               * of a custom convention, or values the callee reads)
                                               * - not expressible from C++; still the one residual
                                               * byte difference, pending FUN_004f1790's own
                                               * decompile (same open item as the raw port's). */
extern unsigned char DAT_00ea0e18;            /* active-object container storage */
extern unsigned int  DAT_00ea0e1c;            /* active-object container (list head ptr at +0x1c) */
}

/* 0x4e5370 - reset the frame counter, start the title music, and prime
 * the active-object container bucket 10000 (the title screen's widgets
 * register under that key; OnExit destroys the same bucket). */
void CState01Title::OnEnter()
{
    FUN_004f1790(&DAT_00ea0e18, 10000);
    m_frameCounter = 0;
    PlayMusicTrack(0);
}

/* 0x4e53a0 - walk the active-object container's bucket list to key
 * 10000 and run every registered object's destructor (vtable slot 0,
 * flag 1 = free), then reset the bucket's intrusive list to empty.
 * Raw port kept the container untyped (undefined4*), and so does this
 * promotion - the container classes aren't reconstructed yet. */
void CState01Title::OnExit()
{
    unsigned int **bucket = *(unsigned int ***)(DAT_00ea0e1c + 0x1c);
    unsigned int key = (unsigned int)bucket[1];
    if (key < 0x2711) {
        while (key != 10000) {
            bucket = (unsigned int **)bucket[7];
            key = (unsigned int)bucket[1];
            if (10000 < key) {
                return;
            }
        }
        unsigned int **node = (unsigned int **)bucket[4];
        while (node != bucket) {
            unsigned int **obj = (unsigned int **)*node;
            node = (unsigned int **)node[4];
            /* obj->vtable[0](1): scalar-deleting destructor, free=1.
             * Truly __thiscall (this=obj in ECX); expressed like the raw
             * port's code* call until the container's element class is
             * reconstructed and this becomes a real virtual call. */
            ((void (__cdecl *)(int))*obj)(1);
        }
        bucket[3] = (unsigned int *)bucket;
        bucket[4] = (unsigned int *)bucket;
    }
}
