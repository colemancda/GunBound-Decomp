import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;

// For each orphan address, scan backwards for a function prologue
// (55 8B EC = PUSH EBP; MOV EBP,ESP) OR a preceding RET/INT3 padding boundary,
// and report a candidate function entry.
public class FindProlog extends GhidraScript {
    String[] sites = {"00443350","00443561","004b9ebe","004e0c68","004e5421"};
    public void run() throws Exception {
        for (String s : sites) {
            Address site = currentProgram.getAddressFactory().getAddress(s);
            Address cand = null;
            for (long back=0; back<0x800; back++) {
                Address a = site.subtract(back);
                int b0 = getByte(a) & 0xff;
                int b1 = getByte(a.add(1)) & 0xff;
                int b2 = getByte(a.add(2)) & 0xff;
                if (b0==0x55 && b1==0x8b && b2==0xec) { cand=a; break; }
            }
            // also find preceding int3 (CC) run or RET (C3/C2) as fallback boundary
            Address boundary=null;
            for (long back=1; back<0x800; back++) {
                Address a = site.subtract(back);
                int b = getByte(a) & 0xff;
                if (b==0xcc) { boundary=a.add(1); break; }
                if (b==0xc3) { boundary=a.add(1); break; }
            }
            println(s+" prologue(55 8B EC)="+(cand!=null?cand:"none")+"  afterRET/INT3="+(boundary!=null?boundary:"none"));
        }
    }
}
