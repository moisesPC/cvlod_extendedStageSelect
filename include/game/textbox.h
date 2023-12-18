#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "module.h"
#include "math.h"
#include "gfx/model_info.h"
#include "ghidra_undefined_types.h"

#define TEXT_COLOR_WHITE  0
#define TEXT_COLOR_RED    1
#define TEXT_COLOR_GREEN  2
#define TEXT_COLOR_YELLOW 8
#define TEXT_COLOR_BROWN  7

#define TEXT_FONT_GOLD_COUNTER     0
#define TEXT_FONT_DEFAULT          1

typedef struct {
    u16 field0_0x0; /* Some index */
    u16 display_time;
    u16 field2_0x4;
    u16 text_width; /* Also affects the red arrow */
    void* field4_0x8;       // struct_15*
    s16 X_pos; /* Stored as a s32, read as a s16 */
    undefined field6_0xe;
    undefined field7_0xf;
    s16 Y_pos; /* Stored as a s32, read as a s16 */
    undefined field9_0x12;
    undefined field10_0x13;
    s16 Z_pos; /* Stored as a s32, read as a s16 */
    undefined field12_0x16;
    undefined field13_0x17;
    vec2f field14_0x18;
    u32 flags;
    u8 number_of_lines; /* Number of rows of the text dialog */
    u8 also_text_print_speed; /* Assumption */
    u8 field18_0x26;
    u8 field19_0x27;
    u8 field20_0x28;
    u8 text_print_speed;
    u8 field22_0x2a; /* Index inside textboxModule's field_0x3C data */
    u8 text_X_pos_offset;
    void* field24_0x2c; /* Pointer to a texture buffer? */
    u16 number_of_chars_in_text;
    u16 field26_0x32;
    u16* text_custom_format;
    char* text_ASCII;
    u8 number_of_digits_in_number;
    u8 field30_0x3d;
    undefined field31_0x3e;
    undefined field32_0x3f;
    void* field33_0x40;        // struct_12*
    void* field34_0x44;        // struct_12*
    u16* field35_0x48;
    undefined field36_0x4c;
    undefined field37_0x4d;
    undefined field38_0x4e;
    undefined field39_0x4f;
    undefined field40_0x50;
    undefined field41_0x51;
    undefined field42_0x52;
    undefined field43_0x53;
    char* field44_0x54;
    undefined field45_0x58;
    undefined field46_0x59;
    undefined field47_0x5a;
    undefined field48_0x5b;
    undefined field49_0x5c;
    undefined field50_0x5d;
    undefined field51_0x5e;
    undefined field52_0x5f;
    undefined field53_0x60;
    undefined field54_0x61;
    undefined field55_0x62;
    u8 field56_0x63; /* Appears to be an index */
    undefined field57_0x64;
    undefined field58_0x65;
    undefined field59_0x66;
    undefined field60_0x67;
    undefined field61_0x68;
    undefined field62_0x69;
    undefined field63_0x6a;
    undefined field64_0x6b;
    undefined field65_0x6c;
    undefined field66_0x6d;
    undefined field67_0x6e;
    undefined field68_0x6f;
    void* window;               // textboxWindow*
    void* Module_0x01A8;        // Module_0x01A8*
    s16 field71_0x78;
    u8 field72_0x7a;
    u8 field73_0x7b;
    u8 field74_0x7c;
    u8 color_palette;
    u8 field76_0x7e;
    u8 field77_0x7f;
    u8 field78_0x80;
    u8 field79_0x81;
    undefined field80_0x82;
    undefined field81_0x83;
    undefined field82_0x84;
    undefined field83_0x85;
    undefined field84_0x86;
    undefined field85_0x87;
    undefined field86_0x88;
    u8 field87_0x89;
    u8 field88_0x8a;
    undefined field89_0x8b;
    u16 field90_0x8c;
    u8 field91_0x8e;
    u8 field92_0x8f;
    u8 field93_0x90;
    undefined field94_0x91;
    u8 field95_0x92;
    u8 field96_0x93;
    u8 field97_0x94;
    undefined field98_0x95;
    undefined field99_0x96;
    undefined field100_0x97;
    vec2f textbox_background_size;
    f32 textbox_opening_close_time;
} textboxData;

typedef struct {
    ModuleHeader header;
    u16 field_0x02;
    u16 field_0x04;
    model_info* model;
    u8 field_0x28[16];
    textboxData* data;
    void* field_0x3C;       // struct_11*
    void* field_0x40;       // struct_12*
    u8 field_0x44[8];
    void* field_0x4C;       // struct_14*
    void* field_0x50;       // struct_15*
    void* field_0x54;       // struct_13*
    u16* text_custom_format;
    u16* field_0x5C;
    u16* field_0x60;
    u16* field_0x64;
    void* field_0x68;       // struct_17*
    u32 field_0x6C;
    u8 field_0x70[4];
} textboxModule;

extern textboxModule* createTextboxModule(ModuleHeader* parent);
extern s32 textboxModule_setParams_ASCIIFormattedString(textboxModule* self, const char* ASCII_text, u32 param_3, f32 X_pos, f32 Y_pos, u8 text_print_speed, u8 number_of_lines);
extern u32 textboxModule_setColorPalette(textboxModule* self, u32 color_palette);
extern u32 textboxModule_setParams_number(textboxModule * self, u32 number, u32 visual_flags, f32 X_pos, f32 Y_pos, u8 number_of_digits, u8 font);
extern u32 textboxModule_setASCIIText(textboxModule* self, const char* text_ASCII);
extern u32 textboxModule_setNumber(textboxModule* self, u32 number);
#endif
