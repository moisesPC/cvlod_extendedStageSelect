#ifndef MODEL_INFO_H
#define MODEL_INFO_H

#include "math.h"
#include "color.h"
#include "ghidra_undefined_types.h"

typedef struct {
    s16 type;
    u16 flags;
    struct model_info* field_0x04;
    struct model_info* prev;
    struct model_info* field_0x0C;
    struct model_info* sibling;
    struct model_info* next;
    color_union primitive_color;
    color_union environment_color;
    color_union blend_color;
    color_union fog_color;
    u16 texture;
    u16 palette;
    undefined field_0x2C[12];
    u32 material_dlist;
    u32 dlist;
    s32 assets_file_ID;
    undefined field_0x44[12];
    vec3f position;
    angle model_angle;
    undefined field_0x62[6];
    vec3f size;
    undefined field_0x74[4];
    mf matrix;
} model_info;

#endif
