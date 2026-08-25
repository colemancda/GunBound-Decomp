/* FUN_00503e30 - 0x00503e30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * THE HASH SLOT (2026-08-25).  The original passes the find `&param_1` for
 * its hash out-parameter -- reusing the incoming parameter slot, whose value
 * it has already cached in EBP -- and then reads the hash back out of that
 * slot for the insert while EBP still holds the original key.  A C port
 * cannot alias param_1 that way without losing the key, so the hash gets a
 * local of its own and param_1 keeps meaning what it means at the entry.
 */
#include "ghidra_types.h"


void FUN_00503e30(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *unaff_ESI;
  int *unaff_EDI;
  uint local_hash;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = StringMap_Find_28((char *)param_1,&local_hash,(undefined4 *)local_4,unaff_EDI,(uint *)&local_8);
  if (iVar2 == 0) {
    if (*unaff_EDI == 0) {
      cVar1 = HashMap_InitHashTable(unaff_EDI,unaff_EDI[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = StringMap_Insert_28(local_8,local_hash,(undefined4 *)param_1,unaff_EDI);
  }
  *(undefined4 *)(iVar2 + 0x12) = *unaff_ESI;
  *(undefined4 *)(iVar2 + 0x16) = unaff_ESI[1];
  *(undefined4 *)(iVar2 + 0x1a) = unaff_ESI[2];
  *(undefined2 *)(iVar2 + 0x1e) = *(undefined2 *)(unaff_ESI + 3);
  return;
}

