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
        // 2026-07-19 session: lobby-entry / broadcast-context recoveries
        {"004e7430", "ResetReplayContext", "src/network/ResetReplayContext.c"},
        {"004e73e0", "SetLocalPeerEndpoint", "src/network/SetLocalPeerEndpoint.c"},
        // 2026-07-18 session: packet-cipher context allocator
        {"004f6f10", "AllocCipherSchedule", "src/network/AllocCipherSchedule.c"},
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
        // 2026-07-17 session 16: functions recovered while driving the client to
        // ServerSelect under the wine virtual desktop and fixing the connection
        // teardown chain that hung the first full GameTick.
        // - the generic 3-field ring-buffer push (write/read cursors + msg/
        //   param1/param2 arrays off the queue-object base pointer); it is the
        //   input-event enqueue, fed &g_inputEventRing from the socket path.
        {"004f2da0", "EnqueueInputEvent", "src/ui_widget/EnqueueInputEvent.c"},
        // - the connection destructor (sets the vtable, closes the socket, joins
        //   the worker thread, deletes the CS, frees the recv buffer) and the
        //   owner-side teardown that calls it - both had dropped ESI/EDI `this`.
        {"004e5590", "DestroyConnectionObject", "src/network/DestroyConnectionObject.c"},
        {"00405930", "CloseAndFreeConnection", "src/network/CloseAndFreeConnection.c"},
        // 2026-07-17 session 15: ServerSelect (state 2) input/command vtable
        // handlers, identified while tracing the server-join path - slot 5
        // dispatches the exit-game/buddy-panel/join-server commands, slot 6
        // is the WM_KEYDOWN handler (Enter = ConnectToSelectedServer), slot 3
        // dispatches the top-nav buttons.
        {"004e1170", "State02_ServerSelect_OnCommand", "src/state_machine/State02_ServerSelect_OnCommand.c"},
        {"004e1430", "State02_ServerSelect_HandleKeyInput", "src/state_machine/State02_ServerSelect_HandleKeyInput.c"},
        {"004e1200", "State02_ServerSelect_OnTopButton", "src/state_machine/State02_ServerSelect_OnTopButton.c"},
        // 2026-07-18 session 17: the texture-atlas cluster behind PreloadTexture
        // (0x4f43a0) - page alloc/init, DirectDraw surface creation, free-tile
        // scan, pixel upload, and the sorted name-record insert that mirrors
        // FindTextureCacheEntryByName.
        {"004f0230", "CreateTextureAtlasSurface", "src/rendering/CreateTextureAtlasSurface.c"},
        {"004f4350", "AllocTextureAtlasPage", "src/rendering/AllocTextureAtlasPage.c"},
        {"004f4170", "InitTextureAtlasPage", "src/rendering/InitTextureAtlasPage.c"},
        {"004f4750", "FindFreeAtlasTileSlot", "src/rendering/FindFreeAtlasTileSlot.c"},
        {"004f41d0", "UploadTileToAtlasSurface", "src/rendering/UploadTileToAtlasSurface.c"},
        {"004f45d0", "InsertTextureCacheRecord", "src/rendering/InsertTextureCacheRecord.c"},
        // 2026-07-18 session 17: the LZHUF COMPRESS side (the decode side was
        // already named) + the XFS write-back that drives it, and the AES key
        // schedule of the network cipher family.
        {"004ea760", "EncodeLZHUFBlock", "src/lzhuf/EncodeLZHUFBlock.c"},
        {"004ea580", "LZHUFUpdate", "src/lzhuf/LZHUFUpdate.c"},
        {"004ea230", "LZHUFPutCode", "src/lzhuf/LZHUFPutCode.c"},
        {"004ea010", "LZHUFDeleteNode", "src/lzhuf/LZHUFDeleteNode.c"},
        {"004f0530", "FlushXFSWriteBlock", "src/fileformat/FlushXFSWriteBlock.c"},
        {"004f48b0", "RijndaelSetKey", "src/network/RijndaelSetKey.c"},
        // 2026-07-18 session 17: the CUIPanelManager input dispatchers - each
        // walks the panel list at manager+4 and forwards a widget virtual;
        // WndProc routes one window message to each (0x200/0x201/0x202/0x203/
        // 0x204/WM_KEYDOWN/WM_KEYUP).
        {"0050f020", "PanelManager_DispatchMouseMove", "src/ui_widget/PanelManager_DispatchMouseMove.c"},
        {"00507ea0", "PanelManager_DispatchMouseDown", "src/ui_widget/PanelManager_DispatchMouseDown.c"},
        {"0050f1b0", "PanelManager_DispatchMouseUp", "src/ui_widget/PanelManager_DispatchMouseUp.c"},
        {"0050f1f0", "PanelManager_DispatchRightMouseDown", "src/ui_widget/PanelManager_DispatchRightMouseDown.c"},
        {"0050f150", "PanelManager_DispatchRightMouseUp", "src/ui_widget/PanelManager_DispatchRightMouseUp.c"},
        {"0050f230", "PanelManager_DispatchKeyDown", "src/ui_widget/PanelManager_DispatchKeyDown.c"},
        {"0050f260", "PanelManager_DispatchKeyUp", "src/ui_widget/PanelManager_DispatchKeyUp.c"},
    };

    /* Addresses where a RENAMES entry is INTENTIONALLY allowed to replace an
     * existing non-FUN_ name (normally left alone). Use only when the current
     * Ghidra name is a low-confidence auto-guess the new name strictly improves
     * on. 004ea580: Ghidra's generic "Update" guess -> the specific
     * "LZHUFUpdate" (the classic LZHUF update() - see LZHUFUpdate.c). */
    static final java.util.Set<String> OVERRIDE_NONDEFAULT =
        new java.util.HashSet<>(java.util.Arrays.asList("004ea580"));

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
            if (!isDefaultName && !OVERRIDE_NONDEFAULT.contains(addrStr)) {
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
