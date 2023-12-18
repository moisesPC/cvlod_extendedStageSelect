#ifndef FADE_H
#define FADE_H

#include "gfx/color.h"

enum fade_flags {
    FADE_WITH_OUTLINE = 0x0001,
    FADE_IN           = 0x4000,
    FADE_OUT          = 0x8000
};

typedef struct {
    u16 flags;
    color_union color;
    u16 current_time;
    u16 max_time;
} fade_settings_struct;

extern void fade_setAllFlags(u16);
extern void fade_setFlag(u16);
extern void fade_removeFlag(u16);
extern void fade_setColor(u8, u8, u8);
extern void fade_setSettings(u16 flags, s16 fade_time, u8 R, u8 G, u8 B);
extern u32 fade_isFading();
extern void fade_calc();

#endif
