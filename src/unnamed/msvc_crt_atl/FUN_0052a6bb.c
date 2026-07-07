/* FUN_0052a6bb - 0x0052a6bb in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mtinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __mtinit(void)

{
  int iVar1;
  HMODULE hModule;
  DWORD *pDVar2;
  DWORD DVar3;
  
  iVar1 = __mtinitlocks();
  if (iVar1 == 0) {
    __mtterm();
    return 0;
  }
  hModule = GetModuleHandleA(s_kernel32_dll_00544f3c);
  if (hModule != (HMODULE)0x0) {
    DAT_005b1910 = GetProcAddress(hModule,s_FlsAlloc_00544f30);
    DAT_005b1914 = GetProcAddress(hModule,s_FlsGetValue_00544f24);
    DAT_005b1918 = GetProcAddress(hModule,s_FlsSetValue_00544f18);
    DAT_005b191c = GetProcAddress(hModule,s_FlsFree_00544f10);
    if (DAT_005b1914 == (FARPROC)0x0) {
      DAT_005b1914 = TlsGetValue_exref;
      DAT_005b1918 = TlsSetValue_exref;
      DAT_005b1910 = FUN_0052a49b;
      DAT_005b191c = TlsFree_exref;
    }
  }
  DAT_0056c230 = (*DAT_005b1910)(__freefls_4);
  if (((DAT_0056c230 != -1) && (pDVar2 = _calloc(1,0x8c), pDVar2 != (DWORD *)0x0)) &&
     (iVar1 = (*DAT_005b1918)(DAT_0056c230,pDVar2), iVar1 != 0)) {
    pDVar2[0x15] = (DWORD)&DAT_0056c240;
    pDVar2[5] = 1;
    DVar3 = GetCurrentThreadId();
    pDVar2[1] = 0xffffffff;
    *pDVar2 = DVar3;
    return 1;
  }
  __mtterm();
  return 0;
}

