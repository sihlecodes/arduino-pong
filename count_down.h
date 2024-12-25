#ifndef COUNT_DOWN_H
#define COUNT_DOWN_H

#include "utils.h"

inline Timer timer(600);

int count = 3;
bool has_served = false;

namespace CountDown {
  bool is_done() {
    return has_served;
  }

  void setup() {

  }

  void loop(OLED& oled) {
    has_served = count == 0;

    if (!timer.has_ticked() || has_served) {
      timer.update();
      return;
    }

    oled.setTextSize(2);
    Size text_count = get_text_size(oled, String(count));

    oled.setCursor(
      (oled.width() - text_count.width) / 2,
      (oled.height() - text_count.height) /2);

    oled.fillRect(
      oled.getCursorX(), oled.getCursorY(),
      text_count.width, text_count.height, SH110X_BLACK);

    oled.print(count--);
    oled.display();
  }
}

#endif