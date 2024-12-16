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
  void show(OLED& oled);
  void setup(OLED& oled);
  void loop(OLED& oled);
}

#endif