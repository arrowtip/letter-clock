#include "rt_clock.hpp"
#include <cmath>
#include <cstdint>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "../util/timestamp.hpp"
#include "../secrets.hpp"

extern const char* ssid;
extern const char* pwd;

static WiFiUDP wifiUdp;
static NTPClient ntpClient = NTPClient(wifiUdp, "pool.ntp.org");
static Timestamp last_ntp_update;


bool ntp_update() {
  if (WiFi.status() == WL_CONNECTED) {
    if (Timestamp::now() - last_ntp_update > RtClock::ntp_update_interval) {
      bool success = ntpClient.forceUpdate();
      last_ntp_update = Timestamp::now();
      return success;
    }
  }
  return false;
}

bool is_summer_time() {
  // starts on last sunday in March at 02:00
  // end on last sunday in October at 02:00
  if (RtClock::get_month() > 2 && RtClock::get_month() < 9) return true;
  if (RtClock::get_month() == 2) {
    if (RtClock::get_week_day() == RtClock::SUNDAY && RtClock::get_day() >= 24) {
      if (RtClock::get_tod_hour() >= 2) return true;
    } else if (RtClock::get_day() - RtClock::get_week_day() >= 24) {
      return true;
    }
  } else if (RtClock::get_month() == 9) {
    if (RtClock::get_week_day() == RtClock::SUNDAY && RtClock::get_day() >= 24) {
      if (RtClock::get_tod_hour() < 2) return true;
    } else if (RtClock::get_day() - RtClock::get_week_day() < 24) {
      return true;
    }
  }
  return false;
}

void RtClock::init() {
  WiFi.begin(ssid, pwd);
  ntpClient.begin();
  ntpClient.setTimeOffset(ntp_time_offset.as_ms() / 1000);
  // manually control updates with forceUpdate()
  ntpClient.setUpdateInterval(std::numeric_limits<unsigned long>::max());
  last_ntp_update = Timestamp::now();
}


uint32_t RtClock::get_unix_time() {
  ntp_update();
  return ntpClient.getEpochTime();
}

uint32_t RtClock::get_year() {
  // TODO continue
  return 1970;
}

// first day is zero
uint32_t RtClock::get_day() {
  ntp_update();
  uint32_t num_days = get_unix_time() / 86400 + 1;
  uint32_t in_year = std::fmod(num_days, 365.25);
  bool leap_year = get_year() % 4 == 0;
  if (in_year < 31) {
    return in_year;
  } else if (in_year < 31 + 28 + leap_year) {
    return in_year - 31 - 28 - leap_year;
  }
  in_year -= leap_year;
  if (in_year < 59 + 31) {
    return in_year - 59;
  } else if (in_year < 90 + 30) {
    return in_year - 90;
  } else if (in_year < 120 + 31) {
    return in_year - 120;
  } else if (in_year < 151 + 30) {
    return in_year - 151;
  }
  // TODO continue

  return 0;
}

RtClock::WeekDay RtClock::get_week_day() {
  ntp_update();
  return static_cast<WeekDay>(ntpClient.getDay());
}

RtClock::Month RtClock::get_month() {
  ntp_update();
  uint32_t num_days = get_unix_time() / 86400 + 1;
  uint32_t in_year = std::fmod(num_days, 365.25);
  bool leap_year = get_year() % 4 == 0;
  if (in_year < 31) {
    return JANUARY;
  } else {
    in_year -= leap_year;
  }
  if (in_year < 31 + 28) {
    return FEBRUARY;
  } else if (in_year < 59 + 31) {
    return MARCH;
  } else if (in_year < 90 + 30) {
    return APRIL;
  } else if (in_year < 120 + 31) {
    return MAY;
  } else if (in_year < 151 + 30) {
    return JUNE;
  } else if (in_year < 181 + 31) {
    return JULY;
  } else if (in_year < 212 + 31) {
    return AUGUST;
  } else if (in_year < 243 + 30) {
    return SEPTEMBER;
  } else if (in_year < 273 + 31) {
    return OCTOBER;
  } else if (in_year < 304 + 30) {
    return NOVEMBER;
  } else {
    return DECEMBER;
  }
}

uint32_t RtClock::get_tod_hour() {
  ntp_update();
  uint32_t hour = ntpClient.getHours();
  return (hour + (is_summer_time() ? 1 : 0)) % 24;
}

uint32_t RtClock::get_tod_hour_12() {
  ntp_update();
  uint32_t hour = get_tod_hour() + (is_summer_time() ? 1 : 0);
  return hour <= 12 ? hour : hour - 12;
}

uint32_t RtClock::get_tod_minute() {
  ntp_update();
  return ntpClient.getMinutes();
}

