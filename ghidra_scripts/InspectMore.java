import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
public class InspectMore extends GhidraScript {
    String[] addrs = {"0040f400","004fdc80","00401200"};
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String a : addrs) {
            Address ea = currentProgram.getAddressFactory().getAddress(a);
            Function f = fm.getFunctionAt(ea);
            if (f==null){println(a+": none");continue;}
            println("== "+a+" size="+f.getBody().getNumAddresses());
            for (Function c: f.getCalledFunctions(monitor)) println("   calls "+c.getEntryPoint()+" "+c.getName());
            java.util.Set<String> callers=new java.util.TreeSet<>();
            for (Function c: f.getCallingFunctions(monitor)) callers.add(c.getEntryPoint()+":"+c.getName());
            println("   called by "+callers);
        }
    }
}
