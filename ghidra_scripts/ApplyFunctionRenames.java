// Applies this project's confirmed function-name promotions (recovered by
// hand from dropped-register/dropped-argument analysis, see the .c files
// under src/ named below and the bringup-frontier session notes) as real
// Ghidra symbol renames, so headless/GUI analysis reflects what's been
// learned instead of showing FUN_<address> everywhere.
//
// Idempotent: skips any address whose function is already named correctly,
// warns (does not overwrite) if a function there already has a DIFFERENT
// user-defined name.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

public class ApplyFunctionRenames extends GhidraScript {
    // {original address, new name, source .c file (for the plate comment)}
    static final String[][] RENAMES = {
        // 2026-07-13 session: widget/active-object registry mouse-hit-test family
        {"0040cea0", "FindActiveObjectAt", "src/ui_widget/FindActiveObjectAt.c"},
        {"004061e0", "HandleActiveObjectMouseMove", "src/ui_widget/HandleActiveObjectMouseMove.c"},
        {"00406120", "HandleActiveObjectMouseDown", "src/ui_widget/HandleActiveObjectMouseDown.c"},
        {"00406170", "HandleActiveObjectMouseUp", "src/ui_widget/HandleActiveObjectMouseUp.c"},
        {"0040ce50", "HandleBackgroundActiveObjectMouseDown", "src/ui_widget/HandleBackgroundActiveObjectMouseDown.c"},
        {"004f3020", "SweepActiveObjectRegistry", "src/ui_widget/SweepActiveObjectRegistry.c"},
        {"004062b0", "DrawActiveObjectRegistry", "src/ui_widget/DrawActiveObjectRegistry.c"},
        // 2026-07-14 session: bring-up crash chain (GameTick per-tick helpers,
        // dialog/network teardown, XFS sprite-load chain)
        {"00406280", "TickActiveObjectRegistry", "src/ui_widget/TickActiveObjectRegistry.c"},
        {"0040cf00", "SyncActiveTextInput", "src/ui_widget/SyncActiveTextInput.c"},
        {"004edce0", "UpdateDeviceAcquisition", "src/ui_widget/UpdateDeviceAcquisition.c"},
        {"004059a0", "CloseDirectLinkSocket", "src/ui_widget/CloseDirectLinkSocket.c"},
        {"004f1520", "ReadSpriteFrameRecord", "src/fileformat/ReadSpriteFrameRecord.c"},
        {"004f2f00", "CreateActiveObjectLayer", "src/ui_widget/CreateActiveObjectLayer.c"},
        {"004f1460", "CloseSpriteReadState", "src/rendering/CloseSpriteReadState.c"},
        // 2026-07-14 session 11: XFS entry lookup/insert chain - fixed the
        // FUN_004f0990 NULL-deref crash past ServerSelect (dropped archive/
        // name/flag registers recovered from disassembly, confirmed via angr)
        {"004f0990", "CompareXFSEntryName", "src/fileformat/CompareXFSEntryName.c"},
        {"004f11a0", "FindXFSEntryIndex", "src/fileformat/FindXFSEntryIndex.c"},
        {"004f1220", "FindOrInsertXFSEntry", "src/fileformat/FindOrInsertXFSEntry.c"},
        {"004f1390", "OpenXFSEntryStream", "src/fileformat/OpenXFSEntryStream.c"},
        // 2026-07-14 session 11: connection constructor un-dropped so the
        // broker socket worker thread spawns (first real server connection)
        {"004d2170", "InitConnectionObject", "src/network/InitConnectionObject.c"},
        {"00405dc0", "SocketWorkerThreadProc", "src/network/SocketWorkerThreadProc.c"},
        // 2026-07-15 session 12: chat-line wrap helper, DirectInput device
        // destructor pair, State11 weather-hazard render slot, State10
        // vtable population
        {"0041b410", "WrapChatLineText", "src/ui_widget/WrapChatLineText.c"},
        {"004ee1f0", "CInputDevice_BaseDestructor", "src/directx_init/CInputDevice_BaseDestructor.c"},
        {"004ee1d0", "CInputDevice_ScalarDeletingDestructor", "src/directx_init/CInputDevice_ScalarDeletingDestructor.c"},
        {"004c1d10", "State11_InBattle_RenderWeatherHazards", "src/state_machine/State11_InBattle_RenderWeatherHazards.c"},
        {"0043e280", "State10_Loading_ProcessPacket", "src/state_machine/State10_Loading_ProcessPacket.c"},
        {"00442240", "State10_Loading_AppendChatLine", "src/state_machine/State10_Loading_AppendChatLine.c"},
        {"00442280", "State10_Loading_Render", "src/state_machine/State10_Loading_Render.c"},
        // 2026-07-15 session 13: input-event queue consumer + 3 of 7
        // widget-command-handler push functions (see
        // src/ui_widget/EnterRoomNumberDialog_OnCommand.c's header for the
        // Ghidra xref/PTR_LAB vtable-family derivation used to find these)
        {"00412130", "ProcessInputEventQueue", "src/ui_widget/ProcessInputEventQueue.c"},
        {"00506b20", "EnterRoomNumberDialog_OnCommand", "src/ui_widget/EnterRoomNumberDialog_OnCommand.c"},
        {"00506950", "EnterRoomNumberDialog_SubmitRoomNumber", "src/ui_widget/EnterRoomNumberDialog_SubmitRoomNumber.c"},
        {"00506480", "CreateRoomDialog_SubmitCreateRoom", "src/ui_widget/CreateRoomDialog_SubmitCreateRoom.c"},
        // 2026-07-16 session 14: confirmed Knight shot spawner; the full
        // weather/terrain-hazard family (spawn dispatcher, per-hazard spawn
        // factories, constructors, render methods, tick methods - see
        // src/battle/SpawnTornadoHazard.c / InitTornadoHazard.c headers for
        // the decoded field map); plus type-suffixed projectile-shot
        // spawners and DetonateProjectile overrides (confirmed mobile TYPE
        // via vtable geometry, mobile NAME not confirmable).
        {"004305c0", "SpawnKnightFlameShot", "src/battle/SpawnKnightFlameShot.c"},
        {"0041ebf0", "SpawnWeatherHazards", "src/battle/SpawnWeatherHazards.c"},
        {"00435800", "SpawnTornadoHazard", "src/battle/SpawnTornadoHazard.c"},
        {"00435ad0", "SpawnFirewallHazard", "src/battle/SpawnFirewallHazard.c"},
        {"00435da0", "SpawnLightningHazard", "src/battle/SpawnLightningHazard.c"},
        {"004ac5a0", "InitTornadoHazard", "src/battle/InitTornadoHazard.c"},
        {"00471320", "InitFirewallHazard", "src/battle/InitFirewallHazard.c"},
        {"0046dde0", "InitLightningHazard", "src/battle/InitLightningHazard.c"},
        {"004ac760", "RenderTornadoHazard", "src/battle/RenderTornadoHazard.c"},
        {"00471550", "RenderFirewallHazard", "src/battle/RenderFirewallHazard.c"},
        {"0046e020", "RenderLightningHazard", "src/battle/RenderLightningHazard.c"},
        {"004ac750", "TickTornadoHazardFrame", "src/battle/TickTornadoHazardFrame.c"},
        {"0046e010", "TickWeatherHazardFrame", "src/battle/TickWeatherHazardFrame.c"},
        {"004acc90", "TickTornadoHazardLifetime", "src/battle/TickTornadoHazardLifetime.c"},
        {"00471a90", "TickWeatherHazardLifetime", "src/battle/TickWeatherHazardLifetime.c"},
        {"004a6920", "InitProjectileLightningHazard", "src/battle/InitProjectileLightningHazard.c"},
        {"00436150", "SpawnProjectileLightningHazard", "src/battle/SpawnProjectileLightningHazard.c"},
        {"0042f4b0", "SpawnShot_Type9", "src/battle/SpawnShot_Type9.c"},
        {"004388e0", "SpawnShot_Type13", "src/battle/SpawnShot_Type13.c"},
        {"004a2ce0", "DetonatePrimaryShot_Bullet4", "src/battle/DetonatePrimaryShot_Bullet4.c"},
        {"004af7a0", "DetonatePrimaryShot_Bullet12", "src/battle/DetonatePrimaryShot_Bullet12.c"},
        // 2026-07-16 session 15: the named-texture-cache family (singleton
        // g_textureCache, was DAT_00eb1bd8) - identity established via the
        // CRT static-init ctor at 0x5429b0 and the texture-name string
        // literals ("CharacterTexture1"/"TornadoTexture"/...) pushed into
        // the already-named PreloadTexture/FindTextureCacheEntryByName -
        // see src/rendering/FlushTextureCache.c's header.
        {"004f42b0", "InitTextureCache", "src/rendering/InitTextureCache.c"},
        {"004f42f0", "DestroyTextureCache", "src/rendering/DestroyTextureCache.c"},
        {"004f46b0", "FlushTextureCache", "src/rendering/FlushTextureCache.c"},
        // 2026-07-17 session 15: the low-level monochrome bitmap-font glyph
        // plotter reached while getting the world-list server rows to render
        // (6x12 1bpp glyph, solid colour, rect-clipped; bitmap in EAX) - see
        // src/rendering/BlitFontGlyphClipped.c's header.
        {"004eafa0", "BlitFontGlyphClipped", "src/rendering/BlitFontGlyphClipped.c"},
        // 2026-07-17: the bitmap-font loader - reads graphics.xfs's "font.fnt"
        // into the ASCII glyph table DAT_00673628; un-stubbed so ServerSelect
        // world-list server names render.
        {"004eae60", "LoadBitmapFont", "src/rendering/LoadBitmapFont.c"},
        // 2026-07-17 session 15: ServerSelect (state 2) input/command vtable
        // handlers, identified while tracing the server-join path - slot 5
        // dispatches the exit-game/buddy-panel/join-server commands, slot 6
        // is the WM_KEYDOWN handler (Enter = ConnectToSelectedServer), slot 3
        // dispatches the top-nav buttons.
        {"004e1170", "State02_ServerSelect_OnCommand", "src/state_machine/State02_ServerSelect_OnCommand.c"},
        {"004e1430", "State02_ServerSelect_HandleKeyInput", "src/state_machine/State02_ServerSelect_HandleKeyInput.c"},
        {"004e1200", "State02_ServerSelect_OnTopButton", "src/state_machine/State02_ServerSelect_OnTopButton.c"},
    };

