/* MpegSynthWindow8FullInterleaved - 0x0051ee0a in the original binary.
 *
 * MPEG audio polyphase synthesis window: 8-bit PCM, full band (32 samples
 * per call), channel-interleaved output.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Sole caller is its thunk MpegSynthWindow8FullInterleavedThunk
 * (0x51af90), which is called twice per block by the both-channel driver
 * 0x516fe0 (table slot 16 of 0x563a60, column 1). That driver feeds the
 * first channel to out and the second channel to out+1, then advances out
 * by 0x40 = 32 samples x 1 bytes x 2 channels, so each channel is written
 * at stride 2.
 * The drivers step the ring offset DAT_005ae93c by 0x20 and mask it with
 * 0x1ff, and the table index is col + (downsample + eightBit*3)*5 with
 * downsample 0 (subband count 0x20 >> downsample = 32) and eightBit 1, as
 * installed by SetupMpegLayerIDecoder, SetupMpegLayerIIIDecoder and
 * DecodeMpegAudioFrame. Raw table bytes at 0x563a60 give slot 16 = driver
 * 0x516fe0.
 * In the body (consistent with, not the basis for, the name): stores are
 * bytes (value shr 8) at stride 2, clip to 0x7fff / -0x8000.
 *
 * SIGNATURE CORRECTED (2026-08-25).  Same hand-written-asm shape as
 * FUN_0051f456 and its two siblings: entry `push ebp; lea ebp,[esp+8];
 * pushal`, exit `popal; pop ebp; ret`, ret 0 with the caller cleaning up.
 * Every general register is saved and restored, so ECX, EDX and EAX are all
 * written before any read -- phantoms, not arguments -- and Ghidra's
 * `return CONCAT44(param_2,in_EAX)` is popal restoring EDX:EAX, not a value.
 * The real arguments are the 3 stack slot(s) its caller already passes.
 */
#include "ghidra_types.h"


