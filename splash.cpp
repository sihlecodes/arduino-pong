#include "splash.h"

bool is_splash_showing;

bool Splash::is_showing() {
  return is_splash_showing;
}

void Splash::hide() {
  is_splash_showing = false;
}

inline unsigned long delta, last;
Size text_prompt;

void Splash::setup(OLED& oled) {
  uint16_t width = oled.width();
  uint16_t height = oled.height();

  oled.clearDisplay();

  oled.setTextSize(1);
  Size text_arduino = get_text_size(oled, TEXT_HEADER);
  
  oled.setTextSize(2);
  Size text_title = get_text_size(oled, TEXT_TITLE);

  oled.setTextSize(1);
  text_prompt = get_text_size(oled, TEXT_PROMPT);

  Size bg(PADDING * 2 + text_title.width - 2, PADDING * 2 + text_title.height - 2);
  Size banner(text_arduino.width, text_arduino.height + SPACING + bg.height + SPACING + text_prompt.height);

  oled.setCursor(
    (width - banner.width) / 2,
    (height - banner.height) / 2);

  oled.setTextColor(SH110X_WHITE);
  oled.setTextSize(1);
  oled.println(TEXT_HEADER);

  oled.fillRoundRect(
    (width - bg.width) / 2,
    oled.getCursorY() + SPACING,
    bg.width, bg.height, 2,
    SH110X_WHITE);

  oled.setTextColor(SH110X_BLACK);
  oled.setCursor(
    (width - bg.width) / 2 + PADDING,
    oled.getCursorY() + SPACING + PADDING);

  oled.setTextSize(2);
  oled.println(TEXT_TITLE);

  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);

  last = millis();
}

void Splash::show(OLED& oled) {
  oled.display();
  is_splash_showing = true;
}

bool previous_blink_state;
bool blink_state;

void Splash::loop(OLED &oled) {
  delta = millis() - last; 

  uint16_t x = (oled.width() - text_prompt.width) / 2;
  uint16_t y = oled.getCursorY() + PADDING + SPACING;

  blink_state = (delta / PROMPT_BLINK_INTERVAL) % 2;

  if (blink_state == previous_blink_state)
    return;

  if (blink_state) {
    oled.setCursor(x, y);
    oled.print(TEXT_PROMPT);
    oled.display();

    oled.setCursor(x, y - text_prompt.height);
  }
  else {
    oled.fillRect(x, y, text_prompt.width, text_prompt.height, SH110X_BLACK);
    oled.display();
  }

  previous_blink_state = blink_state;
}