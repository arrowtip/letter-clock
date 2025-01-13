#pragma once

#include <cstdint>

class Color {
  // REVIEW you can actually define the body here. 
  // friend implies "non-member". They can also be constexpr!
  friend Color operator*(const Color &, const float &);
  friend Color operator*(const float &, const Color &);
  friend Color operator+(const Color &, const Color &);

public:
  constexpr Color(uint32_t rgbw) //REVIEW: prettier would nag that it should be explicit
      : red(rgbw >> 24), green((rgbw & 0xff0000) >> 16), //REVIEW: feels more reasonble to to (rgbw >> 16) & 0xFF, but idk.
        blue((rgbw & 0xff00) >> 8), white(rgbw & 0xff) {}
  constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
      : red(red), green(green), blue(blue), white(white) {}

  explicit inline operator uint32_t() const { 
    // REVIEW: Not sure if UB! uint8_t << 16 
    return red << 24 | green << 16 | blue << 8 | red;
  }


private:
  uint8_t red; // REVIEW: should be const if. Color reflects a immutable data type!
  uint8_t green;
  uint8_t blue;
  uint8_t white;
};

// Prefer constexpr over inline! (constexpr implies inline)
inline Color operator*(const Color &c, const float &f) {
  // REVIEW: No overflow checks!
  return Color(c.red * f, c.green * f, c.blue * f, c.white * f);
}
inline Color operator+(const Color &c1, const Color &c2) {
  // REVIEW: No overflow checks!
  return Color(static_cast<uint32_t>(c1) + static_cast<uint32_t>(c2));
}
