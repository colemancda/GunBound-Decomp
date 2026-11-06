/* PlaceLoadingMapPlayerMarkers - 0x004430c0 in the original binary.
 *
 * Fills the loading object's two 8-entry marker arrays, x at this + 0x10c
 * and y at this + 0x12c, for every player slot whose byte at
 * g_clientContext + 0x45914 is non-zero.  Evidence is from the consumer
 * and the caller.  The consumer is State10_Loading_Render, which walks
 * this + 0x12c as piVar17 and for each occupied slot blits a sprite at
 * (piVar17[-8] + 0x1a, *piVar17 + 2) and draws a name centred about
 * x + 0x1a at y + 5: per-player marker positions, exactly the two arrays
 * written here.  The caller is State10_Loading_PreloadAssets case 0xc,
 * which calls it right after LoadStageDecorationSet with its own this as
 * the one stack argument (ret 4), in the step that loads the stage
 * selected by the byte at ctx + 0x475c4.  The body turns the per-slot
 * ushort at ctx + 0x49a2c scaled by 0x2ec over the camera bound X into x, and scans
 * a 0x2ec-wide short bitmap of the looked-up stage image (key
 * byte(ctx+0x475c4) * 2 + 1 in the DAT_00ea0e1c tree) downward for the
 * first non-zero cell, +0x12, into y, with a fixed 0x7a when no image is
 * found.  LIKELY: "map" and "place" rest on the consumer and the stage
 * index; what the 0x2ec / 0xd1 bitmap is is not established.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void PlaceLoadingMapPlayerMarkers(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  short *psVar4;
  ushort *puVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  
  iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = (uint)*(byte *)(g_clientContext + 0x475c4) * 2 + 1;
  uVar2 = *(uint *)(iVar6 + 4);
  while (uVar2 < 0x2712) {
    if (uVar2 == 0x2711) {
      iVar6 = *(int *)(iVar6 + 0x10);
      uVar2 = *(uint *)(iVar6 + 8);
      goto joined_r0x00443104;
    }
    iVar6 = *(int *)(iVar6 + 0x1c);
    uVar2 = *(uint *)(iVar6 + 4);
  }
  iVar6 = 0;
LAB_00443118:
  iVar8 = 0;
  piVar7 = (int *)(param_1 + 300);
  puVar5 = (ushort *)(g_clientContext + 0x49a2c);
  do {
    if (*(char *)(g_clientContext + 0x45914 + iVar8) != '\0') {
      iVar3 = *(int *)(&g_nCameraBoundX + g_clientContext);
      if (iVar3 < 1) {
        iVar3 = 1;
      }
      iVar3 = (int)((longlong)(ulonglong)((uint)*puVar5 * 0x2ec) / (longlong)iVar3);
      piVar7[-8] = iVar3;
      if (iVar6 == 0) {
        *piVar7 = 0x7a;
      }
      else {
        psVar4 = (short *)(*(int *)(iVar6 + 0x34) + iVar3 * 2);
        iVar3 = 0;
        do {
          if (*psVar4 != 0) break;
          iVar3 = iVar3 + 1;
          psVar4 = psVar4 + 0x2ec;
        } while (iVar3 < 0xd1);
        *piVar7 = iVar3 + 0x12;
      }
    }
    iVar8 = iVar8 + 1;
    puVar5 = puVar5 + 1;
    piVar7 = piVar7 + 1;
    if (7 < iVar8) {
      return;
    }
  } while( true );
joined_r0x00443104:
  if (uVar1 < uVar2) goto LAB_00443112;
  if (uVar2 == uVar1) goto LAB_00443118;
  iVar6 = *(int *)(iVar6 + 0x10);
  uVar2 = *(uint *)(iVar6 + 8);
  goto joined_r0x00443104;
LAB_00443112:
  iVar6 = 0;
  goto LAB_00443118;
}

