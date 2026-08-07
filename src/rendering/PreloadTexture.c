/* PreloadTexture - 0x004f43a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"
#include "xfs.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 PreloadTexture(int param_1,char *param_2)

{
  char cVar1;
  float fVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  void *pvVar7;
  undefined4 *puVar8;
  char local_91;
  int local_90;
  int local_8c;
  undefined1 local_88 [4];
  undefined1 local_84 [3];
  undefined4 uStack_81;
  undefined1 local_7c [124];
  
  iVar4 = FindTextureCacheEntryByName(param_2);
  if (iVar4 != 0) {
    return 1;
  }
  pcVar5 = param_2;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)&uStack_81 + (1 - (int)param_2)] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  puVar3 = &uStack_81;
  do {
    puVar8 = puVar3;
    puVar3 = (undefined4 *)((int)puVar8 + 1);
  } while (*(char *)((int)puVar8 + 1) != '\0');
  *(undefined4 *)((int)puVar8 + 1) = g_textureExt;
  *(undefined1 *)((int)puVar8 + 5) = g_textureExtNul;
  /* Recovered from disassembly (angr): archive=&g_graphicsArchive (EDI),
   * name=the assembled "<name>.<ext>" buffer at &uStack_81+1 (EAX),
   * findExisting=1 (CL), insertFlag=0 (stack). The raw port's
   * FUN_004f1390(0) set findExisting=0 and dropped name/archive. */
  iVar4 = OpenXFSEntryStream((int)&g_graphicsArchive, (char *)((int)&uStack_81 + 1), 1, 0);
  if (iVar4 == 0) {
    return 0;
  }
  /* DROPPED-COUNT FIX (2026-08-06): these four calls passed only 2 of
   * ReadXFSEntryByte's 3 arguments - the byte count arrives in EAX in the
   * original and Ghidra dropped it, while functions.h declares the
   * function K&R-empty so the short calls compiled silently. `count` then
   * came through as whatever sat above the two pushed args in THIS
   * function's frame, and the reader wrote that many bytes into a 4-byte
   * stack local - smashing the frame, which is what zeroed the saved
   * param_1 slot and made the FindFreeAtlasTileSlot call below receive a
   * NULL cache. Counts recovered from orig 0x4f4426-0x4f4461 (`mov eax,N`
   * before each `call 0x4f06c0`): 4, 4, 1, 4 - and the buffer each call
   * targets matches these locals exactly, since ReadXFSEntryByte is
   * callee-clean there (`ret 8`) so all four offsets share one esp. */
  ReadXFSEntryByte(iVar4,(undefined4 *)&local_8c,4);
  ReadXFSEntryByte(iVar4,(undefined4 *)local_88,4);
  ReadXFSEntryByte(iVar4,(undefined4 *)&local_91,1);
  ReadXFSEntryByte(iVar4,(undefined4 *)local_84,4);
  /* cache/pageTag/formatId arrive in EAX/ESI/BL at orig 0x4f4466-0x4f4475
   * and were dropped by Ghidra - see FindFreeAtlasTileSlot.c. */
  iVar6 = FindFreeAtlasTileSlot((undefined4 *)&local_90,param_1,local_8c,local_91);
  if (iVar6 == -1) {
    /* AllocTextureAtlasPage takes the cache in ESI and RETURNS the new
     * page in EAX; InitTextureAtlasPage then takes that page in ESI and
     * the format id in BL, with only the tile size on the stack (orig
     * 0x4f4481-0x4f4497). All of those were dropped. */
    local_90 = (int)AllocTextureAtlasPage(param_1);
    InitTextureAtlasPage(local_8c,(undefined1 *)local_90,local_91);
    iVar6 = 0;
  }
  /* The pixel payload's count is COMPUTED, not a literal (orig
   * 0x4f449e-0x4f44c1): tileDim squared, then doubled for the normal
   * 16-bit format or halved when the format id is 2 - i.e. bytes, not
   * pixels. Same dropped-EAX bug as the four header reads above; left
   * unfixed this would write a garbage-sized block straight into the
   * cache object at +0x401f8. */
  ReadXFSEntryByte(iVar4,(undefined4 *)(param_1 + 0x401f8),
                   (uint)(local_91 == '\x02' ? local_8c * local_8c / 2
                                              : local_8c * local_8c * 2));
  UploadTileToAtlasSurface(param_1 + 0x401f8,iVar6);
  CloseSpriteReadState();
  pvVar7 = operator_new(0x9c);
  pcVar5 = param_2;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)pvVar7 - (int)param_2] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  *(int *)((int)pvVar7 + 0x94) = local_90;
  fVar2 = (float)local_8c * _DAT_0055801c;
  *(int *)((int)pvVar7 + 0x8c) = iVar6;
  *(float *)((int)pvVar7 + 0x88) = fVar2;
  *(float *)((int)pvVar7 + 0x80) =
       (float)(iVar6 % (int)(0x100 / (longlong)local_8c)) * *(float *)((int)pvVar7 + 0x88);
  local_90 = iVar6 / (int)(0x100 / (longlong)local_8c);
  *(float *)((int)pvVar7 + 0x84) = (float)local_90 * *(float *)((int)pvVar7 + 0x88);
  *(char *)((int)pvVar7 + 0x90) = local_91;
  InsertTextureCacheRecord(pvVar7);
  pcVar5 = (char *)(*(int *)(param_1 + 0x401b8) * 0x200 + 0x1b8 + param_1);
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    *pcVar5 = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  *(int *)(param_1 + 0x401b8) = *(int *)(param_1 + 0x401b8) + 1;
  return 1;
}

