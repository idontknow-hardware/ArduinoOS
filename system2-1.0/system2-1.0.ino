// lib
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <IRremote.h>
#include <Ds1302.h>

// IR
#define IR_RECEIVE_PIN 2 // IR
#define DECODE_NEC 1
#define EXCLUDE_UNIVERSAL_PROTOCOLS 1

// piny do czegos
#define RST_PIN = 4;
#define DAT_PIN = 3;
#define CLK_PIN = 5;

// i2c
LiquidCrystal_I2C lcd(0x27,16,2);
LiquidCrystal_I2C lcd2(0x26,16,2);
Ds1302 rtc(RST_PIN, CLK_PIN, DAT_PIN);

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// menu
int jezyk = EEPROM.read(1); // jezyk
int konfig = EEPROM.read(0);
int strona = 0;
int ulubione1 = EEPROM.read(3);
int ulubione2 = EEPROM.read(4);
int aplikacje[] = {};

// czas 
long czas = 0;
long czas2 = 0;
long czas3 = 0;
long roznicaCzasu = 0;
long       }if (aplikacje[0] == 4) {
        int klawisz = IRread();
        Cursor(0, y_d);
        lcd2.printByte(0);
        Cursor(x_k, 3);
        lcd2.printByte(1);
        Cursor(0, 0);
        print("wynik: ", "score: "); // wynik: 
        lcd.print(wynik);
        print_o(", ");
        lcd.print(EEPROM.read(5)); = 0;
long roznicaCzasu2 = 0;
long ostatniCzas2 = 0;
long roznicaCzasu3 = 0;
long ostatniCzas3 = 0;

byte godzina = 0;
byte minuta = 0;
byte dzien = 1;
byte miesiac = 1;
byte rok = 0;

// gry? -chackAJMCPE
int x = 0;
int y = 0;
int y_d = 3;
int x_k = 0;
int kursor_y = 0;
int wynik = 0;

int poz_u = 0;
int s_keyboard = 0;
int i_k = 0;
int s_ust = 0;
int s_info = 0;

bool edycja = 0;
bool keyboard = 0;

int poprawne = EEPROM.read(2);

uint8_t dino[8] = {0xC, 0xF, 0xC, 0xF, 0x1E, 0x1F, 0xA, 0xA};
uint8_t kaktus[8] = {0x4, 0x4, 0x5, 0x16, 0xC, 0x5, 0x6, 0x4};

// tekst -chackAJMCPE
// progmem zeby bylo w ROMie a nie w RAMie
const char tekstPL[][16] PROGMEM = {
  "Zegar",
  "Ustawienia",
  "Dinozaur",
  " bajtow wolnych",
  "? plikow ok", // 5
  "? plikow wolnych",
  "? plikow uszkodzonych",
  "konfiguracja",
  "0/3",
  "zacznij - 5", // 10
  "wybierz jezyk",
  "1/3",
  "PL - 4",
  "EN - 6",
  "Dalej - 5", // 15
  "Pamiec EEPROM",
  "2/3",
  "wykasowac EEPROM?",
  "5 - tak, dalej",
  "wykasowano...", // 20
  "wykasowano pomyslnie!",
  "zakonczono konfiguracje",
  "3/3",
  "?% baterii",
  "?% zuzycia RAMu", // 25
  "1. czas",
  "2. Info o systemie",
  "3. jezyk",
  "ustaw czas i date",
  "Wersja:", // 30
  "pre2f2-1.0",
  "jezyk",
  "Zegar",
  "Ustawienia",
  "Dinozaur", // 35
  "wynik: ",
  "przegrales!"
};

const char tekstEN[][16] PROGMEM = {
  "Clock",
  "Settings",
  "ChromeDino",
  " bytes free",
  "? files ok", // 5
  "? files free",
  "? files corrupted",
  "setup",
  "0/3",
  "begin - 5", // 10
  "choose language",
  "1/3",
  "PL - 4",
  "EN - 6",
  "Go - 5", // 15
  "EEPROM memory",
  "2/3",
  "Erase EEPROM?",
  "5 - yes, go",
  "erased...", // 20
  "erased succesfull!",
  "ended config",
  "3/3",
  "?% battery",
  "?% RAM usage", // 25
  "1. time",
  "2. About system",
  "3. language",
  "set time and date",
  "Version:", // 30
  "pre2f2-1.0",
  "language",
  "Clock",
  "Settings",
  "Dino", // 35
  "score: ",
  "you lose!"
};



/*
  poco dawać 2 stringi!!! 
  Lepiej zrobic sobie liste z angielskimi wiadomosciami i z polskimi, 
  wtedy jest mniej kopiowania danych przed callowaniem funkcji i 
  przy okazji kazdy tekst ładnie koło siebie, umozliwiajac dalsze rozwiniecie (dodatkowe jezyki)
  -chackAJMCPE
*/
void print(String pl, String en) {
  if (y < 2) { // jezeli y < 2, to wtedy ekran1 w przeciwnym wypdaku ekran2
    if (jezyk == 0) lcd.print(pl);
    else lcd.print(en); 
  } else {
    if (jezyk == 0) lcd2.print(pl);
    else lcd2.print(en);   
  }
}


// moze nie za bardzo zooptymalizowana ale na pewno uzywa mniej ramu! -chackAJMCPE
// max string length 16
void printb(uint16_t stringnum) {
  char buffer[16];
  if (y < 2) { // jezeli y < 2, to wtedy ekran1 w przeciwnym wypdaku ekran2
    if (jezyk == 0) {
      strcpy_P(buffer, (char*)pgm_read_word(&(tekstPL[stringnum])));
      lcd.print(buffer);
    } else {
      strcpy_P(buffer, (char*)pgm_read_word(&(tekstEN[stringnum])));
      lcd.print(buffer);
    }
  } else {
    if (jezyk == 0) {
      strcpy_P(buffer, (char*)pgm_read_word(&(tekstPL[stringnum])));
      lcd2.print(buffer);
    } else {
      strcpy_P(buffer, (char*)pgm_read_word(&(tekstEN[stringnum])));
      lcd2.print(buffer);
    }
  }
}


// okej, nie ma co tu zarzucic -chackAJMCPE
void print_o(String napis) {
  if(y < 2){ // jezeli y < 2, to wtedy ekran1 w przeciwnym wypdaku ekran2
  lcd.print(napis);}else{
  
  lcd2.print(napis);
}  
}

// okej, nie ma co tu zarzucic -chackAJMCPE
void Cursor(int newX, int newY) {
  if(newY < 2){
    lcd.setCursor(newX, newY);
  }else{
    lcd2.setCursor(newX, newY - 2);
  }
  x = newX;
  y = newY;
}

int IRread(){
  uint32_t out = 0;
  int nacisniety = 0;
  // Sprawdzamy, czy odebrano jakis sygnal
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData != 0) {
      Serial.print("Odebrano kod przycisku: ");
      // Wyswietlamy kod w formacie szesnastkowym (HEX)
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
    // Bardzo wazne: Wznow nasluchiwanie, aby odebrac kolejny sygnal
    IrReceiver.resume(); 
  }
  return nacisniety;
}

