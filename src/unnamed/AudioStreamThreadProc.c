/* AudioStreamThreadProc - 0x004ef880 in the original binary.
 *
 * The DirectSound streaming worker-thread body: a double-buffered loop that WaitForMultipleObjects on the sound object's 2 position-notification events (100ms timeout), calling the object's refill method (vtable slot 0, given the event index) to decode+fill the just-played buffer half, plus a periodic tick (slot 1); loops while the running flag (obj+0x10) is set. See ARCHITECTURE.md audio section.
 *
 * DROPPED REGISTER ARGUMENT (unaff_ESI): the sound-object pointer arrives
 * via FUN_004ef870's forwarded __beginthread argument, not a real
 * parameter - Ghidra's decompile read it as an uninitialized local,
 * which crashed on the very first `[unaff_ESI+4]` field read. Promoted
 * to a real parameter; see FUN_004ef870.c for the register-recovery
 * detail.
 *
 * CALLING-CONVENTION CAST MISMATCH: both vtable calls (slot 0 "refill",
 * slot 1 "tick") used the generic cdecl code() cast, silently dropping
 * `this`. Confirmed via objdump at 0x4ef8b2-0x4ef8cd: every call loads
 * ECX with the sound object (esi) immediately before `call [edx]`/
 * `call [edx+4]` - slot 0 takes one additional stack arg (the wait
 * result), slot 1 takes none. Fixed with __fastcall typedefs matching
 * this codebase's established GameStateVirtualFn idiom.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"

typedef void (__fastcall *SoundRefillFn)(void *thisPtr, DWORD waitResult);
typedef void (__fastcall *SoundTickFn)(void *thisPtr);

void AudioStreamThreadProc(int *unaff_ESI)

{
  DWORD DVar1;

  if ((char)unaff_ESI[4] != '\0') {
    do {
      DVar1 = WaitForMultipleObjects(2,(HANDLE *)(unaff_ESI + 2),0,100);
      if (DVar1 == 0xffffffff) break;
      if (DVar1 != 0) {
        if (DVar1 == 0x102) {
          if ((char)unaff_ESI[4] == '\0') break;
          (*(SoundTickFn *)(*unaff_ESI + 4))(unaff_ESI);
        }
        else {
          if ((char)unaff_ESI[4] == '\0') break;
          (*(SoundRefillFn *)*unaff_ESI)(unaff_ESI, DVar1);
          (*(SoundTickFn *)(*unaff_ESI + 4))(unaff_ESI);
        }
      }
    } while ((char)unaff_ESI[4] != '\0');
  }
  __endthread();
  return;
}

