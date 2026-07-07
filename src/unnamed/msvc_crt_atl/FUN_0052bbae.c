/* FUN_0052bbae - 0x0052bbae in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Removing unreachable block (ram,0x0052c8ec) */
/* Library Function - Single Match
    __input
   
   Library: Visual Studio 2003 Release */

int __input(undefined4 param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  wchar_t *pwVar8;
  byte *pbVar9;
  char *pcVar10;
  char *pcVar11;
  wchar_t *pwVar12;
  uint uVar13;
  byte *pbVar14;
  bool bVar15;
  longlong lVar16;
  undefined4 *local_1e0;
  uint local_1d8;
  wchar_t local_1d0 [2];
  int local_1cc;
  byte local_1c8;
  undefined1 local_1c7;
  uint local_1c4;
  undefined1 *local_1c0;
  int local_1bc;
  int local_1b8;
  wchar_t *local_1b4;
  undefined8 local_1b0;
  byte local_1a5;
  int local_1a4;
  int local_1a0;
  byte local_19c;
  char local_19b;
  char local_19a;
  char local_199;
  uint local_198;
  char local_192;
  char local_191;
  int local_190;
  char local_189;
  int local_188;
  char local_181;
  char local_180;
  char local_17f [351];
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00545190;
  uStack_c = 0x52bbbd;
  local_20 = DAT_0056bfd4;
  local_1c0 = (undefined1 *)0x0;
  local_1b4 = (wchar_t *)0x0;
  local_198 = 0;
  local_199 = '\0';
  local_188 = 0;
  local_1bc = 0;
LAB_0052bbf1:
  do {
    if (*param_2 == 0) {
LAB_0052c8e3:
      if ((local_198 == 0xffffffff) && ((local_1bc == 0 && (local_199 == '\0')))) {
        local_1bc = -1;
      }
      return local_1bc;
    }
    iVar3 = _isspace((uint)*param_2);
    if (iVar3 == 0) {
      if (*param_2 == 0x25) {
        iVar3 = 0;
        local_1a4 = 0;
        local_19c = 0;
        local_1a0 = 0;
        local_1b8 = 0;
        local_190 = 0;
        local_1a5 = 0;
        local_19b = '\0';
        local_192 = '\0';
        local_181 = '\0';
        local_19a = '\0';
        local_189 = '\0';
        local_191 = '\x01';
        local_1cc = 0;
        pbVar14 = param_2;
        do {
          pbVar9 = pbVar14 + 1;
          uVar7 = (uint)*pbVar9;
          iVar4 = _isdigit(uVar7);
          param_2 = pbVar9;
          if (iVar4 == 0) {
            if (uVar7 < 0x4f) {
              if (uVar7 != 0x4e) {
                if (uVar7 == 0x2a) {
                  local_192 = local_192 + '\x01';
                }
                else if (uVar7 != 0x46) {
                  if (uVar7 == 0x49) {
                    bVar6 = pbVar14[2];
                    if ((bVar6 == 0x36) && (pbVar14[3] == 0x34)) {
                      local_1cc = local_1cc + 1;
                      local_1b0 = 0;
                      param_2 = pbVar14 + 3;
                    }
                    else if (((bVar6 != 0x33) || (param_2 = pbVar14 + 3, *param_2 != 0x32)) &&
                            ((((param_2 = pbVar9, bVar6 != 100 && (bVar6 != 0x69)) &&
                              (bVar6 != 0x6f)) && ((bVar6 != 0x78 && (bVar6 != 0x58))))))
                    goto LAB_0052bd78;
                  }
                  else if (uVar7 == 0x4c) {
                    local_191 = local_191 + '\x01';
                  }
                  else {
LAB_0052bd78:
                    local_181 = local_181 + '\x01';
                    param_2 = pbVar9;
                  }
                }
              }
            }
            else if (uVar7 == 0x68) {
              local_191 = local_191 + -1;
              local_189 = local_189 + -1;
            }
            else {
              if (uVar7 == 0x6c) {
                local_191 = local_191 + '\x01';
              }
              else if (uVar7 != 0x77) goto LAB_0052bd78;
              local_189 = local_189 + '\x01';
            }
          }
          else {
            local_1b8 = local_1b8 + 1;
            iVar3 = (uVar7 - 0x30) + iVar3 * 10;
          }
          pbVar14 = param_2;
        } while (local_181 == '\0');
        if (local_192 == '\0') {
          local_1e0 = param_3;
          local_1b4 = (wchar_t *)*param_3;
          param_3 = param_3 + 1;
        }
        pwVar8 = local_1b4;
        local_181 = '\0';
        if ((local_189 == '\0') && ((*param_2 == 0x53 || (local_189 = -1, *param_2 == 0x43)))) {
          local_189 = '\x01';
        }
        uVar13 = *param_2 | 0x20;
        local_1c4 = uVar13;
        uVar7 = local_198;
        local_190 = iVar3;
        if (uVar13 != 0x6e) {
          if ((uVar13 == 99) || (uVar13 == 0x7b)) {
            local_188 = local_188 + 1;
            uVar7 = __inc();
          }
          else {
            do {
              local_188 = local_188 + 1;
              uVar7 = __inc();
              iVar3 = _isspace(uVar7);
            } while (iVar3 != 0);
          }
        }
        local_198 = uVar7;
        uVar7 = local_198;
        if ((local_1b8 != 0) && (local_190 == 0)) {
LAB_0052c8aa:
          if (uVar7 != 0xffffffff) {
            __ungetc_lk(local_198,param_1);
          }
          goto LAB_0052c8e3;
        }
        if (uVar13 < 0x70) {
          if (uVar13 == 0x6f) {
LAB_0052c542:
            if (local_198 == 0x2d) {
              local_19b = '\x01';
            }
            else if (local_198 != 0x2b) goto LAB_0052c585;
            local_190 = local_190 + -1;
            if ((local_190 == 0) && (local_1b8 != 0)) {
              local_181 = '\x01';
            }
            else {
              local_188 = local_188 + 1;
              local_198 = __inc();
            }
            goto LAB_0052c585;
          }
          if (uVar13 != 99) {
            if (uVar13 == 100) goto LAB_0052c542;
            if (uVar13 < 0x65) {
LAB_0052c147:
              if (*param_2 != local_198) goto LAB_0052c8aa;
              local_199 = local_199 + -1;
              if (local_192 == '\0') {
                param_3 = local_1e0;
              }
              goto LAB_0052c842;
            }
            if (0x67 < uVar13) {
              if (uVar13 == 0x69) {
                uVar13 = 100;
                goto LAB_0052becf;
              }
              if (uVar13 != 0x6e) goto LAB_0052c147;
              iVar3 = local_188;
              lVar16 = local_1b0;
              if (local_192 != '\0') goto LAB_0052c842;
              goto LAB_0052c816;
            }
            pcVar10 = &local_180;
            if (local_198 == 0x2d) {
              local_180 = '-';
              pcVar10 = local_17f;
LAB_0052bf0e:
              local_190 = local_190 + -1;
              local_188 = local_188 + 1;
              local_198 = __inc();
            }
            else if (local_198 == 0x2b) goto LAB_0052bf0e;
            if ((local_1b8 == 0) || (0x15d < local_190)) {
              local_190 = 0x15d;
            }
            while( true ) {
              uVar7 = local_198;
              iVar3 = _isdigit(local_198);
              if ((iVar3 == 0) ||
                 (iVar3 = local_190 + -1, bVar15 = local_190 == 0, local_190 = iVar3, bVar15))
              break;
              local_1a0 = local_1a0 + 1;
              *pcVar10 = (char)uVar7;
              pcVar10 = pcVar10 + 1;
              local_188 = local_188 + 1;
              local_198 = __inc();
            }
            if ((DAT_0056cbf4 == (char)uVar7) &&
               (iVar3 = local_190 + -1, bVar15 = local_190 != 0, local_190 = iVar3, bVar15)) {
              local_188 = local_188 + 1;
              uVar7 = __inc();
              *pcVar10 = DAT_0056cbf4;
              while( true ) {
                pcVar10 = pcVar10 + 1;
                local_198 = uVar7;
                iVar3 = _isdigit(uVar7);
                if ((iVar3 == 0) ||
                   (iVar3 = local_190 + -1, bVar15 = local_190 == 0, local_190 = iVar3, bVar15))
                break;
                local_1a0 = local_1a0 + 1;
                *pcVar10 = (char)uVar7;
                local_188 = local_188 + 1;
                uVar7 = __inc();
              }
            }
            pcVar11 = pcVar10;
            if ((local_1a0 != 0) &&
               (((uVar7 == 0x65 || (uVar7 == 0x45)) &&
                (iVar3 = local_190 + -1, bVar15 = local_190 != 0, local_190 = iVar3, bVar15)))) {
              *pcVar10 = 'e';
              pcVar11 = pcVar10 + 1;
              local_188 = local_188 + 1;
              local_198 = __inc();
              if (local_198 == 0x2d) {
                *pcVar11 = '-';
                pcVar11 = pcVar10 + 2;
LAB_0052c048:
                bVar15 = local_190 != 0;
                local_190 = local_190 + -1;
                if (bVar15) goto LAB_0052c079;
                local_190 = 0;
              }
              else if (local_198 == 0x2b) goto LAB_0052c048;
              while( true ) {
                uVar7 = local_198;
                iVar3 = _isdigit(local_198);
                if ((iVar3 == 0) ||
                   (iVar3 = local_190 + -1, bVar15 = local_190 == 0, local_190 = iVar3, bVar15))
                break;
                local_1a0 = local_1a0 + 1;
                *pcVar11 = (char)uVar7;
                pcVar11 = pcVar11 + 1;
LAB_0052c079:
                local_188 = local_188 + 1;
                local_198 = __inc();
              }
            }
            local_188 = local_188 + -1;
            if (uVar7 != 0xffffffff) {
              __ungetc_lk(uVar7,param_1);
            }
            if (local_1a0 != 0) {
              if (local_192 == '\0') {
                local_1bc = local_1bc + 1;
                *pcVar11 = '\0';
                (*(code *)PTR_FUN_0056c9d0)(local_191 + -1,local_1b4,&local_180);
              }
              goto LAB_0052c842;
            }
            goto LAB_0052c8e3;
          }
          if (local_1b8 == 0) {
            local_1b8 = 1;
            local_190 = local_190 + 1;
          }
LAB_0052c108:
          if ('\0' < local_189) {
            local_19a = '\x01';
          }
LAB_0052c2d2:
          local_188 = local_188 + -1;
          pwVar12 = pwVar8;
          if (local_198 != 0xffffffff) {
            __ungetc_lk(local_198,param_1);
          }
          while( true ) {
            if ((local_1b8 != 0) &&
               (iVar3 = local_190 + -1, bVar15 = local_190 == 0, local_190 = iVar3, bVar15))
            goto LAB_0052c4f3;
            local_188 = local_188 + 1;
            local_198 = __inc();
            if ((local_198 == 0xffffffff) ||
               ((bVar6 = (byte)local_198, uVar13 != 99 &&
                (((uVar13 != 0x73 ||
                  (((8 < (int)local_198 && ((int)local_198 < 0xe)) || (local_198 == 0x20)))) &&
                 ((uVar13 != 0x7b ||
                  (uVar13 = local_1c4,
                  ((int)(char)(local_1c0[(int)local_198 >> 3] ^ local_1a5) & 1 << (bVar6 & 7)) == 0)
                  ))))))) break;
            if (local_192 == '\0') {
              if (local_19a == '\0') {
                *(byte *)pwVar8 = bVar6;
                pwVar8 = (wchar_t *)((int)pwVar8 + 1);
                local_1b4 = pwVar8;
              }
              else {
                local_1c8 = bVar6;
                if ((PTR_DAT_0056cba4[(local_198 & 0xff) * 2 + 1] & 0x80) != 0) {
                  local_188 = local_188 + 1;
                  local_1c7 = __inc();
                }
                _mbtowc(local_1d0,(char *)&local_1c8,DAT_0056cbf0);
                *pwVar8 = local_1d0[0];
                pwVar8 = pwVar8 + 1;
                local_1b4 = pwVar8;
              }
            }
            else {
              pwVar12 = (wchar_t *)((int)pwVar12 + 1);
            }
          }
          local_188 = local_188 + -1;
          if (local_198 != 0xffffffff) {
            __ungetc_lk(local_198,param_1);
          }
LAB_0052c4f3:
          if (pwVar12 == pwVar8) goto LAB_0052c8e3;
          if ((local_192 == '\0') && (local_1bc = local_1bc + 1, local_1c4 != 99)) {
            if (local_19a == '\0') {
              *(byte *)local_1b4 = 0;
            }
            else {
              *local_1b4 = L'\0';
            }
          }
        }
        else {
          if (uVar13 == 0x70) {
            local_191 = '\x01';
            goto LAB_0052c542;
          }
          if (uVar13 == 0x73) goto LAB_0052c108;
          if (uVar13 == 0x75) goto LAB_0052c542;
          if (uVar13 != 0x78) {
            if (uVar13 != 0x7b) goto LAB_0052c147;
            if ('\0' < local_189) {
              local_19a = '\x01';
            }
            pbVar9 = param_2 + 1;
            pbVar14 = pbVar9;
            if (*pbVar9 == 0x5e) {
              pbVar14 = param_2 + 2;
              local_1a5 = 0xff;
            }
            if (local_1c0 == (undefined1 *)0x0) {
              local_1c = &stack0xfffffe14;
              local_1c0 = &stack0xfffffe14;
              local_8 = (undefined *)0xffffffff;
            }
            puVar2 = local_1c0;
            _memset(local_1c0,0,0x20);
            bVar6 = local_19c;
            if ((local_1c4 == 0x7b) && (*pbVar14 == 0x5d)) {
              puVar2[0xb] = 0x20;
              pbVar14 = pbVar14 + 1;
              bVar6 = 0x5d;
            }
            while (bVar5 = *pbVar14, bVar5 != 0x5d) {
              if (((bVar5 == 0x2d) && (bVar6 != 0)) && (bVar1 = pbVar14[1], bVar1 != 0x5d)) {
                bVar5 = bVar1;
                if (bVar6 < bVar1) {
                  bVar5 = bVar6;
                  bVar6 = bVar1;
                }
                if (bVar5 <= bVar6) {
                  uVar7 = (uint)bVar5;
                  local_1d8 = (uint)(byte)((bVar6 - bVar5) + 1);
                  do {
                    puVar2[uVar7 >> 3] = puVar2[uVar7 >> 3] | '\x01' << ((byte)uVar7 & 7);
                    uVar7 = uVar7 + 1;
                    local_1d8 = local_1d8 - 1;
                  } while (local_1d8 != 0);
                }
                pbVar14 = pbVar14 + 2;
                bVar6 = 0;
              }
              else {
                local_19c = bVar5;
                puVar2[bVar5 >> 3] = puVar2[bVar5 >> 3] | '\x01' << (bVar5 & 7);
                pbVar14 = pbVar14 + 1;
                bVar6 = local_19c;
              }
            }
            pwVar8 = local_1b4;
            uVar13 = local_1c4;
            param_2 = pbVar9;
            if (local_1c4 == 0x7b) {
              param_2 = pbVar14;
            }
            goto LAB_0052c2d2;
          }
LAB_0052becf:
          if (local_198 == 0x2d) {
            local_19b = '\x01';
LAB_0052c3f5:
            local_190 = local_190 + -1;
            if ((local_190 == 0) && (local_1b8 != 0)) {
              local_181 = '\x01';
            }
            else {
              local_188 = local_188 + 1;
              local_198 = __inc();
            }
          }
          else if (local_198 == 0x2b) goto LAB_0052c3f5;
          if (local_198 == 0x30) {
            local_188 = local_188 + 1;
            local_198 = __inc();
            if (((char)local_198 == 'x') || ((char)local_198 == 'X')) {
              local_188 = local_188 + 1;
              local_198 = __inc();
              if ((local_1b8 != 0) && (local_190 = local_190 + -2, local_190 < 1)) {
                local_181 = local_181 + '\x01';
              }
              uVar13 = 0x78;
            }
            else {
              local_1a0 = 1;
              if (uVar13 == 0x78) {
                local_188 = local_188 + -1;
                if (local_198 != 0xffffffff) {
                  __ungetc_lk(local_198,param_1);
                }
                local_198 = 0x30;
              }
              else {
                if ((local_1b8 != 0) && (local_190 = local_190 + -1, local_190 == 0)) {
                  local_181 = local_181 + '\x01';
                }
                uVar13 = 0x6f;
              }
            }
          }
LAB_0052c585:
          uVar7 = local_198;
          lVar16 = local_1b0;
          if (local_1cc == 0) {
            while (local_181 == '\0') {
              local_1b0 = lVar16;
              if ((uVar13 == 0x78) || (uVar13 == 0x70)) {
                iVar3 = _isxdigit(uVar7);
                if (iVar3 != 0) {
                  local_1a4 = local_1a4 << 4;
                  iVar3 = _isdigit(uVar7);
                  if (iVar3 == 0) {
                    uVar7 = (uVar7 & 0xffffffdf) - 7;
                  }
                  goto LAB_0052c762;
                }
LAB_0052c75c:
                local_181 = local_181 + '\x01';
              }
              else {
                iVar3 = _isdigit(uVar7);
                if (iVar3 == 0) goto LAB_0052c75c;
                if (uVar13 == 0x6f) {
                  if (0x37 < (int)uVar7) goto LAB_0052c75c;
                  local_1a4 = local_1a4 << 3;
                }
                else {
                  local_1a4 = local_1a4 * 10;
                }
              }
LAB_0052c762:
              lVar16 = local_1b0;
              if (local_181 == '\0') {
                local_1a0 = local_1a0 + 1;
                local_1a4 = local_1a4 + -0x30 + uVar7;
                if ((local_1b8 == 0) || (local_190 = local_190 + -1, local_190 != 0)) {
                  local_188 = local_188 + 1;
                  uVar7 = __inc();
                  lVar16 = local_1b0;
                }
                else {
                  local_181 = '\x01';
                }
              }
              else {
                local_188 = local_188 + -1;
                if (uVar7 != 0xffffffff) {
                  __ungetc_lk(uVar7,param_1);
                  lVar16 = local_1b0;
                }
              }
            }
            local_198 = uVar7;
            if (local_19b != '\0') {
              local_1a4 = -local_1a4;
            }
          }
          else {
            while (local_181 == '\0') {
              local_1b0 = lVar16;
              if ((uVar13 == 0x78) || (uVar13 == 0x70)) {
                iVar3 = _isxdigit(uVar7);
                if (iVar3 != 0) {
                  local_1b0 = local_1b0 << 4;
                  iVar3 = _isdigit(uVar7);
                  if (iVar3 == 0) {
                    uVar7 = (uVar7 & 0xffffffdf) - 7;
                  }
                  goto LAB_0052c64d;
                }
LAB_0052c647:
                local_181 = local_181 + '\x01';
              }
              else {
                iVar3 = _isdigit(uVar7);
                if (iVar3 == 0) goto LAB_0052c647;
                if (uVar13 == 0x6f) {
                  if (0x37 < (int)uVar7) goto LAB_0052c647;
                  local_1b0 = local_1b0 << 3;
                }
                else {
                  lVar16 = __allmul(local_1b0,10,0);
                  local_1b0 = lVar16;
                }
              }
LAB_0052c64d:
              if (local_181 == '\0') {
                local_1a0 = local_1a0 + 1;
                if ((local_1b8 == 0) || (local_190 = local_190 + -1, local_190 != 0)) {
                  local_188 = local_188 + 1;
                  local_1b0 = local_1b0 + (int)(uVar7 - 0x30);
                  uVar7 = __inc();
                  lVar16 = local_1b0;
                }
                else {
                  local_181 = '\x01';
                  lVar16 = local_1b0 + (int)(uVar7 - 0x30);
                }
              }
              else {
                local_188 = local_188 + -1;
                lVar16 = local_1b0;
                if (uVar7 != 0xffffffff) {
                  __ungetc_lk(uVar7,param_1);
                  lVar16 = local_1b0;
                }
              }
            }
            local_1b0._4_4_ = (int)((ulonglong)lVar16 >> 0x20);
            local_1b0._0_4_ = (int)lVar16;
            local_198 = uVar7;
            if (local_19b != '\0') {
              lVar16 = CONCAT44(-(local_1b0._4_4_ + (uint)((int)local_1b0 != 0)),-(int)local_1b0);
            }
          }
          if (uVar13 == 0x46) {
            local_1a0 = 0;
          }
          if (local_1a0 == 0) goto LAB_0052c8e3;
          local_1b0 = lVar16;
          if (local_192 == '\0') {
            local_1bc = local_1bc + 1;
            iVar3 = local_1a4;
            pwVar8 = local_1b4;
LAB_0052c816:
            local_1b0 = lVar16;
            if (local_1cc == 0) {
              if (local_191 == '\0') {
                *pwVar8 = (wchar_t)iVar3;
              }
              else {
                *(int *)pwVar8 = iVar3;
              }
            }
            else {
              *(longlong *)pwVar8 = lVar16;
            }
          }
        }
LAB_0052c842:
        local_199 = local_199 + '\x01';
        pbVar14 = param_2 + 1;
      }
      else {
        local_188 = local_188 + 1;
        uVar7 = __inc();
        local_198 = uVar7;
        if (*param_2 != uVar7) goto LAB_0052c8aa;
        pbVar14 = param_2 + 1;
        if ((PTR_DAT_0056cba4[(uVar7 & 0xff) * 2 + 1] & 0x80) != 0) {
          local_188 = local_188 + 1;
          uVar13 = __inc();
          if (param_2[1] != uVar13) {
            if (uVar13 != 0xffffffff) {
              __ungetc_lk(uVar13,param_1);
            }
            goto LAB_0052c8aa;
          }
          local_188 = local_188 + -1;
          pbVar14 = param_2 + 2;
        }
      }
      param_2 = pbVar14;
      if ((local_198 == 0xffffffff) && ((*param_2 != 0x25 || (param_2[1] != 0x6e))))
      goto LAB_0052c8e3;
      goto LAB_0052bbf1;
    }
    local_188 = local_188 + -1;
    do {
      local_188 = local_188 + 1;
      iVar3 = __inc();
      iVar4 = _isspace(iVar3);
    } while (iVar4 != 0);
    if (iVar3 != -1) {
      __ungetc_lk(iVar3,param_1);
    }
    do {
      param_2 = param_2 + 1;
      iVar3 = _isspace((uint)*param_2);
    } while (iVar3 != 0);
  } while( true );
}