void Clear() {
  lcd.clear();
  lcd2.clear();
}

/*
// Zostawiam bo moze sie przydac, ale lepiej po prostu 
// ustawic keyboard=1 zamiast callowac do funkcji. Mniej JSR
// -chackAJMCPE
void OpenKeyboard() {
  keyboard = 1;
}
*/

int Keyboard() {
  char key = 0;
  int klawisz = IRread();
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
      int klawisz = IRread();
      // taka optymalizacja -chackAJMCPE
      if(klawisz > 13) {
        key = (klawisz - 13) + '1';
      }
    }
    if(s_keyboard == 1) {
      print_o("0, a, b, c, d, e, f, g, h");
      int klawisz = IRread();
      if (klawisz == 13) {
        key = '0';
      }
      // taka optymalizacja -chackAJMCPE
      if (klawisz >= 14 && klawisz <= 22) {
        key = (klawisz - 14) + 'a';
      }   
    }
    if(s_keyboard == 2) {
      print_o("i, j, k, l, m, n, o, p, r");
      int klawisz = IRread();
      // taka optymalizacja -chackAJMCPE
      if(klawisz >= 14 && klawisz <= 22) {
      key = (klawisz - 14) + 'i';
      }  
    }
    if(s_keyboard == 3) {
      print_o("s, t, u, w, x, y, z, -, +");
      int klawisz = IRread();
      // taka optymalizacja -chackAJMCPE
      if((klawisz > 13) && (klawisz <= 19)) {
        key = (klawisz - 13) + 's';
      }  
      if(klawisz == 20) {
        key = '+';
      }
      if(klawisz == 21) {
        key = '-';
      }     
    }
    if(s_keyboard == 4) {
      print_o("=, !, @, #, $, %, ^, &, *");
      int klawisz = IRread();
      if (klawisz == 13) {
        key = '=';
      }
      if (klawisz == 14) {
        key = '!';
      }
      if (klawisz == 15) {
        key = '@';
      }
      // taka optymalizacja -chackAJMCPE
      if(klawisz > 15) {
        key = (klawisz - 16) + '#';
      }    
    }
  }
  if(key != 0) return key;
}




void printAPPS(){
  Cursor(3, 2);
  if (ulubione1 == 1) {
    printb(1); // zegar
  }
  if (ulubione1 == 2) {
    printb(2); // ustawienia
  }
  if (ulubione1 == 4) {
    printb(3); // dinozaur
  }

  Cursor(3, 3);
  if (ulubione2 == 1) {
    printb(1); // zegar
  }
  if (ulubione2 == 2) {
    printb(2); // ustawienia
  }
  if (ulubione2 == 4) {
    printb(3); // dinozaur
  }
}

