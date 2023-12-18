#include "controller.h"
#include "gamestate.h"

#define EXTENDED_STAGE_SELECT 2

// Open the extended stage select by pressing
// L + R + Z in the first controller
void extendedStageSelect_hook() {
    if ((controllers[0].buttons_held & BTN_L) &&
        (controllers[0].buttons_held & BTN_R) &&
        (controllers[0].buttons_held & BTN_Z))
    {
        changeGameState(EXTENDED_STAGE_SELECT);
    }
}
