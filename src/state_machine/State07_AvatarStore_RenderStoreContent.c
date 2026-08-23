/* State07_AvatarStore_RenderStoreContent - 0x00448440 in the original binary.
 *
 * PORTED + RENAMED (2026-08-09): CState07AvatarStore's vtable slot 13
 * (+0x34) - the store's main per-frame render. Draws, in order: the
 * store background sprites (store_back.img key 0x2710 and the window
 * frame key 0x64), the packet/guard debug label overlays (only when the
 * +0x23313 debug flag is set), the 9-cell item grid (FUN_0044a000), the
 * off-screen avatar-preview composite (DirectDraw surface Lock/clear/two
 * BlitAvatarFrameToPreviewTexture blits/Unlock), and the item-detail / category
 * tab labels. Was an unported bring-up auto-stub, so the whole store main
 * area rendered BLACK - only the panel-manager widgets (buddy frame,
 * bottom buttons, scrollbars) drew. Sibling slot 14
 * (State07_AvatarStore_RenderAvatarPreview) draws the avatar on top.
 *
 * REGISTER-RECOVERED ARGS (from orig 0x448440-0x44904f disassembly): the
 * store object `this` arrives in ECX (param_1) and is what the original
 * reloads into EDI/EBX/ESI from _DAT_005b3484 / saved stack throughout -
 * every `param_1 + 0x2xxxx/0x3xxxx` here was Ghidra's dropped
 * unaff_EDI/EBX/EBP. The blit/text calls drop register operands the raw
 * decompile can't see:
 *   - BlitRLESprite(x,y,color,rle): x=ECX and rle=EAX were dropped (only
 *     y,color are stack args). Recovered per call; several x's are the
 *     centered-text form 0x19b - 6*strlen(text).
 *   - DrawFontString(x,y,color): x=ECX dropped, text=EAX dropped (it is a
 *     bring-up no-op anyway, see DrawFontString.c).
 *   - FindSpriteFrame(container,outerKey,innerKey) and
 *     BlitSprite16bpp(gate,x,y,outerKey)/BlitSpriteClipped(gate,x,y,
 *     outerKey) all have REAL ported prototypes now (see DrawSprite.c) -
 *     they MUST be passed their full args, not left verbatim: container
 *     is always (int)&g_spriteRegistry, outerKey/innerKey come from the block's
 *     EDX/ESI, gate from EAX (or the item index the sprite-list walk
 *     matched), and x/y from the two stack pushes (1st push = y, 2nd = x).
 *     Leaving them argless crashed live (page fault in FindSpriteFrame
 *     dereferencing a garbage container) the moment the g_screenSurface
 *     sprite gate was non-zero, which it is on the store screen. Recovered
 *     per block from the 0x448440-0x44904f disassembly.
 *   - PeekPacketChecksumState() is the guarded-value stub that returns 0
 *     (its EAX cell arg is ignored) - so the label values read 0 and the
 *     large iVar-dispatched category-tab region below is skipped in this
 *     build; it is ported faithfully for when that stub is replaced.
 * The two avatar-frame composites' source frame key rides in EAX
 * (*(param_1+0x30bec), `mov eax,[ebx+0x30bec]` at orig 0x4487eb/0x4487fd)
 * - recovered as BlitAvatarFrameToPreviewTexture's explicit 5th
 * parameter (2026-08-09, was FUN_0044b5d0's dropped in_EAX; see that
 * file's header).
 *
 * Not hand-verified beyond the above. See src/README.md's "Raw/verbatim
 * ports" section.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 7 argless PeekPacketChecksumState() calls, in address order.
 * The first six are the same six header/banner counters CState03's
 * RenderRoomLabel reads, off g_clientContext (EDI is loaded from
 * [0x5b3484] at 0x448491 and is still live at 0x44850a): + 0x239b4 (C106),
 * + 0x23790 (C109), + 0x23348 (C117), + 0x39ae8 (C126), + 0x396a0 (C135)
 * and + 0x398c4 (C142).  C189 (0x44884b) is `lea eax,[edi + 0x325b0]` with
 * EDI reloaded from [esp + 0x10]; that slot is where the prologue spilled
 * ECX at 0x44844f (as [esp + 8], before the later push ebx / push ebp), so
 * it is the __fastcall `this` -- param_1 + 0x325b0.  Same cell FUN_0050a1b0
 * reads off g_gameStateVTableArray[7], which is this very object.
 */
#include "ghidra_types.h"
#include <windows.h>
#include <ddraw.h>

