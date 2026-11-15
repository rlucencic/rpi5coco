#include <stdio.h>
#include <string.h>
#include "emu/emu.h"
#include "rom_store.h"

static const struct {
    const char *name, *other;
    uint32_t size;
} roms[ROM_COUNT] = {
    { "bas13.rom", "bas12.rom", 8192 },
    { "extbas11.rom", NULL, 8192 },
    { "disk11.rom", "disk10.rom", 8192 },
    { "coco3.rom", NULL, 32768 },
};

static const char *s_found[ROM_COUNT];

const char *rom_store_name(rom_id_t id)
{
    if (id >= ROM_COUNT) {
        return "";
    }
    return s_found[id] ? s_found[id] : roms[id].name;
}

uint32_t rom_store_size(rom_id_t id)
{
    return id < ROM_COUNT ? roms[id].size : 0;
}

/* Not erased, not zeros: something at the start of most 2 KB blocks */
static bool plausible(const uint8_t *p, uint32_t size)
{
    int blank = 0, blocks = 0;
    for (uint32_t off = 0; off < size; off += 2048, blocks++) {
        bool ff = true, zero = true;
        for (int i = 0; i < 32; i++) {
            ff &= p[off + i] == 0xFF;
            zero &= p[off + i] == 0x00;
        }
        blank += ff || zero;
    }
    return blank * 4 <= blocks;
}

bool rom_store_load(rom_id_t id, uint8_t *buf)
{
    if (id >= ROM_COUNT) {
        return false;
    }
    uint32_t size = roms[id].size;
    if (emu_rom_read(roms[id].name, buf, size) == (long)size && plausible(buf, size)) {
        s_found[id] = roms[id].name;
        return true;
    }
    if (roms[id].other && emu_rom_read(roms[id].other, buf, size) == (long)size && plausible(buf, size)) {
        s_found[id] = roms[id].other;
        return true;
    }
    return false;
}
