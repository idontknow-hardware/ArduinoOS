#define DECODE_NEC 1
#define EXCLUDE_UNIVERSAL_PROTOCOLS 1
#define EXCLUDE_EXOTIC_PROTOCOLS    1
#define NO_LED_FEEDBACK_CODE        1

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <IRremote.h>
 #include <Ds1302.h>
 #include <avr/wdt.h>
#define IR_RECEIVE_PIN 2 // Pin, do którego podpięty jest sygnał
#define przycisk1 6
#define przycisk2 7
#define przycisk3 8
#define PIN1 A1
#define PIN2 A2
#define PIN3 A3
uint8_t s_g = 0;
bool RTC = 1;
bool diagnostyka = 0;
uint8_t blad = 0;
uint8_t w_pin = 0;
uint8_t opcje_port = 0;
uint8_t powiadomienie = 0;
uint8_t port_u = EEPROM.read(10);
bool fullscreen = 0;
uint8_t kod = 0;
uint8_t liczba = 0;
uint8_t i_wg = 0;
long plik_wg = 0;
uint8_t o_s_pliku = 0;
int czekaj = 0;
uint8_t s_w = 0;
int jezyk = EEPROM.read(1); // język
int plik = 64;
bool n_plik = 0;
bool e_plik = 0;
bool mode = 0;
bool opcje = 0;
uint8_t uruchamianie = 0;
uint8_t t_pliku = 0;
uint8_t s_pliku = 0;
uint8_t i_pliku = 0;
uint8_t i_notka = 12;
uint8_t i_kodu = 12;
uint8_t i_kodu_p = 64;
bool warunki = 0;
char t1_kodu = ' ';
uint8_t wartosc1 = 0;
uint8_t wartosc2 = 0;
uint8_t wartosc3 = 0;
uint8_t wartosc4 = 0;
uint8_t wybrana_w = 0;
uint8_t ostatnia_akcja = 0;
uint8_t ob_kom = 0;
uint8_t wartosc = 0;
uint8_t bajt = 0;
uint8_t x_kod = 0;
uint8_t y_kod = 0;
bool naz_pliku = 0;
uint8_t x = 0;
uint8_t y = 0;
uint8_t y_d = 3;
uint8_t x_k = 0;
uint8_t kursor_y = 0;
uint8_t wynik = 0;
uint8_t konfig = EEPROM.read(0);
uint8_t strona = 0;
uint8_t s_keyboard = 0;
uint8_t s_ust = 0;
uint8_t s_info = 0;
uint8_t ulubione1 = EEPROM.read(3);
uint8_t ulubione2 = EEPROM.read(4);
uint8_t ulubione3 = EEPROM.read(11);
uint8_t ulubione4 = EEPROM.read(12);
bool edycja = 0;
bool keyboard = 0;
uint8_t aplikacje[] = {};
uint8_t poprawne = EEPROM.read(2);
bool ostrzezenie = EEPROM.read(6);
uint8_t s_wa = 0;
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
long czas4 = 0;
long roznicaCzasu4 = 0;
long ostatniCzas4 = 0;
uint8_t przycisk1_z = EEPROM.read(7);
uint8_t przycisk2_z = EEPROM.read(8);
uint8_t przycisk3_z = EEPROM.read(9);
byte godzina = 0;
byte minuta = 0;
byte dzien = 1;
byte miesiac = 1;
byte rok = 0;
int procent_o = 0;
int zostalo = 0;
uint8_t dino[8] = {0xC, 0xF, 0xC, 0xF, 0x1E, 0x1F, 0xA, 0xA};
uint8_t kaktus[8] = {0x4, 0x4, 0x5, 0x16, 0xC, 0x5, 0x6, 0x4};
uint8_t plik_u[8] = {0x64, 0xE, 0x1F, 0xE, 0xE, 0xE, 0xE, 0x0};
uint8_t plik_c[8] = {0x0, 0x0, 0x0, 0x10, 0x1B, 0x15, 0x0, 0x0};
uint8_t notatka[8] = {0x0, 0x1F, 0x15, 0x1B, 0x15, 0x1B, 0x1F, 0x0};
uint8_t aplikacja[8] = {0x0, 0x1F, 0x0, 0x8, 0x15, 0x2, 0x1F, 0x0};
uint8_t dane[8] = {0x1C, 0x14, 0x14, 0x1C, 0x8, 0x18, 0x8, 0x8};
uint8_t kodi[8] = {0x1D, 0x0, 0x1F, 0x0, 0x1F, 0x0, 0x1E, 0x1D};
LiquidCrystal_I2C lcd(0x27,16,2);
Ds1302 rtc(RST_PIN, CLK_PIN, DAT_PIN);
LiquidCrystal_I2C lcd2(0x26,16,2);
template<typename T>
void print(T pl, T en) {
    if (y < 2) {
        if (jezyk == 0)
            lcd.print(pl);
        else
            lcd.print(en);
    } else {
        if (jezyk == 0)
            lcd2.print(pl);
        else
            lcd2.print(en);
    }
}
template<typename T>
void print_o(T napis)
{
    if (y < 2)
        lcd.print(napis);
    else
        lcd2.print(napis);
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

uint8_t input() {
  uint8_t nacisniety = 0;  
  if (digitalRead(przycisk1) == 0) {
    nacisniety = przycisk1_z;

  }if (digitalRead(przycisk2) == 0) {
    nacisniety = przycisk2_z;

  }if (digitalRead(przycisk3) == 0) {
    nacisniety = przycisk3_z;

  }if (aplikacje[0] != 8) {
  if (port_u == 0) {int wartoscX = analogRead(PIN1) - 505; 
  int wartoscY = analogRead(PIN2) - 521;
  int stanSW = digitalRead(PIN3);
if (wartoscX < -420 and wartoscY > 0) {
    nacisniety = 1;
  }if (wartoscX > 500 and wartoscY > 0) {
    nacisniety = 3;
  }if (wartoscX > 0 and wartoscY > 490) {
    nacisniety = 2;
  }
}
  if (port_u == 2) {
    
    if (digitalRead(PIN1) == 0) {
    nacisniety = 2;}
  }}
  // Sprawdzamy, czy odebrano jakiś sygnał
  if (IrReceiver.decode()) {

    if (IrReceiver.decodedIRData.command != 0) {
       
      Serial.print(F("Odebrano komende: "));

      uint8_t cmd = IrReceiver.decodedIRData.command;
      Serial.println(cmd);
      

      switch (cmd) {
        case 0x45: nacisniety = 1;  break; // CH-
        case 0x46: nacisniety = 2;  break; // CH
        case 0x47: nacisniety = 3;  break; // CH+
        case 0x44: nacisniety = 4;  break; // PREV
        case 0x40: nacisniety = 5;  break; // NEXT
        case 0x43: nacisniety = 6;  break; // PLAY / PAUSE
        case 0x7: nacisniety = 7;  break; // VOL-
        case 0x15: nacisniety = 8;  break; // VOL+
        case 0x9: nacisniety = 9;  break; // EQ
        case 0x16: nacisniety = 10; break; // 0
        case 0x19: nacisniety = 11; break; // 100+
        case 0xD: nacisniety = 12; break; // 200+
        case 0xC: nacisniety = 13; break; // 1
        case 0x18: nacisniety = 14; break; // 2
        case 0x5E: nacisniety = 15; break; // 3
        case 0x8: nacisniety = 16; break; // 4
        case 0x1C: nacisniety = 17; break; // 5
        case 0x5A: nacisniety = 18; break; // 6
        case 0x42: nacisniety = 19; break; // 7
        case 0x52: nacisniety = 20; break; // 8
        case 0x4A: nacisniety = 21; break; // 9
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



int Keyboard() {
  char keys[45] = {'1','2','3','4','5','6','7','8','9','0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','w','x','y','z','-','+','=','!','@','#','$','%','^','&',' '};
  int key = 0;
  int klawisz = input();
  if(klawisz == 8) {
    s_keyboard++;
    Clear();
  }if (klawisz == 7) {
    s_keyboard--;
    Clear();
  }

  if(keyboard == 1) {
    Cursor(0, 0);
    if (klawisz != 0) {
    print_o(keys[klawisz - 13 + 9 * s_keyboard]);
    key = keys[klawisz - 13 + 9 * s_keyboard];
    }
  }
  return key;
}
void printAPPS(){
  if (s_g == 0) {
  Cursor(3, 2);
  if (ulubione1 == 1) {
    print(F("Zegar"), F("Clock"));
    
  }if (ulubione1 == 2) {
    print(F("Ustawienia"), F("Settings"));
  }if (ulubione1 == 4) {
    print(F("Dinozaur"), F("Dino"));
  }if (ulubione1 == 5) {
    print(F("Pliki"), F("Files"));
  }if (ulubione1 == 6) {
    print(F("Notatnik"), F("Notes"));
  }if (ulubione1 == 9) {
    print_o("Port");
  }
  Cursor(3, 3);
  if (ulubione2 == 1) {
    print(F("Zegar"), F("Clock"));
    
  }if (ulubione2 == 2) {
    print(F("Ustawienia"), F("Settings"));
  }if (ulubione2 == 4) {
    print(F("Dinozaur"), F("Dino"));
  }if (ulubione2 == 5) {
    print(F("Pliki"), F("Files"));
  }if (ulubione2 == 6) {
    print(F("Notatnik"), F("Notes"));
  }if (ulubione2 == 9) {
    print_o("Port");
  }}if (s_g == 1) {
  Cursor(3, 2);
  if (ulubione3 == 1) {
    print(F("Zegar"), F("Clock"));
    
  }if (ulubione3 == 2) {
    print(F("Ustawienia"), F("Settings"));
  }if (ulubione3 == 4) {
    print(F("Dinozaur"), F("Dino"));
  }if (ulubione3 == 5) {
    print(F("Pliki"), F("Files"));
  }if (ulubione3 == 6) {
    print(F("Notatnik"), F("Notes"));
  }if (ulubione3 == 9) {
    print_o("Port");
  }
  Cursor(3, 3);
  if (ulubione4 == 1) {
    print(F("Zegar"), F("Clock"));
    
  }if (ulubione4 == 2) {
    print(F("Ustawienia"), F("Settings"));
  }if (ulubione4 == 4) {
    print(F("Dinozaur"), F("Dino"));
  }if (ulubione4 == 5) {
    print(F("Pliki"), F("Files"));
  }if (ulubione4 == 6) {
    print(F("Notatnik"), F("Notes"));
  }if (ulubione4 == 9) {
    print_o("Port");
  }
  }
}
long readVcc() {

  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  
  long result = ADCL;
  result |= ADCH << 8;
  result = 1125300L / result; // mV
  return result;
}
int procent() {
  long mv = readVcc();
  float voltage = mv / 1000.0;
  
  

  int percent = map(mv, 4000, 5181, 0, 100);
  percent = constrain(percent, 0, 100);
  return percent;
}
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
int tempCPU() {
    ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
  delay(20); 

  ADCSRA |= (1 << ADSC); 
  while (ADCSRA & (1 << ADSC)); 

  int adcVal = ADCW;
  int tempC = (adcVal * 100 - 26116) / 122;
  return tempC;
}
void printDate() {
          Ds1302::DateTime now;
  rtc.getDateTime(&now);
if (RTC == 1) {
  print_o(now.day);
  print_o(F("/"));
  print_o(now.month);
  print_o(F("/"));
  print_o(now.year);
  print_o(" ");
  print_o(now.hour);
  print_o(F(":"));
  print_o(now.minute);
  print_o(":");
  print_o(now.second);}else{
    print_o("?/?/? ");
    print_o(millis() / 3600000);
    print_o(":");
    print_o(millis() / 60000);
    print_o(":");
    print_o(millis() / 1000);
  }
 if (now.minute == 85) {
  RTC = 0;
 }else {
  RTC = 1;
 }
}
double getDistance() {
    int Time;
double Distance;
digitalWrite(A1, HIGH);
delayMicroseconds(10);
digitalWrite(A1, LOW);
Time = pulseIn(A2, HIGH); 
Distance = Time / 58;
return Distance;
}
void setPort() {
if (port_u == 0) {
  pinMode(PIN1, INPUT);
  pinMode(PIN2, INPUT);
  pinMode(PIN3, INPUT_PULLUP);
  Serial.println(F("tryb portu: joystick"));
}if (port_u == 1) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, INPUT);
  digitalWrite(PIN1, LOW);
  Serial.println(F("tryb portu: czujnik odleglosci"));
}if (port_u == 2) {
  pinMode(PIN1, INPUT_PULLUP);
  Serial.println(F("tryb portu: bali switch"));
}if (port_u == 3) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
  Serial.println(F("tryb portu: dioda RGB"));
}
}
void setup() {
wdt_disable();
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
lcd2.createChar(2, plik_u);
lcd2.createChar(3, plik_c);
lcd2.createChar(4, notatka);
lcd2.createChar(5, aplikacja);
lcd2.createChar(6, dane);
lcd2.createChar(7, kodi);
pinMode(przycisk1, INPUT_PULLUP);
pinMode(przycisk2, INPUT_PULLUP);
pinMode(przycisk3, INPUT_PULLUP);

setPort();
if (port_u > 3) {
  Serial.println(F("niepoprawnie wybrany tryb portu! Wejdz do aplikacji 'port' aby ustawic poprawnie!"));
}

  rtc.init();

lcd.setCursor(0, 0);
int ok = 0;
int free = 0;
int cor = 0;
for (int i = 65; i < EEPROM.length(); i = i + 76) {
  if (EEPROM.read(i) == 1) {
    ok++;
  }if (EEPROM.read(i) == 0 or EEPROM.read(i + 1) == 2) {
    free++;
  }if (EEPROM.read(i + 1) >= 3) {
    cor++;
  }}

          Ds1302::DateTime now;
  rtc.getDateTime(&now);
  if (now.minute > 60) {
    RTC = 0;
  }
Clear();
print_o(ok);
print(F(" plikow ok"), F(" files ok"));
Cursor(0, 1);
print_o(free);
print(F(" plikow wolnych"), F(" files free"));
Cursor(0, 2);
print_o(cor);
print(F(" plikow uszkodzonych"), F(" files corrupted"));
long czasD = millis();
long ostatniD = 0;
long roznicaD = czasD - ostatniD;
while(roznicaD < 5000) {
  czasD = millis();
  roznicaD = czasD - ostatniD;
  int klawisz = input();
  if (klawisz == 13) {
    diagnostyka = 1;
    Clear();
    roznicaD = 5000;
  }
}
while(diagnostyka) {
  Cursor(0, 2);
  print("Diagnostyka", "Diagnostic");
  delay(300);
  Clear();
  for (uint8_t i = 0; i < 254; i++) {
    lcd.write(i);
    lcd2.write(i);
  }          Ds1302::DateTime now;
  rtc.getDateTime(&now);
  Clear();
  if (now.minute > 60) {
    print_o("NO RTC!!");
    delay(500);
  }
  diagnostyka = 0;

  int klawisz = input();
  if (klawisz == 13) {
    diagnostyka = 0;
  }
}
  Clear();
if (ostrzezenie == 1) {
Cursor(0, 2);
print(F("Uwaga!"), F("Caution!"));
Cursor(0, 3);
print(F("Jesli usuniesz"), F("If you delete "));
Cursor(0, 0);
print(F(" plik"), F("file"));
Cursor(0, 1);
print(F(" mozesz go nadpisac tworzac nowy!"), F(" you can overwrite it making new!"));
delay(2000);
for (int i = 0; i < 20; i++){
lcd.scrollDisplayLeft();
delay(500);}
Clear();
EEPROM.update(6, 0);

}
procent_o = procent();

Clear();
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
    EEPROM.update(1, jezyk);
    Clear();
  }
  if(klawisz == 18) {
    jezyk = 1;
   EEPROM.update(1, jezyk);
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
      EEPROM.update(i, 0);
      Clear();
      Cursor(0, 0);
      print(F("wykasowano..."), F("erased..."));
           Cursor(0, 1);
      print_o(i);
 
      print(F(" bajt"), F(" byte"));
      delay(1);
    }
    EEPROM.update(1, jezyk);
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
  EEPROM.update(0, 255);
  EEPROM.update(2, 1);
  EEPROM.update(3, 1);
  EEPROM.update(4, 2);
  EEPROM.update(11, 5);
  EEPROM.update(12, 9);
  EEPROM.update(6, 1);
  EEPROM.update(7, 1);
  EEPROM.update(8, 2);
  EEPROM.update(9, 3);
    for (int i = 64; i < EEPROM.length() - 76; i = i + 76) {
      
    for (int i_P = 1; i_P < 76; i_P++) {


      if (i_P == 1) {
        EEPROM.update(i + i_P, 0);

      }if (i_P == 2) {
        EEPROM.update(i + i_P, 1);
      }if (i_P > 2 and i_P < 12) {
        EEPROM.update(i + i_P, 'a');
      }if (i_P > 11) {
        EEPROM.update(i + i_P, 0);
      }
    }
  }
  konfig = EEPROM.read(0);
 }
  }else {

    int klawisz = input();    
    if (klawisz == 2) {
      aplikacje[0] = 0;
      Clear();
      fullscreen = 0;
      s_ust = 0;
      opcje_port = 0;
    }
    int fRAM = freeRam();
    if (2048 - fRAM > 1990 and 2048 - fRAM < 2049) {
      blad = 1;
      aplikacje[0] = -1;
    }
    int C = tempCPU();
    if (C > 40) {
      blad = 2;
      aplikacje[0] = -1;
    }

    if (fullscreen == 0) {
    Cursor(0, 1);
    if (s_info == 0) {

printDate();} if (s_info == 1) {
    int proc = procent();
    print_o(proc);
    print(F("% baterii"), F("% battery"));
  }if (s_info == 2) {
    czas4 = millis();
    roznicaCzasu4 = czas4 - ostatniCzas4;
    if (roznicaCzasu4 > 60000) {
      zostalo = 0;
      int proc = procent();
      int roznica = procent_o - proc;

      for(int i = 0; i < proc; i = i + roznica) {
        zostalo++;

        if(roznica == 0) {
          break;
        }
      }
      procent_o = procent();
      ostatniCzas4 = czas4;
    }
    if (zostalo < 60) {
      print_o("0:");
      print_o(zostalo);
    }else {
      int zostalo2 = zostalo / 60;
      print_o(zostalo2);
      zostalo = zostalo - zostalo2 * 60;
      print_o(":");
      print_o(zostalo);
    }
    print(F(" na baterii"), F(" on battery"));

  }if (s_info == 3) { 
    if (powiadomienie == 0) {
    print(F("brak powiadomien"), F("no notifications"));}
    if (powiadomienie == 1) {
      print(F("wykryto obiekt!"), F("obiect deceted!"));
    }
    if (port_u == 1) {
double Distance = getDistance();

if (Distance < 50) {
  powiadomienie = 1;
}else {
  powiadomienie = 0;
}}
  }if (s_info == 4) {
    int RAM = freeRam();
    print_o(2048 - RAM);
    print(F("B zuzycia RAMu"), F("B RAM usage"));
  }if (s_info == 5) {
  int Val = tempCPU();

  print_o(Val);
    print_o(F(" *C temp. CPU"));
  }if (s_info == 6) {
    s_info = 0;
  }
  czas = millis();
  roznicaCzasu = czas - ostatniCzas;
  if (roznicaCzasu > 10000) {
    lcd.clear();
    ostatniCzas = millis();
    s_info++;
  }}
    if (aplikacje[0] == 0) {
      if (s_g == 0) {
      Cursor(0, 2);
      print_o(F("1."));
      Cursor(0, 3);
      print_o(F("2."));}
      if (s_g == 1) {
        Cursor(0, 2);
        print_o("4.");
        Cursor(0, 3);
        print_o("5.");
      }
      printAPPS();
      Cursor(0, 0);
      print(F("3. Wszystkie apki"), F("3. All apps"));
      int klawisz = input();
      if (klawisz == 1) {
        s_g--;
        Clear();
      }if (klawisz == 3) {
        s_g++;
        Clear();

      }
      if (klawisz == 13) {
        aplikacje[0] = ulubione1;
        Clear();
      }if (klawisz == 14) {
        aplikacje[0] = ulubione2;
        Clear();

      }if (klawisz == 15) {
        aplikacje[0] = 3;
        Clear();
      }if (klawisz == 16) {
        aplikacje[0] = ulubione3;
      }if (klawisz == 17) {
        aplikacje[0] = ulubione4;
      }
    }if (aplikacje[0] == 1) {
      czas = millis();
      roznicaCzasu = czas - ostatniCzas;
      Cursor(0, 2);


  if (roznicaCzasu > 60000) {
    Clear();
    ostatniCzas = millis();

  }
printDate();
    }if (aplikacje[0] == 2) {
      if (s_ust == 0) {

      if (s_w == 0) {
      Cursor(0, 2);
      print(F("1. czas"), F("1. time"));
      Cursor(0, 3);
      print(F("2. Info o systemie"), F("2. About system"));
      Cursor(0, 0);
      print(F("3. jezyk"), F("3. language"));

      }if (s_w == 1) {
        Cursor(0, 2);
        print(F("4. Ustawienia przycisków"), F("4. Button Settings"));
        Cursor(0, 3);
        print(F("5. Czas dzialania"), F("5. Uptime"));
        Cursor(0, 0);
        print(F("6. Bateria"), F("6. Battery"));
      }
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
      }if (klawisz == 16) {
        
        s_ust = 4;
Clear();
      }if (klawisz == 17) {
        s_ust = 5; 
        Clear();
      }if (klawisz == 18) {
        s_ust = 6;
        Clear();
      }
      if (klawisz == 1) {
        Clear();
        s_w--;

      }if (klawisz == 2) {
        Clear();
          aplikacje[0] = 0;

        }if (klawisz == 3) {
        Clear();
          s_w++;

        }
      } if (s_ust == 1) {
      
        Cursor(0, 2);
        print("ustaw czas i date", "set time and date");
        Cursor(0, 3);
        print_o(godzina);
        print_o(':');
        print_o(minuta);
        Cursor(0, 0);
        print_o(dzien);
        print_o('/');
        print_o(miesiac);
        print_o('/');
        print_o(rok);
        
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
          print_o("2-1.0");
        }if (s_ust == 3) {
          Cursor(0, 2);
          print("jezyk", "language");
          print_o(jezyk);
          if (klawisz == 13) {
            jezyk = 0;
            EEPROM.update(1, jezyk);


          }if (klawisz == 14) {
            jezyk = 1;
            EEPROM.update(1, jezyk);
          }
        }if (s_ust == 4) {
          Cursor(0, 3);
          print("Nacisnij przycisk", "Press button");
          Cursor(0, 4);

          int klawisz = input();
          print_o(klawisz);

            if (digitalRead(przycisk1) == 0) {
              czekaj = 0;
              EEPROM.update(7, klawisz);
              przycisk1_z = klawisz;
            }else {
              czekaj++;
            }
            if (digitalRead(przycisk2) == 0) {
              czekaj = 0;
              EEPROM.update(8, klawisz);
              przycisk2_z = klawisz;
            }else {
              czekaj++;
            }
            if (digitalRead(przycisk3) == 0) {
              czekaj = 0;
              EEPROM.update(9, klawisz);
              przycisk3_z = klawisz;
            }else {
              czekaj++;
            }
          if(czekaj > 1000) {
            aplikacje[0] = 0;
            s_ust = 0;
            czekaj = 0;
            Clear();
          }
        }if (s_ust == 5) {
          Cursor(0, 2);
          print("System dziala przez: ", "System works for: ");
          Cursor(0, 3);
          print_o(millis());
          print_o("ms");
          print_o('/');
          print_o(millis() / 1000);
          print_o('s');
          print_o('/');
          Cursor(0, 0);
          print_o(millis() / 60000);
          print_o("min");
          print_o('/');
          print_o(millis() / 3600000);
          print_o("h");
        }if(s_ust == 6) {
          Cursor(0, 0);
          print(F("Napiecie: "), F("Voltage: "));
          long n = readVcc();
          print_o(n);
        }

      }if (aplikacje[0] == 3) {
        if (s_wa == 0) {
        Cursor(0, 2);
        print("Zegar", "Clock");
        Cursor(0, 3);
        print("Ustawienia", "Settings");
        Cursor(0, 0);
        print("Dinozaur", "Dino");
}if (s_wa == 1) {
          Cursor(0, 2);
          print("Pliki", "Files");
          Cursor(0, 3);
          print("Notatnik", "Notes");
          Cursor(0, 0);
          print_o("Port");
        }
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
          if (s_wa == 0) {
          if (kursor_y == 2) {
            aplikacje[0] = 1;
          }if (kursor_y == 3) {
            aplikacje[0] = 2;
          }if (kursor_y == 0) {
            aplikacje[0] = 4;
          }} if (s_wa == 1) {
            if (kursor_y == 2) {
              aplikacje[0] = 5;
            }if (kursor_y == 3) {
              aplikacje[0] = 6;
            }if (kursor_y == 0) {
              aplikacje[0] = 9;
            }
          }
        }if (klawisz == 16) {
          if (s_wa == 0) {
            if (kursor_y == 2) {
            ulubione1 = 1;
            EEPROM.update(3, 1);
          }if (kursor_y == 3) {
            ulubione1 = 2;
            EEPROM.update(3, 2);
          }if (kursor_y == 0) {
            ulubione1 = 4;
            EEPROM.update(3, 4);
          }}if (s_wa == 1) {
            if (kursor_y == 2) {
              EEPROM.update(3, 5);
              ulubione1 = 5;
            }if (kursor_y == 3) {
              EEPROM.update(3, 6);
              ulubione1 = 6;
            }if (kursor_y == 0) {
              EEPROM.update(3, 9);
              ulubione1 = 9;
            }
          }
        }if (klawisz == 18) {
          if (s_wa == 0) {
            if (kursor_y == 2) {
            ulubione2 = 1;
            EEPROM.update(4, 1);
          }if (kursor_y == 3) {
            ulubione2 = 2;
            EEPROM.update(4, 2);
          }if (kursor_y == 0) {
            ulubione2 = 4;
            EEPROM.update(4, 4);
          }}if (s_wa == 1) {
            if (kursor_y == 2) {
              EEPROM.update(4, 5);
              ulubione2 = 5;
            }if (kursor_y == 3) {
              EEPROM.update(4, 6);
              ulubione2 = 6;
            }if (kursor_y == 0) {
              EEPROM.update(4, 9);
              ulubione2 = 9;
            }
          }
        }if (klawisz == 13) {
          if (s_wa == 0) {
            if (kursor_y == 2) {
            ulubione3 = 1;
            EEPROM.update(11, 1);
          }if (kursor_y == 3) {
            ulubione3 = 2;
            EEPROM.update(11, 2);
          }if (kursor_y == 0) {
            ulubione3 = 4;
            EEPROM.update(11, 4);
          }}if (s_wa == 1) {
            if (kursor_y == 2) {
              EEPROM.update(11, 5);
              ulubione3 = 5;
            }if (kursor_y == 3) {
              EEPROM.update(11, 6);
              ulubione3 = 6;
            }if (kursor_y == 0) {
              EEPROM.update(11, 9);
              ulubione3 = 9;
            }
          }          
        }if (klawisz == 15) {
          if (s_wa == 0) {
            if (kursor_y == 2) {
            ulubione4 = 1;
            EEPROM.update(12, 1);
          }if (kursor_y == 3) {
            ulubione4 = 2;
            EEPROM.update(12, 2);
          }if (kursor_y == 0) {
            ulubione4 = 4;
            EEPROM.update(12, 4);
          }}if (s_wa == 1) {
            if (kursor_y == 2) {
              EEPROM.update(12, 5);
              ulubione4 = 5;
            }if (kursor_y == 3) {
              EEPROM.update(12, 6);
              ulubione4 = 6;
            }if (kursor_y == 0) {
              EEPROM.update(12, 9);
              ulubione4 = 9;
            }
          }
        }
        if (klawisz == 1) {
          s_wa--;
          Clear();
        }if (klawisz == 3) {
          s_wa++;
          Clear();
        }
      }if (aplikacje[0] == 4) {
        int klawisz = input();
        Cursor(0, y_d);
        lcd2.write(0);
        Cursor(x_k, 3);
        lcd2.write(1);
        Cursor(0, 0);
        print("wynik: ", "score: ");
        print_o(wynik);
        print_o(", ");
        print_o(EEPROM.read(5));

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
          if (x_k <= 0 && y_d == 3) {
            Cursor(0, 2);
            print("przegrales!", "you lose!");
          if (wynik > EEPROM.read(5)) {
          EEPROM.update(5, wynik);
        }
          }if (x_k <= 0 && y_d == 2) {
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
      }if (aplikacje[0] == 5) {
        int klawisz = input();
        if (n_plik == 0) {
        if (e_plik == 0) {
        if (klawisz == 1) {
          plik = plik - 76;

          Clear();
        }if (klawisz == 3) {
          plik = plik + 76;

          Clear();
        }
        if (EEPROM.read(plik) != 0) {

          Cursor(0, 2);
          if (EEPROM.read(plik + 1) == 2) {
          lcd2.write(2);}else if(EEPROM.read(plik + 1) >= 3) {
            lcd2.write(3);
          }else {
            if (EEPROM.read(plik) == 1) {
              lcd2.write(4);
            }if (EEPROM.read(plik) == 2) {
              lcd2.write(5);
            }if (EEPROM.read(plik) == 3) {
              lcd2.write(6);
            }if (EEPROM.read(plik) == 4) {
              lcd2.write(7);
            }
          }
          print_o(char(EEPROM.read(plik + 3)));
          print_o(char(EEPROM.read(plik + 4)));
          print_o(char(EEPROM.read(plik + 5)));
          print_o(char(EEPROM.read(plik + 6)));
          print_o(char(EEPROM.read(plik + 7)));
          print_o(char(EEPROM.read(plik + 8)));
          print_o(char(EEPROM.read(plik + 9)));
          print_o(char(EEPROM.read(plik + 10)));
          print_o(char(EEPROM.read(plik + 11)));
        }
        Cursor(0, 0);
        print("+ - nowy plik", "+ - new file");
        Cursor(0, 3);
        print("- - opcje", "- - settings");
        if (klawisz == 8) {
          n_plik = 1;
          Clear();
        }
        if (klawisz == 7) {
          e_plik = 1;
          Clear();
        }}else {
          if (naz_pliku == 0){
          Cursor(0, 2);
          if (EEPROM.read(plik + 1) == 1) {
          print("1. Usun", "1. Delete");}else if (EEPROM.read(plik + 1) == 2){
            print("1. Przywroc", "1. Restore");
          }else {
            print("1. Napraw", "1. Repair");
          }
          Cursor(0, 3);
          print("2. Zmien nazwe", "2. Change name");
          Cursor(0, 0);
          print(F("3. Otworz, 4. Powrot"), F("3. Open, 4. Back"));
          int klawisz = input();
          if (klawisz == 13) {
            if (EEPROM.read(plik + 1) == 1) {
              EEPROM.update(plik + 1, 2);
            }else if (EEPROM.read(plik + 1) == 2){
              EEPROM.update(plik + 1, 1);
            }else {
              for (int i = 3; i < 76; i++) {
                uint8_t napraw = EEPROM.read(i + plik);
                if (EEPROM.read(plik) == 1) {
                  if (napraw < 30) {
                    EEPROM.update(plik + i, napraw + 20);
                  }
                }

              }
              for (int i = 3; i < 76; i++) {
                uint8_t napraw = EEPROM.read(i + plik);
                if (EEPROM.read(plik) == 1) {
                  if (napraw > 125) {
                    EEPROM.update(plik + i, napraw - 30);
                  }
                }

              }
              EEPROM.update(plik + 1, 1);
            }
          }if (klawisz == 14) {
            naz_pliku = 1;
          }if (klawisz == 15) {
            if (EEPROM.read(plik) == 1) {
              aplikacje[0] = 6;
              i_notka = 12;
              Clear();
            }if (EEPROM.read(plik) == 4) {
              aplikacje[0] = 7;
              i_kodu = 12;
              Clear();
            }if (EEPROM.read(plik) == 2) {
              aplikacje[0] = 8;
              fullscreen = 1;
              i_kodu = 12;
              Clear();
            }
          }if (klawisz == 16) {
            e_plik = 0;
            Clear();
          }if (klawisz == 17) {
            for (int i = 0; i < 76; i++) {
              if (EEPROM.read(plik + i) < 100) {
                Serial.print('0');
              }if (EEPROM.read(plik + i) < 10) {
                Serial.print('0');
              }
              Serial.print(EEPROM.read(plik + i));
            }
          }} else {
                        Cursor(0, 2);
            print("nazwa pliku", "file name");
            Cursor(0, 3);
            keyboard = 1;
            char t = Keyboard();
            
            if (int(t) != 0) {
              char t1 = t;
              i_pliku++;
              if (i_pliku == 0){
              EEPROM.update(plik + 3, t1);}
              if (i_pliku == 1){
                EEPROM.update(plik + 4, t1);
              }if (i_pliku == 2) {
                EEPROM.update(plik + 5, t1);
              }if (i_pliku == 3) {
                EEPROM.update(plik + 6, t1);
              }if (i_pliku == 4) {
                EEPROM.update(plik + 7, t1);
              }if (i_pliku == 5) {
                EEPROM.update(plik + 8, t1);
              }if (i_pliku == 6) {
                EEPROM.update(plik + 9, t1);
              }if (i_pliku == 7) {
                EEPROM.update(plik + 10, t1);
              }if (i_pliku == 8) {
                EEPROM.update(plik + 11, t1);

              }if (i_pliku > 8) {
                e_plik = 0;
                naz_pliku = 0;
                i_pliku = 0;
                Clear();

              }
              
              print_o(char(EEPROM.read(plik + 3)));
              print_o(char(EEPROM.read(plik + 4)));
              print_o(char(EEPROM.read(plik + 5)));
              print_o(char(EEPROM.read(plik + 6)));
              print_o(char(EEPROM.read(plik + 7)));
              print_o(char(EEPROM.read(plik + 8)));
              print_o(char(EEPROM.read(plik + 9)));
              print_o(char(EEPROM.read(plik + 10)));
              print_o(char(EEPROM.read(plik + 11)));
              }
          }
        }}else {
          if (s_pliku == 0) {
            i_notka = 12;
          for (int i = 64; i < EEPROM.length(); i = i + 76) {
            if (EEPROM.read(i) == 0) {
              plik = i;

              break;
            }else if (EEPROM.read(i + 1) == 2) {
              plik = i;
              break;

            }

          
          }if (plik >= EEPROM.length() - 76) {
            print("brak miejsca, usun cos!", "no space, delete sth!");
            s_pliku = 0;
            i_pliku = 0;
            n_plik = 0;

          }
          if (o_s_pliku == 0) {
            Cursor(0, 2);
            print("Wybierz", "Choose");
            Cursor(0, 3);
            print("Stworz plik", "Create file");
            Cursor(0, 0);
            print("Zaladuj plik", "Load file");
            if (klawisz == 13) {
              o_s_pliku = 1;
            }if (klawisz == 14) {
              o_s_pliku = 2;
            }
          }
          if (o_s_pliku == 1) {
          Cursor(0, 2);
          print("wybierz typ", "choose type");
          Cursor(0, 3);
          print("wybrany typ: ", "choosed type: ");
          Cursor(0, 0);
          if (t_pliku == 1) {
            print("notatka", "note");
          }if (t_pliku == 2) {
            print("aplikacja", "app");
          }if (t_pliku == 3) {
            print("dane", "data");
          }if (t_pliku == 4) {
            print("kod", "code");
          }
          print("(5 - dalej)", "(5 - next)");
          if (klawisz == 13) {
            t_pliku = 1;
            Clear();
          }if (klawisz == 14) {
            t_pliku = 2;
            Clear();
          }if (klawisz == 15) {
            t_pliku = 3;
            Clear();
          }if (klawisz == 16) {
            t_pliku = 4;
            Clear();
          }if (klawisz == 17) {
            s_pliku = 1;
            Clear();
          }}if (o_s_pliku == 2) {
            plik_wg = Serial.read();
            kod = kod * 10 + plik_wg - 48;
            if (plik_wg != -49) {
            liczba++;

            if (liczba == 3) {
              EEPROM.update(plik + i_wg, kod);
              kod = 0;
              liczba = 0;
              i_wg++;
              if(i_wg > 76) {
                o_s_pliku = 0;
                n_plik = 0;
                i_wg = 0;
              }
            }}

          }}else {
            Cursor(0, 2);
            print(F("nazwa pliku"), F("file name"));
            Cursor(0, 3);
            keyboard = 1;
            char t = Keyboard();
            
            if (int(t) != 0) {
              char t1 = t;
              i_pliku++;
              if (i_pliku == 0){
              EEPROM.update(plik + 3, t1);}
              if (i_pliku == 1){
                EEPROM.update(plik + 4, t1);
              }if (i_pliku == 2) {
                EEPROM.update(plik + 5, t1);
              }if (i_pliku == 3) {
                EEPROM.update(plik + 6, t1);
              }if (i_pliku == 4) {
                EEPROM.update(plik + 7, t1);
              }if (i_pliku == 5) {
                EEPROM.update(plik + 8, t1);
              }if (i_pliku == 6) {
                EEPROM.update(plik + 9, t1);
              }if (i_pliku == 7) {
                EEPROM.update(plik + 10, t1);
              }if (i_pliku == 8) {
                EEPROM.update(plik + 11, t1);

              }if (i_pliku > 8) {
                EEPROM.update(plik, t_pliku);
                EEPROM.update(plik + 1, 1);
                n_plik = 0;
                Clear();
                s_pliku = 0;
                i_pliku = 0;
              }
              
              print_o(char(EEPROM.read(plik + 3)));
              print_o(char(EEPROM.read(plik + 4)));
              print_o(char(EEPROM.read(plik + 5)));
              print_o(char(EEPROM.read(plik + 6)));
              print_o(char(EEPROM.read(plik + 7)));
              print_o(char(EEPROM.read(plik + 8)));
              print_o(char(EEPROM.read(plik + 9)));
              print_o(char(EEPROM.read(plik + 10)));
              print_o(char(EEPROM.read(plik + 11)));
              }

          }
        }
      }if (aplikacje[0] == 6) {
        if (EEPROM.read(plik) != 1) {
          plik = plik + 76;
        }
        Clear();
                for (int i = 0; i < i_notka - 13; i++) {
        lcd2.scrollDisplayLeft();}
        for (int i = 12; i < 76; i++) {
        print_o(char(EEPROM.read(plik + i)));}
              
            int klawisz = input();
      if (klawisz == 9) {
        i_notka--;

      }if (klawisz == 2) {
        aplikacje[0] = 0;
        Clear();
      }if (klawisz == 7) {
        s_keyboard--;
      }if (klawisz == 8) {
        s_keyboard++;
      }
      keyboard = 1;
      char t = Keyboard();
      if (int(t) != 0) {
        EEPROM.update(plik + i_notka, t);
        if (i_notka < 76) {
          i_notka++;
        }else {
          print("nie ma miejsca!", "no space!");
        }
        

      }

        
      }if (aplikacje[0] == 7) {

        if (opcje == 0) {
        Cursor(0, 2);
        if (i_kodu > 12) { if (EEPROM.read(i_kodu + plik - 3) == 4) {
          print_o("endif");
        }else if(EEPROM.read(i_kodu + plik - 3) == 5) {
          print_o("create file");
        }else if (EEPROM.read(i_kodu + plik - 3) == 1) {
          
            print_o("print");
          
          print_o(' ');
          print_o(char(EEPROM.read(i_kodu + plik - 2)));}else if(EEPROM.read(i_kodu + plik - 3) == 6) {
            print_o("lff");}if (plik == EEPROM.length()) {
            print(F("brak miejsca, usun cos!"), F("no space, delete sth!"));
      }else if (EEPROM.read(i_kodu + plik - 3) == 1) {
          
            print_o("print");
          
          print_o(' ');
          print_o(char(EEPROM.read(i_kodu + plik - 2)));}else if(EEPROM.read(i_kodu + plik - 3) == 6) {
            print_o(F("lff"));
            print_o(' ');
            print_o(EEPROM.read(i_kodu + plik - 2));
            print_o(" ");
            print_o(EEPROM.read(i_kodu + plik - 1));
          }else if (EEPROM.read(i_kodu + plik - 3) == 2) {
            print_o(F("set"));
            print_o(' ');
            print_o(EEPROM.read(i_kodu + plik - 2));
            print_o(' ');
            print_o(EEPROM.read(i_kodu + plik - 1));
          } else if (EEPROM.read(i_kodu + plik - 3) == 3) {
          print_o(F("if="));
          print_o(' ');
          print_o(EEPROM.read(i_kodu + plik - 2));
          print_o(' ');
          print_o(EEPROM.read(i_kodu + plik - 1));
        }else if(EEPROM.read(i_kodu + plik - 3) == 7) {
            print_o(F("w(t)f"));
            print_o(' ');
            print_o(EEPROM.read(i_kodu + plik - 2));
            print_o(" ");
            print_o(EEPROM.read(i_kodu + plik - 1));
          }else if(EEPROM.read(i_kodu + plik - 3) == 8){
            print_o("cursor_s");
            print_o(' ');
            print_o(EEPROM.read(i_kodu + plik - 2));
            print_o(" ");
            print_o(EEPROM.read(i_kodu + plik - 1));
          }else if(EEPROM.read(i_kodu + plik - 3) == 9) {
            print_o(F("clear"));
          }else if(EEPROM.read(i_kodu + plik - 3) == 10) {
          print_o(F("input"));
          print_o(' ');
          print_o(EEPROM.read(i_kodu + plik - 2));
          }else if(EEPROM.read(i_kodu + plik - 3) == 11) {
            print_o("ADD");
          }else if(EEPROM.read(i_kodu + plik - 3) == 12) {
            print_o("SUB");
          }else if(EEPROM.read(i_kodu + plik - 3) == 13) {
            print_o("*");
          }else if(EEPROM.read(i_kodu + plik - 3) == 14) {
            print_o("/");
          }else if(EEPROM.read(i_kodu + plik - 3) == 15) {
          print_o(F("lfp"));
          print_o(' ');
          print_o(EEPROM.read(i_kodu + plik - 2));
          }else if(EEPROM.read(i_kodu + plik - 3) == 16) {
            print_o("cursor_m");
          }else if(EEPROM.read(i_kodu + plik - 3) == 17) {
          print_o(F("stp"));
          print_o(' ');
          print_o(EEPROM.read(i_kodu + plik - 2));
          } }
        Cursor(0, 3);
        if (ob_kom == 1) {
          print_o("print");
            print_o(' ');
            print_o(t1_kodu);
          
        }
        if (ob_kom == 2) {
            print_o("set");
            print_o(' ');
            print_o(wybrana_w);
            print_o(' ');
            if (wybrana_w == 1) {
              print_o(wartosc1);
            }if (wybrana_w == 2) {
              print_o(wartosc2);
            }
            if (wybrana_w == 3) {
              print_o(wartosc3);
            }if (wybrana_w == 4) {
              print_o(wartosc4);
            }
        }
        if (ob_kom == 3) {
          print_o("if=");
          print_o(' ');
          print_o(wybrana_w);
          print_o(' ');
          print_o(wartosc);
        }
        if (ob_kom == 4) {
          print_o("endif");
        }if (ob_kom == 5) {
          print_o("create file");
        }if (ob_kom == 6) {
          print_o("lff");
          print_o(' ');
          print_o(wybrana_w);
          print_o(" ");
          print_o(bajt);

        }if (ob_kom == 7) {
          print_o("w(t)f");
          print_o(' ');
          print_o(wybrana_w);
          print_o(" ");
          print_o(bajt);
        }if (ob_kom == 8) {
          print_o("cursor_s");
          print_o(' ');
          print_o(x_kod);
          print_o(' ');
          print_o(y_kod);
        }if (ob_kom == 9) {
          print_o("clear");
        }if (ob_kom == 10) {
          print_o("input");
          print_o(' ');
          print_o(wybrana_w);
        }if (ob_kom == 11) {
          print_o("ADD");
        }if (ob_kom == 12) {
          print_o("SUB");
        }if (ob_kom == 13) {
          print_o("*");
        }if (ob_kom == 14) {
          print_o("/");
        }if (ob_kom == 15) {
          print_o(F("lfp"));
          print_o(' ');
          print_o(wybrana_w);
          print_o(' ');
          print_o(w_pin);
        }if (ob_kom == 16) {
          print_o("cursor_m");
        }if (ob_kom == 17) {
          print_o("stp");
          print_o(' ');
          print_o(wybrana_w);
          print_o(' ');
          print_o(w_pin);
        }
        int klawisz = input();
        /* lista komend:
          1 - print
          2 - set
          3 - if=
          4 - endif
          5 - create file
          6 - load from file (lff)
          7 - write to file (w(t)f)
          8 - kursor statyczny (nie mozna zmienic pozycji)
          9 - clear
          10 - input
          11 - dodawanie (tylko wartosc1 + wartosc2 = wartosc3)
          12 - odejmowanie (tylko wartosc1 - wartosc2 = wartosc3)
          13 - mnozenie (tylko wartosc1 * wartosc2 = wartosc3)
          14 - dzielenie (tylko wartosc1 / wartosc2 = wartosc3)
          15 - load from port (obecnie nieużywane)
          16 - kursor ruszający się (można zmienić pozycje, wykorzystuje wartosc3 i wartosc4 dla x i y)
          17 - send do port (obecnie nieużywane)
          */
          if(klawisz == 6) {
            warunki = !warunki;

          }
          if (klawisz == 4) {
            ob_kom = ob_kom - ostatnia_akcja;
          }
        if (warunki == 0) {
        if (klawisz == 13) {
          ob_kom = ob_kom + 1;
          ostatnia_akcja = 1;
          Clear();
        }if (klawisz == 14) {
          ob_kom = ob_kom + 2;
          klawisz = 0; 
          Clear();
          ostatnia_akcja = 2;
        }if (klawisz == 15) {
          ob_kom = ob_kom + 3; 
          klawisz = 0;
          Clear();
          ostatnia_akcja = 3;
        }if (klawisz == 16) {
          ob_kom = ob_kom + 4; 
          Clear();
          ostatnia_akcja = 4;
        }if (klawisz == 17) {
          ob_kom = ob_kom + 5;
          Clear(); 
          ostatnia_akcja = 5;
        }if (klawisz == 18) {
          ob_kom = ob_kom + 6;
          Clear(); 
          ostatnia_akcja = 6;
        }if (klawisz == 19) {
          ob_kom = ob_kom + 7;
          Clear(); 
          ostatnia_akcja = 7;
        }if (klawisz == 20) {
          ob_kom = ob_kom + 8;
          Clear();
          ostatnia_akcja = 8;
        }if (klawisz == 21) {
          ob_kom = ob_kom + 9;
          Clear();
          ostatnia_akcja = 9;
        }if (klawisz == 10) {
          ob_kom = ob_kom * 10;
        }}else {if (ob_kom == 1) {
          keyboard = 1;
  char keys[45] = {'1','2','3','4','5','6','7','8','9','0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','w','x','y','z','-','+','=','!','@','#','$','%','^','&',' '};
  int key = 0;
  int klawisz = input();
  if(klawisz == 8) {
    s_keyboard++;
    Clear();
  }if (klawisz == 7) {
    s_keyboard--;
    Clear();
  }

  if(keyboard == 1) {
    Cursor(0, 0);
    if (klawisz != 0) {
    print_o(keys[klawisz - 13 + 9 * s_keyboard]);
    key = keys[klawisz - 13 + 9 * s_keyboard];
    }
  }
  if (key != 0) {
  t1_kodu = key;}
        }if (ob_kom == 2 or ob_kom == 3 or ob_kom == 6 or ob_kom == 7 or ob_kom == 10 or ob_kom == 15 or ob_kom == 17) {
          if (wybrana_w == 0) {
          if (klawisz == 13) {
            wybrana_w = 1;
            
          }if (klawisz == 14) {
            wybrana_w = 2;
          }if (klawisz == 15) {
            wybrana_w = 3;
          }if (klawisz == 16) {
            wybrana_w = 4;
          }}
         if (ob_kom == 2) {
          if (wybrana_w != 0) {
            if (wybrana_w == 1) {
              if (klawisz == 13) {
                wartosc1 = wartosc1 * 10 + 1;
              }if (klawisz == 14) {
                wartosc1 = wartosc1 * 10 + 2;
              }if (klawisz == 15) {
                wartosc1 = wartosc1 * 10 + 3;
              }if (klawisz == 16) {
                wartosc1 = wartosc1 * 10 + 4;
              }if (klawisz == 17) {
                wartosc1 = wartosc1 * 10 + 5;
              }if (klawisz == 18) {
                wartosc1 = wartosc1 * 10 + 6;
              }if (klawisz == 19) {
                wartosc1 = wartosc1 * 10 + 7;
              }if (klawisz == 20) {
                wartosc1 = wartosc1 * 10 + 8;
              }if (klawisz == 21) {
                wartosc1 = wartosc1 * 10 + 9;
              }if (klawisz == 10) {
                wartosc1 = wartosc1 * 10;
              }
            }
            if (wybrana_w == 2) {
              if (klawisz == 13) {
                wartosc2 = wartosc2 * 10 + 1;
              }if (klawisz == 14) {
                wartosc2 = wartosc2 * 10 + 2;
              }if (klawisz == 15) {
                wartosc2 = wartosc2 * 10 + 3;
              }if (klawisz == 16) {
                wartosc2 = wartosc2 * 10 + 4;
              }if (klawisz == 17) {
                wartosc2 = wartosc2 * 10 + 5;
              }if (klawisz == 18) {
                wartosc2 = wartosc2 * 10 + 6;
              }if (klawisz == 19) {
                wartosc2 = wartosc2 * 10 + 7;
              }if (klawisz == 20) {
                wartosc2 = wartosc2 * 10 + 8;
              }if (klawisz == 21) {
                wartosc2 = wartosc2 * 10 + 9;
              }if (klawisz == 10) {
                wartosc2 = wartosc2 * 10;
              }
            }
            if (wybrana_w == 3) {
              if (klawisz == 13) {
                wartosc3 = wartosc3 * 10 + 1;
              }if (klawisz == 14) {
                wartosc3 = wartosc3 * 10 + 2;
              }if (klawisz == 15) {
                wartosc3 = wartosc3 * 10 + 3;
              }if (klawisz == 16) {
                wartosc3 = wartosc3 * 10 + 4;
              }if (klawisz == 17) {
                wartosc3 = wartosc3 * 10 + 5;
              }if (klawisz == 18) {
                wartosc3 = wartosc3 * 10 + 6;
              }if (klawisz == 19) {
                wartosc3 = wartosc3 * 10 + 7;
              }if (klawisz == 20) {
                wartosc3 = wartosc3 * 10 + 8;
              }if (klawisz == 21) {
                wartosc3 = wartosc3 * 10 + 9;
              }if (klawisz == 10) {
                wartosc3 = wartosc3 * 10;
              }
            }
            if (wybrana_w == 4) {
              if (klawisz == 13) {
                wartosc4 = wartosc4 * 10 + 1;
              }if (klawisz == 14) {
                wartosc4 = wartosc4 * 10 + 2;
              }if (klawisz == 15) {
                wartosc4 = wartosc4 * 10 + 3;
              }if (klawisz == 16) {
                wartosc4 = wartosc4 * 10 + 4;
              }if (klawisz == 17) {
                wartosc4 = wartosc4 * 10 + 5;
              }if (klawisz == 18) {
                wartosc4 = wartosc4 * 10 + 6;
              }if (klawisz == 19) {
                wartosc4 = wartosc4 * 10 + 7;
              }if (klawisz == 20) {
                wartosc4 = wartosc4 * 10 + 8;
              }if (klawisz == 21) {
                wartosc4 = wartosc4 * 10 + 9;
              }if (klawisz == 10) {
                wartosc4 = wartosc4 * 10;
              }
            }
          }
         } 
        }if (ob_kom == 3) {
          if(wybrana_w != 0) {
                          if (klawisz == 13) {
                wartosc = wartosc * 10 + 1;
              }if (klawisz == 14) {
                wartosc = wartosc * 10 + 2;
              }if (klawisz == 15) {
                wartosc = wartosc * 10 + 3;
              }if (klawisz == 16) {
                wartosc = wartosc * 10 + 4;
              }if (klawisz == 17) {
                wartosc = wartosc * 10 + 5;
              }if (klawisz == 18) {
                wartosc = wartosc * 10 + 6;
              }if (klawisz == 19) {
                wartosc = wartosc * 10 + 7;
              }if (klawisz == 20) {
                wartosc = wartosc * 10 + 8;
              }if (klawisz == 21) {
                wartosc = wartosc * 10 + 9;
              }if (klawisz == 10) {
                wartosc = wartosc * 10;
              }
          }
        }if (ob_kom == 6 or ob_kom == 7) {
          if (wybrana_w != 0) {
                          if (klawisz == 13) {
                bajt = bajt * 10 + 1;
              }if (klawisz == 14) {
                bajt = bajt * 10 + 2;
              }if (klawisz == 15) {
                bajt = bajt * 10 + 3;
              }if (klawisz == 16) {
                bajt = bajt * 10 + 4;
              }if (klawisz == 17) {
                bajt = bajt * 10 + 5;
              }if (klawisz == 18) {
                bajt = bajt * 10 + 6;
              }if (klawisz == 19) {
                bajt = bajt * 10 + 7;
              }if (klawisz == 20) {
                bajt = bajt * 10 + 8;
              }if (klawisz == 21) {
                bajt = bajt * 10 + 9;
              }if (klawisz == 10) {
                bajt = bajt * 10;
              }
          }
        }if (ob_kom == 8) {
          if(klawisz == 9) {
            mode = !mode;
          }if (mode == 0) {
            if (klawisz == 13) {
                x_kod = x_kod * 10 + 1;
              }if (klawisz == 14) {
                x_kod = x_kod * 10 + 2;
              }if (klawisz == 15) {
                x_kod = x_kod * 10 + 3;
              }if (klawisz == 16) {
                x_kod = x_kod * 10 + 4;
              }if (klawisz == 17) {
                x_kod = x_kod * 10 + 5;
              }if (klawisz == 18) {
                x_kod = x_kod * 10 + 6;
              }if (klawisz == 19) {
                x_kod = x_kod * 10 + 7;
              }if (klawisz == 20) {
                x_kod = x_kod * 10 + 8;
              }if (klawisz == 21) {
                x_kod = x_kod * 10 + 9;
              }if (klawisz == 10) {
                x_kod = x_kod * 10;
              }
          }else {
            if (klawisz == 13) {
                y_kod = y_kod * 10 + 1;
              }if (klawisz == 14) {
                y_kod = y_kod * 10 + 2;
              }if (klawisz == 15) {
                y_kod = y_kod * 10 + 3;
              }if (klawisz == 16) {
                y_kod = y_kod * 10 + 4;
              }if (klawisz == 17) {
                y_kod = y_kod * 10 + 5;
              }if (klawisz == 18) {
                y_kod = y_kod * 10 + 6;
              }if (klawisz == 19) {
                y_kod = y_kod * 10 + 7;
              }if (klawisz == 20) {
                y_kod = y_kod * 10 + 8;
              }if (klawisz == 21) {
                y_kod = y_kod * 10 + 9;
              }if (klawisz == 10) {
                y_kod = y_kod * 10;
              }
          }
        }if (ob_kom == 15 or ob_kom == 17) {
          if (wybrana_w != 0) {
              if (klawisz > 12) {
              w_pin = klawisz - 12;}
            
          }
        }}
        if (klawisz == 1) {
          i_kodu = i_kodu - 3;
          if (i_kodu < 12) {
            i_kodu = 12;
          }
        }
        if (klawisz == 5) {
          opcje = 1;

        }
        if (klawisz == 11) {
          if (ob_kom == 1) {
          EEPROM.update(i_kodu + plik, ob_kom);
          EEPROM.update(i_kodu + plik + 1, t1_kodu);
          } if (ob_kom == 2) {
            EEPROM.update(i_kodu + plik, ob_kom);
            EEPROM.update(i_kodu + plik + 1, wybrana_w);
            if (wybrana_w == 1) {
            EEPROM.update(i_kodu + plik + 2, wartosc1);}
            if (wybrana_w == 2) {
            EEPROM.update(i_kodu + plik + 2, wartosc2);}
            if (wybrana_w == 3) {
            EEPROM.update(i_kodu + plik + 2, wartosc3);}
            if (wybrana_w == 4) {
            EEPROM.update(i_kodu + plik + 2, wartosc4);}   
            
            wybrana_w = 0;
            wartosc1 = 0;
            wartosc2 = 0;
            wartosc3 = 0;
            wartosc4 = 0;
          }if (ob_kom == 3) {
            EEPROM.update(i_kodu + plik, 3);
            EEPROM.update(i_kodu + plik + 1, wybrana_w);
            EEPROM.update(i_kodu + plik + 2, wartosc);
            
            wybrana_w = 0;
            wartosc = 0;
          }if (ob_kom == 4) {
            EEPROM.update(i_kodu + plik, 4);
            
          }if (ob_kom == 5) {
            EEPROM.update(i_kodu + plik, 5);
            
          }if (ob_kom == 6) {
            EEPROM.update(i_kodu + plik, 6);
            EEPROM.update(i_kodu + plik + 1, wybrana_w);
            EEPROM.update(i_kodu + plik + 2, bajt);
            
            wybrana_w = 0;
            bajt = 0;
          }if (ob_kom == 7) {
            EEPROM.update(i_kodu + plik, 7);
            EEPROM.update(i_kodu + plik + 1, wybrana_w);
            EEPROM.update(i_kodu + plik + 2, bajt);
            
            wybrana_w = 0;
            bajt = 0;
          }if (ob_kom == 8) {
            EEPROM.update(i_kodu + plik, 8);
            EEPROM.update(i_kodu + plik + 1, x_kod);
            EEPROM.update(i_kodu + plik + 2, y_kod);
            x_kod = 0;
            y_kod = 0;
            mode = 0;
          }if (ob_kom == 9) {
            EEPROM.update(i_kodu + plik, 9);
          }if (ob_kom == 10) {
            EEPROM.update(i_kodu + plik, 10);
            EEPROM.update(i_kodu + plik + 1, wybrana_w);
            wybrana_w = 0;
          }if (ob_kom == 11) {
            EEPROM.update(i_kodu + plik, 11);
          }if (ob_kom == 12) {
            EEPROM.update(i_kodu + plik, 12);
          }if (ob_kom == 13) {

            EEPROM.update(i_kodu + plik, 13);

          }if (ob_kom == 14) {
            EEPROM.update(i_kodu + plik, 14);
          }if (ob_kom == 15) {
            EEPROM.update(i_kodu + plik, 15);
            EEPROM.update(i_kodu + plik + 1, wybrana_w);
            EEPROM.update(i_kodu + plik + 2, w_pin);
            wybrana_w = 0;
          }if (ob_kom == 16) {
            EEPROM.update(i_kodu + plik, 16);
          }if (ob_kom == 17) {
            EEPROM.update(i_kodu + plik, 17);
            EEPROM.update(i_kodu + plik + 1, wybrana_w);
            EEPROM.update(i_kodu + plik + 2, w_pin);
            wybrana_w = 0;
          }
          Clear();
          ob_kom = 0; 
          i_kodu = i_kodu + 3;
          warunki = 0;
        }
      }else {
        Cursor(0, 2);
        print(F("1. Uruchom"), F("1. Run"));
        Cursor(0, 3);
        print(F("2. Zamien na aplikacje"), F("2. change to app"));
        int klawisz = input();
        if (klawisz == 13) {
          uruchamianie = 1;
          
        }if (klawisz == 14) {
          uruchamianie = 2;
         
        }
        if (uruchamianie == 1) {
          aplikacje[0] = 8;
          opcje = 0;
          i_kodu = 12;
          fullscreen = 1;
          Clear();
        }if (uruchamianie == 2) {
          EEPROM.update(plik, 2);
          aplikacje[0] = 8;
          opcje = 0;
          i_kodu = 12;
          fullscreen = 1;
          Clear();
        }
        
      }}if (aplikacje[0] == 8) {
        if (EEPROM.read(plik + i_kodu) == 1) {
          if (x < 2) {
          print_o(char(EEPROM.read(plik + i_kodu + 1)));}else {
            print_o(char(EEPROM.read(plik + i_kodu + 1)));
          }
        }if(EEPROM.read(plik + i_kodu) == 2) {
          if (EEPROM.read(plik + i_kodu + 1) == 1) {
            wartosc1 = EEPROM.read(plik + i_kodu + 2);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 2) {
            wartosc2 = EEPROM.read(plik + i_kodu + 2);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 3) {
            wartosc3 = EEPROM.read(plik + i_kodu + 2);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 4) {
            wartosc4 = EEPROM.read(plik + i_kodu + 2);
          }
          

        }if (EEPROM.read(plik + i_kodu) == 3) {
          if (EEPROM.read(plik + i_kodu + 1) == 1) {
            if (wartosc1 != EEPROM.read(plik + i_kodu + 2)) {

              while(EEPROM.read(plik + i_kodu) != 4) {

                i_kodu = i_kodu + 3;
              }
            }
          }
          if (EEPROM.read(plik + i_kodu + 1) == 2) {
            if (wartosc2 != EEPROM.read(plik + i_kodu + 2)) {

              while(EEPROM.read(plik + i_kodu) != 4) {

                i_kodu = i_kodu + 3;
              }
            }
          }
          if (EEPROM.read(plik + i_kodu + 1) == 3) {
            if (wartosc3 != EEPROM.read(plik + i_kodu + 2)) {

              while(EEPROM.read(plik + i_kodu) != 4) {

                i_kodu = i_kodu + 3;
              }
            }
          }
          if (EEPROM.read(plik + i_kodu + 1) == 4) {
            if (wartosc4 != EEPROM.read(plik + i_kodu + 2)) {
              while(EEPROM.read(plik + i_kodu) != 4) {

                i_kodu = i_kodu + 3;
              }
            }

          }
        }if (EEPROM.read(plik + i_kodu) == 5) {
          if(EEPROM.read(plik + 76) == 0 or EEPROM.read(plik + 77) == 2) {
            i_kodu_p = plik + 76;
          EEPROM.update(i_kodu_p, 3);
          EEPROM.update(i_kodu_p + 1, 1);
          EEPROM.update(i_kodu_p + 2, 'd');
          EEPROM.update(i_kodu_p + 3, 'a');
          EEPROM.update(i_kodu_p + 4, 't');
          EEPROM.update(i_kodu_p + 5, 'a');
          for(int i = 6; i < 12; i++) {
            EEPROM.update(i_kodu_p + i, EEPROM.read(plik + i));
          }}else if (EEPROM.read(plik + 76) == 3) {
            i_kodu_p = plik + 76;

          }else {
            print(F("Usun plik nad aplikacja aby aplikacja mogla zapisac dane"), F("Delete file above app so app can save data"));
          }
        }if (EEPROM.read(plik + i_kodu) == 6) {
          bajt = EEPROM.read(plik + i_kodu + 2);         
          if (EEPROM.read(plik + i_kodu + 1) == 1) {
            wartosc1 = EEPROM.read(i_kodu_p + 12 + bajt);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 2) {
            wartosc2 = EEPROM.read(i_kodu_p + 12 + bajt);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 3) {
            wartosc3 = EEPROM.read(i_kodu_p + 12 + bajt);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 4) {
            wartosc4 = EEPROM.read(i_kodu_p + 12 + bajt);
          }

        }if (EEPROM.read(plik + i_kodu) == 7) {
          bajt = EEPROM.read(plik + i_kodu + 2);
          if (EEPROM.read(plik + i_kodu + 1) == 1) {

            EEPROM.update(i_kodu_p + 12 + bajt, wartosc1);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 2) {

            EEPROM.update(i_kodu_p + 12 + bajt, wartosc2);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 3) {

            EEPROM.update(i_kodu_p + 12 + bajt, wartosc3);
          }
          if (EEPROM.read(plik + i_kodu + 1) == 4) {

            EEPROM.update(i_kodu_p + 12 + bajt, wartosc4);
          }
          
        }if (EEPROM.read(plik + i_kodu) == 8) {
          Cursor(EEPROM.read(plik + i_kodu + 1), EEPROM.read(plik + i_kodu + 2));
        }if (EEPROM.read(plik + i_kodu) == 9) {
          Clear();
        }if (EEPROM.read(plik + i_kodu) == 10) {
          if (EEPROM.read(plik + i_kodu + 1) == 1) {
            wartosc1 = input();
          }if (EEPROM.read(plik + i_kodu + 1) == 2) {
            wartosc2 = input();
          }
          if (EEPROM.read(plik + i_kodu + 1) == 3) {
            wartosc3 = input();
          }
          if (EEPROM.read(plik + i_kodu + 1) == 4) {
            wartosc4 = input();
          }

        }if (EEPROM.read(plik + i_kodu) == 11) {
          wartosc3 = wartosc1 + wartosc2;

        }if (EEPROM.read(plik + i_kodu) == 12) {
          wartosc3 = wartosc1 - wartosc2;

        }if (EEPROM.read(plik + i_kodu) == 13) {
          wartosc3 = wartosc1 * wartosc2;

        }if (EEPROM.read(plik + i_kodu) == 14) {
          wartosc3 = wartosc1 / wartosc2;

        }if (EEPROM.read(plik + i_kodu) == 15) {
          if (port_u == 0) {
            if (EEPROM.read(plik + i_kodu + 1) == 1) {
              if (EEPROM.read(plik + i_kodu + 2) == 1) {
                wartosc1 = analogRead(PIN1);
              }if (EEPROM.read(plik + i_kodu + 2) == 2) {
                wartosc1 = analogRead(PIN2);
              }if (EEPROM.read(plik + i_kodu + 2) == 3) {
                wartosc1 = digitalRead(PIN3);
              }
            }            if (EEPROM.read(plik + i_kodu + 1) == 2) {
              if (EEPROM.read(plik + i_kodu + 2) == 1) {
                wartosc2 = analogRead(PIN1);
              }if (EEPROM.read(plik + i_kodu + 2) == 2) {
                wartosc2 = analogRead(PIN2);
              }if (EEPROM.read(plik + i_kodu + 2) == 3) {
                wartosc2 = digitalRead(PIN3);
              }
            }            if (EEPROM.read(plik + i_kodu + 1) == 3) {
              if (EEPROM.read(plik + i_kodu + 2) == 1) {
                wartosc3 = analogRead(PIN1);
              }if (EEPROM.read(plik + i_kodu + 2) == 2) {
                wartosc3 = analogRead(PIN2);
              }if (EEPROM.read(plik + i_kodu + 2) == 3) {
                wartosc3 = digitalRead(PIN3);
              }
            }            if (EEPROM.read(plik + i_kodu + 1) == 4) {
              if (EEPROM.read(plik + i_kodu + 2) == 1) {
                wartosc4 = analogRead(PIN1);
              }if (EEPROM.read(plik + i_kodu + 2) == 2) {
                wartosc4 = analogRead(PIN2);
              }if (EEPROM.read(plik + i_kodu + 2) == 3) {
                wartosc4 = digitalRead(PIN3);
              }
            }
          }if (port_u == 1) {

              double Distance = getDistance();

            if (EEPROM.read(plik + i_kodu + 1) == 1) {
              wartosc1 = Distance;
            }            if (EEPROM.read(plik + i_kodu + 1) == 2) {
              wartosc2 = Distance;
            }            if (EEPROM.read(plik + i_kodu + 1) == 3) {
              wartosc3 = Distance;
            }            if (EEPROM.read(plik + i_kodu + 1) == 4) {
              wartosc4 = Distance;
            }
          }if (port_u == 2) {
              if (EEPROM.read(plik + i_kodu + 1) == 1) {
                wartosc1 = digitalRead(PIN1);
              }
              if (EEPROM.read(plik + i_kodu + 1) == 2) {
                wartosc2 = digitalRead(PIN1);
              }              if (EEPROM.read(plik + i_kodu + 1) == 3) {
                wartosc3 = digitalRead(PIN1);
              }              if (EEPROM.read(plik + i_kodu + 1) == 4) {
                wartosc4 = digitalRead(PIN1);
              }
            }
        }if (EEPROM.read(plik + i_kodu) == 16) {
          Cursor(wartosc3, wartosc4);
        }if (EEPROM.read(plik + i_kodu) == 17) {
         if (port_u == 3) {

            if (EEPROM.read(plik + i_kodu + 2) == 1) {
              digitalWrite(PIN1, wartosc1);
            }if (EEPROM.read(plik + i_kodu + 2) == 2) {
              digitalWrite(PIN2, wartosc1);
            }if (EEPROM.read(plik + i_kodu + 2) == 3) {
              digitalWrite(PIN3, wartosc1);
            }
         }
        }
        i_kodu = i_kodu + 3;
      }if (aplikacje[0] == 9) {
        fullscreen = 1;
        if (opcje_port == 0) {
          EEPROM.update(10, port_u);
        Cursor(0, 2);
        print(F("1. Wykryj automatycznie"), F("1. Detect"));
        Cursor(0, 3);
        print("2. Ustaw", "2. Set");
        Cursor(0, 0);
        print_o("3. Test");
        Cursor(0, 1);
if (port_u == 0) {
  pinMode(PIN1, INPUT);
  pinMode(PIN2, INPUT);
  pinMode(PIN3, INPUT_PULLUP);
  print_o(F("tryb portu: joystick"));
}if (port_u == 1) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, INPUT);
  digitalWrite(PIN1, LOW);
  print_o(F("tryb portu: czujnik odleglosci"));
}if (port_u == 2) {
  pinMode(PIN1, INPUT_PULLUP);
  print_o(F("tryb portu: bali switch"));
}if (port_u == 3) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
  print_o(F("tryb portu: dioda RGB"));
}if (port_u > 3) {
  print_o(F("???"));
}
        int klawisz = input();
        if (klawisz == 13) {
          opcje_port = 1;
        }if (klawisz == 14) {
          opcje_port = 2;
        }if (klawisz == 15) {
          opcje_port = 3;
        }}if (opcje_port == 1) {
          port_u = 0;
          if (port_u == 0) {
            pinMode(PIN1, INPUT);
            pinMode(PIN2, INPUT);
            pinMode(PIN3, INPUT_PULLUP);
          if (analogRead(PIN1) - 505 > -1 and analogRead(PIN2) - 521 > -1) {
            port_u = 0;
            opcje_port = 0;
          }else {
            port_u = 1;
          }}if (port_u == 1) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, INPUT);

