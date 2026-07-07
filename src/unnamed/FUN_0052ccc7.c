/* FUN_0052ccc7 - 0x0052ccc7 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __getstream
   
   Library: Visual Studio 2003 Release */

FILE * __cdecl __getstream(void)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  FILE *pFVar4;
  FILE *_File;
  
  pFVar4 = (FILE *)0x0;
  __lock(1);
  iVar3 = 0;
  do {
    _File = pFVar4;
    if (DAT_00f29440 <= iVar3) {
LAB_0052cdb6:
      if (_File != (FILE *)0x0) {
        _File->_cnt = 0;
        _File->_flag = 0;
        _File->_base = (char *)0x0;
        _File->_ptr = (char *)0x0;
        _File->_tmpfname = (char *)0x0;
        _File->_file = -1;
      }
      FUN_0052cde0();
      return _File;
    }
    iVar1 = *(int *)(DAT_00f28420 + iVar3 * 4);
    if (iVar1 == 0) {
      iVar3 = iVar3 * 4;
      pvVar2 = _malloc(0x38);
      *(void **)(iVar3 + DAT_00f28420) = pvVar2;
      if (*(int *)(iVar3 + DAT_00f28420) != 0) {
        iVar1 = ___crtInitCritSecAndSpinCount(*(int *)(iVar3 + DAT_00f28420) + 0x20,4000);
        if (iVar1 == 0) {
          _free(*(void **)(iVar3 + DAT_00f28420));
          *(undefined4 *)(iVar3 + DAT_00f28420) = 0;
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)(*(int *)(iVar3 + DAT_00f28420) + 0x20));
          _File = *(FILE **)(iVar3 + DAT_00f28420);
        }
      }
      goto LAB_0052cdb6;
    }
    if ((*(byte *)(iVar1 + 0xc) & 0x83) == 0) {
      if (((2 < iVar3) && (iVar3 < 0x14)) && (iVar1 = __mtinitlocknum(iVar3 + 0x10), iVar1 == 0))
      goto LAB_0052cdb6;
      FID_conflict___lock_file2(iVar3,*(void **)(DAT_00f28420 + iVar3 * 4));
      _File = *(FILE **)(DAT_00f28420 + iVar3 * 4);
      if ((_File->_flag & 0x83) == 0) goto LAB_0052cdb6;
      FID_conflict___lock_file2(iVar3,_File);
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

