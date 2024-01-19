#ifndef CVLOD_H
#define CVLOD_H

#include "gfx/color.h"

// Data without a specific header goes here

enum opened_menu {
    NOT_ON_MENU      = 0x00,
    MENU_PAUSE       = 0x09,
    MENU_RENON_SHOP  = 0x0A,
    MENU_GAME_OVER   = 0x0E
};

extern void* Nisitenma_Ichigo_loaded_files_ptr[471];

extern color_union background_color;

extern s32 entrance_cutscene_ID;
extern u16 current_opened_menu;

// Obtain the un-mapped address of data from a Nisitenma-Ichigo file
// This is needed if data is trying to be accessed when said data is not mapped by the TLB
// (which usually happens with data within overlays)
#define GET_UNMAPPED_ADDRESS(file_ID, data_ptr)                                                     \
    (void*) (((u32) Nisitenma_Ichigo_loaded_files_ptr[file_ID]) + (((u32) data_ptr) & 0xFFFFFF))

#endif
