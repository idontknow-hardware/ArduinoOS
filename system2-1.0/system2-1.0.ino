#define DECODE_NEC 1
#define EXCLUDE_UNIVERSAL_PROTOCOLS 1
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <IRremote.h>
 #include <Ds1302.h>
#define IR_RECEIVE_PIN 2 // Pin, do którego podpięty jest sygnał
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
int jezyk = EEPROM.read(1); // język
int x = 0;
int y = 0;
int y_d = 3;
int x_k = 0;
int kursor_y = 0;
int wynik = 0;
int konfig = EEPROM.read(0);
int strona = 0;
int poz_u = 0;
int s_keyboard = 0;
int i_k = 0;
int s_ust = 0;
int s_info = 0;
int ulubione1 = EEPROM.read(3);
int ulubione2 = EEPROM.read(4);
bool edycja = 0;
bool keyboard = 0;
int aplikacje[] = {};
int poprawne = EEPROM.read(2);
const int RST_PIN = 4;
const int DAT_PIN = 3;
const int CLK_PIN = 5;
long czas = 0;
long roznicaCzasu = 0;
long ostatniCzas = 0;
long czas2 = 0;
long roznicaCzasu2 = 0;
long ostatniCzas2 = 0;
long czas3 = 0;
long roznicaCzasu3 = 0;
long ostatniCzas3 = 0;
byte godzina = 0;
byte minuta = 0;
byte dzien = 1;
byte miesiac = 1;
byte rok = 0;
uint8_t dino[8] = {0xC, 0xF, 0xC, 0xF, 0x1E, 0x1F, 0xA, 0xA};
uint8_t kaktus[8] = {0x4, 0x4, 0x5, 0x16, 0xC, 0x5, 0x6, 0x4};
LiquidCrystal_I2C lcd(0x27,16,2);
Ds1302 rtc(RST_PIN, CLK_PIN, DAT_PIN);
LiquidCrystal_I2C lcd2(0x26,16,2);
void print(String pl, String en) {
  if(y < 2){ // jeżeli y < 2, to wtedy ekran1 w przeciwnym wypdaku ekran2
  if(jezyk == 0){
  lcd.print(pl);}else {
    lcd.print(en);
  }}else{
  if(jezyk == 0){
  lcd2.print(pl);}else {
    lcd2.print(en);   
  }
  
}}
void print_o(String napis) {
  if(y < 2){ // jeżeli y < 2, to wtedy ekran1 w przeciwnym wypdaku ekran2
  
  lcd.print(napis);}else{
  
  lcd2.print(napis);
}  
}
void Cursor(int newX, int newY) {
  if(newY < 2){
    lcd.setCursor(newX, newY);
  }else{
    lcd2.setCursor(newX, newY - 2);
  }
  x = newX;
  y = newY;
}
int input(){
  uint32_t out = 0;
  int nacisniety = 0;
  // Sprawdzamy, czy odebrano jakiś sygnał
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData != 0) {
       
      Serial.print("Odebrano kod przycisku: ");
      // Wyświetlamy kod w formacie szesnastkowym (HEX)
      
      
      
      out = IrReceiver.decodedIRData.decodedRawData;
      Serial.print(out);
      switch (out) {
        case -1169817856:
          nacisniety = 1;
          break; // CH-
        case -1186529536:
          nacisniety = 2;
          break; //CH
        case -1203241216:
          nacisniety = 3;
          break;//CH+
        case -1153106176:
          nacisniety = 4; //PREV
          break;
        case -1086259456:
          nacisniety = 5; // NEXT
          break;
        case -1136394496:
          nacisniety = 6; // PLAY / PAUSE
          break;
        case -133693696:
          nacisniety = 7; // VOL-
          break;
        case -367657216:
          nacisniety = 8; // VOL+
          break;
        case -167117056:
          nacisniety = 9; // EQ
          break;
        case -384368896:
          nacisniety = 10; // 0
          break;
        case -434503936:
          nacisniety = 11; // 100+
          break;
        case -233963776:
          nacisniety = 12; //200+
          break;
        case -217252096:
          nacisniety = 13; // 1
          break;
        case -417792256:
          nacisniety = 14;
          break; // 2
        case -1587609856:
          nacisniety = 15;
          break; // 3
        case 4144561920:
          nacisniety = 16;
          break; // 4
        case -484638976:
          nacisniety = 17;
          break; // 5
        case -1520763136:
          nacisniety = 18;
          break; // 6
        case -1119682816:
          nacisniety = 19;
          break; // 7
        case -1387069696:
          nacisniety = 20;
          break; //8
        case -1253376256:
          nacisniety = 21;
          break; //9
      }







    }
 
    // Bardzo ważne: Wznów nasłuchiwanie, aby odebrać kolejny sygnał
    IrReceiver.resume(); 
  }
