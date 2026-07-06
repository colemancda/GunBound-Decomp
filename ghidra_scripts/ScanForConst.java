import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.scalar.Scalar;

public class ScanForConst extends GhidraScript {
    public void run() throws Exception {
        long[] targets = {0x553670L,0x553674L,0x553678L};
        InstructionIterator ii = currentProgram.getListing().getInstructions(true);
        FunctionManager fm = currentProgram.getFunctionManager();
        int found=0;
        while (ii.hasNext() && found < 40) {
            Instruction insn = ii.next();
            for (int i=0;i<insn.getNumOperands();i++) {
                Object[] objs = insn.getOpObjects(i);
                for (Object o: objs) {
                    if (o instanceof Scalar) {
                        long v = ((Scalar)o).getUnsignedValue();
                        for (long t: targets) {
                            if (v==t) {
                                Function f = fm.getFunctionContaining(insn.getAddress());
                                println(insn.getAddress()+" ["+(f!=null?f.getName():"?")+"]: "+insn);
                                found++;
                            }
                        }
                    }
                }
            }
        }
        println("done, found="+found);
    }
}
