#include "src/DS3231/DS3231.h"     //http://rinkydinkelectronics.com/library.php?id=73
#include <Adafruit_NeoPixel.h>

#define PIN 2    // Which pin on the Arduino is connected to the NeoPixels?
#define SENSOR_POWER 13
#define SENSOR_VAL A0
#define NUMPIXELS 114     // How many NeoPixels are attached to the Arduino?

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
DS3231 rtc(SDA, SCL);
Time t;

struct Brightness {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};
Brightness led_brightness;

const int fromSensor = 40;
const int toSensor = 900;
const int fromBrightness = 10;
const int toBrightness = 200;
unsigned long millisTime = 0;
int currentBrightness = 200;
unsigned char hour_blinked; // last hour that activated the bell

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(A1, INPUT);
  led_brightness.r = 255;
  led_brightness.g = 255;
  led_brightness.b = 180;
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  rtc.begin();

  digitalWrite(SENSOR_POWER, HIGH);
  // currentBrightness = map(analogRead(SENSOR_VAL), fromSensor, toSensor, fromBrightness, toBrightness);
  digitalWrite(SENSOR_POWER, LOW);
  pixels.setBrightness(currentBrightness);
 
  currentBrightness = 200;
  Serial.println("startup complete");
}

void loop() {
  Serial.println("loop start");
  t = rtc.getTime();
  Serial.println("time read");
  Serial.print(t.hour);
  Serial.print(" : ");
  Serial.println(t.min);
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  
  pixels.setPixelColor(0, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));     //"es ist"
  pixels.setPixelColor(1, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(3, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(4, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(5, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));

  show_hour();
  show_five_min_steps();
  show_min_acc();

  if (millis() - millisTime >= 1000) {
    digitalWrite(SENSOR_POWER, HIGH);
    millisTime = millis();
    // currentBrightness = map(analogRead(SENSOR_VAL), fromSensor, toSensor, fromBrightness, toBrightness);
    pixels.setBrightness(currentBrightness);
    Serial.print("brightness: ");
    Serial.println(currentBrightness);
    digitalWrite(13, SENSOR_POWER);
  }

  
  pixels.show();
  delay(20);
  pixels.clear();

}

//////////////////////////////////////////////////////////////////////////////////

void show_min_acc() {
  for(int i = 1; i <= t.min % 5; i++){      //minuten
    pixels.setPixelColor(109 + i, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  }
}

void show_five_min_steps() {
  if(t.min < 5){      //weniger als 5 nach
    uhr();
  }
  if(t.min >= 5 && t.min < 10){     //fünf nach
     minfuenf();
     nach();
  }
  if(t.min >= 10 && t.min < 15){      //zehn nach
    minzehn();
    nach();
  }
  if(t.min >= 15 && t.min < 20){      //viertel nach
    minviertel();
    nach();
  }
  if(t.min >= 20 && t.min < 25){      //zwanzig nach
    minzwanzig();
    nach();
  }
  if(t.min >= 25 && t.min < 30){      //fünfundzwanzig nach
    minfuenf();
    vor();
    halb();
  }
  if(t.min >= 30 && t.min < 35){      //halb
    halb();
  }
  if(t.min >= 35 && t.min < 40){      //fünf nach halb
    minfuenf();
    nach();
    halb();
  }
  if(t.min >= 40 && t.min < 45){      //zwanzig vor
    minzwanzig();
    vor();
  }
  if(t.min >= 45 && t.min < 50){      //viertel vor
    mindrei();
    minviertel();
  }
  if(t.min >= 50 && t.min < 55){      //zehn vor
    minzehn();
    vor();
  }
  if(t.min >= 55 && t.min < 60){      //fünf vor
    minfuenf();
    vor();
  }

}
void show_hour() {
  switch (t.hour + ((t.min < 25) ? 0 : 1)) {
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
//prepos
void nach(){
  pixels.setPixelColor(40, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(41, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(42, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(43, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void vor(){
  pixels.setPixelColor(33, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(34, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(35, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void halb(){
  pixels.setPixelColor(44, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(45, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(46, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(47, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void uhr(){
  pixels.setPixelColor(107, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(108, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(109, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}


//minuten
void minfuenf(){
  pixels.setPixelColor(7, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(8, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(9, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(10, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void minzehn(){
  pixels.setPixelColor(11, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(12, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(13, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(14, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void mindrei(){
  pixels.setPixelColor(22, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(23, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(24, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(25, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void minviertel(){
  pixels.setPixelColor(26, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(27, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(29, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(30, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(32, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void minzwanzig(){
  pixels.setPixelColor(15, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(16, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(17, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(20, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(21, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}


//stunden
void eins(){
  pixels.setPixelColor(55, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(56, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(57, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  if(t.min >= 5){pixels.setPixelColor(58, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));}
}
void zwei(){
  pixels.setPixelColor(62, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(63, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(65, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void drei(){
  pixels.setPixelColor(66, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(67, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(68, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(69, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void vier(){
  pixels.setPixelColor(73, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(74, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(75, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(76, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void fuenf(){
  pixels.setPixelColor(51, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(53, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(54, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void sechs(){
  pixels.setPixelColor(77, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(78, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(79, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(80, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(81, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void sieben(){
  pixels.setPixelColor(88, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(89, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(90, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(91, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(92, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(93, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void acht(){
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(86, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(87, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void neun(){
  pixels.setPixelColor(102, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(103, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(104, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(105, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void zehn(){
  pixels.setPixelColor(99, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(100, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(101, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(102, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void elf(){
  pixels.setPixelColor(49, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(50, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(51, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void zwoelf(){
  pixels.setPixelColor(94, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(95, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(96, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(97, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(98, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//datum ten
void dat_ten_null(){
  pixels.setPixelColor(13, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(14, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(23, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(26, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(34, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(37, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(45, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(48, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(56, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(59, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(67, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(70, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(79, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(80, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_ten_eins(){
  pixels.setPixelColor(35, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(25, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(15, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(26, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(37, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(48, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(59, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(70, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(81, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_ten_zwei(){
  pixels.setPixelColor(23, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(13, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(14, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(26, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(37, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(47, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(57, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(67, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(78, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(79, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(80, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(81, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_ten_drei(){
  pixels.setPixelColor(23, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(13, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(14, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(26, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(37, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(47, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(59, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(70, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(80, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(79, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(67, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}


//datum one
void dat_one_null(){
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(39, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(50, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(61, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(75, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(53, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(42, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_eins(){
  pixels.setPixelColor(39, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(29, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(30, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(41, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(63, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(74, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_zwei(){
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(42, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(62, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(83, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(86, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_drei(){
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(42, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(75, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_vier(){
  pixels.setPixelColor(20, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(30, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(40, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(50, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(61, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(62, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(63, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(74, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_fuenf(){
  pixels.setPixelColor(17, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(20, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(39, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(40, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(41, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(53, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(75, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_sechs(){
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(39, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(50, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(61, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(75, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(51, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_sieben(){
  pixels.setPixelColor(17, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(20, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(41, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(51, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(62, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(83, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_acht(){
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(39, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(42, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(51, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(61, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(75, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
void dat_one_neun(){
  pixels.setPixelColor(18, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(19, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(28, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(39, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(31, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(42, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(51, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(52, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(53, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(64, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(75, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(85, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(84, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
  pixels.setPixelColor(72, pixels.Color(led_brightness.r, led_brightness.g, led_brightness.b));
}
