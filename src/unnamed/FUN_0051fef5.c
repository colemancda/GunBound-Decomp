/* FUN_0051fef5 - 0x0051fef5 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    public: __thiscall ATL::CAtlBaseModule::CAtlBaseModule(void)
   
   Library: Visual Studio 2003 Release */

CAtlBaseModule * __thiscall ATL::CAtlBaseModule::CAtlBaseModule(CAtlBaseModule *this)

{
  int iVar1;
  _OSVERSIONINFOA local_9c;
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  _ATL_BASE_MODULE70::_ATL_BASE_MODULE70((_ATL_BASE_MODULE70 *)this);
  *(undefined4 *)(this + 8) = 0x400000;
  *(undefined4 *)(this + 4) = 0x400000;
  *(undefined4 *)this = 0x3c;
  this[0xc] = (CAtlBaseModule)0x0;
  _memset(&local_9c,0,0x94);
  local_9c.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_9c);
  if (local_9c.dwPlatformId == 2) {
    if (local_9c.dwMajorVersion < 5) goto LAB_0051ff6f;
  }
  else if ((local_9c.dwPlatformId != 1) ||
          ((local_9c.dwMajorVersion < 5 &&
           ((local_9c.dwMajorVersion != 4 || (local_9c.dwMinorVersion == 0)))))) goto LAB_0051ff6f;
  this[0xc] = (CAtlBaseModule)0x1;
LAB_0051ff6f:
  *(undefined4 *)(this + 0x10) = 0x710;
  *(undefined **)(this + 0x14) = &DAT_00544b14;
  iVar1 = FUN_00401100();
  if (iVar1 < 0) {
    DAT_005b1c40 = 1;
  }
  return this;
}

