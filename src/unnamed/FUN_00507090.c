/* FUN_00507090 - 0x00507090 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CEditBox (vtable 0x557c84) slot 5, DispatchKey (2026-10-30). The vtable
 * word at 0x557c98 is 0x507090; CEditBox::DispatchKey in
 * src/cxx/EditBox.cpp forwards here. `push esi; mov esi,ecx` at entry and
 * `ret 4` give this in ECX and the key as the one stack argument; the
 * result is AL. Unfocused (+4 clear) returns 0 (0x50716a); every focused
 * path returns 1. With a parent and DAT_007934c4 clear it reports to
 * the parent's slot 7 (OnCommand, `call [eax+0x1c]`), with ECX = the parent
 * (0x5070d0 / 0x5070f9 / 0x50712e / 0x507154 `mov ecx,[esi+8]`), and pushes
 * 0, m_id (+0x24), evt: Escape 0x1001, Enter 0x1100, Shift+Tab 0x1101,
 * Tab 0x1102.
 *
 * PARENT DISPATCH CONVENTION FIXED: the parent is a C++ CPanel whose
 * OnCommand is __thiscall (this in ECX, callee pops 0xc). The raw `code *`
 * call compiled as cdecl. That left ECX unset and popped the three
 * arguments a second time. It now goes through the __fastcall + dummy-EDX
 * idiom, so the parent arrives in ECX and the callee does the cleanup.
 */
#include "ghidra_types.h"

typedef void (__fastcall *ParentOnCommandFn)(void *thisPtr, int dummyEDX,
                                             int evt, int id, int arg);
#define PARENT_ON_COMMAND(self, evt) \
  ((ParentOnCommandFn)(*(void ***)*(int **)((self) + 8))[7])( \
      *(void **)((self) + 8), 0, (evt), *(int *)((self) + 0x24), 0)


undefined4 __thiscall FUN_00507090(int param_1,int param_2)

{
  SHORT SVar1;
  
  if (*(char *)(param_1 + 4) == '\0') {
    return 0;
  }
  if (param_2 == 9) {
    SVar1 = GetKeyState(0x10);
    if (SVar1 < 0) {
      if ((*(int *)(param_1 + 8) != 0) && (DAT_007934c4 == '\0')) {
        PARENT_ON_COMMAND(param_1, 0x1101);
        return 1;
      }
    }
    else if ((*(int *)(param_1 + 8) != 0) && (DAT_007934c4 == '\0')) {
      PARENT_ON_COMMAND(param_1, 0x1102);
    }
  }
  else if (param_2 == 0xd) {
    if ((*(int *)(param_1 + 8) != 0) && (DAT_007934c4 == '\0')) {
      PARENT_ON_COMMAND(param_1, 0x1100);
      return 1;
    }
  }
  else if (((param_2 == 0x1b) && (*(int *)(param_1 + 8) != 0)) && (DAT_007934c4 == '\0')) {
    PARENT_ON_COMMAND(param_1, 0x1001);
    return 1;
  }
  return 1;
}

