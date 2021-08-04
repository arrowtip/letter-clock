#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif
#define PIN        6    // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 114     // How many NeoPixels are attached to the Arduino?
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include <DS3231.h>
DS3231 rtc(SDA, SCL);
Time t;

int r;
int g;
int b;

int i;

int a = 0;

void setup() {
  Serial.begin(9600);
  r = 50;
  g = 50;
  b = 50;
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  rtc.begin();

 
}

void loop() {
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" : ");
  Serial.println(t.min);
  

if(a == 0){
  pixels.setPixelColor(0, pixels.Color(r, g, b));     //"es ist"
  pixels.setPixelColor(1, pixels.Color(r, g, b));
  pixels.setPixelColor(3, pixels.Color(r, g, b));
  pixels.setPixelColor(4, pixels.Color(r, g, b));
  pixels.setPixelColor(5, pixels.Color(r, g, b));

  if(t.min < 25){
      if(t.hour == 1 || t.hour == 13){      //ein
        eins();
      }
      if(t.hour == 2 || t.hour == 14){      //zwei
        zwei();
      }
      if(t.hour == 3 || t.hour == 15){      //drei
        drei();
      }
       if(t.hour == 4 || t.hour == 16){      //vier
        vier();
      }
       if(t.hour == 5 || t.hour == 17){      //fünf
        fuenf();
      }
       if(t.hour == 6 || t.hour == 18){      //sechs
        sechs();
      }
      if(t.hour == 7 || t.hour == 19){      //sieben
        sieben();
      }
      if(t.hour == 8 || t.hour == 20){      //acht
        acht();
      }
      if(t.hour == 9 || t.hour == 21){      //neun
        neun();
      }
      if(t.hour == 10 || t.hour == 22){      //zehn
        zehn();
      }
      if(t.hour == 11 || t.hour == 23){      //elf
        elf();
      }
      if(t.hour == 12 || t.hour == 24){      //zwölf
        zwoelf();
      }
  }


if(t.min >= 25){
  if(t.hour == 12 || t.hour == 24){      //halb eins
        eins();
      }
      if(t.hour == 1 || t.hour == 13){      //halb zwei
        zwei();
      }
      if(t.hour == 2 || t.hour == 14){      //halb drei
        drei();
      }
       if(t.hour == 3 || t.hour == 15){      //halb vier
        vier();
      }
       if(t.hour == 4 || t.hour == 16){      //halb fünf
        fuenf();
      }
       if(t.hour == 5 || t.hour == 17){      //halb sechs
        sechs();
      }
      if(t.hour == 6 || t.hour == 18){      //halb sieben
        sieben();
      }
      if(t.hour == 7 || t.hour == 19){      //halb acht
        acht();
      }
      if(t.hour == 8 || t.hour == 20){      //halb neun
        neun();
      }
      if(t.hour == 9 || t.hour == 21){      //halb zehn
        zehn();
      }
      if(t.hour == 10 || t.hour == 22){      //halb elf
        elf();
      }
      if(t.hour == 11 || t.hour == 23){      //halb zwölf
        zwoelf();
      }
}



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

  for(i=1; i <= t.min%5; i++){      //minuten
    pixels.setPixelColor(109 + i, pixels.Color(r, g, b));
  }

  
  pixels.show();
  delay(20);
  pixels.clear();
}

else{
  dat_ten_neun();
  dat_one_neun();
  pixels.show();
  delay(1000);
  pixels.clear();
}
}

//////////////////////////////////////////////////////////////////////////////////
//prepos
void nach(){
  pixels.setPixelColor(40, pixels.Color(r, g, b));
  pixels.setPixelColor(41, pixels.Color(r, g, b));
  pixels.setPixelColor(42, pixels.Color(r, g, b));
  pixels.setPixelColor(43, pixels.Color(r, g, b));
}
void vor(){
  pixels.setPixelColor(33, pixels.Color(r, g, b));
  pixels.setPixelColor(34, pixels.Color(r, g, b));
  pixels.setPixelColor(35, pixels.Color(r, g, b));
}
void halb(){
  pixels.setPixelColor(44, pixels.Color(r, g, b));
  pixels.setPixelColor(45, pixels.Color(r, g, b));
  pixels.setPixelColor(46, pixels.Color(r, g, b));
  pixels.setPixelColor(47, pixels.Color(r, g, b));
}
void uhr(){
  pixels.setPixelColor(107, pixels.Color(r, g, b));
  pixels.setPixelColor(108, pixels.Color(r, g, b));
  pixels.setPixelColor(109, pixels.Color(r, g, b));
}


