/* FUN_005071a0 - 0x005071a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BlitRLESprite's dropped param_1 (this, ECX)/rleData (4th arg, in_EAX)
 * were recovered via objdump at this function's two call sites
 * (0x5072cf and 0x5072ee): both show
 *   mov ecx, [ebx+0x28]
 *   sub ecx, [ebx+0x13c]   ; -> this (param_1 arg)
 *   lea eax, [ebx+0x38]    ; -> rleData
 * i.e. `this` = *(param_1+0x28) - *(param_1+0x13c), and `rleData` =
 * (byte *)(param_1+0x38) - the same string field this function's own
 * strlen loops (local_8/local_4 computations above) already walk.
 *
 * FIXED (2026-07-15): both SetClipRect calls dropped their 4 corner
 * args. Confirmed via angr: `ebx` at the first call is this function's
 * own `param_1` (mov ebx,ecx at entry, __fastcall's this, never
 * reassigned), so x1/x2/y1/y2 = *(param_1+0x28)/+0x30/+0x34/+0x2c - the
 * +0x34 field isn't otherwise referenced in this file but is a real
 * struct field (angr: mov esi,[ebx+0x34]). The second call is the
 * standard full-screen reset (0,0x31f,0x257,0).
 */
#include "ghidra_types.h"


void __fastcall FUN_005071a0(int param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_8;
  int local_4;
  
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return;
  }
  SetClipRect(*(int *)(param_1 + 0x28), *(int *)(param_1 + 0x30),
              *(int *)(param_1 + 0x34), *(int *)(param_1 + 0x2c));
  if (*(char *)(param_1 + 0x1c) == '\0') {
    uVar5 = *(undefined4 *)(param_1 + 0x2c);
    uVar6 = 0x7bef;
  }
  else {
    if (*(char *)(param_1 + 4) != '\0') {
      FUN_0040c8f0(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c),
                   *(undefined4 *)(param_1 + 0x13c));
      iVar3 = local_8;
      if (local_8 == -1) {
        pcVar2 = (char *)(param_1 + 0x38);
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        iVar3 = (int)pcVar2 - (param_1 + 0x39);
      }
      iVar3 = iVar3 * 6;
      if (iVar3 < *(int *)(param_1 + 0x13c)) {
        *(int *)(param_1 + 0x13c) = iVar3;
      }
      iVar4 = *(int *)(param_1 + 0x13c) + *(int *)(param_1 + 0x30);
      if (iVar3 - iVar4 != 0 && iVar4 <= iVar3) {
        *(int *)(param_1 + 0x13c) = iVar3 - *(int *)(param_1 + 0x30);
      }
      if (local_8 == -1) {
        pcVar2 = (char *)(param_1 + 0x38);
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        local_8 = (int)pcVar2 - (param_1 + 0x39);
      }
      if (local_4 == -1) {
        pcVar2 = (char *)(param_1 + 0x38);
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        local_4 = (int)pcVar2 - (param_1 + 0x39);
      }
      FUN_004eb7a0((local_8 * 6 - *(int *)(param_1 + 0x13c)) + *(int *)(param_1 + 0x28),
                   local_4 * 6 + local_8 * -6 + 2,0xc);
      BlitRLESprite(*(int *)(param_1 + 0x28) - *(int *)(param_1 + 0x13c),
                    *(undefined4 *)(param_1 + 0x2c),0xffff,(byte *)(param_1 + 0x38));
      goto LAB_005072f6;
    }
    uVar5 = *(undefined4 *)(param_1 + 0x2c);
    uVar6 = 0xffff;
  }
  BlitRLESprite(*(int *)(param_1 + 0x28) - *(int *)(param_1 + 0x13c),uVar5,uVar6,
                (byte *)(param_1 + 0x38));
LAB_005072f6:
  SetClipRect(0, 0x31f, 0x257, 0);
  return;
}

