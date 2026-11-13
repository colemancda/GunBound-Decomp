GunBound, statically recompiled, as a port for ROCKNIX (Retroid Pocket 5)
==========================================================================

This package holds the recompiled client for Linux/aarch64 and a launcher for
the Ports menu. It holds NO game data: you copy your own game directory in.
The program contains the game's code translated from your GunBound.gme, so it
only runs with that exact executable (BUILD-INFO.txt has its SHA-256) and is
not for redistribution.

STATUS: tried on one Retroid Pocket 5 (ROCKNIX 20261101, glibc 2.44, SDL
2.32.10, sway), driven over ssh with scripted input: it starts from this
launcher, fills the 1080p screen with a 1440x1080 picture, plays sound, logs
in and plays a battle against a PC client at the game's 20 frames per second.
The controller and touch code was exercised there with an SDL virtual
controller and injected touchscreen events. Nobody has yet held the device
and pressed its buttons while this ran: tell from log.txt if something is off.

What you need
-------------
* ROCKNIX on the device, with SSH enabled (Network Settings in
  EmulationStation; the root password is shown under System Settings).
* Your game directory: GunBound.gme, graphics.xfs, sound.xfs, avatar.xfs,
  characterdata.dat, itemdata.dat, specialdata.dat, stage.dat.
* A GunBound server (broker and world server) running on another machine on
  the same network, reachable from the device, listening on that machine's LAN
  address (not 127.0.0.1). The world server's address in the broker's
  directory file must be the LAN address too: it is what the client is told to
  connect to.
* The account: either the launcher's key or a ready token (see "The account").

Install (from the PC, with DEVICE the handheld's IP address)
------------------------------------------------------------
1. Unpack and copy the port:

     tar xzf gunbound-rocknix.tar.gz
     scp -r gunbound-rocknix/GunBound.sh gunbound-rocknix/gunbound root@DEVICE:/storage/roms/ports/

2. Copy your game files into the port's game directory:

     scp /path/to/your/game/{GunBound.gme,*.xfs,*.dat} root@DEVICE:/storage/roms/ports/gunbound/game/

3. The account (one of the two, see below), for example:

     scp /path/to/Launcher.cs root@DEVICE:/storage/roms/ports/gunbound/game/

4. Set the server's address and your account name:

     ssh root@DEVICE vi /storage/roms/ports/gunbound/gunbound.conf
       GB_USER=yourname
       GB_PASSWORD=1234
       GB_BROKER=192.168.1.10:8372

5. First run over ssh, to see what it says (the picture appears on the
   device's screen; Ctrl+C ends it):

     ssh root@DEVICE
     cd /storage/roms/ports
     bash GunBound.sh

   If the screen stays dark, check that the program runs at all, without a
   window, and look at a frame it drew:

     bash GunBound.sh --headless --frames 200 --dump-frame 150 --dump-path /tmp/gb.png
     # then, on the PC:  scp root@DEVICE:/tmp/gb.png .

6. After that it is in EmulationStation under Ports as "GunBound" (refresh
   the game list from the main menu if it is not shown).

The account
-----------
The game expects a 96-character session token on its command line; its
launcher makes it from the user name and the password with a fixed AES key.
That key is not part of this package. Either

* copy the launcher's source file Launcher.cs (it contains the line
  `byte[] key = { 0x.., ... }`) into gunbound/game/, or put the key's 32
  hexadecimal digits into gunbound/launcher.key; the port then builds the
  token on the device from GB_USER and GB_PASSWORD in gunbound.conf; or
* make the token on the PC and copy it as gunbound/token.txt:

     recomp/tools/make_token.py NAME PASSWORD > token.txt
     scp token.txt root@DEVICE:/storage/roms/ports/gunbound/

  (recomp/package.sh --login NAME PASSWORD puts it into the package.)
  With token.txt present GB_USER and GB_PASSWORD are not used.

Controls
--------
  Left stick            move the pointer (faster the further it is pushed)
  Right stick           move the pointer slowly, for small buttons
  A                     Space: charge and fire in battle (hold, then release)
  B                     Escape
  X, right trigger (R2), left stick click (L3)    left mouse button
  Y, left trigger (L2)  right mouse button
  D-pad                 arrow keys: move the mobile, change the angle
  Start                 Enter (chat, confirm)
  Select                Tab (next text field)
  L1 / R1               F7 / F8 (the game's two function-key shortcuts in battle)
  Select + Start        close the game (it is ended two seconds later if it does not close)
  Touchscreen           a finger is the pointer with the left button held:
                        tap to click, drag to drag

Button names are those of the controller mapping the system gives SDL. On
ROCKNIX that mapping comes from EmulationStation's input configuration, where
A is the button labelled A; if A and B (or X and Y) come out swapped, swap
them in pad.cfg. Everything above is in gunbound/pad.cfg and can be changed
there (the file explains its format); item keys F1..F6, for instance, can be
put on any button with a line such as  rs = key f1.

There is no on-screen keyboard: room titles and chat need a USB or Bluetooth
keyboard. Joining a room and playing do not.

In the game: tap the world, then SERVER. CREATE makes a room; a tap on a room
card and JOIN enters one; START (READY for the others) begins the game once
the teams are even.

Troubleshooting
---------------
Everything the port prints is in /storage/roms/ports/gunbound/log.txt.

* "no such file" or "not found" for the program itself although it exists:
  the system's dynamic loader is not where the program expects it. Try
    /usr/lib/ld-linux-aarch64.so.1 ./gunbound --help
  The launcher already does this when /lib/ld-linux-aarch64.so.1 is missing.
* "version `GLIBC_2.38' not found": the system's C library is older than the
  one the program was built with (see BUILD-INFO.txt). ROCKNIX has shipped
  glibc 2.40 or newer since mid-2025, so update ROCKNIX.
* "libSDL2-2.0.so.0: cannot open shared object file": SDL2 is not installed
  where the loader looks; try  LD_LIBRARY_PATH=/usr/lib bash GunBound.sh
* No window / "cannot create the SDL window": try another video driver, e.g.
    SDL_VIDEODRIVER=wayland bash GunBound.sh      (or kmsdrm)
  The launcher uses sway's display (XDG_RUNTIME_DIR=/var/run/0-runtime-dir,
  WAYLAND_DISPLAY=wayland-1) unless those are already set.
* The controller does nothing: log.txt says either "controller connected:
  NAME" or that a joystick has no mapping (with its GUID). In the second case
  add a mapping line for that GUID to
  /storage/.config/SDL-GameControllerDB/gamecontrollerdb.txt. To see what the
  buttons do, add --trace-input to GB_OPTIONS and read log.txt.
* The world list stays empty and "Access time has expired" appears: the
  broker at GB_BROKER was not reached. Check the address, that the server
  listens on its LAN address, and the PC's firewall (TCP 8372 and the world
  server's port, usually 8370; UDP 8363 between players).
* Too slow in battle: this build is not optimised yet; the 3D effects are
  drawn in software. The game's own settings Effect3D and Background in
  gunbound/save/recomp-registry.txt (0 = off) should reduce that work; this
  has not been measured.
* Rare hangs or odd behaviour that a restart cures: the game's threads are
  all kept on one CPU core because the game relies on x86's memory ordering
  (the log's first line says which core). If you changed that with
  --guest-cpu any, change it back.
* A profile of where the time goes:  add  --profile /tmp/gb.prof  to
  GB_OPTIONS, play, quit with Select+Start, and copy /tmp/gb.prof to the PC
  (recomp/tools/profile_report.py reads it together with the program).
