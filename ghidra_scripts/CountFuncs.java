import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
public class CountFuncs extends GhidraScript {
  public void run() throws Exception {
    FunctionManager fm = currentProgram.getFunctionManager();
    int total=0, real=0;
    for (Function f : fm.getFunctions(true)) { total++; if(!f.isThunk()) real++; }
    println("FUNC_TOTAL="+total);
    println("FUNC_NONTHUNK="+real);
  }
}