double Distance = getDistance();


if (Distance > 170) {
  port_u = 1;
  opcje_port = 0;
}else {
  port_u = 2;
}
          }if (port_u == 2) {
                pinMode(PIN1, INPUT_PULLUP);
            if (digitalRead(PIN1) == 1) {
              port_u = 2;
              opcje_port = 0;
            }else {
                pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
              port_u = 3;
              opcje_port = 0;
            }
          }
        }if (opcje_port == 2) {
            EEPROM.update(10, port_u);
          if (klawisz == 13) {
            port_u = 0;
          }if (klawisz == 14) {
            port_u = 1;
          }if (klawisz == 15) {
            port_u = 2;
          }if (klawisz == 16) {
            port_u = 3;
          }Cursor(0, 0);
          setPort();
if (port_u == 0) {
  print_o(F("tryb portu: joystick"));
}if (port_u == 1) {
  print_o(F("tryb portu: czujnik odleglosci"));
}if (port_u == 2) {
  print_o(F("tryb portu: bali switch"));
}if (port_u == 3) {
  print_o(F("tryb portu: dioda RGB"));
}if (port_u > 3) {
  print_o(F("???"));
}
        }if (opcje_port == 3) {
          Cursor(0, 2);
          print_o("test podlaczonego urzadzenia...");
          Cursor(0, 3);
          if (port_u == 0) {
            print_o(analogRead(PIN1) - 505);
            print_o(analogRead(PIN2) - 521);
          }if (port_u == 1) {

double Distance = getDistance();

print("Dystans: ", "Distance: ");
print_o(Distance);
print_o("cm");
          }if (port_u == 2) {
            print_o(digitalRead(PIN1));
          }if (port_u == 3) {
            print_o("czerwony");
            digitalWrite(PIN1, HIGH);
            digitalWrite(PIN2, LOW);
            digitalWrite(PIN3, LOW);
            delay(200);
            Clear();
            print_o("zielony");
            digitalWrite(PIN1, LOW);
            digitalWrite(PIN2, HIGH);
            digitalWrite(PIN3, LOW);
            delay(200);
            Clear();
            print_o("niebieski");
            digitalWrite(PIN1, LOW);
            digitalWrite(PIN2, LOW);
            digitalWrite(PIN3, HIGH);
            delay(200);
            Clear();
            opcje_port = 0;
          }
        }
      }if (aplikacje[0] == -1) {
        
        if (port_u == 3) {
          digitalWrite(PIN1, HIGH);
          digitalWrite(PIN2, LOW);
          digitalWrite(PIN3, LOW);
        }
        if (blad == 1) {
        Cursor(0, 2);
        print_o("Error 0x0!");          

}if (blad == 2) {
          Cursor(0, 2);
          print_o("Error 0x1!");

        }
        Cursor(0, 3);
        unsigned long czas = millis() + 2000;
        wdt_enable(WDTO_2S);
        while(1) {
          Cursor(0, 0);
         print_o(czas - millis());
        Cursor(0, 3);           
        print_o(2048 - freeRam());
        
      }}

}}
  