/* IDirectDrawSurface7::Lock (vtbl+0x64) / Unlock (vtbl+0x80) - __stdcall
 * COM methods, same explicit-typedef idiom as LockBackBuffer.c. */
typedef HRESULT (WINAPI *SurfaceLockFn)(void *, LPRECT, LPDDSURFACEDESC2, DWORD, HANDLE);
typedef HRESULT (WINAPI *SurfaceUnlockFn)(void *, LPRECT);


void __fastcall State07_AvatarStore_RenderStoreContent(int param_1)

{
  int iVar4;
  int iVar5;
  uint uVar3;
  uint uVar9;
  undefined4 uVar6;
  undefined4 uVar7;
  char *pcVar8;
  char cVar11;
  int *piSurface;
  char *pcBits;
  uint uPitch;
  int iCache;
  int idx;
  int iy;
  bool bVar15;
  char acStack_fc[128];
  DDSURFACEDESC2 ddsd;

  /* --- store background (key 0x2710) --- */
  if ((g_screenSurface != 0) &&
     (iVar4 = FindSpriteFrame((int)&g_spriteRegistry,0x2710,0), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(0,0,0,0x2710);
    }
    else {
      BlitSpriteClipped(0,0,0,0x2710);
    }
  }
  /* --- window frame (key 0x64), gate/innerKey = *(short*)(this+0x23344) --- */
  uVar6 = *(ushort *)(param_1 + 0x23344);
  if (((g_screenSurface != 0) && (0 <= (short)*(ushort *)(param_1 + 0x23344))) &&
     (iVar5 = FindSpriteFrame((int)&g_spriteRegistry,0x64,uVar6), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar6,0xac,9,0x64);
    }
    else {
      BlitSpriteClipped(uVar6,0xac,9,0x64);
    }
  }

  /* --- guard/checksum debug labels (only when the +0x23313 flag set) --- */
  if (*(char *)(param_1 + 0x23313) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x239b4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0x23790));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(acStack_fc,s__s__3d__3d__005536b8,param_1 + 0x23313,uVar7,uVar6);
    BlitRLESprite(0xbe,9,0xfd0f,(byte *)acStack_fc);
  }
  BlitRLESprite(0xbe,0x17,0xffff,(byte *)(param_1 + 0x23330));

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x23348));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x4e20);
  _sprintf(acStack_fc,pcVar8,uVar6);
  for (pcVar8 = acStack_fc; *pcVar8 != '\0'; pcVar8 = pcVar8 + 1) {
  }
  BlitRLESprite(0x19b - (int)(pcVar8 - acStack_fc) * 6,9,0xffff,(byte *)acStack_fc);

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x39ae8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x4e21);
  _sprintf(acStack_fc,pcVar8,uVar6);
  for (pcVar8 = acStack_fc; *pcVar8 != '\0'; pcVar8 = pcVar8 + 1) {
  }
  BlitRLESprite(0x19b - (int)(pcVar8 - acStack_fc) * 6,0x16,0xffff,(byte *)acStack_fc);

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x396a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x4e22);
  _sprintf(acStack_fc,pcVar8,uVar6);
  BlitRLESprite(0xad,0x27,0x1f3b,(byte *)acStack_fc);

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x398c4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x4e23);
  _sprintf(acStack_fc,pcVar8,uVar6);
  for (pcVar8 = acStack_fc; *pcVar8 != '\0'; pcVar8 = pcVar8 + 1) {
  }
  BlitRLESprite(0x19b - (int)(pcVar8 - acStack_fc) * 6,0x27,0xe703,(byte *)acStack_fc);

  /* --- 9-cell item grid --- */
  idx = 0;
  do {
    if (*(int *)(param_1 + 0x2d110) <= idx + *(int *)(param_1 + 0x450) * 9) break;
    FUN_0044a000(param_1,idx);
    idx = idx + 1;
  } while (idx < 9);

  /* --- avatar-preview off-screen composite --- */
  iCache = FindTextureCacheEntryByName(s_AvataTexture1_0055565c);
  if (iCache != 0) {
    piSurface = *(int **)(*(int *)(iCache + 0x94) + 0x110);
    memset(&ddsd,0,0x7c);
    ddsd.dwSize = 0x7c;
    (*(SurfaceLockFn *)(*piSurface + 0x64))(piSurface,(LPRECT)0x0,&ddsd,0,(HANDLE)0x0);
    pcBits = (char *)ddsd.lpSurface;
    uPitch = ddsd.lPitch;
    /* clear the surface: 0x100 rows of uPitch bytes */
    {
      char *pRow = pcBits;
      for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
        memset(pRow,0,uPitch);
        pRow = pRow + uPitch;
      }
    }
    /* two body-part composites (frame key rides in EAX = *(param_1+0x30bec);
     * see KNOWN LIMITATION in the header). */
    BlitAvatarFrameToPreviewTexture(0,0x30d40,(int)pcBits,uPitch,
                                    *(uint *)(param_1 + 0x30bec));
    BlitAvatarFrameToPreviewTexture(0,0x493e0,(int)pcBits + (uPitch >> 1),uPitch,
                                    *(uint *)(param_1 + 0x30bec));
    piSurface = *(int **)(*(int *)(iCache + 0x94) + 0x110);
    (*(SurfaceUnlockFn *)(*piSurface + 0x80))(piSurface,(LPRECT)0x0);
  }

  /* --- item-detail / category dispatch (PeekPacketChecksumState-gated;
   *     the stub returns 0 so iVar4==0 falls straight through to the tab
   *     block below in this build) --- */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x325b0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar4 != 0) {
    if (iVar4 == 1) {
      if (g_screenSurface != 0) {
        iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar9 = *(uint *)(iVar4 + 4);
        while (uVar9 < 0x2715) {
          if (uVar9 == 0x2714) {
            iVar4 = *(int *)(iVar4 + 0x10);
            uVar9 = *(uint *)(iVar4 + 8);
            if (uVar9 < 8) goto LAB_00448970;
            break;
          }
          iVar4 = *(int *)(iVar4 + 0x1c);
          uVar9 = *(uint *)(iVar4 + 4);
        }
      }
      goto LAB_004489b7;
    }
    if (g_screenSurface != 0) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar9 = *(uint *)(iVar4 + 4);
      while (uVar9 < 0x2715) {
        if (uVar9 == 0x2714) {
          iVar4 = *(int *)(iVar4 + 0x10);
          bVar15 = true;
          if (*(int *)(iVar4 + 8) == 0) goto LAB_004488a3;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar9 = *(uint *)(iVar4 + 4);
      }
    }
    goto LAB_004488e3;
  }
  goto LAB_00448ab0;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar9 = *(uint *)(iVar4 + 8);
    if (7 < uVar9) break;
