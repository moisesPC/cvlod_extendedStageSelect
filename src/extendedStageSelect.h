#ifndef EXTENDED_STAGE_SELECT_H
#define EXTENDED_STAGE_SELECT_H

#include "module.h"
#include "textbox.h"

// ID of the Nisitenma-Ichigo file we're gonna replace with the overlay
#define EXTENDED_STAGE_SELECT_OVERLAY_ID 2

#define NUM_MAPS 50
#define OPTION_MAX 8

typedef struct {
    ModuleHeader header;
    textboxModule** mapNamesTextboxes;
    textboxModule** headerNamesTextboxes;
    textboxModule* characterNamesTextbox;
    textboxModule* YesNoTextbox;
    textboxModule* spawnTextbox;
    textboxModule* cutsceneTextbox;
    s8 first_string_ID;
    s8 option;
    s8 map;
    s8 character;
    s8 alternate_costume;
    s8 cutscene;
    s8 spawn;
} extendedStageSelect;

void extendedStageSelect_entrypoint(extendedStageSelect* self);
void extendedStageSelect_createTextboxes(extendedStageSelect* self);
void extendedStageSelect_init(extendedStageSelect* self);
void extendedStageSelect_loop(extendedStageSelect* self);
void extendedStageSelect_warpToMap(extendedStageSelect* self);

void (*extendedStageSelect_functions[])(extendedStageSelect* self) = 
{
    extendedStageSelect_createTextboxes,
    extendedStageSelect_init,
    extendedStageSelect_loop,
    extendedStageSelect_warpToMap
};

// ASCII dots are dashes in LoD text
const char* mapNames[NUM_MAPS] = {
    "Forest of Silence",
    "Castle Wall . Towers",
    "Castle Wall . Main",
    "Villa . Yard",
    "Villa . Foyer",
    "Villa . Hallway",
    "Villa . Maze Garden",
    "Tunnel",
    "Underground Waterway",
    "Castle Center . Main",
    "Castle Center . Bottom Elevator",
    "Castle Center . Gears",
    "Castle Center . Friendly Lizard-man",
    "Castle Center . Library",
    "Castle Center . Nitro Room",
    "Castle Center . Top Elevator",
    "Foggy Lake . Decks",
    "Foggy Lake . Below Decks",
    "Foggy Lake . Lake Pier",
    "Tunnel / Waterway Boss Arena",
    "Castle Keep Stairs",
    "Castle Keep",
    "Castle Crumbling Map",
    "Clock Tower . Gear Climb",
    "Dracula Desert",
    "Rose / Actrice Fan Room",
    "Villa . Vampire Crypt",
    "Room of Clocks",
    "Ending Map",
    "Tower of Sorcery",
    "Tower of Execution . Tower",
    "Tower of Execution . Side Rooms 1",
    "Tower of Execution . Side Rooms 2",
    "Tower of Science . Cube Factory",
    "Tower of Science . Turret",
    "Tower of Ruins . Door Maze",
    "Tower of Ruins . Dark Chambers",
    "Art Tower . Card Galleries",
    "Art Tower . Organ Room",
    "Duel Tower",
    "Clock Tower . Giant Chasm",
    "Clock Tower . Workshop",
    "The Outer Wall",
    "Cornell Intro Village",
    "Intro Cutscene Map",
    "Opening Forest",
    "Dracula Ultimate Map",
    "UNKNOWN 0x2F",
    "UNKNOWN 0x30",
    "Test Grid",
};

#define WOLF_CORNELL 4
const char* characterNames[] = {
    "R",        // Reinhardt
    "C",        // Carrie
    "Co",       // Cornell
    "H",        // Henry
    "W Co"      // Wolf Cornell
};

const char* YesNoSelection[] = {
    "NO",
    "YES"
};

const char* headerNames[] = {
    "LoD Extended Map Select",
    "Character:",
    "Alt Costume:",
    "Cutscene:",
    "Spawn:"
};

#endif
