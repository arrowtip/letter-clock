#pragma once

#include "../util/color.hpp"
#include "../util/timestamp.hpp"
#include <Adafruit_NeoPixel.h>
#include <array>
#include <cstdint>
/*
 * REVIEW: Maybe you could do something where you express staging as a bitset, but to be honest i actually think
 * this is fine. 
 */

class ClockBoard {
public:
  // REVIEW: I would probably prefer a function style for a transtion.
  // A transition that is a function that maps the domain [0,1] to [0,1]. 
  // Maybe just a function pointer or a abstract class (in any way indirect function call)
  enum class Transition {
    Linear,
  };

  static void init();
  static bool update(const Duration time_since_last_transition,
                     const Duration transition_time,
                     const Transition transition);
  static void stage_clear();

  // REVIEW: inline is kind of out of place here, probably better to define in source file.
  // I would actually assume that this is bad to be inlined simply because it doesn't have to be super fast and 
  // will probably polute I-caches in the main (switch statement).
  static inline void stage_es_ist() {
    staging[0] = 1;
    staging[1] = 1;
    staging[2] = 1;
    staging[3] = 1;
    staging[4] = 1;
    staging[5] = 1;
  }
  static inline void stage_nach() {
    staging[40] = 1;
    staging[41] = 1;
    staging[42] = 1;
    staging[43] = 1;
  }
  static inline void stage_vor() {
    staging[33] = 1;
    staging[34] = 1;
    staging[35] = 1;
  }
  static inline void stage_halb() {
    staging[44] = 1;
    staging[45] = 1;
    staging[46] = 1;
    staging[47] = 1;
  }
  static inline void stage_uhr() {
    staging[107] = 1;
    staging[108] = 1;
    staging[109] = 1;
  }
  static inline void stage_min_fuenf() {
    staging[7] = 1;
    staging[8] = 1;
    staging[9] = 1;
    staging[10] = 1;
  }
  static inline void stage_min_zehn() {
    staging[11] = 1;
    staging[12] = 1;
    staging[13] = 1;
    staging[14] = 1;
  }
  static inline void stage_min_drei() {
    staging[22] = 1;
    staging[23] = 1;
    staging[24] = 1;
    staging[25] = 1;
  }
  static inline void stage_min_viertel() {
    staging[26] = 1;
    staging[27] = 1;
    staging[28] = 1;
    staging[29] = 1;
    staging[30] = 1;
    staging[31] = 1;
    staging[32] = 1;
  }
  static inline void stage_min_zwanzig() {
    staging[15] = 1;
    staging[16] = 1;
    staging[17] = 1;
    staging[18] = 1;
    staging[19] = 1;
    staging[20] = 1;
    staging[21] = 1;
  }
  static inline void stage_hour_ein() {
    staging[55] = 1;
    staging[56] = 1;
    staging[57] = 1;
  }
  static inline void stage_hour_eins() {
    staging[55] = 1;
    staging[56] = 1;
    staging[57] = 1;
    staging[58] = 1;
  }
  static inline void stage_hour_zwei() {
    staging[62] = 1;
    staging[63] = 1;
    staging[64] = 1;
    staging[65] = 1;
  }
  static inline void stage_hour_drei() {
    staging[66] = 1;
    staging[67] = 1;
    staging[68] = 1;
    staging[69] = 1;
  }
  static inline void stage_hour_vier() {
    staging[73] = 1;
    staging[74] = 1;
    staging[75] = 1;
    staging[76] = 1;
  }
  static inline void stage_hour_fuenf() {
    staging[51] = 1;
    staging[52] = 1;
    staging[53] = 1;
    staging[54] = 1;
  }
  static inline void stage_hour_sechs() {
    staging[77] = 1;
    staging[78] = 1;
    staging[79] = 1;
    staging[80] = 1;
    staging[81] = 1;
  }
  static inline void stage_hour_sieben() {
    staging[88] = 1;
    staging[89] = 1;
    staging[90] = 1;
    staging[91] = 1;
    staging[92] = 1;
    staging[93] = 1;
  }
  static inline void stage_hour_acht() {
    staging[84] = 1;
    staging[85] = 1;
    staging[86] = 1;
    staging[87] = 1;
  }
  static inline void stage_hour_neun() {
    staging[102] = 1;
    staging[103] = 1;
    staging[104] = 1;
    staging[105] = 1;
  }
  static inline void stage_hour_zehn() {
    staging[99] = 1;
    staging[100] = 1;
    staging[101] = 1;
    staging[102] = 1;
  }
  static inline void stage_hour_elf() {
    staging[49] = 1;
    staging[50] = 1;
    staging[51] = 1;
  }
  static inline void stage_hour_zwoelf() {
    staging[94] = 1;
    staging[95] = 1;
    staging[96] = 1;
    staging[97] = 1;
    staging[98] = 1;
  }

private:
  static constexpr uint8_t num_pixels = 114;
  static constexpr uint8_t led_pin = 2;
  static constexpr uint8_t brightness = 100;
  static constexpr Color color_time = Color(0xa0a0a0);
  static inline Adafruit_NeoPixel led_strip;
  static inline std::array<uint8_t, num_pixels> led_buf_1;
  static inline std::array<uint8_t, num_pixels> led_buf_2;
  // REVIEW: i would prefer pointers here, but references are also fine.
  static inline std::array<uint8_t, num_pixels> &active = led_buf_1;
  static inline std::array<uint8_t, num_pixels> &staging = led_buf_2;
  static void swap_buffers();
};
