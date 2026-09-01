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


void DestroyCommEngine(undefined4 *regEsi)

{
  
  *regEsi = &PTR_LAB_00557654;
  if (regEsi[0xb0] != 0) {
    KillTimer((HWND)regEsi[0xa3],regEsi[0xb0]);
  }
  if (regEsi[0xb1] != 0) {
    KillTimer((HWND)regEsi[0xa3],regEsi[0xb1]);
  }
  if (regEsi[0xa2] != 0xffffffff) {
    closesocket(regEsi[0xa2]);
  }
  if ((HWND)regEsi[0xa3] != (HWND)0x0) {
    DestroyWindow((HWND)regEsi[0xa3]);
  }
  WSACleanup();
  StringMap_RemoveAll_ac((int *)(regEsi + 0xa4));
  if ((void *)regEsi[0xa0] != (void *)0x0) {
    _free((void *)regEsi[0xa0]);
    regEsi[0xa0] = 0;
  }
  return;
}

