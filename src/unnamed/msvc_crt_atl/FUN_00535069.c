/* FUN_00535069 - 0x00535069 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x0053533f) */
/* WARNING: Removing unreachable block (ram,0x005352b9) */
/* WARNING: Removing unreachable block (ram,0x0053541b) */
/* WARNING: Removing unreachable block (ram,0x005352cb) */
/* WARNING: Removing unreachable block (ram,0x005352d3) */
/* WARNING: Removing unreachable block (ram,0x005352d9) */
/* WARNING: Removing unreachable block (ram,0x005352dc) */
/* WARNING: Removing unreachable block (ram,0x005352e3) */
/* WARNING: Removing unreachable block (ram,0x005352ed) */
/* WARNING: Removing unreachable block (ram,0x005353b7) */
/* WARNING: Removing unreachable block (ram,0x005353b1) */
/* WARNING: Removing unreachable block (ram,0x005353bd) */
/* WARNING: Removing unreachable block (ram,0x005353da) */
/* WARNING: Removing unreachable block (ram,0x005353dc) */
/* WARNING: Removing unreachable block (ram,0x005353e4) */
/* WARNING: Removing unreachable block (ram,0x005353e7) */
/* WARNING: Removing unreachable block (ram,0x005353ec) */
/* WARNING: Removing unreachable block (ram,0x005353ef) */
/* WARNING: Removing unreachable block (ram,0x00535424) */
/* WARNING: Removing unreachable block (ram,0x005353f6) */
/* WARNING: Removing unreachable block (ram,0x005353fd) */
/* WARNING: Removing unreachable block (ram,0x0053543b) */
/* WARNING: Removing unreachable block (ram,0x00535442) */
/* WARNING: Removing unreachable block (ram,0x0053544a) */

undefined4 FUN_00535069(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  for (; (((cVar1 = *param_3, cVar1 == ' ' || (cVar1 == '\t')) || (cVar1 == '\n')) ||
         (cVar1 == '\r')); param_3 = param_3 + 1) {
  }
                    /* WARNING: Could not recover jumptable at 0x005350cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (*(code *)PTR_LAB_0053546d)();
  return uVar2;
}

