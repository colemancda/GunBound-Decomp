/* FindOrInsertXFSEntry - 0x004f1220 in the original binary.
 *
 * Locate `name` in an XFS archive's sorted entry table, inserting a new
 * entry (keeping the table sorted) if it is absent. Returns the entry
 * index. Called only by OpenXFSEntryStream's insert path.
 *
 * Two dropped/zero-arg calls recovered from disassembly (confirmed via
 * angr) and restored here:
 *   - FindXFSEntryIndex was called with just the name; it also needs the
 *     archive (its EBX register). Now FindXFSEntryIndex(archive, name).
 *   - The insertion-point linear scan called CompareXFSEntryName with no
 *     args. The disassembly computes the record pointer at the current
 *     index into EAX and the searched name into EDX, so the call is
 *     CompareXFSEntryName(record, name) (record vs name - note the reverse
 *     of FindXFSEntryIndex's own name-vs-record order).
 *
 * Params: archive (EBX), name (2nd stack arg), flag (3rd stack arg, stored
 * as the entry's +0x70 "streamed" bit).
 */
#include "ghidra_types.h"


uint FindOrInsertXFSEntry(int archive, char *name, int flag)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;

  uVar2 = FindXFSEntryIndex(archive, name);
  if (uVar2 == 0xffffffff) {
    uVar5 = *(uint *)(archive + 8);
    uVar2 = 0;
    if (uVar5 != 0) {
      do {
        iVar6 = *(int *)(archive + 0x40 + (uVar2 >> 10) * 4);
        if (iVar6 == 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = (uVar2 & 0x3ff) * 0x80 + iVar6;
        }
        iVar3 = CompareXFSEntryName((char *)iVar6, name);
        if (0 < iVar3) break;
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(archive + 8));
    }
    if ((uVar5 & 0x3ff) == 0) {
      puVar4 = operator_new(0x20000);
      *(undefined4 **)(archive + 0x40 + (uVar5 >> 10) * 4) = puVar4;
      for (iVar3 = 0x8000; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
    }
    uVar5 = *(uint *)(archive + 8);
    *(uint *)(archive + 8) = uVar5 + 1;
    uVar7 = uVar5;
    for (; uVar2 < uVar5; uVar5 = uVar5 - 1) {
      uVar7 = uVar7 - 1;
      iVar3 = *(int *)(archive + 0x40 + (uVar7 >> 10) * 4);
      if (iVar3 == 0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4 = (undefined4 *)((uVar7 & 0x3ff) * 0x80 + iVar3);
      }
      iVar3 = *(int *)(archive + 0x40 + (uVar5 >> 10) * 4);
      if (iVar3 == 0) {
        puVar8 = (undefined4 *)0x0;
      }
      else {
        puVar8 = (undefined4 *)((uVar5 & 0x3ff) * 0x80 + iVar3);
      }
      for (iVar3 = 0x20; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar8 = puVar8 + 1;
      }
    }
    iVar3 = *(int *)(archive + 0x40 + (uVar2 >> 10) * 4);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (uVar2 & 0x3ff) * 0x80 + iVar3;
    }
    iVar6 = iVar3 - (int)name;
    do {
      cVar1 = *name;
      name[iVar6] = cVar1;
      name = name + 1;
    } while (cVar1 != '\0');
  }
  else {
    iVar3 = *(int *)(archive + 0x40 + (uVar2 >> 10) * 4);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (uVar2 & 0x3ff) * 0x80 + iVar3;
    }
  }
  *(undefined4 *)(iVar3 + 0x74) = *(undefined4 *)(archive + 0x10);
  *(undefined4 *)(iVar3 + 0x7c) = 0;
  *(undefined4 *)(iVar3 + 0x78) = 0;
  *(uint *)(iVar3 + 0x70) = (uint)(flag != '\0');
  return uVar2;
}
