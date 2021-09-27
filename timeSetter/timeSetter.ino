#include<DS3231.h>

const int SECOND = 0;
const int MINUTE = 50;
const int HOUR = 17;
const int DAY = 27;
const int MONTH = 9;
const int YEAR = 2021;
const int DOW = 5;    //monday = 1 etc


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
  Serial.println(t.date);
  Serial.println(t.mon);
  Serial.println(t.year);
}
