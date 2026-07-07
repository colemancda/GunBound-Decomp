/* FUN_00405a40 - 0x00405a40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405a40(void)

{
  ushort *puVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int unaff_EDI;
  bool bVar6;
  
  if ((*(char *)(unaff_EDI + 0x2008) != '\0') &&
     (*(int *)(*(int *)(unaff_EDI + 0x2004) + 0x22c) != 3)) {
    *(undefined1 *)(unaff_EDI + 0x2008) = 0;
    *(bool *)(unaff_EDI + 0x2009) = *(int *)(*(int *)(unaff_EDI + 0x2004) + 0x22c) == 2;
  }
  do {
    while( true ) {
      iVar3 = *(int *)(unaff_EDI + 0x2004);
      iVar4 = *(int *)(iVar3 + 0x24238);
      if (iVar4 == *(int *)(iVar3 + 0x24234)) {
        return;
      }
      uVar5 = iVar4 + 1U & 0x800000ff;
      puVar1 = (ushort *)(*(int *)(iVar3 + 0x24240 + iVar4 * 4) + 0x4234 + iVar3);
      if ((int)uVar5 < 0) {
        uVar5 = (uVar5 - 1 | 0xffffff00) + 1;
      }
      *(uint *)(iVar3 + 0x24238) = uVar5;
      uVar2 = *puVar1;
      if (uVar2 < 0xa212) break;
      if ((uVar2 != 0xa221) && (uVar2 != 0xa231)) {
        bVar6 = uVar2 == 0xa241;
        goto LAB_00405af0;
      }
LAB_00405aff:
      if (puVar1[1] == 0) {
        FUN_00411b40();
      }
    }
    if (((uVar2 == 0xa211) || (uVar2 == 0xa001)) || (uVar2 == 0xa111)) goto LAB_00405aff;
    bVar6 = uVar2 == 0xa201;
LAB_00405af0:
    if (bVar6) goto LAB_00405aff;
    FUN_00411b40();
  } while( true );
}

