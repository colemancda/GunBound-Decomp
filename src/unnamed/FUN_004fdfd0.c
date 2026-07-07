/* FUN_004fdfd0 - 0x004fdfd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fdfd0(void)

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
  FUN_00500140();
  if ((void *)unaff_ESI[0xa0] != (void *)0x0) {
    _free((void *)unaff_ESI[0xa0]);
    unaff_ESI[0xa0] = 0;
  }
  return;
}

