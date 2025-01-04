#include "firmware/clock_board.hpp"
#include "util/timestamp.hpp"


extern "C" void app_main() {
  ClockBoard::init();

  while (true) {
    // get time

    // check if update necessary

    // sleep a bit
  }
}
