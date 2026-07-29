/* State07_AvatarStore_OnEnter - 0x00447760 in the original binary.
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
 * moment the AVATAR button opened this state. */
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
  
  LoadSpriteSet(&DAT_00ea0e18,10000);
  LoadSpriteSet(&DAT_00ea0e18,0x2711);
  LoadSpriteSet(&DAT_00ea0e18,0x2712);
  LoadSpriteSet(&DAT_00ea0e18,0x2713);
  LoadSpriteSet(&DAT_00ea0e18,0x2714);
  LoadSpriteSet(&DAT_00ea0e18,1000);
  LoadSpriteSet(&DAT_00ea0e18,0x3e9);
  LoadSpriteSet(&DAT_00ea0e18,0x44c);
  LoadSpriteSet(&DAT_00ea0e18,0x44d);
  LoadSpriteSet(&DAT_00ea0e18,0x44e);
  LoadSpriteSet(&DAT_00ea0e18,0x44f);
  LoadSpriteSet(&DAT_00ea0e18,0x450);
  LoadSpriteSet(&DAT_00ea0e18,0x451);
  LoadSpriteSet(&DAT_00ea0e18,0x452);
  LoadSpriteSet(&DAT_00ea0e18,0x453);
  LoadSpriteSet(&DAT_00ea0e18,0x454);
  LoadSpriteSet(&DAT_00ea0e18,0x455);
  LoadSpriteSet(&DAT_00ea0e18,0x456);
  LoadSpriteSet(&DAT_00ea0e18,0x457);
  LoadSpriteSet(&DAT_00ea0e18,0x4b0);
  LoadSpriteSet(&DAT_00ea0e18,0x4b1);
  LoadSpriteSet(&DAT_00ea0e18,0x4b2);
  LoadSpriteSet(&DAT_00ea0e18,0x4b3);
  LoadSpriteSet(&DAT_00ea0e18,0x514);
  LoadSpriteSet(&DAT_00ea0e18,0x515);
  LoadSpriteSet(&DAT_00ea0e18,0x516);
  LoadSpriteSet(&DAT_00ea0e18,0x517);
  LoadSpriteSet(&DAT_00ea0e18,0x518);
  LoadSpriteSet(&DAT_00ea0e18,0x519);
  LoadSpriteSet(&DAT_00ea0e18,0x51a);
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
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  PreloadTexture(&g_textureCache,s_AvataTexture1_0055565c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
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
  /* archive = g_clientContext + 0xf6e8, orig 0x447c6e `mov ebx,[0x5b3484]`
   * immediately before `call 0x423bf0` - see FUN_00423bf0.c's header. */
  FUN_00423bf0((int)(g_clientContext + 0xf6e8));
  FUN_00449540(param_1,1);
  *(undefined4 *)(param_1 + 0x454) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0044b0b0(param_1);
  FUN_00424400();
  *(undefined1 *)(param_1 + 0x30bb8) = 0;
  LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = 0;
  puVar7 = (undefined2 *)(param_1 + 0x325a8);
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *puVar7 = uVar4;
    iVar8 = iVar8 + 0x224;
    puVar7 = puVar7 + 1;
  } while (iVar8 < 0x890);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32c54) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32c55) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32c54) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32c55) = bVar6;
  *(byte *)(param_1 + 0x32c56) = *(byte *)(param_1 + 0x32c54) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32e63) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32e64) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32e63) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32e64) = bVar6;
  *(byte *)(param_1 + 0x32e65) = *(byte *)(param_1 + 0x32e63) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32ce0) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32ce1) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32ce0) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32ce1) = bVar6;
  *(byte *)(param_1 + 0x32ce2) = *(byte *)(param_1 + 0x32ce0) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_1 + 0x32f90) = 1;
  FUN_0044b720(param_1);
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
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = g_clientContext;
  *(undefined1 *)(param_1 + 0x32f92) = 0;
  *(undefined4 *)(param_1 + 0x32f94) = 0x80000000;
  *(undefined4 *)(param_1 + 0x32f98) = 0x7fffffff;
  if (*(int *)(iVar8 + 0x44bec) == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = _rand();
    *(char *)(param_1 + 0x32e63) = (char)iVar8;
    iVar8 = _rand();
    *(byte *)(param_1 + 0x32e64) = (byte)iVar8;
    bVar6 = *(byte *)(param_1 + 0x32e63) & 7;
    bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
    *(byte *)(param_1 + 0x32e64) = bVar6;
    *(byte *)(param_1 + 0x32e65) = *(byte *)(param_1 + 0x32e63) + bVar6 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0044b720(param_1);
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

