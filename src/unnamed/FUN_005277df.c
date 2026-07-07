/* FUN_005277df - 0x005277df in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int entry(void)

{
  HMODULE pHVar1;
  int iVar2;
  LPSTR lpCmdLine;
  uint nShowCmd;
  int *piVar3;
  HINSTANCE hPrevInstance;
  _OSVERSIONINFOA local_114;
  _STARTUPINFOA local_74;
  int local_30;
  int local_2c;
  LPSTR local_24;
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0056b870;
  uStack_c = 0x5277eb;
  local_114.szCSDVersion[0x7c] = -9;
  local_114.szCSDVersion[0x7d] = 'w';
  local_114.szCSDVersion[0x7e] = 'R';
  local_114.szCSDVersion[0x7f] = '\0';
  local_1c = (undefined1 *)&local_114;
  local_114.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_114);
  DAT_005b18c8 = local_114.dwPlatformId;
  DAT_005b18d4 = local_114.dwMajorVersion;
  _DAT_005b18d8 = local_114.dwMinorVersion;
  _DAT_005b18cc = local_114.dwBuildNumber & 0x7fff;
  if (local_114.dwPlatformId != 2) {
    _DAT_005b18cc = _DAT_005b18cc | 0x8000;
  }
  _DAT_005b18d0 = local_114.dwMajorVersion * 0x100 + local_114.dwMinorVersion;
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  if (((short)pHVar1->unused == 0x5a4d) &&
     (piVar3 = (int *)((int)&pHVar1->unused + pHVar1[0xf].unused), *piVar3 == 0x4550)) {
    if ((short)piVar3[6] == 0x10b) {
      if (0xe < (uint)piVar3[0x1d]) {
        iVar2 = piVar3[0x3a];
        goto LAB_005278a0;
      }
    }
    else if (((short)piVar3[6] == 0x20b) && (0xe < (uint)piVar3[0x21])) {
      iVar2 = piVar3[0x3e];
LAB_005278a0:
      local_20 = (uint)(iVar2 != 0);
      goto LAB_005278a6;
    }
  }
  local_20 = 0;
LAB_005278a6:
  iVar2 = __heap_init();
  if (iVar2 == 0) {
    fast_error_exit(0x1c);
  }
  iVar2 = __mtinit();
  if (iVar2 == 0) {
    fast_error_exit(0x10);
  }
  __RTC_Initialize();
  local_8 = (undefined *)0x0;
  iVar2 = __ioinit();
  if (iVar2 < 0) {
    __amsg_exit(0x1b);
  }
  DAT_00f296b4 = GetCommandLineA();
  DAT_005b1758 = ___crtGetEnvironmentStringsA();
  iVar2 = __setargv();
  if (iVar2 < 0) {
    __amsg_exit(8);
  }
  iVar2 = __setenvp();
  if (iVar2 < 0) {
    __amsg_exit(9);
  }
  local_2c = __cinit(1);
  if (local_2c != 0) {
    __amsg_exit(local_2c);
  }
  local_74.dwFlags = 0;
  GetStartupInfoA(&local_74);
  lpCmdLine = (LPSTR)__wincmdln();
  if ((local_74.dwFlags & 1) == 0) {
    nShowCmd = 10;
  }
  else {
    nShowCmd = (uint)local_74.wShowWindow;
  }
  hPrevInstance = (HINSTANCE)0x0;
  local_24 = lpCmdLine;
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  iVar2 = WinMain(pHVar1,hPrevInstance,lpCmdLine,nShowCmd);
  local_30 = iVar2;
  if (local_20 == 0) {
                    /* WARNING: Subroutine does not return */
    _exit(iVar2);
  }
  __cexit();
  return iVar2;
}

