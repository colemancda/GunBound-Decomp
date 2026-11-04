/* SetMusicVolume - 0x004eeb10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), LIKELY. Calls IDirectSoundBuffer::SetVolume (vtable
 * +0x3c = slot 15) on secondary buffer 0 with (v - 100) * 100, i.e. a
 * 0-100 setting mapped to -10000..0 hundredths of a dB; v arrives in EDX
 * and the whole body is gated on the sound-available flag (0x793549).
 * Buffer 0 is the music channel's: g_secondarySoundBuffers is the array
 * parallel to g_soundChannels, and PlayMusicTrack drives channel 0 (it
 * starts and stops the track through the object at the head of that
 * array). Caller evidence: the battle options handlers
 * (State11_InBattle_HandleMouseInput and HandleKeyInput) store the slider
 * value into the client-context field at DAT_005f2f4c, sit beside a stage-
 * mp3 PlayMusicTrack restart, and call this; the effects slider writes
 * DAT_005f2f50 and calls SetEffectsVolume instead. InitGame calls both
 * during sound setup. LIKELY: channel 0 = music rests on PlayMusicTrack
 * and the slider pairing, not on an explicit label.
 */
#include "ghidra_types.h"


void __fastcall SetMusicVolume(undefined4 param_1,int param_2)

{
  if (g_soundAvailable != '\0') {
    (**(code **)(*(int *)*g_secondarySoundBuffers + 0x3c))((int *)*g_secondarySoundBuffers,(param_2 + -100) * 100);
  }
  return;
}

