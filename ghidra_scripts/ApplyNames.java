import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import java.io.*;

// Apply our function-name identifications from PROGRESS.csv (addr,size,name,...)
// to the program. Skips FUN_/thunk_/empty names and names already applied.
// arg[0] = path to PROGRESS.csv (default: PROGRESS.csv in the launch cwd).
public class ApplyNames extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String csv = args.length > 0 ? args[0] : "PROGRESS.csv";
        BufferedReader r = new BufferedReader(new FileReader(csv));
        FunctionManager fm = currentProgram.getFunctionManager();
        int applied = 0, already = 0, skipped = 0, missing = 0, conflict = 0, line = 0;
        String s;
        while ((s = r.readLine()) != null) {
            line++;
            if (line == 1) continue;                         // header
            String[] c = s.split(",", -1);
            if (c.length < 3) continue;
            String addr = c[0].trim();
            String name = c[2].trim();
            if (name.isEmpty() || name.startsWith("FUN_") || name.startsWith("thunk_")) { skipped++; continue; }
            Address a;
            try { a = currentProgram.getAddressFactory().getAddress(addr); }
            catch (Exception e) { missing++; continue; }
            Function f = fm.getFunctionAt(a);
            if (f == null) { println("MISSING FUNC @" + addr + " (" + name + ")"); missing++; continue; }
            if (name.equals(f.getName())) { already++; continue; }
            try { f.setName(name, SourceType.USER_DEFINED); applied++; }
            catch (Exception e) { println("CONFLICT @" + addr + " -> " + name + ": " + e.getMessage()); conflict++; }
        }
        r.close();
        println("ApplyNames: applied=" + applied + " already=" + already
                + " skipped(FUN_/thunk_/empty)=" + skipped + " missing=" + missing + " conflict=" + conflict);
    }
}
