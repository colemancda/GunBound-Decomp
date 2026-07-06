import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.app.decompiler.*;
public class DecompileOne extends GhidraScript {
    public void run() throws Exception {
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        FunctionManager fm = currentProgram.getFunctionManager();
        String[] addrs = getScriptArgs();
        String target = addrs.length>0 ? addrs[0] : "00443c20";
        Function f = fm.getFunctionAt(currentProgram.getAddressFactory().getAddress(target));
        if (f==null) { println("not found"); return; }
        DecompileResults r = di.decompileFunction(f, 60, monitor);
        println("=====BEGIN "+target+"=====");
        println(r.getDecompiledFunction()!=null ? r.getDecompiledFunction().getC() : "FAILED: "+r.getErrorMessage());
        println("=====END=====");
        di.dispose();
    }
}