return nacisniety;
}
void Clear() {
  lcd.clear();
  lcd2.clear();
}
void OpenKeyboard() {
  keyboard = 1;
}
int Keyboard() {
  char key = 0;
  int klawisz = input();
  Serial.println(s_keyboard);
  if(klawisz == 7) {
    s_keyboard++;
    Clear();
  }if (klawisz == 6) {
    s_keyboard--;
    Clear();
  }

  if(keyboard == 1) {
    Cursor(0, 0);
    if (s_keyboard == 0) {
    print_o("1, 2, 3, 4, 5, 6, 7, 8, 9");
    int klawisz = input();
    if (klawisz == 13) {
      key = '1';
    }if (klawisz == 14) {
      key = '2';
    }if (klawisz == 15) {
      key = '3';
    }if (klawisz == 16) {
      key = '4';
    }if (klawisz == 17) {
      key = '5';
    }if (klawisz == 18) {
      key = '6';
    }if (klawisz == 19) {
      key = '7';
    }if(klawisz == 20) {
      key = '8';
    }if(klawisz == 21) {
      key = '9';
    }}if(s_keyboard == 1) {
    print_o("0, a, b, c, d, e, f, g, h");
    int klawisz = input();
    if (klawisz == 13) {
      key = '0';
    }if (klawisz == 14) {
      key = 'a';
    }if (klawisz == 15) {
      key = 'b';
    }if (klawisz == 16) {
      key = 'c';
    }if (klawisz == 17) {
      key = 'd';
    }if (klawisz == 18) {
      key = 'e';
    }if (klawisz == 19) {
      key = 'f';
    }if(klawisz == 20) {
      key = 'g';
    }if(klawisz == 21) {
      key = 'h';
    }     
    }if(s_keyboard == 2) {
    print_o("i, j, k, l, m, n, o, p, r");
    int klawisz = input();
    if (klawisz == 13) {
      key = 'i';
    }if (klawisz == 14) {
      key = 'j';
    }if (klawisz == 15) {
      key = 'k';
    }if (klawisz == 16) {
      key = 'l';
    }if (klawisz == 17) {
      key = 'm';
    }if (klawisz == 18) {
      key = 'n';
    }if (klawisz == 19) {
      key = 'o';
    }if(klawisz == 20) {
      key = 'p';
    }if(klawisz == 21) {
      key = 'r';
    }     
    }if(s_keyboard == 3) {
    print_o("s, t, u, w, x, y, z, -, +");
    int klawisz = input();
    if (klawisz == 13) {
      key = 's';
    }if (klawisz == 14) {
      key = 't';
    }if (klawisz == 15) {
      key = 'u';
    }if (klawisz == 16) {
      key = 'w';
    }if (klawisz == 17) {
      key = 'x';
    }if (klawisz == 18) {
      key = 'y';
    }if (klawisz == 19) {
      key = 'z';
    }if(klawisz == 20) {
      key = '+';
    }if(klawisz == 21) {
      key = '-';
    }     
    }if(s_keyboard == 4) {
    print_o("=, !, @, #, $, %, ^, &, *");
    int klawisz = input();
    if (klawisz == 13) {
      key = '=';
    }if (klawisz == 14) {
      key = '!';
    }if (klawisz == 15) {
      key = '@';
    }if (klawisz == 16) {
      key = '#';
    }if (klawisz == 17) {
      key = '$';
    }if (klawisz == 18) {
      key = '%';
    }if (klawisz == 19) {
      key = '^';
    }if(klawisz == 20) {
      key = '&';
    }if(klawisz == 21) {
      key = ' ';
    }     
    }
  
  }
  if(key != 0){
  return key;}
}
void printAPPS(){
  Cursor(3, 2);
  if (ulubione1 == 1) {
    print("Zegar", "Clock");
    
  }if (ulubione1 == 2) {
    print("Ustawienia", "Settings");
  }if (ulubione1 == 4) {
    print("Dinozaur", "Dino");
  }
  Cursor(3, 3);
  if (ulubione2 == 1) {
    print("Zegar", "Clock");
    
  }if (ulubione2 == 2) {
    print("Ustawienia", "Settings");
  }if (ulubione2 == 4) {
    print("Dinozaur", "Dino");
  } 
}
void setup() {

  Serial.begin(9600);
  randomSeed(analogRead(0));
  x_k = random(15);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
lcd.init();
lcd.backlight();
lcd2.init();
lcd2.backlight();
lcd.createChar(0, dino);
lcd.createChar(1, kaktus);
lcd2.createChar(0, dino);
lcd2.createChar(1, kaktus);
Serial.println("");
Serial.print("kompilacja: ");
Serial.print(__DATE__);
Serial.print(" ");
Serial.print(__TIME__);
  rtc.init();
int l = 0;
for (int i = 0; i < EEPROM.length(); i++) {
  if(EEPROM.read(i) == 0) {
    l++;
  }
}
lcd.setCursor(0, 0);
lcd.print(l);

print(F(" bajtow wolnych") , F(" bytes free"));
delay(2000);
lcd.clear();
print(F("? plikow ok"), F("? files ok"));
Cursor(0, 1);
print(F("? plikow wolnych"), F("? files free"));
Cursor(0, 2);
print(F("? plikow uszkodzonych"), F("? files corrupted"));
delay(3000);
  Clear();
Serial.println("uruchomiono w:");
Serial.print(millis());
Serial.print("ms");
Serial.print(" czyli ");
Serial.print(millis() / 1000);
Serial.print("s");
}

