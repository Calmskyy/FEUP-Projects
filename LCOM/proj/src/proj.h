#pragma once

#include "fantale.h"

#define VIDEO_MODE 0x14C
#define SUCCESS 0
#define LOAD_ERROR 1
#define GAME_INIT_ERROR 2
#define VIDEO_MODE_INIT_ERROR 3

/**
 * @brief Returns the game object's static variable.
 *
 * @return The game object.
 */
FanTale *get_game();