void __cdecl MpegSynthWindow8FullInterleaved(int param_3,int param_4,int param_5)
{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  float *pfVar14;
  int iVar15;
  float fVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  int iVar22;
  float *pfVar23;
  float *pfVar24;
  
  iVar19 = param_4 + 0x10;
  uVar21 = param_4 + 0x30U & 0x1ff;
  iVar17 = -0x10;
  pfVar24 = (float *)&DAT_00568318;
  do {
    pfVar23 = pfVar24;
    iVar22 = iVar19 * 4;
    iVar18 = iVar19 * 4;
    iVar15 = uVar21 * 4;
    iVar20 = uVar21 * 4;
    iVar19 = *(int *)(&DAT_00569348 +
                     *(int *)(&DAT_00569348 +
                             *(int *)(&DAT_00569348 +
                                     *(int *)(&DAT_00569348 +
                                             *(int *)(&DAT_00569348 +
                                                     *(int *)(&DAT_00569348 +
                                                             *(int *)(&DAT_00569348 +
                                                                     *(int *)(&DAT_00569348 + iVar18
                                                                             ) * 4) * 4) * 4) * 4) *
                                     4) * 4) * 4) + 1;
    uVar21 = *(int *)(&DAT_00569348 +
                     *(int *)(&DAT_00569348 +
                             *(int *)(&DAT_00569348 +
                                     *(int *)(&DAT_00569348 +
                                             *(int *)(&DAT_00569348 +
                                                     *(int *)(&DAT_00569348 +
                                                             *(int *)(&DAT_00569348 +
                                                                     *(int *)(&DAT_00569348 + iVar20
                                                                             ) * 4) * 4) * 4) * 4) *
                                     4) * 4) * 4) - 1;
    DAT_00569344 = (int)ROUND((pfVar23[0xe] *
                               *(float *)(param_3 +
                                         *(int *)(&DAT_00569348 +
                                                 *(int *)(&DAT_00569348 +
                                                         *(int *)(&DAT_00569348 +
                                                                 *(int *)(&DAT_00569348 +
                                                                         *(int *)(&DAT_00569348 +
                                                                                 *(int *)(&
                                                  DAT_00569348 +
                                                  *(int *)(&DAT_00569348 + iVar18) * 4) * 4) * 4) *
                                                  4) * 4) * 4) * 4) +
                              ((pfVar23[0xc] *
                                *(float *)(param_3 +
                                          *(int *)(&DAT_00569348 +
                                                  *(int *)(&DAT_00569348 +
                                                          *(int *)(&DAT_00569348 +
                                                                  *(int *)(&DAT_00569348 +
                                                                          *(int *)(&DAT_00569348 +
                                                                                  *(int *)(&
                                                  DAT_00569348 + iVar18) * 4) * 4) * 4) * 4) * 4) *
                                          4) +
                               ((pfVar23[10] *
                                 *(float *)(param_3 +
                                           *(int *)(&DAT_00569348 +
                                                   *(int *)(&DAT_00569348 +
                                                           *(int *)(&DAT_00569348 +
                                                                   *(int *)(&DAT_00569348 +
                                                                           *(int *)(&DAT_00569348 +
                                                                                   iVar18) * 4) * 4)
                                                           * 4) * 4) * 4) +
                                ((pfVar23[8] *
                                  *(float *)(param_3 +
                                            *(int *)(&DAT_00569348 +
                                                    *(int *)(&DAT_00569348 +
                                                            *(int *)(&DAT_00569348 +
                                                                    *(int *)(&DAT_00569348 + iVar18)
                                                                    * 4) * 4) * 4) * 4) +
                                 ((pfVar23[6] *
                                   *(float *)(param_3 +
                                             *(int *)(&DAT_00569348 +
                                                     *(int *)(&DAT_00569348 +
                                                             *(int *)(&DAT_00569348 + iVar18) * 4) *
                                                     4) * 4) +
                                  ((pfVar23[4] *
                                    *(float *)(param_3 +
                                              *(int *)(&DAT_00569348 +
                                                      *(int *)(&DAT_00569348 + iVar18) * 4) * 4) +
                                   ((pfVar23[2] *
                                     *(float *)(param_3 + *(int *)(&DAT_00569348 + iVar18) * 4) +
                                    ((*pfVar23 * *(float *)(param_3 + iVar22) + 0.0) -
                                    pfVar23[1] * *(float *)(param_3 + iVar15))) -
                                   pfVar23[3] *
                                   *(float *)(param_3 + *(int *)(&DAT_00569348 + iVar20) * 4))) -
                                  pfVar23[5] *
                                  *(float *)(param_3 +
                                            *(int *)(&DAT_00569348 +
                                                    *(int *)(&DAT_00569348 + iVar20) * 4) * 4))) -
                                 pfVar23[7] *
                                 *(float *)(param_3 +
                                           *(int *)(&DAT_00569348 +
                                                   *(int *)(&DAT_00569348 +
                                                           *(int *)(&DAT_00569348 + iVar20) * 4) * 4
                                                   ) * 4))) -
                                pfVar23[9] *
                                *(float *)(param_3 +
                                          *(int *)(&DAT_00569348 +
                                                  *(int *)(&DAT_00569348 +
                                                          *(int *)(&DAT_00569348 +
                                                                  *(int *)(&DAT_00569348 + iVar20) *
                                                                  4) * 4) * 4) * 4))) -
                               pfVar23[0xb] *
                               *(float *)(param_3 +
                                         *(int *)(&DAT_00569348 +
                                                 *(int *)(&DAT_00569348 +
                                                         *(int *)(&DAT_00569348 +
                                                                 *(int *)(&DAT_00569348 +
                                                                         *(int *)(&DAT_00569348 +
                                                                                 iVar20) * 4) * 4) *
                                                         4) * 4) * 4))) -
                              pfVar23[0xd] *
                              *(float *)(param_3 +
                                        *(int *)(&DAT_00569348 +
                                                *(int *)(&DAT_00569348 +
                                                        *(int *)(&DAT_00569348 +
                                                                *(int *)(&DAT_00569348 +
                                                                        *(int *)(&DAT_00569348 +
                                                                                *(int *)(&
                                                  DAT_00569348 + iVar20) * 4) * 4) * 4) * 4) * 4) *
                                        4))) -
                              pfVar23[0xf] *
                              *(float *)(param_3 +
                                        *(int *)(&DAT_00569348 +
                                                *(int *)(&DAT_00569348 +
                                                        *(int *)(&DAT_00569348 +
                                                                *(int *)(&DAT_00569348 +
                                                                        *(int *)(&DAT_00569348 +
                                                                                *(int *)(&
                                                  DAT_00569348 +
                                                  *(int *)(&DAT_00569348 + iVar20) * 4) * 4) * 4) *
                                                  4) * 4) * 4) * 4));
    if (DAT_00569344 < 0x8000) {
      if (DAT_00569344 < -0x8000) {
        DAT_00569344 = -0x8000;
      }
    }
    else {
      DAT_00569344 = 0x7fff;
    }
    ((byte *)(param_5 + 0x20))[iVar17 * 2] = (byte)((uint)DAT_00569344 >> 8) ^ 0x80;
    iVar17 = iVar17 + 1;
    pfVar24 = pfVar23 + 0x10;
  } while (iVar17 != 0);
  iVar17 = *(int *)(&DAT_00569348 +
                   *(int *)(&DAT_00569348 +
                           *(int *)(&DAT_00569348 +
                                   *(int *)(&DAT_00569348 +
                                           *(int *)(&DAT_00569348 +
                                                   *(int *)(&DAT_00569348 +
                                                           *(int *)(&DAT_00569348 +
                                                                   *(int *)(&DAT_00569348 +
                                                                           uVar21 * 4) * 4) * 4) * 4
                                                   ) * 4) * 4) * 4) * 4);
  DAT_00569344 = (int)ROUND(pfVar23[0x17] *
                            *(float *)(param_3 +
                                      *(int *)(&DAT_00569348 +
                                              *(int *)(&DAT_00569348 +
                                                      *(int *)(&DAT_00569348 +
                                                              *(int *)(&DAT_00569348 +
                                                                      *(int *)(&DAT_00569348 +
                                                                              *(int *)(&DAT_00569348
                                                                                      + *(int *)(&
                                                  DAT_00569348 + uVar21 * 4) * 4) * 4) * 4) * 4) * 4
                                                  ) * 4) * 4) +
                            pfVar23[0x16] *
                            *(float *)(param_3 +
                                      *(int *)(&DAT_00569348 +
                                              *(int *)(&DAT_00569348 +
                                                      *(int *)(&DAT_00569348 +
                                                              *(int *)(&DAT_00569348 +
                                                                      *(int *)(&DAT_00569348 +
                                                                              *(int *)(&DAT_00569348
                                                                                      + uVar21 * 4)
                                                                              * 4) * 4) * 4) * 4) *
                                              4) * 4) +
                            pfVar23[0x15] *
                            *(float *)(param_3 +
                                      *(int *)(&DAT_00569348 +
                                              *(int *)(&DAT_00569348 +
                                                      *(int *)(&DAT_00569348 +
                                                              *(int *)(&DAT_00569348 +
                                                                      *(int *)(&DAT_00569348 +
                                                                              uVar21 * 4) * 4) * 4)
                                                      * 4) * 4) * 4) +
                            pfVar23[0x14] *
                            *(float *)(param_3 +
                                      *(int *)(&DAT_00569348 +
                                              *(int *)(&DAT_00569348 +
                                                      *(int *)(&DAT_00569348 +
                                                              *(int *)(&DAT_00569348 + uVar21 * 4) *
                                                              4) * 4) * 4) * 4) +
                            pfVar23[0x13] *
                            *(float *)(param_3 +
                                      *(int *)(&DAT_00569348 +
                                              *(int *)(&DAT_00569348 +
                                                      *(int *)(&DAT_00569348 + uVar21 * 4) * 4) * 4)
                                      * 4) +
                            pfVar23[0x12] *
                            *(float *)(param_3 +
                                      *(int *)(&DAT_00569348 +
                                              *(int *)(&DAT_00569348 + uVar21 * 4) * 4) * 4) +
                            pfVar23[0x11] *
                            *(float *)(param_3 + *(int *)(&DAT_00569348 + uVar21 * 4) * 4) +
                            pfVar23[0x10] * *(float *)(param_3 + uVar21 * 4) + 0.0);
  if (DAT_00569344 < 0x8000) {
    if (DAT_00569344 < -0x8000) {
      DAT_00569344 = -0x8000;
    }
  }
  else {
    DAT_00569344 = 0x7fff;
  }
  *(byte *)(param_5 + 0x20) = (byte)((uint)DAT_00569344 >> 8) ^ 0x80;
  pfVar24 = (float *)&DAT_00568714;
  iVar18 = -0xf;
  do {
    iVar20 = iVar19 + -1;
    iVar22 = iVar17 + 1;
    fVar16 = *pfVar24;
    pfVar23 = pfVar24 + -1;
    pfVar1 = pfVar24 + -2;
    pfVar2 = pfVar24 + -3;
    pfVar3 = pfVar24 + -4;
    pfVar4 = pfVar24 + -5;
    pfVar5 = pfVar24 + -6;
    pfVar6 = pfVar24 + -7;
    pfVar7 = pfVar24 + -8;
    pfVar8 = pfVar24 + -9;
    pfVar9 = pfVar24 + -10;
    pfVar10 = pfVar24 + -0xb;
    pfVar11 = pfVar24 + -0xc;
    pfVar12 = pfVar24 + -0xd;
    pfVar13 = pfVar24 + -0xe;
    iVar19 = *(int *)(&DAT_00569348 +
                     *(int *)(&DAT_00569348 +
                             *(int *)(&DAT_00569348 +
                                     *(int *)(&DAT_00569348 +
                                             *(int *)(&DAT_00569348 +
                                                     *(int *)(&DAT_00569348 +
                                                             *(int *)(&DAT_00569348 +
                                                                     *(int *)(&DAT_00569348 +
                                                                             iVar20 * 4) * 4) * 4) *
                                                     4) * 4) * 4) * 4) * 4);
    pfVar14 = pfVar24 + -0xf;
    iVar17 = *(int *)(&DAT_00569348 +
                     *(int *)(&DAT_00569348 +
                             *(int *)(&DAT_00569348 +
                                     *(int *)(&DAT_00569348 +
                                             *(int *)(&DAT_00569348 +
                                                     *(int *)(&DAT_00569348 +
                                                             *(int *)(&DAT_00569348 +
                                                                     *(int *)(&DAT_00569348 +
                                                                             iVar22 * 4) * 4) * 4) *
                                                     4) * 4) * 4) * 4) * 4);
    pfVar24 = pfVar24 + -0x10;
    DAT_00569344 = (int)ROUND(*pfVar14 *
                              *(float *)(param_3 +
                                        *(int *)(&DAT_00569348 +
                                                *(int *)(&DAT_00569348 +
                                                        *(int *)(&DAT_00569348 +
                                                                *(int *)(&DAT_00569348 +
                                                                        *(int *)(&DAT_00569348 +
                                                                                *(int *)(&
                                                  DAT_00569348 +
                                                  *(int *)(&DAT_00569348 + iVar22 * 4) * 4) * 4) * 4
                                                  ) * 4) * 4) * 4) * 4) +
                              *pfVar13 *
                              *(float *)(param_3 +
                                        *(int *)(&DAT_00569348 +
                                                *(int *)(&DAT_00569348 +
                                                        *(int *)(&DAT_00569348 +
                                                                *(int *)(&DAT_00569348 +
                                                                        *(int *)(&DAT_00569348 +
                                                                                *(int *)(&
                                                  DAT_00569348 +
                                                  *(int *)(&DAT_00569348 + iVar20 * 4) * 4) * 4) * 4
                                                  ) * 4) * 4) * 4) * 4) +
                              *pfVar12 *
                              *(float *)(param_3 +
                                        *(int *)(&DAT_00569348 +
                                                *(int *)(&DAT_00569348 +
                                                        *(int *)(&DAT_00569348 +
                                                                *(int *)(&DAT_00569348 +
                                                                        *(int *)(&DAT_00569348 +
                                                                                *(int *)(&
                                                  DAT_00569348 + iVar22 * 4) * 4) * 4) * 4) * 4) * 4
                                                ) * 4) +
                              *pfVar11 *
                              *(float *)(param_3 +
                                        *(int *)(&DAT_00569348 +
                                                *(int *)(&DAT_00569348 +
                                                        *(int *)(&DAT_00569348 +
                                                                *(int *)(&DAT_00569348 +
                                                                        *(int *)(&DAT_00569348 +
                                                                                *(int *)(&
                                                  DAT_00569348 + iVar20 * 4) * 4) * 4) * 4) * 4) * 4
                                                ) * 4) +
                              *pfVar10 *
                              *(float *)(param_3 +
                                        *(int *)(&DAT_00569348 +
                                                *(int *)(&DAT_00569348 +
                                                        *(int *)(&DAT_00569348 +
                                                                *(int *)(&DAT_00569348 +
                                                                        *(int *)(&DAT_00569348 +
                                                                                iVar22 * 4) * 4) * 4
                                                                ) * 4) * 4) * 4) +
                              *pfVar9 * *(float *)(param_3 +
                                                  *(int *)(&DAT_00569348 +
                                                          *(int *)(&DAT_00569348 +
                                                                  *(int *)(&DAT_00569348 +
                                                                          *(int *)(&DAT_00569348 +
                                                                                  *(int *)(&
                                                  DAT_00569348 + iVar20 * 4) * 4) * 4) * 4) * 4) * 4
                                                  ) +
                              *pfVar8 * *(float *)(param_3 +
                                                  *(int *)(&DAT_00569348 +
                                                          *(int *)(&DAT_00569348 +
                                                                  *(int *)(&DAT_00569348 +
                                                                          *(int *)(&DAT_00569348 +
                                                                                  iVar22 * 4) * 4) *
                                                                  4) * 4) * 4) +
                              *pfVar7 * *(float *)(param_3 +
                                                  *(int *)(&DAT_00569348 +
                                                          *(int *)(&DAT_00569348 +
                                                                  *(int *)(&DAT_00569348 +
                                                                          *(int *)(&DAT_00569348 +
                                                                                  iVar20 * 4) * 4) *
                                                                  4) * 4) * 4) +
                              *pfVar6 * *(float *)(param_3 +
                                                  *(int *)(&DAT_00569348 +
                                                          *(int *)(&DAT_00569348 +
                                                                  *(int *)(&DAT_00569348 +
                                                                          iVar22 * 4) * 4) * 4) * 4)
                              + *pfVar5 * *(float *)(param_3 +
                                                    *(int *)(&DAT_00569348 +
                                                            *(int *)(&DAT_00569348 +
                                                                    *(int *)(&DAT_00569348 +
                                                                            iVar20 * 4) * 4) * 4) *
                                                    4) +
                                *pfVar4 * *(float *)(param_3 +
                                                    *(int *)(&DAT_00569348 +
                                                            *(int *)(&DAT_00569348 + iVar22 * 4) * 4
                                                            ) * 4) +
                                *pfVar3 * *(float *)(param_3 +
                                                    *(int *)(&DAT_00569348 +
                                                            *(int *)(&DAT_00569348 + iVar20 * 4) * 4
                                                            ) * 4) +
                                *pfVar2 * *(float *)(param_3 +
                                                    *(int *)(&DAT_00569348 + iVar22 * 4) * 4) +
                                *pfVar1 * *(float *)(param_3 +
                                                    *(int *)(&DAT_00569348 + iVar20 * 4) * 4) +
                                *pfVar23 * *(float *)(param_3 + iVar22 * 4) +
                                fVar16 * *(float *)(param_3 + iVar20 * 4) + 0.0);
    if (DAT_00569344 < 0x8000) {
      iVar20 = DAT_00569344;
      if (DAT_00569344 < -0x8000) {
        iVar20 = -0x8000;
      }
    }
    else {
      iVar20 = 0x7fff;
    }
    *(byte *)(param_5 + 0x40 + iVar18 * 2) = (byte)((uint)iVar20 >> 8) ^ 0x80;
    iVar18 = iVar18 + 1;
  } while (iVar18 != 0);
  return;
}