LAB_00448970:
    if (uVar9 == 7) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(7,0x8b,0x9c,0x2714);
      }
      else {
        BlitSpriteClipped(7,0x8b,0x9c,0x2714);
      }
      break;
    }
  }
LAB_004489b7:
  uVar9 = *(int *)(param_1 + 0x34788) + 20000;
  if (g_screenSurface != 0) {
    iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar3 = *(uint *)(iVar4 + 4);
    while (uVar3 <= uVar9) {
      if (uVar3 == uVar9) {
        iVar4 = *(int *)(iVar4 + 0x10);
        bVar15 = true;
        if (*(int *)(iVar4 + 8) == 0) goto LAB_004489f7;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar3 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_00448a35;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    bVar15 = *(int *)(iVar4 + 8) == 0;
    if (!bVar15) break;
LAB_004489f7:
    if (bVar15) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(0,0xd1,0xf4,uVar9);
      }
      else {
        BlitSpriteClipped(0,0xd1,0xf4,uVar9);
      }
      break;
    }
  }
LAB_00448a35:
  BlitRLESprite(0xa3,0xab,0xffff,(byte *)(param_1 + 0x327d4));
  iy = 0xd0;
  idx = 0;
  do {
    uVar6 = 0xffff;
    if (idx == 2) {
      uVar6 = 0x1f3b;
    }
    else if (idx == 3) {
      uVar6 = 0xe703;
    }
    BlitRLESprite((idx < 5) ? 0x105 : 0xaf,iy,uVar6,
                  (byte *)(param_1 + idx * 0x80 + 0x32854));
    iy = iy + 0xe;
    idx = idx + 1;
  } while (idx < 8);
  goto LAB_00448ab0;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar9 = *(uint *)(iVar4 + 8);
    if (3 < uVar9) break;
LAB_00448b43:
    if (uVar9 == 3) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(3,0x7a,0xc1,0x2714);
      }
      else {
        BlitSpriteClipped(3,0x7a,0xc1,0x2714);
      }
      break;
    }
  }
  goto LAB_00448b87;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar3 = *(uint *)(iVar4 + 8);
    if (uVar9 < uVar3) break;
LAB_00448bcf:
    if (uVar3 == uVar9) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar9,0xee,0xec,0x2713);
      }
      else {
        BlitSpriteClipped(uVar9,0xee,0xec,0x2713);
      }
      break;
    }
  }
  goto LAB_00448c0f;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar3 = *(uint *)(iVar4 + 8);
    if (uVar9 < uVar3) break;
