/* ConstructConnectionThreadBase - 0x004e5bb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (batch 40). Base-class constructor of the connection object: stores
 * vtable 0x5572e0, zeroes +4 (the worker thread handle), creates four
 * auto-reset unsignalled events (CreateEventA) into +8..+0x14 and clears the
 * byte at +0x18. It is the exact inverse of ShutdownConnectionThread
 * (0x4e5c00), which re-points the object to the same 0x5572e0 vtable,
 * signals the event at +8, waits on the handle at +4 and CloseHandle()s the
 * same four events. Sole caller ConstructConnectionObject (0x4e54e3) passes
 * the object and then overwrites the vtable with the derived 0x5572e8,
 * which is what makes this the base-class step. Returns the object.
 */
#include "ghidra_types.h"


undefined4 * ConstructConnectionThreadBase(undefined4 *param_1)

{
  HANDLE pvVar1;
  undefined4 *puVar2;
  int iVar3;
  
  *param_1 = &PTR_LAB_005572e0;
  param_1[1] = 0;
  puVar2 = param_1 + 2;
  iVar3 = 4;
  do {
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    *puVar2 = pvVar1;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(undefined1 *)(param_1 + 6) = 0;
  return param_1;
}

