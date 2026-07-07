/* FUN_00534ab1 - 0x00534ab1 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _raise
   
   Library: Visual Studio 2003 Release */

int __cdecl _raise(int _SigNum)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  code *pcVar4;
  void *local_34;
  void *local_30;
  _ptiddata local_28;
  
  bVar1 = false;
  if (_SigNum == 2) {
    puVar3 = &DAT_005b1c14;
    pcVar4 = DAT_005b1c14;
LAB_00534b3e:
    bVar1 = true;
  }
  else {
    if (((_SigNum != 4) && (_SigNum != 8)) && (_SigNum != 0xb)) {
      if (_SigNum == 0xf) {
        puVar3 = &DAT_005b1c20;
        pcVar4 = DAT_005b1c20;
      }
      else if (_SigNum == 0x15) {
        puVar3 = &DAT_005b1c18;
        pcVar4 = DAT_005b1c18;
      }
      else {
        if (_SigNum != 0x16) {
          return -1;
        }
        puVar3 = &DAT_005b1c1c;
        pcVar4 = DAT_005b1c1c;
      }
      goto LAB_00534b3e;
    }
    local_28 = __getptd();
    iVar2 = siglookup();
    puVar3 = (undefined4 *)(iVar2 + 8);
    pcVar4 = (code *)*puVar3;
  }
  if (pcVar4 == (code *)0x1) {
    return 0;
  }
  if (pcVar4 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  if (bVar1) {
    __lock(0);
  }
  if (((_SigNum == 8) || (_SigNum == 0xb)) || (_SigNum == 4)) {
    local_30 = local_28->_initarg;
    local_28->_initarg = (void *)0x0;
    if (_SigNum == 8) {
      local_34 = local_28->_pxcptacttab;
      local_28->_pxcptacttab = (void *)0x8c;
      goto LAB_00534b9d;
    }
  }
  else {
LAB_00534b9d:
    iVar2 = DAT_0056c2b8;
    if (_SigNum == 8) {
      for (; iVar2 < DAT_0056c2bc + DAT_0056c2b8; iVar2 = iVar2 + 1) {
        *(undefined4 *)((int)local_28->_initaddr + iVar2 * 0xc + 8) = 0;
      }
      goto LAB_00534bcb;
    }
  }
  *puVar3 = 0;
LAB_00534bcb:
  FUN_00534bec();
  if (_SigNum == 8) {
    (*pcVar4)(8,local_28->_pxcptacttab);
  }
  else {
    (*pcVar4)(_SigNum);
    if ((_SigNum != 0xb) && (_SigNum != 4)) {
      return 0;
    }
  }
  local_28->_initarg = local_30;
  if (_SigNum == 8) {
    local_28->_pxcptacttab = local_34;
  }
  return 0;
}

