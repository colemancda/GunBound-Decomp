/* FUN_00405dd0 - 0x00405dd0 in the original binary.
 *
 * Connection-object worker thread body: waits on up to 4 handles at
 * unaff_ESI+8 (WaitForMultipleObjects) and dispatches through the
 * object's vtable - slot 0 (this,eventCode) on a real signal, slot 1
 * (this) as a "process pending" call, or slot 1 alone on timeout
 * (WAIT_TIMEOUT=0x102). unaff_ESI+0x18 is the "keep running" flag,
 * checked before/after each dispatch. Confirmed __thiscall (ecx=esi) at
 * orig 0x405e05-0x405e0d/0x405e1b-0x405e1d, not a generic code() call -
 * given explicit __thiscall prototypes to avoid the double-stack-cleanup
 * bug (see src/directx_init/InitDirectSound.c's VTBL pattern).
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"

typedef void (__thiscall *ConnWorkerDispatchFn)(void *thisPtr);
typedef void (__thiscall *ConnWorkerSignalFn)(void *thisPtr, DWORD eventCode);

void FUN_00405dd0(int *unaff_ESI)

{
  DWORD DVar1;

  if ((char)unaff_ESI[6] != '\0') {
    do {
      DVar1 = WaitForMultipleObjects(4,(HANDLE *)(unaff_ESI + 2),0,0x32);
      if (DVar1 == 0xffffffff) break;
      if (DVar1 != 0) {
        if (DVar1 == 0x102) {
          if ((char)unaff_ESI[6] == '\0') break;
          ((ConnWorkerDispatchFn)(*(void ***)unaff_ESI)[1])(unaff_ESI);
        }
        else {
          if ((char)unaff_ESI[6] == '\0') break;
          ((ConnWorkerSignalFn)(*(void ***)unaff_ESI)[0])(unaff_ESI,DVar1);
          ((ConnWorkerDispatchFn)(*(void ***)unaff_ESI)[1])(unaff_ESI);
        }
      }
    } while ((char)unaff_ESI[6] != '\0');
  }
  __endthread();
  return;
}

