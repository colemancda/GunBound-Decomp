/* CommEngineDrainAndCloseConnections - 0x004fddd0 in the original binary.
 *
 * Evidence is from the caller and its neighbours.  The sole caller is
 * DestroyCommP2POwner, which first shuts down the owner's current
 * connection (via CommEngineCloseConnection or shutdown(s, 2)) and then
 * calls this at 0x004fd2b0 with the timeout 3000 on the stack.  The
 * engine sub-object is in EBX: the destructor set `lea ebx,[edi+4]`
 * (param_1 + 1, the sub-object whose vtable 0x005575b8 the same
 * destructor installs) at 0x004fd253 and nothing in between touches EBX
 * (CommEngineCloseConnection, CommConnectionList_Erase and 0x00500f90
 * leave it alone), so the call drops that argument.  It is the trailing
 * regEbx parameter and the call site now passes param_1 + 1.
 *
 * What it does with it: sets the byte at engine +0x24 (a re-entry guard,
 * never cleared), pumps the window at +0x20 with PeekMessageA /
 * TranslateMessage / DispatchMessageA and Sleep(100) until the connection
 * list count at +0xc is zero or the timeout elapses.  Whatever is left it
 * then closes one by one: slot 2 of the engine vtable
 * (CommP2POwner_OnConnectionClosed, called with (0, node) exactly as in
 * CommEngineCloseConnection), closesocket on node +8, and the same
 * unlink-and-free sequence as CommConnectionList_Erase, emptying the list
 * with AtlList_RemoveAll_38 at the end.  Name rests on that: wait for the
 * list to drain, then close the remaining connections.  LIKELY - "Drain"
 * means the wait for the list to empty, not data.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void CommEngineDrainAndCloseConnections(int param_1,int *regEbx)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  DWORD DVar5;
  int iVar6;
  DWORD DVar7;
  tagMSG local_1c;
  
  if ((char)regEbx[9] == '\0') {
    *(undefined1 *)(regEbx + 9) = 1;
    DVar5 = GetTickCount();
    while( true ) {
      iVar6 = PeekMessageA(&local_1c,(HWND)regEbx[8],0,0,1);
      while (iVar6 != 0) {
        TranslateMessage(&local_1c);
        DispatchMessageA(&local_1c);
        iVar6 = PeekMessageA(&local_1c,(HWND)regEbx[8],0,0,1);
      }
      if (regEbx[3] == 0) {
        return;
      }
      DVar7 = GetTickCount();
      if (DVar5 + param_1 <= DVar7) break;
      Sleep(100);
    }
    piVar1 = regEbx + 1;
    piVar2 = (int *)regEbx[1];
joined_r0x004fde6a:
    piVar4 = piVar2;
    if (piVar4 != (int *)0x0) {
      piVar2 = (int *)*piVar4;
      (**(code **)(*regEbx + 8))(0,piVar4);
      for (piVar3 = (int *)*piVar1; piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
        if (piVar4 == piVar3) {
          if (piVar4[2] != 0xffffffff) {
            closesocket(piVar4[2]);
          }
          if (piVar4 == (int *)*piVar1) {
            *piVar1 = *piVar4;
          }
          else {
            *(int *)piVar4[1] = *piVar4;
          }
          if (piVar4 == (int *)regEbx[2]) {
            regEbx[2] = piVar4[1];
          }
          else {
            *(int *)(*piVar4 + 4) = piVar4[1];
          }
          FUN_00500f90();
          *piVar4 = regEbx[5];
          iVar6 = regEbx[3];
          regEbx[5] = (int)piVar4;
          regEbx[3] = iVar6 + -1;
          if (iVar6 + -1 == 0) {
            AtlList_RemoveAll_38();
          }
          break;
        }
      }
      goto joined_r0x004fde6a;
    }
  }
  return;
}

