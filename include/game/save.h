#ifndef SAVE_H
#define SAVE_H

#include "ghidra_undefined_types.h"
#include <ultra64.h>

// Player status: Dead
#define DEAD 0x80000000

enum enum_save_flags {
    GAME_WAS_SAVED_AT_LEAST_ONCE=1,
    EASY=16,
    NORMAL=32,
    HARD=64,
    CORNELL_ENDING=4096,
    HARD_MODE_UNLOCKED=8192,
    CORNELL_ALTERNATE_COSTUME=16384,
    REINHARDT_UNLOCKED=32768,
    HENRY_UNLOCKED=65536,
    REINHARDT_GOOD_ENDING=131072,
    CARRIE_GOOD_ENDING=262144,
    REINHARDT_BAD_ENDING=524288,
    CARRIE_BAD_ENDING=1048576,
    CARRIE_UNLOCKED=2097152,
    REINDHART_ALTERNATE_COSTUME=4194304,
    CARRIE_ALTERNATE_COSTUME=8388608,
    VAMP_CURED_USING_PURIFYING=536870912,
    COSTUME_IS_BEING_USED=1073741824,
    CAN_EXPLODE_ON_JUMPING=2147483648
};

enum enum_button_config {
    TYPE_A=0,
    TYPE_B=1,
    TYPE_C=2
};

enum enum_sound_mode {
    STEREO=0,
    MONO=1
};

enum enum_player_character {
    REINHARDT=0,
    CARRIE=1,
    CORNELL=2,
    HENRY=3
};

enum enum_character_animation_set {
    TYPE_REINDHART=0,
    TYPE_CARRIE=1,
    TYPE_CORNELL=2,
    TYPE_HENRY=3,
    TYPE_WOLF_CORNELL=4
};

enum enum_player_subweapon {
    NOTHING=0,
    KNIFE=1,
    HOLY_WATER=2,
    CROSS=3,
    AXE=4,
    WOODEN_STAKE=5,
    ROSE=6
};

typedef struct {
    u32 event_flags[46];
    u32 flags;
    s16 week;
    s16 day;
    s16 hour;
    s16 minute;
    s16 seconds;
    s16 milliseconds;
    u32 gameplay_framecount;
    u16 button_config;
    u16 sound_mode;
    s16 language;               // EUR only
    undefined field12_0xd2;
    undefined field13_0xd3;
    u16 character;
    u16 character_animation_set;
    s16 alternate_costume;
    s16 health;
    s16 field18_0xdc;
    u16 subweapon;
    s32 money;
    u8 inventory_item_amount[49];
    undefined field22_0x115;
    undefined field23_0x116;
    undefined field24_0x117;
    undefined field25_0x118;
    undefined field26_0x119;
    undefined field27_0x11a;
    undefined field28_0x11b;
    undefined field29_0x11c;
    undefined field30_0x11d;
    undefined field31_0x11e;
    undefined field32_0x11f;
    undefined field33_0x120;
    undefined field34_0x121;
    undefined field35_0x122;
    undefined field36_0x123;
    u32 player_status;
    u16 health_depletion_rate_while_poisoned;
    u16 current_hour_VAMP;              // If greater than 0x17, you turn into vampire
    undefined field40_0x12c;
    undefined field41_0x12d;
    undefined field42_0x12e;
    undefined field43_0x12f;
    u16 map_ID;
    u16 map_entrance_ID;
    u16 save_crystal_number;
    undefined field47_0x136;
    undefined field48_0x137;
    u32 times_the_player_has_saved_the_game;
    u32 death_counter;
    undefined field51_0x140;
    undefined field52_0x141;
    undefined field53_0x142;
    undefined field54_0x143;
    undefined field55_0x144;
    undefined field56_0x145;
    undefined field57_0x146;
    undefined field58_0x147;
    undefined field59_0x148;
    undefined field60_0x149;
    undefined field61_0x14a;
    undefined field62_0x14b;
    undefined field63_0x14c;
    undefined field64_0x14d;
    undefined field65_0x14e;
    undefined field66_0x14f;
    undefined field67_0x150;
    undefined field68_0x151;
    undefined field69_0x152;
    undefined field70_0x153;
    undefined field71_0x154;
    undefined field72_0x155;
    undefined field73_0x156;
    undefined field74_0x157;
    undefined field75_0x158;
    undefined field76_0x159;
    undefined field77_0x15a;
    undefined field78_0x15b;
    undefined field79_0x15c;
    undefined field80_0x15d;
    undefined field81_0x15e;
    undefined field82_0x15f;
    u32 money_spent_on_Renon;
} SaveStruct;

extern SaveStruct SaveStruct_gameplay;
extern SaveStruct SaveStruct_cPak;
extern SaveStruct SaveStruct_backup;

extern u16 map_ID;
extern u16 map_entrance_ID;

#endif
