/* ConstructStringFromText - 0x00405510 in the original binary.
 *
 * RENAMED (2026-07-30): a CStringT-style "construct one element from a
 * source" helper - allocates a table/array slot via the vtable call at
 * DAT_005b1444+0xc, then either copies `param_1` as a real C string into
 * it (via AssignStringBuffer) or, if `param_1`'s high 16 bits are zero
 * (a small integer disguised as a pointer - a Win32 resource-ID
 * sentinel), calls FUN_00401880/CString_LoadStringFromInstance instead. Confirmed live via
 * AppendWordFilterEntry's call (constructing one word-filter array
 * element per line of FourWord.txt/Sound.txt) - see that file's own
 * header. Raw/near-verbatim port of Ghidra's decompiler output
 * otherwise, not hand-verified. See src/README.md's "Raw/verbatim
 * ports" section for status.
 *
 * SEH-PROLOGUE ARTIFACT FIX (2026-07-30): same class as
 * AppendWordFilterEntry.c/WidgetChildArray_Destroy.c/FUN_00443c20.c/
 * FUN_00509780.c - `unaff_FS_OFFSET` was an uninitialised pointer the body
 * wrote through (`*unaff_FS_OFFSET = &uStack_c;`) on every call. Stripped
 * per that idiom. Reached live for the first time once AppendWordFilterEntry.c's
 * dropped-args bug was fixed (this function is AppendWordFilterEntry's own
 * `ConstructStringFromText(lineText, arraySlot)` call, constructing one CStringT-style
 * element per word parsed from FourWord.txt/Sound.txt) - the garbage
 * FS_OFFSET write was corrupting memory on every single word appended.
 *
 * AssignStringBuffer DROPPED-LENGTH FIX (2026-07-30): the length-counting
 * do-while loop below already computes what the original passes as
 * AssignStringBuffer's 3rd argument (EBX) - confirmed via objdump (orig
 * 0x405576-0x405589): `lea edx,[eax+1]; <count to NUL>; sub eax,edx` is
 * exactly this loop's shape, and its result feeds `mov ebx,eax` right
 * before the call. See AssignStringBuffer.c's own header for the wider
 * (currently unfixed elsewhere) scope of this same dropped-arg bug.
 */
#include "ghidra_types.h"


int * __thiscall ConstructStringFromText(char *param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;

  uVar4 = 0;
  iVar2 = DAT_005b1444;
  iVar2 = (**(code **)(iVar2 + 0xc))();
  *param_2 = iVar2 + 0x10;
  if (param_1 != (char *)0x0) {
    pcVar3 = param_1;
    if (((uint)param_1 & 0xffff0000) == 0) {
      iVar2 = FUN_00401880((uint)param_1 & 0xffff,0);
      if (iVar2 != 0) {
        CString_LoadStringFromInstance((HMODULE)iVar2,param_2,(uint)param_1 & 0xffff);
      }
      goto LAB_00405592;
    }
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    uVar4 = (uint)(pcVar3 - param_1) - 1;
  }
  AssignStringBuffer(param_2,param_1,uVar4);
LAB_00405592:
  return param_2;
}
