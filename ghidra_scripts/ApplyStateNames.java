import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.symbol.SourceType;

public class ApplyStateNames extends GhidraScript {
    // addr, name  (enter/exit hooks and other identified state methods)
    String[][] labels = {
        {"004e5370","State01_Title_OnEnter"},
        {"004e53b0","State01_Title_OnExit"},
        {"004e14b0","State02_ServerSelect_OnEnter"},
        {"004e17f0","State02_ServerSelect_OnExit"},
        {"00428d00","State03_GameRoomList_OnEnter"},
        {"00429480","State03_GameRoomList_OnExit"},
        {"004433f0","State05_Logo1_OnEnter"},
        {"00443430","State05_Logo1_OnExit"},
        {"00443280","State06_Logo2_OnEnter"},
        {"004432c0","State06_Logo2_OnExit"},
        {"00447760","State07_AvatarStore_OnEnter"},
        {"00448050","State07_AvatarStore_OnExit"},
        {"004d6810","State09_ReadyRoom_OnEnter"},
        {"004d7630","State09_ReadyRoom_OnExit"},
        {"0043e840","State10_Loading_OnEnter"},
        {"0043eff0","State10_Loading_OnExit"},
        {"004bb730","State11_InBattle_OnEnter"},
        {"004bcd00","State11_InBattle_OnExit"},
    };
    // vtable symbol renames: addr, name
    String[][] vtables = {
        {"00557278","vtable_State01_Title"},
        {"005570f0","vtable_State02_ServerSelect"},
        {"00555590","vtable_State05_Logo1"},
        {"00555528","vtable_State06_Logo2"},
        {"005555f8","vtable_State07_AvatarStore"},
        {"005569f8","vtable_State09_ReadyRoom"},
        {"00554018","vtable_State10_Loading"},
        {"005566d8","vtable_State11_InBattle"},
    };
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String[] p : labels) {
            Address a = currentProgram.getAddressFactory().getAddress(p[0]);
            Function f = fm.getFunctionAt(a);
            if (f == null) {
                if (getInstructionAt(a)==null) disassemble(a);
                new CreateFunctionCmd(a).applyTo(currentProgram, monitor);
                f = fm.getFunctionAt(a);
            }
            if (f != null) { f.setName(p[1], SourceType.USER_DEFINED); println("FUNC "+p[0]+" -> "+p[1]); }
            else println("MISS "+p[0]);
        }
        for (String[] p : vtables) {
            Address a = currentProgram.getAddressFactory().getAddress(p[0]);
            createLabel(a, p[1], true);
            println("VT "+p[0]+" -> "+p[1]);
        }
    }
}
