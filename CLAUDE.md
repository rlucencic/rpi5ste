# rpi5ste: the Atari STE on the Raspberry Pi 5

esp32ste's STE (`../esp32ste/components/atari_st`, platform independent)
on the rpi5emu runtime (`../rpi5emu`, its CLAUDE.md: the workflow, the Pi,
the lessons), the 68000 (Musashi, no options) esp32emu's. The machine's own
behaviour, lessons and tests are esp32ste's CLAUDE.md; this project is the
glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The STE as an `emu_machine_t`: esp32ste's `main/main.c` through `../rpi5emu/tools/port_glue.py` and `port_finish.py`, then by hand: esp32ste's menuconfig defaults as constants (colour monitor, every resolution, the data folder as C: and booting from it, the floppy and ACSI images in its st/), up to 4 MB and the CPU choice as on the Tab5, free space by `statvfs()`, the time by `clock_gettime()`, no opcode table copies |
| `src/settings.c` | esp32ste's, over `emu/nvs.h` (section `atari`; defaults TOS 1.62, 1 MB) |
| `src/tos_rom.c` | `st/roms/tos162.img`, `tos206.img` through `emu_rom_read()` (the boards map flash partitions of those names) |

Keep `src/main.c` in step with esp32ste's `main/main.c`.

## Lessons

- **The opcode table copies are 32-bit sized**: `ST_OPCODE_TABLES_SIZE`
  (0x50000, and the Macs' and the Amiga's) is 0x10000 handler pointers of
  4 bytes plus the cycle counts; on the Pi a pointer is 8 bytes and
  `m68k_use_table_copies()` wrote past the buffer (a crash in `st_init()`).
  The copies are the boards' (tables in faster memory than flash): rpi5ste
  passes none.
- **The core's sources are a glob** (`CONFIGURE_DEPENDS`): without it a new
  file in esp32ste's core (`acsi.c`) wasn't built until CMake ran again
  (undefined references at the link).

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5ste build
../rpi5emu/tools/pi.sh rpi5ste headless     # or run: the window here
../rpi5emu/tools/console.sh i 'm -45 -62 0'
../rpi5emu/tools/pi.sh rpi5ste shot out.png
```

Console: the runtime's (`h`) and esp32ste's: `k <hex>` tap a key by its
scancode, `m <dx> <dy> <btn>` the mouse (a double click: `m 0 0 1`, `m 0 0
0` twice, 40 ms apart), `R <tos> <ram KB>`, `C <cpu>`.

Checked on the Pi (2026-11-15, headless): TOS 1.62, 1 MB, at 100% to the
GEM desktop; C: opened by a double click (the data folder's folders);
TOS 2.06 with 4 MB to its desktop. By hand (2026-11-16, the window on a
Mac through XQuartz, `pi.sh run`): TOS 2.06, 4 MB, the grabbed mouse
(since rpi5emu c4383cf; 7 pictures a second while it moves). ACSI
(2026-11-16, headless): HDDRIVER 13.02's demo image in ACSI 0 (`F 2
/tmp/hddrdemo.img`, then `r`), TOS 2.06 booted through it, C: opened by a
double click showed its files, the data folder's drive was D:. Not yet:
sound heard, floppies, 16 MHz, games. The CPU row is 8 or 16 MHz:
esp32ste's Fastest was taken out (2026-11-17), as no other machine has one.
