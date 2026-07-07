/* FUN_0052b759 - 0x0052b759 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _calloc
   
   Library: Visual Studio 2003 Release */

void * __cdecl _calloc(size_t _Count,size_t _Size)

{
  int iVar1;
  uint _Size_00;
  uint dwBytes;
  void *_Dst;
  
  _Size_00 = _Count * _Size;
  dwBytes = _Size_00;
  if (_Size_00 == 0) {
    dwBytes = 1;
  }
  do {
    _Dst = (void *)0x0;
    if (dwBytes < 0xffffffe1) {
      if ((DAT_00f296b0 == 3) && (dwBytes = dwBytes + 0xf & 0xfffffff0, _Size_00 <= DAT_00f2969c)) {
        __lock(4);
        _Dst = (void *)___sbh_alloc_block(_Size_00);
        FUN_0052b803();
        if (_Dst != (void *)0x0) {
          _memset(_Dst,0,_Size_00);
          goto LAB_0052b7ce;
        }
      }
      else {
LAB_0052b7ce:
        if (_Dst != (void *)0x0) {
          return _Dst;
        }
      }
      _Dst = HeapAlloc(DAT_00f296ac,8,dwBytes);
    }
    if (_Dst != (void *)0x0) {
      return _Dst;
    }
    if (DAT_005b18c0 == 0) {
      return (void *)0x0;
    }
    iVar1 = __callnewh(dwBytes);
    if (iVar1 == 0) {
      return (void *)0x0;
    }
  } while( true );
}

