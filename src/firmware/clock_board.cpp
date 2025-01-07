#include "clock_board.hpp"
#include <algorithm>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <limits>
#include "../secrets.hpp"

extern const char* ssid;
extern const char* pwd;

void ClockBoard::init() {
  WiFi.begin(ssid, pwd);
  ntpClient.begin();
  ntpClient.setTimeOffset(ntp_time_offset.as_ms() / 1000);
  // manually control updates with forceUpdate()
  ntpClient.setUpdateInterval(std::numeric_limits<unsigned long>::max());
  last_ntp_update = Timestamp::now();

  led_strip = Adafruit_NeoPixel(num_pixels, led_pin, NEO_GRB + NEO_KHZ800);
  led_strip.begin();
  led_strip.clear();
  led_strip.setBrightness(brightness);
  led_strip.show();
  stage_clear();
}

bool ClockBoard::ntp_update() {
  if (WiFi.status() == WL_CONNECTED) {
    if (Timestamp::now() - last_ntp_update > ntp_update_interval) {
      bool success = ntpClient.forceUpdate();
      last_ntp_update = Timestamp::now();
      return success;
    }
  }
  return false;
}

uint32_t ClockBoard::get_tod_hour() {
  ntp_update();
  return ntpClient.getHours();
}

uint32_t ClockBoard::get_tod_minute() {
  ntp_update();
  return ntpClient.getMinutes();
}

void ClockBoard::stage_clear() { staging.fill(0); }

bool ClockBoard::update(const Duration time_since_last_transition,
                        const Duration transition_time,
                        const Transition transition) {
  ntp_update();
  const float progress =
      std::clamp(static_cast<Time>(time_since_last_transition) /
                     static_cast<Time>(transition_time),
                 0.0f, 1.0f);
  switch (transition) {
  case Transition::Linear:
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
    stage_clear();
    return true;
  }
}

void ClockBoard::swap_buffers() {
  if (std::addressof(led_buf_1) == std::addressof(staging)) {
    staging = led_buf_2;
    active = led_buf_1;
  } else {
    staging = led_buf_1;
    active = led_buf_2;
  }
}
