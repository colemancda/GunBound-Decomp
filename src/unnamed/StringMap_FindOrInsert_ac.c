/* StringMap_FindOrInsert_ac - 0x005000e0 in the original binary.
 *
 * NAMED (2026-10-29), LIKELY: the find-or-insert member of the 0xac-node
 * string-map instantiation, the same shape as StringMap_FindOrInsert_10
 * (0x4265c0): GetNode through StringMap_Find_ac (0x5000f5; map in EAX =
 * ESI, key in EDI); on a miss, if m_ppBins is still NULL run
 * HashMap_InitHashTable (0x50010a) and throw E_OUTOFMEMORY (0x8007000e)
 * if that fails, then CreateNode through StringMap_Insert_ac (0x50012b),
 * which constructs a default value at node+0x14 (FUN_004ff1a0).  No
 * value is written here - the caller does that - which is what separates
 * it from a SetAt such as StringMap_SetAt_1c.
 *
 * One difference from _10: this returns the NODE (EAX from the find, or
 * from the insert - nothing touches it before `ret`), not the value slot;
 * _10 returns node+4.  The one binary caller adds the value offset itself.
 * FUN_004fe8d0 asks FindP2PPeerRecord for the peer's record in the P2P
 * peer table at this+0x290 and, only when that misses, calls this on the same
 * table (`lea esi,[ebx+0x290]` at 0x4fe93b) with the copied 16-char id,
 * then `lea edi,[eax+0x14]` (0x4fe94f) and initialises the record there -
 * node+0x14 being exactly the value slot FindP2PPeerRecord hands out.
 *
 * Why LIKELY rather than certain: there is no exact ATL7 member that
 * returns the CNode* after a find-or-insert (operator[] returns the value
 * reference, which here would be node+0x14), so the name rests on the
 * observable behaviour and the _10 sibling rather than on a library
 * identity.
 *
 * RETURN VALUE RECOVERED (2026-10-29).  The port was declared void, so the
 * C caller could not see the node and FUN_004fe8d0 wrote through an
 * uninitialised `iVar5`.  In the original EAX at `ret` (0x500134) is the
 * StringMap_Find_ac result on a hit (call 0x5000f5 -> `test eax,eax; jne
 * 0x500130`, straight to `pop ebx; add esp,0xc; ret`) or the
 * StringMap_Insert_ac result on a miss (call 0x50012b falls into the same
 * epilogue); nothing between either call and `ret` writes EAX.  Now returns
 * that node; the caller does `lea edi,[eax+0x14]` at 0x4fe94f with it.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * ESI RECOVERED (2026-08-24): it is callerThis + 0x290, FUN_004fe8d0's
 * __thiscall param_1 plus a fixed offset (`lea esi,[ebx+0x290]`, EBX never
 * written after the caller's entry).
 *
 * EDI RECOVERED (2026-08-25): `lea edi,[esp+0x1a]` at 0x4fe941, no push
 * pending; the caller's frame is 0xc8 (SEH 12 + sub esp,0xac + four saves),
 * so 0x1a - 0xc8 = -0xae: the ADDRESS of its `char local_ae [17]`, which the
 * next instruction NUL-terminates (`mov [esp+ecx+0x1a],0`).  It is the name
 * buffer StringMap_Find_ac parses, so the type is char *, not undefined4.
 */
#include "ghidra_types.h"


int StringMap_FindOrInsert_ac(int *regEsi,char *regEdi)

{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = (int)StringMap_Find_ac(regEdi,(uint *)&local_c,(undefined4 *)local_4,regEsi,(uint *)&local_8);
  if (iVar2 == 0) {
    if (*regEsi == 0) {
      cVar1 = HashMap_InitHashTable(regEsi,regEsi[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = (int)StringMap_Insert_ac(local_8,local_c,(undefined4 *)regEdi,regEsi);
  }
  return iVar2;
}

