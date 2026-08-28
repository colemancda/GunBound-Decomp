/* FUN_0047be80 - 0x0047be80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX is a dropped register argument and is the inner lookup key. At
 * 0x0047be84, the third instruction of the function, mov esi,eax reads EAX
 * before anything writes it - the first write to EAX is mov eax,[0xea0e1c]
 * at 0x0047be86, two bytes later - and ESI carries it to 0x0047beb2 cmp
 * eax,esi where it is compared against *(node + 8) while walking the
 * second-level list. EDX is the outer key against *(node + 4). ECX is a
 * PHANTOM: its first touch, 0x0047be8e mov ecx,[eax + 4], is a write, so the
 * declared param_1 occupies the __fastcall ECX slot but carries nothing in.
 * It is left in place only so the two genuine stack parameters keep their
 * positions - deleting it would move param_2 out of EDX and into ECX and
 * silently corrupt the outer key.
 *
 * ret 8 at all three exits (0x0047bea9, 0x0047beca, 0x0047bfcb) means
 * exactly two stack arguments, matching the two stack parameters the
 * four-parameter __fastcall declaration already implies, so regEax is
 * appended rather than re-slotted. The frame is sub esp,8 then push esi,
 * plus push ebx/ebp/edi on the path that reaches the copy loop: 8 + 4 + 4 +
 * 4 + 4 = 24 bytes, and no unbalanced push exists anywhere between
 * 0x0047becd and 0x0047bfc2, so the whole copy path runs at depth entry_esp
 * - 0x18 with a pending-push term of zero. [esp+0x1c] is therefore entry_esp
 * + 4, the first stack argument, and [esp+0x20] is entry_esp + 8, the
 * second. Both are confirmed twice: 0x0047bf74 imul ecx,[esp+0x20] and
 * 0x0047bf7c add ecx,[esp+0x1c] are the two halves of the single source
 * expression uVar10 * param_4 + param_3, and 0x0047bf87 mov [esp+0x1c],esi
 * is the source's own statement param_3 = iVar8 writing that same slot back.
 * The only other stack traffic, the scratch stores at [esp+0x10] and
 * [esp+0x14], lands at entry_esp - 8 and entry_esp - 4, exactly filling the
 * eight bytes carved by sub esp,8 - and the entry_esp - 4 slot is read back
 * at 0x0047bf56 mov ebx,[esp+0x14] as the source's iVar4 = iVar1. No third
 * argument slot at entry_esp + 0xc is ever touched, consistent with ret 8.
 * Ghidra promoted every frame slot to a register temp, so rule 3's local_XXX
 * cross-check is unavailable and these checks stand in for it.
 *
 * There are no ported call sites to update. The binary has four call sites
 * in two callers: 0x0047ddec and 0x0047de14 inside the function at
 * 0x0047dc00, and 0x00481297 and 0x004812bf inside the function at
 * 0x004810c0. Both callers live in address ranges no PROGRESS.csv row
 * covers, and docs/vtable_census.txt lines 665 and 713 list them as UNCARVED
 * slot 3 - the Draw slot, which sibling vtables fill with RenderMobile and
 * DrawSuperFlameEffect - of the projectile vtables at 0x556078 and 0x556110.
 * At every one of the four sites the value is *(int *)(this + 0x30): the
 * last write to EAX before each call is mov eax,[esi + 0x30] at 0x0047dde6,
 * 0x0047de0c, 0x00481291 and 0x004812b7, with one to three argument-setup
 * instructions intervening that never touch EAX - a push ecx at 0x0047ddeb
 * and 0x00481296, and push edi / push edx / mov edx,[esi + 0x38] at
 * 0x0047de0f-0x0047de11 and 0x004812ba-0x004812bc - and ESI is this via mov
 * esi,ecx at 0x0047dc09 and 0x004810c9. An exhaustive scan of every PE
 * section for E8 and E9 rel32 resolving to 0x0047be80 finds those four calls
 * and no jumps, and the raw dword 0x0047be80 appears nowhere in the image,
 * so the function is never taken as a function pointer either. The four
 * sites are exhaustive and none is portable today.
 */
#include "ghidra_types.h"


void __fastcall FUN_0047be80(undefined4 param_1,uint param_2,int param_3,int param_4,uint regEax)

{
  int iVar1;
  uint in_EAX = regEax;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar10 = *(uint *)(iVar2 + 4);
  if (uVar10 <= param_2) {
    while (uVar10 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar10 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar10) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar10 = *(uint *)(iVar2 + 8);
    if (uVar10 <= in_EAX) {
      while (uVar10 != in_EAX) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar10 = *(uint *)(iVar2 + 8);
        if (in_EAX < uVar10) {
          return;
        }
      }
      iVar4 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x10;
      iVar1 = iVar4 + iVar5;
      uVar10 = *(int *)(iVar2 + 0x2c) + 0x10;
      if ((((0 < iVar1) && (iVar5 < 0x20)) && (*(int *)(iVar2 + 0x24) + uVar10 != 0)) &&
         ((int)uVar10 < 0x80)) {
        uVar7 = -uVar10;
        puVar3 = (undefined4 *)(*(int *)(iVar2 + 0x34) + iVar4 * (((int)uVar7 < 0) - 1 & uVar7) * 2)
        ;
        iVar8 = *(int *)(iVar2 + 0x24) - (((int)uVar7 < 0) - 1 & uVar7);
        uVar10 = ((int)uVar10 < 0) - 1 & uVar10;
        if (0x1f < (int)(iVar8 + uVar10)) {
          iVar8 = 0x1f - uVar10;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar4 = iVar1;
        }
        if (0x1f < iVar4 + iVar5) {
          iVar4 = 0x1f - iVar5;
        }
        if (0 < iVar8) {
          puVar6 = (undefined4 *)(uVar10 * param_4 + param_3 + iVar5 * 2);
          param_3 = iVar8;
          do {
            uVar7 = (iVar4 * 2 < 0) - 1 & iVar4 * 2;
            puVar9 = puVar3;
            puVar11 = puVar6;
            for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            puVar3 = (undefined4 *)((int)puVar3 + *(int *)(iVar2 + 0x20) * 2);
            puVar6 = (undefined4 *)((int)puVar6 + param_4);
            param_3 = param_3 + -1;
          } while (param_3 != 0);
        }
      }
    }
  }
  return;
}

