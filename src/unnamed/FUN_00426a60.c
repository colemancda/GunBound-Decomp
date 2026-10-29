/* FUN_00426a60 - 0x00426a60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


int __thiscall FUN_00426a60(char *key,int *node,undefined4 hash)

{
  int iVar1;

  ConstructStringFromText(key,node);
  iVar1 = (**(code **)(DAT_005b1444 + 0xc))();
  node[1] = iVar1 + 0x10;
  node[3] = hash;
  return (int)node;
}

