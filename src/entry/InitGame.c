/* InitGame - 0x0040eaa0 in the original binary.
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

int InitGame(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  undefined1 local_40c [1024];
  undefined4 uStack_4; /* real local var, unrelated to the removed SEH
                         * plumbing below despite the name/position -
                         * reused for other purposes later in this
                         * function. */

  /* Ghidra decompiled a Windows SEH (__except) frame push/pop around
   * this function's body (FS-register frame-chain manipulation,
   * pushing a handler at LAB_0053ce9a on entry, popping it at every
   * return). The actual handler code wasn't included in this
   * function's decompilation - Ghidra only showed the frame plumbing,
   * not what LAB_0053ce9a actually does - so there's no way to
   * preserve its exact recovery behavior in portable C. Stripped
   * entirely (all three sites: this one, the early-return below, and
   * the function's tail) rather than guessing at a replacement -
   * flagged here so it's not lost history. If __except's specific
   * fault-recovery behavior for a failed init step ever turns out to
   * matter, this is the place to revisit. */
  FUN_00415900();
  LoadLocalizedStrings(&g_localizedStringTable);
  FUN_004e3500(&DAT_00794e14);
  LoadChooseEventConfig(&DAT_00e9bea8);
  CoInitialize((LPVOID)0x0);
  DAT_00588f4c = 0;
  BuildAssetPath(local_40c,&DAT_005b1ed0,s_graphics_xfs_00551fdc,0);
  /* param_1 is the main window HWND (WinMain calls InitGame(hWnd, hInstance));
   * the original passed it to InitDirectDraw in EAX. */
  iVar1 = InitDirectDraw(local_40c, (HWND)param_1);
  if (iVar1 == 0) {
    iVar1 = LoadGameDataFiles(g_clientContext);
    if (iVar1 != 0) {
      return iVar1 + 0xe0;
    }
    DAT_007934c8 = DAT_00f11dd4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (DAT_007934c8 == iVar1) {
      FUN_004f1eb0();
      BuildAssetPath(local_40c,&DAT_005b1ed0,s_sound_xfs_005526fc,0);
      InitDirectSound(param_1,0x10,local_40c);
      DAT_007934c8 = DAT_00ea0f54;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (DAT_007934c8 == iVar1) {
        InitDirectInput(param_2);
        FUN_004eae60();
        if ((*(int *)(&DAT_005f2f4c + g_clientContext) == 0) &&
           (DAT_0079354a = 0, DAT_00793549 != '\0')) {
          (**(code **)(*(int *)*DAT_00793554 + 0xc))();
          DAT_00793568 = 0;
        }
        if (*(int *)(&DAT_005f2f50 + g_clientContext) == 0) {
          uVar3 = 1;
          DAT_0079354b = 0;
          if (1 < DAT_00793560) {
            do {
              if (DAT_00793549 != '\0') {
                if (uVar3 != 0xffffffff) {
                  (**(code **)(*(int *)DAT_00793554[uVar3] + 0xc))();
                }
                if (uVar3 == 0) {
                  DAT_00793568 = 0;
                }
              }
              uVar3 = uVar3 + 1;
            } while (uVar3 < DAT_00793560);
          }
        }
        FUN_004eeb10();
        FUN_004eeb30();
        FUN_004edd70(param_1);
        FUN_004ee270(param_1);
        _DAT_00e53c24 = 0;
        _DAT_00e53c28 = 799;
        _DAT_00e53c2c = 0;
        _DAT_00e53c30 = 599;
        DAT_00e52858 = 200;
        DAT_00e52859 = 0xd0;
        DAT_00e5285a = 0xcb;
        DAT_00e5285b = 0xcd;
        DAT_00e52e68 = 0x39;
        FUN_004f0100();
        _DAT_00e9bea0 = &DAT_00795070;
        _DAT_00e9c108 = &DAT_00795070;
        _DAT_00e536e4 = &DAT_00795070;
        _DAT_00e5285c = &DAT_00795070;
        g_gameStateVTableArray[0] = operator_new(4);
        if ((undefined4 *)g_gameStateVTableArray[0] == (undefined4 *)0x0) {
          g_gameStateVTableArray[0] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[0] = &PTR_LAB_00553fb0;
        }
        g_gameStateVTableArray[1] = operator_new(8);
        if ((undefined4 *)g_gameStateVTableArray[1] == (undefined4 *)0x0) {
          g_gameStateVTableArray[1] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[1] = &vtable_State01_Title;
        }
        g_gameStateVTableArray[2] = operator_new(0x6c);
        if ((undefined4 *)g_gameStateVTableArray[2] == (undefined4 *)0x0) {
          g_gameStateVTableArray[2] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[2] = &vtable_State02_ServerSelect;
          *(undefined4 *)((int)g_gameStateVTableArray[2] + 0x68) = 0xffffffff;
        }
        g_gameStateVTableArray[3] = operator_new(0x294);
        if ((undefined4 *)g_gameStateVTableArray[3] == (undefined4 *)0x0) {
          g_gameStateVTableArray[3] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[3] = &vtable_State3_NetworkSession;
          *(undefined4 *)((int)g_gameStateVTableArray[3] + 0x11c) = 0;
          *(undefined1 *)((int)g_gameStateVTableArray[3] + 0x288) = 1;
        }
        g_gameStateVTableArray[5] = operator_new(8);
        if ((undefined4 *)g_gameStateVTableArray[5] == (undefined4 *)0x0) {
          g_gameStateVTableArray[5] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[5] = &vtable_State05_Logo1;
        }
        g_gameStateVTableArray[6] = operator_new(8);
        if ((undefined4 *)g_gameStateVTableArray[6] == (undefined4 *)0x0) {
          g_gameStateVTableArray[6] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[6] = &vtable_State06_Logo2;
        }
        pvVar2 = operator_new(0x34818);
        uStack_4 = 0;
        if (pvVar2 == (void *)0x0) {
          g_gameStateVTableArray[7] = (undefined *)0x0;
        }
        else {
          g_gameStateVTableArray[7] = (undefined *)FUN_00443c20(pvVar2);
        }
        uStack_4 = 0xffffffff;
        pvVar2 = operator_new(0x78c);
        uStack_4 = 1;
        if (pvVar2 == (void *)0x0) {
          g_gameStateVTableArray[9] = (undefined *)0x0;
        }
        else {
          g_gameStateVTableArray[9] = (undefined *)FUN_004d3770(pvVar2);
        }
        uStack_4 = 0xffffffff;
        g_gameStateVTableArray[10] = operator_new(0x150);
        if ((undefined4 *)g_gameStateVTableArray[10] == (undefined4 *)0x0) {
          g_gameStateVTableArray[10] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[10] = &vtable_State10_Loading;
        }
        pvVar2 = operator_new(0x2408);
        uStack_4 = 2;
        if (pvVar2 == (void *)0x0) {
          g_gameStateVTableArray[0xb] = (undefined *)0x0;
        }
        else {
          g_gameStateVTableArray[0xb] = (undefined *)FUN_004b3f90(pvVar2);
        }
        uStack_4 = 0xffffffff;
        g_gameStateVTableArray[0xf] = operator_new(4);
        if ((undefined4 *)g_gameStateVTableArray[0xf] == (undefined4 *)0x0) {
          g_gameStateVTableArray[0xf] = (undefined *)0x0;
        }
        else {
          *(undefined ***)g_gameStateVTableArray[0xf] = &PTR_LAB_00553fb0;
        }
        LoadSpriteSet(&DAT_00ea0e18,500);
        LoadSpriteSet(&DAT_00ea0e18,600);
        LoadSpriteSet(&DAT_00ea0e18,0x259);
        LoadSpriteSet(&DAT_00ea0e18,0x25a);
        LoadSpriteSet(&DAT_00ea0e18,0x262);
        LoadSpriteSet(&DAT_00ea0e18,0x263);
        LoadSpriteSet(&DAT_00ea0e18,0x264);
        LoadSpriteSet(&DAT_00ea0e18,700);
        LoadSpriteSet(&DAT_00ea0e18,0x2bd);
        LoadSpriteSet(&DAT_00ea0e18,0x2be);
        LoadSpriteSet(&DAT_00ea0e18,0x2bf);
        LoadSpriteSet(&DAT_00ea0e18,0x2c6);
        LoadSpriteSet(&DAT_00ea0e18,0x2c7);
        LoadSpriteSet(&DAT_00ea0e18,0x2c8);
        LoadSpriteSet(&DAT_00ea0e18,0x2c9);
        LoadSpriteSet(&DAT_00ea0e18,0x2ca);
        LoadSpriteSet(&DAT_00ea0e18,0x2cb);
        LoadSpriteSet(&DAT_00ea0e18,800);
        LoadSpriteSet(&DAT_00ea0e18,0x321);
        LoadSpriteSet(&DAT_00ea0e18,0x322);
        LoadSpriteSet(&DAT_00ea0e18,0x323);
        LoadSpriteSet(&DAT_00ea0e18,900);
        LoadSpriteSet(&DAT_00ea0e18,0x385);
        LoadSpriteSet(&DAT_00ea0e18,0x38e);
        LoadSpriteSet(&DAT_00ea0e18,0x398);
        LoadSpriteSet(&DAT_00ea0e18,0);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        LoadSpriteSet(&DAT_00ea0e18,1);
        LoadSpriteSet(&DAT_00ea0e18,2);
        LoadSpriteSet(&DAT_00ea0e18,3);
        LoadSpriteSet(&DAT_00ea0e18,0x32);
        LoadSpriteSet(&DAT_00ea0e18,0x33);
        LoadSpriteSet(&DAT_00ea0e18,0x34);
        LoadSpriteSet(&DAT_00ea0e18,100);
        LoadSpriteSet(&DAT_00ea0e18,0x65);
        LoadSpriteSet(&DAT_00ea0e18,0x6e);
        LoadSpriteSet(&DAT_00ea0e18,200);
        LoadSpriteSet(&DAT_00ea0e18,0xc9);
        LoadSpriteSet(&DAT_00ea0e18,0xca);
        LoadSpriteSet(&DAT_00ea0e18,0xcb);
        LoadSpriteSet(&DAT_00ea0e18,0xcc);
        LoadSpriteSet(&DAT_00ea0e18,0xcd);
        LoadSpriteSet(&DAT_00ea0e18,0xce);
        LoadSpriteSet(&DAT_00ea0e18,300);
        LoadSpriteSet(&DAT_00ea0e18,400);
        LoadSpriteSet(&DAT_00ea0e18,1000000);
        LoadSpriteSet(&DAT_00ea0e18,2000000);
        LoadSpriteSet(&DAT_00ea0e18,0x1e8483);
        LoadSpriteSet(&DAT_00ea0e18,0x1e8484);
        LoadSpriteSet(&DAT_00ea0e18,0x1e8485);
        LoadSpriteSet(&DAT_00ea0e18,0x1e8486);
        LoadSpriteSet(&DAT_00ea0e18,0x1e8487);
        LoadSpriteSet(&DAT_00ea0e18,0x1e8488);
        LoadSpriteSet(&DAT_00ea0e18,0x1e8489);
        LoadSpriteSet(&DAT_00ea0e18,0x1e848a);
        LoadSpriteSet(&DAT_00ea0e18,0x1e848b);
        LoadSpriteSet(&DAT_00ea0e18,1100000);
        LoadSpriteSet(&DAT_00ea0e18,2100000);
        LoadSpriteSet(&DAT_00ea0e18,0x200b21);
        LoadSpriteSet(&DAT_00ea0e18,0x200b22);
        LoadSpriteSet(&DAT_00ea0e18,0x200b23);
        pvVar2 = operator_new(0x10);
        if (pvVar2 == (void *)0x0) {
          DAT_007934e4 = 0;
        }
        else {
          /* Same class of call-site/definition mismatch as
           * FUN_004058c0 in WinMain.c: FUN_0040c670's own definition
           * (src/unnamed/FUN_0040c670.c) is void and takes a param this
           * call site doesn't pass. Left as a bare call rather than
           * guessing what DAT_007934e4 should become. */
          FUN_0040c670();
        }
        FUN_00415500();
        FUN_00415530();
        InterlockedExchange((LONG *)&DAT_00e9c348,1);
        FUN_004e6b50();
        _DAT_00e9acd0 = &DAT_00793798;
        FUN_00520380(param_1);
        iVar1 = 0;
      }
      else {
        iVar1 = 0xce;
      }
    }
    else {
      iVar1 = 0xcd;
    }
  }
  return iVar1;
}

