import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;

// For a given list of function entry addrs, print every defined string
// referenced by instructions inside that function (helps ID DLL/proc loaders).
public class DumpStringsInFunc extends GhidraScript {
    String[] addrs = {
        "0040d8e0","004fdf00", // WinMain candidates
        "004edc50","004ee5b0","004efaa0","00521ea0","00522880","00523530" // LoadLibrary+GetProcAddress callers
    };
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String a : addrs) {
            Address ea = currentProgram.getAddressFactory().getAddress(a);
            Function f = fm.getFunctionAt(ea);
            if (f == null) { println(a+": no function"); continue; }
            println("== "+a+" size="+f.getBody().getNumAddresses()+" ==");
            InstructionIterator ii = currentProgram.getListing().getInstructions(f.getBody(), true);
            java.util.Set<String> seen = new java.util.LinkedHashSet<>();
            while (ii.hasNext()) {
                Instruction insn = ii.next();
                for (Reference r : insn.getReferencesFrom()) {
                    Address to = r.getToAddress();
                    Data d = getDataAt(to);
                    if (d != null && d.hasStringValue()) {
                        String v = d.getValue().toString();
                        if (seen.add(v)) println("   str: "+v);
                    }
                }
            }
        }
    }
}
