/* FUN_005039a0 - 0x005039a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX, EDI, EBX RECOVERED (2026-08-31, correcting the 2026-08-25 pass).  At
 * the one site, 0x502403 in CommP2POwner_ProcessPacket, THREE pushes are pending, so
 * `lea eax,[esp+0x30]` (0x5023fd) is esp_b+0x24 = &local_496c itself -- the
 * 16-char id the branch just assembled, the string FUN_004fe8d0's param_2
 * copy loop consumes -- not sa_data+10 (the 08-25 note missed the pushes).
 * EDI is loaded at 0x5023d9 from [esp+0x20] = local_4970 = param_1 - 0x2c8,
 * the engine object, matching the else-branch twin FUN_00503a50(local_4970,
 * &local_496c); the [esp+0x14]=local_497c read at 0x50240c is the post-call
 * EDI RESTORE the 08-25 note mistook for the input.  EBX is `xor esi,esi /
 * mov si,[ebx]` (0x5023ee/0x5023f0) then `mov ebx,esi` (0x502401): the
 * zero-extended WORD at record+0x1b, the port of the second address pair,
 * landing word-wide in FUN_004fe8d0's param_6.  Width settled: pass it as
 * (undefined4)*(ushort *)(rec + 0x1b).
 *
 * FindP2PPeerRecord ID RECOVERED (2026-10-29): the call at 0x5039ae dropped
 * ESI = `mov esi,eax` (0x5039a6) = regEax; witness: the same ESI is pushed
 * as FUN_004fe8d0's id at 0x5039f4, ported as regEax.
 */
#include "ghidra_types.h"


void FUN_005039a0(int param_1,undefined4 param_2,int *param_3,undefined4 regEax,
                  undefined4 regEdi,undefined4 regEbx)

{
  int *piVar1;
  char cVar2;
  
  piVar1 = param_3;
  cVar2 = FindP2PPeerRecord(regEdi,(int *)&param_3,(char *)regEax);
  if ((((cVar2 != '\0') && (*param_3 != 0)) && (param_3[2] == param_1)) &&
     ((((short)param_3[3] == (short)param_2 && ((int *)param_3[4] == piVar1)) &&
      ((short)param_3[5] == (short)regEbx)))) {
    *(undefined1 *)(param_3 + 7) = 0;
    return;
  }
  FUN_004fe8d0((undefined4 *)regEdi,(int)regEax,param_1,(short)param_2,(int)piVar1,(short)regEbx);
  return;
}

