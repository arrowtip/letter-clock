#include "ntp_clock.hpp"
#include "../secrets.hpp"
#include "../util/timestamp.hpp"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <cmath>
#include <cstdint>

extern const char *ssid;
extern const char *pwd;

static WiFiUDP wifiUdp;
static NTPClient ntpClient = NTPClient(wifiUdp, "pool.ntp.org");
static Timestamp last_ntp_update;

static constexpr uint32_t days_per_400y = (365 * 400 + 97);
static constexpr uint32_t days_per_100y = (365 * 100 + 24);
static constexpr uint32_t days_per_4y = (365 * 4 + 1);
static constexpr std::array<uint32_t, 12> days_in_month = {
    31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 29};
// 2000-03-01 (2000 was a leap 400 year leap year)
// see https://en.wikipedia.org/wiki/Leap_year
static constexpr uint32_t leap_epoch = 946684800 + 86400 * (31 + 29);

bool ntp_update() {
  if (Timestamp::now() - last_ntp_update > NtpClock::ntp_update_interval) {
    if (WiFi.status() == WL_CONNECTED) {
      bool success = ntpClient.forceUpdate();
      Serial.printf("NTP update: %d\n", success);
      if (success)
        last_ntp_update = Timestamp::now();
      return success;
    }
  }
  return false;
}

bool is_summer_time() {
  // starts on last sunday in March at 02:00
  // end on last sunday in October at 02:00
  NtpClock::Date date;
  NtpClock::get_date(date);
  if (date.month > NtpClock::MARCH && date.month < NtpClock::OCTOBER)
    return true;
  if (date.month == NtpClock::MARCH) {
    if (date.week_day == NtpClock::SUNDAY && date.day >= 24) {
      if (NtpClock::get_tod_hour() >= 2)
        return true;
    } else if (date.day - date.week_day >= 24) {
      return true;
    }
  } else if (date.month == NtpClock::OCTOBER) {
    if (date.week_day == NtpClock::SUNDAY && date.day >= 24) {
      if (NtpClock::get_tod_hour() < 2)
        return true;
    } else if (date.day - date.week_day < 24) {
      return true;
    }
  }
  return false;
}

void NtpClock::init() {
  WiFi.begin(ssid, pwd);
  ntpClient.begin();
  ntpClient.setTimeOffset(ntp_time_offset.as_ms() / 1000);
  // manually control updates with forceUpdate()
  ntpClient.setUpdateInterval(std::numeric_limits<unsigned long>::max());
  last_ntp_update = Timestamp::now();
}

uint64_t NtpClock::get_unix_time() {
  ntp_update();
  return ntpClient.getEpochTime();
}

bool NtpClock::get_date(NtpClock::Date &date) {
  int64_t secs = get_unix_time() - leap_epoch;
  int64_t days = secs / 86400;
  int32_t rem_secs = secs % 86400;
  // started negative days need to be counted
  if (rem_secs < 0) {
    rem_secs += 86400;
    days--;
  }
  int32_t cycles_qcentr = days / days_per_400y;
  int32_t rem_days = days % days_per_400y;
  if (rem_days < 0) {
    rem_days += days_per_400y;
    cycles_qcentr--;
  }
  uint32_t cycles_centr = rem_days / days_per_100y;
  if (cycles_centr == 4)
    cycles_centr--;
  rem_days -= cycles_centr * days_per_100y;

  uint32_t cycles_q = rem_days / days_per_4y;
  if (cycles_q == 4)
    cycles_q--;
  rem_days -= cycles_q * days_per_4y;

  int32_t rem_years = rem_days / 365;
  if (rem_years == 4)
    rem_years--;
  rem_days -= rem_years * 365;

  // leap year skipped every 100 years if not also divisible by 400
  bool leap = !rem_years && (cycles_q || !cycles_centr);
  uint32_t months;
  for (months = 0; days_in_month[months] <= rem_days; months++) {
    rem_days -= days_in_month[months];
  }
  months += 2;
  if (months >= 12) {
    months -= 12;
    rem_years++;
  }

  int32_t week_day = (3 + days) % 7;
  if (week_day < 0)
    week_day += 7;

  date.year =
      rem_years + 4 * cycles_q + 100 * cycles_centr + 400 * cycles_qcentr;
  date.month = static_cast<NtpClock::Month>(months);
  date.day = rem_days + 1;
  date.week_day = static_cast<NtpClock::WeekDay>(week_day);
  date.leap_year = leap;

  return true;
};

uint32_t NtpClock::get_tod_hour() {
  ntp_update();
  uint32_t hour = ntpClient.getHours();
  return (hour + (is_summer_time() ? 1 : 0)) % 24;
}

uint32_t NtpClock::get_tod_hour_12() {
  uint32_t hour = get_tod_hour() + (is_summer_time() ? 1 : 0);
  return hour <= 12 ? hour : hour - 12;
}

uint32_t NtpClock::get_tod_minute() {
  ntp_update();
  return ntpClient.getMinutes();
}
