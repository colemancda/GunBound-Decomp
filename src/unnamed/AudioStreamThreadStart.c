/* AudioStreamThreadStart - 0x004ef870 in the original binary.
 *
 * __beginthread thread-start thunk: the thread argument arrives via the
 * standard __cdecl stack slot ([esp+8], per __beginthread's ABI), but
 * Ghidra's decompile dropped it entirely instead of forwarding it to
 * AudioStreamThreadProc. Confirmed via objdump at 0x4ef870-0x4ef875
 * (`mov esi,[esp+8]` immediately before `call 0x4ef880`, with ESI never
 * reloaded inside AudioStreamThreadProc itself). Promoted to a real
 * parameter and forwarded.
 *
 * NAMED (batch 35), CERTAIN on the role (was FUN_004ef870).  The whole body
 * is `push esi / mov esi,[esp+8] / call 0x4ef880 / pop esi / ret`: it
 * takes the thread argument from the stack and hands it to
 * AudioStreamThreadProc (0x4ef880) in ESI, which that routine reads as its
 * `this`.  Its address is never called, only passed as the start
 * routine: SoundChannel_Construct and MusicChannel_Construct both do
 * `__beginthread(AudioStreamThreadStart, 0, unaff_ESI)`, and
 * SoundChannel.cpp does `_beginthread(AudioStreamThreadStart, 0, this)`
 * (its extern comment: "__beginthread thunk -> AudioStreamThreadProc").
 * "Start" because it is the entry the CRT thread wrapper invokes, ahead of
 * the Proc loop body; the file stays beside AudioStreamThreadProc.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void AudioStreamThreadStart(void *unaff_ESI)

{
  AudioStreamThreadProc(unaff_ESI);
  return;
}

