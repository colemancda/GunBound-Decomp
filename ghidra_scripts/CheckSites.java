import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
public class CheckSites extends GhidraScript {
    String[] sites = {"00443350","00443561","004b9ebe","004e0c68","004e5421","0042866c"};
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String s : sites) {
            Address a = currentProgram.getAddressFactory().getAddress(s);
            Function f = fm.getFunctionContaining(a);
            println(s+" -> "+(f!=null? f.getEntryPoint()+":"+f.getName()+" size="+f.getBody().getNumAddresses() : "STILL ORPHAN"));
        }
    }
}
