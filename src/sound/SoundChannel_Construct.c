/* SoundChannel_Construct - 0x004ef3a0 in the original binary.
 *
 * DROPPED REGISTER ARGUMENT (unaff_ESI): Ghidra read the object being
 * initialized (a freshly operator_new'd 0x50-byte struct, per the sole
 * caller InitDirectSound.c) as an uninitialized local instead of a real
 * parameter. Confirmed via objdump at 0x4ee77e (`mov esi,eax; call
 * 0x4ef3a0` right after `operator_new(0x50)`). Promoted to a real
 * parameter, forwarded to SoundChannel_ConstructBase (also confirmed via objdump at
 * 0x4ef3a1: `mov ebx,esi` before that call).
 *
 * RETURN VALUE: Ghidra emitted a bare `return;` (MSVC falls through
 * with whatever's in EAX; gcc rejects it as -Wreturn-mismatch), but
 * objdump at 0x4ef434 shows the real function ends with `mov eax,esi`
 * before its `ret` - it returns the same object pointer it was passed,
 * which the caller stores into g_soundChannels[]. Fixed to match.
 *
 * NAMED (batch 36). The secondary sound channel constructor. The sole
 * caller, InitDirectSound, runs it on a fresh operator_new(0x50) block and
 * stores the returned pointer (the same object, in ESI) into
 * g_soundChannels[1..] (slot 0 is the primary channel, MusicChannel_Construct). It
 * runs the shared base construction (0x4ef7e0), installs
 * PTR_LAB_005574e8, the vtable whose slot 3 is SoundChannel_Stop
 * (0x4ef5b0) and which StopSoundChannel and the ShutdownDirectSound teardown
 * dispatch through, sets up the lock at +0x20, and starts the worker with
 * __beginthread(AudioStreamThreadStart, 0, this), keeping the thread
 * handle at +4 and the running flag at +0x10.
 *
 * The mirrored destructor is 0x4ef3f0 (SoundChannel_Destruct), which
 * restores the same vtable and calls SoundChannel_Stop before deleting
 * the lock.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 *SoundChannel_Construct(undefined4 *unaff_ESI)

{
  uintptr_t uVar1;

  SoundChannel_ConstructBase(unaff_ESI);
  *unaff_ESI = &PTR_LAB_005574e8;
  unaff_ESI[5] = 0;
  unaff_ESI[0xe] = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x13) = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 8));
  *(undefined1 *)(unaff_ESI + 4) = 1;
  uVar1 = __beginthread(AudioStreamThreadStart,0,unaff_ESI);
  unaff_ESI[1] = uVar1;
  if (uVar1 == 0) {
    *(undefined1 *)(unaff_ESI + 4) = 0;
  }
  return unaff_ESI;
}

