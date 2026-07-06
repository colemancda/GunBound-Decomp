import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;

// Exports every function as a CSV worklist: addr,size,name,thunk,refCount,callsOut
// Used as the master coverage tracker for the decompilation effort.
public class ExportInventory extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        File out = new File("/Users/coleman/Developer/GunBound-Decomp/PROGRESS.csv");
        PrintWriter pw = new PrintWriter(new FileWriter(out));
        pw.println("addr,size,name,is_thunk,xref_count,calls_out,status");
        int n = 0;
        for (Function f : fm.getFunctions(true)) {
            long size = f.getBody().getNumAddresses();
            int xrefs = 0;
            for (Reference r : getReferencesTo(f.getEntryPoint())) xrefs++;
            int callsOut = f.getCalledFunctions(monitor).size();
            pw.printf("%s,%d,%s,%b,%d,%d,TODO%n",
                f.getEntryPoint(), size, f.getName(), f.isThunk(), xrefs, callsOut);
            n++;
        }
        pw.close();
        println("EXPORTED=" + n + " -> " + out.getAbsolutePath());
    }
}
