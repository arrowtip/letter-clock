#include "ntp_clock.hpp"
#include "../secrets.hpp"
#include "../util/timestamp.hpp"
#include "wl_definitions.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <cmath>
#include <cstdint>

//#define NTP_DEBUG

extern const char *ssid;
extern const char *pwd;

static constexpr uint32_t days_per_400y = (365 * 400 + 97);
static constexpr uint32_t days_per_100y = (365 * 100 + 24);
static constexpr uint32_t days_per_4y = (365 * 4 + 1);
static constexpr std::array<uint32_t, 12> days_in_month = {
    31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 29};
// 2000-03-01 (2000 was a leap 400 year leap year)
// see https://en.wikipedia.org/wiki/Leap_year
static constexpr uint32_t leap_epoch = 946684800 + 86400 * (31 + 29);
static constexpr uint64_t secs_per_70y = 2208988800UL;

static WiFiUDP wifiUdp;
static constexpr uint16_t local_udp_port = 1337;
static constexpr size_t ntp_packet_size = 48;
static std::array<byte, ntp_packet_size> udp_buffer;
static constexpr Duration ntp_timeout = Duration::from_s(5);

static Timestamp last_ntp_update;
static Timestamp last_update_start;
static uint64_t last_ntp_time;
static bool during_update;

void NtpClock::init() {
  WiFi.begin(ssid, pwd);
  wifiUdp.begin(local_udp_port);
  last_ntp_update = Timestamp::now();
  last_update_start = Timestamp::now();
  last_ntp_time = 0;
  during_update = false;
}

bool NtpClock::in_update() { return during_update; }

bool NtpClock::need_update() {
  return Timestamp::now() - last_ntp_update > ntp_update_interval;
}

bool ntp_update_start() {
  if (WiFi.status() != WL_CONNECTED)
    return false;
#ifdef NTP_DEBUG
  Serial.println("ntp update started");
#endif
  // flush any existing packets
  while (wifiUdp.parsePacket() != 0)
    wifiUdp.flush();

  memset(udp_buffer.begin(), 0, ntp_packet_size);
  // Initialize values needed to form NTP request
  udp_buffer[0] = 0b11100011; // LI, Version, Mode
  udp_buffer[1] = 0;          // Stratum, or type of clock
  udp_buffer[2] = 6;          // Polling Interval
  udp_buffer[3] = 0xEC;       // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  udp_buffer[12] = 49;
  udp_buffer[13] = 0x4E;
  udp_buffer[14] = 49;
  udp_buffer[15] = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  wifiUdp.beginPacket(NtpClock::ntp_server_name, 123);
  wifiUdp.write(udp_buffer.begin(), ntp_packet_size);
  wifiUdp.endPacket();

  during_update = true;
  last_update_start = Timestamp::now();
  return true;
}

bool ntp_update_end() {
  if (Timestamp::now() - last_update_start > ntp_timeout) {
#ifdef NTP_DEBUG
    Serial.println("ntp update aborted due to timeout");
#endif
    during_update = false;
    return false;
  }
  if (wifiUdp.parsePacket() == 0) {
    delay(10);
    return false;
  }

  // maybe use half time since update_start until now?
  last_ntp_update = last_update_start;

  wifiUdp.read(udp_buffer.begin(), ntp_packet_size);

  uint64_t highWord = word(udp_buffer[40], udp_buffer[41]);
  uint64_t lowWord = word(udp_buffer[42], udp_buffer[43]);
  uint64_t secsSince1900 = (highWord << 16) | lowWord;
  last_ntp_time = secsSince1900 - secs_per_70y;

#ifdef NTP_DEBUG
  Serial.println("ntp update successful");
#endif

  during_update = false;
  return true;
}

bool ntp_update() {
  if (Timestamp::now() - last_ntp_update > NtpClock::ntp_update_interval) {
    if (!NtpClock::in_update()) {
      ntp_update_start();
    } else {
      return ntp_update_end();
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

uint64_t NtpClock::get_unix_time() {
  ntp_update();
  return last_ntp_time +
         (Timestamp::now() - last_ntp_update + ntp_time_offset).as_ms() / 1000;
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
  uint32_t hour = ((get_unix_time() % 86400L) / 3600);
  return (hour + (is_summer_time() ? 1 : 0)) % 24;
}

uint32_t NtpClock::get_tod_hour_12() {
  uint32_t hour = get_tod_hour() + (is_summer_time() ? 1 : 0);
  return hour <= 12 ? hour : hour - 12;
}

uint32_t NtpClock::get_tod_minute() { return ((get_unix_time() % 3600) / 60); }

uint32_t NtpClock::get_tod_second() { return get_unix_time() % 60; }
