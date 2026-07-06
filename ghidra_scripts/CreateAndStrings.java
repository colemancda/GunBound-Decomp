import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Reference;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.decompiler.*;

// Creates functions at given entry points, then reports for each: size, direct
// callees, and any string constants referenced (transitively 1 level) -- to
// identify what screen/resource each game-state enter-hook sets up.
public class CreateAndStrings extends GhidraScript {
    public void run() throws Exception {
        String[] targets = getScriptArgs();
        FunctionManager fm = currentProgram.getFunctionManager();
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        for (String t : targets) {
            Address a = currentProgram.getAddressFactory().getAddress(t);
            Function f = fm.getFunctionAt(a);
            if (f == null) {
                if (getInstructionAt(a)==null) disassemble(a);
                new CreateFunctionCmd(a).applyTo(currentProgram, monitor);
                f = fm.getFunctionAt(a);
            }
            if (f == null) { println("== "+t+": could not create =="); continue; }
            println("== "+t+" size="+f.getBody().getNumAddresses()+" ==");
            // strings referenced in this func and its direct callees
            java.util.LinkedHashSet<String> strs = new java.util.LinkedHashSet<>();
            collectStrings(f, strs);
            for (Function c : f.getCalledFunctions(monitor)) collectStrings(c, strs);
            int n=0;
            for (String s : strs) { println("   str: "+s); if (++n>=15) break; }
        }
        di.dispose();
    }
    void collectStrings(Function f, java.util.Set<String> out) {
        Listing l = currentProgram.getListing();
        InstructionIterator ii = l.getInstructions(f.getBody(), true);
        while (ii.hasNext()) {
            Instruction insn = ii.next();
            for (Reference r : insn.getReferencesFrom()) {
                Data d = getDataAt(r.getToAddress());
                if (d != null && d.hasStringValue()) {
                    String v = d.getValue().toString();
                    if (v.length()>2) out.add(v);
                }
            }
        }
    }
}
