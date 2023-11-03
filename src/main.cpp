#include "DS3231.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define LDR_PIN_POWER 13
#define LDR_PIN_VAL A0
#define NUM_PIXELS 114
#define BTN_PIN_POWER 3
#define BTN_PIN_1 4
#define BTN_PIN_2 5
#define BTN_PIN_3 6

#define RED 0xff0000
#define GREEN 0xff00
#define BLUE 0xee
#define TRANSITION_TIME 3000


Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
DS3231 rtc(SDA, SCL);
Time rtc_time;

uint8_t led_buff_0[NUM_PIXELS];
uint8_t led_buff_1[NUM_PIXELS];

uint8_t* led_should = led_buff_0;
uint8_t* led_was = led_buff_1;


void light_leds() {
  unsigned long start_millis = millis();
  while (millis() - start_millis < TRANSITION_TIME) {
    uint8_t curr_brightness_coeff = (millis() - start_millis) * 256 / TRANSITION_TIME;
    Serial.println(curr_brightness_coeff);
    for (int i = 0; i < NUM_PIXELS; i++) {
      uint32_t curr_color_coeff = curr_brightness_coeff * led_should[i] 
        + (256 - curr_brightness_coeff) * led_was[i];
      Serial.println(curr_color_coeff);
      pixels.setPixelColor(i, 
        (curr_color_coeff << 16) | 
        (curr_color_coeff << 8) | 
        (curr_color_coeff));
    }
    pixels.show();
  }
  for (int i = 0; i < NUM_PIXELS; i++) {
      pixels.setPixelColor(i, 0xffffff * led_should[i]);
  }
  pixels.show();
}

void do_hour_blink() {


}

void set_min_acc() {
  for(int i = 1; i <= rtc_time.min % 5; i++){
    led_should[109 + i] = 1;
  }
}



void set_es_ist() {
  led_should[0] = 1;
  led_should[1] = 1;
  led_should[2] = 1;
  led_should[3] = 1;
  led_should[4] = 1;
  led_should[5] = 1;
}

void nach(){
  led_should[40] = 1;
  led_should[41] = 1;
  led_should[42] = 1;
  led_should[43] = 1;
}
void vor(){
  led_should[33] = 1;
  led_should[34] = 1;
  led_should[35] = 1;
}
void halb(){
  led_should[44] = 1;
  led_should[45] = 1;
  led_should[46] = 1;
  led_should[47] = 1;
}
void uhr(){
  led_should[107] = 1;
  led_should[108] = 1;
  led_should[109] = 1;
}


// minutes
void minfuenf(){
  led_should[7] = 1;
  led_should[8] = 1;
  led_should[9] = 1;
  led_should[10] = 1;
}
void minzehn(){
  led_should[11] = 1;
  led_should[12] = 1;
  led_should[13] = 1;
  led_should[14] = 1;
}
void mindrei(){
  led_should[22] = 1;
  led_should[23] = 1;
  led_should[24] = 1;
  led_should[25] = 1;
}
void minviertel(){
  led_should[26] = 1;
  led_should[27] = 1;
  led_should[28] = 1;
  led_should[29] = 1;
  led_should[30] = 1;
  led_should[31] = 1;
  led_should[32] = 1;
}
void minzwanzig(){
  led_should[15] = 1;
  led_should[16] = 1;
  led_should[17] = 1;
  led_should[18] = 1;
  led_should[19] = 1;
  led_should[20] = 1;
  led_should[21] = 1;
}


