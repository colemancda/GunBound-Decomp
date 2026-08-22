/* FUN_00415410 - 0x00415410 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00415410(undefined4 *regEsi)

{
  HANDLE pvVar1;
  
  *regEsi = &PTR_LAB_005520a4;
  regEsi[1] = 0;
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  regEsi[2] = pvVar1;
  *(undefined1 *)(regEsi + 3) = 0;
  *regEsi = &PTR_LAB_005520ac;
  regEsi[4] = 0xffffffff;
  regEsi[5] = 0;
  return;
}

