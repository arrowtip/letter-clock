#include "firmware/clock_board.hpp"
#include "firmware/rt_clock.hpp"
#include "util/timestamp.hpp"
#include <Arduino.h>

static uint32_t last_hour;
static uint32_t last_minute;

void setup() {
  ClockBoard::init();
  RtClock::init();

  last_hour = RtClock::get_tod_hour_12();
  last_minute = RtClock::get_tod_minute();
}

void loop() {
    // get time
    uint32_t my_hour = RtClock::get_tod_hour_12();
    uint32_t my_minute = RtClock::get_tod_minute();

    // check if update necessary
    if (my_hour != last_hour || my_minute != last_minute) {


    }

    // sleep a bit
}
