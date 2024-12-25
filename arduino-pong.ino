#include "utils.h"
#include "splash.h"
#include "pong.h"
#include "count_down.h"

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

  // Reading an analog value from a digital pin yields a
  // somewhat random value, good enough for a seed
  randomSeed(analogRead(0));
  // Oddly enough the first random number I get is 0
  // After consuming this 0, I get proper random values
  random();

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  Splash::setup(oled);
  Splash::show(oled);
}

bool is_up_pressed;
bool is_down_pressed;

enum {SPLASH, COUNT_DOWN, PONG} state = SPLASH;

void loop() {
  is_up_pressed = !digitalRead(BUTTON_UP);
  is_down_pressed = !digitalRead(BUTTON_DOWN);

  switch (state) {
    case SPLASH:
      Splash::loop(oled);

      if (is_up_pressed || is_down_pressed) {
        state = COUNT_DOWN;
        Pong::setup(oled);
      }
      break;

    case COUNT_DOWN:
      CountDown::loop(oled);

      if (CountDown::is_done())
        state = PONG;
      break;
      
    case PONG:
      Pong::loop(oled, is_up_pressed, is_down_pressed);
      break;
  }
}
