import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.Memory;

// Dumps a vtable (array of code pointers) until it hits a non-code value.
public class DumpVtable extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String base = args.length>0 ? args[0] : "00553670";
        int max = args.length>1 ? Integer.parseInt(args[1]) : 24;
        FunctionManager fm = currentProgram.getFunctionManager();
        Memory mem = currentProgram.getMemory();
        Address a = currentProgram.getAddressFactory().getAddress(base);
        for (int i=0;i<max;i++) {
            Address slot = a.add(i*4L);
            int val = getInt(slot);
            Address ta = currentProgram.getAddressFactory().getAddress(String.format("%08x", val & 0xffffffffL));
            boolean inText = mem.contains(ta) && val >= 0x401000 && val < 0x544000;
            Function f = fm.getFunctionAt(ta);
            println(String.format("[%2d] %s = 0x%x %s%s", i, slot, val,
                inText?"CODE":"(non-code, stop)", f!=null?" -> "+f.getName():(inText?" -> (no func!)":"")));
            if (!inText) break;
        }
    }
}
