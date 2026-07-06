import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.*;
public class FindCallers2 extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        Function target = fm.getFunctionAt(currentProgram.getAddressFactory().getAddress("00426ad0"));
        for (Reference r : getReferencesTo(target.getEntryPoint())) {
            println("ref from "+r.getFromAddress()+" type="+r.getReferenceType()+" isData="+r.getReferenceType().isData());
            Data d = getDataAt(r.getFromAddress());
            if (d!=null) println("   data: "+d);
            Function caller = fm.getFunctionContaining(r.getFromAddress());
            println("   containing func: "+(caller!=null?caller.getEntryPoint()+":"+caller.getName():"none"));
        }
    }
}
