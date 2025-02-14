#pragma once

#include "../util/timestamp.hpp"
#include <cstdint>

namespace NtpClock {
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
struct Date {
  uint32_t year;
  Month month;
  uint32_t day;
  WeekDay week_day;
  bool leap_year;
};
void init();
uint64_t get_unix_time();
bool get_date(Date &date);
uint32_t get_tod_hour();
uint32_t get_tod_hour_12();
uint32_t get_tod_minute();
uint32_t get_tod_second();
bool in_update();
bool need_update();

constexpr Duration ntp_time_offset = Duration::from_s(3600);
constexpr Duration ntp_update_interval = Duration::from_s(491);
constexpr char* ntp_server_name = "pool.ntp.org";
}; // namespace RtClock
