import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;

public class ListSymbolsInRange extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        String startS = a.length > 0 ? a[0] : "00557b90";
        String endS = a.length > 1 ? a[1] : "00557f40";
        Address start = currentProgram.getAddressFactory().getAddress(startS);
        Address end = currentProgram.getAddressFactory().getAddress(endS);
        println("=====SYMBOLS " + startS + "-" + endS + "=====");
        SymbolIterator it = currentProgram.getSymbolTable().getSymbolIterator(start, true);
        while (it.hasNext()) {
            Symbol s = it.next();
            if (s.getAddress().compareTo(end) > 0) break;
            println(s.getAddress() + "  " + s.getName() + "  type=" + s.getSymbolType());
        }
        println("=====DATA " + startS + "-" + endS + "=====");
        DataIterator dit = currentProgram.getListing().getData(start, true);
        while (dit.hasNext()) {
            Data d = dit.next();
            if (d.getAddress().compareTo(end) > 0) break;
            println(d.getAddress() + "  len=" + d.getLength() + "  type=" + d.getDataType().getName() + "  label=" + d.getLabel());
        }
        println("=====END=====");
    }
}
