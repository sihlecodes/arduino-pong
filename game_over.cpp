#include "game_over.h"

void show_game_over(OLED& oled, const String& message) {
  uint16_t width = oled.width();
  uint16_t height = oled.height();

  oled.setTextColor(SH110X_WHITE);

  oled.setTextSize(1);
  Size text_game_over = get_text_size(oled, TEXT_GAME_OVER);

  oled.setTextSize(2);
  Size text_message = get_text_size(oled, message);

  Size bg(PADDING * 2 + text_message.width - 2, PADDING * 2 + text_message.height - 2);
  Size banner(text_game_over.width, text_game_over.height + SPACING + bg.height);;

  oled.setCursor(
    (width - banner.width) / 2,
    (height - banner.height) / 2);

  oled.setTextColor(SH110X_WHITE);
  oled.setTextSize(1);
  oled.println(TEXT_GAME_OVER);

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
  oled.println(message);
  oled.display();
}