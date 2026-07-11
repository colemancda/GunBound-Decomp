/* Sha1TransformBlocks - 0x004f9fa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall Sha1TransformBlocks(uint *param_1,int param_2)

{
  byte *in_EAX;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  
  uVar10 = param_1[2];
  uVar2 = param_1[1];
  uVar8 = (uint)*in_EAX << 0x18 | (uint)in_EAX[1] << 0x10 | (uint)in_EAX[2] << 8 | (uint)in_EAX[3];
  uVar20 = (uint)in_EAX[4] << 0x18 | (uint)in_EAX[5] << 0x10 | (uint)in_EAX[6] << 8 |
           (uint)in_EAX[7];
  uVar1 = ((param_1[3] ^ uVar10) & uVar2 ^ param_1[3]) +
          (*param_1 << 5 | *param_1 >> 0x1b) + param_1[4] + 0x5a827999 + uVar8;
  uVar9 = uVar2 << 0x1e | uVar2 >> 2;
  uVar3 = (uint)in_EAX[8] << 0x18 | (uint)in_EAX[9] << 0x10 | (uint)in_EAX[10] << 8 |
          (uint)in_EAX[0xb];
  uVar2 = *param_1;
  uVar10 = param_1[3] + 0x5a827999 +
           ((uVar10 ^ uVar9) & uVar2 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar20;
  uVar21 = uVar2 << 0x1e | uVar2 >> 2;
  uVar4 = (uint)in_EAX[0xc] << 0x18 | (uint)in_EAX[0xd] << 0x10 | (uint)in_EAX[0xe] << 8 |
          (uint)in_EAX[0xf];
  uVar2 = ((uVar9 ^ uVar21) & uVar1 ^ uVar9) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar3 + 0x5a827999
          + param_1[2];
  uVar1 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar5 = (uint)in_EAX[0x10] << 0x18 | (uint)in_EAX[0x11] << 0x10 | (uint)in_EAX[0x12] << 8 |
          (uint)in_EAX[0x13];
  uVar9 = ((uVar1 ^ uVar21) & uVar10 ^ uVar21) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar4 + 0x5a827999
          + uVar9;
  uVar10 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar6 = (uint)in_EAX[0x14] << 0x18 | (uint)in_EAX[0x15] << 0x10 | (uint)in_EAX[0x16] << 8 |
          (uint)in_EAX[0x17];
  uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar21 = ((uVar1 ^ uVar10) & uVar2 ^ uVar1) + (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar5 + 0x5a827999
           + uVar21;
  uVar12 = (uint)in_EAX[0x18] << 0x18 | (uint)in_EAX[0x19] << 0x10 | (uint)in_EAX[0x1a] << 8 |
           (uint)in_EAX[0x1b];
  uVar2 = uVar9 * 0x40000000 | uVar9 >> 2;
  uVar1 = ((uVar10 ^ uVar11) & uVar9 ^ uVar10) + (uVar21 * 0x20 | uVar21 >> 0x1b) + uVar6 +
          0x5a827999 + uVar1;
  uVar7 = (uint)in_EAX[0x1c] << 0x18 | (uint)in_EAX[0x1d] << 0x10 | (uint)in_EAX[0x1e] << 8 |
          (uint)in_EAX[0x1f];
  uVar10 = ((uVar11 ^ uVar2) & uVar21 ^ uVar11) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar12 +
           0x5a827999 + uVar10;
  uVar21 = uVar21 * 0x40000000 | uVar21 >> 2;
  uVar13 = (uint)in_EAX[0x20] << 0x18 | (uint)in_EAX[0x21] << 0x10 | (uint)in_EAX[0x22] << 8 |
           (uint)in_EAX[0x23];
  uVar11 = ((uVar2 ^ uVar21) & uVar1 ^ uVar2) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar7 +
           0x5a827999 + uVar11;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar22 = (uint)in_EAX[0x24] << 0x18 | (uint)in_EAX[0x25] << 0x10 | (uint)in_EAX[0x26] << 8 |
           (uint)in_EAX[0x27];
  uVar2 = ((uVar21 ^ uVar9) & uVar10 ^ uVar21) + (uVar11 * 0x20 | uVar11 >> 0x1b) + uVar13 +
          0x5a827999 + uVar2;
  uVar10 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar14 = (uint)in_EAX[0x28] << 0x18 | (uint)in_EAX[0x29] << 0x10 | (uint)in_EAX[0x2a] << 8 |
           (uint)in_EAX[0x2b];
  uVar1 = uVar21 + 0x5a827999 +
          ((uVar10 ^ uVar9) & uVar11 ^ uVar9) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar22;
  uVar21 = uVar11 * 0x40000000 | uVar11 >> 2;
  uVar23 = (uint)in_EAX[0x2c] << 0x18 | (uint)in_EAX[0x2d] << 0x10 | (uint)in_EAX[0x2e] << 8 |
           (uint)in_EAX[0x2f];
  uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar9 = ((uVar10 ^ uVar21) & uVar2 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar14 +
          0x5a827999 + uVar9;
  uVar15 = (uint)in_EAX[0x30] << 0x18 | (uint)in_EAX[0x31] << 0x10 | (uint)in_EAX[0x32] << 8 |
           (uint)in_EAX[0x33];
  uVar10 = ((uVar21 ^ uVar11) & uVar1 ^ uVar21) + (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar23 +
           0x5a827999 + uVar10;
  uVar1 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar24 = (uint)in_EAX[0x34] << 0x18 | (uint)in_EAX[0x35] << 0x10 | (uint)in_EAX[0x36] << 8 |
           (uint)in_EAX[0x37];
  uVar21 = ((uVar11 ^ uVar1) & uVar9 ^ uVar11) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar15 +
           0x5a827999 + uVar21;
  uVar2 = uVar9 * 0x40000000 | uVar9 >> 2;
  uVar16 = (uint)in_EAX[0x38] << 0x18 | (uint)in_EAX[0x39] << 0x10 | (uint)in_EAX[0x3a] << 8 |
           (uint)in_EAX[0x3b];
  uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar11 = ((uVar1 ^ uVar2) & uVar10 ^ uVar1) + (uVar21 * 0x20 | uVar21 >> 0x1b) + uVar24 +
           0x5a827999 + uVar11;
  uVar17 = (uint)in_EAX[0x3c] << 0x18 | (uint)in_EAX[0x3d] << 0x10 | (uint)in_EAX[0x3e] << 8 |
           (uint)in_EAX[0x3f];
  uVar1 = uVar1 + 0x5a827999 +
          ((uVar2 ^ uVar9) & uVar21 ^ uVar2) + (uVar11 * 0x20 | uVar11 >> 0x1b) + uVar16;
  uVar21 = uVar21 * 0x40000000 | uVar21 >> 2;
  uVar2 = ((uVar21 ^ uVar9) & uVar11 ^ uVar9) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar17 + 0x5a827999
          + uVar2;
  uVar11 = uVar11 * 0x40000000 | uVar11 >> 2;
  uVar8 = uVar24 ^ uVar13 ^ uVar3 ^ uVar8;
  uVar10 = uVar8 + 0x5a827999 +
           ((uVar21 ^ uVar11) & uVar1 ^ uVar21) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar20 = uVar16 ^ uVar22 ^ uVar4 ^ uVar20;
  uVar1 = uVar20 + 0x5a827999 +
          ((uVar11 ^ uVar9) & uVar2 ^ uVar11) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21;
  uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar3 = uVar14 ^ uVar5 ^ uVar3 ^ uVar17;
  uVar2 = uVar3 + 0x5a827999 +
          ((uVar9 ^ uVar21) & uVar10 ^ uVar9) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
  uVar11 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar4 = uVar23 ^ uVar6 ^ uVar4 ^ uVar8;
  uVar10 = uVar4 + 0x5a827999 +
           ((uVar21 ^ uVar11) & uVar1 ^ uVar21) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar5 = uVar15 ^ uVar12 ^ uVar5 ^ uVar20;
  uVar1 = uVar5 + 0x6ed9eba1 + (uVar2 ^ uVar11 ^ uVar9) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21;
  uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar6 = uVar24 ^ uVar7 ^ uVar6 ^ uVar3;
  uVar2 = uVar6 + 0x6ed9eba1 + (uVar21 ^ uVar10 ^ uVar9) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
  uVar11 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar12 = uVar16 ^ uVar13 ^ uVar12 ^ uVar4;
  uVar10 = uVar12 + 0x6ed9eba1 + (uVar21 ^ uVar11 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar7 = uVar22 ^ uVar7 ^ uVar5 ^ uVar17;
  uVar1 = uVar7 + 0x6ed9eba1 + (uVar11 ^ uVar9 ^ uVar2) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21;
  uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar13 = uVar14 ^ uVar13 ^ uVar6 ^ uVar8;
  uVar2 = uVar13 + 0x6ed9eba1 + (uVar9 ^ uVar21 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
  uVar11 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar22 = uVar23 ^ uVar22 ^ uVar12 ^ uVar20;
  uVar10 = uVar22 + 0x6ed9eba1 + (uVar21 ^ uVar11 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar14 = uVar15 ^ uVar14 ^ uVar7 ^ uVar3;
  uVar1 = uVar14 + 0x6ed9eba1 + (uVar2 ^ uVar11 ^ uVar9) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21
  ;
  uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar23 = uVar24 ^ uVar23 ^ uVar13 ^ uVar4;
  uVar2 = uVar23 + 0x6ed9eba1 + (uVar21 ^ uVar10 ^ uVar9) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
  uVar11 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar15 = uVar16 ^ uVar15 ^ uVar22 ^ uVar5;
  uVar10 = uVar15 + 0x6ed9eba1 + (uVar21 ^ uVar11 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar25 = uVar24 ^ uVar14 ^ uVar6 ^ uVar17;
  uVar24 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = uVar25 + 0x6ed9eba1 +
          (uVar11 ^ uVar24 ^ uVar2) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21;
  uVar21 = uVar16 ^ uVar23 ^ uVar12 ^ uVar8;
  uVar2 = uVar21 + 0x6ed9eba1 + (uVar24 ^ uVar9 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
  uVar11 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar17 = uVar15 ^ uVar7 ^ uVar20 ^ uVar17;
  uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar17 + 0x6ed9eba1 + (uVar9 ^ uVar11 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar24;
  uVar8 = uVar25 ^ uVar13 ^ uVar3 ^ uVar8;
  uVar24 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar10 = uVar8 + 0x6ed9eba1 + (uVar2 ^ uVar11 ^ uVar16) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar9;
  uVar20 = uVar21 ^ uVar22 ^ uVar4 ^ uVar20;
  uVar18 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar20 + 0x6ed9eba1 +
          (uVar24 ^ uVar1 ^ uVar16) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar11;
  uVar3 = uVar17 ^ uVar14 ^ uVar5 ^ uVar3;
  uVar2 = uVar3 + 0x6ed9eba1 + (uVar24 ^ uVar18 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16;
  uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar11 = uVar23 ^ uVar6 ^ uVar4 ^ uVar8;
  uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar11 + 0x6ed9eba1 + (uVar18 ^ uVar9 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar24;
  uVar24 = uVar15 ^ uVar12 ^ uVar5 ^ uVar20;
  uVar4 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar10 = uVar24 + 0x6ed9eba1 + (uVar9 ^ uVar16 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar18;
  uVar5 = uVar25 ^ uVar7 ^ uVar6 ^ uVar3;
  uVar18 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar5 + 0x6ed9eba1 + (uVar16 ^ uVar4 ^ uVar1) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
  uVar19 = uVar21 ^ uVar13 ^ uVar12 ^ uVar11;
  uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar10 = uVar19 + 0x6ed9eba1 + (uVar10 ^ uVar4 ^ uVar18) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16
  ;
  uVar6 = uVar17 ^ uVar22 ^ uVar7 ^ uVar24;
  uVar2 = uVar6 + 0x6ed9eba1 + (uVar9 ^ uVar1 ^ uVar18) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar4;
  uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar12 = uVar14 ^ uVar13 ^ uVar5 ^ uVar8;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar4 | uVar10) & uVar9 | uVar4 & uVar10) + uVar18 + uVar12;
  uVar7 = uVar23 ^ uVar22 ^ uVar19 ^ uVar20;
  uVar16 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar16 | uVar2) & uVar4 | uVar16 & uVar2) + uVar9 + uVar7;
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar13 = uVar15 ^ uVar14 ^ uVar6 ^ uVar3;
  uVar2 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
          ((uVar9 | uVar1) & uVar16 | uVar9 & uVar1) + uVar4 + uVar13;
  uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar22 = uVar25 ^ uVar23 ^ uVar12 ^ uVar11;
  uVar14 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar4 | uVar10) & uVar9 | uVar4 & uVar10) + uVar16 + uVar22;
  uVar23 = uVar21 ^ uVar15 ^ uVar7 ^ uVar24;
  uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar2 | uVar14) & uVar4 | uVar2 & uVar14) + uVar9 + uVar23;
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar15 = uVar17 ^ uVar25 ^ uVar13 ^ uVar5;
  uVar2 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
          ((uVar9 | uVar1) & uVar14 | uVar9 & uVar1) + uVar4 + uVar15;
  uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar18 = uVar21 ^ uVar22 ^ uVar19 ^ uVar8;
  uVar1 = ((uVar4 | uVar10) & uVar9 | uVar4 & uVar10) + uVar14 + uVar18 + -0x70e44324 +
          (uVar2 * 0x20 | uVar2 >> 0x1b);
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar14 = uVar17 ^ uVar23 ^ uVar6 ^ uVar20;
  uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar21 | uVar2) & uVar4 | uVar21 & uVar2) + uVar9 + uVar14;
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar8 = uVar15 ^ uVar12 ^ uVar3 ^ uVar8;
  uVar2 = ((uVar9 | uVar1) & uVar21 | uVar9 & uVar1) + uVar4 + uVar8 + -0x70e44324 +
          (uVar10 * 0x20 | uVar10 >> 0x1b);
  uVar20 = uVar18 ^ uVar7 ^ uVar11 ^ uVar20;
  uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar4 | uVar10) & uVar9 | uVar4 & uVar10) + uVar21 + uVar20;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar3 = uVar14 ^ uVar13 ^ uVar24 ^ uVar3;
  uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar2 | uVar21) & uVar4 | uVar2 & uVar21) + uVar9 + uVar3;
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar11 = uVar22 ^ uVar5 ^ uVar11 ^ uVar8;
  uVar2 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
          ((uVar9 | uVar1) & uVar21 | uVar9 & uVar1) + uVar4 + uVar11;
  uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar17 = uVar23 ^ uVar19 ^ uVar24 ^ uVar20;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar4 | uVar10) & uVar9 | uVar4 & uVar10) + uVar21 + uVar17;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar5 = uVar15 ^ uVar6 ^ uVar5 ^ uVar3;
  uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar21 | uVar2) & uVar4 | uVar21 & uVar2) + uVar9 + uVar5;
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar24 = uVar18 ^ uVar12 ^ uVar19 ^ uVar11;
  uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
          ((uVar9 | uVar1) & uVar21 | uVar9 & uVar1) + uVar4 + uVar24;
  uVar4 = uVar14 ^ uVar7 ^ uVar6 ^ uVar17;
  uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
          ((uVar16 | uVar10) & uVar9 | uVar16 & uVar10) + uVar21 + uVar4;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar6 = uVar13 ^ uVar12 ^ uVar5 ^ uVar8;
  uVar10 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
           ((uVar1 | uVar21) & uVar16 | uVar1 & uVar21) + uVar9 + uVar6;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar12 = uVar22 ^ uVar7 ^ uVar24 ^ uVar20;
  uVar7 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
          ((uVar9 | uVar2) & uVar21 | uVar9 & uVar2) + uVar16 + uVar12;
  uVar13 = uVar23 ^ uVar13 ^ uVar4 ^ uVar3;
  uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
          ((uVar7 | uVar10) & uVar9 | uVar7 & uVar10) + uVar21 + uVar13;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar22 = uVar15 ^ uVar22 ^ uVar6 ^ uVar11;
  uVar10 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
           ((uVar21 | uVar1) & uVar7 | uVar21 & uVar1) + uVar9 + uVar22;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar23 = uVar18 ^ uVar23 ^ uVar12 ^ uVar17;
  uVar16 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = (uVar21 ^ uVar9 ^ uVar2) + uVar23 + -0x359d3e2a + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar7
  ;
  uVar7 = uVar14 ^ uVar15 ^ uVar13 ^ uVar5;
  uVar2 = (uVar9 ^ uVar16 ^ uVar10) + uVar7 + -0x359d3e2a + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar15 = uVar18 ^ uVar22 ^ uVar24 ^ uVar8;
  uVar10 = (uVar1 ^ uVar16 ^ uVar21) + uVar15 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9
  ;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar14 = uVar14 ^ uVar23 ^ uVar4 ^ uVar20;
  uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar16 + -0x359d3e2a +
          (uVar9 ^ uVar2 ^ uVar21) + uVar14;
  uVar16 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar8 = uVar8 ^ uVar7 ^ uVar6 ^ uVar3;
  uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21 + -0x359d3e2a + (uVar9 ^ uVar16 ^ uVar10) + uVar8;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar20 = uVar20 ^ uVar15 ^ uVar12 ^ uVar11;
  uVar10 = (uVar16 ^ uVar21 ^ uVar1) + uVar9 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar20
  ;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar3 = uVar3 ^ uVar14 ^ uVar13 ^ uVar17;
  uVar1 = (uVar21 ^ uVar9 ^ uVar2) + uVar3 + -0x359d3e2a + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar16
  ;
  uVar16 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar18 = uVar22 ^ uVar5 ^ uVar11 ^ uVar8;
  uVar2 = (uVar9 ^ uVar16 ^ uVar10) + uVar18 + -0x359d3e2a + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21
  ;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar19 = uVar23 ^ uVar24 ^ uVar17 ^ uVar20;
  uVar10 = (uVar1 ^ uVar16 ^ uVar21) + uVar19 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9
  ;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar5 = uVar7 ^ uVar4 ^ uVar5 ^ uVar3;
  uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar16 + -0x359d3e2a + (uVar9 ^ uVar2 ^ uVar21) + uVar5
  ;
  uVar17 = uVar15 ^ uVar6 ^ uVar24 ^ uVar18;
  uVar2 = (uVar9 ^ uVar11 ^ uVar10) + uVar17 + -0x359d3e2a + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21
  ;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar4 = uVar14 ^ uVar12 ^ uVar4 ^ uVar19;
  uVar10 = (uVar11 ^ uVar21 ^ uVar1) + uVar4 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar6 = uVar13 ^ uVar6 ^ uVar5 ^ uVar8;
  uVar1 = (uVar21 ^ uVar9 ^ uVar2) + uVar6 + -0x359d3e2a + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar11
  ;
  uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar12 = uVar22 ^ uVar12 ^ uVar17 ^ uVar20;
  uVar2 = (uVar9 ^ uVar11 ^ uVar10) + uVar12 + -0x359d3e2a + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21
  ;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar3 = uVar23 ^ uVar13 ^ uVar4 ^ uVar3;
  uVar10 = (uVar1 ^ uVar11 ^ uVar21) + uVar3 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar18 = uVar7 ^ uVar22 ^ uVar6 ^ uVar18;
  uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar11 + -0x359d3e2a +
          (uVar9 ^ uVar2 ^ uVar21) + uVar18;
  uVar6 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar19 = uVar15 ^ uVar23 ^ uVar12 ^ uVar19;
  uVar2 = (uVar9 ^ uVar6 ^ uVar10) + uVar19 + -0x359d3e2a + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21;
  uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
  uVar11 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9 + -0x359d3e2a +
          (uVar14 ^ uVar7 ^ uVar3 ^ uVar5) + (uVar6 ^ uVar21 ^ uVar1);
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar10 = (uVar15 ^ uVar18 ^ uVar17 ^ uVar8) + (uVar21 ^ uVar11 ^ uVar2) + -0x359d3e2a +
           (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar6;
  *param_1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21 + -0x359d3e2a +
             (uVar11 ^ uVar9 ^ uVar1) + (uVar14 ^ uVar19 ^ uVar4 ^ uVar20) + *param_1;
  param_1[1] = param_1[1] + uVar10;
  param_1[3] = param_1[3] + uVar9;
  param_1[4] = param_1[4] + uVar11;
  param_2 = param_2 + -1;
  param_1[2] = (uVar1 * 0x40000000 | uVar1 >> 2) + param_1[2];
  if (0 < param_2) {
    do {
      uVar2 = *param_1;
      uVar10 = param_1[1];
      uVar8 = (uint)in_EAX[0x40] << 0x18 | (uint)in_EAX[0x41] << 0x10 | (uint)in_EAX[0x42] << 8 |
              (uint)in_EAX[0x43];
      uVar20 = (uint)in_EAX[0x44] << 0x18 | (uint)in_EAX[0x45] << 0x10 | (uint)in_EAX[0x46] << 8 |
               (uint)in_EAX[0x47];
      uVar1 = (uVar2 << 5 | uVar2 >> 0x1b) + ((param_1[3] ^ param_1[2]) & uVar10 ^ param_1[3]) +
              param_1[4] + 0x5a827999 + uVar8;
      uVar9 = uVar10 << 0x1e | uVar10 >> 2;
      uVar4 = (uint)in_EAX[0x48] << 0x18 | (uint)in_EAX[0x49] << 0x10 | (uint)in_EAX[0x4a] << 8 |
              (uint)in_EAX[0x4b];
      uVar10 = ((param_1[2] ^ uVar9) & uVar2 ^ param_1[2]) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar20
               + 0x5a827999 + param_1[3];
      uVar21 = uVar2 << 0x1e | uVar2 >> 2;
      uVar6 = (uint)in_EAX[0x4c] << 0x18 | (uint)in_EAX[0x4d] << 0x10 | (uint)in_EAX[0x4e] << 8 |
              (uint)in_EAX[0x4f];
      uVar2 = ((uVar9 ^ uVar21) & uVar1 ^ uVar9) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar4 +
              0x5a827999 + param_1[2];
      uVar1 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar5 = (uint)in_EAX[0x50] << 0x18 | (uint)in_EAX[0x51] << 0x10 | (uint)in_EAX[0x52] << 8 |
              (uint)in_EAX[0x53];
      uVar11 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar9 = ((uVar1 ^ uVar21) & uVar10 ^ uVar21) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar6 +
              0x5a827999 + uVar9;
      uVar7 = (uint)in_EAX[0x54] << 0x18 | (uint)in_EAX[0x55] << 0x10 | (uint)in_EAX[0x56] << 8 |
              (uint)in_EAX[0x57];
      uVar21 = ((uVar1 ^ uVar11) & uVar2 ^ uVar1) + (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar5 +
               0x5a827999 + uVar21;
      uVar10 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar12 = (uint)in_EAX[0x58] << 0x18 | (uint)in_EAX[0x59] << 0x10 | (uint)in_EAX[0x5a] << 8 |
               (uint)in_EAX[0x5b];
      uVar1 = ((uVar11 ^ uVar10) & uVar9 ^ uVar11) + (uVar21 * 0x20 | uVar21 >> 0x1b) + uVar7 +
              0x5a827999 + uVar1;
      uVar2 = uVar9 * 0x40000000 | uVar9 >> 2;
      uVar22 = (uint)in_EAX[0x5c] << 0x18 | (uint)in_EAX[0x5d] << 0x10 | (uint)in_EAX[0x5e] << 8 |
               (uint)in_EAX[0x5f];
      uVar9 = uVar21 * 0x40000000 | uVar21 >> 2;
      uVar11 = ((uVar10 ^ uVar2) & uVar21 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar12 +
               0x5a827999 + uVar11;
      uVar13 = (uint)in_EAX[0x60] << 0x18 | (uint)in_EAX[0x61] << 0x10 | (uint)in_EAX[0x62] << 8 |
               (uint)in_EAX[99];
      uVar10 = ((uVar2 ^ uVar9) & uVar1 ^ uVar2) + (uVar11 * 0x20 | uVar11 >> 0x1b) + uVar22 +
               0x5a827999 + uVar10;
      uVar1 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar23 = (uint)in_EAX[100] << 0x18 | (uint)in_EAX[0x65] << 0x10 | (uint)in_EAX[0x66] << 8 |
               (uint)in_EAX[0x67];
      uVar2 = ((uVar9 ^ uVar1) & uVar11 ^ uVar9) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar13 +
              0x5a827999 + uVar2;
      uVar21 = uVar11 * 0x40000000 | uVar11 >> 2;
      uVar14 = (uint)in_EAX[0x68] << 0x18 | (uint)in_EAX[0x69] << 0x10 | (uint)in_EAX[0x6a] << 8 |
               (uint)in_EAX[0x6b];
      uVar11 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar9 = ((uVar21 ^ uVar1) & uVar10 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar23 +
              0x5a827999 + uVar9;
      uVar24 = (uint)in_EAX[0x6c] << 0x18 | (uint)in_EAX[0x6d] << 0x10 | (uint)in_EAX[0x6e] << 8 |
               (uint)in_EAX[0x6f];
      uVar1 = ((uVar21 ^ uVar11) & uVar2 ^ uVar21) + (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar14 +
              0x5a827999 + uVar1;
      uVar10 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar15 = (uint)in_EAX[0x70] << 0x18 | (uint)in_EAX[0x71] << 0x10 | (uint)in_EAX[0x72] << 8 |
               (uint)in_EAX[0x73];
      uVar21 = ((uVar11 ^ uVar10) & uVar9 ^ uVar11) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar24 +
               0x5a827999 + uVar21;
      uVar2 = uVar9 * 0x40000000 | uVar9 >> 2;
      uVar18 = (uint)in_EAX[0x74] << 0x18 | (uint)in_EAX[0x75] << 0x10 | (uint)in_EAX[0x76] << 8 |
               (uint)in_EAX[0x77];
      uVar11 = ((uVar10 ^ uVar2) & uVar1 ^ uVar10) + (uVar21 * 0x20 | uVar21 >> 0x1b) + uVar15 +
               0x5a827999 + uVar11;
      uVar1 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar16 = (uint)in_EAX[0x78] << 0x18 | (uint)in_EAX[0x79] << 0x10 | (uint)in_EAX[0x7a] << 8 |
               (uint)in_EAX[0x7b];
      uVar10 = ((uVar2 ^ uVar1) & uVar21 ^ uVar2) + (uVar11 * 0x20 | uVar11 >> 0x1b) + uVar18 +
               0x5a827999 + uVar10;
      uVar3 = uVar21 * 0x40000000 | uVar21 >> 2;
      uVar17 = (uint)in_EAX[0x7c] << 0x18 | (uint)in_EAX[0x7d] << 0x10 | (uint)in_EAX[0x7e] << 8 |
               (uint)in_EAX[0x7f];
      uVar2 = ((uVar1 ^ uVar3) & uVar11 ^ uVar1) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar16 +
              0x5a827999 + uVar2;
      uVar9 = uVar11 * 0x40000000 | uVar11 >> 2;
      uVar1 = ((uVar9 ^ uVar3) & uVar10 ^ uVar3) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar17 +
              0x5a827999 + uVar1;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar8 = uVar18 ^ uVar13 ^ uVar4 ^ uVar8;
      uVar10 = uVar8 + 0x5a827999 +
               ((uVar9 ^ uVar21) & uVar2 ^ uVar9) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
      uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar20 = uVar16 ^ uVar23 ^ uVar6 ^ uVar20;
      uVar2 = uVar20 + 0x5a827999 +
              ((uVar21 ^ uVar11) & uVar1 ^ uVar21) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar3 = uVar14 ^ uVar5 ^ uVar4 ^ uVar17;
      uVar1 = uVar3 + 0x5a827999 +
              ((uVar11 ^ uVar9) & uVar10 ^ uVar11) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar21;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar4 = uVar24 ^ uVar7 ^ uVar6 ^ uVar8;
      uVar10 = uVar4 + 0x5a827999 +
               ((uVar9 ^ uVar21) & uVar2 ^ uVar9) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
      uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar5 = uVar15 ^ uVar12 ^ uVar5 ^ uVar20;
      uVar2 = uVar5 + 0x6ed9eba1 +
              (uVar1 ^ uVar21 ^ uVar11) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar6 = uVar18 ^ uVar22 ^ uVar7 ^ uVar3;
      uVar1 = uVar6 + 0x6ed9eba1 +
              (uVar9 ^ uVar10 ^ uVar11) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar21;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar12 = uVar16 ^ uVar13 ^ uVar12 ^ uVar4;
      uVar10 = uVar12 + 0x6ed9eba1 +
               (uVar9 ^ uVar21 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
      uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar7 = uVar23 ^ uVar22 ^ uVar5 ^ uVar17;
      uVar2 = uVar7 + 0x6ed9eba1 +
              (uVar21 ^ uVar11 ^ uVar1) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar13 = uVar14 ^ uVar13 ^ uVar6 ^ uVar8;
      uVar1 = uVar13 + 0x6ed9eba1 +
              (uVar11 ^ uVar9 ^ uVar10) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar21;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar22 = uVar24 ^ uVar23 ^ uVar12 ^ uVar20;
      uVar10 = uVar22 + 0x6ed9eba1 +
               (uVar9 ^ uVar21 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
      uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar14 = uVar15 ^ uVar14 ^ uVar7 ^ uVar3;
      uVar2 = uVar14 + 0x6ed9eba1 +
              (uVar1 ^ uVar21 ^ uVar11) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar23 = uVar18 ^ uVar24 ^ uVar13 ^ uVar4;
      uVar1 = uVar23 + 0x6ed9eba1 +
              (uVar9 ^ uVar10 ^ uVar11) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar21;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar15 = uVar16 ^ uVar15 ^ uVar22 ^ uVar5;
      uVar10 = uVar15 + 0x6ed9eba1 +
               (uVar9 ^ uVar21 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
      uVar25 = uVar18 ^ uVar14 ^ uVar6 ^ uVar17;
      uVar24 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar11 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar25 + 0x6ed9eba1 +
              (uVar21 ^ uVar24 ^ uVar1) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar9 = uVar16 ^ uVar23 ^ uVar12 ^ uVar8;
      uVar2 = uVar9 + 0x6ed9eba1 +
              (uVar24 ^ uVar11 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar17 = uVar15 ^ uVar7 ^ uVar20 ^ uVar17;
      uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar17 + 0x6ed9eba1 +
              (uVar11 ^ uVar21 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar24;
      uVar8 = uVar25 ^ uVar13 ^ uVar3 ^ uVar8;
      uVar24 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar10 = uVar8 + 0x6ed9eba1 +
               (uVar2 ^ uVar21 ^ uVar16) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
      uVar20 = uVar9 ^ uVar22 ^ uVar4 ^ uVar20;
      uVar18 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar20 + 0x6ed9eba1 +
              (uVar24 ^ uVar1 ^ uVar16) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21;
      uVar3 = uVar17 ^ uVar14 ^ uVar5 ^ uVar3;
      uVar2 = uVar3 + 0x6ed9eba1 +
              (uVar24 ^ uVar18 ^ uVar10) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar11 = uVar23 ^ uVar6 ^ uVar4 ^ uVar8;
      uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar11 + 0x6ed9eba1 +
              (uVar18 ^ uVar21 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar24;
      uVar24 = uVar15 ^ uVar12 ^ uVar5 ^ uVar20;
      uVar4 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar10 = uVar24 + 0x6ed9eba1 +
               (uVar21 ^ uVar16 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar18;
      uVar5 = uVar25 ^ uVar7 ^ uVar6 ^ uVar3;
      uVar18 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar5 + 0x6ed9eba1 +
              (uVar16 ^ uVar4 ^ uVar1) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar21;
      uVar19 = uVar9 ^ uVar13 ^ uVar12 ^ uVar11;
      uVar21 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar10 = uVar19 + 0x6ed9eba1 +
               (uVar10 ^ uVar4 ^ uVar18) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16;
      uVar6 = uVar17 ^ uVar22 ^ uVar7 ^ uVar24;
      uVar2 = uVar6 + 0x6ed9eba1 +
              (uVar21 ^ uVar1 ^ uVar18) + (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar4;
      uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar12 = uVar14 ^ uVar13 ^ uVar5 ^ uVar8;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
              ((uVar4 | uVar10) & uVar21 | uVar4 & uVar10) + uVar18 + uVar12;
      uVar7 = uVar23 ^ uVar22 ^ uVar19 ^ uVar20;
      uVar16 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
               ((uVar16 | uVar2) & uVar4 | uVar16 & uVar2) + uVar21 + uVar7;
      uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar13 = uVar15 ^ uVar14 ^ uVar6 ^ uVar3;
      uVar2 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
              ((uVar21 | uVar1) & uVar16 | uVar21 & uVar1) + uVar4 + uVar13;
      uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar22 = uVar25 ^ uVar23 ^ uVar12 ^ uVar11;
      uVar14 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
              ((uVar4 | uVar10) & uVar21 | uVar4 & uVar10) + uVar16 + uVar22;
      uVar23 = uVar9 ^ uVar15 ^ uVar7 ^ uVar24;
      uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
               ((uVar2 | uVar14) & uVar4 | uVar2 & uVar14) + uVar21 + uVar23;
      uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar15 = uVar17 ^ uVar25 ^ uVar13 ^ uVar5;
      uVar2 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
              ((uVar21 | uVar1) & uVar14 | uVar21 & uVar1) + uVar4 + uVar15;
      uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar18 = uVar9 ^ uVar22 ^ uVar19 ^ uVar8;
      uVar1 = ((uVar4 | uVar10) & uVar21 | uVar4 & uVar10) + uVar14 + uVar18 + -0x70e44324 +
              (uVar2 * 0x20 | uVar2 >> 0x1b);
      uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar14 = uVar17 ^ uVar23 ^ uVar6 ^ uVar20;
      uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
               ((uVar9 | uVar2) & uVar4 | uVar9 & uVar2) + uVar21 + uVar14;
      uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar8 = uVar15 ^ uVar12 ^ uVar3 ^ uVar8;
      uVar2 = ((uVar21 | uVar1) & uVar9 | uVar21 & uVar1) + uVar4 + uVar8 + -0x70e44324 +
              (uVar10 * 0x20 | uVar10 >> 0x1b);
      uVar20 = uVar18 ^ uVar7 ^ uVar11 ^ uVar20;
      uVar17 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
              ((uVar17 | uVar10) & uVar21 | uVar17 & uVar10) + uVar9 + uVar20;
      uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar3 = uVar14 ^ uVar13 ^ uVar24 ^ uVar3;
      uVar4 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
               ((uVar2 | uVar9) & uVar17 | uVar2 & uVar9) + uVar21 + uVar3;
      uVar21 = uVar22 ^ uVar5 ^ uVar11 ^ uVar8;
      uVar2 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
              ((uVar4 | uVar1) & uVar9 | uVar4 & uVar1) + uVar17 + uVar21;
      uVar11 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar17 = uVar23 ^ uVar19 ^ uVar24 ^ uVar20;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
              ((uVar11 | uVar10) & uVar4 | uVar11 & uVar10) + uVar9 + uVar17;
      uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar5 = uVar15 ^ uVar6 ^ uVar5 ^ uVar3;
      uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
               ((uVar9 | uVar2) & uVar11 | uVar9 & uVar2) + uVar4 + uVar5;
      uVar4 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar24 = uVar18 ^ uVar12 ^ uVar19 ^ uVar21;
      uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
              ((uVar4 | uVar1) & uVar9 | uVar4 & uVar1) + uVar11 + uVar24;
      uVar11 = uVar14 ^ uVar7 ^ uVar6 ^ uVar17;
      uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
              ((uVar16 | uVar10) & uVar4 | uVar16 & uVar10) + uVar9 + uVar11;
      uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar6 = uVar13 ^ uVar12 ^ uVar5 ^ uVar8;
      uVar10 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
               ((uVar1 | uVar9) & uVar16 | uVar1 & uVar9) + uVar4 + uVar6;
      uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar12 = uVar22 ^ uVar7 ^ uVar24 ^ uVar20;
      uVar7 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + 0x8f1bbcdc +
              ((uVar4 | uVar2) & uVar9 | uVar4 & uVar2) + uVar16 + uVar12;
      uVar13 = uVar23 ^ uVar13 ^ uVar11 ^ uVar3;
      uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
              ((uVar7 | uVar10) & uVar4 | uVar7 & uVar10) + uVar9 + uVar13;
      uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar22 = uVar15 ^ uVar22 ^ uVar6 ^ uVar21;
      uVar10 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
               ((uVar9 | uVar1) & uVar7 | uVar9 & uVar1) + uVar4 + uVar22;
      uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar23 = uVar18 ^ uVar23 ^ uVar12 ^ uVar17;
      uVar16 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar1 = (uVar9 ^ uVar4 ^ uVar2) + uVar23 + -0x359d3e2a +
              (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar7;
      uVar7 = uVar14 ^ uVar15 ^ uVar13 ^ uVar5;
      uVar2 = (uVar4 ^ uVar16 ^ uVar10) + uVar7 + -0x359d3e2a +
              (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar9;
      uVar9 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar15 = uVar18 ^ uVar22 ^ uVar24 ^ uVar8;
      uVar10 = (uVar1 ^ uVar16 ^ uVar9) + uVar15 + -0x359d3e2a +
               (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar4;
      uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar14 = uVar14 ^ uVar23 ^ uVar11 ^ uVar20;
      uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar16 + -0x359d3e2a +
              (uVar4 ^ uVar2 ^ uVar9) + uVar14;
      uVar16 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar8 = uVar8 ^ uVar7 ^ uVar6 ^ uVar3;
      uVar18 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar10 = (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar9 + -0x359d3e2a +
               (uVar4 ^ uVar16 ^ uVar10) + uVar8;
      uVar20 = uVar20 ^ uVar15 ^ uVar12 ^ uVar21;
      uVar2 = (uVar16 ^ uVar18 ^ uVar1) + uVar4 + -0x359d3e2a +
              (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar20;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar3 = uVar3 ^ uVar14 ^ uVar13 ^ uVar17;
      uVar1 = (uVar18 ^ uVar9 ^ uVar10) + uVar3 + -0x359d3e2a +
              (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar16;
      uVar4 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar16 = uVar22 ^ uVar5 ^ uVar21 ^ uVar8;
      uVar10 = (uVar9 ^ uVar4 ^ uVar2) + uVar16 + -0x359d3e2a +
               (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar18;
      uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar18 = uVar23 ^ uVar24 ^ uVar17 ^ uVar20;
      uVar2 = (uVar1 ^ uVar4 ^ uVar21) + uVar18 + -0x359d3e2a +
              (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar5 = uVar7 ^ uVar11 ^ uVar5 ^ uVar3;
      uVar17 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar4 + -0x359d3e2a +
              (uVar9 ^ uVar10 ^ uVar21) + uVar5;
      uVar4 = uVar15 ^ uVar6 ^ uVar24 ^ uVar16;
      uVar10 = (uVar9 ^ uVar17 ^ uVar2) + uVar4 + -0x359d3e2a +
               (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21;
      uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar11 = uVar14 ^ uVar12 ^ uVar11 ^ uVar18;
      uVar2 = (uVar17 ^ uVar21 ^ uVar1) + uVar11 + -0x359d3e2a +
              (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar6 = uVar13 ^ uVar6 ^ uVar5 ^ uVar8;
      uVar1 = (uVar21 ^ uVar9 ^ uVar10) + uVar6 + -0x359d3e2a +
              (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar17;
      uVar17 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar12 = uVar22 ^ uVar12 ^ uVar4 ^ uVar20;
      uVar10 = (uVar9 ^ uVar17 ^ uVar2) + uVar12 + -0x359d3e2a +
               (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21;
      uVar21 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar3 = uVar23 ^ uVar13 ^ uVar11 ^ uVar3;
      uVar2 = (uVar1 ^ uVar17 ^ uVar21) + uVar3 + -0x359d3e2a +
              (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar9;
      uVar13 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar16 = uVar7 ^ uVar22 ^ uVar6 ^ uVar16;
      uVar6 = uVar10 * 0x40000000 | uVar10 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar17 + -0x359d3e2a +
              (uVar13 ^ uVar10 ^ uVar21) + uVar16;
      uVar18 = uVar15 ^ uVar23 ^ uVar12 ^ uVar18;
      uVar10 = (uVar13 ^ uVar6 ^ uVar2) + uVar18 + -0x359d3e2a +
               (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21;
      uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar21 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar10 * 0x20 | uVar10 >> 0x1b) + uVar13 + -0x359d3e2a +
              (uVar14 ^ uVar7 ^ uVar3 ^ uVar5) + (uVar6 ^ uVar9 ^ uVar1);
      uVar2 = (uVar15 ^ uVar16 ^ uVar4 ^ uVar8) + (uVar9 ^ uVar21 ^ uVar10) + -0x359d3e2a +
              (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar6;
      uVar10 = uVar10 * 0x40000000 | uVar10 >> 2;
      *param_1 = *param_1 +
                 (uVar14 ^ uVar18 ^ uVar11 ^ uVar20) + (uVar21 ^ uVar10 ^ uVar1) + -0x359d3e2a +
                 (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
      param_1[1] = param_1[1] + uVar2;
      param_1[2] = param_1[2] + (uVar1 * 0x40000000 | uVar1 >> 2);
      param_1[3] = param_1[3] + uVar10;
      param_2 = param_2 + -1;
      param_1[4] = param_1[4] + uVar21;
      in_EAX = in_EAX + 0x40;
    } while (param_2 != 0);
  }
  return;
}

