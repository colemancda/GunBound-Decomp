/* FUN_005300e8 - 0x005300e8 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_005300e8(double param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  dVar2 = (double)((ulonglong)param_1 & _DAT_005490a0);
  dVar3 = (double)((ulonglong)param_1 & uRam005490a8);
  if (!NAN(dVar2) && !NAN(_DAT_00549210)) {
    if (dVar2 < _DAT_00549210) {
      if (_DAT_005491f0 <= dVar2) {
        if (dVar2 < _DAT_005491e0) {
          dVar2 = dVar2 * dVar2;
          dVar5 = dVar2 * dVar2;
          dVar3 = dVar3 * dVar3 * dVar3 * dVar3;
          return (float10)(param_1 -
                          ((((((((_DAT_00549140 * dVar5 + _DAT_00549130) * dVar5 + _DAT_00549120) *
                                dVar5 + _DAT_00549110) * dVar5 + _DAT_00549100) * dVar5 +
                             _DAT_005490f0) * dVar5 + _DAT_005490e0) * dVar5 + _DAT_005490d0) *
                           dVar2 + ((((((dRam00549148 * dVar3 + dRam00549138) * dVar3 + dRam00549128
                                       ) * dVar3 + dRam00549118) * dVar3 + dRam00549108) * dVar3 +
                                    dRam005490f8) * dVar3 + dRam005490e8) * dVar3 + dRam005490d8) *
                          param_1);
        }
        if (_DAT_005491d0 <= dVar2) {
          iVar1 = 0x300;
          dVar3 = DAT_005491a0 / dVar2;
        }
        else {
          iVar4 = (uint)((ulonglong)(dVar2 + DAT_005491c0) >> 0x2c) - (int)DAT_005490c0;
          iVar1 = iVar4 * 3;
          dVar3 = (dVar2 - *(double *)(&DAT_00549bc0 + iVar4 * 0x18)) /
                  (dVar2 * *(double *)(&DAT_00549bc0 + iVar4 * 0x18) + _DAT_005491b0);
        }
        dVar5 = dVar3 * dVar3;
        dVar6 = dVar5 * dVar5;
        dVar7 = dVar3 * dVar3 * dVar3 * dVar3;
        return (float10)(double)((ulonglong)
                                 (*(double *)(&DAT_00549bb0 + iVar1 * 8) -
                                 ((((((_DAT_00549180 * dVar6 + _DAT_00549170) * dVar6 +
                                     _DAT_00549160) * dVar6 + _DAT_00549150) * dVar5 +
                                   ((dRam00549188 * dVar7 + dRam00549178) * dVar7 + dRam00549168) *
                                   dVar7 + dRam00549158) * dVar3 -
                                  *(double *)(&DAT_00549bb8 + iVar1 * 8)) - dVar3)) |
                                (ulonglong)param_1 ^ (ulonglong)dVar2);
      }
      if (_DAT_00549200 <= dVar2) {
        dVar2 = dVar2 * dVar2;
        dVar5 = dVar2 * dVar2;
        dVar3 = dVar3 * dVar3 * dVar3 * dVar3;
        return (float10)(param_1 -
                        ((((_DAT_00549180 * dVar5 + _DAT_00549170) * dVar5 + _DAT_00549160) * dVar5
                         + _DAT_00549150) * dVar2 +
                        ((dRam00549188 * dVar3 + dRam00549178) * dVar3 + dRam00549168) * dVar3 +
                        dRam00549158) * param_1);
      }
      if (dVar2 == _DAT_00549190) {
        return (float10)param_1;
      }
      if (dVar2 < _DAT_00549220) {
        return (float10)(_DAT_00549230 * _DAT_00549230) + (float10)param_1;
      }
      return (float10)_DAT_00549230 * (float10)_DAT_00549230 + (float10)param_1;
    }
    if (!NAN((double)((ulonglong)dVar2 & (ulonglong)DAT_00549090)) && !NAN(DAT_00549090)) {
      return (float10)_DAT_00549230 +
             (float10)*(double *)(&DAT_005490b0 + (param_1._4_4_ >> 0x1f) * -8);
    }
  }
  ___libm_error_support(&param_1,&param_1,&param_1,0x3eb);
  return (float10)param_1;
}

