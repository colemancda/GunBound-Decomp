/* ExplodeOldestMine - 0x00437500 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00437500 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Eviction
 * half of the 8-mines-per-player cap. SpawnMine and SpawnSuperMine call it
 * in `while (FindFreeMineKey(slot) == -1)` retry loops (slot in EDX/ECX),
 * so it must free a key. It scans the player's eight keys (slot*8 .. +7)
 * in the mine layer, keeps the entry with the smallest +0x3f9c (stamped in
 * SpawnMine from the turn counter, so the oldest), fires vtable slot +0x20
 * (ExplodeMine, 0x497ad0 on vtable 0x5563f0), unlinks it (+0xc / +0x10)
 * and calls the scalar-deleting destructor. FindFreeMineKey's header
 * documents this contract. LIKELY: the +0x3f9c-is-age reading is from that
 * header, not re-derived here.
 */
#include "ghidra_types.h"


void __fastcall ExplodeOldestMine(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  iVar5 = -1;
  iVar8 = 100000;
  iVar6 = 0;
  uVar3 = param_2 * 8;
LAB_00437524:
  uVar4 = *(uint *)(iVar2 + 4);
  iVar1 = iVar2;
  while (uVar4 < 0x186a4) {
    if (uVar4 == 0x186a3) {
      iVar1 = *(int *)(iVar1 + 0x10);
      uVar4 = *(uint *)(iVar1 + 8);
      if (uVar4 <= uVar3) goto LAB_0043754d;
      break;
    }
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar4 = *(uint *)(iVar1 + 4);
  }
  goto LAB_00437569;
  while( true ) {
    iVar1 = *(int *)(iVar1 + 0x10);
    uVar4 = *(uint *)(iVar1 + 8);
    if (uVar3 < uVar4) break;
LAB_0043754d:
    if (uVar4 == uVar3) {
      if (*(int *)(iVar1 + 0x3f9c) < iVar8) {
        iVar5 = iVar6;
        iVar8 = *(int *)(iVar1 + 0x3f9c);
      }
      break;
    }
  }
LAB_00437569:
  iVar6 = iVar6 + 1;
  uVar3 = uVar3 + 1;
  if (7 < iVar6) {
    if (iVar5 != -1) {
      uVar3 = *(uint *)(iVar2 + 4);
      uVar4 = param_2 * 8 + iVar5;
      if (uVar3 < 0x186a4) {
        while (uVar3 != 0x186a3) {
          iVar2 = *(int *)(iVar2 + 0x1c);
          uVar3 = *(uint *)(iVar2 + 4);
          if (0x186a3 < uVar3) {
            return;
          }
        }
        piVar7 = *(int **)(iVar2 + 0x10);
        uVar3 = piVar7[2];
        if (uVar3 <= uVar4) {
          while (uVar3 != uVar4) {
            piVar7 = (int *)piVar7[4];
            uVar3 = piVar7[2];
            if (uVar4 < uVar3) {
              return;
            }
          }
          (**(code **)(*piVar7 + 0x20))();
          *(int *)(piVar7[3] + 0x10) = piVar7[4];
          *(int *)(piVar7[4] + 0xc) = piVar7[3];
          (**(code **)*piVar7)(1);
        }
      }
    }
    return;
  }
  goto LAB_00437524;
}

