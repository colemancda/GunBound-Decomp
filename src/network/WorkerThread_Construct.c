/* WorkerThread_Construct - 0x00415410 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00415410 mean this function.)
 *
 * NAMED (batch 48), HIGH. Constructor of the g_workerThreadBlock object
 * (0xe9c9c4). Its sole caller is the dynamic initializer at 0x5411a0 (mov
 * esi,0xe9c9c4; call 0x415410), which registers 0x5437d0 with atexit, and
 * 0x5437d0 is mov esi,0xe9c9c4; call 0x40d1c0 = WorkerThread_Shutdown on
 * the same block. It stamps vtable 0x5520a4 first and then 0x5520ac, the
 * same 0x5520a4 WorkerThread_Shutdown restamps, and fills the fields
 * globals_sized.c records for the block: thread handle +4 (0), event +8
 * (CreateEventA), stop flag +0xc, then +0x10 = -1 and +0x14 = 0 (the block
 * is 0x18 bytes).
 */
#include "ghidra_types.h"


void WorkerThread_Construct(undefined4 *regEsi)

{
  HANDLE pvVar1;
  
  *regEsi = &PTR_LAB_005520a4;
  regEsi[1] = 0;
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  regEsi[2] = pvVar1;
  *(undefined1 *)(regEsi + 3) = 0;
  *regEsi = &PTR_LAB_005520ac;
  regEsi[4] = 0xffffffff;
  regEsi[5] = 0;
  return;
}

