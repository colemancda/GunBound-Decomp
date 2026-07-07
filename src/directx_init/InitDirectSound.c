/* InitDirectSound - 0x004ee5b0 in the original binary.
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


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 InitDirectSound(undefined4 param_1,uint param_2,undefined4 param_3)

{
  FARPROC pFVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piStack_78;
  undefined4 *puStack_74;
  int *piStack_70;
  undefined1 *puStack_6c;
  int **ppiStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int iStack_5c;
  int iStack_58;
  undefined4 uStack_54;
  
  DAT_007935e8 = LoadLibraryA(s_dsound_dll_005574c0);
  if (DAT_007935e8 == (HMODULE)0x0) {
    return 0;
  }
  uStack_54 = (int **)0x4ee5e2;
  pFVar1 = GetProcAddress(DAT_007935e8,s_DirectSoundCreate8_005574ac);
  uStack_54 = (int **)param_3;
  DAT_0079355c = param_1;
  iStack_58 = 0x4ee604;
  OpenXFSArchive();
  DAT_00793560 = 0x1f;
  if (param_2 < 0x20) {
    DAT_00793560 = param_2;
  }
  uStack_54 = (int **)0x0;
  iStack_58 = 0x4ee624;
  iVar2 = (*pFVar1)();
  if (-1 < iVar2) {
    iStack_58 = 2;
    iStack_5c = DAT_0079355c;
    uStack_60 = DAT_0079354c;
    uStack_64 = 0x4ee646;
    iVar2 = (**(code **)(*DAT_0079354c + 0x18))();
    if (-1 < iVar2) {
      uStack_64 = 0;
      ppiStack_68 = &DAT_00793550;
      puStack_6c = &stack0xffffffc4;
      piStack_70 = DAT_0079354c;
      puStack_74 = (undefined4 *)0x4ee697;
      iVar2 = (**(code **)(*DAT_0079354c + 0xc))();
      if (-1 < iVar2) {
        iStack_5c = DAT_00588f3c;
        puStack_74 = &uStack_60;
        uStack_60 = (int *)CONCAT22((short)_DAT_00588f38,1);
        uStack_54 = (int **)CONCAT22(DAT_00588f40,(DAT_00588f40 >> 3) * (short)_DAT_00588f38);
        iStack_58 = DAT_00588f44;
        piStack_78 = DAT_00793550;
        (**(code **)(*DAT_00793550 + 0x38))();
        (**(code **)(*DAT_00793550 + 0x30))(DAT_00793550,0,0,1);
        DAT_00793554 = operator_new(DAT_00793560 * 4);
        DAT_00793558 = operator_new(DAT_00793560 * 4);
        pvVar3 = operator_new(0xb8);
        if (pvVar3 == (void *)0x0) {
          uVar4 = 0;
        }
        else {
          uVar4 = FUN_004eebe0();
        }
        *DAT_00793554 = uVar4;
        uVar5 = 1;
        if (1 < DAT_00793560) {
          do {
            pvVar3 = operator_new(0x50);
            if (pvVar3 == (void *)0x0) {
              uVar4 = 0;
            }
            else {
              uVar4 = FUN_004ef3a0();
            }
            DAT_00793554[uVar5] = uVar4;
            uVar5 = uVar5 + 1;
          } while (uVar5 < DAT_00793560);
        }
        iStack_58 = 0;
        iStack_5c = DAT_00588f44 * 2;
        uStack_54 = &piStack_78;
        uVar5 = 0;
        uStack_64 = 0x24;
        if (DAT_00793560 != 0) {
          do {
            uStack_60 = (int *)((-(uint)(uVar5 != 0) & 0xffffffe0) + 0x1a2);
            (**(code **)(*DAT_0079354c + 0xc))
                      (DAT_0079354c,&uStack_64,(void *)((int)DAT_00793558 + uVar5 * 4),0);
            uVar5 = uVar5 + 1;
          } while (uVar5 < DAT_00793560);
        }
        DAT_00793549 = 1;
        DAT_0079354b = 1;
        DAT_0079354a = 1;
        return 1;
      }
    }
  }
  return 0;
}

