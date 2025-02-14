#pragma once
#include "../util/color.hpp"
#include "../util/timestamp.hpp"
#include "pins_arduino.h"
#include <array>
#include <cstdint>

namespace ClockBoard {
class Transition {
 public:
  // maps f in [0, 1] to progress in [0, 1]
  virtual float progress(const float f) = 0;
};
void init();
bool update(const Duration time_since_last_transition,
            const Duration transition_time, Transition &transition);
void stage_clear();
bool light_sleep(const Duration &duration);
bool try_light_sleep(const Duration &duration);
std::string mac_address();

void stage_es_ist();
void stage_nach();
void stage_vor();
void stage_halb();
void stage_uhr();
void stage_min_fuenf();
void stage_min_zehn();
void stage_min_drei();
void stage_min_viertel();
void stage_min_zwanzig();
void stage_hour_ein();
void stage_hour_eins();
void stage_hour_zwei();
void stage_hour_drei();
void stage_hour_vier();
void stage_hour_fuenf();
void stage_hour_sechs();
void stage_hour_sieben();
void stage_hour_acht();
void stage_hour_neun();
void stage_hour_zehn();
void stage_hour_elf();
void stage_hour_zwoelf();

constexpr uint16_t num_pixels = 114;
constexpr uint8_t led_pin = D1;
constexpr uint8_t brightness = 100;
constexpr Color color_time = Color(0xa0a0a0);
}; // namespace ClockBoard
