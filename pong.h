#ifndef PONG_H
#define PONG_H

#include "utils.h"
#include "game_over.h"
#include "timer.h"

namespace Pong {
  void setup(OLED& oled);
  void loop(OLED& oled, bool is_up_pressed, bool is_down_pressed);
  void render(OLED& oled);
}

#endif