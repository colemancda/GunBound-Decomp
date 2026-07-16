import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

// Exports every function as a CSV worklist: addr,size,name,thunk,refCount,callsOut,status
// Used as the master coverage tracker for the decompilation effort.
//
// MERGES with any existing PROGRESS.csv rather than overwriting it: the
// `status` column (RAW-src/PARITY-cxx-*/EXCLUDED-*/etc) is hand-maintained
// and NOT derivable from Ghidra alone - a plain overwrite would silently
// reset every row's status to TODO. Existing addresses keep their current
// status; only genuinely new addresses (not in the prior file) get TODO.
public class ExportInventory extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        File out = new File(System.getProperty("user.home") + "/Developer/GunBound-Decomp/PROGRESS.csv");

        Map<String, String> existingStatus = new HashMap<>();
        if (out.exists()) {
            try (BufferedReader r = new BufferedReader(new FileReader(out))) {
                String line = r.readLine(); // header
                while ((line = r.readLine()) != null) {
                    String[] c = line.split(",", -1);
                    if (c.length >= 7) {
                        existingStatus.put(c[0].trim(), c[6].trim());
                    }
                }
            }
        }

        PrintWriter pw = new PrintWriter(new FileWriter(out));
        pw.println("addr,size,name,is_thunk,xref_count,calls_out,status");
        int n = 0, kept = 0, fresh = 0;
        for (Function f : fm.getFunctions(true)) {
            long size = f.getBody().getNumAddresses();
            int xrefs = 0;
            for (Reference r : getReferencesTo(f.getEntryPoint())) xrefs++;
            int callsOut = f.getCalledFunctions(monitor).size();
            String addr = f.getEntryPoint().toString();
            String status = existingStatus.get(addr);
            if (status != null) { kept++; } else { status = "TODO"; fresh++; }
            pw.printf("%s,%d,%s,%b,%d,%d,%s%n",
                addr, size, f.getName(), f.isThunk(), xrefs, callsOut, status);
            n++;
        }
        pw.close();
        println("EXPORTED=" + n + " (status kept=" + kept + ", fresh=" + fresh + ") -> " + out.getAbsolutePath());
    }
}
