/* DestroyCommEngine - 0x004fdfd0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004fdfd0).  The comm engine's destructor.  It
 * opens by installing its own vtable - `*this = &PTR_LAB_00557654`, the MSVC
 * destructor signature - and then releases everything the engine owns:
 * KillTimer on the two timer ids at +0xb0/+0xb1, closesocket on the socket at
 * +0xa2, and finally WSACleanup.  (+0xa3 is the notify window's HWND, the one
 * CreateCommEngineNotifyWindow made.)
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void DestroyCommEngine(void)

{
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_LAB_00557654;
  if (unaff_ESI[0xb0] != 0) {
    KillTimer((HWND)unaff_ESI[0xa3],unaff_ESI[0xb0]);
  }
  if (unaff_ESI[0xb1] != 0) {
    KillTimer((HWND)unaff_ESI[0xa3],unaff_ESI[0xb1]);
  }
  if (unaff_ESI[0xa2] != 0xffffffff) {
    closesocket(unaff_ESI[0xa2]);
  }
  if ((HWND)unaff_ESI[0xa3] != (HWND)0x0) {
    DestroyWindow((HWND)unaff_ESI[0xa3]);
  }
  WSACleanup();
  FUN_00500140((int *)(unaff_ESI + 0xa4));
  if ((void *)unaff_ESI[0xa0] != (void *)0x0) {
    _free((void *)unaff_ESI[0xa0]);
    unaff_ESI[0xa0] = 0;
  }
  return;
}

