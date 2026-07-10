import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

// Import the reconstructed C++ types (from gb_cxx_types.gdt, built by
// tools/debug/build_ghidra_types.sh) into the GunBound program and apply the one
// statically-addressable anchor: g_gameStateObjects[16] at 0x5b33f8 becomes a
// CGameState*[16]. The concrete state objects are heap-allocated, so you apply
// CStateNN by hand at the decompiler (right-click -> Retype) or via the live
// Debugger; this makes every type available for that.
//
// arg[0] = path to gb_cxx_types.gdt (default: ghidra/gb_cxx_types.gdt)
public class ApplyCxxTypes extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String gdt = args.length > 0 ? args[0] : "ghidra/gb_cxx_types.gdt";
        File f = new File(gdt);
        if (!f.exists()) {
            println("ERROR: archive not found: " + f.getAbsolutePath());
            return;
        }

        DataTypeManager prog = currentProgram.getDataTypeManager();
        FileDataTypeManager fdtm = FileDataTypeManager.openFileArchive(f, false);

        int n = 0;
        Iterator<DataType> it = fdtm.getAllDataTypes();
        while (it.hasNext()) {
            prog.addDataType(it.next(), DataTypeConflictHandler.REPLACE_HANDLER);
            n++;
        }
        println("imported " + n + " data types into the program");

        List<DataType> found = new ArrayList<>();
        prog.findDataTypes("CGameState", found);
        if (found.isEmpty()) {
            println("ERROR: CGameState not found after import");
            fdtm.close();
            return;
        }
        DataType cgs = found.get(0);
        DataType ptr = prog.getPointer(cgs);
        ArrayDataType arr = new ArrayDataType(ptr, 16, ptr.getLength());

        Address base = toAddr(0x5b33f8);
        clearListing(base, base.add(16 * 4 - 1));
        createData(base, arr);
        currentProgram.getSymbolTable().createLabel(base, "g_gameStateObjects",
                SourceType.USER_DEFINED);
        println("applied CGameState *[16] at 0x5b33f8 (g_gameStateObjects)");
        fdtm.close();
    }
}
