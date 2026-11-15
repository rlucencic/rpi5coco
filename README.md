# rpi5coco

A Tandy Color Computer 2 and 3 for the Raspberry Pi 5, in a window of its
own: [esp32coco](https://github.com/rlucencic/esp32coco)'s CoCo on the
[rpi5emu](https://github.com/rlucencic/rpi5emu) runtime.

- A 6809 or Hitachi 6309, the VDG and the GIME, cartridges, cassettes,
  floppies (DSK, OS9) and an OS-9 hard disk (VHD).
- The setup screen (model, CPU, memory, monitor, sound, the drives), the
  web page for the disk images, the console, as the rest of the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32coco and rpi5coco cloned side by side, then

```sh
cd rpi5coco && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

In the data folder's `roms/` (`~/rpi5emu/roms`), named as esp32coco's:
`bas13.rom` (or `bas12.rom`), `extbas11.rom`, `disk11.rom` (or
`disk10.rom`) for the CoCo 2, `coco3.rom` for the CoCo 3. Not part of this
repository.

## Running

```sh
build/rpi5coco                              # the setup screen first
build/rpi5coco -S --choice "Model=CoCo 2"   # straight into a CoCo 2
build/rpi5coco os9.dsk                      # with a disk in floppy 0
```

Disks, tapes and cartridges live in `~/rpi5emu/coco/`. Letters by
position, digits and symbols by the character a US keyboard gives; Esc
BREAK, Home CLEAR, Ctrl and Alt the CoCo 3's CTRL and ALT, F1 and F2 its
F1 and F2, F5 the reset button. The numeric keypad is the joystick (F11
switches between the right and the left one).

## Licence

MIT.
