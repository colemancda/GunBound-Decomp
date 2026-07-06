import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.*;

public class InspectTable extends GhidraScript {
    public void run() throws Exception {
        Address tableAddr = currentProgram.getAddressFactory().getAddress("00553674");
        // dump 0x40 bytes around it as 4-byte words, resolving function names
        Address start = tableAddr.subtract(0x20);
        FunctionManager fm = currentProgram.getFunctionManager();
        for (int i=0;i<0x40;i+=4) {
            Address a = start.add(i);
            int val = getInt(a);
            Address ta = currentProgram.getAddressFactory().getAddress(String.format("%08x", val & 0xffffffffL));
            Function f = fm.getFunctionAt(ta);
            String marker = a.equals(tableAddr) ? "  <== ProcessPacket ref" : "";
            println(a+": 0x"+Integer.toHexString(val)+(f!=null?"  -> "+f.getName():"")+marker);
        }
        // who references the table region (start of table)?
        println("--- refs to table start "+tableAddr+" minus typical vtable header ---");
        for (Reference r : getReferencesTo(start)) {
            println("ref to tablestart from "+r.getFromAddress());
        }
    }
}
