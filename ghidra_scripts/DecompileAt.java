// Like DecompileOne, but creates the function first if auto-analysis
// didn't define one at the address (vtable-only-referenced functions,
// e.g. the shared widget SetFocus/dtor impl at 0x50e860).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.app.decompiler.*;

public class DecompileAt extends GhidraScript {
    public void run() throws Exception {
        String[] addrs = getScriptArgs();
        String target = addrs.length > 0 ? addrs[0] : "0050e860";
        Address a = currentProgram.getAddressFactory().getAddress(target);
        FunctionManager fm = currentProgram.getFunctionManager();
        Function f = fm.getFunctionAt(a);
        if (f == null) {
            println("no function at " + target + " - disassembling and creating one");
            disassemble(a);
            f = createFunction(a, null);
            if (f == null) { println("createFunction FAILED at " + target); return; }
        }
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        DecompileResults r = di.decompileFunction(f, 60, monitor);
        println("=====BEGIN " + target + "=====");
        println(r.getDecompiledFunction() != null ? r.getDecompiledFunction().getC()
                                                  : "FAILED: " + r.getErrorMessage());
        println("=====END=====");
        di.dispose();
    }
}
