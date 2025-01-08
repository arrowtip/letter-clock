#pragma once

#include "../util/timestamp.hpp"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <cstdint>

class RtClock {
 public:
  static void init();
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
};
