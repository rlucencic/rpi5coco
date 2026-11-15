# rpi5coco: the Tandy Color Computer 2 and 3 on the Raspberry Pi 5

esp32coco's CoCo (`../esp32coco/components/coco`, platform independent,
its parts in folders) on the rpi5emu runtime (`../rpi5emu`, its
CLAUDE.md: the workflow, the Pi, the lessons), the 6809/6309 esp32emu's.
The machine's own behaviour, lessons and tests are esp32coco's CLAUDE.md;
this project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The CoCo as an `emu_machine_t`: esp32coco's `main/main.c` through `../rpi5emu/tools/port_glue.py` and `port_finish.py`, then its two ROM messages |
| `src/settings.c` | esp32coco's, over `emu/nvs.h` (section `coco`) |
| `src/rom_store.c` | `~/rpi5emu/roms/` through `emu_rom_read()` (on the boards the card's `coco/roms`): bas13.rom ... coco3.rom |

Keep `src/main.c` in step with esp32coco's `main/main.c`.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5coco build
../rpi5emu/tools/pi.sh rpi5coco headless     # or run: the window here
../rpi5emu/tools/console.sh i 'T DIR\n'
../rpi5emu/tools/pi.sh rpi5coco shot out.png
```

Console: the runtime's (`h`) and esp32coco's: `k <n>` tap a key (row * 8
+ column: 1 A, 48 ENTER, 35 SPACE), `K <n> 0|1` (55 SHIFT), `T <text>`
(`\n` ENTER), `j <x> <y> <b>` the joystick, `W` the reset button, `w`
rewind the tape, `S <1-8>` fast tape loading, `R <model> [cpu] [ram]`.

Checked on the Pi (2026-11-15, headless): the CoCo 3 (6809, 512 KB) at
100%, 60 frames a second, Disk Extended Color BASIC 2.1 typed into; a blank
disk made, a program saved and DIR (TEST BAS), the file in the image after
quitting; the CoCo 2's Disk Extended Color BASIC 1.1. Not yet: the window
by hand, sound heard, the 6309, OS-9, the hard disk, tapes, games.
