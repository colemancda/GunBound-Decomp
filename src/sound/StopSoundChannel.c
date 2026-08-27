/* StopSoundChannel - 0x004eeae0 in the original binary.
 *
 * Stops whatever the given sound channel is playing.
 *
 * NAMED 2026-08-26.  The vtable slot is already identified in another file:
 * src/unnamed/PlayMusicTrack.c's header describes the same class's
 * "vtable+0xc (\"stop current\") and vtable+0x8 (\"start new\")", and
 * src/sound/AcquireSoundChannel.c's header independently documents slot 2
 * (+8) as the play entry -- `channelObj->vtbl[2](channelIndex, soundName,
 * flag)`.  This calls slot 3 (+0xc) on the same g_soundChannels element, so
 * it is the stop half of a pair whose other half was named first.
 *
 * DAT_00793568 is the currently-playing music track (PlayMusicTrack compares
 * against it to decide whether a switch is needed), which is why this clears
 * it only for channel 0 -- the music channel.  DecodeSoundBufferChunk inlines
 * the identical `if (g_soundAvailable) { channel0->vtbl[3](); track = 0; }`
 * twice, for channel 0 specifically.
 *
 * The channel index arrives in ESI; it was recovered earlier this session and
 * -1 is its "no channel" sentinel.
 *
 * ESI RECOVERED (2026-08-26): the sound-channel index.  The body is 39 bytes:
 * bail if g_soundAvailable is clear; if ESI != -1, take g_soundChannels[ESI]
 * and call its vtable slot 3; then, only when ESI == 0, clear the byte at
 * 0x793568.  ESI is read before any write (`cmp esi,-1` is its first
 * reference), and -1 as a "no channel" sentinel plus the [table + esi*4]
 * indexing is what fixes it as the index rather than a pointer.
 */
#include "ghidra_types.h"


void StopSoundChannel(int soundChannelIndex)

{
  
  if (g_soundAvailable != '\0') {
    if (soundChannelIndex != -1) {
      (**(code **)(**(int **)(g_soundChannels + soundChannelIndex * 4) + 0xc))();
    }
    if (soundChannelIndex == 0) {
      DAT_00793568 = 0;
    }
  }
  return;
}

