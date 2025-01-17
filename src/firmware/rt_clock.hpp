#pragma once

#include "../util/timestamp.hpp"
#include <cstdint>

namespace RtClock {
enum WeekDay : uint32_t {
  SUNDAY = 0,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
};
enum Month : uint32_t {
  JANUARY = 0,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER,
};
void init();
uint32_t get_unix_time();
uint32_t get_year();
Month get_month();
uint32_t get_day();
WeekDay get_week_day();
uint32_t get_tod_hour();
uint32_t get_tod_hour_12();
uint32_t get_tod_minute();

constexpr Duration ntp_time_offset = Duration::from_s(0);
constexpr Duration ntp_update_interval = Duration::from_s(61);
}; // namespace RtClock
