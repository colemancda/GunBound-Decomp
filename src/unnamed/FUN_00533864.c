/* FUN_00533864 - 0x00533864 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___libm_error_support
   
   Library: Visual Studio 2003 Release */

void ___libm_error_support(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_28;
  undefined **local_24;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  if (0xa1 < param_4) {
    if (param_4 < 0x3eb) {
      if (param_4 != 0x3ea) {
        if (param_4 == 0xa2) {
          local_28 = 4;
          goto LAB_00533a16;
        }
        if (param_4 == 0xa6) {
          local_28 = 3;
          local_24 = (undefined **)s_exp10_00549ba0;
        }
        else {
          if (param_4 != 0xaa) {
            if (param_4 == 0xab) {
              local_24 = (undefined **)&DAT_00549ba8;
              goto LAB_00533aaf;
            }
            if (param_4 == 1000) {
              local_24 = &PTR_DAT_005492f4;
            }
            else {
              if (param_4 != 0x3e9) {
                return;
              }
              local_24 = (undefined **)s_log10_005492ec;
            }
            goto LAB_00533aa5;
          }
          local_28 = 2;
          local_24 = (undefined **)&DAT_00549ba8;
        }
        goto LAB_00533a1d;
      }
      local_24 = &PTR_DAT_005492fc;
    }
    else if (param_4 == 0x3eb) {
      local_24 = (undefined **)&DAT_005492bc;
    }
    else if (param_4 == 0x3ec) {
      local_24 = (undefined **)&DAT_00549298;
    }
    else if (param_4 == 0x3ed) {
      local_24 = (undefined **)s_floor_00549290;
    }
    else {
      if (param_4 == 0x3ee) goto LAB_00533a7d;
      if (param_4 != 0x3ef) {
        return;
      }
      local_24 = (undefined **)&DAT_00549280;
    }
LAB_00533aa5:
    *param_3 = *param_1;
    goto LAB_00533aaf;
  }
  if (param_4 == 0xa1) {
    local_28 = 3;
LAB_00533a16:
    local_24 = (undefined **)&DAT_00549b98;
    goto LAB_00533a1d;
  }
  if (param_4 < 0x19) {
    if (param_4 == 0x18) {
      local_28 = 3;
      goto LAB_0053390e;
    }
    if (param_4 == 2) {
      local_28 = 2;
      local_24 = &PTR_DAT_005492f4;
    }
    else {
      if (param_4 == 3) {
        local_24 = &PTR_DAT_005492f4;
LAB_00533aaf:
        local_20 = *param_1;
        local_28 = 1;
        local_18 = *param_2;
        local_10 = *param_3;
        iVar1 = (*(code *)PTR_FUN_0056cc94)(&local_28);
        if (iVar1 == 0) {
          puVar2 = (undefined4 *)FUN_0052b6d4();
          *puVar2 = 0x21;
        }
        goto LAB_00533ae2;
      }
      if (param_4 == 8) {
        local_28 = 2;
        local_24 = (undefined **)s_log10_005492ec;
      }
      else {
        if (param_4 == 9) {
          local_24 = (undefined **)s_log10_005492ec;
          goto LAB_00533aaf;
        }
        if (param_4 != 0xe) {
          if (param_4 != 0xf) {
            return;
          }
          local_24 = &PTR_DAT_005492fc;
          goto LAB_0053395b;
        }
        local_28 = 3;
        local_24 = &PTR_DAT_005492fc;
      }
    }
  }
  else {
    if (param_4 == 0x19) {
      local_24 = &PTR_DAT_005492f8;
LAB_0053395b:
      local_20 = *param_1;
      local_18 = *param_2;
      local_10 = *param_3;
      local_28 = 4;
      (*(code *)PTR_FUN_0056cc94)(&local_28);
      goto LAB_00533ae2;
    }
    if (param_4 == 0x1a) {
      *param_3 = 0x3ff0000000000000;
      return;
    }
    if (param_4 != 0x1b) {
      if (param_4 != 0x1c) {
        if (param_4 != 0x1d) {
          return;
        }
        local_24 = &PTR_DAT_005492f8;
        goto LAB_00533aa5;
      }
LAB_00533a7d:
      local_24 = &PTR_DAT_005492f8;
      goto LAB_00533aaf;
    }
    local_28 = 2;
LAB_0053390e:
    local_24 = &PTR_DAT_005492f8;
  }
LAB_00533a1d:
  local_20 = *param_1;
  local_18 = *param_2;
  local_10 = *param_3;
  iVar1 = (*(code *)PTR_FUN_0056cc94)(&local_28);
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)FUN_0052b6d4();
    *puVar2 = 0x22;
  }
LAB_00533ae2:
  *param_3 = local_10;
  return;
}

