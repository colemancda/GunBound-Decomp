/* FUN_00508d00 - 0x00508d00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Widget_AddChild `this` RECOVERED (2026-10-30): 0x50e670 takes the
 * parent in EBX and the child on the stack. At 0x508df5/0x508e12/0x508e74
 * EBX = esi, the new panel (`mov ebx,esi` at 0x508df3 and again at 0x508e72 after the strlen reuses EBX), puVar3 here;
 * each call now passes it as regEbx.
 *
 * EDI RECOVERED (2026-10-30): the body reads EDI (the buddy name) with no
 * earlier write - `push edi` for __mbsicmp at 0x508d4d, `test edi,edi` at
 * 0x508e17 - and ends in ret 4 with only the manager on the stack. It is
 * now the trailing parameter regEdi, like FUN_00508ea0's. The inline
 * strlen at 0x508e17-0x508e2e leaves the length in EAX and `mov ebx,eax`
 * at 0x508e32 passes it to AssignStringBuffer (0x4056c0, `test ebx,ebx`
 * as its first instruction) as the dropped EBX length. `push edi` at
 * 0x508e39, before the GetLocalizedString pushes, is the third argument
 * of the sprintf at 0x508e4f (`add esp,0xc` at 0x508e54).
 */
#include "ghidra_types.h"


void FUN_00508d00(int param_1,uchar *regEdi)

{
  uchar uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uchar *puVar5;
  char *_Format;
  uint uVar6;
  bool bVar6;
  char local_8c [128];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053cf6e) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar3 = *(undefined4 **)(param_1 + 4);
joined_r0x00508d28:
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = operator_new(0xa8);
    local_4 = 0;
    if (puVar3 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      Panel_BaseConstructor(puVar3);
      *puVar3 = &PTR_LAB_00557d50;
    }
    local_4 = 0xffffffff;
    bVar6 = g_currentGameState == 0xb;
    puVar3[9] = 0x2711;
    puVar3[0x13] = 0;
    puVar3[0x11] = 0x2c6;
    puVar3[0x12] = 2;
    puVar3[10] = 0x12d;
    puVar3[0xb] = 0xd9;
    puVar3[0xc] = 200;
    puVar3[0xd] = 0x8a;
    *(bool *)((int)puVar3 + 0x1e) = bVar6;
    uVar4 = CreateLabelWidget(0,0x2ca,0x44,0x66,0x37,0x1a);
    Widget_AddChild(uVar4,(int)puVar3);
    uVar4 = CreateLabelWidget(1,0x2cb,0x82,0x66,0x37,0x1a);
    Widget_AddChild(uVar4,(int)puVar3);
    /* The inline strlen leaves the length in EAX (0 for a NULL name), and
     * `mov ebx,eax` hands it to AssignStringBuffer as its EBX length. */
    uVar6 = 0;
    puVar5 = regEdi;
    if (regEdi != (uchar *)0x0) {
      do {
        uVar1 = *puVar5;
        puVar5 = puVar5 + 1;
      } while (uVar1 != '\0');
      uVar6 = (uint)(puVar5 - (regEdi + 1));
    }
    AssignStringBuffer(puVar3 + 0x14,regEdi,uVar6);
    _Format = (char *)GetLocalizedString(&g_localizedStringTable,0xfa1);
    /* The name (EDI) is pushed before the GetLocalizedString call, so it
     * is _sprintf's third argument. */
    _sprintf(local_8c,_Format,regEdi);
    uVar4 = CreateStaticTextWidget(0x17,0x2b,0x9a,0x33,local_8c,0xffff);
    Widget_AddChild(uVar4,(int)puVar3);
    PanelManager_Register(puVar3);
  }
  else {
    iVar2 = puVar3[2];
    puVar3 = (undefined4 *)*puVar3;
    if ((((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 0x2711)) ||
        (*(int *)(iVar2 + 0x4c) != 0)) ||
       (iVar2 = __mbsicmp(*(uchar **)(iVar2 + 0x50),regEdi), iVar2 != 0))
    goto joined_r0x00508d28;
  }
  return;
}