    public void run() throws Exception {
        int renamed = 0, skippedAlready = 0, skippedConflict = 0, notFound = 0;
        for (String[] entry : RENAMES) {
            String addrStr = entry[0], newName = entry[1], srcFile = entry[2];
            Address addr = currentProgram.getAddressFactory().getAddress(addrStr);
            Function fn = getFunctionAt(addr);
            if (fn == null) {
                // No function yet (e.g. a tiny vtable-only method Ghidra's
                // auto-analysis never bounded). Disassemble + create one so
                // newly-ported functions still land in the project.
                disassemble(addr);
                fn = createFunction(addr, newName);
                if (fn == null) {
                    println("NOT FOUND: no function at " + addrStr
                            + " and createFunction failed (wanted " + newName + ")");
                    notFound++;
                    continue;
                }
                fn.setComment("Created + named " + newName + ". Real port: " + srcFile);
                println("CREATED+NAMED: " + addrStr + " -> " + newName);
                renamed++;
                continue;
            }
            String current = fn.getName();
            if (current.equals(newName)) {
                skippedAlready++;
                continue;
            }
            boolean isDefaultName = current.startsWith("FUN_");
            if (!isDefaultName) {
                println("CONFLICT: " + addrStr + " already named '" + current
                        + "' (not FUN_-default), wanted '" + newName + "' - skipped, not overwriting");
                skippedConflict++;
                continue;
            }
            fn.setName(newName, SourceType.USER_DEFINED);
            fn.setComment("Promoted " + current + " -> " + newName
                    + ". Real port: " + srcFile
                    + " (see that file's header for the dropped-argument/dropped-register"
                    + " recovery this rename is based on).");
            println("RENAMED: " + addrStr + "  " + current + " -> " + newName);
            renamed++;
        }
        println("=====SUMMARY=====");
        println("renamed: " + renamed);
        println("already correct: " + skippedAlready);
        println("conflicts (left alone): " + skippedConflict);
        println("not found: " + notFound);
    }
}
