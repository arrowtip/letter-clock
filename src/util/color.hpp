#pragma once

#include <algorithm>
#include <cstdint>

class Color {
  friend constexpr Color operator*(const Color &c, const float &f) {
    const uint8_t red = std::clamp(0.0f, 255.0f, f * c.red);
    const uint8_t green = std::clamp(0.0f, 255.0f, f * c.green);
    const uint8_t blue = std::clamp(0.0f, 255.0f, f * c.blue);
    const uint8_t white = std::clamp(0.0f, 255.0f, f * c.white);
    return Color(red, green, blue, white);
  }
  friend constexpr Color operator*(const float &f, const Color &c) {
    return c * f;
  }
  friend constexpr Color operator+(const Color &a, const Color &b) {
    const uint8_t red = std::clamp(0, 255, a.red + b.red);
    const uint8_t green = std::clamp(0, 255, a.green + b.green);
    const uint8_t blue = std::clamp(0, 255, a.blue + b.blue);
    const uint8_t white = std::clamp(0, 255, a.white + b.white);
    return Color(red, green, blue, white);
  }

public:
  constexpr Color(uint32_t rgbw)
      : red(rgbw >> 24), green((rgbw & 0xff0000) >> 16),
        blue((rgbw & 0xff00) >> 8), white(rgbw & 0xff) {}
  constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
      : red(red), green(green), blue(blue), white(white) {}

  explicit inline operator uint32_t() const {
    return static_cast<uint32_t>(red) << 24 |
           static_cast<uint32_t>(green) << 16 |
           static_cast<uint32_t>(blue) << 8 | static_cast<uint32_t>(red);
  }

private:
  const uint8_t red;
  const uint8_t green;
  const uint8_t blue;
  const uint8_t white;
};