//minuten
void minfuenf(){
  pixels.setPixelColor(7, pixels.Color(r, g, b));
  pixels.setPixelColor(8, pixels.Color(r, g, b));
  pixels.setPixelColor(9, pixels.Color(r, g, b));
  pixels.setPixelColor(10, pixels.Color(r, g, b));
}
void minzehn(){
  pixels.setPixelColor(11, pixels.Color(r, g, b));
  pixels.setPixelColor(12, pixels.Color(r, g, b));
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
}
void mindrei(){
  pixels.setPixelColor(22, pixels.Color(r, g, b));
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(24, pixels.Color(r, g, b));
  pixels.setPixelColor(25, pixels.Color(r, g, b));
}
void minviertel(){
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(27, pixels.Color(r, g, b));
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(29, pixels.Color(r, g, b));
  pixels.setPixelColor(30, pixels.Color(r, g, b));
  pixels.setPixelColor(31, pixels.Color(r, g, b));
  pixels.setPixelColor(32, pixels.Color(r, g, b));
}
void minzwanzig(){
  pixels.setPixelColor(15, pixels.Color(r, g, b));
  pixels.setPixelColor(16, pixels.Color(r, g, b));
  pixels.setPixelColor(17, pixels.Color(r, g, b));
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(20, pixels.Color(r, g, b));
  pixels.setPixelColor(21, pixels.Color(r, g, b));
}


