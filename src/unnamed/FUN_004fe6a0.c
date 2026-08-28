/* FUN_004fe6a0 - 0x004fe6a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the connection NODE to close and
 * erase - held in EDI for the whole body (`mov edi,eax` at 0x4fe6a2),
 * verified present in the engine's list before its socket at +8 is
 * closed and FUN_004ff720 unlinks it. param_2 is the vtable'd ENGINE
 * object: the virtual through *param_2+8 fires first, then `add esi,4`
 * at 0x4fe6b2 steps to the raw list at engine+4 for the walk and the
 * erase - which is why the FUN_004ff720 call passes param_2 + 1.
 *
 * The virtual call was also short: the binary pushes EDI then ECX
 * (0x4fe6a8/0x4fe6a9), so it receives (param_1, node), not the single
 * argument the port showed.
 *
 * Six call sites. Five load ECX with 0; the sixth,
 * CommEngineNotifyWndProc's 0x20 arm at 0x4fe7ba, leaves ECX stale in
 * the original - the recovered call passes 0 there to match the other
 * five rather than reproduce an uninitialised read.
 */
#include "ghidra_types.h"


void __fastcall FUN_004fe6a0(undefined4 param_1,int *param_2,int *regEax)

{
  int *in_EAX = regEax;
  int *piVar1;
  
  (**(code **)(*param_2 + 8))(param_1,in_EAX);
  piVar1 = (int *)param_2[1];
  if (piVar1 != (int *)0x0) {
    while (in_EAX != piVar1) {
      piVar1 = (int *)*piVar1;
      if (piVar1 == (int *)0x0) {
        return;
      }
    }
    if (in_EAX[2] != 0xffffffff) {
      closesocket(in_EAX[2]);
    }
    FUN_004ff720(param_2 + 1,in_EAX);
  }
  return;
}

