/* SetEffectsVolume - 0x004eeb30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), LIKELY. Calls IDirectSoundBuffer::SetVolume (vtable
 * +0x3c) with (v - 100) * 100 on every secondary buffer from index 1 up to
 * g_soundChannelCount, i.e. all channels except buffer 0, which
 * SetMusicVolume owns; v arrives in ECX and the body is gated on the
 * sound-available flag (0x793549). Caller evidence: the battle options
 * mouse handler stores the second slider's value into the client-context
 * field at DAT_005f2f50 and calls this (the first slider, DAT_005f2f4c,
 * calls SetMusicVolume next to a PlayMusicTrack restart), HandleKeyInput
 * re-applies it when the saved option at +0x11bc is non-zero, and InitGame
 * calls both during sound setup. LIKELY: that buffers 1.. are the sound
 * effects follows from buffer 0 being the music channel (see
 * SetMusicVolume).
 */
#include "ghidra_types.h"


void __fastcall SetEffectsVolume(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  if ((g_soundAvailable != '\0') && (uVar2 = 1, 1 < g_soundChannelCount)) {
    do {
      piVar1 = *(int **)(g_secondarySoundBuffers + uVar2 * 4);
      (**(code **)(*piVar1 + 0x3c))(piVar1,(param_1 + -100) * 100);
      uVar2 = uVar2 + 1;
    } while (uVar2 < g_soundChannelCount);
  }
  return;
}

