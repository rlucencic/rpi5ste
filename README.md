<h1 align="center">rpi5ste</h1>

<p align="center">
  <b>An Atari STE on the Raspberry Pi 5, in a window of its own.</b><br>
  68000 at 8 MHz (also 16 MHz or as fast as it goes), TOS 1.62 / 2.06, up to 4 MB, floppies, hard disk, ACSI hard disk images.
</p>

<p align="center">
  <img alt="Raspberry Pi 5" src="https://img.shields.io/badge/Raspberry%20Pi-5-c51a4a">
  <img alt="Linux arm64" src="https://img.shields.io/badge/Linux-arm64-333">
  <img alt="SDL 3" src="https://img.shields.io/badge/SDL-3-1d4ed8">
  <img alt="68000" src="https://img.shields.io/badge/CPU-Musashi%2068000-555">
  <img alt="MIT licence" src="https://img.shields.io/badge/licence-MIT-green">
</p>

<p align="center">
  <b>Work in progress:</b> not everything has been tested, and games and demos may or may not
  work satisfactorily.
</p>

<p align="center">
  <img alt="The GEM desktop of TOS 1.62 with drive C: open: the data folder's folders" src="docs/images/tos162-c.png" width="49%">
  <img alt="The GEM desktop of TOS 2.06 with 4 MB" src="docs/images/tos206.png" width="49%">
  <br>
  <sub>TOS 1.62's desktop with drive C: (the data folder) open, and TOS 2.06's with 4 MB, on the Pi.</sub>
</p>

