import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.*;
public class ListImports extends GhidraScript {
    public void run() throws Exception {
        SymbolTable st = currentProgram.getSymbolTable();
        SymbolIterator it = st.getExternalSymbols();
        int n=0;
        while (it.hasNext()) { Symbol s = it.next(); println("IMPORT: "+s.getName()); n++; }
        println("TOTAL_IMPORTS="+n);
    }
}
