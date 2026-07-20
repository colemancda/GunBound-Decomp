/* InitGame - 0x0040eaa0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * RECOVERED (2026-07-18): all 60 LoadSpriteSet calls in the common-UI
 * preload block had their name string DROPPED - LoadSpriteSet (0x4f1790)
 * takes the ".img" entry name in EAX (see LoadSpriteSet.c), and every call
 * site here loads a distinct .data string literal into EAX immediately
 * before `call 0x4f1790` (0x40eebf-0x40f4xx: `push <id>; push 0xea0e18;
 * mov eax,<str>; call`). Ghidra dropped all 60, so the ports called the
 * 3-arg LoadSpriteSet through the K&R decl with a garbage name -> every
 * common-UI sprite set (scrollbar arrows b_scroll_up/down.img 0x259/0x25a,
 * error dialogs, buddy list, report, cursor.img, number fonts...) failed to
 * load. Names extracted programmatically from the original .data via the PE
 * section table, ids cross-verified against each call site's `push` (the
 * one register-push site, `push ebx`=0 at 0x40f0b8, is cursor.img).
 * AppendPersistentButtonName's own dropped EAX here is "cursor"
 * (0x40f0d5: mov eax,0x5524e8) - the software cursor's .epa states. */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* Calling-convention cast mismatch (see file header pattern #2): the two
 * vtable calls below on DAT_00793554[]'s channel objects (slot +0xc) were
 * decompiled by Ghidra as bare no-arg `code()` calls, silently dropping the
 * channel object pointer that the original passes as `this` in ECX with no
 * stack args at all (confirmed via objdump -d -Mintel
 * --start-address=0x40eaa0 --stop-address=0x40ec90 orig/GunBound.gme:
 * `mov ecx,[eax]` / `mov edx,[ecx]` / `call DWORD PTR [edx+0xc]` at 0x40ec2c-
 * 0x40ec30, and `mov ecx,[ecx+esi*4]` / `mov edx,[ecx]` / `call [edx+0xc]`
 * at 0x40ec72-0x40ec77 - no push before either call). Same idiom as
 * ChangeGameState.c's GameStateVirtualFn. */
typedef void (__fastcall *ChannelVtableFn)(void *thisPtr);

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
        LoadBitmapFont();
        if ((*(int *)(&DAT_005f2f4c + g_clientContext) == 0) &&
           (DAT_0079354a = 0, DAT_00793549 != '\0')) {
          (*(ChannelVtableFn *)(*(int *)*DAT_00793554 + 0xc))(*DAT_00793554);
          DAT_00793568 = 0;
        }
        if (*(int *)(&DAT_005f2f50 + g_clientContext) == 0) {
          uVar3 = 1;
          DAT_0079354b = 0;
          if (1 < DAT_00793560) {
            do {
              if (DAT_00793549 != '\0') {
                if (uVar3 != 0xffffffff) {
                  (*(ChannelVtableFn *)(*(int *)DAT_00793554[uVar3] + 0xc))
                            (DAT_00793554[uVar3]);
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
        _DAT_00e9bea0 = &g_inputEventQueueWriteIndex;
        _DAT_00e9c108 = &g_inputEventQueueWriteIndex;
        _DAT_00e536e4 = &g_inputEventQueueWriteIndex;
        _DAT_00e5285c = &g_inputEventQueueWriteIndex;
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
          *(undefined ***)g_gameStateVTableArray[3] = &vtable_State03_GameRoomList;
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
          g_gameStateVTableArray[9] = (undefined *)State09_ReadyRoom_Construct(pvVar2);
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
        LoadSpriteSet(&DAT_00ea0e18,500,"numfont.img");
        LoadSpriteSet(&DAT_00ea0e18,600,"b_scroll_bar.img");
        LoadSpriteSet(&DAT_00ea0e18,0x259,"b_scroll_up.img");
        LoadSpriteSet(&DAT_00ea0e18,0x25a,"b_scroll_down.img");
        LoadSpriteSet(&DAT_00ea0e18,0x262,"b_scroll_bar2.img");
        LoadSpriteSet(&DAT_00ea0e18,0x263,"b_scroll_up2.img");
        LoadSpriteSet(&DAT_00ea0e18,0x264,"b_scroll_down2.img");
        LoadSpriteSet(&DAT_00ea0e18,700,"buddy_back.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2bd,"b_buddy_plus.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2be,"b_buddy_del.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2bf,"b_buddy_exit.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2c6,"buddy_window_back.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2c7,"b_buddywindow_exittalk.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2c8,"b_buddywindow_friendplus.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2c9,"b_buddywindow_friendclose.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2ca,"b_buddywindow_delyes.img");
        LoadSpriteSet(&DAT_00ea0e18,0x2cb,"b_buddywindow_delno.img");
        LoadSpriteSet(&DAT_00ea0e18,800,"report_back.img");
        LoadSpriteSet(&DAT_00ea0e18,0x321,"b_report_confirm.img");
        LoadSpriteSet(&DAT_00ea0e18,0x322,"b_report_exit.img");
        LoadSpriteSet(&DAT_00ea0e18,0x323,"b_report_close.img");
        LoadSpriteSet(&DAT_00ea0e18,900,"error_back.img");
        LoadSpriteSet(&DAT_00ea0e18,0x385,"b_error_confirm.img");
        LoadSpriteSet(&DAT_00ea0e18,0x38e,"info.img");
        LoadSpriteSet(&DAT_00ea0e18,0x398,"waitmessage.img");
        LoadSpriteSet(&DAT_00ea0e18,0,"cursor.img");
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)"cursor");
        LoadSpriteSet(&DAT_00ea0e18,1,"errordialog.img");
        LoadSpriteSet(&DAT_00ea0e18,2,"b_error_confirm.img");
        LoadSpriteSet(&DAT_00ea0e18,3,"waitmessage.img");
        LoadSpriteSet(&DAT_00ea0e18,0x32,"numberfont.img");
        LoadSpriteSet(&DAT_00ea0e18,0x33,"buddymode.img");
        LoadSpriteSet(&DAT_00ea0e18,0x34,"icon.img");
        LoadSpriteSet(&DAT_00ea0e18,100,"rank1.img");
        LoadSpriteSet(&DAT_00ea0e18,0x65,"rank2.img");
        LoadSpriteSet(&DAT_00ea0e18,0x6e,"info.img");
        LoadSpriteSet(&DAT_00ea0e18,200,"b_gamelist_buddyup.img");
        LoadSpriteSet(&DAT_00ea0e18,0xc9,"b_gamelist_buddydown.img");
        LoadSpriteSet(&DAT_00ea0e18,0xca,"b_gamelist_channelup.img");
        LoadSpriteSet(&DAT_00ea0e18,0xcb,"b_gamelist_channeldown.img");
        LoadSpriteSet(&DAT_00ea0e18,0xcc,"b_buddy_up.img");
        LoadSpriteSet(&DAT_00ea0e18,0xcd,"b_buddy_down.img");
        LoadSpriteSet(&DAT_00ea0e18,0xce,"b_buddy_exit.img");
        LoadSpriteSet(&DAT_00ea0e18,300,"avataimsi.img");
        LoadSpriteSet(&DAT_00ea0e18,400,"presentmode.img");
        LoadSpriteSet(&DAT_00ea0e18,1000000,"buddy2.img");
        LoadSpriteSet(&DAT_00ea0e18,2000000,"b_buddy2_addfriend1.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e8483,"b_buddy2_close.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e8484,"b_buddy2_yes.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e8485,"b_buddy2_no.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e8486,"b_buddy2_exit.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e8487,"b_buddy2_up.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e8488,"b_buddy2_down.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e8489,"b_buddy2_addfriend2.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e848a,"b_buddy2_deletefriend.img");
        LoadSpriteSet(&DAT_00ea0e18,0x1e848b,"b_buddy2_exit2.img");
        LoadSpriteSet(&DAT_00ea0e18,1100000,"reportmode.img");
        LoadSpriteSet(&DAT_00ea0e18,2100000,"b_report_exit.img");
        LoadSpriteSet(&DAT_00ea0e18,0x200b21,"b_report_report.img");
        LoadSpriteSet(&DAT_00ea0e18,0x200b22,"b_report_cancel.img");
        LoadSpriteSet(&DAT_00ea0e18,0x200b23,"b_report_close.img");
        pvVar2 = operator_new(0x10);
        if (pvVar2 == (void *)0x0) {
          DAT_007934e4 = 0;
        }
        else {
          /* FIXED (2026-07-14): FUN_0040c670 needs the freshly-allocated
           * block and the main window handle explicitly (both were
           * dropped registers - see that file's own header), AND
           * DAT_007934e4 itself was never actually assigned on this
           * success path (only ever zeroed on the allocation-failure
           * branch above) - confirmed via objdump at InitGame's own
           * call site (orig 0x40f373: `mov esi,eax` right after
           * operator_new, left untouched all the way to the call - a
           * pure passthrough, i.e. this block itself is what
           * DAT_007934e4 is meant to hold). State02_ServerSelect_OnEnter
           * dereferences DAT_007934e4 unconditionally on entry - left
           * NULL, this was a real, live-reproduced NULL+8 write crash
           * the instant the game reached server select. */
          DAT_007934e4 = (uint32_t)pvVar2;
          FUN_0040c670((HINSTANCE)param_2,(undefined4 *)pvVar2,(HWND)param_1);
        }
        /* Both take a fixed global control-block pointer via a dropped ESI
         * register in the original (0x40f38e/0x40f39d); see their own .c
         * files for the recovered addresses. */
        FUN_00415500(DAT_00e9c334);
        FUN_00415530(DAT_007a767c);
        InterlockedExchange((LONG *)&DAT_00e9c348,1);
        FUN_004e6b50();
        _DAT_00e9acd0 = &g_gameEventRingWriteIndex;
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

