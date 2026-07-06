import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import ghidra.app.decompiler.*;
import ghidra.program.model.pcode.HighFunction;
import ghidra.program.model.pcode.HighFunctionDBUtil;
import ghidra.program.model.pcode.HighFunctionDBUtil.ReturnCommitOption;

public class NameProcessPacket2 extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        Address ea = currentProgram.getAddressFactory().getAddress("00426ad0");
        Function f = fm.getFunctionAt(ea);
        if (f == null) { println("not found"); return; }
        f.setName("ProcessPacket", SourceType.USER_DEFINED);

        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        DecompileResults r = di.decompileFunction(f, 60, monitor);
        HighFunction hf = r.getHighFunction();
        if (hf == null) { println("decompile failed: "+r.getErrorMessage()); return; }
        HighFunctionDBUtil.commitParamsToDatabase(hf, true, ReturnCommitOption.NO_COMMIT, SourceType.ANALYSIS);
        di.dispose();

        Parameter[] params = f.getParameters();
        String[] names = {"payloadLen","opcode","payload"};
        int ni = 0;
        for (Parameter p : params) {
            if (p.isAutoParameter()) continue;
            if (ni < names.length) p.setName(names[ni++], SourceType.USER_DEFINED);
        }
        println("Param count: "+params.length);
        for (Parameter p: f.getParameters()) println("  "+p.getDataType()+" "+p.getName()+" auto="+p.isAutoParameter());
    }
}
