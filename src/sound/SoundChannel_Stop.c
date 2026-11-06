/* SoundChannel_Stop - 0x004ef5b0 in the original binary.
 *
 * NAMED (batch 36). The secondary-channel Stop: vtable slot 3 (+0xc) of
 * PTR_LAB_005574e8, the vtable SoundChannel_Construct (0x4ef3a0) installs
 * and keeps. Under the channel lock (+0x20) it stops the channel's
 * DirectSound buffer, g_secondarySoundBuffers[+0x38], with
 * IDirectSoundBuffer vtable +0x48 (Stop), closes the +0x14 read state
 * with CloseSpriteReadState, clears +0x14 and +0x4c, and leaves +0x38 = -1.
 *
 * Evidence is outside the body. StopSoundChannel dispatches `call [vtbl+0xc]`
 * on g_soundChannels[index], and the FUN_004ee850 teardown makes the same
 * slot-3 call on every channel before freeing it; the secondary-channel
 * destructor (0x4ef3f0) calls this address directly after SetEvent. The
 * primary channel's own slot 3 is FUN_004eef00, and the C++ promotion
 * CSoundChannel::Stop in src/cxx/SoundChannel.h is this function.
 *
 * Not to be confused with StopSoundChannel(index), the index-taking wrapper
 * that dispatches to this slot.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall SoundChannel_Stop(int param_1)

{
  int *piVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  if (*(int *)(param_1 + 0x14) != 0) {
    piVar1 = *(int **)(g_secondarySoundBuffers + *(int *)(param_1 + 0x38) * 4);
    (**(code **)(*piVar1 + 0x48))(piVar1);
    CloseSpriteReadState();
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined1 *)(param_1 + 0x4c) = 0;
  }
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}

