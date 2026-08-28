/* AppendChatLogEntry - 0x0041b8c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REGISTER FIX (2026-08-27): the original takes an EIGHTH
 * argument in EAX - the byte length of the message text param_5.  The
 * prologue at 0x41b8c0 is `sub esp,0x98 / push ebx / push ebp / mov
 * ebp,[esp+0xa4] / mov ebx,eax`: EAX is read before it is ever
 * written, so it is a genuine argument, and `ret 0x1c` (0x41bc8a) is
 * exactly the seven stack parameters already declared - so this is an
 * APPEND, not a re-slot.  EBX carries the value into the
 * rep-movsd/rep-movsb pair at 0x41b931/0x41b93a that appends param_5
 * after the name+separator prefix, into the NUL store at 0x41b93c,
 * into the `dec ebx` at 0x41bac2 that eats a leading colour code, and
 * into both WrapChatLineText calls: 0x41bb6a gets the full length,
 * 0x41bbf9 gets the remainder `in_EAX - iVar6` left after the first
 * wrap.  It is now the trailing `regEax` parameter, aliased straight
 * back to Ghidra's `in_EAX` so the body is untouched.
 *
 * All 20 call sites were recovered.  Thirteen compute it inline with
 * the `lea <scratch>,[base+1] / strlen loop / sub eax,<scratch>`
 * idiom - the strlen of the buffer being logged; the scratch is EDX at
 * ten of them, ESI at 0x442271 and 0x4d7da1, and ECX at 0x4d08d2.
 * Four pass the caller's packet body length param_3 - 0x21; both of
 * those callers overwrite their own parameter slot with it at entry
 * (0x423161 and 0x4b54ac), which is why Ghidra prints it as
 * `param_3 - 0x21U` in ApplyBattleActionToContext and as `uVar11` in
 * State11_InBattle_ProcessBattleAction.  One reads the chat length
 * byte at payload+0xd (0x426dce).  Two pass the constant 1 that MSVC
 * folded from strlen(DAT_0054b460), which is the one-character
 * string " " - EBX holds 1 across that whole region (0x4c9c6d,
 * 0x4c9d14, 0x4c9d87).
 *
 * Two of the strlen sites (State11_InBattle_RenderHud 0x4ca9b3 and
 * 0x4cad53) needed a base pointer that the C had lost: Ghidra reuses
 * pcVar4 as the walker and drops the GetLocalizedString result it
 * started from, so that caller gains one local, pcLocStrBase, to
 * hold it.
 *
 * Until now this function had NO declaration in include/functions.h
 * at all (its definition line wraps across two lines, the generator's
 * known blind spot), so every caller compiled it implicitly; a real
 * prototype is added there in address order.
 */
#include "ghidra_types.h"


void AppendChatLogEntry(int param_1,char param_2,char *param_3,char *param_4,char *param_5,
                 undefined2 param_6,char param_7,uint regEax)

{
  char cVar1;
  undefined2 *puVar2;
  uint in_EAX = regEax;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  int extraout_EDX;
  undefined4 *puVar10;
  char *pcVar11;
  undefined2 *puVar12;
  bool bVar13;
  undefined4 local_98; /* Ghidra register slot; was undefined1 [4] */
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined1 local_88;
  undefined4 uStack_81;
  
  if ((param_2 == '\0') || (param_2 == '\a')) {
    pcVar3 = param_4;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)&uStack_81 + (1 - (int)param_4)] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    puVar10 = &uStack_81;
    do {
      pcVar3 = (char *)((int)puVar10 + 1);
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    } while (*pcVar3 != '\0');
    *puVar10 = DAT_00553628;
    pcVar3 = (char *)((int)&uStack_81 + 1);
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar4 = param_5;
    pcVar11 = pcVar3 + (int)&uStack_81 + (1 - ((int)&uStack_81 + 2));
    for (uVar8 = in_EAX >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar8 = in_EAX & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar11 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar11 = pcVar11 + 1;
    }
    pcVar3[(int)&uStack_81 + (in_EAX - ((int)&uStack_81 + 2)) + 1] = '\0';
    FUN_00426120((int)&uStack_81 + 1);
  }
  if (99 < *(int *)(param_1 + 0x3b980)) {
    FUN_0041b840(param_1);
  }
  if (param_3 == (char *)0x0) {
    *(undefined1 *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1) = 0;
  }
  else {
    puVar10 = (undefined4 *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1);
    *puVar10 = *(undefined4 *)param_3;
    puVar10[1] = *(undefined4 *)(param_3 + 4);
    *(char *)(puVar10 + 2) = param_3[8];
  }
  if (param_4 == (char *)0x0) {
    *(undefined1 *)(param_1 + (*(int *)(param_1 + 0x3b980) + 0x2fda) * 0x14) = 0;
  }
  else {
    iVar9 = (int)&local_94 - (int)param_4;
    do {
      cVar1 = *param_4;
      param_4[iVar9] = cVar1;
      param_4 = param_4 + 1;
    } while (cVar1 != '\0');
    puVar2 = (undefined2 *)(local_98 + 3);
    do {
      puVar12 = puVar2;
      puVar2 = (undefined2 *)((int)puVar12 + 1);
    } while (*(char *)((int)puVar12 + 1) != '\0');
    *(undefined2 *)((int)puVar12 + 1) = DAT_00553624;
    iVar9 = *(int *)(param_1 + 0x3b980);
    *(undefined1 *)((int)puVar12 + 3) = DAT_00553626;
    puVar10 = (undefined4 *)(param_1 + (iVar9 + 0x2fda) * 0x14);
    *puVar10 = local_94;
    puVar10[1] = local_90;
    puVar10[2] = local_8c;
    *(undefined1 *)(puVar10 + 3) = local_88;
  }
  if (param_3 != (char *)0x0) {
    iVar9 = 7;
    bVar13 = true;
    pcVar3 = &DAT_00551e24;
    do {
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      bVar13 = *param_3 == *pcVar3;
      param_3 = param_3 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar13);
    if (bVar13) {
      param_2 = '\x05';
      goto LAB_0041bac3;
    }
  }
  if (param_2 == '\x02') {
    cVar1 = *param_5;
    if (cVar1 == '!') {
      param_2 = '\x02';
    }
    else if (cVar1 == '@') {
      param_2 = '\n';
    }
    else if (cVar1 == '#') {
      param_2 = '\v';
    }
    else if (cVar1 == '$') {
      param_2 = '\f';
    }
    else if (cVar1 == '%') {
      param_2 = '\r';
    }
    else if (cVar1 == '^') {
      param_2 = '\x0e';
    }
    else if (cVar1 == '&') {
      param_2 = '\x0f';
    }
    else {
      if (cVar1 != '*') goto LAB_0041bac3;
      param_2 = '\x10';
    }
    in_EAX = in_EAX - 1;
  }
