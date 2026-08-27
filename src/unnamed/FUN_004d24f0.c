/* FUN_004d24f0 - 0x004d24f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
*
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EDI is the CONNECTION
 * CONTEXT.  The body reads `*(int *)(unaff_EDI + 0x84e0)` -- the connection
 * object pointer this tree already documents at that offset -- then marks it
 * +0x22c = 1, closesocket()s its +0x24 handle and clears +0x22a, i.e. it tears
 * down whichever connection the context owns.
 *
 * Each of the four callers holds exactly one site, so nothing rests on
 * ordering, and three of them load the value straight from an already-named
 * global: `mov edi,[0x7934e8]` = g_connectionContextA at 0x4e0b87, and
 * `mov edi,[0x7934ec]` = g_connectionContextB at 0x4e138f and 0x4e1aac.
 * These are LOADS, not addresses -- the globals are declared uint32_t and the
 * surrounding code already uses their VALUE as a base
 * (`g_connectionContextB + 0x4d4`), so the value is what gets passed.
 *
 * ProcessIncomingPackets passes its own param_1.  Its frame: the SEH triple
 * (12) plus a 0x24dc __chkstk puts esp at E-0x24e8, and four register saves
 * at 0x4d2836-0x4d2839 take it to E-0x24f8, so the site's [esp+0x24fc] is
 * E+4.  Cross-checked against that function's own prologue, where
 * [esp+0x24ec] before any save is the same E+4 and is immediately used as
 * `[ecx + 0x84e4]` / `[ecx + 0x84e0]` -- the very fields this callee reads.
 */
#include "ghidra_types.h"


void FUN_004d24f0(int regEdi)

{
  int iVar1;
  int unaff_EDI = regEdi;
  
  iVar1 = *(int *)(unaff_EDI + 0x84e0);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x22c) = 1;
    if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
      closesocket(*(SOCKET *)(iVar1 + 0x24));
    }
    *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
    *(undefined1 *)(iVar1 + 0x22a) = 0;
    *(undefined1 *)(unaff_EDI + 0x84e5) = 0;
  }
  return;
}

