/* FUN_00501770 - 0x00501770 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall FUN_00501770(int param_1,int param_2,int param_3)

{
  ushort *puVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  byte bVar5;
  ushort uVar6;
  SOCKET s;
  int iVar7;
  HWND hWnd;
  UINT_PTR UVar8;
  undefined4 uVar9;
  uint uVar10;
  __time32_t _Var11;
  char *pcVar12;
  byte *pbVar13;
  byte *pbVar14;
  undefined4 *puVar15;
  byte *pbVar16;
  undefined4 *unaff_FS_OFFSET;
  char *pcVar17;
  sockaddr *name;
  uint uVar18;
  uint *namelen;
  uint local_4984;
  char *local_4980;
  int local_497c;
  uint local_4978;
  int iStack_4974;
  undefined4 *local_4970;
  sockaddr local_496c;
  undefined1 local_495c;
  undefined1 local_4958 [4];
  undefined4 local_4954;
  undefined4 local_4950;
  undefined4 local_494c;
  undefined4 local_4944;
  undefined4 uStack_4940;
  undefined4 uStack_493c;
  undefined4 uStack_4938;
  undefined4 uStack_4934;
  undefined1 uStack_4930;
  undefined2 local_4928;
  undefined4 local_4924;
  undefined4 local_4920;
  undefined1 local_491c;
  undefined1 local_4917;
  char local_4914 [17];
  undefined1 local_4903;
  undefined1 local_4902;
  /* RECOVERED (2026-08-28): the 14-byte scratch name field at esp_base+0x90,
   * in the 0x8f..0x9f gap Ghidra left undeclared because its only writers were
   * the argless CopyNameField_e calls.  Every StringMap_SetAt_28 call but the 0x2010
   * one reads it back as the map value record. */
  undefined1 local_4900 [14];
  undefined1 local_48f0 [18];
  undefined1 local_48de;
  undefined1 local_48c9;
  /* RECOVERED (2026-08-28): the record's 8-char field at esp_base+0xc8, in the
   * 0xc8..0xd1 gap; written only by the two argless CopyNameField_a calls, which
   * store 8 characters plus a length byte at +9. */
  undefined1 local_48c8 [10];
  undefined2 local_48be;
  char local_48ba [82];
  undefined4 auStack_4868 [64];
  byte abStack_4768 [256];
  undefined4 local_4668;
  undefined4 local_4664;
  undefined4 local_4660;
  undefined4 local_465c;
  undefined4 local_4658;
  undefined4 local_4654;
  uint local_4650;
  undefined4 local_464c [1493];
  ushort local_2ef8;
  undefined4 local_2ef6 [7];
  undefined1 local_2ed8 [5968];
  ushort local_1788;
  undefined4 local_1786 [1498];
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_00538f8c;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  uStack_1c = 0x501796;
  uVar6 = *(ushort *)(param_2 + 2);
  puVar1 = (ushort *)(param_2 + 4);
  param_3 = param_3 + -4;
  local_497c = param_1;
  iStack_18 = param_1;
  if (uVar6 < 0x2011) {
    if (uVar6 == 0x2010) {
      /* RECOVERED (2026-07-19), orig 0x501ea0-0x501eb4 (frame base =
       * esp_b+0x4990, from `mov [esp+0x14],edi` = local_497c at 0x5017b4):
       *   mov ecx,[edi+0x1784] / push 0x1770 / push ebx / push ecx
       *                              ; capacity=6000, input=ebx=puVar1, schedule
       *   lea ecx,[esp+0x3214]       ; ECX = OUTPUT = &local_1788 (esp_b+0x3208)
       *   EAX = param_3              ; INPUTLEN (guarded by `cmp eax,0x10`)
       * The port dropped ECX entirely and shifted every remaining argument
       * left by one, so the schedule landed in the output slot. */
      if ((0xf < param_3) &&
         (cVar4 = (char)FUN_004f72b0((undefined4 *)&local_1788,
                                     *(int *)(param_1 + 0x1784),(int)puVar1,6000,(uint)param_3),
          cVar4 != '\0')) {
        local_4970 = local_2ef6;
        puVar15 = local_1786;
        local_2ef8 = local_1788;
        if (local_1788 != 0) {
          local_4980 = (char *)(param_1 + 0x17cc);
          local_4984 = (uint)local_1788;
          local_4978 = param_1 - 0x2f4;
          do {
            *local_4970 = *puVar15;
            local_4970 = local_4970 + 1;
            SUBFIELD(local_496c,0,undefined4) = puVar15[1];
            SUBFIELD(local_496c.sa_data,2,undefined4) = puVar15[2];
            SUBFIELD(local_496c.sa_data,6,undefined4) = puVar15[3];
            SUBFIELD(local_496c.sa_data,10,undefined4) = puVar15[4];
            local_495c = 0;
            uVar10 = 0;
            do {
              cVar4 = *(char *)((int)puVar15 + uVar10 + 0x14);
              uVar18 = uVar10;
              if (cVar4 == '\0') break;
              bVar5 = (char)uVar10 + 1;
              uVar18 = (uint)bVar5;
              *(char *)((int)&local_4924 + uVar10) = cVar4;
              uVar10 = uVar18;
            } while (bVar5 < 0xc);
            local_4917 = (char)uVar18;
            *(undefined1 *)((int)&local_4924 + uVar18) = 0;
            uVar10 = 0;
            do {
              bVar5 = (byte)uVar10;
              if (local_496c.sa_data[uVar10 - 2] == '\0') break;
              bVar5 = bVar5 + 1;
              local_48ba[uVar10] = local_496c.sa_data[uVar10 - 2];
              uVar10 = (uint)bVar5;
            } while (bVar5 < 0x10);
            local_48ba[0x11] = bVar5;
            local_48ba[bVar5] = '\0';
            /* RECOVERED (2026-08-28), orig 0x501f8d-0x501faf: ESI is the
             * 14-byte value record the inline 12-byte copy above just built at
             * &local_4924, EDI the string map local_4980 = param_1 + 0x17cc. */
            StringMap_SetAt_28((undefined4)local_48ba,&local_4924,(int *)local_4980);
            uVar6 = *(ushort *)((int)puVar15 + 0x26);
            /* RECOVERED (2026-08-19): the two register arguments, dropped
             * because DispatchP2PMessage (0x504970) had no declaration and
             * every call compiled __cdecl.  orig 0x501fb4-0x501fdb, with the
             * record cursor in EBX (= puVar15 + 0x20 at 0x501fb4):
             *   0x501fb9 mov dx,[ebx+2] / 0x501fc5 movzx esi,dx / mov ecx,esi
             *     -> ECX = the payload LENGTH at puVar15 + 0x26, i.e. uVar6,
             *        the value this loop already reads on the line above
             *   0x501fd9 mov edx,ebx (after two `add ebx,2`)
             *     -> EDX = the PAYLOAD at puVar15 + 0x28, exactly the base the
             *        cursor advance on the line below steps past. */
            DispatchP2PMessage(uVar6,(int)puVar15 + 0x28,
                               local_4978,&local_496c,puVar15[8],
                               *(undefined2 *)(puVar15 + 9));
            puVar15 = (undefined4 *)((int)puVar15 + uVar6 + 0x28);
            local_4984 = local_4984 - 1;
          } while (local_4984 != 0);
          local_4984 = 0;
        }
        FUN_00502500(0x2011);
      }
      goto LAB_00502483;
    }
    if (0x101f < uVar6) {
      if (uVar6 == 0x1ffe) {
        if (3 < param_3) {
          local_4954 = 0;
          local_4950 = 0;
          local_494c = 0;
          local_c = 1;
          iVar7 = (**(code **)(DAT_005b1444 + 0xc))();
          local_4978 = iVar7 + 0x10;
          iVar7 = (**(code **)(DAT_005b1444 + 0xc))();
          iVar7 = iVar7 + 0x10;
          local_c = 2;
          uVar6 = *puVar1;
          pbVar13 = (byte *)(param_2 + 6);
          iStack_4974 = iVar7;
          if (uVar6 < 0xb) {
            if (uVar6 != 0) {
              local_4984 = (uint)uVar6;
              do {
                uVar10 = (uint)*pbVar13;
                pbVar14 = pbVar13 + 1;
                uVar18 = (uint)(*pbVar13 >> 2);
                pbVar13 = pbVar14;
                pbVar16 = (byte *)auStack_4868;
                for (; uVar18 != 0; uVar18 = uVar18 - 1) {
                  *(undefined4 *)pbVar16 = *(undefined4 *)pbVar13;
                  pbVar13 = pbVar13 + 4;
                  pbVar16 = pbVar16 + 4;
                }
                for (uVar18 = uVar10 & 3; uVar18 != 0; uVar18 = uVar18 - 1) {
                  *pbVar16 = *pbVar13;
                  pbVar13 = pbVar13 + 1;
                  pbVar16 = pbVar16 + 1;
                }
                pbVar14 = pbVar14 + uVar10;
                *(undefined1 *)((int)auStack_4868 + uVar10) = 0;
                uVar10 = (uint)*pbVar14;
                pbVar13 = pbVar14 + 1;
                pbVar16 = abStack_4768;
                for (uVar18 = (uint)(*pbVar14 >> 2); uVar18 != 0; uVar18 = uVar18 - 1) {
                  *(undefined4 *)pbVar16 = *(undefined4 *)pbVar13;
                  pbVar13 = pbVar13 + 4;
                  pbVar16 = pbVar16 + 4;
                }
                for (uVar18 = uVar10 & 3; uVar18 != 0; uVar18 = uVar18 - 1) {
                  *pbVar16 = *pbVar13;
                  pbVar13 = pbVar13 + 1;
                  pbVar16 = pbVar16 + 1;
                }
                abStack_4768[uVar10] = 0;
                pbVar13 = pbVar14 + 1 + uVar10;
                FUN_004055b0();
                FUN_004055b0();
                FUN_00502890((undefined4)&local_4978,(int)local_4958);
                local_4984 = local_4984 - 1;
              } while (local_4984 != 0);
              local_4984 = 0;
              param_1 = local_497c;
            }
            iVar7 = iStack_4974;
            (**(code **)(**(int **)(param_1 + 0x17bc) + 0x10))(local_4958);
          }
          local_c = 1;
          piVar2 = (int *)(iVar7 + -4);
          LOCK();
          iVar3 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar3 + -1 < 1) {
            (**(code **)(**(int **)(iVar7 + -0x10) + 4))((undefined4 *)(iVar7 + -0x10));
          }
          piVar2 = (int *)(local_4978 - 4);
          LOCK();
          iVar7 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar7 == 1 || iVar7 + -1 < 0) {
            (**(code **)(**(int **)(local_4978 - 0x10) + 4))((undefined4 *)(local_4978 - 0x10));
          }
          FUN_00502a90((int)local_4958);
        }
      }
      else if ((uVar6 == 0x1fff) && (param_3 == 2)) {
        /* DROPPED-REG FIX 2026-08-28: the node, `mov esi,[edi+0x1780]` at
           0x501d0d with edi = param_1. */
        FUN_004fdda0((int *)(param_1 + -0x2f0),*(int *)(param_1 + 0x1780));
        (**(code **)(**(int **)(param_1 + 0x17bc) + 8))(*puVar1);
      }
      goto LAB_00502483;
    }
    if (uVar6 == 0x101f) {
      if (param_3 == 6) {
        *(undefined1 *)(param_1 + 0x1788) = 1;
        *(undefined2 *)(param_1 + 0x178c) = 2;
        *(undefined4 *)(param_1 + 0x1790) = *(undefined4 *)puVar1;
        *(undefined2 *)(param_1 + 0x178e) = *(undefined2 *)(param_2 + 8);
        *(undefined4 *)(param_1 + 0x1794) = 0;
        *(undefined4 *)(param_1 + 0x1798) = 0;
      }
      goto LAB_00502483;
    }
    if (uVar6 == 0x1001) {
      if (param_3 == 4) {
        if (*(void **)(param_1 + 0x1784) != (void *)0x0) {
          _free(*(void **)(param_1 + 0x1784));
        }
        /* RECOVERED (2026-07-18), orig 0x501b4c `mov esi,0x2dbabe65` /
         * 0x501b5f `mov [edi+0x1784],eax`: the checksum base was a dropped
         * ESI argument and the schedule pointer a dropped return value. */
        uVar9 = (undefined4)AllocCipherSchedule(0x2dbabe65);
        *(undefined4 *)(param_1 + 0x1784) = uVar9;
        cVar4 = FUN_004fcd80(local_4914,0x11,param_1 + 0x182c);
        if (((cVar4 != '\0') && (cVar4 = FUN_004fcd80(&local_4944,0x15,param_1 + 0x1ab0), cVar4 != '\0')) &&
           /* RECOVERED (2026-07-19), orig 0x501baa-0x501bb5: EncodeHandshakeBlock's
            * credKey/credStr arrive in ESI/EAX (`lea esi,[esp+0x8c]` /
            * `lea eax,[esp+0x5c]`), and those two stack slots are exactly the
            * buffers the preceding pair of FUN_004fcd80 calls fills - the 0x11-byte
            * one is credKey (a 16-char name + NUL) and the 0x15-byte one is credStr
            * (20 bytes + NUL), matching BuildSystemInfoBlob's two outputs on the
            * other login path. This call site had been passing only 4 of the 6
            * arguments ever since EncodeHandshakeBlock's signature was corrected,
            * so this whole translation unit silently failed to compile and the
            * linker kept reusing a stale object file. */
           (cVar4 = EncodeHandshakeBlock(*(undefined4 *)(param_1 + 0x1784),&DAT_00551b7c,
                                 *(undefined4 *)puVar1,&local_2ef8,
                                 (char *)local_4914,(char *)&local_4944), cVar4 != '\0')) {
          local_4978 = 0x10;
          cVar4 = FUN_00503930(&local_4984,&local_497c);
          if ((cVar4 != '\0') &&
             (iVar7 = getsockname(*(SOCKET *)(param_1 + -0x40),&local_496c,(int *)&local_4978),
             iVar7 == 0)) {
            local_4660 = uStack_4940;
            local_465c = uStack_493c;
            local_4654 = uStack_4934;
            local_4664 = local_4944;
            local_4650 = local_4984;
            local_4658 = uStack_4938;
            local_4668 = 0x13;
            local_464c[0] = CONCAT22(SUBFIELD(local_464c[0],2,undefined2),SUBFIELD(local_496c.sa_data,0,undefined2));
            /* RECOVERED (2026-07-19), orig 0x501c52-0x501c86:
             *   lea eax,[esp+0x1abc] / push eax ; output = local_2ed8
             *   push ecx (=[edi+0x1784])        ; schedule
             *   mov eax,0x24                    ; EAX = INPUTLEN = 0x24
             *   lea ecx,[esp+0x334]             ; ECX = INPUT = &local_4668,
             *                                   ;   the 0x24-byte block whose
             *                                   ;   first dword is the 0x13 set
             *                                   ;   at 0x501c73 */
            cVar4 = (char)EncodeP2PPacketBlocks(*(undefined4 *)(param_1 + 0x1784),(int)local_2ed8,0x1750,
                                       (byte *)&local_4668,0x24);
            if (cVar4 != '\0') {
              FUN_00502500(0x1010);
            }
          }
        }
      }
      goto LAB_00502483;
    }
    if ((uVar6 != 0x1011) || (param_3 < 2)) goto LAB_00502483;
    local_4954 = 0;
    local_4950 = 0;
    local_494c = 0;
    local_c = 0;
    uStack_4940 = 0;
    uStack_493c = 0;
    uStack_4938 = 0;
    uStack_4934 = 0;
    uStack_4930 = 0;
    local_4978 = (uint)*puVar1;
    local_4980 = (char *)(param_2 + 6);
    local_4984 = 0x10;
    local_4944 = 0;
    if (*puVar1 == 0) {
      if (0x1d < param_3) {
        local_4970 = (undefined4 *)(param_1 + -0x2c8);
        FUN_00503bb0(param_1 + -0x2c8);
        FUN_004fefe0((int *)(param_1 + 0x17fc));
        namelen = &local_4984;
        name = &local_496c;
        s = GetConnectionSocketIfListed(*(undefined4 **)(param_1 + 0x1780),
                                        param_1 + -0x2f0);
        iVar7 = getpeername(s,name,(int *)namelen);
        pcVar12 = local_4980;
        if (iVar7 == 0) {
          sendto(*(SOCKET *)(param_1 + -0x40),local_4980,4,0,&local_496c,local_4984);
        }
        local_4980 = (char *)(param_1 + 0x179c);
        /* RECOVERED (2026-08-28).  EBX is this branch's packet cursor and it is
         * pcVar12 - Ghidra kept the register but folded the `add ebx,N` steps
         * into the offsets of the reads it modelled (src line 364's
         * `pcVar12 + 0x18` IS 0x50190b `mov ax,[ebx+8]` at ebx = pcVar12+0x10).
         * orig 0x5018af `add ebx,4` reaches the 12-byte owner nick at
         * param_2+0xa; ESI is the 14-byte scratch record at param_1+0x179c
         * that the line above just put in local_4980. */
        CopyNameField_e((int)local_4980,(int)(pcVar12 + 4));
        FUN_004fcd80(local_4914,0x11,param_1 + 0x182c);
        /* RECOVERED (2026-08-28), orig 0x5018d9/0x5018dd: `lea esi,[esp+0x7c]`
         * is local_4914 (0x4990-0x7c) and `lea eax,[esp+0x116]` is
         * local_48ba + 0x40 (0x48ba sits at esp_base+0xd6), both at zero
         * pending depth. EAX is the 18-byte destination, ESI the source. */
        FUN_004fdc50((int)(local_48ba + 0x40),(int)local_4914);
        /* RECOVERED (2026-08-28), orig 0x5018e9 `mov esi,[esp+0x10]` and
         * 0x5018bd/0x5018f4 `mov edi,[esp+0x14]` / `add edi,0x17cc`: ESI is
         * that same 14-byte record, EDI the string map at param_1+0x17cc, and
         * the pushed argument is the key. */
        StringMap_SetAt_28((undefined4)(local_48ba + 0x40),(undefined4 *)local_4980,
                     (int *)(local_497c + 0x17cc));
        /* RECOVERED (2026-08-28), orig 0x5018d1 `add ebx,0xc`: the 8-byte field
         * at param_2+0x16, i.e. pcVar12 + 0x10. */
        CopyNameField_a((int)&local_4924,(int)(pcVar12 + 0x10));
        local_4978 = CONCAT22(SUBFIELD(local_4978,2,undefined2),*(undefined2 *)(pcVar12 + 0x18));
        uVar6 = *(ushort *)(pcVar12 + 0x1a);
        pcVar12 = pcVar12 + 0x1c;
        if (100 < uVar6) {
          uVar6 = 100;
        }
        if (uVar6 != 0) {
          local_4980 = (char *)(uint)uVar6;
          do {
            /* RECOVERED (2026-08-28).  At the top of each record EBX == pcVar12
             * (proved by 0x501980 `cmp byte ptr [ebx],0` being the
             * `pcVar12[0x1c]` test below, after 0x50194e `add ebx,0x10` and
             * 0x501978 `add ebx,0xc`).  The record is [16-byte id][12-byte
             * nick][flag or 20-byte note][8-byte field][ushort status], and the
             * nick is upserted into the param_1+0x17cc map under the id. */
            CopyNameField_12((int)local_48f0,(int)pcVar12);
            CopyNameField_e((int)local_4900,(int)(pcVar12 + 0x10));
            StringMap_SetAt_28((undefined4)local_48f0,(undefined4 *)local_4900,
                         (int *)(local_497c + 0x17cc));
            if (pcVar12[0x1c] == '\0') {
              pcVar12 = pcVar12 + 0x1d;
            }
            else {
              local_4944 = *(undefined4 *)(pcVar12 + 0x1c);
              uStack_4940 = *(undefined4 *)(pcVar12 + 0x20);
              uStack_493c = *(undefined4 *)(pcVar12 + 0x24);
              uStack_4938 = *(undefined4 *)(pcVar12 + 0x28);
              uStack_4934 = *(undefined4 *)(pcVar12 + 0x2c);
              uStack_4930 = 0;
              pcVar12 = pcVar12 + 0x30;
            }
            FUN_005037d0((int)&local_48de,(int)&local_4944);
            /* RECOVERED (2026-08-28), orig 0x5019c4 `mov edi,ebx`: EDI is the
             * cursor as the two branches above left it, which is exactly the
             * current pcVar12 - witnessed by 0x5019d2 `mov cx,[ebx+8]` being
             * the `*(pcVar12 + 8)` read two lines below. */
            CopyNameField_a((int)local_48c8,(int)pcVar12);
            local_48be = *(undefined2 *)(pcVar12 + 8);
            pcVar12 = pcVar12 + 10;
            Vector_PushBack_34((int)local_4958,(undefined4)local_48f0);
            FUN_00502750(local_497c + 0x17ac,(int)local_48f0);
            FUN_00503a10((int)local_48f0,(int)local_4970);
            local_4980 = local_4980 + -1;
          } while (local_4980 != (char *)0x0);
        }
        param_1 = local_497c;
        if (*(int *)(local_497c + 0x17c0) == 0) {
          hWnd = CreateWindowExA(0,s_STATIC_00557b50,s_CBuddy2_Timer_Receiving_Window_00557b74,
                                 0x80000000,0,0,0,0,(HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,(LPVOID)0x0)
          ;
          *(HWND *)(param_1 + 0x17c0) = hWnd;
          if (hWnd != (HWND)0x0) {
            SetWindowLongA(hWnd,-0x15,param_1 + -0x2f4);
            SetWindowLongA(*(HWND *)(param_1 + 0x17c0),-4,(LONG)FUN_004fdaa0);
          }
        }
        if ((*(HWND *)(param_1 + 0x17c0) != (HWND)0x0) && (*(int *)(param_1 + 0x17c4) == 0)) {
          UVar8 = SetTimer(*(HWND *)(param_1 + 0x17c0),0x14d,60000,(TIMERPROC)0x0);
          *(UINT_PTR *)(param_1 + 0x17c4) = UVar8;
        }
        *(undefined1 *)(param_1 + 0x177d) = 1;
        *(undefined1 *)(param_1 + 0x1788) = 0;
        FUN_00501600(param_1 - 0x2f4);
        pcVar12 = (char *)&local_4924;
        pcVar17 = local_4914;
        uVar10 = 0;
        uVar18 = local_4978;
        goto LAB_00501b17;
      }
    }
    else {
      FUN_00501600(param_1 - 0x2f4);
      FUN_00503810((int)&DAT_00551cb1,(int)(local_48ba + 0x12));
      uVar18 = 0;
      pcVar12 = local_48ba + 0x12;
      pcVar17 = &DAT_00551cb1;
      uVar10 = local_4978;
LAB_00501b17:
      (**(code **)(**(int **)(param_1 + 0x17bc) + 0xc))(uVar10,pcVar17,pcVar12,uVar18,local_4958);
    }
    FUN_005028f0((int)local_4958);
    goto LAB_00502483;
  }
  if (uVar6 < 0x3004) {
    if (uVar6 == 0x3003) {
      if ((1 < param_3) && (*puVar1 == 0)) {
        SUBFIELD(local_496c.sa_data,2,undefined4) = *(undefined4 *)(param_2 + 10);
        SUBFIELD(local_496c,0,undefined4) = *(undefined4 *)(param_2 + 6);
        pcVar12 = *(char **)(param_1 + 0x17b0);
        SUBFIELD(local_496c.sa_data,6,undefined4) = *(undefined4 *)(param_2 + 0xe);
        SUBFIELD(local_496c.sa_data,10,undefined4) = *(undefined4 *)(param_2 + 0x12);
        local_495c = 0;
        if (pcVar12 != *(char **)(param_1 + 0x17b4)) {
          do {
            iVar7 = __strnicmp(pcVar12,(char *)&local_496c,0x10);
            if (iVar7 == 0) {
              FUN_005027d0(pcVar12,(undefined4 *)&local_4978,param_1 + 0x17ac);
              break;
            }
            pcVar12 = pcVar12 + 0x12;
          } while (pcVar12 != *(char **)(param_1 + 0x17b4));
        }
      }
    }
    else if (uVar6 == 0x2021) {
      /* RECOVERED (2026-07-19), orig 0x502161-0x502175 - identical shape to the
       * 0x2010 site above except `lea ecx,[esp+0x334]` (= esp_b+0x328 =
       * local_4668) is the OUTPUT buffer, and the guard is `cmp eax,0x30`. */
      if ((0x2f < param_3) &&
         (cVar4 = (char)FUN_004f72b0(&local_4668,*(int *)(param_1 + 0x1784),(int)puVar1,6000,
                                     (uint)param_3),
          cVar4 != '\0')) {
        /* RECOVERED (2026-08-28), orig 0x502185/0x502195: the decoded block
         * starts at &local_4668, with the 16-byte id at +0 and the 12-byte nick
         * at +0x10 - the same record shape the +0x1e/+0x20 pair below sits on
         * top of.  esp_b+0x338 is Ghidra's own local_4658, so the nick source
         * is named rather than reached by offset.  EBX is not a packet cursor
         * on this path: it carries puVar1 into FUN_004f72b0 at 0x50216c and
         * local_497c - 0x2f4 into DispatchP2PMessage at 0x5021e3. */
        CopyNameField_12((int)local_4958,(int)&local_4668);
        CopyNameField_e((int)local_4900,(int)&local_4658);
        iVar7 = local_497c;
        StringMap_SetAt_28((undefined4)local_4958,(undefined4 *)local_4900,
                     (int *)(iVar7 + 0x17cc));
        _Var11 = FID_conflict___time32((__time32_t *)0x0);
        /* RECOVERED (2026-08-19), same dropped register pair; orig
         * 0x5021ca/0x5021ec, anchored on this branch's own decode buffer
         * (&local_4668 = esp_b+0x328, per the note above):
         *   movzx esi,[esp+0x346] -> esp_b+0x346 = &local_4668 + 0x1e = LENGTH
         *   lea edx,[esp+0x358]   -> esp_b+0x348 = &local_4668 + 0x20 = PAYLOAD
         * The +0x1e/+0x20 pair is the [name16][tag16][len16][payload] record
         * SendP2PNamedMessage composes, sitting 0xc bytes into the decoded
         * buffer. */
        DispatchP2PMessage(*(ushort *)((int)&local_4668 + 0x1e),
                           (int)&local_4668 + 0x20,
                           iVar7 + -0x2f4,local_4958,_Var11,local_464c[0]);
      }
    }
    else if (((uVar6 == 0x3001) && (1 < param_3)) && (*puVar1 == 0)) {
      SUBFIELD(local_496c,0,undefined4) = *(undefined4 *)(param_2 + 6);
      SUBFIELD(local_496c.sa_data,2,undefined4) = *(undefined4 *)(param_2 + 10);
      SUBFIELD(local_496c.sa_data,6,undefined4) = *(undefined4 *)(param_2 + 0xe);
      SUBFIELD(local_496c.sa_data,10,undefined4) = *(undefined4 *)(param_2 + 0x12);
      local_495c = 0;
      /* RECOVERED (2026-08-28), orig 0x50206e `add ebx,0x10`: the 12-byte nick
       * at param_2+0x16, following the 16-byte id at param_2+6 that the four
       * assignments above copied into local_496c.  The cursor is a literal
       * param_2 offset on this path, as the *(param_2 + 0x22/0x26/0x2a) reads
       * below already show. */
      CopyNameField_e((int)local_4900,param_2 + 0x16);
      /* RECOVERED (2026-08-28), orig 0x50208c/0x502090: `lea esi,[esp+0x24]`
       * is &local_496c and `lea eax,[esp+0x104]` is local_48ba + 0x2e. */
      FUN_004fdc50((int)(local_48ba + 0x2e),(int)&local_496c);
      StringMap_SetAt_28((undefined4)(local_48ba + 0x2e),(undefined4 *)local_4900,
                   (int *)(local_497c + 0x17cc));
      local_4924 = *(undefined4 *)(param_2 + 0x22);
      local_4920 = *(undefined4 *)(param_2 + 0x26);
      local_4978 = CONCAT22(SUBFIELD(local_4978,2,undefined2),*(undefined2 *)(param_2 + 0x2a));
      local_491c = 0;
      FUN_004fdc50((int)local_4914,(int)&local_496c);
      iVar7 = local_497c;
      FUN_00502750(iVar7 + 0x17ac,(int)local_4914);
      FUN_00503a10((int)&local_496c,iVar7 + -0x2c8);
      /* RECOVERED (2026-08-28), orig 0x502105 `mov edi,esi` and 0x502113
       * `lea edi,[esp+0x6c]`: both sources are stack fields this branch just
       * built - the 16-byte id in local_496c and the 8-byte field in
       * local_4924 - not packet bytes. */
      CopyNameField_12((int)local_48f0,(int)&local_496c);
      CopyNameField_a((int)local_48c8,(int)&local_4924);
      local_48be = (undefined2)local_4978;
      local_48c9 = 0;
      local_48de = 0;
      (**(code **)(**(int **)(iVar7 + 0x17bc) + 0x2c))(local_48f0);
    }
    goto LAB_00502483;
  }
  if (uVar6 == 0x3fff) {
    if (1 < param_3) {
      if (*puVar1 != 0) {
        local_4984 = (uint)*puVar1;
        local_4970 = (undefined4 *)(param_1 + -0x2c8);
        puVar15 = (undefined4 *)(param_2 + 6);
        do {
          SUBFIELD(local_496c,0,undefined4) = *puVar15;
          SUBFIELD(local_496c.sa_data,2,undefined4) = puVar15[1];
          SUBFIELD(local_496c.sa_data,6,undefined4) = puVar15[2];
          SUBFIELD(local_496c.sa_data,10,undefined4) = puVar15[3];
          local_4902 = *(char *)(puVar15 + 4) != '\0';
          pcVar12 = (char *)((int)puVar15 + 0x11);
          local_495c = 0;
          if ((bool)local_4902) {
            local_4980 = (char *)((int)puVar15 + 0x1d);
            FUN_005039a0(*(undefined4 *)pcVar12,*(undefined2 *)((int)puVar15 + 0x15),
                         *(undefined4 *)((int)puVar15 + 0x17),
                         (undefined4)(local_496c.sa_data + 10),(undefined4)local_497c);
            pcVar12 = local_4980;
            param_1 = local_497c;
          }
          else {
            FUN_00503a50(local_4970,&local_496c);
            FUN_004fdc50((int)(local_48ba + 0x1c),(int)&local_496c);
            FUN_004fe500();
          }
          uVar10 = 0;
          do {
            uVar18 = uVar10;
            if (local_496c.sa_data[uVar10 - 2] == '\0') break;
            bVar5 = (char)uVar10 + 1;
            uVar18 = (uint)bVar5;
            local_4914[uVar10] = local_496c.sa_data[uVar10 - 2];
            uVar10 = uVar18;
          } while (bVar5 < 0x10);
          piVar2 = *(int **)(param_1 + 0x17bc);
          local_4903 = (undefined1)uVar18;
          local_4914[uVar18] = '\0';
          (**(code **)(*piVar2 + 0x14))(local_4914);
          local_4984 = local_4984 - 1;
          puVar15 = (undefined4 *)pcVar12;
        } while (local_4984 != 0);
      }
    }
    goto LAB_00502483;
  }
  if ((uVar6 != 0x4001) || (param_3 < 2)) goto LAB_00502483;
  local_4954 = 0;
  local_4950 = 0;
  local_494c = 0;
  local_c = 3;
  if (*puVar1 == 0) {
    if (3 < param_3) {
      iVar7 = param_2 + 8;
      if (*(ushort *)(param_2 + 6) != 0) {
        local_4984 = (uint)*(ushort *)(param_2 + 6);
        local_4980 = (char *)(param_1 + 0x17cc);
        do {
          /* RECOVERED (2026-08-28).  iVar7 IS the orig's EBX cursor over the
           * 0x26-byte records: 16-byte id at +0, 12-byte nick at +0x10 (orig
           * 0x5022fb), 8-byte field at +0x1c (orig 0x50231c), ushort at +0x24
           * - which is what the *(iVar7 + 0x24) read below already encodes.
           * TWO of the three stack destinations are one contiguous record
           * based at &local_4944 - the id at +0 and the 8-byte field at +0x12
           * - as the Vector_PushBack_1e(&local_4944,...) call below shows; 0x502326
           * `lea esi,[esp+0x5e]` is that base + 0x12 and cannot get a local of
           * its own because it starts inside uStack_4934.  The nick goes to
           * the separate scratch buffer local_4900, which StringMap_SetAt_28 then
           * copies into the param_1 + 0x17cc map under the id. */
          CopyNameField_12((int)&local_4944,iVar7);
          CopyNameField_e((int)local_4900,iVar7 + 0x10);
          StringMap_SetAt_28((undefined4)&local_4944,(undefined4 *)local_4900,
                       (int *)local_4980);
          CopyNameField_a((int)((char *)&local_4944 + 0x12),iVar7 + 0x1c);
          local_4928 = *(undefined2 *)(iVar7 + 0x24);
          iVar7 = iVar7 + 0x26;
          Vector_PushBack_1e(&local_4944,(int)&local_4954);
          local_4984 = local_4984 - 1;
        } while (local_4984 != 0);
        local_4984 = 0;
      }
      goto LAB_00502356;
    }
  }
  else {
LAB_00502356:
    (**(code **)(**(int **)(local_497c + 0x17bc) + 0x34))(local_4958);
  }
  FUN_005028f0((int)local_4958);
LAB_00502483:
  *unaff_FS_OFFSET = local_14;
  return 1;
}

