#include "rt_clock.hpp"
#include <cstdint>
#include "../util/timestamp.hpp"
#include "../secrets.hpp"

extern const char* ssid;
extern const char* pwd;

void RtClock::init() {
  WiFi.begin(ssid, pwd);
  ntpClient.begin();
  ntpClient.setTimeOffset(ntp_time_offset.as_ms() / 1000);
  // manually control updates with forceUpdate()
  ntpClient.setUpdateInterval(std::numeric_limits<unsigned long>::max());
  last_ntp_update = Timestamp::now();
}

bool RtClock::ntp_update() {
  if (WiFi.status() == WL_CONNECTED) {
    if (Timestamp::now() - last_ntp_update > ntp_update_interval) {
      bool success = ntpClient.forceUpdate();
      last_ntp_update = Timestamp::now();
      return success;
    }
  }
  return false;
}

uint32_t RtClock::get_tod_hour() {
  ntp_update();
  return ntpClient.getHours();
}

uint32_t RtClock::get_tod_hour_12() {
  ntp_update();
  uint32_t hour = ntpClient.getHours();
  return hour <= 12 ? hour : hour - 12;
}

uint32_t RtClock::get_tod_minute() {
  ntp_update();
  return ntpClient.getMinutes();
}

