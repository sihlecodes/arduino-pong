#ifndef PONG_H
#define PONG_H

#include <Arduino.h>
#include "utils.h"

namespace Pong {
  void start(OLED& oled, uint16_t width, uint16_t height);
  void update(OLED& oled, bool is_up_pressed, bool is_down_pressed);
  void render_ui(OLED& oled);
  void render(OLED& oled);
}

#endif