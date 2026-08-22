/* FUN_00401180 - 0x00401180 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00401180(undefined4 *regEsi)

{
  HANDLE pvVar1;
  
  *regEsi = &PTR_LAB_0054b450;
  regEsi[1] = 0;
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  regEsi[2] = pvVar1;
  *(undefined1 *)(regEsi + 3) = 0;
  *regEsi = &PTR_LAB_0054b458;
  *(undefined1 *)(regEsi + 4) = 0;
  return;
}

