/* StringMap_RemoveKey_ac - 0x00504050 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::RemoveKey(key) for the 0xac-node
 * string-keyed maps - instruction for instruction the same routine as
 * StringMap_RemoveKey_1c (0x4fe500), with this instantiation's callees:
 * GetNode is StringMap_Find_ac (0x504070; map in EAX = ESI, key pushed
 * from EDX), pPrev slot zeroed at 0x504068; on a miss return false;
 * otherwise unlink the node through m_nHash at node+0xa8 and m_pNext at
 * node+0xa4, hand it to StringMap_FreeNode_ac (0x5040a5 / 0x5040c0) and
 * return true.
 *
 * The one binary caller, FUN_00503a50 at 0x503b8b, passes `lea
 * eax,[ebp+0x290]` - the id-keyed P2P peer table HasP2PPeerRecord
 * tests - and in EDX the 16-char id it has just copied into a local
 * (`lea edx,[esp+0x12]`), as its last act before returning.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX RECOVERED (2026-08-25) by promotion: it is the map object, passed
 * straight through to the find helper (`mov esi,eax` at the entry, `mov
 * eax,esi` before the call) and then used to rewrite the bucket head.
 *
 * MAP AND KEY RECOVERED (2026-10-29).  The previous body declared
 * `int *regEax` as an uninitialised local and the functions.h prototype
 * was `__fastcall ()`, so callers passed neither input.  The disassembly
 * fixes the real convention: the map arrives in EAX (`mov esi,eax` at
 * 0x504055, then `mov eax,esi` before the find call at 0x504070) and the
 * key in EDX (`push edx` at 0x504061, the find helper's first
 * stack argument).  ECX is NOT an input - it is overwritten by `lea
 * ecx,[esp+0x10]` at 0x50405c before any read - and there are no
 * stack arguments (plain `ret`).  So the Ghidra __fastcall label was
 * wrong: the port is now a plain function taking the key (EDX) and the
 * map (EAX) as trailing register parameters, the repo's promotion idiom.
 * C site fixed: 0x503b8b in FUN_00503a50 (EAX = `lea eax,[ebp+0x290]` at
 * 0x503b81, EDX = `lea edx,[esp+0x12]` at 0x503b87).
 */
#include "ghidra_types.h"


undefined4 StringMap_RemoveKey_ac(char *regEdx,int *regEax)

{
  int iVar1;
  int local_c;
  undefined1 local_8 [8];
  
  local_c = 0;
  iVar1 = (int)StringMap_Find_ac(regEdx,(uint *)local_8,(undefined4 *)&local_c,regEax,
                       (uint *)(local_8 + 4));
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c == 0) {
    *(undefined4 *)(*regEax + (*(uint *)(iVar1 + 0xa8) % (uint)regEax[2]) * 4) =
         *(undefined4 *)(iVar1 + 0xa4);
    StringMap_FreeNode_ac(iVar1,(int)regEax);
    return 1;
  }
  *(undefined4 *)(local_c + 0xa4) = *(undefined4 *)(iVar1 + 0xa4);
  StringMap_FreeNode_ac(iVar1,(int)regEax);
  return 1;
}

