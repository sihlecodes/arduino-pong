#include "utils.h"

Size get_text_size(OLED& oled, const String& text) {
  Size size;

  oled.getTextBounds(text, 0, 0, nullptr, nullptr,
                     &size.width, &size.height);

  return size;
}

double clamp(double value, double minimum, double maximum) {
  return max(min(value, maximum), minimum);
}

void Vector2::set(double x, double y) {
  this->x = x;
  this->y = y;
}

void Vector2::set(const Vector2& other) {
  this->x = other.x;
  this->y = other.y;
}

double Vector2::magnitude() {
  return sqrt(x * x + y * y);
}

void Vector2::from_angle(double angle) {
  double magnitude_ = magnitude();
  
  x = magnitude_ * cos(angle);
  y = magnitude_ * sin(angle);
}

void Size::set(uint16_t width, uint16_t height) {
  this->width = width;
  this->height = height;
}