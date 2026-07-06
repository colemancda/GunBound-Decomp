import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.app.decompiler.*;
public class DecompileInitGame extends GhidraScript {
    public void run() throws Exception {
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        FunctionManager fm = currentProgram.getFunctionManager();
        Function f = fm.getFunctionAt(currentProgram.getAddressFactory().getAddress("0040eaa0"));
        DecompileResults r = di.decompileFunction(f, 60, monitor);
        println("=====BEGIN=====");
        println(r.getDecompiledFunction()!=null ? r.getDecompiledFunction().getC() : "FAILED: "+r.getErrorMessage());
        println("=====END=====");
        di.dispose();
    }
}
