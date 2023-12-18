#include "memory.h"
#include "fade.h"
#include "controller.h"
#include "gamestate.h"
#include "save.h"
#include "cvlod.h"
#include "extendedStageSelect.h"

/*
 * Extended Stage Select mod for Castlevania: Legacy of Darkness, by moisesPC
 * 
 * - The overlay file replaces the unused debug font assets file in the vanilla ROM
 * - The overlay is mapped to 0x0F000000 by the TLB, since we're gonna allocate it dynamically
 * - Handled by module 0x2006 (0x0006 in the vanila ROM) and gamestate 2 (unused in the final game)
 */


// Entrypoint function. Executed every frame as long as the module is active
// Used to branch to the other functions
void extendedStageSelect_entrypoint(extendedStageSelect* self) {
    ENTER(self, extendedStageSelect_functions);
}

// The textboxes must be created in a separate function to ensure that
// the textboxData field associated to each textbox is created.
// Otherwise ptr_textboxModule_setParams_ASCIIFormattedString() will fail
// because it checks whether the textboxData isn't NULL before proceeding
void extendedStageSelect_createTextboxes(extendedStageSelect* self) {
    textboxModule* (*ptr_createTextboxModule)(ModuleHeader*) = createTextboxModule;
    void* (*ptr_heap_alloc)(s32 kind, u32 data_size) = heap_alloc;
    void (*ptr_module_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = module_curLevel_goToNextFuncAndClearTimer;
    u32 i = 0;

    // Headers
    self->headerNamesTextboxes = ptr_heap_alloc(HEAP_KIND_MULTIPURPOSE, sizeof(textboxModule* [5]));
    for (i = 0; i < 5; i++) {
        self->headerNamesTextboxes[i] = ptr_createTextboxModule(self);
    }
    // Map names
    self->mapNamesTextboxes = ptr_heap_alloc(HEAP_KIND_MULTIPURPOSE, sizeof(textboxModule* [OPTION_MAX]));
    for (i = 0; i < OPTION_MAX; i++) {
        self->mapNamesTextboxes[i] = ptr_createTextboxModule(self);
    }
    // Character names
    self->characterNamesTextbox = ptr_createTextboxModule(self);
    // Yes / No
    self->YesNoTextbox = ptr_createTextboxModule(self);
    // Cutscene number
    self->cutsceneTextbox = ptr_createTextboxModule(self);
    // Spawn number
    self->spawnTextbox = ptr_createTextboxModule(self);

    // Go to extendedStageSelect_init()
    ptr_module_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
}

void extendedStageSelect_init(extendedStageSelect* self) {
    void (*ptr_module_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = module_curLevel_goToNextFuncAndClearTimer;
    s32 (*ptr_textboxModule_setParams_ASCIIFormattedString)(textboxModule*, const char*, u32, f32, f32, u8, u8) = textboxModule_setParams_ASCIIFormattedString;
    u32 (*ptr_textboxModule_setColorPalette)(textboxModule*, u32) = textboxModule_setColorPalette;
    u32 (*ptr_textboxModule_setParams_number)(textboxModule*, u32, u32, f32, f32, u8, u8) = textboxModule_setParams_number;
    void (*ptr_fade_setSettings)(u16, s16, u8, u8, u8) = fade_setSettings;
    u32 i = 0;

    /////////////// Headers ///////////////
    // CV64 Extended Map Select
    ptr_textboxModule_setParams_ASCIIFormattedString(self->headerNamesTextboxes[0], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, headerNames[0]), 0, -110.0f, 110.f, 16, 1);
    // Character:
    ptr_textboxModule_setParams_ASCIIFormattedString(self->headerNamesTextboxes[1], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, headerNames[1]), 0, -140.0f, -70.f, 16, 1);
    // Alt. Costume:
    ptr_textboxModule_setParams_ASCIIFormattedString(self->headerNamesTextboxes[2], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, headerNames[2]), 0, -10.0f, -70.f, 16, 1);
    // Cutscene:
    ptr_textboxModule_setParams_ASCIIFormattedString(self->headerNamesTextboxes[3], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, headerNames[3]), 0, -140.0f, -90.f, 16, 1);
    // Spawn:
    ptr_textboxModule_setParams_ASCIIFormattedString(self->headerNamesTextboxes[4], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, headerNames[4]), 0, -10.0f, -90.f, 16, 1);

    for (i = 0; i < 5; i++) {
        ptr_textboxModule_setColorPalette(self->headerNamesTextboxes[i], TEXT_COLOR_YELLOW);
    }

    /////////////// Map Names ///////////////
    for (i = 0; i < OPTION_MAX; i++) {
        // Y pos varies by 20.0f, starting from 90.0f
        ptr_textboxModule_setParams_ASCIIFormattedString(self->mapNamesTextboxes[i], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, mapNames[i]), 0, -120.0f, 90.f - (20.0f * i), 16, 1);
    }
    // Set the color of the first option to red
    ptr_textboxModule_setColorPalette(self->mapNamesTextboxes[0], TEXT_COLOR_RED);

    /////////////// Character names ///////////////
    ptr_textboxModule_setParams_ASCIIFormattedString(self->characterNamesTextbox, GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, characterNames[0]), 0, -60.0f, -70.f, 16, 1);

    /////////////// Yes / No ///////////////
    ptr_textboxModule_setParams_ASCIIFormattedString(self->YesNoTextbox, GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, YesNoSelection[0]), 0, 100.0f, -70.f, 16, 1);

    /////////////// Cutscene ///////////////
    ptr_textboxModule_setParams_number(self->cutsceneTextbox, 0, 0, -58.0f, -90.f, 3, TEXT_FONT_DEFAULT);

    /////////////// Spawn ///////////////
    ptr_textboxModule_setParams_number(self->spawnTextbox, 0, 0, 52.0f, -90.f, 2, TEXT_FONT_DEFAULT);

    // Set background color to black
    background_color.color_u32 = 0x000000FF;
    // Cancel any previous fades
    ptr_fade_setSettings(FADE_IN, 1, 0, 0, 0);

    // Go to extendedStageSelect_loop()
    ptr_module_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
}

