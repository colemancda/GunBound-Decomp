/* FUN_004daa60 - 0x004daa60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004daa60(int *param_1,int param_2)

{
  int iVar1;
  uint in_EAX;
  undefined4 uVar2;
  int iVar3;
  byte bVar4;
  char cVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(in_EAX);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = g_clientContext;
  *(undefined1 *)(g_clientContext + 0x45124) = param_2;
  bVar4 = (byte)in_EAX;
  *(bool *)(iVar1 + 0x45120) = (bVar4 & 0x10) == 0x10;
  *(byte *)(iVar1 + 0x45121) = (byte)(in_EAX >> 5) & 3;
  *(bool *)(iVar1 + 0x45122) = (bVar4 & 0x80) == 0x80;
  *(byte *)(iVar1 + 0x45123) = bVar4 & 0xf;
  *(byte *)(iVar1 + 0x45127) = (byte)(in_EAX >> 8) & 0xf;
  *(byte *)(iVar1 + 0x45128) = (byte)(in_EAX >> 0xc) & 3;
  *(byte *)(iVar1 + 0x45126) = (byte)(in_EAX >> 0xe) & 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(in_EAX >> 0x12 & 3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(in_EAX >> 0x10 & 3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar5 = (char)(in_EAX >> 0x18);
  if (cVar5 != *(char *)(g_clientContext + 0x45578)) {
    uVar7 = 6;
    uVar6 = 4;
    *(char *)(g_clientContext + 0x45578) = cVar5;
    iVar1 = *param_1;
    uVar2 = GetLocalizedString(&g_localizedStringTable,(in_EAX >> 0x18) + 10000);
    (**(code **)(iVar1 + 0x28))(uVar2,uVar6,uVar7);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  switch(uVar2) {
  case 0:
    CreateButtonWidget(&DAT_00e9be90,0,10,0x3f2,s_b_ready_option_00556b30,0x13d,0xe1,0x51,0x18,0,0);
    FUN_00405fb0();
    goto LAB_004dabfb;
  case 1:
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0xb,0x3f3,s_b_ready_option_00556b30,0x13d,0xe1,0x51,0x18,0,0)
    ;
LAB_004dabfb:
    FUN_00405fb0();
LAB_004dac8a:
    FUN_00405fb0();
    break;
  case 2:
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0xc,0x3f4,s_b_ready_option_00556b30,0x13d,0xe1,0x51,0x18,0,0)
    ;
    goto LAB_004dac8a;
  case 3:
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0xd,0x3f5,s_b_ready_option_00556b30,0x13d,0xe1,0x51,0x18,0,0)
    ;
  }
  switch(*(undefined1 *)(g_clientContext + 0x45124)) {
  case 2:
    CreateButtonWidget(&DAT_00e9be90,0,0x14,0x3fc,s_b_ready_option_00556b30,0x193,0xe1,0x51,0x18,0,0
                      );
    FUN_00405fb0();
    goto LAB_004dad46;
  case 4:
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x15,0x3fd,s_b_ready_option_00556b30,0x193,0xe1,0x51,0x18,0,0
                      );
LAB_004dad46:
    FUN_00405fb0();
LAB_004dadd5:
    FUN_00405fb0();
    break;
  case 6:
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x16,0x3fe,s_b_ready_option_00556b30,0x193,0xe1,0x51,0x18,0,0
                      );
    goto LAB_004dadd5;
  case 8:
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x17,0x3ff,s_b_ready_option_00556b30,0x193,0xe1,0x51,0x18,0,0
                      );
  }
  switch(*(undefined1 *)(g_clientContext + 0x45127)) {
  case 0:
    CreateButtonWidget(&DAT_00e9be90,0,0x1e,0x406,s_b_ready_option_00556b30,0x193,0xff,0x51,0x18,0,0
                      );
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    break;
  case 1:
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x1f,0x407,s_b_ready_option_00556b30,0x193,0xff,0x51,0x18,0,0
                      );
    FUN_00405fb0();
    goto LAB_004daf59;
  case 2:
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x20,0x408,s_b_ready_option_00556b30,0x193,0xff,0x51,0x18,0,0
                      );
LAB_004daf59:
    FUN_00405fb0();
    break;
  case 3:
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x21,0x409,s_b_ready_option_00556b30,0x193,0xff,0x51,0x18,0,0
                      );
  }
  switch(*(undefined1 *)(g_clientContext + 0x45128)) {
  case 0:
    CreateButtonWidget(&DAT_00e9be90,0,0x32,0x41a,s_b_ready_option_00556b30,0x193,0x11d,0x51,0x18,0,
                       0);
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = 0x58;
    break;
  case 1:
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x33,0x41b,s_b_ready_option_00556b30,0x193,0x11d,0x51,0x18,0,
                       0);
    FUN_00405fb0();
    FUN_00405fb0();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = 0x28;
    break;
  case 2:
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x34,0x41c,s_b_ready_option_00556b30,0x193,0x11d,0x51,0x18,0,
                       0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = 0x38;
    break;
  case 3:
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x35,0x41d,s_b_ready_option_00556b30,0x193,0x11d,0x51,0x18,0,
                       0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = 0x48;
    break;
  default:
    goto switchD_004dafd1_default;
  }
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
switchD_004dafd1_default:
  cVar5 = *(char *)(g_clientContext + 0x45126);
  if (cVar5 == '\0') {
    CreateButtonWidget(&DAT_00e9be90,0,0x3c,0x424,s_b_ready_option_00556b30,0x13d,0x11d,0x51,0x18,0,
                       0);
    FUN_00405fb0();
LAB_004db263:
    FUN_00405fb0();
  }
  else {
    if (cVar5 == '\x01') {
      FUN_00405fb0();
      CreateButtonWidget(&DAT_00e9be90,0,0x3d,0x425,s_b_ready_option_00556b30,0x13d,0x11d,0x51,0x18,
                         0,0);
      goto LAB_004db263;
    }
    if (cVar5 == '\x02') {
      FUN_00405fb0();
      FUN_00405fb0();
      CreateButtonWidget(&DAT_00e9be90,0,0x3e,0x426,s_b_ready_option_00556b30,0x13d,0x11d,0x51,0x18,
                         0,0);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = *(int *)(&DAT_0056d350 + *(char *)(g_clientContext + 0x44ef8) * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(iVar3 % iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  switch(uVar2) {
  case 0:
    CreateButtonWidget(&DAT_00e9be90,0,0x46,0x42e,s_b_ready_option_00556b30,0x13d,0xff,0x51,0x18,0,0
                      );
    FUN_00405fb0();
    break;
  case 1:
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x47,0x42f,s_b_ready_option_00556b30,0x13d,0xff,0x51,0x18,0,0
                      );
    break;
  case 2:
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x48,0x430,s_b_ready_option_00556b30,0x13d,0xff,0x51,0x18,0,0
                      );
    goto LAB_004db3cd;
  case 3:
    FUN_00405fb0();
    FUN_00405fb0();
    FUN_00405fb0();
    CreateButtonWidget(&DAT_00e9be90,0,0x49,0x431,s_b_ready_option_00556b30,0x13d,0xff,0x51,0x18,0,0
                      );
  default:
    goto switchD_004db2fc_default;
  }
  FUN_00405fb0();
LAB_004db3cd:
  FUN_00405fb0();
switchD_004db2fc_default:
  FUN_004db720();
  FUN_004db920();
  RefreshReadyRoomControls(param_1,1,0);
  return;
}

