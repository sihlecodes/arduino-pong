// #ifndef UTILS_H
// #define UTILS_H

#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

typedef Adafruit_SH1106G OLED;

struct Vector2 {
  double x;
  double y;

  Vector2(double x = 0, double y = 0)
    : x(x), y(y) {}
  
  void set(double x, double y);
};

struct Size {
  uint16_t width;
  uint16_t height;

  Size(uint16_t width = 0, uint16_t height = 0)
    : width(width), height(height) {}
  
  void set(uint16_t width, uint16_t height);
};

Size get_text_size(OLED& oled, const String& text);

// #endif