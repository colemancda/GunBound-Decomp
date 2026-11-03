/* FUN_004057c0 - 0x004057c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): ECX and EAX were both dropped, and the growth policy
 * was missing.  The two binary callers set them in the calling block:
 * 0x405708 (inside AssignStringBuffer) `mov eax,ebx` / `mov ecx,ebp` =
 * (length, the CString*), and 0x40566b (CString_LoadStringFromInstance)
 * `mov eax,esi` / `mov ecx,ebp` = (WideCharToMultiByte's length, the
 * CString*).  EAX is the required capacity (`cmp edx,eax / jle` at
 * 0x4057cb: it is raised to the current length), ECX the CString (`mov
 * esi,ecx`, 0x4057c1).  Declared cdecl (string, then the EAX value as a
 * trailing parameter) - both callers are ported.  The grow arm at
 * 0x4057e6-0x405801 is geometric: edi = old alloc length, `+= 0x400` above
 * 0x400 else doubled, raised to the requirement, handed to 0x405890 in EDI
 * with ESI = the string; the port had called it with nothing.  The shared
 * arm at 0x4057d7 (`push esi / call 0x405810`) passes the string on the
 * stack and the capacity in EAX.
 */
#include "ghidra_types.h"


void FUN_004057c0(int *param_1,int regEax)

{
  int iVar1;
  int iVar2;

  iVar1 = *param_1;
  if (regEax < *(int *)(iVar1 + -0xc)) {
    regEax = *(int *)(iVar1 + -0xc);
  }
  if (1 < *(int *)(iVar1 + -4)) {
    FUN_00405810(param_1,regEax);
    return;
  }
  iVar2 = *(int *)(iVar1 + -8);
  if (iVar2 < regEax) {
    if (iVar2 < 0x401) {
      iVar2 = iVar2 + iVar2;
    }
    else {
      iVar2 = iVar2 + 0x400;
    }
    if (iVar2 < regEax) {
      iVar2 = regEax;
    }
    FUN_00405890(param_1,iVar2);
  }
  return;
}
