/* MusicChannel_Construct - 0x004eebe0 in the original binary.
 *
 * DROPPED REGISTER ARGUMENT (unaff_ESI): Ghidra read the object being
 * initialized (a freshly operator_new'd 0xb8-byte struct, per the sole
 * caller InitDirectSound.c) as an uninitialized local instead of a real
 * parameter. Confirmed via objdump at 0x4ee74d (`mov esi,eax; call
 * 0x4eebe0` right after `operator_new(0xb8)`). Promoted to a real
 * parameter, forwarded to SoundChannel_ConstructBase.
 *
 * RETURN VALUE: Ghidra emitted a bare `return;`, but objdump at
 * 0x4eec6b shows the real function ends with `mov eax,esi` before its
 * `ret` - it returns the same object pointer it was passed, which the
 * caller stores into *g_soundChannels. Fixed to match.
 *
 * NAMED (batch 41), LIKELY on the "Music" half. Constructor of the
 * 0xb8-byte object InitDirectSound builds for g_soundChannels[0]: it runs
 * SoundChannel_ConstructBase, passes through the secondary-channel vtable
 * 0x5574e8 (as SoundChannel_Construct does), starts the AudioStreamThread
 * worker, then zeroes the extra streaming fields (+0x98..+0xac) and stores
 * 20000 at +0xa0, and finally installs vtable 0x5574cc. The shape (vtable
 * 0x5574e8 then 0x5574cc, size 0xb8) is read off InitDirectSound's
 * operator_new(0xb8) and the two vtables in globals.c, and 0x5574cc
 * slot 4 is DecodeSoundBufferChunk, the compressed-stream refill.
 *
 * Why "Music": slot 0 of g_soundChannels is driven by PlayMusicTrack
 * (it stops and restarts the track through this object), and
 * SetMusicVolume sets the volume of the parallel g_secondarySoundBuffers
 * entry 0. That is indirect; no string or label names the channel, so
 * the role rests on those two callers. The tree's C++ promotion calls
 * the class CPrimaryStreamChannel (src/cxx/SoundChannel.h).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 *MusicChannel_Construct(undefined4 *unaff_ESI)

{
  undefined4 uVar1;
  uintptr_t uVar2;

  SoundChannel_ConstructBase(unaff_ESI);
  *unaff_ESI = &PTR_LAB_005574e8;
  unaff_ESI[5] = 0;
  unaff_ESI[0xe] = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x13) = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 8));
  *(undefined1 *)(unaff_ESI + 4) = 1;
  uVar2 = __beginthread(AudioStreamThreadStart,0,unaff_ESI);
  unaff_ESI[1] = uVar2;
  if (uVar2 == 0) {
    *(undefined1 *)(unaff_ESI + 4) = 0;
  }
  uVar1 = DAT_00588f44;
  unaff_ESI[0x14] = 0;
  unaff_ESI[0x26] = 0;
  unaff_ESI[0x27] = 0;
  unaff_ESI[0x29] = 0;
  unaff_ESI[0x2a] = 0;
  unaff_ESI[0x2b] = 0;
  *unaff_ESI = &PTR_LAB_005574cc;
  unaff_ESI[0x28] = 20000;
  unaff_ESI[0x2c] = uVar1;
  unaff_ESI[0x2d] = 0xffffffff;
  return unaff_ESI;
}

