/* WorkerThreadEventLoop - 0x004157b0 in the original binary.
 *
 * The worker thread's event loop: waits on the block's two handles and
 * dispatches through its vtable until the running flag clears.
 *
 * WaitForMultipleObjects(2, &block[2], FALSE, 10) -- the two wait handles at
 * +8/+0xc, with a 10 ms timeout.  On timeout it calls vtable slot 1 (the idle
 * tick); on a signalled handle it calls slot 0 with the handle index and then
 * slot 1.  It rechecks the running flag at +0x10 before every dispatch and
 * after every iteration, then __endthread()s.
 *
 * The +8/+0xc/+0x10 reading is globals.c's, recorded for this block before
 * this function was looked at -- so the loop and the declaration agree without
 * either being derived from the other.
 *
 * Which SUBSYSTEM's thread this runs is deliberately not asserted.  Several
 * classes share these methods, each installing its own vtable in its
 * constructor, and the loop only ever reaches them through that vtable.
 */
#include "ghidra_types.h"


void WorkerThreadEventLoop(int *unaff_ESI)

{
  DWORD DVar1;

  if ((char)unaff_ESI[4] != '\0') {
    do {
      DVar1 = WaitForMultipleObjects(2,(HANDLE *)(unaff_ESI + 2),0,10);
      if (DVar1 == 0xffffffff) break;
      if (DVar1 != 0) {
        if (DVar1 == 0x102) {
          if ((char)unaff_ESI[4] == '\0') break;
          (**(code **)(*unaff_ESI + 4))();
        }
        else {
          if ((char)unaff_ESI[4] == '\0') break;
          (**(code **)*unaff_ESI)(DVar1);
          (**(code **)(*unaff_ESI + 4))();
        }
      }
    } while ((char)unaff_ESI[4] != '\0');
  }
  __endthread();
  return;
}