rpi5ste runs [esp32ste](https://github.com/rlucencic/esp32ste)'s STE on a Raspberry Pi 5 with
64-bit Linux, in a window of its own (X11 or Wayland, through SDL 3). The machine is the
same code as on the ESP32 boards: esp32ste's platform-independent core and
[esp32emu](https://github.com/rlucencic/esp32emu)'s CPU core, on
[rpi5emu](https://github.com/rlucencic/rpi5emu), the family's Linux runtime: a setup
screen in the window, sound, the Pi's keyboard and mouse, a web page on your network and a
console.

It's one of the rpi5 family, the Raspberry Pi versions of the esp32 emulators:
[rpi5zx](https://github.com/rlucencic/rpi5zx) (ZX Spectrum),
[rpi5cpc](https://github.com/rlucencic/rpi5cpc) (Amstrad CPC),
[rpi5cbm](https://github.com/rlucencic/rpi5cbm) (Commodore 64 and 128),
[rpi5coco](https://github.com/rlucencic/rpi5coco) (Tandy Color Computer 2 and 3),
[rpi5gs](https://github.com/rlucencic/rpi5gs) (Apple IIGS),
[rpi5msx](https://github.com/rlucencic/rpi5msx) (MSX1 and MSX2),
[rpi5xl](https://github.com/rlucencic/rpi5xl) (Atari 800XL and 130XE),
[rpi5pc](https://github.com/rlucencic/rpi5pc) (IBM PC/XT and PC/AT),
[rpi5mac](https://github.com/rlucencic/rpi5mac) (Macintosh Plus, SE, Classic),
[rpi5mac2](https://github.com/rlucencic/rpi5mac2) (Macintosh LC and II),
[rpi5mac3](https://github.com/rlucencic/rpi5mac3) (Macintosh LC II and LC III),
[rpi5arc](https://github.com/rlucencic/rpi5arc) (Acorn Archimedes),
[rpi5ami](https://github.com/rlucencic/rpi5ami) (Amiga 500, 2000, 600, 1200).

## Features

**The machine**
- 68000 ([Musashi](https://github.com/kstenerud/Musashi) core) at **8 MHz** like an STE. Also
  faster, like an accelerator board: **16 MHz**, or **Fastest**, as
  fast as it keeps real time (16–20 MHz in GEM, far more in tight loops). The
  rest of the machine keeps the STE's timing; the choice applies at once,
  no restart
- Real time at 8 MHz on the Pi with most of a core to spare
- TOS 1.62 or 2.06, chosen on the setup screen
- 512 KB, 1 MB or 4 MB of RAM
- Low, medium and high resolution on one screen, like a multisync monitor;
  Set Preferences offers all three, and the last one is remembered
- Blitter, YM2149 and STE DMA sound, MFP 68901, IKBD with the clock set from the Pi's time

**Disks**
- **Hard disk C:** the data folder, at file level: copy programs into it
  from the Pi or over the network, no disk image or driver needed
- **Floppy drives A: and B:** `.ST` images (read and written) and `.MSA`
  images (read-only), with a WD1772 controller that TOS can format disks on
- **New blank disks** from the setup screen: `EMPTY0001.ST`, `EMPTY0002.ST`, …
- A disk in A: at power-on boots, as games expect

**Around it**
- **A window** of its own on the Pi's desktop (X11 or Wayland), resizable, full screen
  with Ctrl+Alt+F; the picture in the machine's shape, sharp pixels
- **Setup screen** in the window, first thing at start and any time with Ctrl+Alt+M:
  TOS, memory, CPU speed, the sound's volume, the drives and their images (insert, eject, new
  blank ones), Start / Back / Restart, Reset
- **The Pi's keyboard and mouse**: keys by position, as the boards' Bluetooth keyboards;
  a click in the window gives the mouse to the machine, Ctrl+Alt+G takes it back
- **Web page** at `http://<the Pi>:8080/`: drop images (or ZIP files) onto it, insert
  them, make blank ones, and watch the machine and its drives live
- **Sound** through SDL (PipeWire, PulseAudio or ALSA), the machine paced by the clock
- **Console** on the terminal and on `127.0.0.1:6400`: keys, typing, drives, screenshots

<p align="center">
  <img src="docs/images/setup.png" width="80%" alt="The setup screen in the window: the STE's choices, the sound, Disks and Start">
  <br><sub>The setup screen in the window, before the STE starts</sub>
</p>

## Getting started

### 1. What you need

- A Raspberry Pi 5 with 64-bit Linux (developed on Ubuntu 26.04; any Linux with SDL 3.2 or
  later should do)
- The tools and libraries:
  `sudo apt install build-essential cmake ninja-build pkg-config libsdl3-dev libsdl3-ttf-dev libpng-dev`
- [esp32emu](https://github.com/rlucencic/esp32emu), [rpi5emu](https://github.com/rlucencic/rpi5emu)
  and [esp32ste](https://github.com/rlucencic/esp32ste), cloned next to this project
- The ROMs (below)

### 2. Build

```sh
git clone https://github.com/rlucencic/esp32emu.git
git clone https://github.com/rlucencic/rpi5emu.git
git clone https://github.com/rlucencic/esp32ste.git
git clone https://github.com/rlucencic/rpi5ste.git && cd rpi5ste
cmake -S . -B build -G Ninja && cmake --build build
```

### 3. ROMs

`tos162.img` and/or `tos206.img` in the data folder's `roms/`
(`~/rpi5emu/roms`), named as esp32ste's. Not part of this repository.

### 4. First start

1. `build/rpi5ste`: the setup screen opens in a window.
2. Choose the TOS and click **Start**.
3. Put images into `~/rpi5emu/floppies/` (floppies `.ST`, `.MSA`; hard disks `.IMG`, `.HD`),
   drop them on the window or the web page, and insert them on the setup screen's **Disks** page.

## Using it

| To | Do |
|---|---|
| Get back to the setup screen | Ctrl+Alt+M (the machine waits meanwhile) |
| Full screen | Ctrl+Alt+F |
| Give the mouse to the machine, take it back | A click in the window; Ctrl+Alt+G |
| Run as fast as it goes (warp) | Ctrl+Alt+W, again for real speed |
| Take a screenshot | Ctrl+Alt+S (into `~/rpi5emu/screenshots`), or the console's `s` |
| Insert an image | The setup screen's **Disks** page, drop it on the window or the web page, or name it on the command line: `build/rpi5ste game.st` |
| Start straight into the machine | `build/rpi5ste -S`, with the setup screen's rows as `--choice`: `build/rpi5ste -S --choice "System=TOS 2.06" --choice "Memory=4 MB"` |
| Show the window on another computer | Log in with `ssh -C -Y <the Pi>` and start it there: fine for still pictures; games want the Pi's own monitor |
| Make a blank floppy | Setup screen → **Disks** → **New empty disk** |
| Use a hard disk image | Insert it into **ACSI 0** on the **Disks** page and reset: with a driver on it (AHDI, HDDRIVER, ICD, PPDriver) TOS boots from it, its partitions are C: onward and `~/rpi5emu` the next letter |
| Use programs from the Pi | Copy them anywhere into `~/rpi5emu`: it's drive C: |

Images live in `~/rpi5emu/floppies/`, settings in `~/.config/rpi5emu/settings.ini`; the
inserted images are remembered across starts. `build/rpi5ste --help` lists the options.

## How it works

```mermaid
flowchart LR
  subgraph emu [Emulation thread]
    EMU["Emulation<br>68000 · MFP · shifter · blitter<br>WD1772 · YM2149 · DMA sound · IKBD"]
  end
  subgraph main [Main thread]
    WIN["Window · setup screen<br>SDL 3"]
  end
  subgraph others [Other threads]
    WEB[Web page :8080]
    CON[Console :6400]
  end
  EMU -- picture --> WIN
  EMU -- sound --> SND[SDL audio]
  WIN -- keys · mouse --> EMU
  DATA[("~/rpi5emu<br>roms · floppies")]
  EMU <--> DATA
  WEB <--> DATA
```

- **[esp32ste](https://github.com/rlucencic/esp32ste)'s `components/atari_st`**: the STE,
  platform independent: the same code runs on the ESP32 boards.
- **`src/`**: the glue, esp32ste's `main/main.c` ported: memory, ROMs, settings, keyboard map,
  drives and status.
- **[rpi5emu](https://github.com/rlucencic/rpi5emu)**: the window, the setup screen, sound,
  input, the web page, the console, the data folder and the settings.
- **[esp32emu](https://github.com/rlucencic/esp32emu)**: the CPU core (Musashi 68000).

## Development

```sh
../rpi5emu/tools/pi.sh rpi5ste build        # from another computer: sync to the Pi, build there
../rpi5emu/tools/pi.sh rpi5ste run          # its window on this computer (ssh -C -Y)
../rpi5emu/tools/pi.sh rpi5ste headless     # no window: drive it through the console
../rpi5emu/tools/console.sh i 's /tmp/shot.png'
```

`CLAUDE.md` has the details: the layout, how it was ported, the checks; esp32ste's own
`CLAUDE.md` has the machine's.

## Limitations

- Checked on the Pi through its console and screenshots: TOS 1.62 and 2.06 at full speed to the desktop; C: opened with a double click. By hand in the
  window (forwarded to a Mac): TOS 2.06 and the mouse. ACSI: HDDRIVER's demo image booted (headless), its C: opened, `~/rpi5emu` D:. Not yet with the sound
  heard, or with much software.
- Over X forwarding (`ssh -Y`) every changed picture crosses the network: 8 to 15 a second, about 7 to a Mac
  (XQuartz, drawn in software).
- `.STX` (Pasti) images of copy-protected originals don't work; `.MSA`
  images are read-only.
- No FPU, MIDI or Mega STE hardware.
- Floppy access is faster than a real drive, which a few loaders may notice.

## Credits

- [Musashi](https://github.com/kstenerud/Musashi) by Karl Stenerud (MIT
  licence), via Matt Evans' [fork](https://github.com/evansm7/Musashi) for
  embedded use
- The Atari ST community's documentation of the hardware, and
  [Hatari](https://www.hatari-emu.org) as the reference for how it behaves
- [SDL](https://libsdl.org) 3 for the window, the sound and the input

## Licence

[MIT](LICENSE).

Atari, ST and TOS are trademarks of their respective owners. This project
contains no Atari code; you need your own TOS ROM images.
