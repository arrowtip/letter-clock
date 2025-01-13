#include "firmware/clock_board.hpp"
#include "firmware/rt_clock.hpp"
#include "util/timestamp.hpp"
#include <Arduino.h>

static uint32_t last_hour;
static uint32_t last_minute;
static uint32_t my_hour;
static uint32_t my_minute;
static bool update_done;
static constexpr Duration transition_time = Duration::from_s(1);
static Timestamp last_transition;

void setup() {
  ClockBoard::init();
  RtClock::init();

  last_hour = RtClock::get_tod_hour_12();
  last_minute = RtClock::get_tod_minute();
  update_done = true;
  last_transition = Timestamp::now();
  my_hour = RtClock::get_tod_hour_12();
  my_minute = RtClock::get_tod_minute();
}

void loop() {
    my_hour = RtClock::get_tod_hour_12();
    my_minute = RtClock::get_tod_minute();
    // REVIEW: I'm mean it doesn't look nice, but i dont think there is a better way. Any abstraction 
    // would probably make it worse!

    // check if update necessary
    if (my_hour != last_hour || my_minute != last_minute) {
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
      update_done = ClockBoard::update(Timestamp::now() - last_transition, transition_time, ClockBoard::Transition::Linear);
    } else {
      // sleep a bit
      // TODO replace with actual sleep 
      delay(1000); 
    }
}
