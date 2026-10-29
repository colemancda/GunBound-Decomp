/* StringMap_RemoveKey_1c - 0x004fe500 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::RemoveKey(key) for the 0x1c-node
 * string-keyed maps - the same member as IntMap_RemoveKey_14, with the
 * string instantiation's callees: GetNode is StringMap_Find_1c
 * (0x4fe520; map in EAX = ESI, key pushed from EDX), pPrev slot zeroed
 * at 0x4fe518; on a miss return false; otherwise unlink the node through
 * m_nHash at node+0x18 and m_pNext at node+0x14, hand it to
 * StringMap_FreeNode_1c (0x4fe54f / 0x4fe564) and return true.
 *
 * The callers confirm the member.  The unported flag setter at 0x4fdba0
 * (see StringMap_SetAt_1c's header) works one map, the comm engine's at
 * this+0x1af0: one branch is StringMap_SetAt_1c(id, 1) at 0x4fdc1c, the
 * other is this function at 0x4fdbe1 with `lea eax,[edi+0x1af0]` and the
 * same copied 16-char id in EDX - set the flag, or remove the key.  The
 * second site, 0x50243e in FUN_00501770, passes `lea eax,[edi+0x17fc]`
 * and a 16-char id local (`lea edx,[esp+0xf2]`).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX RECOVERED (2026-08-25) by promotion: it is the map object, passed
 * straight through to the find helper (`mov esi,eax` at the entry, `mov
 * eax,esi` before the call) and then used to rewrite the bucket head.
 *
 * THE MAP IS NOT ACTUALLY RECOVERED - LEFT UNFIXED (2026-10-29).  The
 * EAX note above says the map was promoted, but the body still declares
 * `int *regEax` as an UNINITIALISED LOCAL and dereferences it, and the
 * prototype in functions.h is `__fastcall ()`, so the C caller(s) pass
 * neither the map (EAX) nor the key (EDX, param_2 here).  Recovering it
 * means a trailing map parameter plus the key at every C site:
 * 0x50243e (FUN_00501770) EAX = its EDI + 0x17fc, EDX = its id local
 * at esp+0xf2; 0x4fdbe1 is in the uncarved 0x4fdba0, so has no C site.
 */
#include "ghidra_types.h"


undefined4 __fastcall StringMap_RemoveKey_1c(undefined4 param_1,undefined4 param_2)

{
  int *regEax;   /* the map; see the header note */
  int iVar1;
  int local_c;
  undefined1 local_8 [8];
  
  local_c = 0;
  iVar1 = StringMap_Find_1c((char *)param_2,(uint *)local_8,(undefined4 *)&local_c,regEax,
                       (uint *)(local_8 + 4));
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c == 0) {
    *(undefined4 *)(*regEax + (*(uint *)(iVar1 + 0x18) % (uint)regEax[2]) * 4) =
         *(undefined4 *)(iVar1 + 0x14);
    StringMap_FreeNode_1c(iVar1,(int)regEax);
    return 1;
  }
  *(undefined4 *)(local_c + 0x14) = *(undefined4 *)(iVar1 + 0x14);
  StringMap_FreeNode_1c(iVar1,(int)regEax);
  return 1;
}

