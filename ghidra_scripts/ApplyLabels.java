import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;

// Applies our bootstrapped function-name identifications from Phase 1 analysis.
public class ApplyLabels extends GhidraScript {
    String[][] labels = {
        {"0040d8e0","WinMain"},
        {"004fdf00","InitCommP2PNotifyWindow"},
        {"004edc50","InitDirectInput"},
        {"004ee5b0","InitDirectSound"},
        {"004efaa0","InitDirectDraw"},
        {"0040f400","Shutdown"},
    };
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String[] pair : labels) {
            Address a = currentProgram.getAddressFactory().getAddress(pair[0]);
            Function f = fm.getFunctionAt(a);
            if (f == null) { println("MISSING FUNC AT "+pair[0]); continue; }
            f.setName(pair[1], SourceType.USER_DEFINED);
            println("LABELED "+pair[0]+" -> "+pair[1]);
        }
    }
}
