/* FUN_0050dfd0 - 0x0050dfd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BlitRLESprite's dropped 4th arg (rleData) and its ECX/`this` arg were
 * recovered from objdump at this file's single call site (0x50dff8):
 *   lea  ebx,[esi + 0x3a]      ; ebx = param_1 + 0x3a  (rleData, before loop)
 *   ...
 *   mov  eax,ebx               ; EAX = rleData for this iteration <-- dropped
 *   mov  ecx,[esi + 0x28]      ; ECX = *(int *)(param_1 + 0x28)    <-- dropped
 *   call BlitRLESprite
 *   ...
 *   add  ebx,0x80              ; rleData advances by 0x80 bytes/iteration,
 *                               ; in lockstep with iVar1's +0xe/iteration.
 * Neither *(param_1+0x28) nor the param_1+0x3a-based array is referenced
 * anywhere else in this function, so both are new to this fix.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050dfd0(int param_1)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;

  if (*(char *)(param_1 + 0x1e) == '\0') {
    iVar1 = 0;
    pbVar3 = (byte *)(param_1 + 0x3a);
    do {
      if (*(int *)(param_1 + 0x2c) < iVar1) break;
      BlitRLESprite(*(int *)(param_1 + 0x28),iVar1 + *(int *)(param_1 + 0x2c),
                    *(undefined2 *)(param_1 + 0x38),pbVar3);
      iVar1 = iVar1 + 0xe;
      pbVar3 = pbVar3 + 0x80;
    } while (iVar1 < 0x8c);
    if (*(char *)(param_1 + 0x1e) == '\0') {
      uVar2 = 0;
      if (*(int *)(param_1 + 0x10) != 0) {
        if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        do {
          (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x24))();
          uVar2 = uVar2 + 1;
        } while (uVar2 < *(uint *)(param_1 + 0x10));
      }
    }
  }
  return;
}

