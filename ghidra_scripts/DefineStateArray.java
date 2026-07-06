import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;

// Formalizes g_gameStateVTableArray (0x5b33f8) as a real 16-element array of
// object pointers, based on: ChangeGameState indexes it by state id (0-15,
// confirmed via the newStateId==0xf quit special-case landing exactly on
// element 15 = 0x5b33f8 + 15*4 = 0x5b3434, which shares the same trivial
// vtable as element 0 -- a null-object pattern for the two non-visual states).
public class DefineStateArray extends GhidraScript {
    public void run() throws Exception {
        Address base = currentProgram.getAddressFactory().getAddress("005b33f8");
        clearListing(base, base.add(0x40 - 1));
        Pointer voidPtr = PointerDataType.dataType;
        ArrayDataType arr = new ArrayDataType(voidPtr, 16, voidPtr.getLength());
        createData(base, arr);
        currentProgram.getSymbolTable().createLabel(base, "g_gameStateObjects", SourceType.USER_DEFINED);
        println("Defined g_gameStateObjects[16] at " + base);

        Address vt = currentProgram.getAddressFactory().getAddress("00553670");
        Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(vt);
        if (s != null) {
            s.setName("vtable_State3_NetworkSession", SourceType.USER_DEFINED);
            println("Renamed vtable symbol at " + vt + " -> " + s.getName());
        }

        FunctionManager fm = currentProgram.getFunctionManager();
        Function pp = fm.getFunctionAt(currentProgram.getAddressFactory().getAddress("00426ad0"));
        if (pp != null) {
            pp.setComment("Virtual method referenced from g_gameStateObjects[3]'s vtable (slot 1).\n" +
                "State 3's packet-receive handler: dispatches by opcode (ushort) on the\n" +
                "payload. Confirmed opcode 0x6001 -> ChangeGameState(7); a later branch\n" +
                "sums per-player equipped-item stats then resets viewport to (0,0,799,599)\n" +
                "and calls ChangeGameState(9). See PROTOCOL.md for the opcode map.");
            println("Commented ProcessPacket");
        }
    }
}
