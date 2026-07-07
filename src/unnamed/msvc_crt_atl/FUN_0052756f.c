/* FUN_0052756f - 0x0052756f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _clock
   
   Library: Visual Studio 2003 Release */

clock_t __cdecl _clock(void)

{
  clock_t cVar1;
  longlong lVar2;
  _FILETIME local_c;
  
  GetSystemTimeAsFileTime(&local_c);
  lVar2 = __allmul(local_c.dwHighDateTime,0,0,1);
  cVar1 = __aulldiv((lVar2 - CONCAT44(_DAT_005b1754,_DAT_005b1750)) +
                    (ulonglong)local_c.dwLowDateTime,10000,0);
  return cVar1;
}

