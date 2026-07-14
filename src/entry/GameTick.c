/* GameTick - 0x00413130 in the original binary.
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

/* CGameState's OnTick(+0x24)/etc. virtuals take `this` via ECX
 * (__fastcall), same as OnEnter/OnExit - see ChangeGameState.c's
 * GameStateVirtualFn comment. The generic `code()` cast (plain cdecl)
 * this file used for these calls pushed `this` on the stack instead of
 * loading it into ECX, so State06_Logo2_OnTick (declared __fastcall,
 * confirmed via functions.h) read garbage/null off its own object
 * pointer and crashed. */
typedef void (__fastcall *GameStateVirtualFn)(void *thisPtr);
typedef void (__fastcall *GameStateVirtualFn3)(void *thisPtr, undefined4 a1, undefined4 a2, undefined4 a3);

/* IDirect3DDevice7/IDirectDrawSurface7 vtable calls below (g_pD3DDevice7,
 * g_pBackBufferSurface) were also cast through the generic `code()`/
 * `int(**)()` type (implicit __cdecl), not the COM methods' real
 * __stdcall. Ghidra's disassembly at these call sites (e.g. the Clear()
 * call at 0x413438) shows no caller-side `add esp, N` after the `call`,
 * confirming the callee already pops its own args - i.e. it's really
 * __stdcall, and a cdecl-typed call site here would add a redundant
 * caller-side cleanup once compiled, corrupting the frame (see
 * InitDirectDraw.c's identical fix/writeup). Given real prototypes here
 * too, matching InitDirectDraw.c's QueryInterfaceFn/etc. idiom. */
typedef HRESULT (WINAPI *D3DBeginSceneFn)(void *thisPtr);
typedef HRESULT (WINAPI *D3DEndSceneFn)(void *thisPtr);
typedef HRESULT (WINAPI *D3DClearFn)(void *thisPtr, DWORD count, void *rects, DWORD flags, DWORD color, undefined4 z, DWORD stencil);
typedef HRESULT (WINAPI *D3DSetRenderStateFn)(void *thisPtr, DWORD state, DWORD value);
typedef HRESULT (WINAPI *D3DSetTextureFn)(void *thisPtr, DWORD stage, void *texture);
typedef HRESULT (WINAPI *SurfaceUnlockFn)(void *thisPtr, void *rect);

void GameTick(void)

