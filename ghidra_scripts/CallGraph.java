import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;

// Prints the direct callees of a set of functions by name (post-labeling check).
public class CallGraph extends GhidraScript {
    String[] names = {"WinMain","InitDirectInput","InitDirectSound","InitDirectDraw"};
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String n : names) {
            Function f = null;
            for (Function cand : fm.getFunctions(true)) if (cand.getName().equals(n)) { f = cand; break; }
            if (f == null) { println(n+": not found"); continue; }
            println("== "+n+" @ "+f.getEntryPoint()+" callees: ");
            for (Function c : f.getCalledFunctions(monitor)) println("   "+c.getEntryPoint()+" "+c.getName());
        }
    }
}
