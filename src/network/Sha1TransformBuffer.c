/* Sha1TransformBuffer - 0x004f76f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall Sha1TransformBuffer(undefined4 param_1,uint *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint *in_EAX;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
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
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  int local_8;
  
  uVar15 = *in_EAX;
  uVar2 = in_EAX[2];
  uVar1 = ((in_EAX[3] ^ uVar2) & in_EAX[1] ^ in_EAX[3]) + (uVar15 << 5 | uVar15 >> 0x1b) + in_EAX[4]
          + 0x5a827999 + *param_2;
  uVar3 = in_EAX[1] << 0x1e | in_EAX[1] >> 2;
  uVar2 = in_EAX[3] + 0x5a827999 +
          ((uVar2 ^ uVar3) & uVar15 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + param_2[1];
  uVar8 = uVar15 << 0x1e | uVar15 >> 2;
  puVar7 = param_2 + 2;
  uVar13 = *puVar7;
  uVar15 = ((uVar3 ^ uVar8) & uVar1 ^ uVar3) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar13 + 0x5a827999
           + in_EAX[2];
  uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar14 = param_2[3];
  uVar25 = param_2[4];
  uVar1 = uVar3 + 0x5a827999 +
          ((uVar16 ^ uVar8) & uVar2 ^ uVar8) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar14;
  uVar17 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar3 = param_2[5];
  uVar2 = uVar8 + 0x5a827999 +
          ((uVar16 ^ uVar17) & uVar15 ^ uVar16) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar25;
  uVar18 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar8 = param_2[6];
  uVar15 = uVar16 + 0x5a827999 +
           ((uVar17 ^ uVar18) & uVar1 ^ uVar17) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar3;
  uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar16 = param_2[7];
  uVar1 = uVar17 + 0x5a827999 +
          ((uVar18 ^ uVar4) & uVar2 ^ uVar18) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar8;
  uVar9 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar17 = param_2[8];
  uVar2 = uVar18 + 0x5a827999 +
          ((uVar4 ^ uVar9) & uVar15 ^ uVar4) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16;
  uVar19 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar18 = param_2[9];
  uVar5 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar4 + 0x5a827999 +
          ((uVar9 ^ uVar19) & uVar1 ^ uVar9) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar17;
  uVar15 = uVar9 + 0x5a827999 +
           ((uVar5 ^ uVar19) & uVar2 ^ uVar19) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar18;
  uVar4 = param_2[10];
  uVar10 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar9 = param_2[0xb];
  uVar2 = uVar19 + 0x5a827999 +
          ((uVar5 ^ uVar10) & uVar1 ^ uVar5) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar4;
  uVar20 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar19 = param_2[0xc];
  uVar1 = uVar5 + 0x5a827999 +
          ((uVar10 ^ uVar20) & uVar15 ^ uVar10) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar9;
  uVar6 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar15 = uVar10 + 0x5a827999 +
           ((uVar20 ^ uVar6) & uVar2 ^ uVar20) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar19;
  uVar5 = param_2[0xd];
  uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar2 = uVar20 + 0x5a827999 +
          ((uVar6 ^ uVar11) & uVar1 ^ uVar6) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar5;
  uVar10 = param_2[0xe];
  uVar21 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar6 + 0x5a827999 +
          ((uVar11 ^ uVar21) & uVar15 ^ uVar11) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar10;
  uVar6 = param_2[0xf];
  uVar20 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar15 = uVar11 + 0x5a827999 +
           ((uVar20 ^ uVar21) & uVar2 ^ uVar21) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar6;
  uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar12 = uVar5 ^ uVar17 ^ uVar13 ^ *param_2;
  uVar22 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar12 + 0x5a827999 +
          ((uVar20 ^ uVar11) & uVar1 ^ uVar20) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar21;
  uVar23 = uVar10 ^ uVar18 ^ uVar14 ^ param_2[1];
  uVar21 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar2 = uVar23 + 0x5a827999 +
          ((uVar11 ^ uVar22) & uVar15 ^ uVar11) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar20;
  uVar13 = uVar6 ^ uVar4 ^ uVar25 ^ uVar13;
  uVar15 = uVar13 + 0x5a827999 +
           ((uVar22 ^ uVar21) & uVar1 ^ uVar22) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar11;
  uVar11 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar24 = uVar9 ^ uVar3 ^ uVar14 ^ uVar12;
  uVar14 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = uVar24 + 0x5a827999 +
          ((uVar21 ^ uVar11) & uVar2 ^ uVar21) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar22;
  uVar20 = uVar19 ^ uVar8 ^ uVar25 ^ uVar23;
  uVar25 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar2 = uVar20 + 0x6ed9eba1 + (uVar15 ^ uVar11 ^ uVar14) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar21
  ;
  uVar21 = uVar5 ^ uVar16 ^ uVar3 ^ uVar13;
  uVar15 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar21 + 0x6ed9eba1 + (uVar25 ^ uVar1 ^ uVar14) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar11;
  uVar11 = uVar10 ^ uVar17 ^ uVar8 ^ uVar24;
  uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar2 = uVar11 + 0x6ed9eba1 + (uVar25 ^ uVar15 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar14;
  uVar26 = uVar6 ^ uVar18 ^ uVar16 ^ uVar20;
  uVar14 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar26 + 0x6ed9eba1 + (uVar15 ^ uVar3 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25;
  uVar17 = uVar4 ^ uVar17 ^ uVar21 ^ uVar12;
  uVar8 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar2 = uVar17 + 0x6ed9eba1 + (uVar3 ^ uVar14 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar15;
  uVar27 = uVar9 ^ uVar18 ^ uVar11 ^ uVar23;
  uVar15 = uVar27 + 0x6ed9eba1 + (uVar14 ^ uVar8 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar3;
  uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar18 = uVar19 ^ uVar4 ^ uVar26 ^ uVar13;
  uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = uVar18 + 0x6ed9eba1 + (uVar2 ^ uVar8 ^ uVar25) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar14
  ;
  uVar28 = uVar5 ^ uVar9 ^ uVar17 ^ uVar24;
  uVar2 = uVar28 + 0x6ed9eba1 + (uVar3 ^ uVar15 ^ uVar25) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar8;
  uVar8 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar9 = uVar10 ^ uVar19 ^ uVar27 ^ uVar20;
  uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar9 + 0x6ed9eba1 + (uVar3 ^ uVar8 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25;
  uVar29 = uVar6 ^ uVar5 ^ uVar18 ^ uVar21;
  uVar15 = uVar29 + 0x6ed9eba1 + (uVar8 ^ uVar16 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
  uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar14 = uVar10 ^ uVar28 ^ uVar11 ^ uVar12;
  uVar4 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar16 ^ uVar3 ^ uVar1) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar8 + 0x6ed9eba1 + uVar14;
  uVar25 = uVar6 ^ uVar9 ^ uVar26 ^ uVar23;
  uVar8 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar2 = uVar25 + 0x6ed9eba1 + (uVar3 ^ uVar4 ^ uVar15) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16;
  uVar12 = uVar29 ^ uVar17 ^ uVar13 ^ uVar12;
  uVar15 = uVar12 + 0x6ed9eba1 + (uVar1 ^ uVar4 ^ uVar8) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar3;
  uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar23 = uVar14 ^ uVar27 ^ uVar24 ^ uVar23;
  uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = uVar23 + 0x6ed9eba1 + (uVar16 ^ uVar2 ^ uVar8) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar4;
  uVar13 = uVar25 ^ uVar18 ^ uVar20 ^ uVar13;
  uVar4 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar2 = uVar13 + 0x6ed9eba1 + (uVar16 ^ uVar3 ^ uVar15) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar8;
  uVar19 = uVar28 ^ uVar21 ^ uVar24 ^ uVar12;
  uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = uVar19 + 0x6ed9eba1 + (uVar3 ^ uVar4 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar16;
  uVar16 = uVar9 ^ uVar11 ^ uVar20 ^ uVar23;
  uVar15 = uVar16 + 0x6ed9eba1 + (uVar4 ^ uVar8 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
  uVar5 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar22 = uVar29 ^ uVar26 ^ uVar21 ^ uVar13;
  uVar2 = uVar22 + 0x6ed9eba1 + (uVar8 ^ uVar5 ^ uVar1) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar4;
  uVar3 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar4 = uVar14 ^ uVar17 ^ uVar11 ^ uVar19;
  uVar6 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar1 = uVar4 + 0x6ed9eba1 + (uVar15 ^ uVar5 ^ uVar3) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar8;
  uVar24 = uVar25 ^ uVar27 ^ uVar26 ^ uVar16;
  uVar15 = uVar24 + 0x6ed9eba1 + (uVar6 ^ uVar2 ^ uVar3) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar5;
  uVar5 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar26 = uVar18 ^ uVar17 ^ uVar22 ^ uVar12;
  uVar2 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
          ((uVar5 | uVar1) & uVar6 | uVar5 & uVar1) + uVar3 + uVar26;
  uVar3 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar10 = uVar28 ^ uVar27 ^ uVar4 ^ uVar23;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar3 | uVar15) & uVar5 | uVar3 & uVar15) + uVar6 + uVar10;
  uVar8 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar6 = uVar9 ^ uVar18 ^ uVar24 ^ uVar13;
  uVar15 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar8 | uVar2) & uVar3 | uVar8 & uVar2) + uVar5 + uVar6;
  uVar17 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar20 = uVar29 ^ uVar28 ^ uVar26 ^ uVar19;
  uVar2 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
          ((uVar17 | uVar1) & uVar8 | uVar17 & uVar1) + uVar3 + uVar20;
  uVar3 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar11 = uVar14 ^ uVar9 ^ uVar10 ^ uVar16;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar15 | uVar3) & uVar17 | uVar15 & uVar3) + uVar8 + uVar11;
  uVar8 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar21 = uVar25 ^ uVar29 ^ uVar6 ^ uVar22;
  uVar15 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar8 | uVar2) & uVar3 | uVar8 & uVar2) + uVar17 + uVar21;
  uVar14 = uVar14 ^ uVar20 ^ uVar4 ^ uVar12;
  uVar18 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar2 = ((uVar18 | uVar1) & uVar8 | uVar18 & uVar1) + uVar3 + uVar14 + -0x70e44324 +
          (uVar15 * 0x20 | uVar15 >> 0x1b);
  uVar17 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar27 = uVar25 ^ uVar11 ^ uVar24 ^ uVar23;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar17 | uVar15) & uVar18 | uVar17 & uVar15) + uVar8 + uVar27;
  uVar3 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar12 = uVar21 ^ uVar26 ^ uVar13 ^ uVar12;
  uVar15 = ((uVar3 | uVar2) & uVar17 | uVar3 & uVar2) + uVar18 + uVar12 + -0x70e44324 +
           (uVar1 * 0x20 | uVar1 >> 0x1b);
  uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar23 = uVar14 ^ uVar10 ^ uVar19 ^ uVar23;
  uVar2 = ((uVar25 | uVar1) & uVar3 | uVar25 & uVar1) + uVar17 + uVar23 + -0x70e44324 +
          (uVar15 * 0x20 | uVar15 >> 0x1b);
  uVar13 = uVar27 ^ uVar6 ^ uVar16 ^ uVar13;
  uVar17 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar15 | uVar17) & uVar25 | uVar15 & uVar17) + uVar3 + uVar13;
  uVar3 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar8 = uVar20 ^ uVar22 ^ uVar19 ^ uVar12;
  uVar15 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar3 | uVar2) & uVar17 | uVar3 & uVar2) + uVar25 + uVar8;
  uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar16 = uVar11 ^ uVar4 ^ uVar16 ^ uVar23;
  uVar2 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
          ((uVar25 | uVar1) & uVar3 | uVar25 & uVar1) + uVar17 + uVar16;
  uVar17 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar18 = uVar21 ^ uVar24 ^ uVar22 ^ uVar13;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
          ((uVar17 | uVar15) & uVar25 | uVar17 & uVar15) + uVar3 + uVar18;
  uVar3 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar4 = uVar14 ^ uVar26 ^ uVar4 ^ uVar8;
  uVar15 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
           ((uVar3 | uVar2) & uVar17 | uVar3 & uVar2) + uVar25 + uVar4;
  uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar9 = uVar27 ^ uVar10 ^ uVar24 ^ uVar16;
  uVar19 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
          ((uVar25 | uVar1) & uVar3 | uVar25 & uVar1) + uVar17 + uVar9;
  uVar17 = uVar6 ^ uVar26 ^ uVar18 ^ uVar12;
  uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
          ((uVar15 | uVar19) & uVar25 | uVar15 & uVar19) + uVar3 + uVar17;
  uVar3 = uVar20 ^ uVar10 ^ uVar4 ^ uVar23;
  uVar15 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
           ((uVar5 | uVar1) & uVar19 | uVar5 & uVar1) + uVar25 + uVar3;
  uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar10 = uVar11 ^ uVar6 ^ uVar9 ^ uVar13;
  uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
          ((uVar25 | uVar2) & uVar5 | uVar25 & uVar2) + uVar19 + uVar10;
  uVar19 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar6 = uVar21 ^ uVar20 ^ uVar17 ^ uVar8;
  uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
          ((uVar19 | uVar15) & uVar25 | uVar19 & uVar15) + uVar5 + uVar6;
  uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar20 = uVar14 ^ uVar11 ^ uVar3 ^ uVar16;
  uVar11 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar19 ^ uVar5 ^ uVar1) + uVar20 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25;
  uVar21 = uVar27 ^ uVar21 ^ uVar10 ^ uVar18;
  uVar15 = (uVar5 ^ uVar11 ^ uVar2) + uVar21 + -0x359d3e2a + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar19
  ;
  uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar19 = uVar14 ^ uVar6 ^ uVar4 ^ uVar12;
  uVar2 = (uVar1 ^ uVar11 ^ uVar25) + uVar19 + -0x359d3e2a +
          (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar5;
  uVar14 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar5 = uVar27 ^ uVar20 ^ uVar9 ^ uVar23;
  uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar11 + -0x359d3e2a + (uVar14 ^ uVar15 ^ uVar25) + uVar5
  ;
  uVar11 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar12 = uVar12 ^ uVar21 ^ uVar17 ^ uVar13;
  uVar15 = (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar25 + -0x359d3e2a +
           (uVar14 ^ uVar11 ^ uVar2) + uVar12;
  uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar23 = uVar23 ^ uVar19 ^ uVar3 ^ uVar8;
  uVar22 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar14 + -0x359d3e2a +
          (uVar11 ^ uVar25 ^ uVar1) + uVar23;
  uVar13 = uVar13 ^ uVar5 ^ uVar10 ^ uVar16;
  uVar2 = (uVar25 ^ uVar22 ^ uVar15) + uVar13 + -0x359d3e2a +
          (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar11;
  uVar14 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar11 = uVar6 ^ uVar18 ^ uVar8 ^ uVar12;
  uVar15 = (uVar22 ^ uVar14 ^ uVar1) + uVar11 + -0x359d3e2a +
           (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25;
  uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar24 = uVar20 ^ uVar4 ^ uVar16 ^ uVar23;
  uVar1 = (uVar2 ^ uVar14 ^ uVar25) + uVar24 + -0x359d3e2a +
          (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar22;
  uVar8 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar16 = uVar21 ^ uVar9 ^ uVar18 ^ uVar13;
  uVar18 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar14 + -0x359d3e2a + (uVar8 ^ uVar15 ^ uVar25) + uVar16
  ;
  uVar4 = uVar19 ^ uVar17 ^ uVar4 ^ uVar11;
  uVar15 = (uVar8 ^ uVar18 ^ uVar1) + uVar4 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25;
  uVar14 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar9 = uVar5 ^ uVar3 ^ uVar9 ^ uVar24;
  uVar1 = (uVar18 ^ uVar14 ^ uVar2) + uVar9 + -0x359d3e2a + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar8
  ;
  uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar8 = uVar10 ^ uVar17 ^ uVar16 ^ uVar12;
  uVar2 = (uVar14 ^ uVar25 ^ uVar15) + uVar8 + -0x359d3e2a + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar18
  ;
  uVar17 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar3 = uVar6 ^ uVar3 ^ uVar4 ^ uVar23;
  uVar15 = (uVar25 ^ uVar17 ^ uVar1) + uVar3 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar14
  ;
  uVar14 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar13 = uVar20 ^ uVar10 ^ uVar9 ^ uVar13;
  uVar1 = (uVar2 ^ uVar17 ^ uVar14) + uVar13 + -0x359d3e2a +
          (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar25;
  uVar18 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar11 = uVar21 ^ uVar6 ^ uVar8 ^ uVar11;
  uVar8 = uVar15 * 0x40000000 | uVar15 >> 2;
  uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar17 + -0x359d3e2a +
          (uVar18 ^ uVar15 ^ uVar14) + uVar11;
  uVar24 = uVar19 ^ uVar20 ^ uVar3 ^ uVar24;
  uVar15 = (uVar18 ^ uVar8 ^ uVar1) + uVar24 + -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar14
  ;
  uVar14 = uVar1 * 0x40000000 | uVar1 >> 2;
  uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
  uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar18 + -0x359d3e2a +
          (uVar5 ^ uVar21 ^ uVar13 ^ uVar16) + (uVar8 ^ uVar14 ^ uVar2);
  uVar2 = (uVar19 ^ uVar11 ^ uVar4 ^ uVar12) + (uVar14 ^ uVar25 ^ uVar15) + -0x359d3e2a +
          (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar8;
  uVar15 = uVar15 * 0x40000000 | uVar15 >> 2;
  *in_EAX = (uVar25 ^ uVar15 ^ uVar1) + (uVar5 ^ uVar24 ^ uVar9 ^ uVar23) + *in_EAX + -0x359d3e2a +
            (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar14;
  in_EAX[1] = in_EAX[1] + uVar2;
  in_EAX[3] = in_EAX[3] + uVar15;
  local_8 = param_3 + -1;
  in_EAX[2] = (uVar1 * 0x40000000 | uVar1 >> 2) + in_EAX[2];
  in_EAX[4] = in_EAX[4] + uVar25;
  if (0 < local_8) {
    do {
      uVar15 = *in_EAX;
      uVar2 = in_EAX[1];
      uVar1 = ((in_EAX[3] ^ in_EAX[2]) & uVar2 ^ in_EAX[3]) +
              (uVar15 << 5 | uVar15 >> 0x1b) + puVar7[0xe] + 0x5a827999 + in_EAX[4];
      uVar8 = uVar2 << 0x1e | uVar2 >> 2;
      uVar14 = puVar7[0x10];
      uVar2 = in_EAX[3] + 0x5a827999 +
              ((in_EAX[2] ^ uVar8) & uVar15 ^ in_EAX[2]) +
              (uVar1 * 0x20 | uVar1 >> 0x1b) + puVar7[0xf];
      uVar13 = uVar15 << 0x1e | uVar15 >> 2;
      uVar25 = puVar7[0x11];
      uVar15 = in_EAX[2] + 0x5a827999 +
               ((uVar8 ^ uVar13) & uVar1 ^ uVar8) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar14;
      uVar17 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar3 = puVar7[0x12];
      uVar1 = uVar8 + 0x5a827999 +
              ((uVar17 ^ uVar13) & uVar2 ^ uVar13) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar25;
      uVar18 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar2 = uVar13 + 0x5a827999 +
              ((uVar17 ^ uVar18) & uVar15 ^ uVar17) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
      uVar8 = puVar7[0x13];
      uVar13 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar16 = puVar7[0x14];
      uVar15 = uVar17 + 0x5a827999 +
               ((uVar18 ^ uVar13) & uVar1 ^ uVar18) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar8;
      uVar9 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar17 = puVar7[0x15];
      uVar1 = uVar18 + 0x5a827999 +
              ((uVar13 ^ uVar9) & uVar2 ^ uVar13) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar16;
      uVar19 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar18 = puVar7[0x16];
      uVar2 = uVar13 + 0x5a827999 +
              ((uVar9 ^ uVar19) & uVar15 ^ uVar9) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar17;
      uVar13 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar4 = puVar7[0x17];
      uVar10 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar9 + 0x5a827999 +
              ((uVar19 ^ uVar13) & uVar1 ^ uVar19) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar18;
      uVar15 = uVar19 + 0x5a827999 +
               ((uVar10 ^ uVar13) & uVar2 ^ uVar13) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar4;
      uVar9 = puVar7[0x18];
      uVar11 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar19 = puVar7[0x19];
      uVar2 = uVar13 + 0x5a827999 +
              ((uVar10 ^ uVar11) & uVar1 ^ uVar10) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar9;
      uVar6 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar5 = puVar7[0x1a];
      uVar1 = uVar10 + 0x5a827999 +
              ((uVar11 ^ uVar6) & uVar15 ^ uVar11) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar19;
      uVar20 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar10 = puVar7[0x1b];
      uVar15 = uVar11 + 0x5a827999 +
               ((uVar6 ^ uVar20) & uVar2 ^ uVar6) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar5;
      uVar13 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar2 = uVar6 + 0x5a827999 +
              ((uVar20 ^ uVar13) & uVar1 ^ uVar20) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar10;
      uVar11 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar6 = puVar7[0x1c];
      uVar1 = uVar20 + 0x5a827999 +
              ((uVar13 ^ uVar11) & uVar15 ^ uVar13) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar6;
      uVar15 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar20 = puVar7[0x1d];
      uVar13 = ((uVar15 ^ uVar11) & uVar2 ^ uVar11) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar20 +
               0x5a827999 + uVar13;
      uVar12 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar21 = puVar7[0xe] ^ uVar10 ^ uVar18 ^ uVar14;
      uVar2 = uVar21 + 0x5a827999 +
              ((uVar15 ^ uVar12) & uVar1 ^ uVar15) + (uVar13 * 0x20 | uVar13 >> 0x1b) + uVar11;
      uVar22 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar11 = uVar6 ^ uVar4 ^ uVar25 ^ puVar7[0xf];
      uVar1 = uVar11 + 0x5a827999 +
              ((uVar12 ^ uVar22) & uVar13 ^ uVar12) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar15;
      uVar13 = uVar13 * 0x40000000 | uVar13 >> 2;
      uVar14 = uVar20 ^ uVar9 ^ uVar3 ^ uVar14;
      uVar15 = uVar14 + 0x5a827999 +
               ((uVar22 ^ uVar13) & uVar2 ^ uVar22) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar12;
      uVar12 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar24 = uVar19 ^ uVar8 ^ uVar25 ^ uVar21;
      uVar2 = uVar24 + 0x5a827999 +
              ((uVar13 ^ uVar12) & uVar1 ^ uVar13) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar22;
      uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar22 = uVar5 ^ uVar16 ^ uVar3 ^ uVar11;
      uVar1 = uVar22 + 0x6ed9eba1 +
              (uVar15 ^ uVar12 ^ uVar25) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar13;
      uVar13 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar26 = uVar10 ^ uVar17 ^ uVar8 ^ uVar14;
      uVar15 = uVar26 + 0x6ed9eba1 +
               (uVar13 ^ uVar2 ^ uVar25) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar12;
      uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar23 = uVar6 ^ uVar18 ^ uVar16 ^ uVar24;
      uVar2 = uVar23 + 0x6ed9eba1 +
              (uVar13 ^ uVar3 ^ uVar1) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar25;
      uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar27 = uVar20 ^ uVar4 ^ uVar17 ^ uVar22;
      uVar1 = uVar27 + 0x6ed9eba1 +
              (uVar3 ^ uVar25 ^ uVar15) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar13;
      uVar13 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar18 = uVar9 ^ uVar18 ^ uVar26 ^ uVar21;
      uVar15 = uVar18 + 0x6ed9eba1 +
               (uVar25 ^ uVar13 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
      uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar28 = uVar19 ^ uVar4 ^ uVar23 ^ uVar11;
      uVar2 = uVar28 + 0x6ed9eba1 +
              (uVar13 ^ uVar3 ^ uVar1) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar25;
      uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar9 = uVar5 ^ uVar9 ^ uVar27 ^ uVar14;
      uVar1 = uVar9 + 0x6ed9eba1 +
              (uVar15 ^ uVar3 ^ uVar25) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar13;
      uVar13 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar19 = uVar10 ^ uVar19 ^ uVar18 ^ uVar24;
      uVar15 = uVar19 + 0x6ed9eba1 +
               (uVar13 ^ uVar2 ^ uVar25) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
      uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar29 = uVar6 ^ uVar5 ^ uVar28 ^ uVar22;
      uVar2 = uVar29 + 0x6ed9eba1 +
              (uVar13 ^ uVar3 ^ uVar1) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar25;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar30 = uVar20 ^ uVar10 ^ uVar9 ^ uVar26;
      uVar1 = uVar30 + 0x6ed9eba1 +
              (uVar3 ^ uVar8 ^ uVar15) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar13;
      uVar17 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar13 = uVar6 ^ uVar19 ^ uVar23 ^ uVar21;
      uVar15 = uVar13 + 0x6ed9eba1 +
               (uVar8 ^ uVar17 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
      uVar12 = uVar20 ^ uVar29 ^ uVar27 ^ uVar11;
      uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar2 = uVar12 + 0x6ed9eba1 +
              (uVar17 ^ uVar25 ^ uVar1) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar8;
      uVar3 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar21 = uVar30 ^ uVar18 ^ uVar14 ^ uVar21;
      uVar16 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar1 = uVar21 + 0x6ed9eba1 +
              (uVar15 ^ uVar25 ^ uVar3) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar17;
      uVar11 = uVar13 ^ uVar28 ^ uVar24 ^ uVar11;
      uVar15 = uVar11 + 0x6ed9eba1 +
               (uVar16 ^ uVar2 ^ uVar3) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar25;
      uVar14 = uVar12 ^ uVar9 ^ uVar22 ^ uVar14;
      uVar25 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar14 + 0x6ed9eba1 +
              (uVar16 ^ uVar25 ^ uVar1) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar3;
      uVar3 = uVar19 ^ uVar26 ^ uVar24 ^ uVar21;
      uVar17 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar2 = uVar3 + 0x6ed9eba1 +
              (uVar25 ^ uVar8 ^ uVar15) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16;
      uVar22 = uVar29 ^ uVar23 ^ uVar22 ^ uVar11;
      uVar16 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar22 + 0x6ed9eba1 +
              (uVar8 ^ uVar17 ^ uVar1) + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25;
      uVar25 = uVar30 ^ uVar27 ^ uVar26 ^ uVar14;
      uVar15 = uVar25 + 0x6ed9eba1 +
               (uVar17 ^ uVar16 ^ uVar2) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar8;
      uVar4 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar24 = uVar13 ^ uVar18 ^ uVar23 ^ uVar3;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = uVar24 + 0x6ed9eba1 +
              (uVar1 ^ uVar16 ^ uVar4) + (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar17;
      uVar17 = uVar12 ^ uVar28 ^ uVar27 ^ uVar22;
      uVar2 = uVar17 + 0x6ed9eba1 +
              (uVar8 ^ uVar15 ^ uVar4) + (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar16;
      uVar16 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar18 = uVar9 ^ uVar18 ^ uVar25 ^ uVar21;
      uVar15 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
               ((uVar16 | uVar1) & uVar8 | uVar16 & uVar1) + uVar4 + uVar18;
      uVar10 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar4 = uVar19 ^ uVar28 ^ uVar24 ^ uVar11;
      uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
              ((uVar10 | uVar2) & uVar16 | uVar10 & uVar2) + uVar8 + uVar4;
      uVar8 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar9 = uVar29 ^ uVar9 ^ uVar17 ^ uVar14;
      uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
              ((uVar8 | uVar15) & uVar10 | uVar8 & uVar15) + uVar16 + uVar9;
      uVar16 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar19 = uVar30 ^ uVar19 ^ uVar18 ^ uVar3;
      uVar5 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
              ((uVar16 | uVar1) & uVar8 | uVar16 & uVar1) + uVar10 + uVar19;
      uVar10 = uVar13 ^ uVar29 ^ uVar4 ^ uVar22;
      uVar15 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
               ((uVar2 | uVar5) & uVar16 | uVar2 & uVar5) + uVar8 + uVar10;
      uVar8 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar6 = uVar12 ^ uVar30 ^ uVar9 ^ uVar25;
      uVar20 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
              ((uVar8 | uVar1) & uVar5 | uVar8 & uVar1) + uVar16 + uVar6;
      uVar26 = uVar13 ^ uVar19 ^ uVar24 ^ uVar21;
      uVar2 = ((uVar20 | uVar15) & uVar8 | uVar20 & uVar15) + uVar5 + uVar26 + -0x70e44324 +
              (uVar1 * 0x20 | uVar1 >> 0x1b);
      uVar13 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar16 = uVar12 ^ uVar10 ^ uVar17 ^ uVar11;
      uVar15 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
               ((uVar13 | uVar1) & uVar20 | uVar13 & uVar1) + uVar8 + uVar16;
      uVar21 = uVar6 ^ uVar18 ^ uVar14 ^ uVar21;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = ((uVar8 | uVar2) & uVar13 | uVar8 & uVar2) + uVar20 + uVar21 + -0x70e44324 +
              (uVar15 * 0x20 | uVar15 >> 0x1b);
      uVar11 = uVar26 ^ uVar4 ^ uVar3 ^ uVar11;
      uVar20 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
              ((uVar20 | uVar15) & uVar8 | uVar20 & uVar15) + uVar13 + uVar11;
      uVar14 = uVar16 ^ uVar9 ^ uVar22 ^ uVar14;
      uVar15 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
               ((uVar1 | uVar5) & uVar20 | uVar1 & uVar5) + uVar8 + uVar14;
      uVar13 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar3 = uVar19 ^ uVar25 ^ uVar3 ^ uVar21;
      uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
              ((uVar13 | uVar2) & uVar5 | uVar13 & uVar2) + uVar20 + uVar3;
      uVar8 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar20 = uVar10 ^ uVar24 ^ uVar22 ^ uVar11;
      uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
              ((uVar8 | uVar15) & uVar13 | uVar8 & uVar15) + uVar5 + uVar20;
      uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar25 = uVar6 ^ uVar17 ^ uVar25 ^ uVar14;
      uVar12 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
              ((uVar5 | uVar1) & uVar8 | uVar5 & uVar1) + uVar13 + uVar25;
      uVar13 = uVar26 ^ uVar18 ^ uVar24 ^ uVar3;
      uVar15 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
               ((uVar12 | uVar2) & uVar5 | uVar12 & uVar2) + uVar8 + uVar13;
      uVar8 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar17 = uVar16 ^ uVar4 ^ uVar17 ^ uVar20;
      uVar22 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
              ((uVar8 | uVar1) & uVar12 | uVar8 & uVar1) + uVar5 + uVar17;
      uVar18 = uVar9 ^ uVar18 ^ uVar25 ^ uVar21;
      uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
              ((uVar15 | uVar22) & uVar8 | uVar15 & uVar22) + uVar12 + uVar18;
      uVar4 = uVar19 ^ uVar4 ^ uVar13 ^ uVar11;
      uVar15 = (uVar2 * 0x20 | uVar2 >> 0x1b) + 0x8f1bbcdc +
               ((uVar5 | uVar1) & uVar22 | uVar5 & uVar1) + uVar8 + uVar4;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar9 = uVar10 ^ uVar9 ^ uVar17 ^ uVar14;
      uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + 0x8f1bbcdc +
              ((uVar8 | uVar2) & uVar5 | uVar8 & uVar2) + uVar22 + uVar9;
      uVar12 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar19 = uVar6 ^ uVar19 ^ uVar18 ^ uVar3;
      uVar2 = (uVar1 * 0x20 | uVar1 >> 0x1b) + 0x8f1bbcdc +
              ((uVar12 | uVar15) & uVar8 | uVar12 & uVar15) + uVar5 + uVar19;
      uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar10 = uVar26 ^ uVar10 ^ uVar4 ^ uVar20;
      uVar15 = (uVar12 ^ uVar5 ^ uVar1) + uVar10 + -0x359d3e2a +
               (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar8;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar6 = uVar16 ^ uVar6 ^ uVar9 ^ uVar25;
      uVar1 = (uVar5 ^ uVar8 ^ uVar2) + uVar6 + -0x359d3e2a +
              (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar12;
      uVar12 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar22 = uVar26 ^ uVar19 ^ uVar13 ^ uVar21;
      uVar2 = (uVar15 ^ uVar8 ^ uVar12) + uVar22 + -0x359d3e2a +
              (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar5;
      uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar16 = uVar16 ^ uVar10 ^ uVar17 ^ uVar11;
      uVar15 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar8 + -0x359d3e2a +
               (uVar5 ^ uVar1 ^ uVar12) + uVar16;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar21 = uVar21 ^ uVar6 ^ uVar18 ^ uVar14;
      uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar12 + -0x359d3e2a +
              (uVar5 ^ uVar8 ^ uVar2) + uVar21;
      uVar12 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar11 = uVar11 ^ uVar22 ^ uVar4 ^ uVar3;
      uVar2 = (uVar8 ^ uVar12 ^ uVar15) + uVar11 + -0x359d3e2a +
              (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar5;
      uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar14 = uVar14 ^ uVar16 ^ uVar9 ^ uVar20;
      uVar15 = (uVar12 ^ uVar5 ^ uVar1) + uVar14 + -0x359d3e2a +
               (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar8;
      uVar8 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar24 = uVar19 ^ uVar25 ^ uVar3 ^ uVar21;
      uVar1 = (uVar5 ^ uVar8 ^ uVar2) + uVar24 + -0x359d3e2a +
              (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar12;
      uVar3 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar12 = uVar10 ^ uVar13 ^ uVar20 ^ uVar11;
      uVar2 = (uVar15 ^ uVar8 ^ uVar3) + uVar12 + -0x359d3e2a +
              (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar5;
      uVar5 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar20 = uVar6 ^ uVar17 ^ uVar25 ^ uVar14;
      uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar8 + -0x359d3e2a +
              (uVar5 ^ uVar1 ^ uVar3) + uVar20;
      uVar8 = uVar22 ^ uVar18 ^ uVar13 ^ uVar24;
      uVar15 = (uVar5 ^ uVar25 ^ uVar2) + uVar8 + -0x359d3e2a +
               (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar3;
      uVar13 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar3 = uVar16 ^ uVar4 ^ uVar17 ^ uVar12;
      uVar2 = (uVar25 ^ uVar13 ^ uVar1) + uVar3 + -0x359d3e2a +
              (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar5;
      uVar17 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar18 = uVar9 ^ uVar18 ^ uVar20 ^ uVar21;
      uVar1 = (uVar13 ^ uVar17 ^ uVar15) + uVar18 + -0x359d3e2a +
              (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25;
      uVar25 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar4 = uVar19 ^ uVar4 ^ uVar8 ^ uVar11;
      uVar15 = (uVar17 ^ uVar25 ^ uVar2) + uVar4 + -0x359d3e2a +
               (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar13;
      uVar13 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar14 = uVar10 ^ uVar9 ^ uVar3 ^ uVar14;
      uVar2 = (uVar1 ^ uVar25 ^ uVar13) + uVar14 + -0x359d3e2a +
              (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar17;
      uVar17 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar24 = uVar6 ^ uVar19 ^ uVar18 ^ uVar24;
      uVar18 = uVar15 * 0x40000000 | uVar15 >> 2;
      uVar1 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar25 + -0x359d3e2a +
              (uVar17 ^ uVar15 ^ uVar13) + uVar24;
      uVar12 = uVar22 ^ uVar10 ^ uVar4 ^ uVar12;
      uVar15 = (uVar17 ^ uVar18 ^ uVar2) + uVar12 + -0x359d3e2a +
               (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar13;
      uVar13 = uVar2 * 0x40000000 | uVar2 >> 2;
      uVar25 = uVar1 * 0x40000000 | uVar1 >> 2;
      uVar1 = (uVar15 * 0x20 | uVar15 >> 0x1b) + uVar17 + -0x359d3e2a +
              (uVar16 ^ uVar6 ^ uVar14 ^ uVar20) + (uVar18 ^ uVar13 ^ uVar1);
      uVar2 = (uVar22 ^ uVar24 ^ uVar8 ^ uVar21) + (uVar13 ^ uVar25 ^ uVar15) + -0x359d3e2a +
              (uVar1 * 0x20 | uVar1 >> 0x1b) + uVar18;
      uVar15 = uVar15 * 0x40000000 | uVar15 >> 2;
      *in_EAX = *in_EAX + (uVar16 ^ uVar12 ^ uVar3 ^ uVar11) + (uVar25 ^ uVar15 ^ uVar1) +
                          -0x359d3e2a + (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar13;
      in_EAX[1] = in_EAX[1] + uVar2;
      in_EAX[2] = in_EAX[2] + (uVar1 * 0x40000000 | uVar1 >> 2);
      in_EAX[3] = in_EAX[3] + uVar15;
      local_8 = local_8 + -1;
      in_EAX[4] = in_EAX[4] + uVar25;
      puVar7 = puVar7 + 0x10;
    } while (local_8 != 0);
  }
  return;
}

