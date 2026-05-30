#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <IRremote.h>
 #include <Ds1302.h>
#define IR_RECEIVE_PIN 2 // Pin, do którego podpięty jest sygnał
int jezyk = EEPROM.read(1); // język
int x = 0;
int y = 0;
int konfig = EEPROM.read(0);
int strona = 0;
int poz_u = 0;
int s_keyboard = 0;
int i_k = 0;
int s_ust = 0;
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
byte godzina = 0;
byte minuta = 0;
byte dzien = 1;
byte miesiac = 1;
byte rok = 0;
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
  long out = 0;
  int nacisniety = 0;
  // Sprawdzamy, czy odebrano jakiś sygnał
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData != 0) {
       
      Serial.print("Odebrano kod przycisku: ");
      // Wyświetlamy kod w formacie szesnastkowym (HEX)
      
      
      
      out = IrReceiver.decodedIRData.decodedRawData;
      Serial.print(out);
      if (out == -1169817856) {
        nacisniety = 1; // CH-
      }
      if (out == -1186529536) {
        nacisniety = 2; // CH
      }if (out == -1203241216) {
        nacisniety = 3; // CH+
      }if (out == -1153106176) {
        nacisniety = 3; // PREV
      }if (out == -1086259456) {
        nacisniety = 4; //NEXT
      }if (out == -1136394496) {
        nacisniety = 5; //PLAY / PAUSE
      }if (out == -133693696) {
        nacisniety = 6; // VOL-
      }if (out == -367657216) {
        nacisniety = 7; //VOL+
      }if (out == -167117056) {
        nacisniety = 8; //EQ
      }if (out == -384368896) {
        nacisniety = 9; //0
      }if (out == -434503936) {
        nacisniety = 10; // 100+
      }if (out == -233963776) {
        nacisniety = 11; // 200+
      }if (out == -217252096) {
        nacisniety = 12; // 1
      }if (out == -417792256) {
        nacisniety = 13; // 2
      }if (out == -1587609856) {
        nacisniety = 14; // 3
      }if (out == -150405376) {
        nacisniety = 15; // 4
      }if (out == -484638976) {
        nacisniety = 16; // 5
      }if (out == -1520763136) {
        nacisniety = 17; // 6
      }if (out == -1119682816) {
        nacisniety = 18; // 7
      }if (out == -1387069696) {
        nacisniety = 19; // 8
      }if (out == -1253376256) {
        nacisniety = 20; // 9
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
    if (klawisz == 12) {
      key = '1';
    }if (klawisz == 13) {
      key = '2';
    }if (klawisz == 14) {
      key = '3';
    }if (klawisz == 15) {
      key = '4';
    }if (klawisz == 16) {
      key = '5';
    }if (klawisz == 17) {
      key = '6';
    }if (klawisz == 18) {
      key = '7';
    }if(klawisz == 19) {
      key = '8';
    }if(klawisz == 20) {
      key = '9';
    }}if(s_keyboard == 1) {
    print_o("0, a, b, c, d, e, f, g, h");
    int klawisz = input();
    if (klawisz == 12) {
      key = '0';
    }if (klawisz == 13) {
      key = 'a';
    }if (klawisz == 14) {
      key = 'b';
    }if (klawisz == 15) {
      key = 'c';
    }if (klawisz == 16) {
      key = 'd';
    }if (klawisz == 17) {
      key = 'e';
    }if (klawisz == 18) {
      key = 'f';
    }if(klawisz == 19) {
      key = 'g';
    }if(klawisz == 20) {
      key = 'h';
    }     
    }if(s_keyboard == 2) {
    print_o("i, j, k, l, m, n, o, p, r");
    int klawisz = input();
    if (klawisz == 12) {
      key = 'i';
    }if (klawisz == 13) {
      key = 'j';
    }if (klawisz == 14) {
      key = 'k';
    }if (klawisz == 15) {
      key = 'l';
    }if (klawisz == 16) {
      key = 'm';
    }if (klawisz == 17) {
      key = 'n';
    }if (klawisz == 18) {
      key = 'o';
    }if(klawisz == 19) {
      key = 'p';
    }if(klawisz == 20) {
      key = 'r';
    }     
    }if(s_keyboard == 3) {
    print_o("s, t, u, w, x, y, z, -, +");
    int klawisz = input();
    if (klawisz == 12) {
      key = 's';
    }if (klawisz == 13) {
      key = 't';
    }if (klawisz == 14) {
      key = 'u';
    }if (klawisz == 15) {
      key = 'w';
    }if (klawisz == 16) {
      key = 'x';
    }if (klawisz == 17) {
      key = 'y';
    }if (klawisz == 18) {
      key = 'z';
    }if(klawisz == 19) {
      key = '+';
    }if(klawisz == 20) {
      key = '-';
    }     
    }if(s_keyboard == 4) {
    print_o("=, !, @, #, $, %, ^, &, *");
    int klawisz = input();
    if (klawisz == 12) {
      key = '=';
    }if (klawisz == 13) {
      key = '!';
    }if (klawisz == 14) {
      key = '@';
    }if (klawisz == 15) {
      key = '#';
    }if (klawisz == 16) {
      key = '$';
    }if (klawisz == 17) {
      key = '%';
    }if (klawisz == 18) {
      key = '^';
    }if(klawisz == 19) {
      key = '&';
    }if(klawisz == 20) {
      key = ' ';
    }     
    }
  
  }
  if(key != 0){
  return key;}
}
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
lcd.init();
lcd.backlight();
lcd2.init();
lcd2.backlight();
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
    if(klawisz == 16){
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
  if(klawisz == 15) {
    jezyk = 0;
    EEPROM.put(1, jezyk);
    Clear();
  }
  if(klawisz == 17) {
    jezyk = 1;
   EEPROM.put(1, jezyk);
   Clear();
  } if(klawisz == 16) {
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
  if(klawisz == 16) {
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
 }
  }else {
    int klawisz = input();
    if (klawisz == 2) {
      aplikacje[0] = 0;
      Clear();
      Serial.println("test");
      s_ust = 0;
    }
    if (aplikacje[0] == 0) {
      Cursor(0, 2);
      print(F("1. Zegar"), F("1. Clock"));
      Cursor(0, 3);
      print("2. Ustawienia", "2. Settings");
      int klawisz = input();
      if (klawisz == 12) {
        aplikacje[0] = 1;
        Clear();
      }if (klawisz == 13) {
        aplikacje[0] = 2;
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
      
      if (klawisz == 12) {
        s_ust = 1;
        Clear();
      }
      if (klawisz == 13) {
        s_ust = 2;
        Clear();
      }if (klawisz == 14) {
        s_ust = 3;
        Clear();
      }
      } if (s_ust == 1) {
      
        Cursor(0, 2);
        print("ustaw czas i date", "set time and date");
        Cursor(0, 3);
        lcd2.print(godzina);
        lcd2.print(":");
        lcd2.print(minuta);
        Cursor(0, 1);
        lcd.print(dzien);
        lcd.print("/");
        lcd.print(miesiac);
        lcd.print("/");
        lcd.print(rok);
        
        if (klawisz == 12) {
          if (edycja == 0) {
          godzina++;
          Clear();}else {
            dzien++;
            Clear();
          }
        }if (klawisz == 13) {
          if (edycja == 0) {
          godzina--;
          Clear();}else {
            dzien--;
            Clear();
          }
        }if (klawisz == 14) {
          if (edycja == 0) {
          minuta++;
          Clear();} else {
            miesiac++;
            Clear();
          }
        }if (klawisz == 15) {
          if (edycja == 0) {
          minuta--;
          Clear();}else {
            miesiac--;
            Clear();
          }
          }
                  if (klawisz == 16) {
          edycja = !edycja;
        }if (klawisz == 17) {
          rok++;
          Clear();
        }if (klawisz == 18) {
          rok--;
          Clear();
        }if (klawisz == 9) {
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
          if (klawisz == 12) {
            jezyk = 0;
            EEPROM.put(1, jezyk);

          }if (klawisz == 13) {
            jezyk = 1;
            EEPROM.put(1, jezyk);
          }
        }

      }
    }}
  