void extendedStageSelect_loop(extendedStageSelect* self) {
    void (*ptr_module_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = module_curLevel_goToNextFuncAndClearTimer;
    u32 (*ptr_textboxModule_setASCIIText)(textboxModule*, const char*) = textboxModule_setASCIIText;
    u32 (*ptr_textboxModule_setColorPalette)(textboxModule*, u32) = textboxModule_setColorPalette;
    u32 (*ptr_textboxModule_setNumber)(textboxModule*, u32) = textboxModule_setNumber;
    u32 i = 0;
    
    // Map selection
    if ((controllers[0].buttons_pressed & BTN_DDOWN)) {
        // If the cursor is at the bottom of the list, scroll down
        if (self->option == (OPTION_MAX - 1) && self->map < NUM_MAPS - 1) {
            self->option = (OPTION_MAX - 1);
            self->first_string_ID++;
            // Go through the list of options and update the strings with the next one immediatly below it,
            // simulating the user scrolling down by one in the list
            for (i = 0; i < OPTION_MAX; i++) {
                if (self->first_string_ID >= NUM_MAPS) {
                    self->first_string_ID = NUM_MAPS - 1;
                }
                ptr_textboxModule_setASCIIText(self->mapNamesTextboxes[i], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, mapNames[self->first_string_ID + i]));
            }
        }
        else if (self->option < (OPTION_MAX - 1)) {
            self->option++;
            // Set current option to red, and previous option to white
            ptr_textboxModule_setColorPalette(self->mapNamesTextboxes[self->option], TEXT_COLOR_RED);
            ptr_textboxModule_setColorPalette(self->mapNamesTextboxes[self->option - 1], TEXT_COLOR_WHITE);
        }
        self->map++;
    }
    if ((controllers[0].buttons_pressed & BTN_DUP)) {
        // If the cursor is at the top of the list, scroll up
        if (self->option == 0 && self->map > 0) {
            self->option = 0;
            self->first_string_ID--;
            // Go through the list of options and update the strings with the next one immediatly before it,
            // simulating the user scrolling up by one in the list
            for (i = 0; i < OPTION_MAX; i++) {
                if (self->first_string_ID < 0) {
                    self->first_string_ID = 0;
                }
                ptr_textboxModule_setASCIIText(self->mapNamesTextboxes[i], GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, mapNames[self->first_string_ID + i]));
            }
        }
        else if (self->option > 0) {
            self->option--;
            // Set current option to red, and option below to white
            ptr_textboxModule_setColorPalette(self->mapNamesTextboxes[self->option], TEXT_COLOR_RED);
            ptr_textboxModule_setColorPalette(self->mapNamesTextboxes[self->option + 1], TEXT_COLOR_WHITE);
        }
        self->map--;
    }

    // Stop moving if reaching either the bottom or top of the whole list
    if (self->map >= NUM_MAPS) {
        self->map = NUM_MAPS - 1;
    }
    else if (self->map < 0) {
        self->map = 0;
    }

    // Character selection
    if (controllers[0].buttons_pressed & BTN_L) {
        if (self->character == WOLF_CORNELL) {
            self->character = REINHARDT;
        }
        else {
            self->character++;
        }
        // Update the character name string to show the selected character name
        ptr_textboxModule_setASCIIText(self->characterNamesTextbox, GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, characterNames[self->character]));
    }

    // Alternate costume selection
    if (controllers[0].buttons_pressed & BTN_R) {
        if (self->alternate_costume == TRUE) {
            self->alternate_costume = FALSE;
        }
        else {
            self->alternate_costume = TRUE;
        }
        ptr_textboxModule_setASCIIText(self->YesNoTextbox, GET_UNMAPPED_ADDRESS(EXTENDED_STAGE_SELECT_OVERLAY_ID, YesNoSelection[self->alternate_costume]));
    }

    // Spawn selection
    if (controllers[0].buttons_pressed & BTN_CRIGHT) {
        if (self->spawn >= 120) {
            self->spawn = 120;
        }
        else {
            self->spawn++;
        }
        ptr_textboxModule_setNumber(self->spawnTextbox, self->spawn);
    }
    else if (controllers[0].buttons_pressed & BTN_CLEFT) {
        if (self->spawn <= 0) {
            self->spawn = 0;
        }
        else {
            self->spawn--;
        }
        ptr_textboxModule_setNumber(self->spawnTextbox, self->spawn);
    }

    // Cutscene selection
    if (controllers[0].buttons_pressed & BTN_DRIGHT) {
        if (self->cutscene >= 200) {
            self->cutscene = 200;
        }
        else {
            self->cutscene++;
        }
        ptr_textboxModule_setNumber(self->cutsceneTextbox, self->cutscene);
    }
    else if (controllers[0].buttons_pressed & BTN_DLEFT) {
        if (self->cutscene <= 0) {
            self->cutscene = 0;
        }
        else {
            self->cutscene--;
        }
        ptr_textboxModule_setNumber(self->cutsceneTextbox, self->cutscene);
    }

    // Go to extendedStageSelect_warpToMap() when selecting an option with A
    if (controllers[0].buttons_pressed & BTN_A) {
        ptr_module_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
    }
}

void extendedStageSelect_warpToMap(extendedStageSelect* self) {
    void (*ptr_changeGameState)(s32) = changeGameState;

    map_ID = self->map;
    map_entrance_ID = self->spawn;
    entrance_cutscene_ID = self->cutscene;
    
    switch (self->character) {
        case CORNELL:
            // If selecting Cornell, make sure to not spawn as Wolf Cornell if not selected
            SaveStruct_gameplay.character_animation_set = TYPE_CORNELL;
            break;
        case WOLF_CORNELL:
            self->character = CORNELL;
            SaveStruct_gameplay.character_animation_set = TYPE_WOLF_CORNELL;
            // Set jewel count to 99 so that you can play as much as possible as Wolf Cornell
            SaveStruct_gameplay.inventory_item_amount[1] = 99;
            break;
    }

    SaveStruct_gameplay.character = self->character;
    SaveStruct_gameplay.alternate_costume = self->alternate_costume;
    current_opened_menu = NOT_ON_MENU;          // Prevent any menu to open all of the sudden after warping
    ptr_changeGameState(GAMEPLAY);              // Restart the gameplay state with the selected options
}
