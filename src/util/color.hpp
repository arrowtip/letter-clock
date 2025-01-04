#pragma once

#include <cstdint>

class Color {
  friend Color operator*(const Color &, const float &);
  friend Color operator*(const float &, const Color &);
  friend Color operator+(const Color &, const Color &);

public:
  constexpr Color(uint32_t rgbw)
      : red(rgbw >> 24), green((rgbw & 0xff0000) >> 16),
        blue((rgbw & 0xff00) >> 8), white(rgbw & 0xff) {}
  constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
      : red(red), green(green), blue(blue), white(white) {}

  explicit inline operator uint32_t() const { 
    return red << 24 | green << 16 | blue << 8 | red;
  }


private:
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t white;
};

inline Color operator*(const Color &c, const float &f) {
  return Color(c.red * f, c.green * f, c.blue * f, c.white * f);
}
inline Color operator+(const Color &c1, const Color &c2) {
  return Color(static_cast<uint32_t>(c1) + static_cast<uint32_t>(c2));
}
