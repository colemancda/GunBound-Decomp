/* FUN_004fd880 - 0x004fd880 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DEAD-CODED COUNT HEADER + DROPPED REGISTERS RECOVERED (2026-09-01).  The
 * raw port dropped the record-count word the binary writes at the frame base
 * (0x4fd8ca-0x4fd8cc `mov word[esp+0x14],ax`, ax = (list end - list start) /
 * 0x12) and started the name copies there instead, and it called FUN_00502500
 * with the opcode bound into the ECX/length slot.  Rebuilt from
 * 0x4fd8a2-0x4fd945: the frame is [count:u16][0x10-char names ...][0x14-byte
 * final record]; EDX = frame base, ECX = (cursor - frame base) + 0x14 (the
 * final record), EBX = this (param_1, reloaded `mov ebx,[esp+0x1c]` at
 * 0x4fd92e), opcode 0x3004 pushed at 0x4fd940.  NOTE: 0x4fd8a2 is where
 * Ghidra split off the phantom twin FUN_004fd8a2.c; this file is the real,
 * complete model.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall FUN_004fd880(int param_1,int param_2,char *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *_Dest;
  uint uVar4;
  /* One contiguous frame: [count:u16][names][final 0x14 record]. */
  char frame [0x1770];
  undefined4 uStack_4;

  uStack_4 = 0x4fd88a;
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0x1700;
  }
  iVar1 = *(int *)(param_2 + 4);
  *(ushort *)frame = (iVar1 == 0) ? 0 : (ushort)((*(int *)(param_2 + 8) - iVar1) / 0x12);
  _Dest = frame + 2;
  iVar3 = 0;
  for (uVar4 = 0;
      (iVar1 = *(int *)(param_2 + 4), iVar1 != 0 &&
      (uVar4 < (uint)((*(int *)(param_2 + 8) - iVar1) / 0x12))); uVar4 = uVar4 + 1) {
    _strncpy(_Dest,(char *)(iVar3 + iVar1),0x10);
    _Dest = _Dest + 0x10;
    iVar3 = iVar3 + 0x12;
  }
  _strncpy(_Dest,param_3,0x14);
  /* opcode -> stack param, ECX = payload length, EDX = frame, EBX = this. */
  uVar2 = FUN_00502500((int)(_Dest + 0x14 - frame),(undefined4 *)frame,0x3004,param_1);
  return uVar2;
}

