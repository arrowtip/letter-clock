#include "clock_board.hpp"

void ClockBoard::init() {
  led_strip = Adafruit_NeoPixel(num_pixels, led_pin, NEO_GRB + NEO_KHZ800);
  led_strip.begin();
  led_strip.clear();
  led_strip.setBrightness(brightness);
  led_strip.show();
  stage_clear();
}

void ClockBoard::stage_clear() { staging.fill(0); }

bool ClockBoard::update(const float progress, const Transition transition) {
  switch (transition) {
  case Transition::Linear:
    for (uint i = 0; i < num_pixels; i++) {
      Color value = color_time * progress * staging[i] +
                    color_time * (1.0f - progress) * active[i];
      led_strip.setPixelColor(i, static_cast<uint32_t>(value));
    }
    led_strip.show();
    break;
  }
}