{
  undefined4 *puVar1;
  char cVar2;
  DWORD DVar3;
  char *_Format;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  DWORD DVar7;
  uint uVar8;
  undefined *puVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  char local_400 [1024];
  
  if (g_currentGameState == 0) {
    return;
  }
  if (g_currentGameState == 0xf) {
    return;
  }
  if (g_valueGuardTamperFlag == '\x01') {
    g_valueGuardTamperFlag = '\0';
    ShowErrorDialog(1);
  }
  if ((DAT_00793640 != 0) && (DAT_00793516 == '\0')) {
    g_pendingGameState = 0xf;
    g_stateChangeRequested = '\x01';
    ChangeGameState(0xf);
    DAT_00793516 = '\x01';
  }
  DVar3 = timeGetTime();
  uVar10 = (DVar3 - DAT_007934e0) / 0x32;
  if (DAT_00793521 != '\0') {
    puVar12 = &DAT_005b22d0;
    _Format = (char *)GetLocalizedString(&g_localizedStringTable,9000);
    _sprintf(local_400,_Format,puVar12);
    DAT_00793521 = '\0';
    (*(GameStateVirtualFn3 *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
              (g_gameStateVTableArray[g_currentGameState],local_400,2,6);
  }
  if (uVar10 == 0) {
    return;
  }
  PumpBattleActions(uVar10);
  DAT_007934fc = DAT_007934fc + 1;
  if (1 < uVar10) {
    DAT_00793500 = DAT_00793500 + -1 + uVar10;
  }
  g_frameCounter = g_frameCounter + uVar10;
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\x01') {
    SubFromPacketChecksum(uVar10);
    cVar2 = PacketChecksumLessEqual(&DAT_006aa67c + g_clientContext,0);
    if (cVar2 != '\0') {
      SetGuardedBool(0);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9084);
  FUN_0050f290();
  /* orig 0x4132a4 loads EBX = &DAT_00e9be90 immediately before this call
   * (0x4132a9); TickActiveObjectRegistry's argument was dropped by Ghidra as
   * unaff_EBX - see that file. */
  TickActiveObjectRegistry((int)&DAT_00e9be90);
  /* orig 0x4132ae loads EAX = &DAT_00e9c0fc immediately before this call
   * (0x4132b3); SyncActiveTextInput's registry argument was dropped by Ghidra
   * as in_EAX - see that file. */
  SyncActiveTextInput((int)&DAT_00e9c0fc);
  FUN_0041b6f0();
  FUN_0041c0a0();
  FUN_004022b0();
  FUN_00412130();
  if ((g_bBattleSessionActive == '\0') && (DAT_00793517 == '\0')) {
    DAT_00793517 = 0;
    for (uVar8 = uVar10; uVar8 != 0; uVar8 = uVar8 - 1) {
      (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x24))
                (g_gameStateVTableArray[g_currentGameState]);
      FUN_004b3e00(&DAT_00e9b4e8);
      if (DAT_0056d118 != -1) {
        DAT_0056d118 = DAT_0056d118 + 1;
      }
    }
  }
  else {
    (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x24))
              (g_gameStateVTableArray[g_currentGameState]);
  }
  DAT_00793517 = 0;
  for (; uVar10 != 0; uVar10 = uVar10 - 1) {
    /* Ghidra dropped both calls' real argument: the disassembly at
     * 0x413340/0x41334a loads ECX with fixed global struct addresses
     * (0xe53698, 0xe52810) immediately before each call, not any value
     * derived from this function's own locals. These are the same two
     * DirectInput device-object addresses already identified in
     * FUN_004ee270.c (mouse, 0xe53698) and FUN_004edd70.c (keyboard,
     * 0xe52810) - FUN_004ee540 decrements that struct's input-timer
     * fields at +0x68..+0x84 once per elapsed tick, and FUN_004ee0d0
     * decrements another set of that struct's fields at +0x25c-0x4
     * through +0x25c+0x8, repeated over 0x40 stride-0x10 entries.
     * AdvanceSpriteAnimation's own argument is likewise dropped: orig
     * 0x413354/0x413359 loads EAX with the cursor singleton 0x7a7644
     * immediately before the call - this is the software-cursor tick. */
    /* Orig passes the fixed device/cursor singleton addresses 0xe53698 (mouse),
     * 0xe52810 (keyboard), 0x7a7644 (cursor) as literals. Those singletons are
     * never constructed in bring-up (their DirectInput constructors are
     * stubbed), so point the timer updates at zeroed backing blocks - a correct
     * no-op for the input-less logo path. See globals.c. */
    FUN_004ee540((int)g_mouseDeviceTimerBlock);
    FUN_004ee0d0((int)g_keyboardDeviceTimerBlock);
    AdvanceSpriteAnimation((int)g_softwareCursorAnimBlock);
  }
  if (5 < *(int *)(&DAT_0067e3c8 + g_clientContext)) {
    if (DAT_00793515 == '\0') {
      iVar5 = *(int *)g_gameStateVTableArray[g_currentGameState];
      uVar13 = 6;
      uVar11 = 2;
      DAT_00793515 = '\x01';
      uVar4 = GetLocalizedString(&g_localizedStringTable,0x141);
      (*(GameStateVirtualFn3 *)(iVar5 + 0x28))(g_gameStateVTableArray[g_currentGameState],uVar4,uVar11,uVar13);
      *(undefined4 *)(&DAT_0067e3c8 + g_clientContext) = 0;
    }
    else {
      ShowErrorDialog(1);
      *(undefined4 *)(&DAT_0067e3c8 + g_clientContext) = 0;
    }
  }
  FUN_00425770(g_clientContext);
  FUN_00422f70(g_clientContext);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9084);
  if (DAT_007934cc == '\0') goto LAB_00413a44;
  g_frameTriangleCounter = 0;
  if (g_pD3DDevice7 != (int *)0x0) {
    (*(D3DClearFn *)(*g_pD3DDevice7 + 0x28))(g_pD3DDevice7,0,0,3,DAT_00793634,0x3f800000,0);
  }
  FUN_004e9070();
  _DAT_00793618 = 0;
  if (g_currentGameState == 0xb) {
    cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
    if (cVar2 == '\0') {
      DAT_0079352c = 0;
    }
    else {
      DAT_005b3620 = DAT_005b3620 / 2;
      (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x2c))
                (g_gameStateVTableArray[g_currentGameState]);
      DAT_0079352c = 0;
      (*(SurfaceUnlockFn *)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
    }
    iVar5 = (*(D3DBeginSceneFn *)(*g_pD3DDevice7 + 0x14))(g_pD3DDevice7);
    if (iVar5 == 0) {
      FUN_004f3ea0();
      (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x30))
                (g_gameStateVTableArray[g_currentGameState]);
      if (DAT_00793610 != '\0') {
        (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,7,0);
      }
      DAT_00793610 = '\0';
      FUN_004f3ee0();
      (*(D3DEndSceneFn *)(*g_pD3DDevice7 + 0x18))(g_pD3DDevice7);
    }
