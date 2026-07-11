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
typedef HRESULT (WINAPI *CreateSoundBufferFn)(void *, const void *, void **, IUnknown *);
typedef HRESULT (WINAPI *SetFormatFn)(void *, const void *);
typedef HRESULT (WINAPI *PlayFn)(void *, DWORD, DWORD, DWORD);
#define VTBL(iface, n) (*(void ***)(iface))[n]

undefined4 InitDirectSound(undefined4 param_1,uint param_2,undefined4 param_3)

{
  FARPROC pFVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piStack_78;
  undefined4 *puStack_74;
  int *piStack_70;
  undefined1 *puStack_6c;
  int **ppiStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int iStack_5c;
  int iStack_58;
  undefined4 uStack_54;
  /* Ghidra artifact: raw stack reference the decompiler couldn't map
   * to a named local; declared so the raw port parses. */
  undefined stack0xffffffc4;

  DAT_007935e8 = LoadLibraryA(s_dsound_dll_005574c0);
  if (DAT_007935e8 == (HMODULE)0x0) {
    return 0;
  }
  uStack_54 = (int **)0x4ee5e2;
  pFVar1 = GetProcAddress(DAT_007935e8,s_DirectSoundCreate8_005574ac);
  uStack_54 = (int **)param_3;
  DAT_0079355c = param_1;
  iStack_58 = 0x4ee604;
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
    iStack_58 = 2;
    iStack_5c = DAT_0079355c;
    uStack_60 = DAT_0079354c;
    uStack_64 = 0x4ee646;
    iVar2 = ((SetCooperativeLevelFn)VTBL(DAT_0079354c, 6))
                (DAT_0079354c, (HWND)DAT_0079355c, 2);
    if (-1 < iVar2) {
      iVar2 = ((CreateSoundBufferFn)VTBL(DAT_0079354c, 3))
                  (DAT_0079354c, &stack0xffffffc4, (void **)&DAT_00793550, 0);
      if (-1 < iVar2) {
        iStack_5c = DAT_00588f3c;
        puStack_74 = &uStack_60;
        uStack_60 = (int *)CONCAT22((short)_DAT_00588f38,1);
        uStack_54 = (int **)CONCAT22(DAT_00588f40,(DAT_00588f40 >> 3) * (short)_DAT_00588f38);
        iStack_58 = DAT_00588f44;
        piStack_78 = DAT_00793550;
        ((SetFormatFn)VTBL(DAT_00793550, 0xe))(DAT_00793550, &uStack_60);
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
        iStack_58 = 0;
        iStack_5c = DAT_00588f44 * 2;
        uStack_54 = &piStack_78;
        uVar5 = 0;
        uStack_64 = 0x24;
        if (DAT_00793560 != 0) {
          do {
            uStack_60 = (int *)((-(uint)(uVar5 != 0) & 0xffffffe0) + 0x1a2);
            ((CreateSoundBufferFn)VTBL(DAT_0079354c, 3))
                      (DAT_0079354c,&uStack_64,(void **)((int)DAT_00793558 + uVar5 * 4),0);
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

