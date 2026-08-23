/* State07_AvatarStore_OnEnter - 0x00447760 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified. *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the per-category equipped part-code array at ctx+0x3ac08 walked by the C's own byte cursor iVar8 (0x224 per category, bound 0x890 = 4 categories) into the panel's +0x325a8 shorts - the array Equip/UnequipAvatarSlot write.  Its cell-less `EncodeOutgoingPacketField(0xffffffff)`/`(0)` calls remain 1-arg (value-only, cell dropped) - flagged for the encode pass.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Removing unreachable block (ram,0x00447efc) */
/* WARNING: Removing unreachable block (ram,0x00447f06) */

/* DROPPED-`this` FIX (2026-07-29): two vtable slot-1 calls below had their
 * `this` dropped by Ghidra (bare `(**(code**)(*obj+4))(arg)`, no leading
 * this), confirmed via objdump at 0x447c11-0x447c28 and 0x447f2b-0x447f34:
 *   - orig 0x447c17 `lea ecx,[ebp+0x30bbc]` - this = &(param_1+0x30bbc),
 *     the ADDRESS of that embedded sub-object (not the vtable-pointer
 *     value read from it into edx for the call target).
 *   - orig 0x447f32 `mov ecx,edi` - this = edi = piVar1, the walked list
 *     node already in scope at the call site.
 * Both are genuine C++ __thiscall dispatches (this in ECX), so both use
 * the established __fastcall + literal-0 dummy-EDX idiom for an erased
 * __thiscall vtable slot (ghidra_types.h keeps __fastcall real under MSVC
 * but erases __thiscall - same pattern as WndProc.c's StateSlot6DispatchFn).
 * Left dropped, `this` came through as whatever ECX last held, so this
 * crashed (wild vtable-slot-1 call through garbage) reproduced live the
 * moment the AVATAR button opened this state.
 *
 * DROPPED-EAX .img NAMES FIX (2026-08-06): all 30 LoadSpriteSet calls
 * below were missing their third argument. LoadSpriteSet takes the
 * sprite-set name in EAX (`LoadSpriteSet(container, key, imgName)` -
 * see LoadSpriteSet.c), Ghidra dropped it, and functions.h declares
 * LoadSpriteSet K&R-empty so the 2-arg calls compiled silently. The
 * name pointer then came through as stale garbage and FindXFSEntry ->
 * CompareXFSEntryName faulted dereferencing it - live-reproduced as the
 * first crash reached once the destructor-chain bugs were fixed and
 * this state actually became reachable. Recovered all 30 names from the
 * original's own call sites (0x447776-0x4479ba, `mov eax,<.rdata addr>`
 * before each `call 0x4f1790`); every recovered key was asserted equal
 * to the key already in this file, so the names line up positionally by
 * construction. Same bug class as InitGame's 60 LoadSpriteSet calls.
 *
 * DROPPED-EAX BUTTON NAMES FIX (2026-08-06): the same bug, one call
 * deeper. All 25 AppendPersistentButtonName calls below were missing
 * their name argument too (it also arrives in EAX - see that file's
 * header, and ChangeGameState.c's already-recovered call sites), and
 * again functions.h declares it K&R-empty so the 1-arg calls compiled.
 * Once the LoadSpriteSet names above were restored this became the next
 * live crash, faulting on the stale name pointer inside the function's
 * first string-copy loop. Recovered all 25 from the original's own call
 * sites (0x4479cf-0x447bf6, `mov eax,<.rdata addr>` before each
 * `call 0x401740`); 7 of the strings had no symbol yet and were added to
 * globals.c/globals.h following the existing s_<name>_<addr> naming. */
typedef void (__fastcall *VtableSlot1StrFn)(void *thisPtr, int dummyEDX, const char *str);

