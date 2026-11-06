/* SoundChannel_DestructBase - 0x004ef820 in the original binary.
 *
 * NAMED (batch 36), LIKELY. The base-subobject destructor, the mirror of
 * SoundChannel_ConstructBase (0x4ef7e0). Its sole caller is the secondary
 * channel destructor at 0x4ef3f0, which calls it last (`mov eax,esi / call
 * 0x4ef820`, object in EAX) after SoundChannel_Stop and
 * DeleteCriticalSection. It resets the vtable to PTR_LAB_005574e0, the
 * base vtable ConstructBase installs, clears the running flag at +0x10,
 * signals the event at +8, waits up to 1000 ms on the thread handle at +4
 * and closes the two events at +8 and +0xc.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void SoundChannel_DestructBase(undefined4 *regEax)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = regEax + 2;
  *regEax = &PTR_LAB_005574e0;
  *(undefined1 *)(regEax + 4) = 0;
  SetEvent((HANDLE)regEax[2]);
  if ((HANDLE)regEax[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)regEax[1],1000);
  }
  iVar2 = 2;
  do {
    CloseHandle((HANDLE)*puVar1);
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

