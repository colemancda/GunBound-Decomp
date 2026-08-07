/* FUN_0044fcb0 - 0x0044fcb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"

/* Slot 1 of this widget's vtable is a genuine C++ __thiscall(name) with
 * one callee-cleaned stack arg - the established __fastcall+dummy-EDX
 * idiom (same typedef as State07_AvatarStore_OnEnter's dispatch). The
 * raw port called it through the generic cdecl `code()` cast with only
 * the string, dropping `this` and unbalancing ESP by 4 per call
 * (stack-cleanup mismatch class - see InitDirectDraw.c's header). */
typedef void (__fastcall *VtableSlot1StrFn)(void *thisPtr, int dummyEDX, const char *str);

void __fastcall FUN_0044fcb0(int *param_1)

{
  int iVar1;
  
  AdvanceSpriteAnimation((int)param_1);
  if ((char)param_1[0xd] != '\0') {
    iVar1 = _rand();
    if ((iVar1 % 10 != 0) && ((char)param_1[0x232] == '\0')) {
      ((VtableSlot1StrFn)*(code **)(*param_1 + 4))
                ((void *)param_1,0,s_normal_00552230);
      return;
    }
    ((VtableSlot1StrFn)*(code **)(*param_1 + 4))
              ((void *)param_1,0,(const char *)DAT_00555b4c);
    *(undefined1 *)(param_1 + 0x232) = 0;
  }
  return;
}

