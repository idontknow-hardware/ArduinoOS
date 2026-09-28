#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Keypad.h> //biblioteka od klawiatury
#include <Ds1302.h>
const unsigned char zegar[] PROGMEM = {
0xf8,0x1f,0x84,0x20,0x82,0x40,0x81,0x80,0x81,0x80,0x81,0x80,
 0x81,0x80,0x81,0xff,0x01,0x80,0x01,0x80,0x02,0x40,0xfc,0x3f,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
const unsigned char ustawienia[] PROGMEM = {
   0x0c,0x63,0x8c,0x73,0xff,0x3f,0x0f,0x30,0x07,0x20,0x07,0x60,
 0x04,0x40,0x0c,0x40,0x08,0x40,0x38,0x60,0xf8,0x7d,0x18,0xff,
 0x0c,0xf0,0x00,0x60,0x00,0x00,0x00,0x00
};
Ds1302 rtc(12, 10, 11);
const byte ROWS = 4; // ile wierszy
const byte COLS = 4; //ile kolumn
char i = ' ';
int8_t app = -1;
byte rowPins[ROWS] = {5, 4, 3, 2}; //piny wierszy
byte colPins[COLS] = {6, 7, 8, 9}; //piny kolum
char name[9];
int lcz = 0;
int liczbaart = 0;
char keys[ROWS][COLS] = { //mapowanie klawiatury
  {'A','3','2','1'},
  {'B','6','5','4'},
  {'C','9','8','7'},
  {'D','#','0','*'}
};
uint8_t op = 0;
uint8_t X = 0;
uint8_t Y = 0;
uint8_t xk = 0;
uint8_t yk = 0;
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
bool s = 0;
int str = 0;
bool t = 0;
void setup() {
  pinMode(A0, OUTPUT);
  Serial.begin(9600);
  rtc.init();
  Ds1302::DateTime now;
  rtc.getDateTime(&now);
  Serial.println(now.hour);
  for (int i = 0; i < 9; i++) {
    name[i] = EEPROM.read(i + 3);
  }
u8g2.begin(); 
bool check;
uint8_t free; 
for (int iu = 0; iu < 5; iu++) {
  u8g2.firstPage();
 do {
    u8g2.setFont(u8g2_font_9x15_tf);       
    u8g2.setCursor(32, 32);  
    print(F("WITAM"), F("WELCOME"));
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawFrame(32, 55, 64, 5);

 
    if (op == 0) { 
    for (int ip = 0; ip < 9; ip++) {
      u8g2.setCursor(ip * 6 + 32, 50);
       printo(name[ip]);
    }}if (op == 1) {
      u8g2.setCursor(0, 50);
      print(F("sprawdzanie danych..."), F("checking data..."));
      u8g2.drawBox(0, 55, 12, 5);
      printo(check);
    }if (op == 2) {
      u8g2.setCursor(0, 50);
      print(F("Wolne pliki..."), F("Free Files..."));
      u8g2.drawBox(32, 55, 24, 5);
      printo(free);
    }if (op == 3) {
          u8g2.setCursor(0, 50);
      print(F("I/O: keypad"), F("I/O: keypad"));
      u8g2.drawBox(32, 55, 64, 5);
    }                 
  } while ( u8g2.nextPage() );
  delay(3000);
  Serial.println(op);
  op++;
  if (op == 1) {
    check = Check();
  }
  if (op == 2) {
    free = FreeFiles();
  }if (op == 3) {

  }
  }

}

void loop() {
  u8g2.firstPage();
  do {
    if (app > -1) {
      runAppScreen(app);
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
      u8g2.drawButtonUTF8(30, 40, U8G2_BTN_BW1, 0, 1, 1, "NEXT");
    }if (str == 1) {
      u8g2.setCursor(10, 15);
      u8g2.setFont(u8g2_font_6x10_tr);
      print(F("KONFIGURACJA(1/5)"), F("CONFIG(1/5)"));
      u8g2.setFont(u8g2_font_5x7_tr);
      u8g2.setCursor(0, 30);
      print(F("Prosze wybrac jezyk"), F("Please choose language"));
      u8g2.drawButtonUTF8(30, 40, U8G2_BTN_BW1, 0, 1, 1, "PL");
      u8g2.drawButtonUTF8(60, 40, U8G2_BTN_BW1, 0, 1, 1, "EN");
      u8g2.drawButtonUTF8(60, 60, U8G2_BTN_BW1, 0, 1, 1, "NEXT");
    }if (str == 2) {
      u8g2.setCursor(10, 15);
      u8g2.setFont(u8g2_font_6x10_tr);
      print(F("KONFIGURACJA(2/5)"), F("CONFIG(2/5)"));  
      u8g2.setFont(u8g2_font_5x7_tr);
      u8g2.setCursor(0, 30);
      printo(F("EEPROM"));
      DrawButtonLang(30, 40, 0, 1, 1, "WYCZYSC EEPROM", "ERASE EEPROM");
      u8g2.setCursor(0, 50);
      print(F("UWAGA! JESLI WYBIERZESZ"), F("WARNING! If you select"));
      u8g2.setCursor(0, 57);
      print(F("TA OPCJE CALY EEPROM"), F("this option, the entire EEPROM"));
      u8g2.setCursor(0, 64);
      print(F("ZOSTANIE WYKASOWANY!"), F("will be erased!"));
    }if (str == 3) {
      u8g2.setCursor(10, 10);
      u8g2.setFont(u8g2_font_6x10_tr);
      print(F("KONFIGURACJA(3/5)"), F("CONFIG(3/5)"));  
      u8g2.setFont(u8g2_font_5x7_tr);
      u8g2.setCursor(0, 20);
      print(F("Nazwa użytkownika:"), F("User name:"));      
      Keyboard(i);
        for (uint8_t id = 0; id < 8; id++) {
          u8g2.setCursor(id * 6 + 85, 20);
          u8g2.setFont(u8g2_font_5x7_tr);
          printo(name[id]);
        }
    }if (str == 4) {
      u8g2.setCursor(10, 10);
      u8g2.setFont(u8g2_font_6x10_tr);
      print(F("KONFIGURACJA(4/5)"), F("CONFIG(4/5)"));  
      u8g2.setFont(u8g2_font_5x7_tr);
      u8g2.setCursor(0, 20);
      printo(F("Admin"));
      u8g2.drawButtonUTF8(30, 40, U8G2_BTN_BW1, 0, 1, 1, "ON");
      u8g2.drawButtonUTF8(60, 40, U8G2_BTN_BW1, 0, 1, 1, "OFF");
      u8g2.drawButtonUTF8(60, 60, U8G2_BTN_BW1, 0, 1, 1, "NEXT");
    }if (str == 5) {
      u8g2.setCursor(10, 10);
      u8g2.setFont(u8g2_font_6x10_tr);
      print(F("KONFIGURACJA(5/5)"), F("CONFIG(5/5)"));  
      u8g2.setFont(u8g2_font_5x7_tr);
      u8g2.setCursor(0, 20);
      print(F("Koniec konfiguracji"), F("End of config"));     
    }}else {
      if (app == -1) {
  u8g2.drawXBMP(16, 16, 16, 16, zegar);
  u8g2.setCursor(16, 36);
  print(AppNamePL(0), AppNameEN(0));
  u8g2.drawXBMP(40, 16, 16, 16, ustawienia);
  u8g2.setCursor(40, 40);
  print(AppNamePL(1), AppNameEN(1));
      }
    }
        if (app == -1) {
      DrawMouse();
    }
    
    for (int a = 0; a < liczbaart; a++) {
     u8g2.drawPixel(random(128), random(64));
     u8g2.drawDisc(random(128), random(64), random(10), random(10));
     u8g2.drawBox(random(128), random(64), random(30), random(30));
    }
  } while ( u8g2.nextPage() );
  i = input();
  Serial.println(i);
  Serial.println(str);
  if(i == '0') {
    if (t == 0) {
    t = changeMouse();}
    Serial.print(t);
  } if (t == 1) {
    moveMouse(i);
    X = GetMouseX();
    Y = GetMouseY();
    Serial.print(F("X: "));
    Serial.println(X);
    Serial.print(F("Y: "));
    Serial.println(Y);
  }   
  bool check = Check();
  if (check == 1) {
  s = 1;}
  if (s == 1) {
    if (str == 0) {
    if (X > 30 and Y > 29 and X < 50 and Y < 42) {
      if (i == '5') {
      str = 1;}}
    }if (str == 1) {
      if (X > 29 and Y > 30 and X < 39 and Y < 43) {
        if (i == '5') {
          SetLanguage(0);
        }
      }
      if (X > 57 and Y > 32 and X < 69 and Y < 43) {
        if (i == '5') {
          SetLanguage(1);
        }
      }
      if (X > 58 and Y > 51 and X < 79 and Y < 61) {
        if (i == '5') {
          str = 2;
        }
      }
    }if (str == 2) {
      if (X > 29 and Y > 32 and X < 99 and Y < 41) {
        if (i == '5') {
          ClearEEPROM();
          for (int i = 64; i < EEPROM.length(); i = i + 81) {
            for (int i_P = 0; i_P < 80; i_P++) {
              if (i_P == 0) {
                EEPROM.update(i + i_P, 1);
              }
            }
          }
  for(int i = 0; i < EEPROM.length(); i++) {
    Serial.print(i);
    Serial.print(" ");
    Serial.print(EEPROM.read(i));
    Serial.println("");
  }
          str = 3;
        }
      }
      }if (str == 3) {
        if (lcz > 8) {
          str = 4;
        }
        char l = getKeyboard();
        if (i == '5') {
          if (l != 0) {
          name[lcz] = l;
          Serial.println(name[lcz]);
          lcz++;

        }}
      }if (str == 4) {
        if (X > 29 and Y > 30 and X < 39 and Y < 43) {
        if (i == '5') {
          SetAdmin(1);
        }
      }
      if (X > 58 and Y > 32 and X < 75 and Y < 42) {
      if (i == '5') {
        SetAdmin(0);}
      }
      if (X > 58 and Y > 51 and X < 79 and Y < 61) {
        if (i == '5') {
          str = 5;
        }
      }      
      }if (str == 5) {
        WriteAll();
        delay(3000);
        s = 0;
      }
    }else {
      if (X > 16 and Y > 16 and X < 30 and Y < 28) {
      if (i == '5') {
        app = 0;
      }}
      if (X > 43 and Y > 16 and X < 55 and Y < 30) {
        if (i == '5') {
          app = 1;
        }
      }
              
      if (app > -1) {
          runApp(app);
          if (i == '*') {
            app = -1;
          }
      }
    }
  }
