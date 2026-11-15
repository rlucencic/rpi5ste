# rpi5ste

An Atari STE for the Raspberry Pi 5, in a window of its own:
[esp32ste](https://github.com/rlucencic/esp32ste)'s STE (with esp32emu's
68000, Musashi) on the [rpi5emu](https://github.com/rlucencic/rpi5emu)
runtime.

- The 68000 at 8 or 16 MHz or as fast as it goes, TOS 1.62 or 2.06, up to
  4 MB, the blitter, DMA sound, floppies (ST, MSA), and the data folder as
  hard disk C: (GEMDOS: copy programs into it from any computer).
- The setup screen (TOS, memory, CPU, sound, the drives), the web page for
  the disk images, the console, as the rest of the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32ste and rpi5ste cloned side by side, then

```sh
cd rpi5ste && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

`tos162.img` and/or `tos206.img` in the data folder's `roms/`
(`~/rpi5emu/roms`), named as esp32ste's. Not part of this repository.

## Running

```sh
build/rpi5ste                                  # the setup screen first
build/rpi5ste -S --choice "System=TOS 2.06" --choice "Memory=4 MB"
build/rpi5ste game.st                          # with a disk in A:
```

Floppy images live in `~/rpi5emu/floppies/`; drive C: is `~/rpi5emu`
itself (TOS boots from it: AUTO folder, DESKTOP.INF). The keyboard by
position (US), F11 or Page Down Undo, F12 or Page Up Help; the mouse after
a click in the window.

## Licence

MIT.
