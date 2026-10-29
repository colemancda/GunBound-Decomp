/* StringMap_Find_10 - 0x00426780 in the original binary.
 *
 * ATL7 CAtlMap::GetNode(key, iBin, nHash, pPrev) - same out-parameter
 * order - for the CStringA-keyed maps with 0x10-byte nodes
 * (key +0, value +4, m_pNext +8, m_nHash +0xc): hash the key (h*0x21+c
 * over the signed chars), take it modulo the bin count at map+8, then
 * walk bin[i] along +8 comparing +0xc against the hash and then the key
 * with __mbscmp.  h*0x21+c is CStringElementTraits::Hash's (h<<5)+h+c
 * verbatim.  Returns the node (or 0) and reports the bucket index, the
 * hash and the predecessor through its three out-parameters.
 *
 * Distinct from StringMap_Find_1c/_28/_ac (0x4ff130/0x4fef70/0x500ef0):
 * those hash through HashStringNoCase, link at +0x14/+0x20/+0xa4 and
 * compare with __stricmp over inline char-array keys.  This one is
 * case-sensitive over a CStringA pointer at node+0.
 *
 * The suffix is the stride and not a value type on purpose.  Find never
 * touches the value, so this one body serves BOTH 0x10-node
 * instantiations in the image (identical code, one copy): the
 * CStringA->CStringA maps whose insert is StringMap_Insert_CString
 * (0x426960) - the nickname/user-id caches at ctx+0x6aa41c/+0x6aa44c and
 * the Sound.txt table DAT_00794e14 - and the CStringA->POD
 * ChooseEvent.txt table DAT_00e9bea8, whose insert is
 * StringMap_Insert_Int (0x409d10; ParseChooseEventLine,
 * 0x409cef-0x409cfa).  A _CString suffix here would hide the second
 * family.  9 binary call sites.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * FIXED (2026-07-15): a string-keyed hash-table lookup (computes the
 * string's hash, then walks the matching bucket's chain for an exact
 * match via __mbscmp). `table` (the hash table object, was `in_EAX`) and
 * `key` (the string being looked up, was `unaff_EBX`) were both dropped
 * registers. Confirmed via angr disassembly of the sole caller,
 * ParseChooseEventLine (0x409cb0-0x409cc7): `mov ebx,eax` at that
 * function's own entry (ebx = its own incoming EAX = param_2, the parsed
 * line/message) is never touched before `mov eax,esi; call 0x426780`
 * (esi = that function's own param_1, the event registry) - i.e. table
 * and key are ParseChooseEventLine's own param_1/param_2, still live in
 * EAX/EBX at the call.
 */
#include "ghidra_types.h"


undefined4 * StringMap_Find_10(uint *param_1,uint *param_2,undefined4 *param_3,int *table,
                           uchar *key)

{
  uchar *puVar1;
  uchar uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  uchar *puVar7;

  uVar5 = 0;
  uVar2 = *key;
  puVar7 = key;
  while (uVar2 != '\0') {
    uVar5 = uVar5 * 0x21 + (int)(char)uVar2;
    puVar1 = puVar7 + 1;
    puVar7 = puVar7 + 1;
    uVar2 = *puVar1;
  }
  *param_2 = uVar5;
  *param_1 = uVar5 % (uint)table[2];
  if (*table != 0) {
    *param_3 = 0;
    puVar3 = (undefined4 *)0x0;
    puVar4 = *(undefined4 **)(*table + *param_1 * 4);
    while( true ) {
      if (puVar4 == (undefined4 *)0x0) {
        return (undefined4 *)0x0;
      }
      if ((puVar4[3] == *param_2) && (iVar6 = __mbscmp((uchar *)*puVar4,key), iVar6 == 0))
      break;
      puVar3 = puVar4;
      puVar4 = (undefined4 *)puVar4[2];
    }
    *param_3 = puVar3;
    return puVar4;
  }
  return (undefined4 *)0x0;
}

