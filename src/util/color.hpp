#pragma once

#include "HardwareSerial.h"
#include <algorithm>
#include <cmath>
#include <cstdint>

class Color {
  friend Color operator*(const Color &c, const float &f) {
    const uint8_t red =
        std::clamp(static_cast<int>(std::round(f * c.red)), 0, 255);
    const uint8_t green =
        std::clamp(static_cast<int>(std::round(f * c.green)), 0, 255);
    const uint8_t blue =
        std::clamp(static_cast<int>(std::round(f * c.blue)), 0, 255);
    const uint8_t white =
        std::clamp(static_cast<int>(std::round(f * c.white)), 0, 255);
    return Color(red, green, blue, white);
  }
  friend Color operator*(const float &f, const Color &c) { return c * f; }
  friend constexpr Color operator+(const Color &a, const Color &b) {
    const uint8_t red = std::clamp(a.red + b.red, 0, 255);
    const uint8_t green = std::clamp(a.green + b.green, 0, 255);
    const uint8_t blue = std::clamp(a.blue + b.blue, 0, 255);
    const uint8_t white = std::clamp(a.white + b.white, 0, 255);
    return Color(red, green, blue, white);
  }

public:
  constexpr Color(uint32_t wrgb)
      : red((wrgb & 0xff0000) >> 16), green((wrgb & 0xff00) >> 8),
        blue((wrgb & 0xff)), white((wrgb & 0xff000000) >> 24) {}
  constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
      : red(red), green(green), blue(blue), white(white) {}

  explicit inline operator uint32_t() const {
    return (static_cast<uint32_t>(red) << 16) |
           (static_cast<uint32_t>(green) << 8) | static_cast<uint32_t>(blue) |
           (static_cast<uint32_t>(white) << 24);
  }

private:
  const uint8_t red;
  const uint8_t green;
  const uint8_t blue;
  const uint8_t white;
};
