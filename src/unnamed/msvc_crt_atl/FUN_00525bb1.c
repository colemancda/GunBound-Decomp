/* FUN_00525bb1 - 0x00525bb1 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __beginthread
   
   Library: Visual Studio 2003 Release */

uintptr_t __cdecl __beginthread(_StartAddress *_StartAddress,uint _StackSize,void *_ArgList)

{
  undefined4 *puVar1;
  _ptiddata _Ptd;
  HANDLE hThread;
  DWORD DVar2;
  pthreadlocinfo unaff_ESI;
  
  DVar2 = 0;
  if (_StartAddress == (_StartAddress *)0x0) {
    puVar1 = (undefined4 *)FUN_0052b6d4();
    *puVar1 = 0x16;
  }
  else {
    _Ptd = _calloc(1,0x8c);
    if (_Ptd != (_ptiddata)0x0) {
      __initptd(_Ptd,unaff_ESI);
      *(_StartAddress **)_Ptd->_con_ch_buf = _StartAddress;
      *(void **)(_Ptd->_con_ch_buf + 4) = _ArgList;
      hThread = CreateThread((LPSECURITY_ATTRIBUTES)0x0,_StackSize,FUN_00525b1f,_Ptd,4,&_Ptd->_tid);
      _Ptd->_thandle = (uintptr_t)hThread;
      if ((hThread != (HANDLE)0x0) && (DVar2 = ResumeThread(hThread), DVar2 != 0xffffffff)) {
        return (uintptr_t)hThread;
      }
      DVar2 = GetLastError();
    }
    _free(_Ptd);
    if (DVar2 != 0) {
      __dosmaperr(DVar2);
    }
  }
  return 0xffffffff;
}

