/* FUN_005039a0 - 0x005039a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX and EDI RECOVERED (2026-08-25).  EAX is `lea eax,[esp+0x30]` = -0x4960
 * under FUN_00501770's -0x4990 constant, which that function does not declare
 * either -- because it is 0xc into its `sockaddr local_496c`, i.e.
 * local_496c.sa_data + 10, the same field the source already writes through
 * SUBFIELD(local_496c.sa_data,10,...).  EDI is the VALUE at -0x497c, and the
 * line immediately after the call is `param_1 = local_497c`, which names it.
 *
 * EBX stays open: it is a zero-extended word off the packet cursor, and the
 * source passes the same address as a dword, so the width needs settling
 * before the expression can be written honestly.
 */
#include "ghidra_types.h"


void FUN_005039a0(int param_1,undefined4 param_2,int *param_3,undefined4 regEax,
                  undefined4 regEdi)

{
  int *piVar1;
  char cVar2;
  undefined4 unaff_EBX;
  
  piVar1 = param_3;
  cVar2 = FUN_004fe860(regEdi,&param_3);
  if ((((cVar2 != '\0') && (*param_3 != 0)) && (param_3[2] == param_1)) &&
     ((((short)param_3[3] == (short)param_2 && ((int *)param_3[4] == piVar1)) &&
      ((short)param_3[5] == (short)unaff_EBX)))) {
    *(undefined1 *)(param_3 + 7) = 0;
    return;
  }
  FUN_004fe8d0(regEax,param_1,param_2,piVar1,unaff_EBX);
  return;
}

