/* FUN_0040c6f0 - 0x0040c6f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* FIXED (2026-07-20): a WNDPROC installed via SetWindowLongA(GWL_WNDPROC);
 * __stdcall, confirmed by `ret 0x10` at every return in the original.
 * Ghidra emitted __cdecl, and the install site passed the literal
 * original-binary address instead of this symbol. Same bug class as
 * FUN_004fecb0.
 *
 * SPLIT-STACK-BUFFER FIX (2026-07-29): `local_88` (1 byte) and `local_87`
 * (4 bytes) are Ghidra's fragmentary view of ONE contiguous 0x7f-byte IME
 * composition-string buffer - the same split-struct bug class as the SHA-1
 * context (see session notes: "when `&local_XXX` is passed as a context,
 * subtract the Ghidra local names - if they form a struct, coalesce"). The
 * zeroing loop below writes 0x1f*4+2 = 126 bytes starting one byte past
 * `local_88`, and `ImmGetCompositionStringA` is then told the buffer at
 * `&local_88` is dwBufLen=0x7f (127) bytes long - together they cover
 * exactly a 127-byte region from `local_88`'s address. Left split, MSVC
 * allocates `local_88`/`local_87` as two tiny, non-contiguous stack slots
 * (5 bytes total), so both the zeroing loop and (far worse)
 * ImmGetCompositionStringA's real write - which runs on EVERY WM_KEYDOWN/
 * WM_CHAR/WM_IME_* this subclassed edit control receives, i.e. on ordinary
 * typing, IME composition or not - blow straight through this function's
 * own frame into whatever called it, smashing the saved return address.
 * This was the crash reproduced live: press any key while the lobby's
 * chat edit box has real Win32 focus (it's SetFocus'd once at InitGame and
 * nothing takes focus back), and the game dies ~1s later on an unrelated
 * function's `ret` - the classic delayed stack-smash signature (EIP lands
 * on raw stack bytes at a constant ESP-relative offset). Coalesced into a
 * single properly-sized buffer; the emptiness check against `&local_87`
 * becomes the equivalent `imeCompBuf+1`. */
LRESULT __stdcall FUN_0040c6f0(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  char cVar1;
  HIMC pHVar2;
  LONG LVar3;
  char *pcVar4;
  BOOL BVar5;
  LRESULT LVar6;
  int iVar7;
  undefined4 *puVar8;
  DWORD DVar9;
  DWORD dwBufLen;
  char imeCompBuf[0x80];

  imeCompBuf[0] = '\0';
  puVar8 = (undefined4 *)(imeCompBuf + 1);
  for (iVar7 = 0x1f; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  *(undefined2 *)puVar8 = 0;
  dwBufLen = 0x7f;
  *(undefined1 *)((int)puVar8 + 2) = 0;
  pcVar4 = imeCompBuf;
  DVar9 = 8;
  pHVar2 = ImmGetContext(param_1);
  LVar3 = ImmGetCompositionStringA(pHVar2,DVar9,pcVar4,dwBufLen);
  if (LVar3 == -1) {
    DAT_007934c4 = false;
  }
  else {
    pcVar4 = imeCompBuf;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    DAT_007934c4 = pcVar4 != (char *)(imeCompBuf + 1);
  }
  pHVar2 = ImmGetContext(param_1);
  BVar5 = ImmGetOpenStatus(pHVar2);
  DAT_007934c5 = BVar5 != 0;
  if (param_2 < 0x106) {
    if (param_2 < 0x104) {
      if (param_2 == 0x7b) {
        return 0;
      }
      if ((param_2 < 0x100) || (0x101 < param_2)) goto LAB_0040c7ad;
    }
    SendMessageA((HWND)*DAT_005b1c48,param_2,param_3,param_4);
  }
LAB_0040c7ad:
  if (*(char *)(DAT_005b1c48 + 2) == '\0') {
    switch(param_2) {
    case 0x100:
    case 0x102:
    case 0x104:
    case 0x105:
      return 1;
    }
  }
  else {
    switch(param_2 - 0x100) {
    case 0:
      if ((((param_3 == 9) || (param_3 == 0x26)) || (param_3 == 0x28)) || (param_3 == 0xd)) {
        return 1;
      }
      break;
    case 2:
    case 4:
    case 5:
      if (param_3 == 0xd) {
        return 1;
      }
      if (param_3 == 9) {
        return 1;
      }
    default:
      LVar6 = CallWindowProcA((WNDPROC)DAT_005b1c48[3],(HWND)DAT_005b1c48[1],param_2,param_3,param_4
                             );
      return LVar6;
    }
  }
  LVar6 = CallWindowProcA((WNDPROC)DAT_005b1c48[3],(HWND)DAT_005b1c48[1],param_2,param_3,param_4);
  return LVar6;
}

