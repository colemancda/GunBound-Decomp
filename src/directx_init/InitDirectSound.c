/* InitDirectSound - 0x004ee5b0 in the original binary.
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
#include <mmsystem.h>
#include <dsound.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* Every raw vtable call below is dispatched through an explicit __stdcall
 * function-pointer cast, not the generic `code` (K&R/unspecified-args) type.
 * `code()` defaults to __cdecl under MSVC, so the compiler emits a caller-
 * side `add esp, N` after some of these calls to pop args it pushed itself -
 * but every one is a real COM vtable method (__stdcall, already self-cleans
 * via `ret N`). That double cleanup corrupts the caller's frame once enough
 * such calls accumulate - see SetupZBuffer.c/InitDirectDraw.c for the full
 * writeup and how this was found (a hardware watchpoint on the saved-EBP
 * stack slot, firing from inside a DirectX DLL). */
typedef HRESULT (WINAPI *SetCooperativeLevelFn)(void *, HWND, DWORD);
typedef HRESULT (WINAPI *CreateSoundBufferFn)(void *, const DSBUFFERDESC *, void **, IUnknown *);
typedef HRESULT (WINAPI *SetFormatFn)(void *, const WAVEFORMATEX *);
typedef HRESULT (WINAPI *PlayFn)(void *, DWORD, DWORD, DWORD);
#define VTBL(iface, n) (*(void ***)(iface))[n]

undefined4 InitDirectSound(undefined4 param_1,uint param_2,undefined4 param_3)

