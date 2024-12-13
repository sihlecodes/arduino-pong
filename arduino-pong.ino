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

  show_splash(oled);
}

void loop() {
}

Size get_text_size(OLED &oled, const String &text) {
  Size size;

  oled.getTextBounds(text, 0, 0, nullptr, nullptr,
      &size.width, &size.height);
  
  return size;
}
