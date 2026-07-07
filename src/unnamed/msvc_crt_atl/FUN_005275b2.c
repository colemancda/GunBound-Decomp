/* FUN_005275b2 - 0x005275b2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    ___inittime
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release, Visual Studio 2008 Release */

undefined4 ___inittime(void)

{
  longlong lVar1;
  _FILETIME local_c;
  
  GetSystemTimeAsFileTime(&local_c);
  lVar1 = __allmul(local_c.dwHighDateTime,0,0,1);
  _DAT_005b1750 = lVar1 + (ulonglong)local_c.dwLowDateTime;
  return 0;
}

