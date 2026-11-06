/* SoundChannel_ConstructBase - 0x004ef7e0 in the original binary.
 *
 * DROPPED REGISTER ARGUMENT (unaff_EBX): Ghidra read the object being
 * initialized as an uninitialized unaff_EBX local instead of a real
 * parameter. Both real callers (SoundChannel_Construct/FUN_004eebe0) confirm via
 * objdump at 0x4ef3a0-0x4ef3a3 (`mov ebx,esi` immediately before `call
 * 0x4ef7e0`) that EBX is simply their own object pointer forwarded
 * through - promoted to a real parameter here and at both call sites.
 *
 * NAMED (batch 36), LIKELY. The base-subobject constructor shared by both
 * sound channel classes: both SoundChannel_Construct (0x4ef3a0, secondary)
 * and FUN_004eebe0 (primary) call it first, with the object in EBX
 * (`mov ebx,esi` immediately before the call). It installs
 * PTR_LAB_005574e0, a vtable of only no-op stubs plus
 * PollSoundBufferPosition that each derived constructor then overwrites
 * (see globals.c), zeroes the thread handle at +4, creates the two events
 * at +8 and +0xc with CreateEventA, and clears the running flag at +0x10.
 *
 * Its counterpart is SoundChannel_DestructBase (0x4ef820), which resets the
 * same base vtable, signals and joins the thread and closes the two events.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void SoundChannel_ConstructBase(undefined4 *unaff_EBX)

{
  HANDLE pvVar1;
  undefined4 *puVar2;
  int iVar3;

  *unaff_EBX = &PTR_LAB_005574e0;
  unaff_EBX[1] = 0;
  puVar2 = unaff_EBX + 2;
  iVar3 = 2;
  do {
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    *puVar2 = pvVar1;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(undefined1 *)(unaff_EBX + 4) = 0;
  return;
}

