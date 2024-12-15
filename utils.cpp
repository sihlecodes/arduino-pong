#include "utils.h"

Size get_text_size(OLED& oled, const String& text) {
  Size size;

  oled.getTextBounds(text, 0, 0, nullptr, nullptr,
                     &size.width, &size.height);

  return size;
}

void Vector2::set(double x, double y) {
  this->x = x;
  this->y = y;
}

double Vector2::magnitude() {
  return sqrt(x * x + y * y);
}

void Vector2::from_angle(double angle) {
  x = magnitude() * cos(angle);
  y = magnitude() * sin(angle);
}

void Size::set(uint16_t width, uint16_t height) {
  this->width = width;
  this->height = height;
}