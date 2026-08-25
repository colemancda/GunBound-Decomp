/* FUN_00500ef0 - 0x00500ef0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX and EBX RECOVERED (2026-08-25).  This is a chained hash-map FIND, and
 * it returns THREE things: the hash through param_2, the predecessor node
 * through param_3, and the bucket index through EBX -- which Ghidra dropped,
 * along with EAX, the map object itself (`mov esi,eax` at the entry, then
 * `div [esi+8]` against the bucket count).
 *
 * That dropped bucket-index out-pointer is why two of the callers declare a
 * local_8 they never assign: its only writer was this argument.  With EBX a
 * real parameter those locals are initialised again.
 */
#include "ghidra_types.h"


char * FUN_00500ef0(char *param_1,uint *param_2,undefined4 *param_3,int *regEax,uint *regEbx)

{
  char *pcVar1;
  char *_Str1;
  uint uVar2;
  int iVar3;
  
  uVar2 = HashStringNoCase((int)param_1);
  *param_2 = uVar2;
  *regEbx = uVar2 % (uint)regEax[2];
  if (*regEax != 0) {
    *param_3 = 0;
    pcVar1 = (char *)0x0;
    for (_Str1 = *(char **)(*regEax + *regEbx * 4); _Str1 != (char *)0x0;
        _Str1 = *(char **)(_Str1 + 0xa4)) {
      if ((*(uint *)(_Str1 + 0xa8) == *param_2) && (iVar3 = __stricmp(_Str1,param_1), iVar3 == 0)) {
        *param_3 = pcVar1;
        return _Str1;
      }
      pcVar1 = _Str1;
    }
  }
  return (char *)0x0;
}

