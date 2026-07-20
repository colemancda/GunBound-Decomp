// Applies this project's confirmed GLOBAL/data-symbol renames (recovered by
// hand from usage analysis, see globals.c/globals.h's "was DAT_" annotations
// and the bringup-frontier session notes) as real Ghidra symbol renames, so
// headless/GUI analysis shows the descriptive names instead of DAT_<address>.
//
// The counterpart of ApplyFunctionRenames.java for DATA symbols (functions
// live in the FunctionManager; globals are plain symbols in the SymbolTable).
// Idempotent: skips any address already named correctly; warns (does not
// overwrite) if a DIFFERENT user-defined name is already there.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;

public class RenameDataSymbols extends GhidraScript {
    // {data address, new name, note}
    static final String[][] RENAMES = {
        // 2026-07-18 session: server-reply wait counter driving the PLEASE WAIT
        // (waitmessage.img) overlay; -1 idle, 0 on request, +1/tick, shows >40.
        {"0056d118", "g_serverWaitTicks", "src/globals.c - PLEASE WAIT wait counter"},
        // 2026-07-19 session: the game-event ring PumpBattleActions drains
        // (type 5/data -1 -> joinChannelRequest 0x2000; every entry also goes
        // to the current state's vtable slot 3). Inert as ported: nothing in
        // .text writes the write index.
        {"00793798", "g_gameEventRingWriteIndex", "drained by PumpBattleActions (0x412bca)"},
        {"0079379c", "g_gameEventRingReadIndex",  "drained by PumpBattleActions (0x412bca)"},
        {"007937a0", "g_gameEventTypeRing",       "512 dwords of event type"},
        {"00793fa0", "g_gameEventDataRing",       "512 dwords of event data"},
        // WinMain's peer-to-peer auto-connect object (operator_new(0x200c));
        // session sub-object at +0x2004; non-NULL from startup.
        {"007934f4", "g_directLinkConnection",    "src/entry/WinMain.c"},
    };

    public void run() throws Exception {
        SymbolTable st = currentProgram.getSymbolTable();
        int applied = 0, skipped = 0, warned = 0;
        for (String[] entry : RENAMES) {
            Address addr = currentProgram.getAddressFactory().getAddress(entry[0]);
            String newName = entry[1];
            Symbol sym = st.getPrimarySymbol(addr);
            if (sym == null) {
                st.createLabel(addr, newName, SourceType.USER_DEFINED);
                println("LABELED " + entry[0] + " -> " + newName);
                applied++;
                continue;
            }
            if (sym.getName().equals(newName)) {
                skipped++;
                continue;
            }
            // Overwrite the default DAT_/auto name; warn if a different
            // user-defined name already exists (don't clobber hand work).
            if (sym.getSource() == SourceType.USER_DEFINED) {
                println("WARN " + entry[0] + " already USER-named '" + sym.getName()
                        + "' != '" + newName + "' - leaving as-is");
                warned++;
                continue;
            }
            sym.setName(newName, SourceType.USER_DEFINED);
            println("RENAMED " + entry[0] + " " + sym.getName() + " -> " + newName);
            applied++;
        }
        println("RenameDataSymbols: applied=" + applied + " skipped=" + skipped + " warned=" + warned);
    }
}
