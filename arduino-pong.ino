#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include "pong.h"

#define BUTTON_UP A1
#define BUTTON_DOWN A0

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_SDA 11
#define OLED_SCK 12
#define OLED_RES 10
#define OLED_DC 8
#define OLED_CS 7

OLED oled(
  OLED_WIDTH, OLED_HEIGHT,
  OLED_SDA,
  OLED_SCK, OLED_DC,
  OLED_RES, OLED_CS);

void setup() {
  Serial.begin(9600);
  oled.begin(0, true);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  show_splash(oled);
  delay(2000);

  Pong::start(oled, OLED_WIDTH, OLED_HEIGHT);
}

bool is_up_pressed;
bool is_down_pressed;

void loop() {
  is_up_pressed = !digitalRead(BUTTON_UP);
  is_down_pressed = !digitalRead(BUTTON_DOWN);

  Pong::update(oled, is_up_pressed, is_down_pressed);
  Pong::render(oled);

  oled.display();
  // delay(10);
}