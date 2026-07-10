/* FUN_004f0d70 - 0x004f0d70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"
#include "xfs.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

/* CloseXFSArchive - flushes any dirty blocks back to the archive file, frees
 * the 0x400 cached block pointers at archive+0x40, closes the file handle
 * (archive+0x1040) and marks it XFS_CLOSED. The archive `this` pointer arrived
 * in ESI in the original (a dropped register arg in Ghidra's `(void)` port);
 * promoted to an explicit parameter so callers can pass it. */
undefined4 FUN_004f0d70(XFSArchive *archive)

{
  undefined4 uVar1;
  DWORD DVar2;
  BOOL BVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_ESI = (int)archive;
  DWORD DStack_4000c;
  DWORD DStack_40008;
  uint uStack_40004;
  undefined1 auStack_40000 [262144];
  
  if ((*(int *)(unaff_ESI + 0x1040) == -1) || (*(char *)(unaff_ESI + 0x1044) == '\x01')) {
    return 0x40001;
  }
  if (*(char *)(unaff_ESI + 0x1045) != '\0') {
LAB_004f0fac:
    puVar4 = (undefined4 *)(unaff_ESI + 0x40);
    iVar5 = 0x400;
    do {
      if ((void *)*puVar4 != (void *)0x0) {
        _free((void *)*puVar4);
      }
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    CloseHandle(*(HANDLE *)(unaff_ESI + 0x1040));
    *(undefined4 *)(unaff_ESI + 0x1040) = 0xffffffff;
    return 1;
  }
  if (*(char *)(unaff_ESI + 0x10730) == '\0') {
    *(undefined4 *)(unaff_ESI + 0xc) = 0;
  }
  else {
    uVar1 = FUN_004f1020();
    *(undefined4 *)(unaff_ESI + 0xc) = uVar1;
  }
  DVar2 = SetFilePointer(*(HANDLE *)(unaff_ESI + 0x1040),*(LONG *)(unaff_ESI + 0x10),(PLONG)0x0,0);
  if (DVar2 != 0xffffffff) {
    iVar5 = unaff_ESI + 0x1048;
    DStack_40008 = FUN_004ea760(iVar5,auStack_40000,unaff_ESI,0x40);
    BVar3 = WriteFile(*(HANDLE *)(unaff_ESI + 0x1040),&DStack_40008,4,&DStack_4000c,
                      (LPOVERLAPPED)0x0);
    if ((((BVar3 == 1) && (DStack_4000c == 4)) &&
        (BVar3 = WriteFile(*(HANDLE *)(unaff_ESI + 0x1040),auStack_40000,DStack_40008,&DStack_4000c,
                           (LPOVERLAPPED)0x0), BVar3 == 1)) && (DStack_4000c == DStack_40008)) {
      uStack_40004 = 0;
      if ((*(uint *)(unaff_ESI + 8) & 0xfffffc00) != 0) {
        puVar4 = (undefined4 *)(unaff_ESI + 0x40);
        do {
          DStack_40008 = FUN_004ea760(iVar5,auStack_40000,*puVar4,0x20000);
          BVar3 = WriteFile(*(HANDLE *)(unaff_ESI + 0x1040),&DStack_40008,4,&DStack_4000c,
                            (LPOVERLAPPED)0x0);
          if (((BVar3 != 1) || (DStack_4000c != 4)) ||
             ((BVar3 = WriteFile(*(HANDLE *)(unaff_ESI + 0x1040),auStack_40000,DStack_40008,
                                 &DStack_4000c,(LPOVERLAPPED)0x0), BVar3 != 1 ||
              (DStack_4000c != DStack_40008)))) goto LAB_004f0ff2;
          uStack_40004 = uStack_40004 + 1;
          puVar4 = puVar4 + 1;
        } while (uStack_40004 < *(uint *)(unaff_ESI + 8) >> 10);
      }
      if ((*(uint *)(unaff_ESI + 8) & 0x3ff) != 0) {
        DStack_40008 = FUN_004ea760(iVar5,auStack_40000,
                                    *(undefined4 *)(unaff_ESI + 0x40 + uStack_40004 * 4),0x20000);
        BVar3 = WriteFile(*(HANDLE *)(unaff_ESI + 0x1040),&DStack_40008,4,&DStack_4000c,
                          (LPOVERLAPPED)0x0);
        if (((BVar3 != 1) || (DStack_4000c != 4)) ||
           ((BVar3 = WriteFile(*(HANDLE *)(unaff_ESI + 0x1040),auStack_40000,DStack_40008,
                               &DStack_4000c,(LPOVERLAPPED)0x0), BVar3 != 1 ||
            (DStack_4000c != DStack_40008)))) goto LAB_004f0ff2;
      }
      BVar3 = WriteFile(*(HANDLE *)(unaff_ESI + 0x1040),(LPCVOID)(unaff_ESI + 0x10),4,&DStack_4000c,
                        (LPOVERLAPPED)0x0);
      if ((BVar3 == 1) && (DStack_4000c == 4)) {
        SetEndOfFile(*(HANDLE *)(unaff_ESI + 0x1040));
        goto LAB_004f0fac;
      }
    }
  }
LAB_004f0ff2:
  CloseHandle(*(HANDLE *)(unaff_ESI + 0x1040));
  *(undefined4 *)(unaff_ESI + 0x1040) = 0xffffffff;
  return 0;
}

