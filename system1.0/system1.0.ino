

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
#include <EEPROM.h>
#define LED 10
#define LED2 11
#define LED3 12
int aplikacja = 0;
byte uspienie_czas = EEPROM.read(0);
int sekundy = EEPROM.read(1);
int minuty = EEPROM.read(2);
int godziny = EEPROM.read(3);
int zajete1 = EEPROM.read(4);
int zajete2 = EEPROM.read(5);
uint16_t wynik = 0;
bool scroll = 0;
int i1 = 0;
int i2 = 0;
bool start = 1;
bool next = 0;
int numer = 1;
int wybor = 0;
int ustaw_m = 0;// nie udalo sie zrobic zapisu dla plikow
int ustaw_g = 0;
int ustawienia = 0;
int menuw = 0;
bool plik = 0;
int x = 15;
int y = 1;
bool y1 = 0;
bool y2 = 0;
int roznicawynik = 0;
char s = 0;
char znakk = 'a';
int iz = 65;
bool y1p = 0;
bool y2p = 0;
int x1 = 0;
int x2 = 0;
int menuk = 0;
String skladnik1 = "0";
String skladnik2 = "0";
int dzialanie = 0;
String zawartosc = EEPROM.get(6, zawartosc);
bool y_myszki = 0;
char znak = 'a';
int znak2 = 1;
int menu = 0;
int menuu = 0;
int frame = 0;
unsigned long aktualnyCzas = 0;

unsigned long zapamietanyCzas = 0;

unsigned long roznicaCzasu = 0;
unsigned long aktualnyCzas2 = 0;

unsigned long zapamietanyCzas2 = 0;

unsigned long roznicaCzasu2 = 0;
unsigned long aktualnyCzas3 = 0;

unsigned long zapamietanyCzas3 = 0;

unsigned long roznicaCzasu3 = 0;

unsigned long aktualnyCzas4 = 0;

unsigned long zapamietanyCzas4 = 0;

unsigned long roznicaCzasu4 = 0;
unsigned long aktualnyCzas5 = 0;

unsigned long zapamietanyCzas5 = 0;

unsigned long roznicaCzasu5 = 0;
unsigned long czas = 0;
unsigned long czas2 = 1000;
int ostatniwynik = 0;
int x_kursora = 0;
bool y_kursora = 0;
int najlepszy = EEPROM.get(207, najlepszy);
int opinia = 0;
int opinia2 = EEPROM.read(209);
int ulubionaap1 = EEPROM.read(210);
int ulubionaap2 = EEPROM.read(211);
int ulubionaap3 = EEPROM.read(212);
int ulubionaap4 = EEPROM.read(213);
int ulubionaap5 = EEPROM.read(214);
int ulubionaap6 = EEPROM.read(215);
int ulubionaap7 = EEPROM.read(216);
int ulubionaap8 = EEPROM.read(217);
const byte ROWS = 4; 
int ik = 229;// 218 - 228 wartosci niestandardowych zmiennych
const byte COLS = 4; 
bool uspienie = 0;
byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {6, 7, 8, 9};

int temperatura1 = 0;
int wybort = 0;
int temperatura2 = 0;
char keys[ROWS][COLS] = {

  {'A','3','2','1'},

  {'B','6','5','4'},

  {'C','9','8','7'},

  {'D','*','0','#'}

};
uint8_t ok[8]  = {0x1,0x11,0xa,0xe,0x4,0x0,0x0};
uint8_t postep[8]  = {0x0,0x0,0x1f,0x0,0x0,0x1f,0x0};
uint8_t postep2[8]  = {0x0,0x0,0x1f,0x1f,0x1f,0x1f,0x0};
uint8_t dino[8] = {0xC, 0xF, 0xC, 0xF, 0x1E, 0x1F, 0xA, 0xA};
uint8_t dino2[8] = {0xC, 0xF, 0xC, 0xF, 0x1E, 0x1F, 0xA, 0x11};
uint8_t dino3[8] = {0xC, 0xF, 0xC, 0xF, 0x1E, 0x1F, 0xA, 0x4};
uint8_t kaktus[8] = {0x4, 0x4, 0x5, 0x16, 0xC, 0x5, 0x6, 0x4};
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int wolne = 0;

LiquidCrystal_I2C lcd(0x27,16,2);


