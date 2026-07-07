/* FUN_00530cbb - 0x00530cbb in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* Library Function - Single Match
    ___security_error_handler
   
   Library: Visual Studio 2003 Release */

void ___security_error_handler(int param_1)

{
  DWORD DVar1;
  size_t sVar2;
  char *_Str;
  char *local_12c;
  CHAR local_128 [260];
  undefined1 local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_005494a8;
  uStack_c = 0x530cca;
  local_20 = DAT_0056bfd4;
  if (DAT_005b1b2c == (code *)0x0) {
    if (param_1 == 1) {
      local_12c = s_A_buffer_overrun_has_been_detect_00549310;
    }
    else {
      local_12c = s_A_security_error_of_unknown_caus_005493d0;
    }
    local_24 = 0;
    DVar1 = GetModuleFileNameA((HMODULE)0x0,local_128,0x104);
    if (DVar1 == 0) {
      FUN_0052baa0();
    }
    _Str = local_128;
    sVar2 = _strlen(_Str);
    if (0x3c < sVar2 + 0xb) {
      sVar2 = _strlen(_Str);
      _Str = &stack0xfffffea7 + sVar2;
      _strncpy(_Str,&DAT_00545660,3);
    }
    _strlen(_Str);
    local_1c = &stack0xfffffec8;
    FUN_0052baa0();
    FUN_0052bab0();
    FUN_0052bab0();
    FUN_0052bab0();
    FUN_0052bab0(&stack0xfffffec8,&DAT_00545640);
    FUN_0052bab0(&stack0xfffffec8,local_12c);
    ___crtMessageBoxA(&stack0xfffffec8,s_Microsoft_Visual_C___Runtime_Lib_00545618,0x12010);
  }
  else {
    local_8 = (undefined *)0x0;
    (*DAT_005b1b2c)();
    local_8 = (undefined *)0xffffffff;
  }
                    /* WARNING: Subroutine does not return */
  __exit();
}

