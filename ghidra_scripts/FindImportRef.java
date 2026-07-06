import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import java.util.*;

// Lists, for each named external import symbol we care about, every function
// that calls it. Used to bootstrap labels (InitDirectDraw, InitWinsock, etc).
public class FindImportRef extends GhidraScript {
    String[] targets = {
        "WSAStartup","WSACleanup","recvfrom","sendto","recv","send","socket",
        "closesocket","ioctlsocket","WSAAsyncSelect","WSAEventSelect",
        "CreateWindowExA","RegisterClassA","SendMessageA",
        "LoadLibraryA","GetProcAddress"
    };
    public void run() throws Exception {
        SymbolTable st = currentProgram.getSymbolTable();
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String t : targets) {
            List<Symbol> syms = new ArrayList<>();
            SymbolIterator it = st.getSymbols(t);
            while (it.hasNext()) syms.add(it.next());
            if (syms.isEmpty()) { println(t+": NOT FOUND"); continue; }
            for (Symbol s : syms) {
                Set<String> callers = new TreeSet<>();
                for (Reference r : getReferencesTo(s.getAddress())) {
                    Function f = fm.getFunctionContaining(r.getFromAddress());
                    if (f != null) callers.add(f.getEntryPoint()+":"+f.getName());
                }
                println(t+" @ "+s.getAddress()+" <- "+callers);
            }
        }
    }
}