LAB_00413510:
    cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
    if (cVar2 == '\0') {
      DAT_0079352c = 0;
    }
    else {
      DAT_005b3620 = DAT_005b3620 / 2;
      (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x34))
                (g_gameStateVTableArray[g_currentGameState]);
      DAT_0079352c = 0;
      (*(SurfaceUnlockFn *)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
    }
    iVar5 = (*(D3DBeginSceneFn *)(*g_pD3DDevice7 + 0x14))(g_pD3DDevice7);
    if (iVar5 == 0) {
      FUN_004f3ea0();
      (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x38))
                (g_gameStateVTableArray[g_currentGameState]);
      if (DAT_00793610 != '\0') {
        (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,7,0);
      }
      DAT_00793610 = '\0';
      FUN_004f3ee0();
      (*(D3DEndSceneFn *)(*g_pD3DDevice7 + 0x18))(g_pD3DDevice7);
    }
  }
  else if ((g_currentGameState == 9) || (g_currentGameState == 7)) goto LAB_00413510;
  cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
  if (cVar2 == '\0') {
    DAT_0079352c = 0;
  }
  else {
    DAT_005b3620 = DAT_005b3620 / 2;
    (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x3c))
              (g_gameStateVTableArray[g_currentGameState]);
    FUN_004b3e60(&DAT_00e9b4e8);
    DrawActiveObjectRegistry(&DAT_00e9be90);
    DrawActiveObjectRegistry(&DAT_00e9c0fc);
    iVar5 = DAT_00e53c48;
    while (iVar5 != 0) {
      puVar1 = (undefined4 *)(iVar5 + 8);
      iVar5 = *(int *)(iVar5 + 4);
      (*(GameStateVirtualFn *)(*(int *)*puVar1 + 0x24))((void *)*puVar1);
    }
    if ((g_stateChangeInProgress == 0) && (0x28 < DAT_0056d118)) {
      /* DrawSprite's arg was dropped as `in_EAX` - recovered from
       * objdump at this call site (0x413664): EAX is built as
       * `(DAT_0056d118 / 2) % 4` via cdq/sar/and-normalize, the usual
       * MSVC signed div-then-mod idiom for a power-of-2 divisor. */
      DrawSprite((DAT_0056d118 / 2) % 4);
    }
    DAT_0079352c = 0;
    (*(SurfaceUnlockFn *)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
  }
  iVar5 = (*(D3DBeginSceneFn *)(*g_pD3DDevice7 + 0x14))(g_pD3DDevice7);
  if (iVar5 == 0) {
    *(undefined4 *)(DAT_00792190 + 0x7c) = 0;
    DAT_00793660 = 1;
    if (DAT_00793611 != '\0') {
      (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,0);
    }
    DAT_00793611 = '\0';
    (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x40))
              (g_gameStateVTableArray[g_currentGameState]);
    if (DAT_0056d108 == -1) {
LAB_00413791:
      if (((g_stateChangeInProgress != 0) || (DAT_0079350c != '\0')) || (DAT_0079350d != '\0'))
      goto LAB_004137a9;
    }
    else {
      if (g_stateChangeInProgress == 0) {
        if (g_currentBlendMode != 1) {
          g_currentBlendMode = 1;
          _DAT_00792194 = 1;
          (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
          (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
        }
        (*(D3DSetTextureFn *)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
        FUN_004edaa0(0xffffffff,0xffffffff,800,0xffffffff,0xffffffff,
                     *(undefined4 *)(DAT_0056d108 * 4 + 0x56d11c));
        FUN_004edaa0(800,600 - *(int *)(DAT_0056d108 * 4 + 0x56d11c),800,600,0xffffffff,600);
        goto LAB_00413791;
      }
LAB_004137a9:
      if (g_currentBlendMode != 1) {
        g_currentBlendMode = 1;
        _DAT_00792194 = 1;
        (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
        (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
      }
      BuildColorQuad(0,0,799,0,799,599,0,599,0,0,0,0,0x80000000,0x80000000);
    }
    if (DAT_00793610 != '\0') {
      (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,7,0);
    }
    DAT_00793610 = '\0';
    FUN_004f3ee0();
    (*(D3DEndSceneFn *)(*g_pD3DDevice7 + 0x18))(g_pD3DDevice7);
  }
  cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
  if (cVar2 == '\0') {
    DAT_0079352c = 0;
  }
  else {
    DAT_005b3620 = DAT_005b3620 / 2;
    if (DAT_0079350d != '\0') {
      (*(GameStateVirtualFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x44))
                (g_gameStateVTableArray[g_currentGameState]);
    }
    if (g_stateChangeInProgress == 0) {
      if (DAT_0079350d != '\0') goto LAB_00413933;
    }
    else {
      /* FindSpriteFrame's (container,outerKey,innerKey) were dropped; orig
       * 0x4138a6-0x4138ab loads EAX=&DAT_00ea0e18, EDX=0x384, ESI=0. */
      if ((DAT_0079352c != 0) &&
          (iVar5 = FindSpriteFrame((int)&DAT_00ea0e18,0x384,0), iVar5 != 0)) {
        if (*(char *)(iVar5 + 0x18) == '\x01') {
          BlitSprite16bpp(0xf9,0xc1);
        }
        else {
          BlitSpriteClipped(0);
        }
      }
      /* BlitRLESprite's 1st/4th args (this/rleData) were dropped -
       * objdump at this call site (0x4138f7) shows ECX = 0x11d (this)
       * and EAX = &DAT_005b1d70 (rleData), the same text-scratch buffer
       * used by RenderWrappedText/ShowErrorDialogFmt elsewhere in this
       * codebase - not any locally computed cursor. */
      BlitRLESprite(0x11d,0xcf,0xffff,(byte *)DAT_005b1d70);
      iVar5 = 0xec;
      /* orig DAT_005b1da2 was DAT_005b1d70+0x32 in the original's fixed
       * address space (Ghidra split it into its own symbol) - now folded
       * into the sized DAT_005b1d70 array, see globals.c. */
      puVar9 = DAT_005b1d70 + 0x32;
      do {
        /* BlitRLESprite's 1st/4th args (this/rleData) were dropped -
         * objdump at this call site (0x41391d) shows ECX = 0x115 (this,
         * a FIXED constant reloaded every iteration - NOT an advancing
         * cursor derived from puVar9/iVar5) and EAX = esi (this file's
         * own puVar9, advanced by 0x32 each loop iteration). */
        BlitRLESprite(0x115,iVar5,0xffff,(byte *)puVar9);
        puVar9 = puVar9 + 0x32;
        iVar5 = iVar5 + 0xe;
      /* orig loop bound was the literal address DAT_005b1d70+0x15e
       * (0x5b1ece in the original's fixed address space) - a raw stack/data
       * offset that only made sense there; rewritten relative to our own
       * relinked DAT_005b1d70 so the loop terminates at the buffer's real
       * end regardless of where the linker places it. */
      } while (puVar9 < DAT_005b1d70 + 0x15e);
LAB_00413933:
      DrawActiveObjectRegistry(&DAT_00e9be90);
      DrawActiveObjectRegistry(&DAT_00e9c0fc);
    }
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\x01') && (g_frameCounter % 0x14 < 10)) {
      if (DAT_0079352c != 0) {
        /* orig 0x41397f-0x413989 loads EAX=&DAT_00ea0e18, EDX=0x190, ESI=0. */
        iVar5 = FindSpriteFrame((int)&DAT_00ea0e18,0x190,0);
        if (iVar5 != 0) {
          if (*(char *)(iVar5 + 0x18) == '\x01') {
            BlitSprite16bpp(0x2fc,8);
          }
          else {
            BlitSpriteClipped(0);
          }
        }
        goto LAB_004139be;
      }
    }
    else {
LAB_004139be:
      iVar5 = g_cursorFrame;
      /* orig 0x4139c6-0x4139d7 loads EAX=&DAT_00ea0e18, EDX=0, ESI=g_cursorFrame
       * (the software-cursor sprite lookup). */
      if (((DAT_0079352c != 0) && (-1 < g_cursorFrame)) &&
          (iVar6 = FindSpriteFrame((int)&DAT_00ea0e18,0,g_cursorFrame), iVar6 != 0)) {
        if (*(char *)(iVar6 + 0x18) == '\x01') {
          BlitSprite16bpp(g_cursorAnchorX,g_cursorAnchorY);
        }
        else {
          BlitSpriteClipped(iVar5);
        }
      }
    }
    if (DAT_00793520 != '\0') {
      DAT_00793520 = '\0';
      FUN_00412e50();
    }
    DAT_0079352c = 0;
    (*(SurfaceUnlockFn *)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
  }
  PresentFrame();
LAB_00413a44:
  DVar7 = timeGetTime();
  DAT_007934e0 = DVar3 - (DVar3 - DAT_007934e0) % 0x32;
  uVar10 = (DVar3 - DVar7) + 0x2d;
  Sleep(uVar10 & ((int)uVar10 < 1) - 1);
  timeGetTime();
  if (((DAT_0056d108 != -1) && (g_stateChangeInProgress == 0)) &&
     (DAT_0056d108 = DAT_0056d108 + _DAT_007934d8, DAT_0056d108 == 0xb)) {
    DAT_0056d108 = -1;
    ChangeGameState(g_pendingGameState);
  }
  if (g_stateChangeRequested != '\0') {
    ChangeGameState(g_pendingGameState);
  }
  DAT_00e536c4 = 0;
  DAT_00e536c0 = 0;
  return;
}

