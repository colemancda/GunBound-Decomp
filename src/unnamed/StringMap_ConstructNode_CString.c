/* StringMap_ConstructNode_CString - 0x00426a60 in the original binary.
 *
 * NAMED (2026-10-29): the CAtlMap<K,V>::CNode constructor that ATL7's
 * CAtlMap::NewNode runs as `::new( pNewNode ) CNode( key, nHash )` -
 * m_key(key), a default-constructed m_value, m_nHash(nHash).  The
 * evidence is the one caller, StringMap_Insert_CString (0x426960, that
 * instantiation's NewNode): it pops the node off the free list at
 * map+0x2c, raises its SEH state to 1 (`mov [ebp-4],1` at 0x4269e3)
 * around this call and drops it to -1 right after (0x4269ef) - NewNode's
 * _ATLTRY around the placement new - and then links the returned node
 * into the bin and rehashes.  The node layout written here is the one
 * StringMap_FindOrInsert_10's header records for that map (+0 key, +4
 * value, +8 chain, +0xc hash): key CStringA at +0, nil CStringA at +4,
 * hash at +0xc; +8 is left for the caller's link.
 *
 * The _CString suffix follows its caller: the other 0x10-node insert,
 * FUN_00409d10 (the ChooseEvent.txt map's), inlines its node
 * construction - the key constructor at 0x409d96 and the hash store at
 * 0x409da5, with nothing written to the POD value at +4 - so it has no
 * separate counterpart of this function.  Node rather than Element
 * because the object is the map's CNode, not a bare value.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-10-29): the node constructor that
 * StringMap_Insert_CString runs on each fresh 0x10-byte node.  The real
 * convention is ECX = key, stack = (node, hash), `ret 8` at 0x426ab3.
 * Ghidra kept only the two stack args, so the port lost the key:
 * 0x426a76-0x426a7b pushes the node (`mov esi,[esp+0x14]; push esi`) and
 * calls ConstructStringFromText (0x405510) with ECX still holding the
 * incoming key, building the key CStringA at node+0.  The port called it
 * with the node alone, so every node was built with no key string.  The
 * value CStringA at node+4 (nil string, 0x426a88-0x426a9c) and the hash
 * at node+0xc are unchanged.  The SEH registration through the
 * uninitialised `unaff_FS_OFFSET` is stripped, the same artifact
 * ConstructStringFromText.c's header describes.
 */
#include "ghidra_types.h"


int __thiscall StringMap_ConstructNode_CString(char *key,int *node,undefined4 hash)

{
  int iVar1;

  ConstructStringFromText(key,node);
  iVar1 = (**(code **)(DAT_005b1444 + 0xc))();
  node[1] = iVar1 + 0x10;
  node[3] = hash;
  return (int)node;
}

