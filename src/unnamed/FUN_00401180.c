/* FUN_00401180 - 0x00401180 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00401180(void)

{
  HANDLE pvVar1;
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_LAB_0054b450;
  unaff_ESI[1] = 0;
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  unaff_ESI[2] = pvVar1;
  *(undefined1 *)(unaff_ESI + 3) = 0;
  *unaff_ESI = &PTR_LAB_0054b458;
  *(undefined1 *)(unaff_ESI + 4) = 0;
  return;
}

