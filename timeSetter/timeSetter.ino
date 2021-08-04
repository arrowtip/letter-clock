#include<DS3231.h>

const int SECOND = 0;
const int MINUTE = 0;
const int HOUR = 12;
const int DAY = 1;
const int MONTH = 6;
const int YEAR = 2021;


DS3231 rtc(SDA, SCL);
Time t;


void setup() {
  rtc.begin();
  rtc.setTime(17, 47, 0);
  rtc.setDate(1, 5, 2021);

}

void loop() {
   t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" : ");
  Serial.println(t.min);
}
