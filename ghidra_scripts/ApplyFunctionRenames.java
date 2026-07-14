// Applies this project's confirmed function-name promotions (recovered by
// hand from dropped-register/dropped-argument analysis, see the .c files
// under src/ named below and the bringup-frontier session notes) as real
// Ghidra symbol renames, so headless/GUI analysis reflects what's been
// learned instead of showing FUN_<address> everywhere.
//
// Idempotent: skips any address whose function is already named correctly,
// warns (does not overwrite) if a function there already has a DIFFERENT
// user-defined name.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

public class ApplyFunctionRenames extends GhidraScript {
    // {original address, new name, source .c file (for the plate comment)}
    static final String[][] RENAMES = {
        // 2026-07-13 session: widget/active-object registry mouse-hit-test family
        {"0040cea0", "FindActiveObjectAt", "src/ui_widget/FindActiveObjectAt.c"},
        {"004061e0", "HandleActiveObjectMouseMove", "src/ui_widget/HandleActiveObjectMouseMove.c"},
        {"00406120", "HandleActiveObjectMouseDown", "src/ui_widget/HandleActiveObjectMouseDown.c"},
        {"00406170", "HandleActiveObjectMouseUp", "src/ui_widget/HandleActiveObjectMouseUp.c"},
        {"0040ce50", "HandleBackgroundActiveObjectMouseDown", "src/ui_widget/HandleBackgroundActiveObjectMouseDown.c"},
        {"004f3020", "SweepActiveObjectRegistry", "src/ui_widget/SweepActiveObjectRegistry.c"},
        {"004062b0", "DrawActiveObjectRegistry", "src/ui_widget/DrawActiveObjectRegistry.c"},
        // 2026-07-14 session: bring-up crash chain (GameTick per-tick helpers,
        // dialog/network teardown, XFS sprite-load chain)
        {"00406280", "TickActiveObjectRegistry", "src/ui_widget/TickActiveObjectRegistry.c"},
        {"0040cf00", "SyncActiveTextInput", "src/ui_widget/SyncActiveTextInput.c"},
        {"004edce0", "UpdateDeviceAcquisition", "src/ui_widget/UpdateDeviceAcquisition.c"},
        {"004059a0", "CloseDirectLinkSocket", "src/ui_widget/CloseDirectLinkSocket.c"},
        {"004f1520", "ReadSpriteFrameRecord", "src/fileformat/ReadSpriteFrameRecord.c"},
        {"004f2f00", "CreateActiveObjectLayer", "src/ui_widget/CreateActiveObjectLayer.c"},
        {"004f1460", "CloseSpriteReadState", "src/rendering/CloseSpriteReadState.c"},
    };

    public void run() throws Exception {
        int renamed = 0, skippedAlready = 0, skippedConflict = 0, notFound = 0;
        for (String[] entry : RENAMES) {
            String addrStr = entry[0], newName = entry[1], srcFile = entry[2];
            Address addr = currentProgram.getAddressFactory().getAddress(addrStr);
            Function fn = getFunctionAt(addr);
            if (fn == null) {
                println("NOT FOUND: no function at " + addrStr + " (wanted " + newName + ")");
                notFound++;
                continue;
            }
            String current = fn.getName();
            if (current.equals(newName)) {
                skippedAlready++;
                continue;
            }
            boolean isDefaultName = current.startsWith("FUN_");
            if (!isDefaultName) {
                println("CONFLICT: " + addrStr + " already named '" + current
                        + "' (not FUN_-default), wanted '" + newName + "' - skipped, not overwriting");
                skippedConflict++;
                continue;
            }
            fn.setName(newName, SourceType.USER_DEFINED);
            fn.setComment("Promoted " + current + " -> " + newName
                    + ". Real port: " + srcFile
                    + " (see that file's header for the dropped-argument/dropped-register"
                    + " recovery this rename is based on).");
            println("RENAMED: " + addrStr + "  " + current + " -> " + newName);
            renamed++;
        }
        println("=====SUMMARY=====");
        println("renamed: " + renamed);
        println("already correct: " + skippedAlready);
        println("conflicts (left alone): " + skippedConflict);
        println("not found: " + notFound);
    }
}