LAB_0041bac3:
  *(char *)(*(int *)(param_1 + 0x3b980) + 0x3c4d8 + param_1) = param_2;
  *(undefined2 *)(param_1 + 0x3f73c + *(int *)(param_1 + 0x3b980) * 2) = param_6;
  pcVar4 = (char *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1);
  pcVar3 = pcVar4 + 1;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar5 = (char *)(param_1 + (*(int *)(param_1 + 0x3b980) * 5 + 0xef42) * 4);
  pcVar11 = pcVar5 + 1;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  cVar1 = (param_7 == '\0') * '\b' + 'H';
  local_98 = (undefined4)((uint)(param_7 == '\0') * 4 + 9);
  /* DROPPED-REG FIX 2026-08-28: RE-SLOT. The three values passed were
     right but sat two slots left of home - orig 0x41bb52-0x41bb6a pushes
     them as param_3/4/5 (esi = the position, ebx = in_EAX, edi = the
     width) while EDX carries the dest (the current row's 0x80-stride
     message field) and EAX the text, param_5 of this function
     ([esp+0xbc] at depth 0xa8 = entry+0x14). */
  iVar6 = WrapChatLineText(0,*(int *)(param_1 + 0x3b980) * 0x80 + 0x3c53c + param_1,
                           (int)(pcVar4 + (int)(pcVar5 + ((2 - (int)pcVar11) - (int)pcVar3))),
                           in_EAX,(int)cVar1,param_5);
  iVar9 = *(int *)(param_1 + 0x3b980) + 1;
  *(int *)(param_1 + 0x3b980) = iVar9;
  if (0 < iVar6) {
    if (99 < iVar9) {
      FUN_0041b840(param_1);
      iVar6 = extraout_EDX;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1) = 0;
    *(undefined1 *)(param_1 + (*(int *)(param_1 + 0x3b980) + 0x2fda) * 0x14) = 0;
    *(undefined2 *)(param_1 + 0x3f73c + *(int *)(param_1 + 0x3b980) * 2) = 0;
    *(char *)(*(int *)(param_1 + 0x3b980) + 0x3c4d8 + param_1) = param_2;
    /* DROPPED-REG FIX 2026-08-28: the continuation - text advanced by
       the first call's return, budget reduced by the same, the dest
       re-evaluated against the incremented row index. */
    WrapChatLineText(0,*(int *)(param_1 + 0x3b980) * 0x80 + 0x3c53c + param_1,
                     (int)(pcVar4 + (int)(pcVar5 + ((2 - (int)pcVar11) - (int)pcVar3))),
                     in_EAX - iVar6,(int)cVar1,param_5 + iVar6);
    if (*(int *)(param_1 + 0x3b97c) == *(int *)(param_1 + 0x3b980) - (int)local_98) {
      *(int *)(param_1 + 0x3b97c) = *(int *)(param_1 + 0x3b97c) + 1;
    }
    iVar9 = *(int *)(param_1 + 0x3b980) + 1;
    *(int *)(param_1 + 0x3b980) = iVar9;
  }
  if (*(int *)(param_1 + 0x3b97c) == (iVar9 - (int)local_98) + -1) {
    *(int *)(param_1 + 0x3b97c) = *(int *)(param_1 + 0x3b97c) + 1;
  }
  piVar7 = DAT_00e53c44;
  if (DAT_00e53c44 != (int *)0x0) {
    while( true ) {
      iVar6 = piVar7[2];
      piVar7 = (int *)*piVar7;
      if ((*(int *)(iVar6 + 0x20) == 0) &&
         (*(int *)(iVar6 + 0x24) == (-(uint)(param_7 != '\0') & 0xffffe4a7) + 0x2329)) break;
      if (piVar7 == (int *)0x0) {
        return;
      }
    }
    Widget_SetChildRange(iVar9,local_98);
    uVar8 = Widget_FindChildIndex();
    if (uVar8 != 0xffffffff) {
      if (*(uint *)(iVar6 + 0x10) <= uVar8) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      *(undefined4 *)(*(int *)(*(int *)(iVar6 + 0xc) + uVar8 * 4) + 0x40) =
           *(undefined4 *)(param_1 + 0x3b97c);
    }
  }
  return;
}

