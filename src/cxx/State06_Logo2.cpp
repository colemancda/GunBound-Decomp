/* CState06Logo2 - second logo screen, promoted from the raw C ports
 * State06_Logo2_OnEnter.c (0x443280) / State06_Logo2_OnExit.c
 * (0x4432c0). See src/cxx/README.md. */
#include "GameState.h"

extern "C" {
int PlayMusicTrack(int trackId);
int __stdcall LoadSpriteSet(void *container, int key);
extern unsigned char DAT_00ea0e18;
extern unsigned int  DAT_00ea0e1c;
void FUN_0040d260(void *outBlob);
}

/* 0x443280 - same shape as Title/Logo1: prime bucket 10000 (with
 * "logomode2.img"/"logo2.mp3" register args), reset the frame counter,
 * start the music. */
void CState06Logo2::OnEnter()
{
    LoadSpriteSet(&DAT_00ea0e18, 10000);
    m_frameCounter = 0;
    PlayMusicTrack(0);
}

/* 0x4432c0 - destroy bucket 10000, then compute the system-info blob
 * but DISCARD it (unlike Logo1's OnExit, which sends it as 0xa000 -
 * here the call's side effects are presumably what matters). */
void CState06Logo2::OnExit()
{
    unsigned char blob[40];
    unsigned int **bucket = *(unsigned int ***)(DAT_00ea0e1c + 0x1c);
    unsigned int key = (unsigned int)bucket[1];
    if (key < 0x2711) {
        while (key != 10000) {
            bucket = (unsigned int **)bucket[7];
            key = (unsigned int)bucket[1];
            if (10000 < key) {
                FUN_0040d260(blob);
                return;
            }
        }
        unsigned int **node = (unsigned int **)bucket[4];
        while (node != bucket) {
            unsigned int **obj = (unsigned int **)*node;
            node = (unsigned int **)node[4];
            ((void (__cdecl *)(int))*obj)(1);
        }
        bucket[3] = (unsigned int *)bucket;
        bucket[4] = (unsigned int *)bucket;
    }
    FUN_0040d260(blob);
}
