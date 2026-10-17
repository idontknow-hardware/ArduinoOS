#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Ds1302.h>
void Clock(); 
void ClockScreen(); 
void Sett(); void SettScreen(); 
void Dino(); void DinoScreen(); 
void Przeg(); 
void PrzegScreen(); 
void Not(); 
void NotScreen(); 
const unsigned char zegar[] PROGMEM = {0xf8,0x1f,0x84,0x20,0x82,0x40,0x81,0x80,0x81,0x80,0x81,0x80, 0x81,0x80,0x81,0xff,0x01,0x80,0x01,0x80,0x02,0x40,0xfc,0x3f, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; const unsigned char ustawienia[] PROGMEM = { 0x0c,0x63,0x8c,0x73,0xff,0x3f,0x0f,0x30,0x07,0x20,0x07,0x60, 0x04,0x40,0x0c,0x40,0x08,0x40,0x38,0x60,0xf8,0x7d,0x18,0xff, 0x0c,0xf0,0x00,0x60,0x00,0x00,0x00,0x00}; 
const unsigned char dinozaur[] PROGMEM = { 0x7c,0x00,0xc4,0x00,0x94,0x00,0xc4,0x00,0x7c,0x00,0x3c,0x0c, 0xe4,0x0c,0xa4,0x8c,0x24,0xcc,0xe4,0x6c,0xa4,0x3e,0x3c,0x0c, 0x24,0x0c,0x24,0x0c,0x24,0x0c,0x6c,0x0c}; 
const unsigned char przegladarka[] PROGMEM = { 0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x00,0x11,0x00,0xf1,0x1f, 0x81,0x18,0x81,0x18,0x81,0x19,0xc1,0x1e,0x31,0x10,0x19,0x10, 0x01,0x10,0xff,0x1f,0x00,0x00,0x00,0x00}; 
const unsigned char notatnik[] PROGMEM = { 0xc0,0x01,0xf8,0x1f,0xcc,0x31,0xc4,0x21,0xc4,0x21,0x84,0x20, 0xfc,0x3f,0x04,0x20,0xcc,0x39,0x74,0x2e,0x04,0x20,0x7c,0x3e, 0xc4,0x23,0xfc,0x2d,0x0c,0x33,0xfc,0x3f}; 
Ds1302 rtc(12, 10, 11); 
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 
#include "defines.h"
char i = ' '; 
int8_t app = -1; 
char name[9]; 
uint8_t lcz = 0; 
uint8_t liczbaart = 0; 
uint8_t op = 0; 
uint8_t X = 0; 
uint8_t Y = 0; 
uint8_t xk = 0; 
uint8_t yk = 0; 
bool s = 0; 
uint8_t str = 0; 
bool t = 0; 
bool swiatlo = 0;
unsigned long ostatniRuchMyszy = 0;
struct App {
  char namePL[24]; 
  char nameEN[24]; 
  void (*run)();
  void (*screen)();
  const uint8_t *icon;
};

const App apps[] PROGMEM = {
  { "Zegar",      "Clock",    Clock, ClockScreen, zegar       },
  { "Ustawienia", "Settings", Sett,  SettScreen,  ustawienia  },
  { "Dinozaur",   "Dinosaur", Dino,  DinoScreen,  dinozaur    },
  { "Przegladarka plikow", "File explorer", Przeg, PrzegScreen, przegladarka},
  { "Notatnik",   "Notes",    Not,   NotScreen,   notatnik    }
};
const uint8_t APP_COUNT = sizeof(apps) / sizeof(apps[0]);
 

uint8_t selApp = 0; 
void DrawLauncher() {

  const uint8_t *iconPtr = (const uint8_t *)pgm_read_ptr(&(apps[selApp].icon));
  if (iconPtr) u8g2.drawXBMP(56, 10, 16, 16, iconPtr);

  u8g2.setFont(u8g2_font_6x10_tr);
  

  const char *nmPtr = (jezyk == 0) ? apps[selApp].namePL : apps[selApp].nameEN;


  u8g2.setCursor(16 , 40);
  

  u8g2.print((const __FlashStringHelper *)nmPtr);

  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setCursor(60, 60);
  printo((unsigned)(selApp + 1));
  printo('/');
  printo((unsigned)APP_COUNT);

  DrawButton(2, 30, 9, "<");
  DrawButton(120, 30, 9, ">");
}





void setup() {
UpdatePort();
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
  Serial.begin(9600); 
  rtc.init(); 
  Ds1302::DateTime now; 
  rtc.getDateTime(&now); 
  DEBUG_PRINTLN(now.hour); 
  for (int i = 0;  i < 9;  i++) {
    name[i] = EEPROM.read(i + 3); 
  }
  u8g2.begin();  
  bool check; 
  uint8_t free;  
  for (int iu = 0;  iu < 5;  iu++) {
    u8g2.firstPage(); 
    do {
      u8g2.setFont(u8g2_font_9x15_tr);        
      u8g2.setCursor(32, 32);   
      print(F("WITAM"), F("WELCOME")); 
      u8g2.setFont(u8g2_font_5x7_tr); 
      u8g2.drawFrame(32, 55, 64, 5); 

 
      if (op == 0) { 
        for (int ip = 0;  ip < 9;  ip++) {
          u8g2.setCursor(ip * 6 + 32, 50); 
         printo(name[ip]); 
        }
      }
      if (op == 1) {
        u8g2.setCursor(0, 50); 
        print(F("sprawdzanie danych..."), F("checking data...")); 
        u8g2.drawBox(0, 55, 12, 5); 
        printo(check); 
      }
      if (op == 2) {
        u8g2.setCursor(0, 50); 
        print(F("Wolne pliki..."), F("Free Files...")); 
        u8g2.drawBox(32, 55, 24, 5); 
        printo(free); 
      }
      if (op == 3) {
        u8g2.setCursor(0, 50); 
        print(F("I/O: keypad"), F("I/O: keypad")); 
        u8g2.drawBox(32, 55, 64, 5); 
      }                 
    } 
    while (u8g2.nextPage()); 
    delay(3000); 
    DEBUG_PRINTLN(op); 
    op++; 
    if (op == 1) {
      check = Check(); 
      RGB(0, 0, 1);
    }
    if (op == 2) {
      free = FreeFiles();
      RGB(0, 1, 0); 
    }
    if (op == 3) {
      RGB(1, 0, 0);
    }
  }
  RGB(0, 0, 0);
}

void loop() {
  u8g2.firstPage(); 
  do {
if (app > -1) {

  void (*screenFunc)() = (void (*)())pgm_read_ptr(&(apps[app].screen));
  if (screenFunc) screenFunc();
}
    if (s == 1) {
      if (str == 0) {
        u8g2.setCursor(10, 15); 
        u8g2.setFont(u8g2_font_6x10_tr); 
        printo(F("CONFIG(0/5)")); 
        u8g2.setCursor(0, 46); 
        u8g2.setFont(u8g2_font_5x7_tr); 
        printo(F("Use '0' to activate mouse")); 
        u8g2.setCursor(0, 53); 
        printo(F("mode on keypad, then move")); 
        u8g2.setCursor(0, 60); 
        printo(F("mouse (circle) to button")); 
        u8g2.setCursor(0, 67); 
        printo(F("'NEXT'")); 
        DrawButton(30, 40, 9, "NEXT"); 
      }
      if (str == 1) {
        u8g2.setCursor(10, 15); 
        u8g2.setFont(u8g2_font_6x10_tr); 
        print(F("KONFIGURACJA(1/5)"), F("CONFIG(1/5)")); 
        u8g2.setFont(u8g2_font_5x7_tr); 
        u8g2.setCursor(0, 30); 
        print(F("Prosze wybrac jezyk"), F("Please choose language")); 
        DrawButton(30, 40, 9, "PL"); 
        DrawButton(60, 40, 9, "EN"); 
        DrawButton(60, 60, 9,  "NEXT"); 
      }
      if (str == 2) {
        u8g2.setCursor(10, 15); 
        u8g2.setFont(u8g2_font_6x10_tr); 
        print(F("KONFIGURACJA(2/5)"), F("CONFIG(2/5)"));   
        u8g2.setFont(u8g2_font_5x7_tr); 
        u8g2.setCursor(0, 30); 
        printo(F("EEPROM")); 
        DrawButtonLang(30, 40, 9, "WYCZYSC EEPROM", "ERASE EEPROM"); 
        u8g2.setCursor(0, 50); 
        print(F("UWAGA! JESLI WYBIERZESZ"), F("WARNING! If you select")); 
        u8g2.setCursor(0, 57); 
        print(F("TA OPCJE CALY EEPROM"), F("this option, the entire EEPROM")); 
        u8g2.setCursor(0, 64); 
        print(F("ZOSTANIE WYKASOWANY!"), F("will be erased!")); 
      }
      if (str == 3) {
        u8g2.setCursor(10, 10); 
        u8g2.setFont(u8g2_font_6x10_tr); 
        print(F("KONFIGURACJA(3/5)"), F("CONFIG(3/5)"));   
        u8g2.setFont(u8g2_font_5x7_tr); 
        u8g2.setCursor(0, 20); 
        print(F("Nazwa użytkownika:"), F("User name:"));       
        Keyboard(i); 
          for (uint8_t id = 0;  id < 8;  id++) {
            u8g2.setCursor(id * 6 + 85, 20); 
            u8g2.setFont(u8g2_font_5x7_tr); 
            printo(name[id]); 
          }
      }
      if (str == 4) {
        u8g2.setCursor(10, 10); 
        u8g2.setFont(u8g2_font_6x10_tr); 
        print(F("KONFIGURACJA(4/5)"), F("CONFIG(4/5)"));   
        u8g2.setFont(u8g2_font_5x7_tr); 
        u8g2.setCursor(0, 20); 
        printo(F("Admin")); 
        DrawButton(30, 40, 9,  "ON"); 
        DrawButton(60, 40, 9,  "OFF"); 
        DrawButton(60, 60, 9, "NEXT"); 
      }
      if (str == 5) {
        u8g2.setCursor(10, 10); 
        u8g2.setFont(u8g2_font_6x10_tr); 
        print(F("KONFIGURACJA(5/5)"), F("CONFIG(5/5)"));   
        u8g2.setFont(u8g2_font_5x7_tr); 
        u8g2.setCursor(0, 20); 
        print(F("Koniec konfiguracji"), F("End of config"));      
      }
    } else {
      if (app == -1) {
        DrawLauncher(); 
      }
    }
    if (app == -1) {
      DrawMouse(); 
    }
    
    for (int a = 0;  a < liczbaart;  a++) {
     u8g2.drawPixel(random(128), random(64)); 
     u8g2.drawDisc(random(128), random(64), random(10), random(10)); 
     u8g2.drawBox(random(128), random(64), random(30), random(30)); 
    }
  } 
  while (u8g2.nextPage()); 
  i = input(); 
  DEBUG_PRINTLN(i); 
  DEBUG_PRINTLN(str); 
  if(i == '0') {
    if (t == 0) {
      t = changeMouse(); 
    }
    DEBUG_PRINT(t); 
  }     if (millis() - ostatniRuchMyszy >= 20UL) {
      ostatniRuchMyszy = millis();
      moveMouse(i);
      X = GetMouseX();
      Y = GetMouseY();
      Serial.println("X: ");
      Serial.print(X);
      Serial.println("Y: ");
      Serial.print(Y);
    }  
  if (Check() == 1) {
    s = 1; 
  }
  if (s == 1) {
    if (str == 0) {
      if (X > 30 && Y > 29 && X < 50 && Y < 42) {
        if (i == '5') {
          str = 1; 
        }
      }
    }
    if (str == 1) {
      if (X > 29 && Y > 30 && X < 39 && Y < 43) {
        if (i == '5') {
          SetLanguage(0); 
        }
      }
      if (X > 57 && Y > 32 && X < 69 && Y < 43) {
        if (i == '5') {
          SetLanguage(1); 
        }
      }
      if (X > 58 && Y > 51 && X < 79 && Y < 61) {
        if (i == '5') {
          str = 2; 
        }
      }
    }
    if (str == 2) {
      if (X > 29  &&  Y > 32  &&  X < 99  &&  Y < 41) {
        if (i == '5') {
          ClearEEPROM(); 
          for (int address = StartFile;  address < EEPROM.length();  address += FileLength) {
            EEPROM.update(address, 1);  
          }
          str = 3; 
        }
      }
    }
    if (str == 3) {
        if (lcz > 8) {
          str = 4; 
        }
        char l = getKeyboard(); 
        if (i == '5') {
          if (l != 0) {
          name[lcz] = l; 
          DEBUG_PRINTLN(name[lcz]); 
          lcz++; 

        }}
    }
    if (str == 4) {
      if (X > 29 && Y > 30 && X < 39 && Y < 43) {
        if (i == '5') {
          SetAdmin(1); 
        }
      }
      if (X > 58 && Y > 32 && X < 75 && Y < 42) {
        if (i == '5') {
          SetAdmin(0); 
        }
      }
      if (X > 58 && Y > 51 && X < 79 && Y < 61) {
        if (i == '5') {
          str = 5; 
        }
      }      
    }
    if (str == 5) {
      WriteAll(); 
      delay(3000); 
      s = 0; 
    }
  } else {
    if (swiatlo) {
      RGB(0, 1, 0);
    }else {
      RGB(0, 0, 0);
    }
    if (urz == PORT_DISTANCE) {
      if (millis() - OstatniPomiar > 250UL) {
        OstatniPomiar = millis();
    uint16_t obecnaOdleglosc = ReadDistance();
        if (distMode == DIST_MODE_SAVER) {
          if (obecnaOdleglosc > 150) {
            u8g2.setPowerSave(1);
          }else {
            u8g2.setPowerSave(0);
          }
        }else {
          if (obecnaOdleglosc > 3 and obecnaOdleglosc < 13) {
            i = 'B';
          }if (obecnaOdleglosc > 16 and obecnaOdleglosc < 23) {
            i = '5';
          }if (obecnaOdleglosc > 27 and obecnaOdleglosc < 40) {
            i = 'C';
          }
        }
      }
    }
    if (app == -1) {
      if (i == 'B') {
        selApp = (selApp + APP_COUNT - 1) % APP_COUNT; 
      }
      if (i == 'C') {
        selApp = (selApp + 1) % APP_COUNT; 
      }
        if (i == 'A') {
          swiatlo = !swiatlo;
          delay(50);
        }
      if (i == '5') {
        app = selApp; 
      }
    }
    if (app > -1) {
  void (*runFunc)() = (void (*)())pgm_read_ptr(&(apps[app].run));
  if (runFunc) runFunc(); 
 
      if (i == '*') {
        app = -1; 
      }
    }
  }
}