// okej, ale nie bylo za bardzo czytelne, teraz powinno byc -chackAJMCPE
void setup() {
  // init
  Serial.begin(9600);
  rtc.init();
  lcd.init();
  lcd2.init();
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // IR init
  randomSeed(analogRead(0)); // random seed init
  x_k = random(15); // Niewiem co to -chackAJMCPE

  // backlight on
  lcd.backlight();
  lcd2.backlight();
  
  // pokaz apki
  lcd.createChar(0, dino);
  lcd.createChar(1, kaktus);
  lcd2.createChar(0, dino);
  lcd2.createChar(1, kaktus);

  // print wersji na uart
  Serial.print("\r\n");
  Serial.print("Date of build: ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.print(__TIME__);
  
  // sprawdzanie ile jest wolnych bajtow, mozna optymalizowac ale nie teraz
  int l = 0;
  for (int i = 0; i < EEPROM.length(); i++) {
    if(EEPROM.read(i) == 0) {
      l++;
    }
  }

  // print danych
  lcd.setCursor(0, 0);
  lcd.print(l); // print wolnych bajtow (liczba)
  printb(4); // print wolnych bajtow (tekst)
  delay(2000);

  lcd.clear();
  printb(5); // pliki ok

  Cursor(0, 1);
  printb(6); // pliki wolne

  Cursor(0, 2);
  printb(7); // pliki uszkodzone
  delay(3000);


  Clear();
  Serial.println("uruchomiono w:");
  Serial.print(millis());
  Serial.print("ms");
  Serial.print(" czyli ");
  Serial.print(millis() / 1000);
  Serial.print("s");
}


// Oj, tu bylo duzo poprawek formatowania i kodu, 
// nie chce mi sie dokumentowac co dokladnie zmienilem. -chackAJMCPE
void loop() {
  if (konfig != 255) {
    if (strona == 0) { // ekran ustawien
      // cos na ekran
      Cursor(0, 2);
      printb(7); // konfiguracja
      Cursor(0, 3);
      print_o(F("0/3"));
      Cursor(0, 0);
      printb(9); // zacznij - 5

      // przycisk
      int klawisz = IRread(); 
      if (klawisz == 17) {
        strona = 1;  
        Clear();  
      }
    }
    if (strona == 1) { // ekran jezyka
      // cos na ekran
      Cursor(0, 2);
      printb(10); // wybierz jezyk
      Cursor(0, 3);
      print_o(F("1/3"));
      Cursor(0, 0);
      printb(12); // PL - 4
      Cursor(0, 1);
      printb(13); // EN - 6
      printb(14); // Dalej - 5

      int klawisz = IRread(); // zczytaj przyciski

      switch (klawisz) {
        case 16: {
          jezyk = 0;
        }
        case 18: {
          jezyk = 1;
        }
        case 17: {
          strona = 2;
        }
      }
      if (klawisz) Clear();
      if (klawisz == 18 || klawisz == 16) EEPROM.put(1, jezyk);
    }
    if(strona == 2) { // ekran wykasowywania
      // cos na ekran
      Cursor(0, 2);
      printb(15); // Pamiec EEPROM
      Cursor(0, 3);
      print_o(F("2/3"));
      Cursor(0, 0);
      printb(17); // wykasowac EEPROM?
      Cursor(0, 1);
      printb(18); // 5 - tak, dalej

      int klawisz = IRread(); // zczytaj przyciski
      if(klawisz == 17) {
        for(int i = 0; i < EEPROM.length(); i++) {
          EEPROM.put(i, 0);
          Clear();
          Cursor(0, 0);
          printb(19); // wykasowano...
          Cursor(0, 1);
          lcd.print(i);
          print_o(" bajt");
          delay(1);
        }
        EEPROM.put(1, jezyk);
        Clear();
        printb(20); // wykasowano pomyslnie!
        delay(100);
        strona = 3;
        Clear();
      }
    }
    if (strona == 3) {
      Cursor(0, 2);
      printb(21); // zakonczono konfiguracje
      print_o(F("3/3"));
      EEPROM.put(0, 255);
      EEPROM.put(2, 1);
      EEPROM.put(3, 1);
      EEPROM.put(4, 2);
    }
  } else {
    int klawisz = IRread();
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
    printb(23); // ?% baterii
  }if (s_info == 2) {
    printb(24); // pozostalo ? minut na baterii
  }if (s_info == 3) {
    printb(25); // brak powiadomien
  }if (s_info == 4) {
    printb(26); // ?% zuzycia RAMu
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
      printb(26); // 3. Wszystkie aplikacje
      int klawisz = IRread();
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
      printb(26);
      Cursor(0, 3);
      printb(27);
      Cursor(0, 0);
      printb(28);
      int klawisz = IRread();
      
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
        printb(29); // ustaw czas i date
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
          printb(30); // Wersja:
          Cursor(0, 3);
          print_o("pre2f2-1.0");
        }if (s_ust == 3) {
          Cursor(0, 2);
          printb(32); // jezyk
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
        printb(33);
        Cursor(0, 3);
        printb(34);
        Cursor(0, 0);
        printb(35);
        Cursor(15, kursor_y);
        print_o("<");
        int klawisz = IRread();
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
        int klawisz = IRread();
        Cursor(0, y_d);
        lcd2.printByte(0);
        Cursor(x_k, 3);
        lcd2.printByte(1);
        Cursor(0, 0);
        printb(36); // wynik: 
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
            printb(37); // przegrales!
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




