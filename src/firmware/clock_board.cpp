#include "clock_board.hpp"
#include <algorithm>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <limits>


void ClockBoard::init() {
  led_strip = Adafruit_NeoPixel(num_pixels, led_pin, NEO_GRB + NEO_KHZ800);
  led_strip.begin();
  led_strip.clear();
  led_strip.setBrightness(brightness);
  led_strip.show();
  stage_clear();
  swap_buffers();
}

void ClockBoard::stage_clear() { staging.fill(0); }

bool ClockBoard::update(const Duration time_since_last_transition,
                        const Duration transition_time,
                        const Transition transition) {
  // REVIEW: Note implicit float convertion. Might be hard to understand
  const float progress =
      std::clamp(static_cast<Time>(time_since_last_transition) /
                     static_cast<Time>(transition_time),
                 0.0f, 1.0f);
  switch (transition) {
  // REVIEW: i like brackets here "case A: {...;break;}" for a local variable scope.
  case Transition::Linear:
    // REVIEW: uint is a weird type!! just saying i would prefer unsigned int or 
    // even better uint16_t to be compatible without convertion with setPixelColor(uint16_t,...);
    // By the same rule num_pixels should be uint16_t as well.
    for (uint i = 0; i < num_pixels; i++) {
      Color value = color_time * progress * staging[i] +
                    color_time * (1.0f - progress) * active[i];
      led_strip.setPixelColor(i, static_cast<uint32_t>(value));
    }
    break;
  }
  led_strip.show();
  if (progress < 1.0f) {
    return false;
  } else {
    swap_buffers();
    return true;
  }
}

void ClockBoard::swap_buffers() {
  // REVIEW: Use std::swap (<- requires pointers to correctly express intent) or a temporary instead of branching
  if (std::addressof(led_buf_1) == std::addressof(staging)) {
    // REVIEW: Interessting situation not actually sure what is going to happen here!
    staging = led_buf_2;
    active = led_buf_1;
  } else {
    staging = led_buf_1;
    active = led_buf_2;
  }
  stage_clear();
}
