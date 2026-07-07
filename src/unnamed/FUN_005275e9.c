/* FUN_005275e9 - 0x005275e9 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _realloc
   
   Library: Visual Studio 2003 Release */

void * __cdecl _realloc(void *_Memory,size_t _NewSize)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  LPVOID pvVar4;
  int local_24;
  void *local_20;
  
  if (_Memory == (void *)0x0) {
    pvVar1 = _malloc(_NewSize);
  }
  else {
    if (_NewSize == 0) {
      _free(_Memory);
    }
    else if (DAT_00f296b0 == 3) {
      do {
        local_20 = (void *)0x0;
        if (_NewSize < 0xffffffe1) {
          __lock(4);
          local_24 = ___sbh_find_block(_Memory);
          if (local_24 != 0) {
            if (_NewSize <= DAT_00f2969c) {
              iVar2 = ___sbh_resize_block(local_24,_Memory,_NewSize);
              if (iVar2 == 0) {
                local_20 = (void *)___sbh_alloc_block(_NewSize);
                if (local_20 != (void *)0x0) {
                  uVar3 = *(int *)((int)_Memory + -4) - 1;
                  if (_NewSize <= uVar3) {
                    uVar3 = _NewSize;
                  }
                  _memcpy(local_20,_Memory,uVar3);
                  local_24 = ___sbh_find_block(_Memory);
                  ___sbh_free_block(local_24,_Memory);
                }
              }
              else {
                local_20 = _Memory;
              }
            }
            if (local_20 == (void *)0x0) {
              if (_NewSize == 0) {
                _NewSize = 1;
              }
              _NewSize = _NewSize + 0xf & 0xfffffff0;
              local_20 = HeapAlloc(DAT_00f296ac,0,_NewSize);
              if (local_20 != (LPVOID)0x0) {
                uVar3 = *(int *)((int)_Memory + -4) - 1;
                if (_NewSize <= uVar3) {
                  uVar3 = _NewSize;
                }
                _memcpy(local_20,_Memory,uVar3);
                ___sbh_free_block(local_24,_Memory);
              }
            }
          }
          FUN_00527751();
          if (local_24 == 0) {
            if (_NewSize == 0) {
              _NewSize = 1;
            }
            _NewSize = _NewSize + 0xf & 0xfffffff0;
            local_20 = HeapReAlloc(DAT_00f296ac,0,_Memory,_NewSize);
          }
        }
        if (local_20 != (void *)0x0) {
          return local_20;
        }
        if (DAT_005b18c0 == 0) {
          return (void *)0x0;
        }
        iVar2 = __callnewh(_NewSize);
      } while (iVar2 != 0);
    }
    else {
      do {
        pvVar4 = (LPVOID)0x0;
        if (_NewSize < 0xffffffe1) {
          if (_NewSize == 0) {
            _NewSize = 1;
          }
          pvVar4 = HeapReAlloc(DAT_00f296ac,0,_Memory,_NewSize);
        }
        if (pvVar4 != (LPVOID)0x0) {
          return pvVar4;
        }
        if (DAT_005b18c0 == 0) {
          return (void *)0x0;
        }
        iVar2 = __callnewh(_NewSize);
      } while (iVar2 != 0);
    }
    pvVar1 = (void *)0x0;
  }
  return pvVar1;
}