{
  FARPROC pFVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint uVar5;
  /* Real DSBUFFERDESC/WAVEFORMATEX structs. Ghidra scattered the primary
   * buffer's DSBUFFERDESC across a raw, never-written stack slot
   * (`stack0xffffffc4`) instead of recognizing the zero-fill + dwSize/
   * dwFlags writes at orig 0x4ee651-0x4ee690 as one struct - the port was
   * calling CreateSoundBuffer with uninitialized stack instead of
   * {dwSize=sizeof(DSBUFFERDESC), dwFlags=DSBCAPS_PRIMARYBUFFER|
   * DSBCAPS_CTRLVOLUME}. The secondary-buffer DSBUFFERDESC (orig
   * 0x4ee79c-0x4ee81b, per-iteration dwFlags only) was similarly only
   * partially named (uStack_64..uStack_54 covered just 0x14 of the
   * required 0x24 bytes), leaving dwReserved/guid3DAlgorithm unzeroed.
   * The WAVEFORMATEX (orig 0x4ee69b-0x4ee6f9) was already correctly
   * recognized as one contiguous struct by Ghidra (uStack_60/iStack_5c/
   * iStack_58/uStack_54 via puStack_74); rebuilt here as a typed struct
   * to match, with field values unchanged. */
  DSBUFFERDESC primaryDesc;
  DSBUFFERDESC secondaryDesc;
  WAVEFORMATEX waveFmt;

  DAT_007935e8 = LoadLibraryA(s_dsound_dll_005574c0);
  if (DAT_007935e8 == (HMODULE)0x0) {
    return 0;
  }
  pFVar1 = GetProcAddress(DAT_007935e8,s_DirectSoundCreate8_005574ac);
  DAT_0079355c = param_1;
  /* original: ESI=sound-archive singleton (0xea0f50), path in ECX
   * (=param_1), writeFlag 1, param_3 0. Bring-up routes it through the
   * shared scratch archive. */
  OpenXFSArchive(&g_xfsScratch,(LPCSTR)param_1,1,0);
  DAT_00793560 = 0x1f;
  if (param_2 < 0x20) {
    DAT_00793560 = param_2;
  }
  /* DirectSoundCreate8(pcGuidDevice=NULL, ppDS8=&DAT_0079354c, pUnkOuter=NULL).
   * Ghidra emitted this as an argless `(*pFVar1)()`; the real argument push
   * order was recovered from the original at 0x4ee619-0x4ee622 (push NULL /
   * &DAT_0079354c / NULL). Without the args, DAT_0079354c never gets a valid
   * IDirectSound8 pointer written into it, and the very next line's vtable
   * dereference (*DAT_0079354c) reads NULL/garbage and calls through it. */
  iVar2 = ((HRESULT (WINAPI *)(GUID *, void **, IUnknown *))pFVar1)
              (NULL, (void **)&DAT_0079354c, NULL);
  if (-1 < iVar2) {
    iVar2 = ((SetCooperativeLevelFn)VTBL(DAT_0079354c, 6))
                (DAT_0079354c, (HWND)DAT_0079355c, 2);
    if (-1 < iVar2) {
      /* Primary buffer: DSBUFFERDESC{dwSize=sizeof, dwFlags=
       * DSBCAPS_PRIMARYBUFFER|DSBCAPS_CTRLVOLUME=0x81}, rest zeroed.
       * Recovered from the zero-fill + two field writes at orig
       * 0x4ee651-0x4ee690, immediately before the `call [ecx+0xc]`
       * (CreateSoundBuffer, vtbl slot 3) at 0x4ee694. */
      ZeroMemory(&primaryDesc, sizeof(primaryDesc));
      primaryDesc.dwSize = sizeof(primaryDesc);
      primaryDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
      iVar2 = ((CreateSoundBufferFn)VTBL(DAT_0079354c, 3))
                  (DAT_0079354c, &primaryDesc, (void **)&DAT_00793550, 0);
      if (-1 < iVar2) {
        /* WAVEFORMATEX for the primary buffer's SetFormat (vtbl slot 0xe).
         * Ghidra already recognized uStack_60/iStack_5c/iStack_58/uStack_54
         * as one contiguous struct (via puStack_74 = &uStack_60); rebuilt
         * as a typed WAVEFORMATEX with the same field values, recovered
         * from orig 0x4ee69b-0x4ee6f9. */
        waveFmt.wFormatTag = WAVE_FORMAT_PCM;
        waveFmt.nChannels = (short)_DAT_00588f38;
        waveFmt.nSamplesPerSec = DAT_00588f3c;
        waveFmt.nAvgBytesPerSec = DAT_00588f44;
        waveFmt.nBlockAlign = (DAT_00588f40 >> 3) * (short)_DAT_00588f38;
        waveFmt.wBitsPerSample = DAT_00588f40;
        waveFmt.cbSize = 0;
        ((SetFormatFn)VTBL(DAT_00793550, 0xe))(DAT_00793550, &waveFmt);
        ((PlayFn)VTBL(DAT_00793550, 0xc))(DAT_00793550,0,0,1);
        DAT_00793554 = operator_new(DAT_00793560 * 4);
        DAT_00793558 = operator_new(DAT_00793560 * 4);
        pvVar3 = operator_new(0xb8);
        if (pvVar3 == (void *)0x0) {
          uVar4 = 0;
        }
        else {
          uVar4 = FUN_004eebe0();
        }
        *DAT_00793554 = uVar4;
        uVar5 = 1;
        if (1 < DAT_00793560) {
          do {
            pvVar3 = operator_new(0x50);
            if (pvVar3 == (void *)0x0) {
              uVar4 = 0;
            }
            else {
              uVar4 = FUN_004ef3a0();
            }
            DAT_00793554[uVar5] = uVar4;
            uVar5 = uVar5 + 1;
          } while (uVar5 < DAT_00793560);
        }
        /* Secondary (per-channel) buffers: DSBUFFERDESC{dwSize=sizeof,
         * dwBufferBytes=2*DAT_00588f44, lpwfxFormat=&waveFmt}, dwFlags set
         * per-iteration below. Ghidra only named 5 of the struct's 9 dwords
         * (uStack_64..uStack_54, 0x14 of the required 0x24 bytes), leaving
         * dwReserved/guid3DAlgorithm unzeroed; recovered as one full struct
         * from the zero-fill + field writes at orig 0x4ee7a4-0x4ee81b. */
        ZeroMemory(&secondaryDesc, sizeof(secondaryDesc));
        secondaryDesc.dwSize = sizeof(secondaryDesc);
        secondaryDesc.dwBufferBytes = DAT_00588f44 * 2;
        secondaryDesc.lpwfxFormat = &waveFmt;
        uVar5 = 0;
        if (DAT_00793560 != 0) {
          do {
            secondaryDesc.dwFlags = (-(uint)(uVar5 != 0) & 0xffffffe0) + 0x1a2;
            ((CreateSoundBufferFn)VTBL(DAT_0079354c, 3))
                      (DAT_0079354c,&secondaryDesc,(void **)((int)DAT_00793558 + uVar5 * 4),0);
            uVar5 = uVar5 + 1;
          } while (uVar5 < DAT_00793560);
        }
        DAT_00793549 = 1;
        DAT_0079354b = 1;
        DAT_0079354a = 1;
        return 1;
      }
    }
  }
  return 0;
}

