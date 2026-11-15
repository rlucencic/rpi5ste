#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* A TOS image from the data folder's roms/ (<name>.img: tos162.img,
 * tos206.img; the boards map it from a flash partition of that name), read
 * into memory (big-endian)
 */
typedef struct {
    const uint8_t *data;
    size_t size;
    uint16_t version;       /* e.g. 0x0162 */
    uint32_t base;          /* ROM base address in the ST memory map */
} tos_rom_t;

/* Read roms/<name>.img and check its TOS header; false if it isn't one */
bool tos_rom_map(const char *name, tos_rom_t *rom);

/* Let it go (st_init() keeps its own copy of the ROM) */
void tos_rom_unmap(tos_rom_t *rom);
