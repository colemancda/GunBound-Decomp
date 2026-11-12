/* SaveScreenshotBmp - 0x00412e50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00412e50 mean this function.)
 *
 * NAMED (batch 48), HIGH. Writes the back buffer to a numbered .bmp. Its
 * sole caller is GameTick, behind DAT_00793520, which WndProc sets in its
 * key handler for VK 0x7a (F11); GameTick then reads the DAT_00793521 flag
 * this function raises and formats localized string 9000 with the saved
 * file name (copied to DAT_005b22d0). The file name comes from
 * FindFreeScreenshotFilename (format string %s%s%07d.bmp, directory
 * g_screenPath, prefix the literal GunBound at 0x552748). The body writes
 * a 14-byte file header (magic 0x4d42) and a 40-byte info header for
 * 800x600, 24 bpp, then fwrite()s 600 rows of 0x960 bytes converted from
 * the 16-bit surface; the byte tables at 0x56d3e0/0x56d400 are the 5- and
 * 6-bit expansion tables.
 */
#include "ghidra_types.h"


void SaveScreenshotBmp(void)

{
  char cVar1;
  ushort uVar2;
  void *_Memory;
  void *pvVar3;
  FILE *pFVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  ushort *puVar7;
  int iVar8;
  int iVar9;
  int local_444;
  undefined2 local_440;
  undefined2 uStack_43e;
  undefined2 local_43c;
  undefined2 uStack_43a;
  undefined2 local_438;
  undefined2 uStack_436;
  undefined2 local_434;
  void *local_430;
  FILE *local_42c;
  undefined4 local_428;
  undefined4 local_424;
  undefined4 local_420;
  undefined4 local_41c;
  undefined4 local_418;
  undefined4 local_414;
  undefined4 local_410;
  undefined4 local_40c;
  undefined4 local_408;
  undefined4 local_404;
  char local_400 [1024];
  
  pvVar3 = operator_new(0x15f900);
  local_414 = 0;
  uStack_43a = 0;
  local_438 = 0;
  local_408 = 0;
  local_404 = 0;
  local_440 = 0x4d42;
  uStack_43e = 0xf936;
  local_43c = 0x15;
  uStack_436 = 0x36;
  local_434 = 0;
  local_428 = 0x28;
  local_424 = 800;
  local_420 = 600;
  local_41c = 0x180001;
  local_418 = 0;
  local_410 = 0x48;
  local_40c = 0x48;
  local_430 = pvVar3;
  FindFreeScreenshotFilename(&g_screenPath,local_400);
  pFVar4 = (FILE *)FUN_00525fac(local_400,&DAT_00552218);
  local_42c = pFVar4;
  _fwrite(&local_440,0xe,1,pFVar4);
  _fwrite(&local_428,0x28,1,pFVar4);
  pFVar4 = local_42c;
  _Memory = local_430;
  iVar8 = g_screenPitch * 0x4ae + g_screenSurface;
  puVar6 = (undefined1 *)((int)pvVar3 + 1);
  local_444 = 600;
  do {
    iVar9 = 0xa0;
    puVar5 = puVar6;
    puVar7 = (ushort *)(iVar8 + 4);
    do {
      uVar2 = puVar7[-2];
      puVar5[-1] = (&DAT_0056d3e0)[(byte)puVar7[-2] & 0x1f];
      *puVar5 = (&DAT_0056d400)[(byte)(uVar2 >> 5) & 0x3f];
      puVar5[1] = (&DAT_0056d3e0)[(byte)(uVar2 >> 0xb)];
      uVar2 = puVar7[-1];
      puVar5[2] = (&DAT_0056d3e0)[(byte)puVar7[-1] & 0x1f];
      puVar5[3] = (&DAT_0056d400)[(byte)(uVar2 >> 5) & 0x3f];
      puVar5[4] = (&DAT_0056d3e0)[(byte)(uVar2 >> 0xb)];
      uVar2 = *puVar7;
      puVar5[5] = (&DAT_0056d3e0)[(byte)*puVar7 & 0x1f];
      puVar5[6] = (&DAT_0056d400)[(byte)(uVar2 >> 5) & 0x3f];
      puVar5[7] = (&DAT_0056d3e0)[(byte)(uVar2 >> 0xb)];
      uVar2 = puVar7[1];
      puVar5[8] = (&DAT_0056d3e0)[(byte)puVar7[1] & 0x1f];
      puVar5[9] = (&DAT_0056d400)[(byte)(uVar2 >> 5) & 0x3f];
      puVar5[10] = (&DAT_0056d3e0)[(byte)(uVar2 >> 0xb)];
      uVar2 = puVar7[2];
      puVar6 = puVar5 + 0xf;
      iVar9 = iVar9 + -1;
      puVar5[0xb] = (&DAT_0056d3e0)[(byte)puVar7[2] & 0x1f];
      puVar5[0xc] = (&DAT_0056d400)[(byte)(uVar2 >> 5) & 0x3f];
      puVar5[0xd] = (&DAT_0056d3e0)[(byte)(uVar2 >> 0xb)];
      puVar5 = puVar6;
      puVar7 = puVar7 + 5;
    } while (iVar9 != 0);
    iVar8 = iVar8 + g_screenPitch * -2;
    local_444 = local_444 + -1;
  } while (local_444 != 0);
  _fwrite(local_430,0x960,600,local_42c);
  _fclose(pFVar4);
  _free(_Memory);
  iVar8 = 0;
  do {
    cVar1 = local_400[iVar8];
    (&DAT_005b22d0)[iVar8] = cVar1;
    iVar8 = iVar8 + 1;
  } while (cVar1 != '\0');
  DAT_00793521 = 1;
  return;
}

