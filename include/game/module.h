#ifndef MODULE_H
#define MODULE_H

#include <ultra64.h>

#define MODULE_SIZE        0x74
#define MODULE_HEADER_SIZE 0x20

typedef struct {
    u8 timer;                      // Could also be "number of accesses to function"
    u8 function;                   // ID within the functions array
} functionInfo;                    // Size = 0x2

typedef struct {
    s16 ID;
    s16 flags;
    s16 field_0x04;
    s16 field_0x06;
    functionInfo current_function[3];
    s16 functionInfo_ID;
    void (*destroy)(void*);                // Officially called "OBJ_destruct"
    struct ModuleHeader* parent;
    struct ModuleHeader* next;
    struct ModuleHeader* child;
} ModuleHeader;                            // Size = 0x20

extern void module_curLevel_goToNextFuncAndClearTimer(u16 current_functionInfo[], s16* functionInfo_ID);

// Mostly used inside entrypoint functions
// Commas at the end of statements needed for matching
#define ENTER(self, functions_array)                                                       \
    s16 funcID;                                                                            \
    funcID = self->header.functionInfo_ID + 1;                                             \
    self->header.functionInfo_ID = funcID,                                                 \
    self->header.current_function[funcID].timer++;                                         \
    functions_array[self->header.current_function[funcID].function](self);                 \
    self->header.functionInfo_ID--;

#endif
