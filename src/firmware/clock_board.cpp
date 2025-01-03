#include "clock_board.hpp"

void ClockBoard::init() {
  led_strip = Adafruit_NeoPixel(num_pixels, led_pin, NEO_GRB + NEO_KHZ800);
  led_strip.begin();
  led_strip.clear();
  led_strip.setBrightness(brightness);
  led_strip.show();
  stage_clear();
}

void ClockBoard::stage_clear() {
  staging.fill(0);
}

bool ClockBoard::update(const Duration time_since_last_transition) {

}