LAB_00448c89:
    if (uVar3 == uVar9) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar9,0x182,0xec,0x2714);
      }
      else {
        BlitSpriteClipped(uVar9,0x182,0xec,0x2714);
      }
      break;
    }
  }
  goto LAB_00448cc9;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    bVar15 = *(int *)(iVar4 + 8) == 0;
    if (!bVar15) break;
LAB_00448d01:
    if (bVar15) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(0,0xbc,0x11b,0x7530);
      }
      else {
        BlitSpriteClipped(0,0xbc,0x11b,0x7530);
      }
      break;
    }
  }
  goto LAB_00448d4a;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar9 = *(uint *)(iVar4 + 8);
    if (4 < uVar9) break;
LAB_00448ddf:
    if (uVar9 == 4) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(4,0x7a,0xc1,0x2714);
      }
      else {
        BlitSpriteClipped(4,0x7a,0xc1,0x2714);
      }
      break;
    }
  }
  goto LAB_00448e23;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar3 = *(uint *)(iVar4 + 8);
    if (uVar9 < uVar3) break;
LAB_00448e67:
    if (uVar3 == uVar9) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar9,0xee,0xec,0x2713);
      }
      else {
        BlitSpriteClipped(uVar9,0xee,0xec,0x2713);
      }
      break;
    }
  }
  goto LAB_00448ea7;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar3 = *(uint *)(iVar4 + 8);
    if (uVar9 < uVar3) break;
LAB_00448f3b:
    if (uVar3 == uVar9) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar9,0x182,0xec,0x2714);
      }
      else {
        BlitSpriteClipped(uVar9,0x182,0xec,0x2714);
      }
      break;
    }
  }
  goto LAB_00448f7b;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    bVar15 = *(int *)(iVar4 + 8) == 0;
    if (!bVar15) break;
LAB_00448fb3:
    if (bVar15) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(0,0xbc,0x11b,0x9c40);
      }
      else {
        BlitSpriteClipped(0,0xbc,0x11b,0x9c40);
      }
      break;
    }
  }
  goto LAB_00448ff6;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    bVar15 = *(int *)(iVar4 + 8) == 0;
    if (!bVar15) break;
LAB_004488a3:
    if (bVar15) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(0,0x7a,0xc1,0x2714);
      }
      else {
        BlitSpriteClipped(0,0x7a,0xc1,0x2714);
      }
      break;
    }
  }
LAB_004488e3:
  BlitRLESprite(0xa2,0xcf,0xffff,(byte *)(param_1 + 0x327d4));
  idx = 0xf1;
  iCache = param_1 + 0x32854;
  do {
    BlitRLESprite(0x94,idx,0xffff,(byte *)iCache);
    idx = idx + 0xe;
    iCache = iCache + 0x80;
  } while (idx < 0x145);
