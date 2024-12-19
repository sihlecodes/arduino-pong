#include "utils.h"

Size get_text_size(OLED& oled, const String& text) {
  Size size;

  oled.getTextBounds(text, 0, 0, nullptr, nullptr,
                     &size.width, &size.height);

  return size;
}

float map(float value, float in_min, float in_max, float out_min, float out_max) {
  float percentage = (value - in_min) / (in_max - in_min);
  return out_min + (out_max - out_min) * percentage;
}

float clamp(float value, float minimum, float maximum) {
  return max(min(value, maximum), minimum);
}

void Vector2::set(float x, float y) {
  this->x = x;
  this->y = y;
}

void Vector2::set(const Vector2& other) {
  this->x = other.x;
  this->y = other.y;
}

float Vector2::magnitude() {
  return sqrt(x * x + y * y);
}

void Vector2::from_angle(float angle) {
  float magnitude_ = magnitude();

  x = magnitude_ * cos(angle);
  y = magnitude_ * sin(angle);
}

void Size::set(uint16_t width, uint16_t height) {
  this->width = width;
  this->height = height;
}