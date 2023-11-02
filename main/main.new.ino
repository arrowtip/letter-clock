#include "src/DS3231/DS3231.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define LDR_PIN_POWER 13
#define LDR_PN_VAL A0
#define NUM_PIXELS 114
#define BTN_PIN_POWER 3
#define BTN_PIN_1 4
#define BTN_PIN_2 5
#define BTN_PIN_3 6


Adafruit_NeoPixel led_strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
DS3231 rtc(SDA, SCL);
Time rtc_time;

uint8_t led_was[NUM_PIXELS / 8]; //TODO roof resutl
uint8_t led_should[NUM_PIXELS / 8];

struct RGB_Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};
RGB_Color led_color;
uint8_t max_brightness;
uint8_t last_hour_blinked;
unsigned long last_millis;

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN_POWER, OUTPUT);
  pinMode(LDR_PIN_VAL, INPUT);
  pinMode(BTN_PIN_POWER, OUTPUT);
  pinMode(BTN_PIN_1, INPUT);
  pinMode(BTN_PIN_2, INPUT);
  pinMode(BTN_PIN_3, INPUT);

  led_color.r = 255;
  led_color.g = 255;
  led_color.b = 180;
  
  pixels.begin();
  rtc.begin();
  rtc_time = rtc.getTime();
  hour_blinked = rtc_time.hour;

  max_brightness = get_brightness();
 
  Serial.println("startup complete");
}

void loop() {
  rtc_time = rtc.getTime();
  Serial.println(rtc.getTimeStr(FORMAT_LONG));
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));

  if (rtc_time.hour - last_hour_blinked > 0) {

  } else {

  }

  if (millis() - last_millis > BRIGHTNESS_UPDATE_INTERVAL) {
    max_brightness = get_brightness();
    Serial.print("brightness: ");
    Serial.println(max_brightness);
  }
}






