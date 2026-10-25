
extern uint8_t mouseX;
extern uint8_t mouseY;
extern int jezyk;
extern bool admin;
extern bool p;
extern int plikMenu;
extern uint8_t urz;
extern int scaleXJ;
extern int scaleYJ;
extern bool distMode;
extern unsigned long OstatniPomiar;
char keys[4][4] = { //mapowanie klawiatury 
{'A','3','2','1'}, 
{'B','6','5','4'}, 
{'C','9','8','7'}, 
{'D','#','0','*'}}; 
byte rowPins[4] = {5, 4, 3, 2};  //piny wierszy
byte colPins[4] = {6, 7, 8, 9};  //piny kolumn
uint8_t c_k = 0;
uint8_t r_k = 0;
bool key() {
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  bool wynik = 1;
  for (c_k = 0; c_k < 4; c_k++) {
    digitalWrite(colPins[c_k], LOW);
    for (r_k = 0; r_k < 4; r_k++) {
      wynik = digitalRead(rowPins[r_k]);
      if (wynik == 0) {
        return wynik;
      }
    }
    digitalWrite(colPins[c_k], HIGH);
  }
  return 1;
}
char keypad() {
  bool wynik = key();
  if (wynik == 0) {
  return keys[r_k][c_k];}else {
    return ' ';
  }
}
#define printo(tekst)  u8g2.print(tekst)

#define GetMouseX() mouseX
#define GetMouseY() mouseY
#define SetLanguage(j) jezyk = j
#define SetAdmin(a) admin = a
#define DrawMouse() u8g2.drawDisc(X, Y, 3)
// pliki
#define StartFile 65
#define FileLength 80
#define Flag 0
#define Type 1
#define NameBegin 2
#define NameEnd 10
#define Year 11
#define Month 12
#define Day 13
#define Hour 14
#define Min 15
#define DataStart 16
#define DataEnd 80
#define DataLength 64
#define FLAG_IS 0x01
#define FLAG_DELETE 0x02
#define FLAG_CORRUPTED 0x03
#define TYPE_NOTE 0x01
#define TYPE_DATA 0x02
#define TYPE_ANIMATION 0x03
#define TYPE_BANIMATION 0x04
// port
#define DEBUG 0
#if DEBUG
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif
#define PORT_NOTHING 0x00
#define PORT_BUZZER 0x01
#define PORT_JOYSTICK 0x02
#define PORT_DISTANCE 0x03
#define PORT_BALI 0x04
#define PORT_RGB 0x05
#define PORT_BUTTONS 0x06
#define DIST_MODE_SAVER 0x00
#define DIST_MODE_SCROLL 0x01
char input() {
  if (urz == PORT_JOYSTICK && digitalRead(A0) == 0) {
    return '5';
  }

  return keypad();
}
void DrawButton(uint8_t x, uint8_t y, uint8_t h, const char *text) {
  uint8_t szerokosc = (strlen(text) * 5) + 2; 
  u8g2.drawFrame(x, y - 6, szerokosc, h + 2);
  u8g2.setCursor(x + 1, y + h - 7); 
  printo(text);
}
