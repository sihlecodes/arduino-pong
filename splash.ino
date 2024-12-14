#define SPACING 4
#define PADDING 4

#define TEXT_HEADER "Arduino"
#define TEXT_TITLE "PONG"

void show_splash(OLED& oled) {
  oled.clearDisplay();

  oled.setTextSize(1);
  Size text_arduino = get_text_size(oled, TEXT_HEADER);
  
  oled.setTextSize(2);
  Size text_title = get_text_size(oled, TEXT_TITLE);

  Size bg(PADDING * 2 + text_title.width - 2, PADDING * 2 + text_title.height - 2);
  Size banner(text_arduino.width, text_arduino.height + SPACING + bg.height);

  oled.setCursor(
    (OLED_WIDTH - banner.width) / 2,
    (OLED_HEIGHT - banner.height) / 2);

  oled.setTextColor(SH110X_WHITE);
  oled.setTextSize(1);
  oled.println(TEXT_HEADER);

  oled.fillRoundRect(
    (OLED_WIDTH - bg.width) / 2,
    oled.getCursorY() + SPACING,
    bg.width, bg.height, 2,
    SH110X_WHITE);

  oled.setTextColor(SH110X_BLACK);
  oled.setCursor(
    (OLED_WIDTH - bg.width) / 2 + PADDING,
    oled.getCursorY() + SPACING + PADDING);

  oled.setTextSize(2);
  oled.println(TEXT_TITLE);

  oled.display();
}