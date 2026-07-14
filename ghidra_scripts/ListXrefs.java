import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.listing.Instruction;

public class ListXrefs extends GhidraScript {
    public void run() throws Exception {
        String[] addrs = getScriptArgs();
        String target = addrs.length > 0 ? addrs[0] : "00e9be94";
        Address a = currentProgram.getAddressFactory().getAddress(target);
        println("=====XREFS to " + target + "=====");
        ReferenceIterator it = currentProgram.getReferenceManager().getReferencesTo(a);
        int count = 0;
        while (it.hasNext()) {
            Reference r = it.next();
            Address from = r.getFromAddress();
            Instruction insn = currentProgram.getListing().getInstructionAt(from);
            println(from + "  " + r.getReferenceType() + "  " + (insn != null ? insn.toString() : "?"));
            count++;
        }
        println("total: " + count);
        println("=====END=====");
    }
}