void loop() {

if(konfig != 255){
  if(strona == 0){
  Cursor(0, 2);
  print(F("konfiguracja"), F("setup"));
  Cursor(0, 3);
  print_o(F("0/3"));
  Cursor(0, 0);
  print(F("zacznij - 5"), F("begin - 5"));
  int klawisz = input();
  if(klawisz != 0){
    if(klawisz == 17){
 strona = 1;  
 Clear();  }}}if (strona == 1){
  int klawisz = input();
  Cursor(0, 2);
  print(F("wybierz jezyk"), F("choose language"));
  Cursor(0, 3);
  print_o(F("1/3"));
  Cursor(0, 0);
  print(F("PL - 4"), F("PL - 4"));
  Cursor(0, 1);
  print(F("EN - 6"), F("EN - 6"));
  print(F("Dalej - 5"), F("Go - 5"));
  if(klawisz == 16) {
    jezyk = 0;
    EEPROM.put(1, jezyk);
    Clear();
  }
  if(klawisz == 18) {
    jezyk = 1;
   EEPROM.put(1, jezyk);
   Clear();
  } if(klawisz == 17) {
    strona = 2;
    Clear();
  }
 }if(strona == 2) {
  int klawisz = input();
  Cursor(0, 2);
  print(F("Pamiec EEPROM"), F("EEPROM memory"));
  Cursor(0, 3);
  print_o(F("2/3"));
  Cursor(0, 0);
  print(F("wykasowac EEPROM?"), F("Erase EEPROM?"));
  Cursor(0, 1);
  print(F("5 - tak, dalej"), F("5 - yes, go"));
  if(klawisz == 17) {
    for(int i = 0; i < EEPROM.length(); i++) {
      EEPROM.put(i, 0);
      Clear();
      Cursor(0, 0);
      print(F("wykasowano..."), F("erased..."));
           Cursor(0, 1);
      lcd.print(i);
 
      print(F(" bajt"), F(" byte"));
      delay(1);
    }
    EEPROM.put(1, jezyk);
    Clear();
    print(F("wykasowano pomyslnie!"), F("erased succesfull!"));
    delay(100);
    strona = 3;
    Clear();
  }
 }if (strona == 3) {
  Cursor(0, 2);
  print(F("zakonczono konfiguracje"), F("ended config"));
  print_o(F("3/3"));
  EEPROM.put(0, 255);
  EEPROM.put(2, 1);
  EEPROM.put(3, 1);
  EEPROM.put(4, 2);
 }
  }else {
    int klawisz = input();
    if (klawisz == 2) {
      aplikacje[0] = 0;
      Clear();
      Serial.println("test");
      s_ust = 0;
    }
    Cursor(0, 1);
    if (s_info == 0) {
    Ds1302::DateTime now;
      rtc.getDateTime(&now);
  lcd.print(now.day);
  lcd.print(F("/"));
  lcd.print(now.month);
  lcd.print(F("/"));
  lcd.print(now.year);
  lcd.print(" ");
  lcd.print(now.hour);
  lcd.print(F(":"));
  lcd.print(now.minute);} if (s_info == 1) {
    print("?% baterii", "?% battery");
  }if (s_info == 2) {
    print("pozostalo ? minut na baterii", "? minutes on battery");
  }if (s_info == 3) {
    print("brak powiadomien", "no notifications");
  }if (s_info == 4) {
    print("?% zuzycia RAMu", "?% RAM usage");
  }if (s_info == 5) {
    s_info = 0;
  }
  czas = millis();
  roznicaCzasu = czas - ostatniCzas;
  if (roznicaCzasu > 30000) {
    lcd.clear();
    ostatniCzas = millis();
    Serial.println(ostatniCzas);
    s_info++;
  }
    if (aplikacje[0] == 0) {
      Cursor(0, 2);
      print_o("1.");
      Cursor(0, 3);
      print_o("2.");
      printAPPS();
      Cursor(0, 0);
      print("3. Wszystkie aplikacje", "3. All apps");
      int klawisz = input();
      if (klawisz == 13) {
        aplikacje[0] = ulubione1;
        Clear();
      }if (klawisz == 14) {
        aplikacje[0] = ulubione2;
        Clear();
      }if (klawisz == 15) {
        aplikacje[0] = 3;
        Clear();
      }
    }if (aplikacje[0] == 1) {
      czas = millis();
      roznicaCzasu = czas - ostatniCzas;
      Cursor(0, 2);
        Ds1302::DateTime now;
        Serial.println(roznicaCzasu);
  if (roznicaCzasu > 30000) {
    Clear();
    ostatniCzas = millis();
    Serial.println(ostatniCzas);
  }
  rtc.getDateTime(&now);
  lcd2.print(now.day);
  lcd2.print(F("/"));
  lcd2.print(now.month);
  lcd2.print(F("/"));
  lcd2.print(now.year);
  Cursor(0, 3);
  lcd2.print(now.hour);
  lcd2.print(F(":"));
  lcd2.print(now.minute);
    }if (aplikacje[0] == 2) {
      if (s_ust == 0) {

      Cursor(0, 2);
      print("1. czas", "1. time");
      Cursor(0, 3);
      print("2. Info o systemie", "2. About system");
      Cursor(0, 0);
      print("3. jezyk", "3. language");
      int klawisz = input();
      
      if (klawisz == 13) {
        s_ust = 1;
        Clear();
      }
      if (klawisz == 14) {
        s_ust = 2;
        Clear();
      }if (klawisz == 15) {
        s_ust = 3;
        Clear();
      }if (klawisz == 2) {
          aplikacje[0] = 0;
          Clear();
        }
      } if (s_ust == 1) {
      
        Cursor(0, 2);
        print("ustaw czas i date", "set time and date");
        Cursor(0, 3);
        lcd2.print(godzina);
        lcd2.print(":");
        lcd2.print(minuta);
        Cursor(0, 0);
        lcd.print(dzien);
        lcd.print("/");
        lcd.print(miesiac);
        lcd.print("/");
        lcd.print(rok);
        
        if (klawisz == 13) {
          if (edycja == 0) {
          godzina++;
          Clear();}else {
            dzien++;
            Clear();
          }
        }if (klawisz == 14) {
          if (edycja == 0) {
          godzina--;
          Clear();}else {
            dzien--;
            Clear();
          }
        }if (klawisz == 15) {
          if (edycja == 0) {
          minuta++;
          Clear();} else {
            miesiac++;
            Clear();
          }
        }if (klawisz == 16) {
          if (edycja == 0) {
          minuta--;
          Clear();}else {
            miesiac--;
            Clear();
          }
          }
                  if (klawisz == 17) {
          edycja = !edycja;
        }if (klawisz == 18) {
          rok++;
          Clear();
        }if (klawisz == 19) {
          rok--;
          Clear();
        }if (klawisz == 10) {
          Ds1302::DateTime dt = {
  .year = rok,
   .month = miesiac,
   .day = dzien,
  .hour = godzina,
   .minute = minuta,
    .second = 0,
   .dow = 1
 };
  rtc.setDateTime(&dt);
        }
        }if (s_ust == 2) {
          Cursor(0, 2);
          print("Wersja:", "Version:");
          Cursor(0, 3);
          print_o("pre1f2-1.0");
        }if (s_ust == 3) {
          Cursor(0, 2);
          print("jezyk", "language");
          lcd2.print(jezyk);
          if (klawisz == 13) {
            jezyk = 0;
            EEPROM.put(1, jezyk);

          }if (klawisz == 14) {
            jezyk = 1;
            EEPROM.put(1, jezyk);
          }
        }

      }if (aplikacje[0] == 3) {
        Cursor(0, 2);
        print("Zegar", "Clock");
        Cursor(0, 3);
        print("Ustawienia", "Settings");
        Cursor(0, 0);
        print("Dinozaur", "Dino");
        Cursor(15, kursor_y);
        print_o("<");
        int klawisz = input();
        if (klawisz == 14) {
          kursor_y++;
          Clear();
        }if (klawisz == 20) {
          kursor_y--;
          Clear();
        }if (klawisz == 2) {
          aplikacje[0] = 0;
          Clear();
        }if (klawisz == 17) {
          Clear();
          if (kursor_y == 2) {
            aplikacje[0] = 1;
          }if (kursor_y == 3) {
            aplikacje[0] = 2;
          }if (kursor_y == 0) {
            aplikacje[0] = 4;
          }
        }if (klawisz == 16) {
            if (kursor_y == 2) {
            ulubione1 = 1;
            EEPROM.put(3, 1);
          }if (kursor_y == 3) {
            ulubione1 = 2;
            EEPROM.put(3, 2);
          }if (kursor_y == 0) {
            ulubione1 = 4;
            EEPROM.put(3, 4);
          }
        }if (klawisz == 18) {
            if (kursor_y == 2) {
            ulubione2 = 1;
            EEPROM.put(4, 1);
          }if (kursor_y == 3) {
            ulubione2 = 2;
            EEPROM.put(4, 2);
          }if (kursor_y == 0) {
            ulubione2 = 4;
            EEPROM.put(4, 2);
          }
        }
      }if (aplikacje[0] == 4) {
        int klawisz = input();
        Cursor(0, y_d);
        lcd2.printByte(0);
        Cursor(x_k, 3);
        lcd2.printByte(1);
        Cursor(0, 0);
        print("wynik: ", "score: ");
        lcd.print(wynik);
        print_o(", ");
        lcd.print(EEPROM.read(5));

          czas2 = millis();
          czas3 = millis();
          roznicaCzasu2 = czas2 - ostatniCzas2;
          roznicaCzasu3 = czas3 - ostatniCzas3;
          if (roznicaCzasu2 > 1500) {
            y_d = 3;
            ostatniCzas2 = czas2;
            Clear();
           
          }if (roznicaCzasu3 > 500) {
             x_k--;
            ostatniCzas3 = czas3;
            Clear();
          }
          if (x_k <= 0 & y_d == 3) {
            Cursor(0, 2);
            print("przegrales!", "you lose!");
          if (wynik > EEPROM.read(5)) {
          EEPROM.put(5, wynik);
        }
          }if (x_k <= 0 & y_d == 2) {
            x_k = random(15);
            wynik++;
            Clear();
          }
        if (klawisz == 17) {
          Clear();
          if (x_k > 0) {
          y_d = 2;}else {
            wynik = 0;
            x_k = random(15);
          }

        }
      }
    }}
  



