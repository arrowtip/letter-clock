#pragma once

#include "../util/timestamp.hpp"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <cstdint>

// REVIEW: could also just be a namespace.
// Avoids having to define to much internal behavior in headers. In my opinion better seperation
class RtClock {
 public:
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
  static void init();
  static uint32_t get_unix_time();
  static uint32_t get_year();
  static Month get_month();
  static uint32_t get_day();
  static WeekDay get_week_day();
  static uint32_t get_tod_hour();
  static uint32_t get_tod_hour_12();
  static uint32_t get_tod_minute();


 private:
  static constexpr Duration ntp_time_offset = Duration::from_s(0);
  static constexpr Duration ntp_update_interval = Duration::from_s(61);
  static inline WiFiUDP wifiUdp;
  static inline NTPClient ntpClient = NTPClient(wifiUdp, "pool.ntp.org");
  static inline Timestamp last_ntp_update;

  static bool ntp_update();
  static bool is_summer_time();
};
