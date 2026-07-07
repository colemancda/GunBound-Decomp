/* OpenXFSArchive - 0x004f0a50 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 OpenXFSArchive(LPCSTR param_1,int param_2,int param_3)

{
  HANDLE hFile;
  DWORD DVar1;
  BOOL BVar2;
  void *pvVar3;
  int iVar4;
  uint uVar5;
  short *unaff_ESI;
  short *psVar6;
  DWORD DStack_40008;
  DWORD DStack_40004;
  undefined1 auStack_40000 [262144];
  
  if (*(int *)(unaff_ESI + 0x820) != -1) {
    return 0x40001;
  }
  SetFileAttributesA(param_1,0x80);
  hFile = CreateFileA(param_1,(-(uint)(param_2 != '\0') & 0xc0000000) + 0xc0000000,
                      (uint)(param_2 != '\0') * 2 + 1,(LPSECURITY_ATTRIBUTES)0x0,4,
                      (-(uint)(param_2 != '\0') & 0xf8000000) + 0x10000080,(HANDLE)0x0);
  *(HANDLE *)(unaff_ESI + 0x820) = hFile;
  if (hFile == (HANDLE)0xffffffff) {
    return 0;
  }
  DVar1 = SetFilePointer(hFile,-4,(PLONG)0x0,2);
  *(undefined1 *)(unaff_ESI + 0x8398) = param_3;
  if (DVar1 == 0xffffffff) {
    unaff_ESI[2] = 0;
    unaff_ESI[3] = 0;
    unaff_ESI[4] = 0;
    unaff_ESI[5] = 0;
    unaff_ESI[6] = 0;
    unaff_ESI[7] = 0;
    unaff_ESI[8] = 0;
    unaff_ESI[9] = 0;
    unaff_ESI[0] = 0x4658;
    unaff_ESI[1] = 0x3253;
    psVar6 = unaff_ESI + 10;
    for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
      psVar6[0] = 0;
      psVar6[1] = 0;
      psVar6 = psVar6 + 2;
    }
    *(char *)((int)unaff_ESI + 0x1045) = param_2;
    return 1;
  }
  BVar2 = ReadFile(*(HANDLE *)(unaff_ESI + 0x820),&DStack_40004,4,&DStack_40008,(LPOVERLAPPED)0x0);
  if ((BVar2 == 1) && (DStack_40008 == 4)) {
    SetFilePointer(*(HANDLE *)(unaff_ESI + 0x820),DStack_40004,(PLONG)0x0,0);
    BVar2 = ReadFile(*(HANDLE *)(unaff_ESI + 0x820),&DStack_40004,4,&DStack_40008,(LPOVERLAPPED)0x0)
    ;
    if ((BVar2 == 1) && (DStack_40008 == 4)) {
      BVar2 = ReadFile(*(HANDLE *)(unaff_ESI + 0x820),auStack_40000,DStack_40004,&DStack_40008,
                       (LPOVERLAPPED)0x0);
      if ((BVar2 == 1) && (DStack_40008 == DStack_40004)) {
        DecodeLZHUFBlock(unaff_ESI + 0x824,unaff_ESI,auStack_40000,DStack_40008,0x40);
        if (*unaff_ESI == DAT_0055751c) {
          uVar5 = 0;
          if ((*(uint *)(unaff_ESI + 4) & 0xfffffc00) != 0) {
            psVar6 = unaff_ESI + 0x20;
            do {
              BVar2 = ReadFile(*(HANDLE *)(unaff_ESI + 0x820),&DStack_40004,4,&DStack_40008,
                               (LPOVERLAPPED)0x0);
              if ((BVar2 != 1) || (DStack_40008 != 4)) goto LAB_004f0d14;
              pvVar3 = operator_new(0x20000);
              *(void **)psVar6 = pvVar3;
              BVar2 = ReadFile(*(HANDLE *)(unaff_ESI + 0x820),auStack_40000,DStack_40004,
                               &DStack_40008,(LPOVERLAPPED)0x0);
              if ((BVar2 != 1) || (DStack_40008 != DStack_40004)) goto LAB_004f0d14;
              DecodeLZHUFBlock(unaff_ESI + 0x824,*(undefined4 *)psVar6,auStack_40000,DStack_40008,
                               0x20000);
              uVar5 = uVar5 + 1;
              psVar6 = psVar6 + 2;
            } while (uVar5 < *(uint *)(unaff_ESI + 4) >> 10);
          }
          if ((*(uint *)(unaff_ESI + 4) & 0x3ff) == 0) {
LAB_004f0cf9:
            *(char *)((int)unaff_ESI + 0x1045) = param_2;
            return 1;
          }
          BVar2 = ReadFile(*(HANDLE *)(unaff_ESI + 0x820),&DStack_40004,4,&DStack_40008,
                           (LPOVERLAPPED)0x0);
          if ((BVar2 == 1) && (DStack_40008 == 4)) {
            pvVar3 = operator_new(0x20000);
            *(void **)(unaff_ESI + uVar5 * 2 + 0x20) = pvVar3;
            BVar2 = ReadFile(*(HANDLE *)(unaff_ESI + 0x820),auStack_40000,DStack_40004,&DStack_40008
                             ,(LPOVERLAPPED)0x0);
            if ((BVar2 == 1) && (DStack_40008 == DStack_40004)) {
              DecodeLZHUFBlock(unaff_ESI + 0x824,*(undefined4 *)(unaff_ESI + uVar5 * 2 + 0x20),
                               auStack_40000,DStack_40008,0x20000);
              goto LAB_004f0cf9;
            }
          }
        }
      }
    }
  }
LAB_004f0d14:
  CloseHandle(*(HANDLE *)(unaff_ESI + 0x820));
  unaff_ESI[0x820] = -1;
  unaff_ESI[0x821] = -1;
  return 0;
}