void setup(){
  
  for(int i = 6; i < 200;i++){
   s = EEPROM.read(i);
   while(s == 0){
    i++;
    s = EEPROM.read(i);}
    zawartosc += s;
    }
  randomSeed(analogRead(A0));
  pinMode(LED, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(A5, INPUT);
wolne = 0;
for(int i = 0; i < EEPROM.length(); i++){
  if(EEPROM.read(i) == 0){
    wolne++;}}
lcd.init();


lcd.backlight();
lcd.createChar(0, ok);
lcd.createChar(1, postep);
lcd.createChar(2, postep2);
lcd.createChar(3, dino);
lcd.createChar(4, dino2);
lcd.createChar(5, dino3);
lcd.createChar(6, kaktus);
lcd.home();
int k = 0;
  Serial.begin(9600);
  Serial.print(F("halo"));
  if(Serial.available() > 0){
    digitalWrite(LED3, HIGH);
    }else{
   
      digitalWrite(LED3, HIGH);
      delay(500);
      digitalWrite(LED3, LOW);
      delay(500);
      digitalWrite(LED3, HIGH);}
    delay(500);
    digitalWrite(LED3, LOW);
  lcd.setCursor(0, 0);
  lcd.print(wolne);
  lcd.print(F(" bytes free"));
  lcd.setCursor(0, 1);
  delay(500);
  lcd.print(F("Ready"));
  delay(500);
  if(wolne == EEPROM.length()){
    lcd.clear();
    lcd.print(F("no data in memory"));
    uspienie_czas = 1;}
      int procent = 0;
      int x = 0;
  for (int i = 0;i <= random(1, 10); i++){
lcd.setCursor(0,0);
    analogWrite(LED, k);
  lcd.clear();
  if(procent > 100){
    break;}
  lcd.print(F("loading"));
  lcd.print(procent);
  lcd.print(F("%"));
  k = k + 8;
  

lcd.setCursor(0, 1);
if(procent > 5){
  lcd.printByte(2);}if (procent > 11){
    lcd.printByte(2);}if(procent > 17){
      lcd.printByte(2);}if(procent > 23){
        lcd.printByte(2);}if(procent > 29){
          lcd.printByte(2);}if(procent > 35){
            lcd.printByte(2);}if(procent > 41){
              lcd.printByte(2);}if(procent > 47){
                lcd.printByte(2);}if(procent > 53){
                  lcd.printByte(2);}if(procent > 60){
                    lcd.printByte(2);}if(procent > 65){
                      lcd.printByte(2);}if(procent > 71){
                        lcd.printByte(2);}if(procent > 79){
                          lcd.printByte(2);}if(procent > 85){
                            lcd.printByte(2);}if(procent == 100){
                             
                                lcd.printByte(2);
                                delay(500);
                         
                                break;}
                                
 
for(int i = 0; i < 16; i++){
  lcd.printByte(1);}
 

  
          procent = procent + random(25);
 
   delay(500);}
   lcd.clear();
   procent = 100;
   lcd.setCursor(0, 0);
     lcd.print(F("loading"));
  lcd.print(procent);
  lcd.print(F("%"));
  lcd.setCursor(0, 1);
  lcd.print(F("ukonczono"));
  lcd.printByte(0);
  delay(500);
  lcd.clear();
    digitalWrite(LED, LOW);
}
int getAplikacja(int numer){
  if(numer == 1){
    lcd.print(F("zegar"));}else if(numer == 2){
      lcd.print(F("ustawienia"));}else if(numer == 3){
        lcd.print(F("notatnik"));}else if(numer == 4){
          lcd.print(F("dinozaur"));}else if(numer == 5){
            lcd.print(F("pogoda"));}else if(numer == 6){
              lcd.print(F("opinia"));}else if(numer == 7){
                lcd.print(F("2 gracze"));}else if(numer == 8){
                  lcd.print(F("kalkulator"));}else if(numer == 10){
                    lcd.print(F("edytor kodu"));}else if(numer == 11){
                      lcd.print(F("wlasna aplikacja1"));}}

void nextFrame(){
  aktualnyCzas5 = millis();
  roznicaCzasu5 = aktualnyCzas5 - zapamietanyCzas5;
  if(roznicaCzasu5 > czas2){
  frame++;
  zapamietanyCzas5 = aktualnyCzas5;}
  if(frame == 0){
 lcd.printByte(3);}else if(frame == 1){
  lcd.printByte(4);}else if(frame == 2){
    lcd.printByte(3);}else if(frame == 3){
    lcd.printByte(5);}
  if(frame > 3){
    frame = 0;}}
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
void loop(){
  while (start == 1) {
    if(next == 0) {
        lcd.setCursor(0, 0);
      if(zajete1 == 0) {
  
    lcd.print(F("1. puste"));}else{
      lcd.print(F("uzytkownik 1"));}
    lcd.setCursor(0, 1);
    if(zajete2 == 0){
    lcd.print(F("2. puste"));}else{
      lcd.print(F(""));}}else if (next == 1) {
      if(zajete1 == 0){
        
        lcd.clear();
  lcd.print(F("witamy!"));
  zajete1 = 1;
  lcd.print(numer);
    EEPROM.put(4, zajete1);
    lcd.clear();
    lcd.print(F("uzytkownik"));
    lcd.print(numer);}
  delay(500);
  lcd.clear();
  start = 0;}else if(next == 2){
         if(zajete2 == 0){
        lcd.clear();
  lcd.print(F("witamy!"));
  lcd.print(numer + 1);
  zajete2 = 1;
    EEPROM.put(5, zajete2);
  }else{
    lcd.clear();
    lcd.print(F("uzytkownik"));
    lcd.print(numer + 1);}
  delay(500);
  lcd.clear();
  start = 0;
    }
    int klawisz = klawiatura.getKey();
if(klawisz){

if(klawisz == 49){
  next = 1;

}
  if(klawisz == 50) {
    next = 2;}
  if(klawisz == 35) {
    aplikacja = 0;}
    }}
int klawisz = klawiatura.getKey();

if(klawisz) {if(uspienie == 1) {lcd.backlight();
digitalWrite(LED3, LOW);}
  czas = 0;
uspienie = 0;
lcd.print(klawisz);
Serial.print(klawisz);

if(klawisz == 49){
  lcd.clear();
  if(aplikacja == 0) {
  aplikacja = ulubionaap1;}else if (aplikacja == 2) {
    if(wybor == 0){
    wybor = 1;}else if(wybor  == 1) {
      uspienie_czas = 1;}else if(wybor == 2){
        if(ustawienia == 0) {
        ustaw_m = ustaw_m + 1;}else if (ustawienia == 1) {
          ustaw_g = ustaw_g + 1;}}}else if(aplikacja == 3){
            if(plik == 0) {
            plik = 1;}else if (plik == 1){
              zawartosc += znak;
              
           
                   }}else if(aplikacja == 5){
                    if(wybort == 0){
                    temperatura1 ++;}else if(wybort == 1){
                      temperatura2++;}}else if(aplikacja == 6){
                        opinia++;
                        EEPROM.put(209, opinia);
                        lcd.clear();}else if(aplikacja == 7){
                          y1 = !y1;
                          lcd.clear();}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 1;}else if(menuk == 1){
                              dzialanie = 1;}else if(menuk == 2){
                              skladnik2 += 1;}
                          }else if(aplikacja == 9){
                            if(menuw == 0){
                              if(y_myszki == 0){
                                aplikacja = 1;}else{
                                  aplikacja = 2;}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                      aplikacja = 3;}else{
                                        aplikacja = 4;}}else if(menuw == 2){
                                          if(y_myszki == 0){
                                            aplikacja = 5;}else{
                                              aplikacja = 6;}}else if(menuw == 3){
                                                if(y_myszki == 0){
                                                  aplikacja = 7;}else{
                                                    aplikacja = 8;}}else if(menuw == 4){
                                                      if(y_myszki == 0){
                                                        if(y_myszki == 0){
                                                          aplikacja = 10;}}else{
                                                            aplikacja = 11;}}}else if(aplikacja == 10){
                                                              if(EEPROM.read(ik - 1) != 1){
                                                            lcd.setCursor(0, 1);
                                                            lcd.print(F("printznak"));
                                                            EEPROM.put(ik, 1);
                                                            delay(100);
                                                            lcd.clear();
                                                            ik++;
                                                              }else{
                                                            if(EEPROM.read(ik == 1)){
                                                              
                                                              EEPROM.put(ik, iz);}
                                                              ik++;}}
  
  
  
  }
  if(klawisz == 50) {
    if(aplikacja == 0){
    aplikacja = ulubionaap2;}else if (aplikacja == 2) {
      if(wybor == 0) {
        wybor = 2;}else if(wybor == 1){
          uspienie_czas = 2;}else if(wybor == 2){
            if(ustawienia == 0) {
        ustaw_m = ustaw_m + 2;}else if (ustawienia == 1) {
          ustaw_g = ustaw_g + 2;}}}
    lcd.clear();if(aplikacja == 3){if(plik == 1){
      zawartosc.remove(zawartosc.length() - 1, 1);
      lcd.clear();
          }}else if(aplikacja == 5){
            if(wybort == 0){
            temperatura1 = temperatura1 + 2;}else if(wybort == 1){
              temperatura2 = temperatura2 + 2;}}else if(aplikacja == 7){
                y1p = y1;
                x1 = 0;
                i1 = i1 + 1;}else if(aplikacja == 8){
                            if(menuk == 0){
                              if(y_myszki == 0){
                            skladnik1 += 2;}else if(menuk == 1){
                              dzialanie = 2;}else if(menuk == 2){
                              skladnik2 += 2;}
                          }}else if(aplikacja == 9){
                            if(ulubionaap1 == 0){
                              if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap1 = 1;
                                EEPROM.put(210, ulubionaap1);}else{
                                  ulubionaap1 = 2;
                                  EEPROM.put(210 , ulubionaap1);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap1 = 3;
                                EEPROM.put(210, ulubionaap1);}else{
                                  ulubionaap1 = 4;
                                  EEPROM.put(210 , ulubionaap1);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap1 = 5;
                                EEPROM.put(210, ulubionaap1);}else{
                                  ulubionaap1 = 6;
                                  EEPROM.put(210 , ulubionaap1);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap1 = 7;
                                EEPROM.put(210, ulubionaap1);}else{
                                  ulubionaap1 = 8;
                                  EEPROM.put(210 , ulubionaap1);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap1 = 10;
                                      EEPROM.put(210, ulubionaap1);}else{
                                        ulubionaap1 = 11;
                                        EEPROM.put(210, ulubionaap1);}}}else if(ulubionaap2 == 0){
                                    if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap2 = 1;
                                EEPROM.put(211, ulubionaap2);}else{
                                  ulubionaap2 = 2;
                                  EEPROM.put(211 , ulubionaap2);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap2 = 3;
                                EEPROM.put(211, ulubionaap2);}else{
                                  ulubionaap2 = 4;
                                  EEPROM.put(211 , ulubionaap2);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap2 = 5;
                                EEPROM.put(211, ulubionaap2);}else{
                                  ulubionaap2 = 6;
                                  EEPROM.put(211 , ulubionaap2);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap2 = 7;
                                EEPROM.put(211, ulubionaap2);}else{
                                  ulubionaap2 = 8;
                                  EEPROM.put(211 , ulubionaap2);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap2 = 10;
                                      EEPROM.put(211, ulubionaap2);
                                  }else{
                                        ulubionaap2 = 11;
                                        EEPROM.put(211, ulubionaap2);}}}else if(ulubionaap3 == 0){
                                    if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap3 = 1;
                                EEPROM.put(212, ulubionaap3);}else{
                                  ulubionaap3 = 2;
                                  EEPROM.put(212 , ulubionaap3);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap3 = 3;
                                EEPROM.put(212, ulubionaap3);}else{
                                  ulubionaap3 = 4;
                                  EEPROM.put(212 , ulubionaap3);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap3 = 5;
                                EEPROM.put(212, ulubionaap3);}else{
                                  ulubionaap3 = 6;
                                  EEPROM.put(212 , ulubionaap3);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap3 = 7;
  
                                EEPROM.put(212, ulubionaap3);}else{
                                  ulubionaap3 = 8;
                                  EEPROM.put(212 , ulubionaap3);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap3 = 10;
                                      EEPROM.put(212, ulubionaap3);
                                  }else{
                                        ulubionaap3 = 11;
                                        EEPROM.put(212, ulubionaap3);}}}else if(ulubionaap4 == 0){
                                    if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap4 = 1;
                                EEPROM.put(213, ulubionaap4);}else{
                                  ulubionaap4 = 2;
                                  EEPROM.put(213 , ulubionaap4);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap4 = 3;
                                EEPROM.put(213, ulubionaap4);}else{
                                  ulubionaap4 = 4;
                                  EEPROM.put(213 , ulubionaap4);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap4 = 5;
                                EEPROM.put(213, ulubionaap4);}else{
                                  ulubionaap4 = 6;
                                  EEPROM.put(213 , ulubionaap4);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap4 = 7;
                                EEPROM.put(213, ulubionaap4);}else{
                                  ulubionaap4 = 8;
                                  EEPROM.put(213 , ulubionaap4);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap4 = 10;
                                      EEPROM.put(213, ulubionaap4);}else{
                                        ulubionaap4 = 11;
                                        EEPROM.put(213, ulubionaap4);}}}else if(ulubionaap5 == 0){
                                    if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap5 = 1;
                                EEPROM.put(214, ulubionaap5);}else{
                                  ulubionaap5 = 2;
                                  EEPROM.put(214 , ulubionaap5);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap5 = 3;
                                EEPROM.put(214, ulubionaap5);}else{
                                  ulubionaap5 = 4;
                                  EEPROM.put(214 , ulubionaap5);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap5 = 5;
                                EEPROM.put(214, ulubionaap5);}else{
                                  ulubionaap5 = 6;
                                  EEPROM.put(214 , ulubionaap5);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap5 = 7;
                                EEPROM.put(214, ulubionaap5);}else{
                                  ulubionaap5 = 8;
                                  EEPROM.put(214 , ulubionaap1);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap5 = 10;
                                      EEPROM.put(214, ulubionaap5);}else{
                                        ulubionaap5 = 11;
                                        EEPROM.put(214, ulubionaap5);}}}else if(ulubionaap6 == 0){
                                    if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap6 = 1;
                                EEPROM.put(215, ulubionaap6);}else{
                                  ulubionaap6 = 2;
                                  EEPROM.put(215 , ulubionaap6);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap6 = 3;
                                EEPROM.put(215, ulubionaap6);}else{
                                  ulubionaap6 = 4;
                                  EEPROM.put(215 , ulubionaap6);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap6 = 5;
                                EEPROM.put(215, ulubionaap6);}else{
                                  ulubionaap6 = 6;
                                  EEPROM.put(215 , ulubionaap6);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap6 = 7;
                                EEPROM.put(215, ulubionaap6);}else{
                                  ulubionaap6 = 8;
                                  EEPROM.put(215 , ulubionaap6);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap6 = 10;
                                      EEPROM.put(215, ulubionaap6);}else{
                                        ulubionaap6 = 11;
                                        EEPROM.put(215, ulubionaap6);}}}else if(ulubionaap7 == 0){
                                    if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap7 = 1;
                                EEPROM.put(216, ulubionaap7);}else{
                                  ulubionaap7 = 2;
                                  EEPROM.put(216 , ulubionaap7);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap7 = 3;
                                EEPROM.put(216, ulubionaap7);}else{
                                  ulubionaap7 = 4;
                                  EEPROM.put(216 , ulubionaap7);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap7 = 5;
                                EEPROM.put(216, ulubionaap7);}else{
                                  ulubionaap7 = 6;
                                  EEPROM.put(216 , ulubionaap7);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap7 = 7;
                                EEPROM.put(216, ulubionaap7);}else{
                                  ulubionaap7 = 8;
                                  EEPROM.put(216 , ulubionaap7);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap7 = 10;
                                      EEPROM.put(216, ulubionaap7);
                                  }else{
                                        ulubionaap7 = 11;
                                        EEPROM.put(216, ulubionaap7);}}}else if(ulubionaap8 == 0){
                                      if(menuw == 0){
                              if(y_myszki == 0){
                                ulubionaap8 = 1;
                                EEPROM.put(217, ulubionaap8);}else{
                                  ulubionaap8 = 2;
                                  EEPROM.put(217 , ulubionaap8);}}else if(menuw == 1){
                                    if(y_myszki == 0){
                                ulubionaap8 = 3;
                                EEPROM.put(217, ulubionaap8);}else{
                                  ulubionaap8 = 4;
                                  EEPROM.put(217 , ulubionaap8);}}if(menuw == 2){
                                                                        if(y_myszki == 0){
                                ulubionaap8 = 5;
                                EEPROM.put(217, ulubionaap8);}else{
                                  ulubionaap8 = 6;
                                  EEPROM.put(217 , ulubionaap8);}}else if(menuw == 3){
                                                                        if(y_myszki == 0){
                                ulubionaap8 = 7;
                                EEPROM.put(217, ulubionaap8);}else{
                                  ulubionaap8 = 8;
                                  EEPROM.put(217 , ulubionaap8);}}else if(menuw == 4){
                                    if(y_myszki == 0){
                                      ulubionaap8 = 10;
                                      EEPROM.put(217, ulubionaap8);}else{
                                        ulubionaap8 = 11;
                                        EEPROM.put(217, ulubionaap8);}}}}else if(aplikacja == 10){
                                                             if(EEPROM.read(ik - 1) != 1){
                                                              ik++;
                                                              lcd.setCursor(0, 1);
                                                            lcd.print(F("wyszysc"));
                                                            EEPROM.put(ik, 2);
                                                            delay(100);
                                                            lcd.clear();}else if(EEPROM.read(ik - 1) == 1){
                                                              iz = iz + 1;

                                                              }}}
  if(klawisz == 35) {


        if(aplikacja == 2 && wybor == 2){
              minuty = ustaw_m;
        godziny = ustaw_g;
    ustaw_m = 0;

    ustaw_g = 0;
}   wybort = 0;
    ustawienia = 0;
    plik = 0;
        aplikacja = 0;
    wybor = 0;
    lcd.noBlink();
    lcd.clear();}else if(klawisz == 42){
      digitalWrite(LED2, HIGH);
      lcd.clear();
        EEPROM.put(0, uspienie_czas);
        EEPROM.put(1, sekundy);
        EEPROM.put(2, minuty);
        EEPROM.put(3, godziny);
EEPROM.put(6, zawartosc);
        lcd.print(F("zapisywanie"));
        lcd.setCursor(0,1);
       
        for(int i = 0; i < 15; i++) {
       
          lcd.print(F("."));
          delay(100);
          }
          lcd.clear();
          digitalWrite(LED2, LOW);
          
     }else if (klawisz == 51){
      if(aplikacja == 0){
          aplikacja = ulubionaap3;
          lcd.clear();}else if(aplikacja == 5){
            lcd.clear();
            wybort++;}else if(aplikacja == 2){
              if(wybor == 0){
                wybor = 3;}else if(wybor == 2){
                            if(ustawienia == 0){
            ustawienia = 1;
            lcd.clear();
            }}}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 3;}else if(menuk == 1){
                              dzialanie = 3;}else if(menuk == 2){
                              skladnik2 += 3;}
                          }else if(aplikacja == 9){
                            ulubionaap1 = 0;
                            ulubionaap2 = 0;
                            ulubionaap3 = 0;
                            ulubionaap4 = 0;
                            ulubionaap5 = 0;
                            ulubionaap6 = 0;
                            ulubionaap7 = 0;
                            ulubionaap8 = 0;
                            EEPROM.put(210, ulubionaap1);
                            EEPROM.put(211, ulubionaap2);
                             EEPROM.put(212, ulubionaap3);
                            EEPROM.put(213, ulubionaap4);
                             EEPROM.put(214, ulubionaap5);
                            EEPROM.put(215, ulubionaap6);
                             EEPROM.put(216, ulubionaap7);
                            EEPROM.put(217, ulubionaap8);
                            }else if(aplikacja == 10){
                              if(EEPROM.read(ik - 1) == 1){
                                iz = iz - 1;}else{
                                  ik++;
                                  lcd.setCursor(0, 1);
                                  lcd.print(F("przesun kursor(prawo)"));
                                  EEPROM.put(ik, 3);
                                  delay(100);
                                  lcd.clear();}}
}else if(klawisz == 65){
              if(aplikacja == 0){
              lcd.clear();
              menu = menu + 1;}else if(aplikacja == 2){
                lcd.clear();
                menuu = menuu + 1;}else if(aplikacja == 8){
                            menuk = menuk + 1;
                            lcd.clear();
                            if(menuk > 3){
                              menuk = 0;
                              skladnik1 = "0";
                              skladnik2 = "0";}
                          }else if(aplikacja == 9){
                            lcd.clear();
                            menuw = menuw + 1;
                            }}else if(klawisz == 68){
                if(aplikacja == 0){
              lcd.clear();
              menu = menu - 1;}else if(aplikacja == 2){
                lcd.clear();
                menuu = menuu - 1;}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 0;}else if(menuk == 2){
                              skladnik2 += 0;}
                          }else if(aplikacja == 9){
                            
                            menuw = menuw - 1;
                            lcd.clear();}}else if(klawisz == 66){
                  if(plik == 1){
                    znak2 = znak2 + 1;
                    lcd.clear();
                    lcd.print(zawartosc);}}else if(klawisz == 67){
                      if(plik==1){
                        znak2 = znak2 - 1;
                        lcd.clear();
                        lcd.print(zawartosc);}}else if(klawisz == 52){
                          if(scroll == 0){
                          if(aplikacja == 0){
                          aplikacja = ulubionaap4;
                          lcd.clear();}else if(aplikacja == 5){
                            if(wybort == 0){
                            temperatura1 = temperatura1 * -1;
                            lcd.clear();}else if(wybort == 1){
                              lcd.clear();
                              temperatura2 = temperatura2 * -1;}}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 4;}else if(menuk == 1){
                              dzialanie = 4;}else if(menuk == 2){
                              skladnik2 += 4;}
                          }else if(aplikacja == 2){
                            wybor = 4;
                            lcd.clear();}else if(aplikacja == 10){
                              ik++;
                                  lcd.setCursor(0, 1);
                                  lcd.print(F("przesun kursor(lewo)"));
                                  EEPROM.put(ik, 4);
                                  delay(100);
                                  lcd.clear();}}else{
                                lcd.scrollDisplayRight();}}else if(klawisz == 53){
                            if(aplikacja == 4){
                              if(x <= 0 && y == 1){
                                x = random(2, 15);
                                wynik = 0;}
                               
                               
                              y = 0;
                           
                              lcd.clear();
                              
                              
                                }else if(aplikacja == 0){
                                  aplikacja = ulubionaap5;
                                  lcd.clear();}else if(aplikacja == 7){
                                    y2p = y2;
                                    x2 = 15;
                                    i2 = i2 + 1;}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 5;}else if(menuk == 2){
                              skladnik2 += 5;}
                          }else if(aplikacja == 2){
                            wybor = 5;}else if(aplikacja == 9){
                              y_myszki = ! y_myszki;
                              lcd.clear();}else if(aplikacja == 10){
                                ik++;
                                  lcd.setCursor(0, 1);
                                  lcd.print(F("odwrotne"));
                                  EEPROM.put(ik, 5);
                                  delay(100);
                                  lcd.clear();}}else if(klawisz == 54){
                                    if(scroll == 0){
                                    if(aplikacja == 0){
                                      aplikacja = ulubionaap6;
                                      lcd.clear();}else if(aplikacja == 4){
                                        najlepszy = 0;
                                        EEPROM.put(207,najlepszy);}else if(aplikacja == 7){
                                          y2 = !y2;
                                          lcd.clear();}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 6;}else if(menuk == 2){
                              skladnik2 += 6;}
                          }}else{
                                        lcd.scrollDisplayLeft();}}else if(klawisz == 48){
                                        scroll = !scroll;}else if(klawisz == 55){
                                          if(aplikacja == 0){
                                            aplikacja = ulubionaap7;
                                            lcd.clear();}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 7;}else if(menuk == 2){
                              skladnik2 += 7;}
                          }}else if(klawisz == 56){
                                              if(aplikacja == 0){
                                                aplikacja = ulubionaap8;
                                                lcd.clear();}else if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 8;}else if(menuk == 2){
                              skladnik2 += 8;}
                          }}else if(klawisz == 57){
                            if(aplikacja == 8){
                            if(menuk == 0){
                            skladnik1 += 9;}else if(menuk == 2){
                              skladnik2 += 9;}
                          }else if(aplikacja == 0){
                            aplikacja = 9;
                            lcd.clear();}}}else if(!klawisz) {
          if (aplikacja == 0){
      czas ++;
      if(czas >= uspienie_czas * 1000){
uspienie = 1;
}}}
if (uspienie == 0) {
 if(aplikacja == 0) {
  if(menu == 0) {
  lcd.setCursor(0,0);
  lcd.print(F("1. "));
  getAplikacja(ulubionaap1);
  lcd.setCursor(0,1);
  lcd.print(F("2. "));
  getAplikacja(ulubionaap2);}else if(menu == 1){
      lcd.setCursor(0,0);
  lcd.print(F("3. "));
  getAplikacja(ulubionaap3);
  lcd.setCursor(0,1);
  lcd.print(F("4. "));
  getAplikacja(ulubionaap4);}else if(menu == 2){
    lcd.setCursor(0, 0);
    lcd.print(F("5. "));
    getAplikacja(ulubionaap5);
    lcd.setCursor(0, 1);
    lcd.print(F("6. "));
    getAplikacja(ulubionaap6);}else if(menu == 3){
     lcd.setCursor(0, 0);
    lcd.print(F("7. "));
    getAplikacja(ulubionaap7);
    lcd.setCursor(0, 1);
    lcd.print(F("8. "));
    getAplikacja(ulubionaap8);}else if(menu == 4){
           lcd.setCursor(0, 0);
    lcd.print(F("9. wszystkie aplikacje"));
   }
}else if(aplikacja == 1) {
  lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(godziny);
    lcd.print(F(":"));
    lcd.print(minuty);
    lcd.print(F(":"));
    lcd.print(sekundy);

}else if(aplikacja == 2) {
  if (wybor == 0) {
    if(menuu == 0){
  lcd.setCursor(0, 0);
  lcd.print(F("1. Ustawienia uspienia"));
  lcd.setCursor(0, 1);
  lcd.print(F("2. czas"));
  lcd.print(wybor);}else if(menuu == 1){
    lcd.setCursor(0, 0);
    lcd.print(F("3. info o systemie"));
    lcd.setCursor(0, 1);
    lcd.print(F("4.czas dzialania"));}else if(menuu == 2){
      lcd.setCursor(0 ,0);
      lcd.print(F("5. bateria"));}}else if (wybor == 1){
    lcd.setCursor(0, 0);
    lcd.print(F("po ilu minutach uspienie?"));
    lcd.setCursor(0, 1);
    lcd.print(uspienie_czas);}else if (wybor == 2) {
      if(ustawienia == 0){
      lcd.setCursor(0,0);
      lcd.print(F("ustaw czas(minuty)"));
      lcd.setCursor(0, 1);
      lcd.print(ustaw_m);
      if(ustaw_m >= 60){
        ustawienia = 1;}}else if(ustawienia == 1){
      
      lcd.setCursor(0,0);
      lcd.print(F("ustaw godziny"));
      
      lcd.setCursor(0, 1);
      lcd.print(ustaw_g);}}else if(wybor == 3){
        wolne = 0;
for(int i = 0; i < EEPROM.length(); i++){
  if(EEPROM.read(i) == 0){
    wolne++;}}
        if(Serial.read() == 'V'){
          Serial.println(F("wersja systemu to 1.0"));
          Serial.println(F(""));
          Serial.print(EEPROM.length() - wolne);
          Serial.print(F("/"));
          Serial.print(EEPROM.length());
          Serial.print(F(" B zajete"));
          Serial.println(F(""));}
              lcd.setCursor(0,0);
      lcd.print(EEPROM.length() - wolne);
      lcd.print(F("/"));
      lcd.print(EEPROM.length());
      lcd.print(F(" B zajete"));
      lcd.setCursor(0, 1);
      lcd.print(F("sys v: pre1af1.1"));}else if(wybor == 4){
        lcd.setCursor(0,0);
        lcd.print(millis());
        delay(100);
        lcd.clear();}else if(wybor == 5){
          
long mv = readVcc();
  float voltage = mv / 1000.0;
  

  int percent = map(mv, 4800, 5150, 0, 100);
  percent = constrain(percent, 0, 100);
  lcd.setCursor(0, 0);
  lcd.print("VCC: ");
  lcd.print(voltage, 2);
  lcd.print("V | ");
  lcd.setCursor(0, 1);
  lcd.print(percent);
  lcd.println("%");
  
  delay(100);
  
  lcd.clear();
  }
  }else if(aplikacja == 3) {
    if(plik == 0){
    lcd.setCursor(0, 0);
    lcd.print(F("witaj w notatniku"));
    lcd.setCursor(0, 1);
    lcd.print(F("1. plik 1"));}else if(plik == 1){

 
      if(znak2 == 1) {
        znak = 'a';}else if(znak2 == 2) {
          znak = 'b';}else if(znak2 == 3){
            znak = 'c';}else if(znak2 == 4){
              znak = 'd';}else if(znak2 == 5){
                znak = 'e';}else if(znak2 == 6){
                  znak = 'f';}else if(znak2 == 7){
                    znak = 'g';}else if(znak2 == 8){
                      znak = 'h';}else if(znak2 == 9){
                        znak= 'i';}else if(znak2 == 10){
                          znak = 'j';}else if(znak2 == 11){
                            znak = 'k';}else if(znak2 == 12){
                              znak = 'l';}else if(znak2 == 13){
                                znak = 'm';}else if(znak2 == 14){
                                  znak = 'n';}else if(znak2 == 15){
                                    znak = 'o';}else if(znak2 == 16){
                                      znak = 'q';}else if(znak2 == 17){
                                        znak = 'p';}else if(znak2 == 18){
                                          znak = 'r';}else if(znak2 == 19){
                                            znak = 's';}else if(znak2 == 20){
                                              znak = 't';}else if(znak2 == 21){
                                                znak = 'u';}else if(znak2 == 22){
                                                  znak = 'v';}else if(znak2 == 23){
                                                    znak = 'w';}else if(znak2 == 24){
                                                      znak = 'x';}else if(znak2 == 25){
                                                        znak = 'y';}else if(znak2 == 26){
                                                          znak = 'z';}else if(znak2 == 27){
                                                            znak = '1';}else if(znak2 == 28){
                                                              znak = '2';}else if(znak2 == 29){
                                                                znak = '3';}else if(znak2 == 30){
                                                                  znak = '4';}else if(znak2 == 31){
                                                                    znak = '5';}else if (znak2 == 32){
                                                                      znak = '6';}else if(znak2 == 33){
                                                                        znak = '7';}else if(znak2 == 34){
                                                                          znak = '8';}else if(znak2 == 35){
                                                                            znak = '9';}else if(znak2 == 36){
                                                                              znak = '0';}else if(znak2 == 37){
                                                                                znak = '.';}else if(znak2 == 38){
                                                                                  znak= ',';}
                                                                                  lcd.setCursor(0, 0);
                                                                                  lcd.print(zawartosc);
                                                                                  lcd.blink();
                                                                                
     }
    }else if(aplikacja == 4){

      if(x <= 0 && y == 1){
        czas2 = 1000;
        lcd.setCursor(0, 0);
        lcd.print(F("game over"));
        lcd.setCursor(0, 1);
        lcd.print(F("high score:"));
        lcd.print(najlepszy);
        if(wynik >= najlepszy){
          najlepszy = wynik;
          EEPROM.put(207, najlepszy);}}else if(x <= 0){
        x = random(2, 15);
        wynik = wynik + 1;
        Serial.println(wynik);}else {
          lcd.setCursor(2, 0);
          lcd.print(F("score:"));
          lcd.print(wynik);
                  lcd.setCursor(0, y);
      nextFrame();
      lcd.setCursor(x, 1);
      lcd.printByte(6);
    
     
      aktualnyCzas3 = millis();
      roznicaCzasu3 = aktualnyCzas3 - zapamietanyCzas3;
      if(roznicaCzasu3 >= czas2){
                                zapamietanyCzas3 = aktualnyCzas3;
                                 x = x - 1;
                                 lcd.clear();
                                 ;}
      
      aktualnyCzas2 = millis();
                              roznicaCzasu2 = aktualnyCzas2 - zapamietanyCzas2;
                              if(y == 0){
                                
      if(roznicaCzasu2 >= 1500UL){
                                zapamietanyCzas2 = aktualnyCzas2;
                                y = 1;
                                lcd.clear();
                                roznicawynik = wynik - ostatniwynik;
                                if(roznicawynik >= 5){
                                  ostatniwynik = wynik;
                                  czas2 = czas2 - 50;}}}}}else if(aplikacja == 5){
                                    if(wybort == 0){
                                    lcd.setCursor(0,0);
                                    lcd.print(F("1 h temu:(temp)"));
                                   lcd.setCursor(0, 1);
                                    lcd.print(temperatura1);
                                    }else if(wybort == 1){
                                      lcd.setCursor(0,0);
                                      lcd.print(F("teraz(temp)"));
                                      lcd.setCursor(0, 1);
                                      lcd.print(temperatura2);}else if(wybort == 2){
                                     
                                       
                                        lcd.setCursor(0, 0);
                                        int roznicatemperatur = temperatura1 - temperatura2; 
                                        lcd.print(godziny + 1);
                                        lcd.print(F(" "));
                                        lcd.print(temperatura2 + roznicatemperatur);
                                        
                                         
                                        lcd.setCursor(0, 1);
                                        roznicatemperatur = temperatura1 - temperatura2; 
                                        lcd.print(godziny + 2);
                                        lcd.print(F(" "));
                                        lcd.print(temperatura2 + roznicatemperatur * 2);
                                        }}else if(aplikacja == 6){
                                          lcd.setCursor(0, 0);
                                          lcd.print(F("podajopinie(1-10)"));
                                          lcd.setCursor(0, 1);
                                          lcd.print(opinia);
                                          Serial.println(opinia2);
                                          opinia2 = EEPROM.read(209);}else if(aplikacja == 7){
                                            lcd.setCursor(0, y1);
                                            lcd.print(F("1"));
                                            for(int i = 0; i < 10; i++){
                                              lcd.setCursor(x1, y1p);
                                              lcd.print(F("-"));}
                                             aktualnyCzas4 = millis();
                                             roznicaCzasu4 = aktualnyCzas4 - zapamietanyCzas4;
                                             if(roznicaCzasu4 > 1000){
                                              zapamietanyCzas4 = aktualnyCzas4;
                                              lcd.clear();
                                              if(x1 > 15){
                                                x1 = 0;}
                                              x1 = x1 + 1;
                                              if(x2 < 0){
                                                x2 = 15;}
                                              x2 = x2 - 1;}
                                              if(x2 == 0 && y2p == y1){
                                                lcd.clear();
                                                lcd.print(F("gracz 2"));}
                                                if(x1 == 15 && y1p == y2){
                                                  lcd.clear();
                                                  lcd.print(F("gracz1"));}
                                              lcd.setCursor(x2, y2p);
                                              lcd.print(F("-"));
                                             
                                              
                                            lcd.setCursor(15, y2);
                                            lcd.print(F("2"));}else if(aplikacja == 8){
                                              if(menuk == 0){
                                              lcd.setCursor(0, 0);
                                              lcd.print(F("kalkulator - podaj liczbe1"));
                                              lcd.setCursor(0, 1);
                                              lcd.print(skladnik1);}else if(menuk == 1){
                                                lcd.setCursor(0, 0);
                                              lcd.print(F("kalkulator - podaj dzialanie(1+2-3*4/)"));
                                              lcd.setCursor(0, 1);
                                              lcd.print(dzialanie);}else if(menuk == 2){
                                                 lcd.setCursor(0, 0);
                                              lcd.print(F("kalkulator - podaj liczbe2"));
                                              lcd.setCursor(0, 1);
                                              lcd.print(skladnik2); }else if(menuk = 3){
                                                int skladniik1 = skladnik1.toInt();
                                                int skladniik2 = skladnik2.toInt();
                                                int wynikd = 0;
                                                if(dzialanie == 1){
                                                  wynikd = skladniik1 + skladniik2;}else if(dzialanie == 2){
                                                    wynikd = skladniik1 - skladniik2;}else if(dzialanie == 3){
                                                      wynikd = skladniik1 * skladniik2;}else if(dzialanie == 4){
                                                        wynikd = skladniik1 / skladniik2;}
                                                        lcd.setCursor(0, 0);
                                                        lcd.print(wynikd);}}else if(aplikacja == 9){
                                                          lcd.setCursor(15, y_myszki);
                                                          lcd.print(F("<"));
                                                          if(menuw == 0){
                                                          lcd.setCursor(0 , 0);
                                                          lcd.print(F("zegar"));
                                                          lcd.setCursor(0, 1);
                                                          lcd.print(F("ustawienia"));}else if(menuw == 1){
                                                                                                                     lcd.setCursor(0 , 0);
                                                          lcd.print(F("notatnik"));
                                                          lcd.setCursor(0, 1);
                                                          lcd.print(F("dinozaur")); }else if(menuw == 2){
                                                                                                                      lcd.setCursor(0 , 0);
                                                          lcd.print(F("pogoda"));
                                                          lcd.setCursor(0, 1);
                                                          lcd.print(F("opinia"));}else if(menuw == 3){
                                                                                                                      lcd.setCursor(0 , 0);
                                                          lcd.print(F("2 gracze"));
                                                          lcd.setCursor(0, 1);
                                                          lcd.print(F("kalkulator"));}else if(menuw == 4){
                                                            lcd.setCursor(0, 0);
                                                            lcd.print(F("edytor kodu"));
                                                            lcd.setCursor(0, 1);
                                                            lcd.print(F("wlasna aplikacja1"));}}else if(aplikacja == 10){
                                                            lcd.setCursor(0, 0);
                                                            lcd.print(F("podaj komende"));}else if(aplikacja == 11){
                                                              for(int i = 229; i < 419; i++){
                                                                if(EEPROM.read(i) == 1){
                                         
                                                                  
                                                                 

                                                                 
                                                                 i = i + 1;
                                                                 if(EEPROM.read(i) == 65){
                                                                  lcd.print('a');}else if(EEPROM.read(i) == 66){
                                                                    lcd.print('b');}else if(EEPROM.read(i) == 67){
                                                                      lcd.print('c');}else if(EEPROM.read(i) == 68){
                                                                        lcd.print('d');}else if(EEPROM.read(i) == 69){
                                                                          lcd.print('e');}else if(EEPROM.read(i) == 70){
                                                                            lcd.print('f');}else if(EEPROM.read(i) == 71){
                                                                              lcd.print('g');}else if(EEPROM.read(i) == 72){
                                                                                lcd.print('h');}else if(EEPROM.read(i) == 73){
                                                                                  lcd.print('i');}else if(EEPROM.read(i) == 74){
                                                                                    lcd.print('j');}else if(EEPROM.read(i) == 75){
                                                                                      lcd.print('k');}else if(EEPROM.read(i) == 76){
                                                                                        lcd.print('l');}else if(EEPROM.read(i) == 77){
                                                                                          lcd.print('m');}else if(EEPROM.read(i) == 78){
                                                                                            lcd.print('n');}else if(EEPROM.read(i) == 79){
                                                                                              lcd.print('o');}else if(EEPROM.read(i) == 80){
                                                                                                lcd.print('p');}else if(EEPROM.read(i) == 81){
                                                                                                  lcd.print('r');}else if(EEPROM.read(i) == 82){
                                                                                                    lcd.print('s');}else if(EEPROM.read(i) == 83){
                                                                                                      lcd.print('t');}else if(EEPROM.read(i) == 84){
                                                                                                        lcd.print('u');}else if(EEPROM.read(i) == 85){
                                                                                                          lcd.print('w');}else if(EEPROM.read(i) == 86){
                                                                                                            lcd.print('x');}else if(EEPROM.read(i) == 87){
                                                                                                              lcd.print('y');}else if(EEPROM.read(i) == 88){
                                                                                                                lcd.print('z');}else if(EEPROM.read(i) == 89){
                                                                                                                  lcd.print(' ');}  
                                                                         delay(50);                                                                                                    
                                                                  }else if(EEPROM.read(i) == 2){
                                  
                                                                 
                                                                    lcd.clear();
                                                                
                                                                    }else if(EEPROM.read(i) == 3){
                                                                                                                                    
                                                                    x_kursora = x_kursora + 1;
                                                                      lcd.setCursor(x_kursora, y_kursora);                               
                                                                      delay(50);
                                                                      
                                                                     
                                                                     }else if(EEPROM.read(i) == 4){
                                                                      x_kursora = x_kursora - 1;
                                                                      lcd.setCursor(x_kursora, y_kursora);
                                                                      delay(50);
                                                                      }else if(EEPROM.read(i) == 5){
                                                                        y_kursora = !y_kursora;
                                                                        lcd.setCursor(x_kursora, y_kursora);}}}}else if (uspienie  == 1) {
            lcd.noBacklight();
        lcd.clear();
        digitalWrite(LED3, HIGH);
       }
    aktualnyCzas = millis();
  
  roznicaCzasu = aktualnyCzas - zapamietanyCzas;
  if (roznicaCzasu >= 1000UL) {
    zapamietanyCzas = aktualnyCzas;
    sekundy++;
    if(aplikacja == 1){
      lcd.clear();}

    
  
    if(sekundy > 59){
      minuty = minuty + 1;
      sekundy = 0;}
      if(minuty > 59){
        godziny++;
        minuty = 0;}if(godziny >= 24){
          godziny = 0;
          minuty = 0;
          sekundy = 0;}}
}
