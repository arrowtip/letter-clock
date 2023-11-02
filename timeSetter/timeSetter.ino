#include "src/DS3231/DS3231.h"

const int SECOND = 0;
const int MINUTE = 44;
const int HOUR = 16;
const int DAY = 2;
const int MONTH = 7;
const int YEAR = 2023;
const int DOW = 7;    //monday = 1 etc


DS3231 rtc(SDA, SCL);
Time t;


void setup() {
  rtc.begin();
  rtc.setTime(HOUR, MINUTE, SECOND);
  rtc.setDate(DAY, MONTH, YEAR);
  rtc.setDOW(DOW);
  Serial.begin(9600);

}

void loop() {
   t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" : ");
  Serial.println(t.min);
  Serial.print("date: ");
  Serial.print(t.date);
  Serial.print(t.mon);
  Serial.println(t.year);
}
