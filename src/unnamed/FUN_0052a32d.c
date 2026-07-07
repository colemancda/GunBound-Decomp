/* FUN_0052a32d - 0x0052a32d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __setmbcp
   
   Library: Visual Studio 2003 Release */

int __cdecl __setmbcp(int _CodePage)

{
  int *_Memory;
  int iVar1;
  int local_24;
  
  local_24 = -1;
  __lock(0xd);
  DAT_005b190c = 0;
  if (_CodePage == -2) {
    DAT_005b190c = 1;
    _CodePage = GetOEMCP();
  }
  else if (_CodePage == -3) {
    DAT_005b190c = 1;
    _CodePage = GetACP();
  }
  else if (_CodePage == -4) {
    DAT_005b190c = 1;
    _CodePage = DAT_005b1b9c;
  }
  if (_CodePage == DAT_00f29564) {
    local_24 = 0;
  }
  else {
    if ((DAT_00f29448 == (int *)0x0) || (_Memory = DAT_00f29448, *DAT_00f29448 != 0)) {
      _Memory = _malloc(0x220);
    }
    if ((_Memory != (int *)0x0) && (local_24 = __setmbcp_lk(_CodePage), local_24 == 0)) {
      *_Memory = 0;
      _Memory[1] = DAT_00f29564;
      _Memory[2] = DAT_00f2944c;
      _Memory[3] = DAT_00f29444;
      for (iVar1 = 0; iVar1 < 5; iVar1 = iVar1 + 1) {
        *(undefined2 *)((int)_Memory + iVar1 * 2 + 0x10) = (&DAT_00f29570)[iVar1];
      }
      for (iVar1 = 0; iVar1 < 0x101; iVar1 = iVar1 + 1) {
        *(undefined1 *)(iVar1 + 0x1c + (int)_Memory) = (&DAT_00f29460)[iVar1];
      }
      for (iVar1 = 0; DAT_00f29448 = _Memory, iVar1 < 0x100; iVar1 = iVar1 + 1) {
        *(undefined1 *)(iVar1 + 0x11d + (int)_Memory) = (&DAT_00f29580)[iVar1];
      }
    }
    if ((local_24 == -1) && (_Memory != DAT_00f29448)) {
      _free(_Memory);
    }
  }
  FUN_0052a474();
  return local_24;
}

