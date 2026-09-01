/* FUN_00401ee0 - 0x00401ee0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * (2026-09-01: the note below predates a rename - FUN_00426090 is now
 * FindNicknameByUserId.)
 *
 * DROPPED REGISTER RECOVERED (2026-08-24): EAX is a NAME string -- the key
 * FUN_00401c50(param_1, char *) searches the list for.  Seven call sites,
 * five different sources, each pinned individually:
 *   FUN_00402cf0 (2)   its own regEdi, the char * it was itself given
 *   DispatchDirectLinkPacket (2)   (char *)param_3 + 1 -- the name one byte into the
 *                      packet payload.  Frame 0x138 (sub esp,0x12c + three
 *                      saved registers, not four), so [esp+0x140] is +8:
 *                      the second stack parameter.  Then `inc eax`.
 *   DispatchDirectLinkPacket (1)   case 0x1002, a cold block after the epilogue reached
 *                      only from the entry dispatch (`ja 0x403564` at
 *                      0x4032ee); on that path EDI still holds the entry
 *                      `mov edi, eax` -- DispatchDirectLinkPacket's OWN incoming EAX,
 *                      which is still an unrecovered local there.  Passed
 *                      through as-is so the dependency is visible.
 *   FUN_00404330 (1)   &local_20, a 32-byte buffer FUN_00426090 fills
 *   FUN_00411b40 (1)   &local_150, the record the source assembles from
 *                      param_1[6] on the lines above
 */
#include "ghidra_types.h"


void FUN_00401ee0(int param_1,char *regEax)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  puVar2 = (undefined4 *)FUN_00401bb0(param_1);
  if (puVar2 != (undefined4 *)0x0) {
    iVar3 = FUN_00401c50(param_1,regEax);
    if (iVar3 < 0x7f) {
      puVar6 = (undefined4 *)(param_1 + 0x15b0 + iVar3 * 4);
      puVar7 = (undefined4 *)(param_1 + 0x15ac + iVar3 * 4);
      for (iVar5 = 0x7f - iVar3; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
    }
    if (*(void **)(param_1 + 0x17a8) != (void *)0x0) {
      _free(*(void **)(param_1 + 0x17a8));
      *(undefined4 *)(param_1 + 0x17a8) = 0;
    }
    *(undefined4 *)(puVar2[3] + 0x10) = puVar2[4];
    *(undefined4 *)(puVar2[4] + 0xc) = puVar2[3];
    (**(code **)*puVar2)(1);
    iVar3 = *(int *)(param_1 + 0xc10) + -1;
    *(int *)(param_1 + 0xc10) = iVar3;
    piVar4 = DAT_00e53c44;
    if (DAT_00e53c44 != (int *)0x0) {
      while( true ) {
        piVar1 = (int *)*piVar4;
        if ((*(int *)(piVar4[2] + 0x20) == 0) && (*(int *)(piVar4[2] + 0x24) == 20000)) break;
        piVar4 = piVar1;
        if (piVar1 == (int *)0x0) {
          return;
        }
      }
      Widget_SetChildRange(iVar3,7);
    }
  }
  return;
}

