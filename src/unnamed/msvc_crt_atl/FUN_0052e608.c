/* FUN_0052e608 - 0x0052e608 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setargv
   
   Library: Visual Studio 2003 Release */

int __cdecl __setargv(void)

{
  void *pvVar1;
  int iVar2;
  int in_ECX;
  int local_8;
  
  local_8 = in_ECX;
  if (DAT_00f2968c == 0) {
    ___initmbctable();
  }
  DAT_005b1b24 = 0;
  GetModuleFileNameA((HMODULE)0x0,&DAT_005b1a20,0x104);
  _DAT_005b18f8 = &DAT_005b1a20;
  parse_cmdline(0,&local_8);
  pvVar1 = _malloc(in_ECX + local_8 * 4);
  if (pvVar1 == (void *)0x0) {
    iVar2 = -1;
  }
  else {
    parse_cmdline(pvVar1,&local_8);
    _DAT_005b18dc = local_8 + -1;
    iVar2 = 0;
    _DAT_005b18e0 = pvVar1;
  }
  return iVar2;
}

