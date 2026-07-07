/* FUN_0052a12e - 0x0052a12e in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___updatetmbcinfo
   
   Library: Visual Studio 2003 Release */

pthreadmbcinfo __cdecl ___updatetmbcinfo(void)

{
  _ptiddata p_Var1;
  pthreadmbcinfo _Memory;
  
  __lock(0xd);
  p_Var1 = __getptd();
  _Memory = p_Var1->_tpxcptinfoptrs;
  if (_Memory != DAT_00f29448) {
    if ((_Memory != (pthreadmbcinfo)0x0) &&
       (_Memory->refcount = _Memory->refcount + -1, _Memory->refcount == 0)) {
      _free(_Memory);
    }
    p_Var1->_tpxcptinfoptrs = DAT_00f29448;
    _Memory = DAT_00f29448;
    DAT_00f29448->refcount = DAT_00f29448->refcount + 1;
  }
  FUN_0052a194();
  return _Memory;
}

