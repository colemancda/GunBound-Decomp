/* FUN_004ff770 - 0x004ff770 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"

/* capped-16 string length - the inlined equivalent of FUN_004f7360 (orig
 * 0x4f7360: scan for NUL, cap at 0x10), whose AL return Ghidra dropped at
 * the Sha1Absorb call sites below (their length arg). See Sha1Absorb.c. */
static uint gb_capped16_len(const char *s) {
  uint n = 0;
  while (n < 0x10 && s[n] != '\0') { n = n + 1; }
  return n;
}


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_004ff770(int *param_1,int param_2)

{
  undefined4 *puVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  undefined4 *local_3190;
  int local_318c;
  undefined4 local_3188;
  undefined4 local_3184;
  undefined4 local_3180;
  undefined4 local_317c;
  undefined1 local_3178;
  sockaddr local_3174;
  int local_3164;
  uint local_3160;
  int local_315c;
  _FILETIME local_3158;
  ushort local_3150;
  undefined1 local_314e [16];
  undefined4 local_313e;
  undefined4 local_313a;
  undefined4 local_3136;
  undefined4 local_3132;
  undefined4 local_312e;
  undefined1 local_3128 [96];
  undefined1 local_30c8 [0x20c];  /* schedule is 0x20c - see BuildSystemInfoBlob */
  char local_2ec0;
  ushort local_2ebc;
  undefined4 local_2eba;
  undefined4 local_2eb6;
  undefined4 local_2eb2;
  undefined4 local_2eae;
  undefined1 local_2eaa [16];
  undefined4 local_2e9a [1491];
  undefined1 local_174c [12];
  undefined2 uStack_1740;
  ushort local_173e;
  undefined2 auStack_173c [2972];
  undefined4 uStack_4;
  
  uStack_4 = 0x4ff77a;
  local_3174.sa_data[0] = '\0';
  local_3174.sa_data[1] = '\0';
  local_3174.sa_data[2] = '\0';
  local_3174.sa_data[3] = '\0';
  local_3174.sa_data[4] = '\0';
  local_3174.sa_data[5] = '\0';
  local_3174.sa_data[6] = '\0';
  local_3174.sa_data[7] = '\0';
  local_3174.sa_data[8] = '\0';
  local_3174.sa_data[9] = '\0';
  local_3174.sa_data[10] = '\0';
  local_3174.sa_data[0xb] = '\0';
  local_3174.sa_data[0xc] = '\0';
  local_3174.sa_data[0xd] = '\0';
  local_3174.sa_family = 0;
  local_3164 = 0x10;
  if ((param_2 == 0) &&
     (uVar3 = recvfrom(param_1[0xa2],(char *)&local_2ebc,6000,0,&local_3174,&local_3164),
     0 < (int)uVar3)) {
    if (uVar3 == 0x26) {
      if ((local_2ebc == 0x26) && (iVar4 = FUN_004fcdf0(local_2eaa,0x10), iVar4 == 0)) {
        local_3184 = local_2eb6;
        local_3188 = local_2eba;
        local_3180 = local_2eb2;
        local_317c = local_2eae;
        local_3178 = 0;
        cVar2 = FUN_004fe860(param_1,&local_3190);
        if (cVar2 != '\0') {
          iVar4 = FUN_005006f0();
          if (iVar4 != 0) {
            (**(code **)*param_1)
                      (1,local_2eaa,*(undefined2 *)(iVar4 + 0x10),iVar4 + 0x14,
                       *(undefined2 *)(iVar4 + 0x12),iVar4 + 4);
            FUN_00500710();
          }
          *local_3190 = CONCAT22(SUBFIELD(local_3174.sa_data,4,undefined2),SUBFIELD(local_3174.sa_data,2,undefined2));
          *(undefined2 *)(local_3190 + 1) = SUBFIELD(local_3174.sa_data,0,undefined2);
          return;
        }
      }
    }
    else if (((0x35 < uVar3) && (local_2ebc == uVar3)) &&
            (iVar4 = FUN_004fcdf0(local_2eaa,0x10), iVar4 == 0)) {
      local_3184 = local_2eb6;
      local_3188 = local_2eba;
      local_3180 = local_2eb2;
      local_317c = local_2eae;
      local_3178 = 0;
      cVar2 = FUN_004fe860(param_1,&local_3190);
      if (cVar2 == '\0') {
        FUN_004fe8d0(&local_3188,CONCAT22(SUBFIELD(local_3174.sa_data,4,undefined2),SUBFIELD(local_3174.sa_data,2,undefined2)),
                     CONCAT22(SUBFIELD(local_3174.sa_data,2,undefined2),SUBFIELD(local_3174.sa_data,0,undefined2)),
                     CONCAT22(SUBFIELD(local_3174.sa_data,4,undefined2),SUBFIELD(local_3174.sa_data,2,undefined2)),
                     CONCAT22(SUBFIELD(local_3174.sa_data,2,undefined2),SUBFIELD(local_3174.sa_data,0,undefined2)));
        cVar2 = FUN_004fe860(param_1,&local_3190);
        if (cVar2 == '\0') {
          return;
        }
      }
      else {
        *local_3190 = CONCAT22(SUBFIELD(local_3174.sa_data,4,undefined2),SUBFIELD(local_3174.sa_data,2,undefined2));
        *(undefined2 *)(local_3190 + 1) = SUBFIELD(local_3174.sa_data,0,undefined2);
      }
      puVar1 = local_3190;
      local_3150 = 0x26;
      cVar2 = FUN_004fcd80(local_314e,0x10);
      if (cVar2 != '\0') {
        local_313e = local_2eba;
        local_3136 = local_2eb2;
        local_313a = local_2eb6;
        local_3132 = local_2eae;
        local_312e = local_2e9a[0];
        sendto(param_1[0xa2],(char *)&local_3150,(uint)local_3150,0,&local_3174,0x10);
        local_2ec0 = FUN_00500900();
        if (local_2ec0 == '\0') {
          uVar3 = local_2ebc - 0x26;
          local_318c = (int)(uVar3 + ((int)uVar3 >> 0x1f & 0xfU)) >> 4;
          uVar3 = uVar3 & 0x8000000f;
          bVar5 = uVar3 == 0;
          if ((int)uVar3 < 0) {
            bVar5 = (uVar3 - 1 | 0xfffffff0) == 0xffffffff;
          }
          if ((bVar5) && (local_318c != 0)) {
            /* DROPPED length arg (2026-07-18), see Sha1Absorb.c. P2P/UDP
             * path, not on the ServerSelect->world-login route. The two
             * dead FUN_004f7360() calls were the dropped-return length
             * computations - folded into gb_capped16_len; call 3 is the
             * fixed 4-byte trailer. */
            FUN_004f76c0();
            Sha1Absorb((int)local_3128,(byte *)&local_2eba,gb_capped16_len((char *)&local_2eba));
            Sha1Absorb((int)local_3128,(byte *)local_2eaa,gb_capped16_len((char *)local_2eaa));
            Sha1Absorb((int)local_3128,(byte *)local_2e9a,4);
            Sha1Final((int)local_3128);
            /* RECOVERED, orig 0x4ffaca-0x4ffada: key = ECX = the SHA-1
             * digest (local_3128), EDX=0x10, EDI=[esp+0xf4] = local_30c8. */
            RijndaelSetKey((uint *)local_3128,0x10,2,(uint *)local_30c8);
            /* RECOVERED (2026-07-19), orig 0x4ffae3-0x4ffaf9 (frame base =
             * esp_b+0x3190, anchored on `lea edi,[esp+0xf4]` = local_30c8):
             *   lea ecx,[esp+0xf4] / push ecx ; arg1 = SCHEDULE = local_30c8
             *   mov eax,[esp+0x30]            ; EAX = COUNT  = local_318c
             *   lea ecx,[esp+0x1a74]          ; ECX = DEST   = local_174c
             *   lea edx,[esp+0x32a]           ; EDX = SOURCE = local_2e9a + 4
             *                                 ;   (past the 4-byte nonce that
             *                                 ;    was SHA-absorbed above) */
            FUN_004fcd50((int)local_174c,(int)local_30c8,
                         (uint *)((char *)local_2e9a + 4),local_318c);
            if ((uint)local_173e <= local_2ebc - 0x36) {
              GetSystemTimeAsFileTime(&local_3158);
              FUN_00500940(puVar1 + 8,&local_3158);
              if (0x100 < (uint)local_3190[9]) {
                local_3190 = (undefined4 *)FUN_00500b70();
                while (local_3190 != (undefined4 *)0x0) {
                  FUN_00500ba0(&local_3190,&local_318c,&local_3160);
                  uVar3 = __aulldiv(local_3158.dwLowDateTime - local_3160,
                                    (local_3158.dwHighDateTime - local_315c) -
                                    (uint)(local_3158.dwLowDateTime < local_3160),10000,0);
                  if (60000 < uVar3) {
                    FUN_005009b0();
                  }
                }
              }
              (**(code **)(*param_1 + 8))
                        (&local_3188,CONCAT22(local_173e,uStack_1740),auStack_173c,
                         CONCAT22(auStack_173c[0],local_173e),local_174c);
            }
          }
        }
      }
    }
  }
  return;
}

