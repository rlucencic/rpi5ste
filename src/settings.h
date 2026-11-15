#pragma once

#include <stdint.h>

/* The 68000's speed choice, as on the Tab5 (the MaTouch's build stays at
 * 8 MHz)
 */
#define SETTINGS_CPU_CHOICE 1

/* Machine settings kept in the settings file (section "atari"), as
 * esp32ste's NVS; defaults as its menuconfig's: TOS 1.62, 1 MB
 */
typedef struct {
    uint8_t tos;            /* 0 = TOS 1.62, 1 = TOS 2.06 */
    uint16_t ram_kb;        /* 512, 1024, 4096 */
    int8_t resolution;      /* last desktop resolution: 0 low, 1 medium, 2 high, -1 none */
    uint8_t cpu;            /* 68000 speed: SETTINGS_CPU_8MHZ, _16MHZ, _FASTEST */
} settings_t;

enum { SETTINGS_CPU_8MHZ, SETTINGS_CPU_16MHZ, SETTINGS_CPU_FASTEST };

extern settings_t settings;

void settings_load(void);
void settings_save(void);

/* The chosen TOS's name: tos162, tos206 (its file: roms/<name>.img) */
const char *settings_tos_partition(void);