LAB_00448ab0:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)(*(byte *)(param_1 + 0x32c54) + *(byte *)(param_1 + 0x32c55) + -0x34) ==
      *(char *)(param_1 + 0x32c56)) {
    cVar11 = '\x01' - ((*(byte *)(param_1 + 0x32c55) >> (*(byte *)(param_1 + 0x32c54) & 7) & 1)
                      != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar11 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (cVar11 != '\0') {
    if (g_screenSurface != 0) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar9 = *(uint *)(iVar4 + 4);
      while (uVar9 < 0x2715) {
        if (uVar9 == 0x2714) {
          iVar4 = *(int *)(iVar4 + 0x10);
          uVar9 = *(uint *)(iVar4 + 8);
          if (uVar9 < 4) goto LAB_00448b43;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar9 = *(uint *)(iVar4 + 4);
      }
    }
LAB_00448b87:
    uVar9 = *(uint *)(param_1 + 0x32c58);
    if ((g_screenSurface != 0) && (-1 < (int)uVar9)) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar3 = *(uint *)(iVar4 + 4);
      while (uVar3 < 0x2714) {
        if (uVar3 == 0x2713) {
          iVar4 = *(int *)(iVar4 + 0x10);
          uVar3 = *(uint *)(iVar4 + 8);
          if (uVar3 <= uVar9) goto LAB_00448bcf;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar3 = *(uint *)(iVar4 + 4);
      }
    }
LAB_00448c0f:
    DrawFontString(0x104,0xec,0);
    BlitRLESprite(0x104,0xec,0xffff,(byte *)(param_1 + 0x32c5c));
    uVar9 = *(uint *)(param_1 + 0x32cdc);
    if (g_screenSurface != 0) {
      if (-1 < (int)uVar9) {
        iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar3 = *(uint *)(iVar4 + 4);
        while (uVar3 < 0x2715) {
          if (uVar3 == 0x2714) {
            iVar4 = *(int *)(iVar4 + 0x10);
            uVar3 = *(uint *)(iVar4 + 8);
            if (uVar3 <= uVar9) goto LAB_00448c89;
            break;
          }
          iVar4 = *(int *)(iVar4 + 0x1c);
          uVar3 = *(uint *)(iVar4 + 4);
        }
      }
LAB_00448cc9:
      if (g_screenSurface != 0) {
        iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar9 = *(uint *)(iVar4 + 4);
        while (uVar9 < 0x7531) {
          if (uVar9 == 30000) {
            iVar4 = *(int *)(iVar4 + 0x10);
            bVar15 = true;
            if (*(int *)(iVar4 + 8) == 0) goto LAB_00448d01;
            break;
          }
          iVar4 = *(int *)(iVar4 + 0x1c);
          uVar9 = *(uint *)(iVar4 + 4);
        }
      }
    }
  }
LAB_00448d4a:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)(*(byte *)(param_1 + 0x32e63) + *(byte *)(param_1 + 0x32e64) + -0x34) ==
      *(char *)(param_1 + 0x32e65)) {
    cVar11 = '\x01' - ((*(byte *)(param_1 + 0x32e64) >> (*(byte *)(param_1 + 0x32e63) & 7) & 1)
                      != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar11 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (cVar11 != '\0') {
    if (g_screenSurface != 0) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar9 = *(uint *)(iVar4 + 4);
      while (uVar9 < 0x2715) {
        if (uVar9 == 0x2714) {
          iVar4 = *(int *)(iVar4 + 0x10);
          uVar9 = *(uint *)(iVar4 + 8);
          if (uVar9 < 5) goto LAB_00448ddf;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar9 = *(uint *)(iVar4 + 4);
      }
    }
LAB_00448e23:
    uVar9 = *(uint *)(param_1 + 0x32e68);
    if ((g_screenSurface != 0) && (-1 < (int)uVar9)) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar3 = *(uint *)(iVar4 + 4);
      while (uVar3 < 0x2714) {
        if (uVar3 == 0x2713) {
          iVar4 = *(int *)(iVar4 + 0x10);
          uVar3 = *(uint *)(iVar4 + 8);
          if (uVar3 <= uVar9) goto LAB_00448e67;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar3 = *(uint *)(iVar4 + 4);
      }
    }
LAB_00448ea7:
    DrawFontString(0x104,0xec,0);
    BlitRLESprite(0x104,0xec,0xffff,(byte *)(param_1 + 0x32e6c));
    BlitRLESprite(0x129,0x104,0xffff,(byte *)(param_1 + 0x32ef0));
    uVar9 = *(uint *)(param_1 + 0x32eec);
    if (g_screenSurface != 0) {
      if (-1 < (int)uVar9) {
        iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar3 = *(uint *)(iVar4 + 4);
        while (uVar3 < 0x2715) {
          if (uVar3 == 0x2714) {
            iVar4 = *(int *)(iVar4 + 0x10);
            uVar3 = *(uint *)(iVar4 + 8);
            if (uVar3 <= uVar9) goto LAB_00448f3b;
            break;
          }
          iVar4 = *(int *)(iVar4 + 0x1c);
          uVar3 = *(uint *)(iVar4 + 4);
        }
      }
LAB_00448f7b:
      if (g_screenSurface != 0) {
        iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar9 = *(uint *)(iVar4 + 4);
        while (uVar9 < 0x9c41) {
          if (uVar9 == 40000) {
            iVar4 = *(int *)(iVar4 + 0x10);
            bVar15 = true;
            if (*(int *)(iVar4 + 8) == 0) goto LAB_00448fb3;
            break;
          }
          iVar4 = *(int *)(iVar4 + 0x1c);
          uVar9 = *(uint *)(iVar4 + 4);
        }
      }
    }
LAB_00448ff6:
    BlitRLESprite(0x156,0x11a,0x29a9,(byte *)(param_1 + 0x32f10));
    BlitRLESprite(0xf2,0x12b,0xffff,(byte *)(param_1 + 0x32f30));
    BlitRLESprite(0xe8,0x137,0xffff,(byte *)(param_1 + 0x32f50));
  }
  return;
}
