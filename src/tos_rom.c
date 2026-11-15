#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emu/emu.h"
#include "emu/log.h"
#include "tos_rom.h"

#define TOS_SIZE            (256 * 1024)

static const char *TAG = "tos_rom";

/* Header country codes (word at +0x1C, bits 15..1) */
static const char *const countries[] = {
    "US", "DE", "FR", "UK", "ES", "IT", "SE", "CH (FR)", "CH (DE)",
    "TR", "FI", "NO", "DK", "SA", "NL", "CZ", "HU",
};

static uint16_t rd16(const uint8_t *p)
{
    return (p[0] << 8) | p[1];
}

static uint32_t rd32(const uint8_t *p)
{
    return ((uint32_t)rd16(p) << 16) | rd16(p + 2);
}

bool tos_rom_map(const char *name, tos_rom_t *rom)
{
    char file[64];
    snprintf(file, sizeof(file), "%s.img", name);
    uint8_t *buf = malloc(TOS_SIZE);
    if (buf == NULL) {
        return false;
    }
    /* 192 KB (1.x) or 256 KB (2.x), the rest as erased flash */
    memset(buf, 0xFF, TOS_SIZE);
    long n = emu_rom_read(file, buf, TOS_SIZE);
    uint32_t base = n >= 0x20 ? rd32(buf + 0x08) : 0;
    if (n < 0x20 || rd16(buf) != 0x602E || (base != 0xE00000 && base != 0xFC0000)) {
        if (n >= 0) {
            EMU_LOGE(TAG, "%s: no TOS image (header %04x, base %06lx)", file, rd16(buf), (unsigned long)base);
        }
        free(buf);
        return false;
    }
    uint16_t version = rd16(buf + 0x02);
    uint16_t country = rd16(buf + 0x1C);
    unsigned int country_id = country >> 1;
    EMU_LOGI(TAG, "%s: TOS %x.%02x, %02x.%02x.%04x, %s, %s, base $%06lx", file, version >> 8, version & 0xFF,
             buf[0x19], buf[0x18], rd16(buf + 0x1A),
             country_id < sizeof(countries) / sizeof(countries[0]) ? countries[country_id] : "??",
             (country & 1) ? "PAL" : "NTSC", (unsigned long)base);
    rom->data = buf;
    rom->size = TOS_SIZE;
    rom->version = version;
    rom->base = base;
    return true;
}

void tos_rom_unmap(tos_rom_t *rom)
{
    free((void *)rom->data);
    rom->data = NULL;
}
