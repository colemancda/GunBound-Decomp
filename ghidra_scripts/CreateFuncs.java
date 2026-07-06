import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.app.cmd.function.CreateFunctionCmd;

// Creates functions at code addresses that are vtable targets but were never
// bound to Function objects by auto-analysis.
public class CreateFuncs extends GhidraScript {
    public void run() throws Exception {
        String[] targets = {"004fdef0","004285c0","00428b90","00428d00","00429730","00442240","00429810",
                            "004431a0","004435b0","004b9cd2","004e0210","004e5320"};
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String t : targets) {
            Address a = currentProgram.getAddressFactory().getAddress(t);
            Function existing = fm.getFunctionAt(a);
            if (existing != null) { println(t+" already a function: "+existing.getName()); continue; }
            if (getInstructionAt(a) == null) disassemble(a);
            CreateFunctionCmd cmd = new CreateFunctionCmd(a);
            boolean ok = cmd.applyTo(currentProgram, monitor);
            Function f = fm.getFunctionAt(a);
            println(t+" create="+ok+(f!=null?" size="+f.getBody().getNumAddresses():" (still none)"));
        }
    }
}
