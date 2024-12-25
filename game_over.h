#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "utils.h"

#define SPACING 4
#define PADDING 4

#define TEXT_GAME_OVER "Game Over"

namespace GameOver {
  bool is_declared();
  void declare(const String& message);
  void show(OLED& oled);
}

#endif