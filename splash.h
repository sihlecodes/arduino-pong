#ifndef SPLASH_H
#define SPLASH_H

#include "utils.h"

#define SPACING 4
#define PADDING 4

#define TEXT_HEADER "Arduino"
#define TEXT_TITLE "PONG"
#define TEXT_PROMPT "PRESS START"

#define PROMPT_BLINK_INTERVAL 600

namespace Splash {
  bool is_showing();
  void hide();
  void setup(OLED& oled, uint16_t width, uint16_t height);
  void loop(OLED& oled, uint16_t width, uint16_t height);
}

#endif