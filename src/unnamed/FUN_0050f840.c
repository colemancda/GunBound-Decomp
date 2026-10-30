/* FUN_0050f840 - 0x0050f840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * PARENT DISPATCH CONVENTION FIXED (2026-10-30): the change report is
 * `mov ecx,[edx+8]` (0x50f867, the scrollbar's parent), `mov esi,[ecx]`,
 * push pos, m_id, 0x2000, `call [esi+0x1c]` (0x50f87d): the parent's slot 7,
 * OnCommand, with the parent in ECX. The parent is a C++ panel
 * (AvatarStorePanel_Draw steps its id-0 scrollbar through here), whose
 * OnCommand is __thiscall and pops its 0xc bytes. The raw `code *` call
 * compiled as cdecl, so ECX was not the parent and the arguments were
 * popped twice. It now uses the __fastcall + dummy-EDX idiom.
 */
#include "ghidra_types.h"

typedef void (__fastcall *ParentOnCommandFn)(void *thisPtr, int dummyEDX,
                                             int evt, int id, int arg);


void __fastcall FUN_0050f840(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_2 + 0x38) - *(int *)(param_2 + 0x3c);
  param_1 = param_1 + *(int *)(param_2 + 0x40);
  iVar2 = iVar1;
  if (param_1 <= iVar1) {
    iVar2 = param_1;
  }
  if (iVar2 < 0) {
    iVar1 = 0;
  }
  else if (param_1 <= iVar1) {
    iVar1 = param_1;
  }
  if (iVar1 != *(int *)(param_2 + 0x40)) {
    *(int *)(param_2 + 0x40) = iVar1;
    if (*(int **)(param_2 + 8) != (int *)0x0) {
      ((ParentOnCommandFn)(*(void ***)*(int **)(param_2 + 8))[7])
          (*(void **)(param_2 + 8),0,0x2000,*(int *)(param_2 + 0x24),iVar1);
    }
  }
  return;
}

