/* FUN_00528f26 - 0x00528f26 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __heap_init
   
   Library: Visual Studio 2003 Release */

int __cdecl __heap_init(void)

{
  int iVar1;
  int in_stack_00000004;
  
  DAT_00f296ac = HeapCreate((uint)(in_stack_00000004 == 0),0x1000,0);
  if (DAT_00f296ac == (HANDLE)0x0) {
    return 0;
  }
  DAT_00f296b0 = ___heap_select();
  if ((DAT_00f296b0 == 3) && (iVar1 = ___sbh_heap_init(0x3f8), iVar1 == 0)) {
    HeapDestroy(DAT_00f296ac);
    return 0;
  }
  return 1;
}

