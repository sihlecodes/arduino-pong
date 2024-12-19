#ifndef UTILS_H
#define UTILS_H

#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>

typedef Adafruit_SH1106G OLED;

struct Vector2 {
  float x;
  float y;

  Vector2(float x = 0, float y = 0)
    : x(x), y(y) {}

  void set(float x, float y);
  void set(const Vector2& other);
  void from_angle(float angle);
  float magnitude();
};

struct Size {
  uint16_t width;
  uint16_t height;

  Size(uint16_t width = 0, uint16_t height = 0)
    : width(width), height(height) {}

  void set(uint16_t width, uint16_t height);
};

Size get_text_size(OLED& oled, const String& text);

float map(float value, float in_min, float in_max, float out_min, float out_max);
float clamp(float value, float minimum, float maximum);

#endif