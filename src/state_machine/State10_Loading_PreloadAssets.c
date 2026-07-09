/* State10_Loading_PreloadAssets - 0x0043f0e0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall State10_Loading_PreloadAssets(int param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffff7f;
  undefined4 *puVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  char acStack_80 [4];
  undefined1 auStack_7c [124];
  
  iVar4 = *(int *)(param_1 + 4);
  *(int *)(param_1 + 4) = iVar4 + 1;
  switch(iVar4) {
  case 0xc:
    FUN_004e3d60(&DAT_006a7708 + g_clientContext,&DAT_00551cb1);
    FUN_004430c0(param_1);
    _sprintf(acStack_80,(char *)&PTR_DAT_00555500,
             (uint)*(byte *)(g_clientContext + 0x475c4) * 0x7d28 + 0x1a1ec8 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    uVar3 = FindPreloadedTextureByName(acStack_80);
    *(undefined4 *)(&DAT_006a7f70 + g_clientContext) = uVar3;
    puVar1 = (undefined4 *)&stack0xffffff7f;
    do {
      puVar6 = puVar1;
      puVar1 = (undefined4 *)((int)puVar6 + 1);
    } while (*(char *)((int)puVar6 + 1) != '\0');
    *(undefined4 *)((int)puVar6 + 1) = DAT_005554f8;
    *(undefined1 *)((int)puVar6 + 5) = DAT_005554fc;
    FUN_004f1790(&DAT_00ea0e18,0x1e14);
    DAT_00793634 = FUN_0040a4d0((uint)*(byte *)(g_clientContext + 0x475c4) * 0x7d28 + 0x1a328c +
                                g_clientContext);
    break;
  case 0xd:
    FUN_004e4010((uint)*(byte *)(g_clientContext + 0x475c4) * 0x7d28 + 0x1a1ec8 + g_clientContext);
    break;
  case 0xe:
    FUN_004e3c50(&DAT_006a7708 + g_clientContext);
    if (*(ushort *)(&DAT_006aa660 + g_clientContext) != 0xffff) {
      _sprintf(acStack_80,s_event14__d_img_005554e8,*(ushort *)(&DAT_006aa660 + g_clientContext) + 1);
      FUN_004f1790(&DAT_00ea0e18,0x2712);
    }
    break;
  case 0xf:
    cVar2 = FUN_0041c2c0(g_clientContext,0);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,5000);
      FUN_004f1790(&DAT_00ea0e18,0x13ec);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x10:
    cVar2 = FUN_0041c2c0(g_clientContext,0);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,6000);
      FUN_004f1790(&DAT_00ea0e18,0x1771);
      FUN_004f1790(&DAT_00ea0e18,0x17d4);
      FUN_004f1790(&DAT_00ea0e18,0x17d5);
      FUN_004f1790(&DAT_00ea0e18,0x1a2c);
      FUN_004f1790(&DAT_00ea0e18,0x1a2d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x11:
    cVar2 = FUN_0041c2c0(g_clientContext,0);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,8000);
      FUN_004f1790(&DAT_00ea0e18,0x1f41);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2008);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x206c);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x12:
    cVar2 = FUN_0041c2c0(g_clientContext,1);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1389);
      FUN_004f1790(&DAT_00ea0e18,0x13ed);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x13:
    cVar2 = FUN_0041c2c0(g_clientContext,1);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1772);
      FUN_004f1790(&DAT_00ea0e18,0x1773);
      FUN_004f1790(&DAT_00ea0e18,0x17d6);
      FUN_004f1790(&DAT_00ea0e18,0x17d7);
      FUN_004f1790(&DAT_00ea0e18,0x1a2e);
      FUN_004f1790(&DAT_00ea0e18,0x1a2f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x14:
    cVar2 = FUN_0041c2c0(g_clientContext,1);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f42);
      FUN_004f1790(&DAT_00ea0e18,0x1f43);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2009);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x206d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x15:
    cVar2 = FUN_0041c2c0(g_clientContext,2);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x138a);
      FUN_004f1790(&DAT_00ea0e18,0x13ee);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x16:
    cVar2 = FUN_0041c2c0(g_clientContext,2);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1774);
      FUN_004f1790(&DAT_00ea0e18,0x1775);
      FUN_004f1790(&DAT_00ea0e18,0x17d8);
      FUN_004f1790(&DAT_00ea0e18,0x17d9);
      FUN_004f1790(&DAT_00ea0e18,0x1a30);
      FUN_004f1790(&DAT_00ea0e18,0x1a31);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x17:
    cVar2 = FUN_0041c2c0(g_clientContext,2);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f44);
      FUN_004f1790(&DAT_00ea0e18,0x1f45);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x200a);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x206e);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x18:
    cVar2 = FUN_0041c2c0(g_clientContext,3);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x138b);
      FUN_004f1790(&DAT_00ea0e18,0x13ef);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x19:
    cVar2 = FUN_0041c2c0(g_clientContext,3);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1776);
      FUN_004f1790(&DAT_00ea0e18,0x1777);
      FUN_004f1790(&DAT_00ea0e18,0x17da);
      FUN_004f1790(&DAT_00ea0e18,0x17db);
      FUN_004f1790(&DAT_00ea0e18,0x1a32);
      FUN_004f1790(&DAT_00ea0e18,0x1a33);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1a:
    cVar2 = FUN_0041c2c0(g_clientContext,3);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f46);
      FUN_004f1790(&DAT_00ea0e18,0x1f47);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x200b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x206f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1b:
    cVar2 = FUN_0041c2c0(g_clientContext,4);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x138c);
      FUN_004f1790(&DAT_00ea0e18,0x13f0);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1c:
    cVar2 = FUN_0041c2c0(g_clientContext,4);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1778);
      FUN_004f1790(&DAT_00ea0e18,0x1779);
      FUN_004f1790(&DAT_00ea0e18,0x17dc);
      FUN_004f1790(&DAT_00ea0e18,0x17dd);
      FUN_004f1790(&DAT_00ea0e18,0x1a34);
      FUN_004f1790(&DAT_00ea0e18,0x1a35);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1d:
    cVar2 = FUN_0041c2c0(g_clientContext,4);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f48);
      FUN_004f1790(&DAT_00ea0e18,0x1f49);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x200c);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2070);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1e:
    cVar2 = FUN_0041c2c0(g_clientContext,5);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x138d);
      FUN_004f1790(&DAT_00ea0e18,0x13f1);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1f:
    cVar2 = FUN_0041c2c0(g_clientContext,5);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x177a);
      FUN_004f1790(&DAT_00ea0e18,0x177b);
      FUN_004f1790(&DAT_00ea0e18,0x17de);
      FUN_004f1790(&DAT_00ea0e18,0x17df);
      FUN_004f1790(&DAT_00ea0e18,0x1a36);
      FUN_004f1790(&DAT_00ea0e18,0x1a37);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x20:
    cVar2 = FUN_0041c2c0(g_clientContext,5);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f4a);
      FUN_004f1790(&DAT_00ea0e18,0x1f4b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x200d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2071);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x21:
    cVar2 = FUN_0041c2c0(g_clientContext,6);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x138e);
      FUN_004f1790(&DAT_00ea0e18,0x13f2);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x22:
    cVar2 = FUN_0041c2c0(g_clientContext,6);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x177c);
      FUN_004f1790(&DAT_00ea0e18,0x177d);
      FUN_004f1790(&DAT_00ea0e18,0x17e0);
      FUN_004f1790(&DAT_00ea0e18,0x17e1);
      FUN_004f1790(&DAT_00ea0e18,0x1a38);
      FUN_004f1790(&DAT_00ea0e18,0x1a39);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    if (*(char *)(g_clientContext + 0x45578) == '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x17d2);
      FUN_004f1790(&DAT_00ea0e18,0x17d3);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x17ca);
      FUN_004f1790(&DAT_00ea0e18,0x17cb);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
      FUN_004f1790(&DAT_00ea0e18,0x17d2);
      FUN_004f1790(&DAT_00ea0e18,0x17d3);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x17ca);
      FUN_004f1790(&DAT_00ea0e18,0x17cb);
    }
    break;
  case 0x23:
    cVar2 = FUN_0041c2c0(g_clientContext,6);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f4c);
      FUN_004f1790(&DAT_00ea0e18,0x1f4d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x200e);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2072);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x24:
    cVar2 = FUN_0041c2c0(g_clientContext,7);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x138f);
      FUN_004f1790(&DAT_00ea0e18,0x13f3);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x25:
    cVar2 = FUN_0041c2c0(g_clientContext,7);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x177e);
      FUN_004f1790(&DAT_00ea0e18,0x177f);
      FUN_004f1790(&DAT_00ea0e18,0x17e2);
      FUN_004f1790(&DAT_00ea0e18,0x17e3);
      FUN_004f1790(&DAT_00ea0e18,0x1a3a);
      FUN_004f1790(&DAT_00ea0e18,0x1a3b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x26:
    cVar2 = FUN_0041c2c0(g_clientContext,7);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f4f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x200f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2073);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x27:
    cVar2 = FUN_0041c2c0(g_clientContext,8);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1390);
      FUN_004f1790(&DAT_00ea0e18,0x13f4);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x28:
    cVar2 = FUN_0041c2c0(g_clientContext,8);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1780);
      FUN_004f1790(&DAT_00ea0e18,0x1781);
      FUN_004f1790(&DAT_00ea0e18,0x17e4);
      FUN_004f1790(&DAT_00ea0e18,0x17e5);
      FUN_004f1790(&DAT_00ea0e18,0x1a3c);
      FUN_004f1790(&DAT_00ea0e18,0x1a3d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x29:
    cVar2 = FUN_0041c2c0(g_clientContext,8);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f50);
      FUN_004f1790(&DAT_00ea0e18,0x1f51);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x17d0);
      FUN_004f1790(&DAT_00ea0e18,0x17d1);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2010);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2074);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2a:
    cVar2 = FUN_0041c2c0(g_clientContext,9);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1391);
      FUN_004f1790(&DAT_00ea0e18,0x13f5);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2b:
    cVar2 = FUN_0041c2c0(g_clientContext,9);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1782);
      FUN_004f1790(&DAT_00ea0e18,0x1783);
      FUN_004f1790(&DAT_00ea0e18,0x17e6);
      FUN_004f1790(&DAT_00ea0e18,0x17e7);
      FUN_004f1790(&DAT_00ea0e18,0x1a3e);
      FUN_004f1790(&DAT_00ea0e18,0x1a3f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2c:
    cVar2 = FUN_0041c2c0(g_clientContext,9);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f52);
      FUN_004f1790(&DAT_00ea0e18,0x1f53);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2011);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2075);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    FUN_004f1790(&DAT_00ea0e18,0x17ce);
    FUN_004f1790(&DAT_00ea0e18,0x17cf);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x2d:
    cVar2 = FUN_0041c2c0(g_clientContext,10);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1392);
      FUN_004f1790(&DAT_00ea0e18,0x13f6);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2e:
    cVar2 = FUN_0041c2c0(g_clientContext,10);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1784);
      FUN_004f1790(&DAT_00ea0e18,0x1785);
      FUN_004f1790(&DAT_00ea0e18,0x17e8);
      FUN_004f1790(&DAT_00ea0e18,0x17e9);
      FUN_004f1790(&DAT_00ea0e18,0x1a40);
      FUN_004f1790(&DAT_00ea0e18,0x1a41);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2f:
    cVar2 = FUN_0041c2c0(g_clientContext,10);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f54);
      FUN_004f1790(&DAT_00ea0e18,0x1f55);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2012);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2076);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x30:
    cVar2 = FUN_0041c2c0(g_clientContext,0xb);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1393);
      FUN_004f1790(&DAT_00ea0e18,0x13f7);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x31:
    cVar2 = FUN_0041c2c0(g_clientContext,0xb);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1786);
      FUN_004f1790(&DAT_00ea0e18,0x1787);
      FUN_004f1790(&DAT_00ea0e18,0x17ea);
      FUN_004f1790(&DAT_00ea0e18,0x17eb);
      FUN_004f1790(&DAT_00ea0e18,0x1a42);
      FUN_004f1790(&DAT_00ea0e18,0x1a43);
      FUN_004f1790(&DAT_00ea0e18,0x1a8e);
      FUN_004f1790(&DAT_00ea0e18,0x1a8f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x32:
    cVar2 = FUN_0041c2c0(g_clientContext,0xb);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f56);
      FUN_004f1790(&DAT_00ea0e18,0x1f57);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2013);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2077);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x33:
    cVar2 = FUN_0041c2c0(g_clientContext,0xc);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1394);
      FUN_004f1790(&DAT_00ea0e18,0x13f8);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x34:
    cVar2 = FUN_0041c2c0(g_clientContext,0xc);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1788);
      FUN_004f1790(&DAT_00ea0e18,0x1789);
      FUN_004f1790(&DAT_00ea0e18,0x17ec);
      FUN_004f1790(&DAT_00ea0e18,0x17ed);
      FUN_004f1790(&DAT_00ea0e18,0x1a44);
      FUN_004f1790(&DAT_00ea0e18,0x1a45);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x35:
    cVar2 = FUN_0041c2c0(g_clientContext,0xc);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f58);
      FUN_004f1790(&DAT_00ea0e18,0x1f59);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2014);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2078);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x36:
    FUN_004f1790(&DAT_00ea0e18,0x1395);
    FUN_004f1790(&DAT_00ea0e18,0x13f9);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x37:
    FUN_004f1790(&DAT_00ea0e18,0x178a);
    FUN_004f1790(&DAT_00ea0e18,0x178b);
    FUN_004f1790(&DAT_00ea0e18,0x17ee);
    FUN_004f1790(&DAT_00ea0e18,0x17ef);
    FUN_004f1790(&DAT_00ea0e18,0x1a46);
    FUN_004f1790(&DAT_00ea0e18,0x1a47);
    FUN_004f1790(&DAT_00ea0e18,0x1a8c);
    FUN_004f1790(&DAT_00ea0e18,0x1a8d);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x38:
    FUN_004f1790(&DAT_00ea0e18,0x1f5a);
    FUN_004f1790(&DAT_00ea0e18,0x1f5b);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x2015);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x2079);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x39:
    FUN_004f1790(&DAT_00ea0e18,0x1396);
    FUN_004f1790(&DAT_00ea0e18,0x13fa);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x3a:
    FUN_004f1790(&DAT_00ea0e18,0x178c);
    FUN_004f1790(&DAT_00ea0e18,0x178d);
    FUN_004f1790(&DAT_00ea0e18,0x17f0);
    FUN_004f1790(&DAT_00ea0e18,0x17f1);
    FUN_004f1790(&DAT_00ea0e18,0x1a48);
    FUN_004f1790(&DAT_00ea0e18,0x1a49);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x19c8);
    FUN_004f1790(&DAT_00ea0e18,0x19ca);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x3b:
    FUN_004f1790(&DAT_00ea0e18,0x1f5c);
    FUN_004f1790(&DAT_00ea0e18,0x1f5d);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x19c9);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x2016);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x207a);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x17cc);
    FUN_004f1790(&DAT_00ea0e18,0x17cd);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x3c:
    cVar2 = FUN_0041c2c0(g_clientContext,0xf);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1397);
      FUN_004f1790(&DAT_00ea0e18,0x13fb);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x3d:
    cVar2 = FUN_0041c2c0(g_clientContext,0xf);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x178e);
      FUN_004f1790(&DAT_00ea0e18,0x178f);
      FUN_004f1790(&DAT_00ea0e18,0x17f2);
      FUN_004f1790(&DAT_00ea0e18,0x17f3);
      FUN_004f1790(&DAT_00ea0e18,0x1a4a);
      FUN_004f1790(&DAT_00ea0e18,0x1a4b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x3e:
    cVar2 = FUN_0041c2c0(g_clientContext,0xf);
    if ((cVar2 != '\0') && (*(char *)(g_clientContext + 0x45578) == '\0')) {
      FUN_004f1790(&DAT_00ea0e18,0x1f5e);
      FUN_004f1790(&DAT_00ea0e18,0x1f5f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x2017);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x207b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x3f:
    FUN_004f1790(&DAT_00ea0e18,7000);
    FUN_004f1790(&DAT_00ea0e18,0x1b59);
    FUN_004f1790(&DAT_00ea0e18,0x1b5a);
    FUN_004f1790(&DAT_00ea0e18,0x1bbc);
    if (*(char *)(g_clientContext + 0x45578) == '\x01') {
      FUN_004f1790(&DAT_00ea0e18,6000);
      FUN_004f1790(&DAT_00ea0e18,0x17d4);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,8000);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x40:
    if (*(char *)(g_clientContext + 0x45578) == '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1838);
      FUN_004f1790(&DAT_00ea0e18,0x189c);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x1fa4);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x41:
    if (*(char *)(g_clientContext + 0x45578) == '\0') {
      FUN_004f1790(&DAT_00ea0e18,0x1839);
      FUN_004f1790(&DAT_00ea0e18,0x189d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      FUN_004f1790(&DAT_00ea0e18,0x1fa5);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x42:
    FUN_004f1790(&DAT_00ea0e18,0x183a);
    FUN_004f1790(&DAT_00ea0e18,0x189e);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x1fa6);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x1900);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x43:
    FUN_004f1790(&DAT_00ea0e18,0x1fa7);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,9000);
    break;
  case 0x44:
    FUN_004f1790(&DAT_00ea0e18,0x1964);
    FUN_004f1790(&DAT_00ea0e18,0x1965);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x1fa8);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x45:
    FUN_004f1790(&DAT_00ea0e18,4000);
    FUN_004f1790(&DAT_00ea0e18,0x1194);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x1f4e);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x46:
    if (*(char *)(g_clientContext + 0x5010d) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x47:
    if (*(char *)(g_clientContext + 0x5010e) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x48:
    if (*(char *)(g_clientContext + 0x5010f) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x49:
    if (*(char *)(g_clientContext + 0x50110) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x4a:
    if (*(char *)(g_clientContext + 0x50111) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x4b:
    if (*(char *)(g_clientContext + 0x50112) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x4c:
    if (*(char *)(g_clientContext + 0x50113) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x4d:
    if (*(char *)(g_clientContext + 0x50114) != '\0') {
      FUN_004431a0();
    }
    break;
  case 0x4e:
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x14b4);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004f1790(&DAT_00ea0e18,0x14b5);
    FUN_004f1790(&DAT_00ea0e18,0x14b6);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x4f:
    FUN_004f1790(&DAT_00ea0e18,0x2329);
    cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,3);
    if (cVar2 != '\0') {
      FUN_004f1790(&DAT_00ea0e18,3000);
      FUN_004f1790(&DAT_00ea0e18,0xbb9);
      FUN_004f1790(&DAT_00ea0e18,0xbba);
      FUN_004f1790(&DAT_00ea0e18,0xbbb);
      FUN_004f1790(&DAT_00ea0e18,0xc1c);
      FUN_004f1790(&DAT_00ea0e18,0xc1d);
      FUN_004f1790(&DAT_00ea0e18,0xc1e);
      FUN_004f1790(&DAT_00ea0e18,0xc1f);
      FUN_004f1790(&DAT_00ea0e18,0xc80);
      FUN_004f1790(&DAT_00ea0e18,0xc81);
      FUN_004f1790(&DAT_00ea0e18,0xc82);
      FUN_004f1790(&DAT_00ea0e18,0xc83);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x50:
    FUN_004f1790(&DAT_00ea0e18,1000);
    FUN_004f1790(&DAT_00ea0e18,0x3e9);
    FUN_004f1790(&DAT_00ea0e18,0x3ea);
    FUN_004f1790(&DAT_00ea0e18,0x3eb);
    FUN_004f1790(&DAT_00ea0e18,0x3ec);
    FUN_004f1790(&DAT_00ea0e18,0x3ed);
    FUN_004f1790(&DAT_00ea0e18,0x3ee);
    FUN_004f1790(&DAT_00ea0e18,0x3ef);
    FUN_004f1790(&DAT_00ea0e18,0x3f0);
    FUN_004f1790(&DAT_00ea0e18,0x3f1);
    FUN_004f1790(&DAT_00ea0e18,0x3f2);
    FUN_004f1790(&DAT_00ea0e18,0x3f3);
    FUN_004f1790(&DAT_00ea0e18,0x3f4);
    FUN_004f1790(&DAT_00ea0e18,0x3f5);
    FUN_004f1790(&DAT_00ea0e18,0x3f6);
    FUN_004f1790(&DAT_00ea0e18,0x3f7);
    FUN_004f1790(&DAT_00ea0e18,0x3f8);
    FUN_004f1790(&DAT_00ea0e18,0x3f9);
    FUN_004f1790(&DAT_00ea0e18,0x3fa);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x51:
    Replay_AppendEvent(0x82ff);
    Replay_FlushEvent();
  }
  if (*(int *)(param_1 + 0x108) == -1) {
    iVar4 = 0;
    do {
      if ((*(char *)(g_clientContext + 0x45914 + iVar4) != '\0') &&
         (*(char *)(g_clientContext + 0x449ba + iVar4) == '\0')) goto LAB_00442056;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 8);
    *(undefined4 *)(param_1 + 0x108) = 0x3c;
  }
LAB_00442056:
  if (*(int *)(param_1 + 0x108) % 0x14 == 0) {
    FUN_004ee9b0(0);
  }
  if ((0 < *(int *)(param_1 + 0x108)) &&
     (iVar4 = *(int *)(param_1 + 0x108) + -1, *(int *)(param_1 + 0x108) = iVar4, iVar4 == 0)) {
    *(undefined4 *)(param_1 + 0x108) = 0xfffffffe;
    g_pendingGameState = 0xb;
    g_stateChangeRequested = 0;
    DAT_0056d108 = 0;
    _DAT_007934d8 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 == iVar5) {
      Replay_AppendEvent(0x8600);
      Replay_FlushEvent();
    }
  }
  return;
}

