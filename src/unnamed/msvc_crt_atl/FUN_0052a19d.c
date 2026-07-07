/* FUN_0052a19d - 0x0052a19d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setmbcp_lk
   
   Library: Visual Studio 2003 Release */

undefined4 __setmbcp_lk(UINT param_1)

{
  BYTE *pBVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  BOOL BVar5;
  BYTE *pBVar6;
  int iVar7;
  int extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar8;
  byte *pbVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  uint local_20;
  _cpinfo local_1c;
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  if (param_1 != 0) {
    iVar8 = 0;
    uVar4 = 0;
    do {
      if (*(UINT *)((int)&DAT_0056c140 + uVar4) == param_1) {
        puVar11 = (undefined4 *)&DAT_00f29460;
        for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar11 = 0;
          puVar11 = puVar11 + 1;
        }
        local_20 = 0;
        *(undefined1 *)puVar11 = 0;
        pbVar9 = (byte *)(iVar8 * 0x30 + 0x56c150);
        do {
          bVar3 = *pbVar9;
          pbVar10 = pbVar9;
          while ((bVar3 != 0 && (bVar2 = pbVar10[1], bVar2 != 0))) {
            uVar4 = (uint)bVar3;
            if (uVar4 <= bVar2) {
              bVar3 = (&DAT_0056c138)[local_20];
              do {
                (&DAT_00f29461)[uVar4] = (&DAT_00f29461)[uVar4] | bVar3;
                uVar4 = uVar4 + 1;
              } while (uVar4 <= bVar2);
            }
            pbVar10 = pbVar10 + 2;
            bVar3 = *pbVar10;
          }
          local_20 = local_20 + 1;
          pbVar9 = pbVar9 + 8;
        } while (local_20 < 4);
        DAT_00f29564 = param_1;
        DAT_00f2944c = 1;
        DAT_00f29444 = _CPtoLCID();
        _DAT_00f29570 = *(undefined4 *)(&DAT_0056c144 + extraout_ECX);
        DAT_00f29574 = *(undefined4 *)(&DAT_0056c148 + extraout_ECX);
        DAT_00f29578 = *(undefined4 *)(&DAT_0056c14c + extraout_ECX);
        goto LAB_0052a314;
      }
      uVar4 = uVar4 + 0x30;
      iVar8 = iVar8 + 1;
    } while (uVar4 < 0xf0);
    BVar5 = GetCPInfo(param_1,&local_1c);
    if (BVar5 == 1) {
      puVar11 = (undefined4 *)&DAT_00f29460;
      for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined1 *)puVar11 = 0;
      DAT_00f29564 = param_1;
      DAT_00f29444 = 0;
      if (local_1c.MaxCharSize < 2) {
        DAT_00f2944c = 0;
      }
      else {
        if (local_1c.LeadByte[0] != '\0') {
          pBVar6 = local_1c.LeadByte + 1;
          do {
            bVar3 = *pBVar6;
            if (bVar3 == 0) break;
            for (uVar4 = (uint)pBVar6[-1]; uVar4 <= bVar3; uVar4 = uVar4 + 1) {
              (&DAT_00f29461)[uVar4] = (&DAT_00f29461)[uVar4] | 4;
            }
            pBVar1 = pBVar6 + 1;
            pBVar6 = pBVar6 + 2;
          } while (*pBVar1 != 0);
        }
        uVar4 = 1;
        do {
          (&DAT_00f29461)[uVar4] = (&DAT_00f29461)[uVar4] | 8;
          uVar4 = uVar4 + 1;
        } while (uVar4 < 0xff);
        DAT_00f29444 = _CPtoLCID();
        DAT_00f2944c = extraout_ECX_00;
      }
      _DAT_00f29570 = 0;
      DAT_00f29574 = 0;
      DAT_00f29578 = 0;
      goto LAB_0052a314;
    }
    if (DAT_005b190c == 0) {
      return 0xffffffff;
    }
  }
  setSBCS();
LAB_0052a314:
  setSBUpLow();
  return 0;
}

