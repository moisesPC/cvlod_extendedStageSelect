#ifndef MEMORY_H
#define MEMORY_H

#include <ultra64.h>

enum heap_kind {
    HEAP_KIND_MULTIPURPOSE,     // Most dynamically-allocated data is allocated on this heap
    HEAP_KIND_1,
    HEAP_KIND_MENU_DATA,        // Assets used on some menus (usually file 0x60 and 0x61). Some menu-related structs are also allocated on this heap
    HEAP_KIND_3,
    HEAP_KIND_4,
    HEAP_KIND_5,
    HEAP_KIND_6,
    HEAP_KIND_MAP_DATA          // Current map's data (assets file, collision data, etc)
};

// There's also 0x4000, see function 0x80001008
enum heap_block_flags_enum {
    HEAP_BLOCK_FREE   = 0x0000,
    HEAP_BLOCK_ACTIVE = 0x8000
};

enum heap_flags_enum {
    HEAP_INACTIVE                = 0x0000,
    HEAP_WRITE_BACK_CACHE_TO_RAM = 0x4000,
    HEAP_ACTIVE                  = 0x8000
};

typedef struct {
    u16 flags;
    u8 field_0x02[2];
    u32 size;                   // Size of the block
    void* field_0x08;           // Display List / GFX related?
    void* data_start;
    void* data_end;             // End of the allocated data, NOT end of the block
    u8 field_0x14[4];           // Related to file decompression?
} heapBlockHeader;

typedef struct {
    u16 flags;
    u8 field_0x02[2];
    u32 size;                       // Size of the heap
    heapBlockHeader* heap_start;    // Start of the block array
} heapInfo;

extern void* heap_alloc(s32 kind, u32 data_size);
extern void heapBlock_free(void* ptr);

#endif
