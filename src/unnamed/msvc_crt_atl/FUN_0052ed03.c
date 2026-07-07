/* FUN_0052ed03 - 0x0052ed03 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x0052ed47) */
/* WARNING: Removing unreachable block (ram,0x0052ed34) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    ___sse2_available_init
   
   Library: Visual Studio 2003 Release */

undefined4 ___sse2_available_init(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  uint uVar4;
  uint local_20;
  int local_1c;
  uint local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  local_20 = 0;
  local_1c = 0;
  local_18 = local_18 & 0xffffff00;
  uVar4 = (uint)(in_NT & 1) * 0x4000 | (uint)(in_IF & 1) * 0x200 | (uint)(in_TF & 1) * 0x100 | 0x40
          | (uint)(in_AF & 1) * 0x10 | 4 | (uint)(in_ID & 1) * 0x200000 |
          (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000
  ;
  uVar2 = uVar4 ^ 0x200000;
  if (((uint)((uVar2 & 0x4000) != 0) * 0x4000 | (uint)((uVar2 & 0x200) != 0) * 0x200 |
       (uint)((uVar2 & 0x100) != 0) * 0x100 | (uint)((uVar2 & 0x40) != 0) * 0x40 |
       (uint)((uVar2 & 0x10) != 0) * 0x10 | (uint)((uVar2 & 4) != 0) * 4 |
       (uint)((uVar2 & 0x200000) != 0) * 0x200000 | (uint)((uVar2 & 0x40000) != 0) * 0x40000) !=
      uVar4) {
    iVar3 = cpuid_basic_info(0);
    local_18 = *(uint *)(iVar3 + 4);
    local_14 = *(undefined4 *)(iVar3 + 8);
    local_10 = *(undefined4 *)(iVar3 + 0xc);
    piVar1 = (int *)cpuid_Version_info(1);
    local_1c = *piVar1;
    local_20 = piVar1[2];
  }
  _DAT_00f28310 = 0;
  DAT_00f2830c = 0;
  if (((local_20 & 0x4000000) != 0) && (iVar3 = FUN_0052ecce(), iVar3 != 0)) {
    _DAT_00f28310 = 1;
    iVar3 = _strncmp(s_AuthenticAMD_005456f4,(char *)&local_18,0xc);
    if ((iVar3 != 0) ||
       (uVar2 = local_1c >> 8 & 0xf,
       (~-(uint)(uVar2 != 0xf) & local_1c >> 0x14 & 0xffU) + uVar2 != 0xf)) {
      DAT_00f2830c = 1;
    }
  }
  return 0;
}