//stunden
void eins(){
  pixels.setPixelColor(55, pixels.Color(r, g, b));
  pixels.setPixelColor(56, pixels.Color(r, g, b));
  pixels.setPixelColor(57, pixels.Color(r, g, b));
  if(t.min >= 5){pixels.setPixelColor(58, pixels.Color(r, g, b));}
}
void zwei(){
  pixels.setPixelColor(62, pixels.Color(r, g, b));
  pixels.setPixelColor(63, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(65, pixels.Color(r, g, b));
}
void drei(){
  pixels.setPixelColor(66, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
  pixels.setPixelColor(68, pixels.Color(r, g, b));
  pixels.setPixelColor(69, pixels.Color(r, g, b));
}
void vier(){
  pixels.setPixelColor(73, pixels.Color(r, g, b));
  pixels.setPixelColor(74, pixels.Color(r, g, b));
  pixels.setPixelColor(75, pixels.Color(r, g, b));
  pixels.setPixelColor(76, pixels.Color(r, g, b));
}
void fuenf(){
  pixels.setPixelColor(51, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(53, pixels.Color(r, g, b));
  pixels.setPixelColor(54, pixels.Color(r, g, b));
}
void sechs(){
  pixels.setPixelColor(77, pixels.Color(r, g, b));
  pixels.setPixelColor(78, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
  pixels.setPixelColor(81, pixels.Color(r, g, b));
}
void sieben(){
  pixels.setPixelColor(88, pixels.Color(r, g, b));
  pixels.setPixelColor(89, pixels.Color(r, g, b));
  pixels.setPixelColor(90, pixels.Color(r, g, b));
  pixels.setPixelColor(91, pixels.Color(r, g, b));
  pixels.setPixelColor(92, pixels.Color(r, g, b));
  pixels.setPixelColor(93, pixels.Color(r, g, b));
}
void acht(){
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
  pixels.setPixelColor(86, pixels.Color(r, g, b));
  pixels.setPixelColor(87, pixels.Color(r, g, b));
}
void neun(){
  pixels.setPixelColor(102, pixels.Color(r, g, b));
  pixels.setPixelColor(103, pixels.Color(r, g, b));
  pixels.setPixelColor(104, pixels.Color(r, g, b));
  pixels.setPixelColor(105, pixels.Color(r, g, b));
}
void zehn(){
  pixels.setPixelColor(99, pixels.Color(r, g, b));
  pixels.setPixelColor(100, pixels.Color(r, g, b));
  pixels.setPixelColor(101, pixels.Color(r, g, b));
  pixels.setPixelColor(102, pixels.Color(r, g, b));
}
void elf(){
  pixels.setPixelColor(49, pixels.Color(r, g, b));
  pixels.setPixelColor(50, pixels.Color(r, g, b));
  pixels.setPixelColor(51, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
}
void zwoelf(){
  pixels.setPixelColor(94, pixels.Color(r, g, b));
  pixels.setPixelColor(95, pixels.Color(r, g, b));
  pixels.setPixelColor(96, pixels.Color(r, g, b));
  pixels.setPixelColor(97, pixels.Color(r, g, b));
  pixels.setPixelColor(98, pixels.Color(r, g, b));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//datum ten
void dat_ten_null(){
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(34, pixels.Color(r, g, b));
  pixels.setPixelColor(37, pixels.Color(r, g, b));
  pixels.setPixelColor(45, pixels.Color(r, g, b));
  pixels.setPixelColor(48, pixels.Color(r, g, b));
  pixels.setPixelColor(56, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
  pixels.setPixelColor(70, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
}
void dat_ten_eins(){
  pixels.setPixelColor(35, pixels.Color(r, g, b));
  pixels.setPixelColor(25, pixels.Color(r, g, b));
  pixels.setPixelColor(15, pixels.Color(r, g, b));
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(37, pixels.Color(r, g, b));
  pixels.setPixelColor(48, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(70, pixels.Color(r, g, b));
  pixels.setPixelColor(81, pixels.Color(r, g, b));
}
void dat_ten_zwei(){
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(37, pixels.Color(r, g, b));
  pixels.setPixelColor(47, pixels.Color(r, g, b));
  pixels.setPixelColor(57, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
  pixels.setPixelColor(78, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
  pixels.setPixelColor(81, pixels.Color(r, g, b));
}
void dat_ten_drei(){
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(37, pixels.Color(r, g, b));
  pixels.setPixelColor(47, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(70, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
}
void dat_ten_vier(){
  pixels.setPixelColor(15, pixels.Color(r, g, b));
  pixels.setPixelColor(25, pixels.Color(r, g, b));
  pixels.setPixelColor(35, pixels.Color(r, g, b));
  pixels.setPixelColor(45, pixels.Color(r, g, b));
  pixels.setPixelColor(56, pixels.Color(r, g, b));
  pixels.setPixelColor(57, pixels.Color(r, g, b));
  pixels.setPixelColor(58, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(47, pixels.Color(r, g, b));
  pixels.setPixelColor(69, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
}
void dat_ten_fuenf(){
  pixels.setPixelColor(12, pixels.Color(r, g, b));
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(15, pixels.Color(r, g, b));
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(34, pixels.Color(r, g, b));
  pixels.setPixelColor(35, pixels.Color(r, g, b));
  pixels.setPixelColor(36, pixels.Color(r, g, b));
  pixels.setPixelColor(48, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(70, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
}
void dat_ten_sechs(){
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(34, pixels.Color(r, g, b));
  pixels.setPixelColor(45, pixels.Color(r, g, b));
  pixels.setPixelColor(56, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
  pixels.setPixelColor(70, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(47, pixels.Color(r, g, b));
  pixels.setPixelColor(46, pixels.Color(r, g, b));
}
void dat_ten_sieben(){
  pixels.setPixelColor(12, pixels.Color(r, g, b));
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(15, pixels.Color(r, g, b));
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(36, pixels.Color(r, g, b));
  pixels.setPixelColor(46, pixels.Color(r, g, b));
  pixels.setPixelColor(57, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
  pixels.setPixelColor(78, pixels.Color(r, g, b));
}
void dat_ten_acht(){
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(34, pixels.Color(r, g, b));
  pixels.setPixelColor(37, pixels.Color(r, g, b));
  pixels.setPixelColor(46, pixels.Color(r, g, b));
  pixels.setPixelColor(47, pixels.Color(r, g, b));
  pixels.setPixelColor(56, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
  pixels.setPixelColor(70, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
}
void dat_ten_neun(){
  pixels.setPixelColor(13, pixels.Color(r, g, b));
  pixels.setPixelColor(14, pixels.Color(r, g, b));
  pixels.setPixelColor(23, pixels.Color(r, g, b));
  pixels.setPixelColor(26, pixels.Color(r, g, b));
  pixels.setPixelColor(34, pixels.Color(r, g, b));
  pixels.setPixelColor(37, pixels.Color(r, g, b));
  pixels.setPixelColor(46, pixels.Color(r, g, b));
  pixels.setPixelColor(47, pixels.Color(r, g, b));
  pixels.setPixelColor(48, pixels.Color(r, g, b));
  pixels.setPixelColor(59, pixels.Color(r, g, b));
  pixels.setPixelColor(70, pixels.Color(r, g, b));
  pixels.setPixelColor(80, pixels.Color(r, g, b));
  pixels.setPixelColor(79, pixels.Color(r, g, b));
  pixels.setPixelColor(67, pixels.Color(r, g, b));
}


//datum one
void dat_one_null(){
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(39, pixels.Color(r, g, b));
  pixels.setPixelColor(50, pixels.Color(r, g, b));
  pixels.setPixelColor(61, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
  pixels.setPixelColor(75, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(53, pixels.Color(r, g, b));
  pixels.setPixelColor(42, pixels.Color(r, g, b));
  pixels.setPixelColor(31, pixels.Color(r, g, b));
}
void dat_one_eins(){
  pixels.setPixelColor(39, pixels.Color(r, g, b));
  pixels.setPixelColor(29, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(30, pixels.Color(r, g, b));
  pixels.setPixelColor(41, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(63, pixels.Color(r, g, b));
  pixels.setPixelColor(74, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
}
void dat_one_zwei(){
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(31, pixels.Color(r, g, b));
  pixels.setPixelColor(42, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(62, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
  pixels.setPixelColor(83, pixels.Color(r, g, b));
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
  pixels.setPixelColor(86, pixels.Color(r, g, b));
}
void dat_one_drei(){
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(31, pixels.Color(r, g, b));
  pixels.setPixelColor(42, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(75, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
}
void dat_one_vier(){
  pixels.setPixelColor(20, pixels.Color(r, g, b));
  pixels.setPixelColor(30, pixels.Color(r, g, b));
  pixels.setPixelColor(40, pixels.Color(r, g, b));
  pixels.setPixelColor(50, pixels.Color(r, g, b));
  pixels.setPixelColor(61, pixels.Color(r, g, b));
  pixels.setPixelColor(62, pixels.Color(r, g, b));
  pixels.setPixelColor(63, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(74, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
}
void dat_one_fuenf(){
  pixels.setPixelColor(17, pixels.Color(r, g, b));
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(20, pixels.Color(r, g, b));
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(39, pixels.Color(r, g, b));
  pixels.setPixelColor(40, pixels.Color(r, g, b));
  pixels.setPixelColor(41, pixels.Color(r, g, b));
  pixels.setPixelColor(53, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(75, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
}
void dat_one_sechs(){
  pixels.setPixelColor(31, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(39, pixels.Color(r, g, b));
  pixels.setPixelColor(50, pixels.Color(r, g, b));
  pixels.setPixelColor(61, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
  pixels.setPixelColor(75, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(51, pixels.Color(r, g, b));
}
void dat_one_sieben(){
  pixels.setPixelColor(17, pixels.Color(r, g, b));
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(20, pixels.Color(r, g, b));
  pixels.setPixelColor(31, pixels.Color(r, g, b));
  pixels.setPixelColor(41, pixels.Color(r, g, b));
  pixels.setPixelColor(51, pixels.Color(r, g, b));
  pixels.setPixelColor(62, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
  pixels.setPixelColor(83, pixels.Color(r, g, b));
}
void dat_one_acht(){
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(31, pixels.Color(r, g, b));
  pixels.setPixelColor(39, pixels.Color(r, g, b));
  pixels.setPixelColor(42, pixels.Color(r, g, b));
  pixels.setPixelColor(51, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(61, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
  pixels.setPixelColor(75, pixels.Color(r, g, b));
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
}
void dat_one_neun(){
  pixels.setPixelColor(18, pixels.Color(r, g, b));
  pixels.setPixelColor(19, pixels.Color(r, g, b));
  pixels.setPixelColor(28, pixels.Color(r, g, b));
  pixels.setPixelColor(39, pixels.Color(r, g, b));
  pixels.setPixelColor(31, pixels.Color(r, g, b));
  pixels.setPixelColor(42, pixels.Color(r, g, b));
  pixels.setPixelColor(51, pixels.Color(r, g, b));
  pixels.setPixelColor(52, pixels.Color(r, g, b));
  pixels.setPixelColor(53, pixels.Color(r, g, b));
  pixels.setPixelColor(64, pixels.Color(r, g, b));
  pixels.setPixelColor(75, pixels.Color(r, g, b));
  pixels.setPixelColor(85, pixels.Color(r, g, b));
  pixels.setPixelColor(84, pixels.Color(r, g, b));
  pixels.setPixelColor(72, pixels.Color(r, g, b));
}
