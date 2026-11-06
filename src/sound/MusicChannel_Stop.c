/* MusicChannel_Stop - 0x004eef00 in the original binary.
 *
 * NAMED (batch 41), LIKELY on the "Music" half. Slot 3 (+0xc) of the
 * vtable 0x5574cc that MusicChannel_Construct leaves on g_soundChannels[0]
 * (find_vtable_refs: 0x4eef00 sits at .data 0x5574d8). It is the sibling
 * of SoundChannel_Stop, slot 3 of 0x5574e8, with the same shape for the
 * larger object: under the lock at +0x20, and only if the active flag at
 * +0x50 is set, it stops the channel's DirectSound buffer (IDirectSoundBuffer
 * vtable +0x48 = Stop), frees the two heap blocks at +0x98 and
 * +0xa8, clears +0x98/+0xa4/+0xa8/+0xac, closes the read state at +0x14
 * through CloseSpriteReadState and clears the flags at +0x50 and +0x4c.
 *
 * Callers do the deciding: PlayMusicTrack dispatches `call [vtbl+0xc]`
 * on *g_soundChannels and then slot 2 (the start, with the track name)
 * on the same object, and InitGame makes the same slot-3 call, so this
 * stops whatever the channel is playing before a new track starts. The
 * Music half rests on PlayMusicTrack driving channel 0 (see
 * MusicChannel_Construct).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall MusicChannel_Stop(int param_1)

{
  int *piVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  if (*(int *)(param_1 + 0x50) != 0) {
    piVar1 = *(int **)(g_secondarySoundBuffers + *(int *)(param_1 + 0x38) * 4);
    (**(code **)(*piVar1 + 0x48))(piVar1);
    _free(*(void **)(param_1 + 0x98));
    _free(*(void **)(param_1 + 0xa8));
    *(undefined4 *)(param_1 + 0x98) = 0;
    *(undefined4 *)(param_1 + 0xa4) = 0;
    *(undefined4 *)(param_1 + 0xa8) = 0;
    *(undefined4 *)(param_1 + 0xac) = 0;
    CloseSpriteReadState();
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined1 *)(param_1 + 0x4c) = 0;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}

