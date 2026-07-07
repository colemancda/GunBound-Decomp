/* FUN_00525131 - 0x00525131 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __heap_alloc
   
   Library: Visual Studio 2003 Release */

void * __cdecl __heap_alloc(size_t _Size)

{
  void *pvVar1;
  LPVOID pvVar2;
  
  if ((DAT_00f296b0 == 3) && (_Size <= DAT_00f2969c)) {
    __lock(4);
    pvVar1 = (void *)___sbh_alloc_block(_Size);
    FUN_005251a3();
    if (pvVar1 != (void *)0x0) {
      return pvVar1;
    }
  }
  if (_Size == 0) {
    _Size = 1;
  }
  if (DAT_00f296b0 != 1) {
    _Size = _Size + 0xf & 0xfffffff0;
  }
  pvVar2 = HeapAlloc(DAT_00f296ac,0,_Size);
  return pvVar2;
}

