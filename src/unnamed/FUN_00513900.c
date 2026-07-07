/* FUN_00513900 - 0x00513900 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00513900(void)

{
  uint *puVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  
  puVar10 = &DAT_00f25f00;
  iVar8 = 0;
  uVar4 = DAT_005ab4f4;
  iVar5 = DAT_005ab704;
  pbVar7 = DAT_005a9680;
  do {
    iVar9 = 0;
    uVar6 = DAT_005ab91c;
    while (uVar6 < 0x20) {
      switch((&switchD_0051392e::switchdataD_00514460)[uVar6]) {
      case (undefined *)0x513935:
        puVar10[iVar9] = 0;
        break;
      case (undefined *)0x513941:
        if (iVar5 < 2) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -2;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 1) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x5139a7:
        if (iVar5 < 3) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -3;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 3) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513a10:
        if (iVar5 < 4) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -4;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 7) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513a79:
        if (iVar5 < 5) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -5;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0xf) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513ae1:
        if (iVar5 < 6) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -6;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x1f) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513b4a:
        if (iVar5 < 7) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -7;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x3f) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513bb3:
        if (iVar5 < 8) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -8;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x7f) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513c1b:
        if (iVar5 < 9) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -9;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0xff) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513c87:
        if (iVar5 < 10) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -10;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x1ff) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513cf3:
        if (iVar5 < 0xb) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xb;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x3ff) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513d5e:
        if (iVar5 < 0xc) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xc;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x7ff) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513dca:
        if (iVar5 < 0xd) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xd;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0xfff) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513e36:
        if (iVar5 < 0xe) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xe;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x1fff) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513ea1:
        if (iVar5 < 0xf) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xf;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        puVar10[iVar9] = (float)(int)(uVar6 - 0x3fff) * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        break;
      case (undefined *)0x513f0d:
        puVar10[iVar9] = 0;
        puVar10[iVar9 + 1] = 0;
        goto LAB_005143e2;
      case (undefined *)0x513f21:
        if (iVar5 < 2) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -2;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 1;
        goto LAB_0051433e;
      case (undefined *)0x513f6c:
        if (iVar5 < 3) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -3;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 3;
        goto LAB_005143b4;
      case (undefined *)0x513fb9:
        if (iVar5 < 4) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -4;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 7;
        goto LAB_005142c5;
      case (undefined *)0x514006:
        if (iVar5 < 5) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -5;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0xf;
        goto LAB_0051433e;
      case (undefined *)0x514053:
        if (iVar5 < 6) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -6;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x1f;
        goto LAB_005143b4;
      case (undefined *)0x5140a0:
        if (iVar5 < 7) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -7;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x3f;
        goto LAB_005142c5;
      case (undefined *)0x5140ed:
        if (iVar5 < 8) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -8;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x7f;
        goto LAB_0051433e;
      case (undefined *)0x51413a:
        if (iVar5 < 9) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -9;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0xff;
        goto LAB_005143b4;
      case (undefined *)0x51418a:
        if (iVar5 < 10) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -10;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x1ff;
        goto LAB_005142c5;
      case (undefined *)0x5141da:
        if (iVar5 < 0xb) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xb;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x3ff;
        goto LAB_0051433e;
      case (undefined *)0x51422a:
        if (iVar5 < 0xc) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xc;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x7ff;
        goto LAB_005143b4;
      case (undefined *)0x51427a:
        if (iVar5 < 0xd) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xd;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0xfff;
LAB_005142c5:
        puVar10[iVar9] = (float)iVar5 * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        fVar2 = (float)iVar5 * *(float *)(PTR_DAT_00563b40 + iVar9 * 4 + 4);
        goto LAB_005143de;
      case (undefined *)0x5142f3:
        if (iVar5 < 0xe) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xe;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x1fff;
LAB_0051433e:
        puVar10[iVar9] = (float)iVar5 * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        fVar2 = (float)iVar5 * *(float *)(PTR_DAT_00563b40 + iVar9 * 4 + 4);
LAB_005143de:
        puVar10[iVar9 + 1] = fVar2;
LAB_005143e2:
        iVar9 = iVar9 + 1;
        break;
      case (undefined *)0x514369:
        if (iVar5 < 0xf) {
          for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
            uVar4 = uVar4 << 8 | (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
            DAT_005a9680 = pbVar7;
          }
        }
        DAT_005ab704 = iVar5 + -0xf;
        uVar6 = uVar4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = uVar4 - (uVar6 << ((byte)DAT_005ab704 & 0x1f));
        iVar5 = uVar6 - 0x3fff;
LAB_005143b4:
        puVar10[iVar9] = (float)iVar5 * *(float *)(PTR_DAT_00563b40 + iVar9 * 4);
        fVar2 = (float)iVar5 * *(float *)(PTR_DAT_00563b40 + iVar9 * 4 + 4);
        goto LAB_005143de;
      case (undefined *)0x514407:
        iVar9 = DAT_005ab8d4;
        if (iVar5 < DAT_005ab8d4) {
          iVar9 = DAT_005ab8d4 - iVar5;
          iVar5 = 8;
          iVar3 = iVar9 >> 3;
          iVar9 = iVar9 + iVar3 * -8;
          uVar4 = (uint)pbVar7[iVar3];
          pbVar7 = pbVar7 + iVar3 + 1;
          DAT_005a9680 = pbVar7;
        }
        iVar5 = iVar5 - iVar9;
        uVar4 = uVar4 - ((uVar4 >> ((byte)iVar5 & 0x1f)) << ((byte)iVar5 & 0x1f));
        DAT_005ab4f4 = uVar4;
        DAT_005ab704 = iVar5;
      case (undefined *)0x51444a:
        puVar10 = puVar10 + 0x40;
        goto LAB_00514450;
      }
      puVar1 = &DAT_005ab920 + iVar9;
      iVar9 = iVar9 + 1;
      uVar4 = DAT_005ab4f4;
      iVar5 = DAT_005ab704;
      pbVar7 = DAT_005a9680;
      uVar6 = *puVar1;
    }
LAB_00514450:
    iVar8 = iVar8 + 1;
    if (0xb < iVar8) {
      return;
    }
  } while( true );
}

