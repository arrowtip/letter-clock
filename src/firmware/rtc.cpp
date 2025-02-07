#include "rtc.hpp"
#include "user_interface.h"


static uint64_t time_acc_us = 0;
static uint32_t last_tick = 0;

void Rtc::init() {
  time_acc_us = 0;
  last_tick = system_get_rtc_time();
}

// system time since call to init() in micro seconds
uint64_t Rtc::get_system_time() {
  // cal is in us, bits [11, 0] are decimal
  uint32_t cal = system_rtc_clock_cali_proc();
  uint32_t ticks = system_get_rtc_time();
  time_acc_us += static_cast<uint64_t>(ticks - last_tick) * static_cast<uint64_t>((cal * 1000) >> 12) / 1000;

  last_tick = ticks;

  return time_acc_us;
}




