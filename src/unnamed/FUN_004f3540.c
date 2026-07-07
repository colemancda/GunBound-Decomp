/* FUN_004f3540 - 0x004f3540 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f3540(undefined4 param_1,int param_2)

{
  float fVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  
  iVar4 = 0;
  puVar5 = (undefined4 *)(param_2 + 0x210);
  do {
    uVar6 = FUN_004f4810();
    iVar3 = (int)((ulonglong)uVar6 >> 0x20);
    puVar2 = (undefined4 *)uVar6;
    *puVar5 = *puVar2;
    puVar5[1] = puVar2[1];
    puVar5[2] = puVar2[2];
    iVar4 = iVar4 + 0x10;
    puVar5[3] = puVar2[3];
    puVar5 = puVar5 + 4;
  } while (iVar4 < 0x80);
  fVar1 = *(float *)(param_2 + 0xe0);
  *(float *)(iVar3 + 0x2b4) = -*(float *)(param_2 + 0xe0);
  *(float *)(iVar3 + 0x290) = fVar1;
  *(undefined4 *)(iVar3 + 0x294) = *(undefined4 *)(iVar3 + 0xe4);
  *(float *)(iVar3 + 0x2b8) = -*(float *)(iVar3 + 0xe4);
  *(undefined4 *)(iVar3 + 0x298) = *(undefined4 *)(iVar3 + 0xe8);
  *(float *)(iVar3 + 700) = -*(float *)(iVar3 + 0xe8);
  *(undefined4 *)(iVar3 + 0x29c) = *(undefined4 *)(iVar3 + 0xf0);
  *(undefined4 *)(iVar3 + 0x2a0) = *(undefined4 *)(iVar3 + 0xf4);
  *(float *)(iVar3 + 0x2c0) = -*(float *)(iVar3 + 0xf0);
  *(undefined4 *)(iVar3 + 0x2a4) = *(undefined4 *)(iVar3 + 0xf8);
  *(float *)(iVar3 + 0x2c4) = -*(float *)(iVar3 + 0xf4);
  *(undefined4 *)(iVar3 + 0x2a8) = *(undefined4 *)(iVar3 + 0x100);
  *(undefined4 *)(iVar3 + 0x2ac) = *(undefined4 *)(iVar3 + 0x104);
  *(float *)(iVar3 + 0x2c8) = -*(float *)(iVar3 + 0xf8);
  *(undefined4 *)(iVar3 + 0x2b0) = *(undefined4 *)(iVar3 + 0x108);
  *(float *)(iVar3 + 0x2cc) = -*(float *)(iVar3 + 0x100);
  *(float *)(iVar3 + 0x2d0) = -*(float *)(iVar3 + 0x104);
  *(float *)(iVar3 + 0x2d4) = -*(float *)(iVar3 + 0x108);
  *(float *)(iVar3 + 0x2d8) =
       -(*(float *)(iVar3 + 0x290) * *(float *)(iVar3 + 0x220) +
        *(float *)(iVar3 + 0x294) * *(float *)(iVar3 + 0x224) +
        *(float *)(iVar3 + 0x298) * *(float *)(iVar3 + 0x228));
  *(float *)(iVar3 + 0x2dc) =
       -(*(float *)(iVar3 + 0x29c) * *(float *)(iVar3 + 0x220) +
        *(float *)(iVar3 + 0x2a0) * *(float *)(iVar3 + 0x224) +
        *(float *)(iVar3 + 0x2a4) * *(float *)(iVar3 + 0x228));
  *(float *)(iVar3 + 0x2e0) =
       -(*(float *)(iVar3 + 0x220) * *(float *)(iVar3 + 0x2a8) +
        *(float *)(iVar3 + 0x2ac) * *(float *)(iVar3 + 0x224) +
        *(float *)(iVar3 + 0x2b0) * *(float *)(iVar3 + 0x228));
  *(float *)(iVar3 + 0x2e4) =
       -(*(float *)(iVar3 + 0x2b4) * *(float *)(iVar3 + 0x280) +
        *(float *)(iVar3 + 0x2b8) * *(float *)(iVar3 + 0x284) +
        *(float *)(iVar3 + 700) * *(float *)(iVar3 + 0x288));
  *(float *)(iVar3 + 0x2e8) =
       -(*(float *)(iVar3 + 0x2c0) * *(float *)(iVar3 + 0x280) +
        *(float *)(iVar3 + 0x2c4) * *(float *)(iVar3 + 0x284) +
        *(float *)(iVar3 + 0x2c8) * *(float *)(iVar3 + 0x288));
  *(float *)(iVar3 + 0x2ec) =
       -(*(float *)(iVar3 + 0x2cc) * *(float *)(iVar3 + 0x280) +
        *(float *)(iVar3 + 0x2d0) * *(float *)(iVar3 + 0x284) +
        *(float *)(iVar3 + 0x2d4) * *(float *)(iVar3 + 0x288));
  return;
}

