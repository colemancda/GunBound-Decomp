import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.Data;
import ghidra.program.model.address.Address;
import java.util.ArrayList;
import java.util.List;

// Read-only sanity check: confirm the reconstructed C++ types persisted in the
// program and that g_gameStateObjects is typed.
public class CheckCxxTypes extends GhidraScript {
    public void run() throws Exception {
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        String[] names = {"CGameState", "CState02ServerSelect", "CState11InBattle",
                          "CWidget", "CPanel", "CWorldListPanel", "ServerListSoA", "GbInventoryItem"};
        for (String nm : names) {
            List<DataType> l = new ArrayList<>();
            dtm.findDataTypes(nm, l);
            println(nm + ": " + (l.isEmpty() ? "MISSING" : (l.get(0).getLength() + " bytes")));
        }
        Address base = toAddr(0x5b33f8);
        Data d = getDataAt(base);
        println("data @0x5b33f8: " + (d == null ? "none" : d.getDataType().getName())
                + "  label=" + currentProgram.getSymbolTable().getPrimarySymbol(base));
    }
}
