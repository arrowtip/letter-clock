#include "firmware/clock_board.hpp"
#include "firmware/rt_clock.hpp"
#include "util/timestamp.hpp"
#include <Arduino.h>

static uint32_t last_hour;
static uint32_t last_minute;
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
}

void loop() {
    // get time
    uint32_t my_hour = RtClock::get_tod_hour_12();
    uint32_t my_minute = RtClock::get_tod_minute();

    // check if update necessary
    if (!update_done) {
      update_done = ClockBoard::update(Timestamp::now() - last_transition, transition_time, ClockBoard::Transition::Linear);
    }
    if (my_hour != last_hour || my_minute != last_minute) {
      ClockBoard::stage_es_ist();
      if (my_minute < 5) {

      } else if (my_minute < 10) {

      } else if (my_minute < 15) {

      } else if (my_minute < 20) {

      } else if (my_minute < 25) {

      } else if (my_minute < 30) {

      } else if (my_minute < 35) {

      } else if (my_minute < 40) {

      } else if (my_minute < 45) {

      } else if (my_minute < 50) {

      } else if (my_minute < 55) {

      } else {

      } 
      switch (my_hour) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
        case 3:
          break;
        case 4:
          break;
        case 5:
          break;
        case 6:
          break;
        case 7:
          break;
        case 8:
          break;
        case 9:
          break;
        case 10:
          break;
        case 11:
          break;
        case 12:
          break;
      }
      last_hour = my_hour;
      last_minute = my_minute;
    }

    // sleep a bit
    // TODO replace with actual sleep
    delay(1000);
}
