import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.*;

// Finds all call sites to ChangeGameState and disassembles a window of
// instructions immediately before each call, to recover the ESI (state id)
// value that's set via register (not a stack arg) prior to the call.
public class FindStateCalls extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        Function target = null;
        for (Function f : fm.getFunctions(true)) if (f.getName().equals("ChangeGameState")) { target = f; break; }
        if (target == null) { println("not found"); return; }
        Listing listing = currentProgram.getListing();
        for (Reference r : getReferencesTo(target.getEntryPoint())) {
            Address callAddr = r.getFromAddress();
            Function caller = fm.getFunctionContaining(callAddr);
            println("== call at "+callAddr+" in "+(caller!=null?caller.getName():"?")+" ==");
            // walk backwards up to 8 instructions
            Instruction insn = listing.getInstructionAt(callAddr);
            java.util.List<String> lines = new java.util.ArrayList<>();
            Instruction cur = insn;
            for (int i=0;i<8 && cur!=null;i++) {
                lines.add(0, cur.getAddress()+": "+cur.toString());
                cur = listing.getInstructionBefore(cur.getAddress());
            }
            for (String l: lines) println("   "+l);
        }
    }
}
