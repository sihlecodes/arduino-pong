#include "game_over.h"

String game_over_message;
bool is_game_over = false;

bool GameOver::is_declared() {
  return is_game_over;
}

void GameOver::declare(const String &message) {
  is_game_over = true;
  game_over_message = message;

  Serial.println(message);
}

void GameOver::show(OLED& oled) {
  uint16_t width = oled.width();
  uint16_t height = oled.height();

  oled.setTextColor(SH110X_WHITE);

  oled.setTextSize(1);
  Size text_game_over = get_text_size(oled, TEXT_GAME_OVER);

  oled.setTextSize(2);
  Size text_message = get_text_size(oled, game_over_message);

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
  oled.println(game_over_message);
  oled.display();
}