// hours
void eins(){
  led_should[55] = 1;
  led_should[56] = 1;
  led_should[57] = 1;
  if(rtc_time.min >= 5){
    led_should[58] = 1;
  }
}
void zwei(){
  led_should[62] = 1;
  led_should[63] = 1;
  led_should[64] = 1;
  led_should[65] = 1;
}
void drei(){
  led_should[66] = 1;
  led_should[67] = 1;
  led_should[68] = 1;
  led_should[69] = 1;
}
void vier(){
  led_should[73] = 1;
  led_should[74] = 1;
  led_should[75] = 1;
  led_should[76] = 1;
}
void fuenf(){
  led_should[51] = 1;
  led_should[52] = 1;
  led_should[53] = 1;
  led_should[54] = 1;
}
void sechs(){
  led_should[77] = 1;
  led_should[78] = 1;
  led_should[79] = 1;
  led_should[80] = 1;
  led_should[81] = 1;
}
void sieben(){
  led_should[88] = 1;
  led_should[89] = 1;
  led_should[90] = 1;
  led_should[91] = 1;
  led_should[92] = 1;
  led_should[93] = 1;
}
void acht(){
  led_should[84] = 1;
  led_should[85] = 1;
  led_should[86] = 1;
  led_should[87] = 1;
}
void neun(){
  led_should[102] = 1;
  led_should[103] = 1;
  led_should[104] = 1;
  led_should[105] = 1;
}
void zehn(){
  led_should[99] = 1;
  led_should[100] = 1;
  led_should[101] = 1;
  led_should[102] = 1;
}
void elf(){
  led_should[49] = 1;
  led_should[50] = 1;
  led_should[51] = 1;
}
void zwoelf(){
  led_should[94] = 1;
  led_should[95] = 1;
  led_should[96] = 1;
  led_should[97] = 1;
  led_should[98] = 1;
}

void set_five_min_steps() {
  if(rtc_time.min < 5){      //weniger als 5 nach
    uhr();
  }
  if(rtc_time.min >= 5 && rtc_time.min < 10){     //fünf nach
     minfuenf();
     nach();
  }
  if(rtc_time.min >= 10 && rtc_time.min < 15){      //zehn nach
    minzehn();
    nach();
  }
  if(rtc_time.min >= 15 && rtc_time.min < 20){      //viertel nach
    minviertel();
    nach();
  }
  if(rtc_time.min >= 20 && rtc_time.min < 25){      //zwanzig nach
    minzwanzig();
    nach();
  }
  if(rtc_time.min >= 25 && rtc_time.min < 30){      //fünfundzwanzig nach
    minfuenf();
    vor();
    halb();
  }
  if(rtc_time.min >= 30 && rtc_time.min < 35){      //halb
    halb();
  }
  if(rtc_time.min >= 35 && rtc_time.min < 40){      //fünf nach halb
    minfuenf();
    nach();
    halb();
  }
  if(rtc_time.min >= 40 && rtc_time.min < 45){      //zwanzig vor
    minzwanzig();
    vor();
  }
  if(rtc_time.min >= 45 && rtc_time.min < 50){      //viertel vor
    mindrei();
    minviertel();
  }
  if(rtc_time.min >= 50 && rtc_time.min < 55){      //zehn vor
    minzehn();
    vor();
  }
  if(rtc_time.min >= 55 && rtc_time.min < 60){      //fünf vor
    minfuenf();
    vor();
  }
}

void set_hour() {
  switch (rtc_time.hour + ((rtc_time.min < 25) ? 0 : 1)) {
    case 1:
    case 13: eins();
    break;
    case 2:
    case 14: zwei();
    break;
    case 3:
    case 15: drei();
    break;
    case 4:
    case 16: vier();
    break;
    case 5:
    case 17: fuenf();
    break;
    case 6:
    case 18: sechs();
    break;
    case 7:
    case 19: sieben();
    break;
    case 8:
    case 20: acht();
    break;
    case 9:
    case 21: neun();
    break;
    case 10:
    case 22: zehn();
    break;
    case 11:
    case 23: elf();
    break;
    case 12:
    case 24:
    case 0: zwoelf();
    break;
  }
}


void set_leds() {
  set_es_ist();
  set_hour();
  set_five_min_steps();
  set_min_acc();
}

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN_POWER, OUTPUT);
  pinMode(LDR_PIN_VAL, INPUT);
  pinMode(BTN_PIN_POWER, OUTPUT);
  pinMode(BTN_PIN_1, INPUT);
  pinMode(BTN_PIN_2, INPUT);
  pinMode(BTN_PIN_3, INPUT);

  pixels.begin();
  rtc.begin();
  rtc_time = rtc.getTime();
  set_leds();
  light_leds();

  Serial.println("startup complete");
}

void loop() {
  Serial.println(rtc.getTimeStr(FORMAT_LONG));

  if (rtc_time.hour != rtc.getTime().hour) {
    rtc_time = rtc.getTime();
    do_hour_blink();
  } else if (rtc_time.min != rtc.getTime().min) {
    rtc_time = rtc.getTime();
    set_leds();
    light_leds();
    uint8_t* temp = led_was;
    led_was = led_should;
    led_should = temp;
    memset(led_should, 0, NUM_PIXELS);
  }

  delay(10000);
}
