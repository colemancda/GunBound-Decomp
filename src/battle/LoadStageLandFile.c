/* LoadStageLandFile - 0x004e3c50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (LIKELY). Callers: the two loading-phase handlers
 * (ProcessBattleFrame case 4 and State10_Loading_PreloadAssets case 0xe)
 * pass the stage object at ctx+0x6a7708 and the per-room map-name buffer
 * (ctx + 0x1a1ec8 + slot*0x7d28), the very buffer handed to
 * PreloadBattleTextures in the preceding case. The function appends the
 * literal at 0x557258 (verified in the binary: the string ".lnd") to a
 * copy of that name and opens it in g_graphicsArchive through
 * OpenXFSEntryStream (orig 0x4e3d09 call 0x4f1390, edi = 0xf11dd0).
 * The consumers confirm what the file holds. It reads two dwords into
 * stage +0x18 and +0x1c (ctx+0x6a7720 / 0x6a7724: the width and height
 * projectile bounds code compares against, g_nCameraBoundX/Y, and the stride
 * FindFirstImpactAlongStep_XMajor uses) and then width*height bytes
 * (imul at orig 0x4e3d35, count in EAX - a register argument Ghidra dropped
 * from the ReadXFSEntryByte calls here) into stage +0x34 (ctx+0x6a773c),
 * which the Simulate* bodies index as the per-pixel terrain mask. A
 * second same-sized buffer is allocated at +0x38 and not filled here.
 * Land rather than terrain in the name is taken from the .lnd extension.
 * Known port defect, not changed here: the three ReadXFSEntryByte calls
 * omit the EAX byte count (4, 4, width*height).
 *
 * DROPPED-ARGUMENT FIX (2026-07-29): confirmed via objdump. Entry
 * `mov edi,eax` (0x4e3c60) - the function's own name-string argument
 * arrives in EAX and is immediately stashed in EDI for the local_80 copy
 * loop; Ghidra rendered the read (not the missing parameter) as `in_EAX`.
 * Promoted to an explicit `name` parameter.
 *
 * The stale `OpenXFSEntryStream(0)` (see functions.h's "K&R-empty
 * deliberately" note) resolves to archive=&g_graphicsArchive,
 * name=local_80, findExisting=1, insertFlag=0: orig 0x4e3cfc-0x4e3d09
 * `push 0x0` / `mov cl,0x1` / `lea eax,[esp+0x10]` (= the same buffer
 * local_80 was just built into) / `mov edi,0xf11dd0` (= &g_graphicsArchive,
 * same literal as CloseSpriteReadState.c/LoadSpriteSet.c) / `call
 * 0x4f1390`.
 */
#include "ghidra_types.h"
#include "xfs.h"


void LoadStageLandFile(int param_1, char *name)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  char *in_EAX;
  void *pvVar6;
  int iVar7;
  undefined4 *puVar8;
  bool bVar9;
  char local_80 [128];

  in_EAX = name;
  
  iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar7 + 4);
  while (uVar2 < 0xea61) {
    if (uVar2 == 60000) {
      iVar7 = *(int *)(iVar7 + 0x10);
      bVar9 = true;
      if (*(int *)(iVar7 + 8) == 0) goto LAB_004e3c93;
      goto LAB_004e3c9f;
    }
    iVar7 = *(int *)(iVar7 + 0x1c);
    uVar2 = *(uint *)(iVar7 + 4);
  }
  iVar7 = 0;
  goto LAB_004e3ca5;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    bVar9 = *(int *)(iVar7 + 8) == 0;
    if (!bVar9) break;
LAB_004e3c93:
    if (bVar9) goto LAB_004e3ca5;
  }
LAB_004e3c9f:
  iVar7 = 0;
LAB_004e3ca5:
  iVar3 = -(int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[(int)(local_80 + iVar3)] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  puVar5 = (undefined4 *)(local_80 - 1);
  do {
    puVar8 = puVar5;
    puVar5 = (undefined4 *)((int)puVar8 + 1);
  } while (*(char *)((int)puVar8 + 1) != '\0');
  iVar3 = *(int *)(iVar7 + 0x24);
  iVar4 = *(int *)(iVar7 + 0x20);
  *(undefined4 *)((int)puVar8 + 1) = DAT_00557258;
  *(undefined1 *)((int)puVar8 + 5) = DAT_0055725c;
  pvVar6 = operator_new(iVar3 * iVar4);
  *(void **)(param_1 + 0x34) = pvVar6;
  pvVar6 = operator_new(*(int *)(iVar7 + 0x24) * *(int *)(iVar7 + 0x20));
  *(void **)(param_1 + 0x38) = pvVar6;
  iVar7 = OpenXFSEntryStream((int)&g_graphicsArchive, local_80, 1, 0);
  if (iVar7 != 0) {
    /* EAX = byte count at each call: mov eax,4 (0x4e3d1a, 0x4e3d29) and
     * [ebp+0x18]*[ebp+0x1c] = w*h (0x4e3d33/0x4e3d35) for the pixel data. */
    ReadXFSEntryByte(iVar7,param_1 + 0x18,4);
    ReadXFSEntryByte(iVar7,param_1 + 0x1c,4);
    ReadXFSEntryByte(iVar7,*(undefined4 *)(param_1 + 0x34),
                     *(int *)(param_1 + 0x18) * *(int *)(param_1 + 0x1c));
    CloseSpriteReadState();
  }
  return;
}

