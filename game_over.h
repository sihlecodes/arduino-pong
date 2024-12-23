#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "utils.h"

#define SPACING 4
#define PADDING 4

#define TEXT_GAME_OVER "Game Over"

void show_game_over(OLED& oled, const String& message);

#endif