#include "clock_board.hpp"
#include "firmware/ntp_clock.hpp"
#include "user_interface.h"
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <algorithm>
#include <cstddef>
#include <limits>
#include <span>
#include <variant>

/*#define BOARD_DEBUG*/

static Adafruit_NeoPixel led_strip = Adafruit_NeoPixel(
    ClockBoard::num_pixels, ClockBoard::led_pin, NEO_GRB + NEO_KHZ800);
static std::array<uint8_t, ClockBoard::num_pixels> led_buf_1;
static std::array<uint8_t, ClockBoard::num_pixels> led_buf_2;
static std::span<uint8_t> active(led_buf_1);
static std::span<uint8_t> staging(led_buf_2);

enum FetState : uint8_t {
  FetOpen = 0,
  FetClosed = 1,
};

void swap_buffers() {
  std::swap(active, staging);
  ClockBoard::stage_clear();
}

void ClockBoard::init() {
  pinMode(fet_pin, OUTPUT);
  led_power(false);
  led_strip.begin();
  led_strip.clear();
  led_strip.setBrightness(brightness);
  led_strip.show();
  stage_clear();
  swap_buffers();
  WiFi.setSleepMode(WIFI_LIGHT_SLEEP);
}

std::string ClockBoard::mac_address() {
  return std::string(WiFi.macAddress().c_str());
}

void ClockBoard::led_power(bool on) {
  digitalWrite(fet_pin, on ? FetClosed : FetOpen);
}

void callback_wakeup() {
  wifi_fpm_close();
  wifi_set_opmode(STATION_MODE);
  wifi_station_connect();

  Serial.begin(115200);
  // without println and flush the chip sleeps twice as long
  // as it should.
  Serial.println("");
  Serial.flush();
}

/* system clock is shut off during light sleep */
bool ClockBoard::light_sleep(const Duration &duration) {
  if (duration == Duration::from_ms(0)) {
    return true;
  }
  wifi_station_disconnect();
  bool success = wifi_set_opmode(NULL_MODE);
#ifdef BOARD_DEBUG
  Serial.printf("board set op mode was: %d\n", success);
#endif
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  wifi_fpm_set_wakeup_cb(callback_wakeup);
  wifi_fpm_do_sleep(duration.as_us());
  esp_delay(duration.as_ms() + 1);
  return success;
}

/* system clock is shut off during light sleep */
bool ClockBoard::try_light_sleep(const Duration &duration) {
  // give wifi time to connect if update necessary
  if (NtpClock::need_update() || NtpClock::in_update()) {
#ifdef BOARD_DEBUG
    Serial.println("sleep aborted");
#endif
    return false;
  }
#ifdef BOARD_DEBUG
  Serial.println("board actually going to sleep");
#endif
  return light_sleep(duration);
}

void ClockBoard::stage_clear() { std::fill(staging.begin(), staging.end(), 0); }

bool ClockBoard::update(const Duration time_since_last_transition,
                        const Duration transition_time,
                        Transition &transition) {
  const float progress =
      std::clamp(static_cast<Time>(time_since_last_transition) /
                     static_cast<Time>(transition_time),
                 0.0f, 1.0f);
  const float trans_progress = transition.progress(progress);
  const Color old = (1.0f - trans_progress) * color_time;
  const Color now = color_time * trans_progress;
  for (uint16_t i = 0; i < num_pixels; i++) {
    led_strip.setPixelColor(
        i, static_cast<uint32_t>(now * staging[i] + old * active[i]));
  }
  led_strip.show();
  if (progress >= 1.0f) {
#ifdef BOARD_DEBUG
    Serial.println("board transition completed");
#endif
    swap_buffers();
    return true;
  } else {
    return false;
  }
}

void ClockBoard::stage_es_ist() {
  staging[0] = 1;
  staging[1] = 1;
  staging[3] = 1;
  staging[4] = 1;
  staging[5] = 1;
}
void ClockBoard::stage_nach() {
  staging[40] = 1;
  staging[41] = 1;
  staging[42] = 1;
  staging[43] = 1;
}
void ClockBoard::stage_vor() {
  staging[33] = 1;
  staging[34] = 1;
  staging[35] = 1;
}
void ClockBoard::stage_halb() {
  staging[44] = 1;
  staging[45] = 1;
  staging[46] = 1;
  staging[47] = 1;
}
void ClockBoard::stage_uhr() {
  staging[107] = 1;
  staging[108] = 1;
  staging[109] = 1;
}
void ClockBoard::stage_min_fuenf() {
  staging[7] = 1;
  staging[8] = 1;
  staging[9] = 1;
  staging[10] = 1;
}
void ClockBoard::stage_min_zehn() {
  staging[11] = 1;
  staging[12] = 1;
  staging[13] = 1;
  staging[14] = 1;
}
void ClockBoard::stage_min_drei() {
  staging[22] = 1;
  staging[23] = 1;
  staging[24] = 1;
  staging[25] = 1;
}
void ClockBoard::stage_min_viertel() {
  staging[26] = 1;
  staging[27] = 1;
  staging[28] = 1;
  staging[29] = 1;
  staging[30] = 1;
  staging[31] = 1;
  staging[32] = 1;
}
void ClockBoard::stage_min_zwanzig() {
  staging[15] = 1;
  staging[16] = 1;
  staging[17] = 1;
  staging[18] = 1;
  staging[19] = 1;
  staging[20] = 1;
  staging[21] = 1;
}
void ClockBoard::stage_hour_ein() {
  staging[55] = 1;
  staging[56] = 1;
  staging[57] = 1;
}
void ClockBoard::stage_hour_eins() {
  staging[55] = 1;
  staging[56] = 1;
  staging[57] = 1;
  staging[58] = 1;
}
void ClockBoard::stage_hour_zwei() {
  staging[62] = 1;
  staging[63] = 1;
  staging[64] = 1;
  staging[65] = 1;
}
void ClockBoard::stage_hour_drei() {
  staging[66] = 1;
  staging[67] = 1;
  staging[68] = 1;
  staging[69] = 1;
}
void ClockBoard::stage_hour_vier() {
  staging[73] = 1;
  staging[74] = 1;
  staging[75] = 1;
  staging[76] = 1;
}
void ClockBoard::stage_hour_fuenf() {
  staging[51] = 1;
  staging[52] = 1;
  staging[53] = 1;
  staging[54] = 1;
}
void ClockBoard::stage_hour_sechs() {
  staging[77] = 1;
  staging[78] = 1;
  staging[79] = 1;
  staging[80] = 1;
  staging[81] = 1;
}
void ClockBoard::stage_hour_sieben() {
  staging[88] = 1;
  staging[89] = 1;
  staging[90] = 1;
  staging[91] = 1;
  staging[92] = 1;
  staging[93] = 1;
}
void ClockBoard::stage_hour_acht() {
  staging[84] = 1;
  staging[85] = 1;
  staging[86] = 1;
  staging[87] = 1;
}
void ClockBoard::stage_hour_neun() {
  staging[102] = 1;
  staging[103] = 1;
  staging[104] = 1;
  staging[105] = 1;
}
void ClockBoard::stage_hour_zehn() {
  staging[99] = 1;
  staging[100] = 1;
  staging[101] = 1;
  staging[102] = 1;
}
void ClockBoard::stage_hour_elf() {
  staging[49] = 1;
  staging[50] = 1;
  staging[51] = 1;
}
void ClockBoard::stage_hour_zwoelf() {
  staging[94] = 1;
  staging[95] = 1;
  staging[96] = 1;
  staging[97] = 1;
  staging[98] = 1;
}
