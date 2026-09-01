/* ConfigureAsyncSocket - 0x004ff350 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004ff350).  Puts a socket into the comm engine's
 * asynchronous mode, and the message number is what ties the subsystem
 * together:
 *     ioctlsocket(s, FIONBIO, &nonblocking)
 *     WSAAsyncSelect(s, engine->hwnd, 0x478, 0x33)
 *     setsockopt(s, SOL_SOCKET, SO_SNDBUF, ...)
 *     setsockopt(s, SOL_SOCKET, SO_RCVBUF, ...)
 * 0x478 is exactly the one message CommEngineNotifyWndProc handles, and the
 * hwnd comes from the same engine object CreateCommEngineNotifyWindow filled
 * in - so this is the registration side of that window procedure.  Called
 * from ConnectToHostPort.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 __thiscall ConfigureAsyncSocket(SOCKET param_1,u_long param_2,undefined4 param_3)

{
  u_long uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 sourceRecord[6];
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uVar1 = param_2;
  puStack_8 = &LAB_005377f8;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  /* RECOVERED: orig 0x4ff3cb/0x4ff3ad-0x4ff3d3/0x4ff3a5 build a 6-dword
     node-seed record Ghidra dead-coded (only the callee's EDI reads it):
     {socket, param_3[0..3], 0}.  param_3 is really a pointer to a 16-byte
     host record - it is copied out HERE, before line 44 reuses its stack
     slot as the 6000-byte setsockopt value (orig mov [esp+0x68],0x1770). */
  sourceRecord[0] = param_1;
  sourceRecord[1] = ((undefined4 *)param_3)[0];
  sourceRecord[2] = ((undefined4 *)param_3)[1];
  sourceRecord[3] = ((undefined4 *)param_3)[2];
  sourceRecord[4] = ((undefined4 *)param_3)[3];
  sourceRecord[5] = 0;
  param_2 = 1;
  ioctlsocket(param_1,-0x7ffb9982,&param_2);
  iVar2 = WSAAsyncSelect(param_1,*(HWND *)(uVar1 + 0x20),0x478,0x33);
  if (iVar2 == -1) {
    FUN_00501010();
    *unaff_FS_OFFSET = local_c;
    return 0;
  }
  param_3 = 6000;
  setsockopt(param_1,0xffff,0x1002,(char *)&param_3,4);
  setsockopt(param_1,0xffff,0x1001,(char *)&param_3,4);
  /* DROPPED-REG FIX: orig 0x4ff45e `mov eax,esi` with 0x4ff455
     `lea esi,[ebp+4]` (EBP = uVar1, the engine) and 0x4ff45a
     `lea edi,[esp+0x18]` = the sourceRecord rebuilt above. */
  uVar3 = FUN_00500fa0(*(undefined4 *)(uVar1 + 8),0,(int)(uVar1 + 4),sourceRecord);
  if (*(undefined4 **)(uVar1 + 8) == (undefined4 *)0x0) {
    *(undefined4 *)(uVar1 + 4) = uVar3;
  }
  else {
    **(undefined4 **)(uVar1 + 8) = uVar3;
  }
  *(undefined4 *)(uVar1 + 8) = uVar3;
  FUN_00501010();
  *unaff_FS_OFFSET = local_c;
  return uVar3;
}

