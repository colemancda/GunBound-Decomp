/* FUN_004157b0 - 0x004157b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004157b0(void)

{
  DWORD DVar1;
  int *unaff_ESI;
  
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

