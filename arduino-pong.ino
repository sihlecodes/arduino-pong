#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_SDA 11
#define OLED_SCK 12
#define OLED_RES 10
#define OLED_DC 8
#define OLED_CS 7

typedef Adafruit_SH1106G OLED;

OLED oled(
  OLED_WIDTH, OLED_HEIGHT,
  OLED_SDA, 
  OLED_SCK, OLED_DC,
  OLED_RES, OLED_CS);

struct Size {
  uint16_t width;
  uint16_t height;

  Size(uint16_t width = 0, uint16_t height = 0) : width(width), height(height) {}
};

void setup() {
  Serial.begin(9600);
  oled.begin(0, true);
  
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SH110X_WHITE);
  
  #define SPACING 4
  #define PADDING 4

  #define TEXT_HEADER "Arduino"
  #define TEXT_TITLE "PONG"

  Size text_arduino = get_text_size(oled, TEXT_HEADER);
  Size text_title = get_text_size(oled, TEXT_TITLE);

  Size bg(PADDING * 2 + text_title.width - 2, PADDING * 2 + text_title.height - 2);
  Size banner(text_arduino.width, text_arduino.height + SPACING + bg.height);

  oled.setCursor(
    (OLED_WIDTH - banner.width) / 2,
    (OLED_HEIGHT - banner.height) / 2);

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

  oled.println(TEXT_TITLE);
  oled.display();
}

void loop() {
}

Size get_text_size(OLED &oled, const String &text) {
  Size size;

  oled.getTextBounds(text, 0, 0, nullptr, nullptr,
      &size.width, &size.height);
  
  return size;
}
