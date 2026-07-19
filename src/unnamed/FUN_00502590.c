/* FUN_00502590 - 0x00502590 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __fastcall
FUN_00502590(ushort param_1,int param_2,char *param_3,undefined2 param_4,undefined4 *param_5)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  char local_2ee8 [16];
  undefined2 local_2ed8;
  ushort local_2ed6;
  undefined4 local_2ed4 [1495];
  undefined1 local_1778 [5996];
  undefined4 uStack_c;
  
  uStack_c = 0x5025a0;
  if (0xff < param_1) {
    param_1 = 0xff;
  }
  _strncpy(local_2ee8,param_3,0x10);
  local_2ed8 = param_4;
  puVar3 = local_2ed4;
  for (uVar2 = (uint)(param_1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = *param_5;
    param_5 = param_5 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar2 = param_1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar3 = *(undefined1 *)param_5;
    param_5 = (undefined4 *)((int)param_5 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  local_2ed6 = param_1;
  /* RECOVERED (2026-07-19), orig 0x502602-0x50261c (frame base anchored on the
   * strncpy dest `lea ecx,[esp+0x18]` at 0x5025b9 = local_2ee8):
   *   push 0x1770 / lea eax,[esp+0x1790] / push eax ; capacity, output=local_1778
   *   push ecx (=[ebx+0x1a78])                      ; schedule
   *   lea ecx,[esp+0x28]                            ; ECX = INPUT = local_2ee8
   *   lea ecx,[eax+0x1f] / imul 0x2aaaaaab / ...    ; EAX = INPUTLEN =
   *                                                 ;   ((param_1+0x1f)/0xc)*0xc
   * 0x1f = the 0x14-byte header (16-byte name + param_4 + param_1) plus the
   * 0xb round-up to a whole 12-byte block. */
  cVar1 = (char)FUN_004f7210(*(undefined4 *)(param_2 + 0x1a78),(int)local_1778,6000,
                             (byte *)local_2ee8,(((int)param_1 + 0x1f) / 0xc) * 0xc);
  if (cVar1 == '\0') {
    return;
  }
  FUN_00502500(0x2000);
  return;
}

