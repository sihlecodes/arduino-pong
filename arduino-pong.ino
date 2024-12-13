#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

#define BUTTON_UP A1
#define BUTTON_DOWN A0

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

const uint8_t bitmap_up[] PROGMEM = {
  B00001000,
  B00000000,
  B00011100,
  B00000000,
  B00111110,
  B00000000,
  B01111111,
  B00000000,
  B11111111,
  B10000000,
};

const uint8_t bitmap_down[] PROGMEM = {
  B11111111,
  B10000000,
  B01111111,
  B00000000,
  B00111110,
  B00000000,
  B00011100,
  B00000000,
  B00001000,
  B00000000,
};

void setup() {
  Serial.begin(9600);
  oled.begin(0, true);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  show_splash(oled);
}

bool is_up_pressed;
bool is_down_pressed;

void loop() {
  is_up_pressed = !digitalRead(BUTTON_UP);
  is_down_pressed = !digitalRead(BUTTON_DOWN);

  uint16_t x = 10;
  uint16_t y = 48;
  uint16_t w = 9;
  uint16_t h = 5;

  if (is_up_pressed) {
    Serial.println("UP");

    oled.fillRect(x, y, w, h, SH110X_BLACK);
    oled.drawBitmap(x, y, bitmap_up, w, h, SH110X_WHITE);
  }

  if (is_down_pressed) {
    Serial.println("DOWN");

    oled.fillRect(x, y, w, h, SH110X_BLACK);
    oled.drawBitmap(x, y, bitmap_down, w, h, SH110X_WHITE);
  }

  oled.display();

  delay(100);
}

Size get_text_size(OLED &oled, const String &text) {
  Size size;

  oled.getTextBounds(text, 0, 0, nullptr, nullptr,
                     &size.width, &size.height);

  return size;
}