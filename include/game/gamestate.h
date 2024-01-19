#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <ultra64.h>

enum gameState_ID {
    KONAMI_LOGO = 1,
    GAMESTATE_2 = 2,
    GAMEPLAY = 3,
    GAMENOTE_DELETE = 4,
    OPENING = 5,
    TITLE_SCREEN = 6,
    TITLE_DEMO = 7,
    DATA_SCREEN = 8,
    OPTIONS = 9,
    CREDITS = 10,
    GAME_OVER = 11,
    EXPANSION_PAK_SCREEN = 12
};

extern void changeGameState(s32 game_state);

#endif
