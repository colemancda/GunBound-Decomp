/* ParseChooseEventLine - 0x00409cb0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void ParseChooseEventLine(void)

{
  char cVar1;
  undefined4 in_EAX;
  int iVar2;
  int *unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar2 = FUN_00426780(local_8,&local_c,local_4);
  if (iVar2 == 0) {
    if (*unaff_ESI == 0) {
      cVar1 = FUN_00500c00(unaff_ESI,unaff_ESI[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x8007000e);
      }
    }
    iVar2 = FUN_00409d10(unaff_ESI,in_EAX,local_c);
  }
  *(undefined4 *)(iVar2 + 4) = unaff_EDI;
  return;
}

