/* SoundChannel_Destruct - 0x004ef3f0 in the original binary.
 *
 * NAMED (batch 36), LIKELY. The secondary sound channel destructor, the
 * mirror of SoundChannel_Construct (0x4ef3a0). The sole caller, the
 * FUN_004ee850 DirectSound teardown, calls it on each g_soundChannels entry
 * and immediately _free()s the same pointer, after having already
 * dispatched the slot-3 Stop and signalled the worker itself. The body
 * re-installs PTR_LAB_005574e8 (the vtable Construct installs), clears the
 * running flag, SetEvents the event at +8, calls SoundChannel_Stop
 * (0x4ef5b0) directly, DeleteCriticalSection on the lock at +0x20 that
 * Construct initialised, then runs SoundChannel_DestructBase (0x4ef820).
 * It takes its object on the stack and ends in ret 4, which the port does
 * not model (cdecl).
 *
 * Named Destruct, not Destructor, to pair with SoundChannel_Construct and
 * SoundChannel_DestructBase. There is no scalar-deleting wrapper: the
 * caller frees the block itself.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void SoundChannel_Destruct(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537bd8;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_LAB_005574e8;
  local_4 = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  SetEvent((HANDLE)param_1[2]);
  SoundChannel_Stop();
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 8));
  SoundChannel_DestructBase(param_1);
  *unaff_FS_OFFSET = local_c;
  return;
}

