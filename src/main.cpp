#include "firmware/clock_board.hpp"
#include "firmware/ntp_clock.hpp"
#include "firmware/rtc.hpp"
#include "util/timestamp.hpp"
#include <Arduino.h>
#include <algorithm>

#define MAIN_DEBUG

class Linear : public ClockBoard::Transition {
  float progress(const float f) override { return f; }
};
class Square : public ClockBoard::Transition {
  float progress(const float f) override {
    return f < 0.5 ? 2 * f * f : 1 - std::pow(-2 * f + 2, 2) / 2;
  }
};
class Quad : public ClockBoard::Transition {
  float progress(const float f) override {
    return f < 0.5 ? 8 * f * f * f * f : 1 - std::pow(-2 * f + 2, 4) / 2;
  }
};

static uint32_t last_hour;
static uint32_t last_minute;
static uint32_t my_hour;
static uint32_t my_minute;
static uint32_t my_second;
static bool update_done;
static constexpr Duration transition_time = Duration::from_s(2);
static Timestamp last_transition;
static Quad my_transition;
static NtpClock::Date date;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(1);
  delay(1000);

  Rtc::init();
  NtpClock::init();
  ClockBoard::init();

  last_hour = 25;
  last_minute = 61;
  update_done = true;
  last_transition = Timestamp::now();

  Serial.println("");
  Serial.println("##############################");
  Serial.println("#  LETTER CLOCK STARTING UP  #");
  Serial.println("##############################");
  Serial.println("#        MAC address:        #");
  Serial.printf("#     %s      #\n", ClockBoard::mac_address().c_str());
  Serial.println("##############################");
  Serial.println("");

  ClockBoard::led_power(true);
}

void loop() {
  my_hour = NtpClock::get_tod_hour_12();
  my_minute = NtpClock::get_tod_minute();
  my_second = NtpClock::get_tod_second();

  // check if update necessary
  if (my_hour != last_hour || my_minute != last_minute) {
#ifdef MAIN_DEBUG
    Serial.printf("current time: %d : %d\n", my_hour, my_minute);
#endif

    ClockBoard::stage_es_ist();
    if (my_minute < 5) {
      ClockBoard::stage_uhr();
    } else if (my_minute < 10) {
      ClockBoard::stage_min_fuenf();
      ClockBoard::stage_nach();
    } else if (my_minute < 15) {
      ClockBoard::stage_min_zehn();
      ClockBoard::stage_nach();
    } else if (my_minute < 20) {
      ClockBoard::stage_min_viertel();
      ClockBoard::stage_nach();
    } else if (my_minute < 25) {
      ClockBoard::stage_min_zwanzig();
      ClockBoard::stage_nach();
    } else if (my_minute < 30) {
      ClockBoard::stage_min_fuenf();
      ClockBoard::stage_vor();
      ClockBoard::stage_halb();
    } else if (my_minute < 35) {
      ClockBoard::stage_halb();
    } else if (my_minute < 40) {
      ClockBoard::stage_min_fuenf();
      ClockBoard::stage_nach();
      ClockBoard::stage_halb();
    } else if (my_minute < 45) {
      ClockBoard::stage_min_zwanzig();
      ClockBoard::stage_vor();
    } else if (my_minute < 50) {
      ClockBoard::stage_min_drei();
      ClockBoard::stage_min_viertel();
    } else if (my_minute < 55) {
      ClockBoard::stage_min_zehn();
      ClockBoard::stage_vor();
    } else {
      ClockBoard::stage_min_fuenf();
      ClockBoard::stage_vor();
    }
    switch (my_hour) {
    case 0:
      ClockBoard::stage_hour_zwoelf();
      break;
    case 1:
      if (my_minute < 5) {
        ClockBoard::stage_hour_ein();
      } else {
        ClockBoard::stage_hour_eins();
      }
      break;
    case 2:
      ClockBoard::stage_hour_zwei();
      break;
    case 3:
      ClockBoard::stage_hour_drei();
      break;
    case 4:
      ClockBoard::stage_hour_vier();
      break;
    case 5:
      ClockBoard::stage_hour_fuenf();
      break;
    case 6:
      ClockBoard::stage_hour_sechs();
      break;
    case 7:
      ClockBoard::stage_hour_sieben();
      break;
    case 8:
      ClockBoard::stage_hour_acht();
      break;
    case 9:
      ClockBoard::stage_hour_neun();
      break;
    case 10:
      ClockBoard::stage_hour_zehn();
      break;
    case 11:
      ClockBoard::stage_hour_elf();
      break;
    case 12:
      ClockBoard::stage_hour_zwoelf();
      break;
    }
    last_hour = my_hour;
    last_minute = my_minute;
    update_done = false;
    last_transition = Timestamp::now();
  }
  if (!update_done) {
    update_done = ClockBoard::update(Timestamp::now() - last_transition,
                                     transition_time, my_transition);
  } else {
    int32_t sleep_time = 50 - my_second;
    if (sleep_time > 0) {
#ifdef MAIN_DEBUG
      Serial.printf("sleep time: %d\n", sleep_time);
#endif
      ClockBoard::try_light_sleep(Duration::from_s(sleep_time));
    }
  }
}