void __fastcall State07_AvatarStore_OnEnter(int param_1)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  byte bVar6;
  undefined2 *puVar7;
  int iVar8;
  
  LoadSpriteSet(&g_spriteRegistry,10000,"store_back.img");
  LoadSpriteSet(&g_spriteRegistry,0x2711,"store_avatar.img");
  LoadSpriteSet(&g_spriteRegistry,0x2712,"store_myavatar.img");
  LoadSpriteSet(&g_spriteRegistry,0x2713,"store_icon.img");
  LoadSpriteSet(&g_spriteRegistry,0x2714,"store_window_back.img");
  LoadSpriteSet(&g_spriteRegistry,1000,"b_store_exit.img");
  LoadSpriteSet(&g_spriteRegistry,0x3e9,"b_store_buddygame.img");
  LoadSpriteSet(&g_spriteRegistry,0x44c,"b_store_cap.img");
  LoadSpriteSet(&g_spriteRegistry,0x44d,"b_store_cloth.img");
  LoadSpriteSet(&g_spriteRegistry,0x44e,"b_store_glasse.img");
  LoadSpriteSet(&g_spriteRegistry,0x44f,"b_store_flag.img");
  LoadSpriteSet(&g_spriteRegistry,0x450,"b_store_exitem.img");
  LoadSpriteSet(&g_spriteRegistry,0x451,"b_store_puton.img");
  LoadSpriteSet(&g_spriteRegistry,0x452,"b_store_buy.img");
  LoadSpriteSet(&g_spriteRegistry,0x453,"b_store_up.img");
  LoadSpriteSet(&g_spriteRegistry,0x454,"b_store_down.img");
  LoadSpriteSet(&g_spriteRegistry,0x455,"b_store_cashcharge.img");
  LoadSpriteSet(&g_spriteRegistry,0x456,"b_store_event01.img");
  LoadSpriteSet(&g_spriteRegistry,0x457,"b_store_event02.img");
  LoadSpriteSet(&g_spriteRegistry,0x4b0,"b_myavatar_sell.img");
  LoadSpriteSet(&g_spriteRegistry,0x4b1,"b_myavatar_dry.img");
  LoadSpriteSet(&g_spriteRegistry,0x4b2,"b_myavatar_gift.img");
  LoadSpriteSet(&g_spriteRegistry,0x4b3,"b_myavatar_leave.img");
  LoadSpriteSet(&g_spriteRegistry,0x514,"b_storewindow_yes.img");
  LoadSpriteSet(&g_spriteRegistry,0x515,"b_storewindow_no.img");
  LoadSpriteSet(&g_spriteRegistry,0x516,"b_storewindow_confirm.img");
  LoadSpriteSet(&g_spriteRegistry,0x517,"b_storewindow_cancel.img");
  LoadSpriteSet(&g_spriteRegistry,0x518,"b_storewindow_cashcharge.img");
  LoadSpriteSet(&g_spriteRegistry,0x519,"b_storewindow_gold.img");
  LoadSpriteSet(&g_spriteRegistry,0x51a,"b_storewindow_cash.img");
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_exit_00555778);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_buddygame_00555764);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_cap_00555758);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_cloth_00555748);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_glasse_00555738);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_flag_00555728);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_exitem_00555718);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_puton_00555708);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_buy_005556fc);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_up_005556f0);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_down_005556e0);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_cashcharge_005556cc);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_event01_005556bc);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_event02_005556ac);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_sell_0055569c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_dry_00555690);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_store_gift_00555680);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_storewindow_yes_00555a1c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_storewindow_no_0055566c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_storewindow_confirm_00555a8c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_storewindow_cancel_00555a30);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_storewindow_cashcharge_00555a70);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_storewindow_gold_00555a5c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_storewindow_cash_00555a48);
  PreloadTexture(&g_textureCache,s_AvataTexture1_0055565c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_avata_00553fa8);
  uVar5 = FindPreloadedTextureByName(s_avata_00553fa8);
  *(undefined4 *)(param_1 + 0x30bd8) = uVar5;
  (*(VtableSlot1StrFn *)(*(int *)(param_1 + 0x30bbc) + 4))
            ((void *)(param_1 + 0x30bbc),0,s_normal_00552230);
  PlayMusicTrack(1,(byte *)"channel.mp3");
  *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x32f91) = 0;
  NoOpMethod();
  cVar3 = FUN_00419d30();
  if (cVar3 == '\0') {
    ShowErrorDialog(1);
  }
  /* orig 0x447c6e `mov ebx,[0x5b3484]` immediately before `call 0x423bf0`
   * - the inbound EBX is g_clientContext ITSELF (the callee derives the
   * avatar archive as ctx+0xf6e8 and encodes the per-category part-count
   * guard cells at ctx+0x5f3774..; see FUN_00423bf0.c's 2026-08-11
   * header). Was passed pre-offset (ctx+0xf6e8) before that fix. */
  FUN_00423bf0((int)g_clientContext);
  FUN_00449540(param_1,1);
  *(undefined4 *)(param_1 + 0x454) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  FUN_0044b0b0(param_1);
  FUN_00424400();
  *(undefined1 *)(param_1 + 0x30bb8) = 0;
  LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar8 = 0;
  puVar7 = (undefined2 *)(param_1 + 0x325a8);
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ac08 + iVar8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    *puVar7 = uVar4;
    iVar8 = iVar8 + 0x224;
    puVar7 = puVar7 + 1;
  } while (iVar8 < 0x890);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32c54) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32c55) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32c54) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32c55) = bVar6;
  *(byte *)(param_1 + 0x32c56) = *(byte *)(param_1 + 0x32c54) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32e63) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32e64) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32e63) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32e64) = bVar6;
  *(byte *)(param_1 + 0x32e65) = *(byte *)(param_1 + 0x32e63) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32ce0) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32ce1) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32ce0) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32ce1) = bVar6;
  *(byte *)(param_1 + 0x32ce2) = *(byte *)(param_1 + 0x32ce0) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined1 *)(param_1 + 0x32f90) = 1;
  CreateAvatarStoreButtons(param_1);
  if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
    piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
    uVar2 = piVar1[2];
    while (uVar2 < 0xb) {
      if (uVar2 == 10) {
        *(undefined1 *)(piVar1 + 0x13) = 0;
        if (piVar1[9] != 3) {
          (*(VtableSlot1StrFn *)(*piVar1 + 4))(piVar1,0,s_active_00551e58);
          *(undefined1 *)(piVar1 + 0x13) = 1;
        }
        break;
      }
      piVar1 = (int *)piVar1[4];
      uVar2 = piVar1[2];
    }
  }
  uVar5 = BuildAvatarStorePanel(&g_uiPanelManager);
  *(undefined4 *)(param_1 + 0x34784) = uVar5;
  FUN_00449250(param_1,1,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar8 = g_clientContext;
  *(undefined1 *)(param_1 + 0x32f92) = 0;
  *(undefined4 *)(param_1 + 0x32f94) = 0x80000000;
  *(undefined4 *)(param_1 + 0x32f98) = 0x7fffffff;
  if (*(int *)(iVar8 + 0x44bec) == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar8 = _rand();
    *(char *)(param_1 + 0x32e63) = (char)iVar8;
    iVar8 = _rand();
    *(byte *)(param_1 + 0x32e64) = (byte)iVar8;
    bVar6 = *(byte *)(param_1 + 0x32e63) & 7;
    bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
    *(byte *)(param_1 + 0x32e64) = bVar6;
    *(byte *)(param_1 + 0x32e65) = *(byte *)(param_1 + 0x32e63) + bVar6 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    CreateAvatarStoreButtons(param_1);
  }
  else {
    RenderInventoryItemDetail(param_1);
  }
  *(undefined4 *)(param_1 + 0x34790) = 0;
  *(undefined1 *)(param_1 + 0x34814) = 0;
  *(undefined4 *)(param_1 + 0x32f9c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3478c) = 0xffffffff;
  return;
}

