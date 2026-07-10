/* InitDirectDraw - 0x004efaa0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "xfs.h"
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte InitDirectDraw(undefined4 param_1)

{
  int *piVar1;
  char cVar2;
  HWND in_EAX;
  FARPROC pFVar3;
  int iVar4;
  undefined4 *puVar5;
  IMAGE_DOS_HEADER *pIVar6;
  undefined4 *puStack_158;
  int *piStack_154;
  undefined *puStack_150;
  int *piStack_14c;
  IMAGE_DOS_HEADER **ppIStack_148;
  int *piStack_144;
  undefined *puStack_140;
  int **ppiStack_13c;
  int *piStack_138;
  int *piStack_134;
  int *piStack_130;
  undefined4 uStack_12c;
  HWND pHStack_128;
  int *piStack_124;
  undefined4 uStack_120;
  int **ppiStack_11c;
  undefined4 uStack_118;
  int *piStack_114;
  int *piStack_110;
  int **ppiStack_10c;
  int **ppiStack_108;
  int *piStack_104;
  undefined4 *puStack_100;
  int aiStack_b4 [3];
  undefined4 uStack_a8;
  undefined4 auStack_a4 [5];
  undefined4 uStack_90;
  undefined4 uStack_4c;
  undefined4 uStack_3c;
  /* Ghidra artifact: raw stack reference the decompiler couldn't map
   * to a named local; declared so the raw port parses. */
  undefined stack0xffffff20;

  DAT_007935ec = in_EAX;
  g_hDDrawDll = LoadLibraryA(s_ddraw_dll_00557510);
  if (g_hDDrawDll == (HMODULE)0x0) {
    return 0x1a;
  }
  pFVar3 = GetProcAddress(g_hDDrawDll,s_DirectDrawCreateEx_005574fc);
  iVar4 = (*pFVar3)();
  if (iVar4 < 0) {
    return 0x19;
  }
  iVar4 = (**(code **)(*g_pDirectDraw7 + 0x50))();
  piVar1 = g_pDirectDraw7;
  if (iVar4 < 0) {
    return 0x18;
  }
  if (DAT_00588f4c == '\0') {
    iVar4 = *g_pDirectDraw7;
    puStack_100 = (undefined4 *)DAT_00588f60;
    piStack_104 = (int *)0x4efb60;
    piStack_104 = (int *)FUN_0053753c();
    ppiStack_108 = (int **)0x4efb6c;
    ppiStack_108 = (int **)FUN_0053753c();
    ppiStack_10c = (int **)piVar1;
    piStack_110 = (int *)0x4efb71;
    iVar4 = (**(code **)(iVar4 + 0x54))();
    if (iVar4 < 0) {
      return 0x1c;
    }
  }
  puVar5 = auStack_a4;
  for (iVar4 = 0x1f; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  auStack_a4[0] = 0x7c;
  if (DAT_00588f4c == '\0') {
    _DAT_006773b4 = 0;
    _DAT_006773bc = 800;
    _DAT_006773b8 = 0;
    _DAT_006773c0 = 600;
    auStack_a4[1] = 0x21;
    uStack_3c = 0x6218;
    uStack_90 = 1;
  }
  else {
    puStack_100 = (undefined4 *)0x4efbb5;
    GetClientRect(DAT_007935ec,(LPRECT)&DAT_006773b4);
    puStack_100 = (undefined4 *)0x4efbc8;
    ClientToScreen(DAT_007935ec,(LPPOINT)&DAT_006773b4);
    puStack_100 = (undefined4 *)0x4efbd6;
    ClientToScreen(DAT_007935ec,(LPPOINT)&DAT_006773bc);
    auStack_a4[1] = 1;
    uStack_3c = 0x200;
  }
  puStack_100 = auStack_a4;
  piStack_104 = g_pDirectDraw7;
  ppiStack_108 = (int **)0x4efc38;
  iVar4 = (**(code **)(*g_pDirectDraw7 + 0x18))();
  if (iVar4 < 0) {
    return 0x1d;
  }
  if (DAT_00588f4c == '\0') {
    ppiStack_108 = &g_pBackBufferSurface;
    ppiStack_10c = (int **)&stack0xffffff20;
    piStack_110 = g_pPrimarySurface;
    piStack_114 = (int *)0x4efcd0;
    iVar4 = (**(code **)(*g_pPrimarySurface + 0x30))();
    if (iVar4 < 0) {
      return 0x1f;
    }
  }
  else {
    aiStack_b4[1] = 7;
    ppiStack_108 = (int **)0x4efc63;
    uStack_a8 = FUN_0053753c();
    ppiStack_108 = (int **)0x4efc72;
    aiStack_b4[2] = FUN_0053753c();
    ppiStack_108 = (int **)0x0;
    ppiStack_10c = &g_pBackBufferSurface;
    piStack_110 = aiStack_b4;
    uStack_4c = 0x2040;
    piStack_114 = g_pDirectDraw7;
    uStack_118 = 0x4efc97;
    iVar4 = (**(code **)(*g_pDirectDraw7 + 0x18))();
    if (iVar4 < 0) {
      return 0x1e;
    }
  }
  uStack_118 = 0;
  ppiStack_11c = &g_pClipper;
  uStack_120 = 0;
  piStack_124 = g_pDirectDraw7;
  pHStack_128 = (HWND)0x4efcf2;
  (**(code **)(*g_pDirectDraw7 + 0x10))();
  pHStack_128 = DAT_007935ec;
  uStack_12c = 0;
  piStack_130 = g_pClipper;
  piStack_134 = (int *)0x4efd05;
  (**(code **)(*g_pClipper + 0x20))();
  piStack_134 = g_pClipper;
  piStack_138 = g_pBackBufferSurface;
  ppiStack_13c = (int **)0x4efd17;
  (**(code **)(*g_pBackBufferSurface + 0x70))();
  ppiStack_13c = &g_pDirect3D7;
  puStack_140 = &IID_IDirect3D7;
  piStack_144 = g_pDirectDraw7;
  ppIStack_148 = (IMAGE_DOS_HEADER **)0x4efd2b;
  iVar4 = (**(code **)*g_pDirectDraw7)();
  if (iVar4 < 0) {
    return 0x20;
  }
  ppIStack_148 = &g_pD3DDevice7;
  piStack_14c = g_pBackBufferSurface;
  puStack_150 = &DAT_00f22504;
  piStack_154 = g_pDirect3D7;
  puStack_158 = (undefined4 *)0x4efd57;
  iVar4 = (**(code **)(*g_pDirect3D7 + 0x10))();
  if (iVar4 < 0) {
    return 0x21;
  }
  uStack_120 = 0;
  ppiStack_11c = (int **)0x0;
  puStack_158 = (undefined4 *)0x4efd7a;
  uStack_118 = FUN_0053753c();
  puStack_158 = (undefined4 *)0x4efd89;
  piStack_114 = (int *)FUN_0053753c();
  puStack_158 = &uStack_120;
  piStack_110 = (int *)0x0;
  ppiStack_10c = (int **)0x3f800000;
  iVar4 = (**(code **)(*(int *)g_pD3DDevice7 + 0x34))(g_pD3DDevice7);
  if (iVar4 < 0) {
    return 0x22;
  }
  pIVar6 = g_pD3DDevice7;
  iVar4 = (**(code **)(*(int *)g_pD3DDevice7 + 0x10))(g_pD3DDevice7,EnumTextureFormatsCallback,0);
  if (iVar4 < 0) {
    return 0x23;
  }
  puStack_150 = (undefined *)0x0;
  piStack_14c = (int *)0x0;
  ppIStack_148 = (IMAGE_DOS_HEADER **)0x0;
  piStack_154 = (int *)0x1000;
  (**(code **)(*g_pDirectDraw7 + 0x5c))(g_pDirectDraw7,&piStack_154,&puStack_158,&ppiStack_11c);
  if (pIVar6 < &IMAGE_DOS_HEADER_00400000) {
    return 0x1b;
  }
  FUN_004f3e40();
  FUN_004f3a00();
  (**(code **)(*(int *)g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x28,1);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x10,5);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x11,3);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x10,5);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x11,3);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,2,2);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,3,0);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,5,2);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,6,0);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,1,4);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,4,4);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x50))(g_pD3DDevice7,8,3);
  (**(code **)(*(int *)g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x88,1);
  OpenXFSArchive(&g_graphicsArchive,param_1,1,0);
  _DAT_00f23658 = 600;
  _DAT_00f23654 = 800;
  puVar5 = &DAT_00f22650;
  for (iVar4 = 0x400; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  _DAT_00f23650 = 0;
  DAT_00f2465c = 0;
  cVar2 = SetupZBuffer();
  return -(cVar2 != '\x01') & 100;
}

