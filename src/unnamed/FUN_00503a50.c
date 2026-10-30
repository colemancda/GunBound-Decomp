/* FUN_00503a50 - 0x00503a50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * StringMap_RemoveKey_ac CALL RECOVERED (2026-10-29): it was called with no
 * arguments; now passes the key (EDX, 0x503b87) and the peer table at
 * param_1+0x290 (EAX, 0x503b81) - see the comment at the call.
 *
 * FindP2PPeerRecord ID RECOVERED (2026-10-29): the call at 0x503a67 dropped
 * ESI = `mov esi,ebx` (0x503a65) with EBX = `mov ebx,[esp+0x20]` (0x503a54)
 * = the second stack argument, param_2 - the same EBX the id copy loop
 * reads at 0x503b64 (ported off iVar7 = param_2).
 *
 * PROTOTYPE SETTLED (2026-10-29): two stack arguments and nothing else -
 * `ret 8` at 0x503b97; EBX = [esp+0x20] (0x503a54) and EBP = [esp+0x20]
 * after one more push (0x503a59) are both loaded from the stack, and ECX/
 * EDX/EDI are written before any read.  Both binary callers (0x50241c in
 * FUN_00501770, 0x503c2c in FUN_00503bb0) push exactly two dwords, so
 * functions.h now declares (undefined4 *param_1, int param_2).
 */
#include "ghidra_types.h"


void FUN_00503a50(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char cVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  char acStack_12 [17];
  undefined1 uStack_1;
  uint uVar8;
  
  iVar7 = param_2;
  puVar2 = param_1;
  cVar4 = FindP2PPeerRecord((undefined4)param_1,(int *)&param_1,(char *)param_2);
  puVar3 = param_1;
  if (cVar4 != '\0') {
    puVar1 = param_1;
    if (param_1[0x15] != 0) {
      uVar6 = 0;
      if (param_1[0x16] != 0) {
        piVar9 = (int *)param_1[0x14];
        do {
          if (*piVar9 != 0) {
            puVar10 = (undefined4 *)((int *)param_1[0x14])[uVar6];
            goto joined_r0x00503aa3;
          }
          uVar6 = uVar6 + 1;
          piVar9 = piVar9 + 1;
        } while (uVar6 < (uint)param_1[0x16]);
      }
    }
    puVar10 = (undefined4 *)0x0;
joined_r0x00503aa3:
    while (param_1 = puVar10, param_1 != (undefined4 *)0x0) {
      puVar10 = param_1;
      if ((param_1 != (undefined4 *)0x0) &&
         (puVar10 = (undefined4 *)param_1[0x5d8], puVar10 == (undefined4 *)0x0)) {
        uVar6 = (uint)param_1[0x5d9] % (uint)puVar3[0x16];
        do {
          uVar6 = uVar6 + 1;
          iVar7 = param_2;
          if ((uint)puVar3[0x16] <= uVar6) break;
          puVar1 = *(undefined4 **)(puVar3[0x14] + uVar6 * 4);
          if (puVar1 != (undefined4 *)0x0) {
            puVar10 = puVar1;
          }
        } while (puVar10 == (undefined4 *)0x0);
      }
      (**(code **)*puVar2)
                (0,iVar7,*(undefined2 *)(param_1 + 4),param_1 + 5,
                 *(undefined2 *)((int)param_1 + 0x12),param_1 + 1);
      puVar1 = param_1;
    }
    uVar6 = 0;
    param_1 = puVar1;
    if (puVar3[0x21] != 0) {
      iVar11 = 0;
      if (puVar3[0x21] == 0) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      do {
        iVar7 = puVar3[0x20] + iVar11;
        (**(code **)*puVar2)
                  (0,param_2,*(undefined2 *)(iVar7 + 0xc),iVar7 + 0x10,*(undefined2 *)(iVar7 + 0xe),
                   iVar7);
        uVar6 = uVar6 + 1;
        iVar11 = iVar11 + 0x1750;
        iVar7 = param_2;
      } while (uVar6 < (uint)puVar3[0x21]);
    }
  }
  uVar6 = 0;
  do {
    uVar8 = uVar6;
    if (*(char *)(uVar6 + iVar7) == '\0') break;
    bVar5 = (char)uVar6 + 1;
    uVar8 = (uint)bVar5;
    acStack_12[uVar6] = *(char *)(uVar6 + iVar7);
    uVar6 = uVar8;
  } while (bVar5 < 0x10);
  uStack_1 = (undefined1)uVar8;
  acStack_12[uVar8] = '\0';
  /* RECOVERED (2026-10-29), orig 0x503b8b: EAX = `lea eax,[ebp+0x290]`
   * (0x503b81) with EBP = the incoming param_1 (`mov ebp,[esp+0x20]` at
   * 0x503a59, never rewritten; held here in puVar2 because param_1 is
   * reused) and EDX = `lea edx,[esp+0x12]` (0x503b87) = acStack_12, the
   * 16-char id the loop above just copied and NUL-terminated. */
  StringMap_RemoveKey_ac(acStack_12,(int *)((int)puVar2 + 0x290));
  return;
}

