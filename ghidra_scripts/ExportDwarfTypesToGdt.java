import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.util.task.TaskMonitor;
import java.io.File;
import java.util.Iterator;

// Copies every data type in the current program's DataTypeManager into a
// standalone .gdt file archive. Run it on the program produced by importing
// build/gb_cxx_types.o (DWARF), to capture the whole C++ type set (CGameState,
// CWidget hierarchy, protocol structs, ...) as a portable archive that can be
// opened in the GunBound.gme project (File -> Open File Archive) and applied.
//
// arg[0] = output .gdt path (default /tmp/gb_cxx_types.gdt)
public class ExportDwarfTypesToGdt extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String out = args.length > 0 ? args[0] : "/tmp/gb_cxx_types.gdt";
        File f = new File(out);
        if (f.exists() && !f.delete()) {
            println("WARN: could not delete existing " + out);
        }
        FileDataTypeManager fdtm = FileDataTypeManager.createFileArchive(f);
        int tx = fdtm.startTransaction("copy types");
        DataTypeManager src = currentProgram.getDataTypeManager();
        int n = 0, cxx = 0;
        Iterator<DataType> it = src.getAllDataTypes();
        while (it.hasNext()) {
            DataType dt = it.next();
            fdtm.addDataType(dt, DataTypeConflictHandler.REPLACE_HANDLER);
            n++;
            String nm = dt.getName();
            if (nm.startsWith("CGameState") || nm.startsWith("CState") || nm.startsWith("CWidget")
                    || nm.startsWith("CPanel") || nm.startsWith("CLabel") || nm.startsWith("Gb")
                    || nm.startsWith("ServerListSoA") || nm.startsWith("PeerEndpoint")) {
                cxx++;
                println("  + " + nm + "  (" + dt.getLength() + " bytes)");
            }
        }
        fdtm.endTransaction(tx, true);
        fdtm.save();
        fdtm.close();
        println("exported " + n + " data types (" + cxx + " reconstructed C++ types) to " + out);
    }
}
