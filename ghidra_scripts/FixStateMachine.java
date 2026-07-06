import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.lang.Register;
import ghidra.program.model.data.IntegerDataType;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import java.util.*;

public class FixStateMachine extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        Function target = null;
        for (Function f : fm.getFunctions(true)) if (f.getName().equals("ChangeGameState")) { target = f; break; }
        if (target == null) { println("ChangeGameState not found"); return; }

        Register esi = currentProgram.getRegister("ESI");
        ParameterImpl p = new ParameterImpl("newStateId", IntegerDataType.dataType, esi, currentProgram);
        target.setCustomVariableStorage(true);
        target.replaceParameters(Arrays.asList(p),
            Function.FunctionUpdateType.CUSTOM_STORAGE, true, SourceType.USER_DEFINED);
        println("Set ChangeGameState(int newStateId) via ESI");

        // Rename the associated globals discovered via call-site analysis.
        renameGlobal("007934d0", "g_currentGameState");
        renameGlobal("005b33ec", "g_pendingGameState");
        renameGlobal("007934d4", "g_stateChangeRequested");
        renameGlobal("005b33f8", "g_gameStateVTableArray");
        renameGlobal("00793508", "g_stateChangeInProgress");
    }
    void renameGlobal(String addrHex, String name) throws Exception {
        Address a = currentProgram.getAddressFactory().getAddress(addrHex);
        Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(a);
        if (s != null) {
            s.setName(name, SourceType.USER_DEFINED);
            println("RENAMED "+addrHex+" -> "+name);
        } else {
            createLabel(a, name, true);
            println("LABELED "+addrHex+" -> "+name);
        }
    }
}
