#include "defines.h"
uint8_t urz = 1;
bool wycisz = EEPROM.read(13);
int jezyk = EEPROM.read(1);
bool admin = EEPROM.read(2);
bool mouse = 0;
uint8_t mouseX = 40;
uint8_t mouseY = 30;
uint8_t TABX[] = {40, 60, 60};
uint8_t TABY[] = {35, 52, 35};
uint8_t TABidx = 0;
uint8_t freefiles = 0;
long czas = 0;
long roznicaCzasu = 0;
long oczas = 0;
uint8_t sens = EEPROM.read(11);
char keyboard[4][10] = {
  {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
  {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ' '},
  {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', ' ', ' '},
};


template<typename T>
void print(T pl, T en) {
  if (jezyk == 0) {
    u8g2.print(pl);
  } else {
    u8g2.print(en);
  }
}


bool Check() {
  return EEPROM.read(0) != 250;
}

void moveMouse(char i) {
  if (sens == 0) {
    sens = 1;
  }
  if (i == '4') {
    mouseX = mouseX - sens; 
  }
  if (i == '6') {
    mouseX = mouseX + sens; 
  }
  if (i == '2') {
    mouseY = mouseY - sens; 
  }
  if (i == '8') {
    mouseY = mouseY + sens; 
  }


  if (i == 'D') {
    mouseX = TABX[TABidx];
    mouseY = TABY[TABidx];
    TABidx++;
    if (TABidx > sizeof(TABX) / sizeof(TABX[0])) {
      TABidx = 0;
    }
  }
}



void DrawButtonLang(uint8_t X, uint8_t Y, uint8_t w, uint8_t padding_h, uint8_t padding_v, const char *pl, const char *en) {
  if (jezyk == 0) {
    u8g2.drawButtonUTF8(X, Y, U8G2_BTN_BW1, 0, 1, 1, pl);
  }else {
    u8g2.drawButtonUTF8(X, Y, U8G2_BTN_BW1, 0, 1, 1, en);    
  }
}

void ClearEEPROM() {
  for (int I = 0; I < EEPROM.length(); I++) {
    EEPROM.update(I, 0);
  }
}
void Keyboard(char i) {
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.drawButtonUTF8(0, 32, U8G2_BTN_BW1, 0, 1, 1, "1");
  u8g2.drawButtonUTF8(8, 32, U8G2_BTN_BW1, 0, 1, 1, "2");
  u8g2.drawButtonUTF8(16, 32, U8G2_BTN_BW1, 0, 1, 1, "3");
  u8g2.drawButtonUTF8(24, 32, U8G2_BTN_BW1, 0, 1, 1, "4");
  u8g2.drawButtonUTF8(32, 32, U8G2_BTN_BW1, 0, 1, 1, "5");
  u8g2.drawButtonUTF8(40, 32, U8G2_BTN_BW1, 0, 1, 1, "6");
  u8g2.drawButtonUTF8(48, 32, U8G2_BTN_BW1, 0, 1, 1, "7");
  u8g2.drawButtonUTF8(56, 32, U8G2_BTN_BW1, 0, 1, 1, "8");
  u8g2.drawButtonUTF8(64, 32, U8G2_BTN_BW1, 0, 1, 1, "9");
  u8g2.drawButtonUTF8(72, 32, U8G2_BTN_BW1, 0, 1, 1, "0");
  u8g2.drawButtonUTF8(0, 41, U8G2_BTN_BW1, 0, 1, 1, "Q");
  u8g2.drawButtonUTF8(8, 41, U8G2_BTN_BW1, 0, 1, 1, "W");
  u8g2.drawButtonUTF8(16, 41, U8G2_BTN_BW1, 0, 1, 1, "E");
  u8g2.drawButtonUTF8(24, 41, U8G2_BTN_BW1, 0, 1, 1, "R");
  u8g2.drawButtonUTF8(32, 41, U8G2_BTN_BW1, 0, 1, 1, "T");
  u8g2.drawButtonUTF8(40, 41, U8G2_BTN_BW1, 0, 1, 1, "Y");
  u8g2.drawButtonUTF8(48, 41, U8G2_BTN_BW1, 0, 1, 1, "U");
  u8g2.drawButtonUTF8(56, 41, U8G2_BTN_BW1, 0, 1, 1, "I");
  u8g2.drawButtonUTF8(64, 41, U8G2_BTN_BW1, 0, 1, 1, "O");
  u8g2.drawButtonUTF8(72, 41, U8G2_BTN_BW1, 0, 1, 1, "P");
  u8g2.drawButtonUTF8(0, 50, U8G2_BTN_BW1, 0, 1, 1, "A");
  u8g2.drawButtonUTF8(8, 50, U8G2_BTN_BW1, 0, 1, 1, "S");
  u8g2.drawButtonUTF8(16, 50, U8G2_BTN_BW1, 0, 1, 1, "D");
  u8g2.drawButtonUTF8(24, 50, U8G2_BTN_BW1, 0, 1, 1, "F");
  u8g2.drawButtonUTF8(32, 50, U8G2_BTN_BW1, 0, 1, 1, "G");
  u8g2.drawButtonUTF8(40, 50, U8G2_BTN_BW1, 0, 1, 1, "H");
  u8g2.drawButtonUTF8(48, 50, U8G2_BTN_BW1, 0, 1, 1, "J");
  u8g2.drawButtonUTF8(56, 50, U8G2_BTN_BW1, 0, 1, 1, "K");
  u8g2.drawButtonUTF8(64, 50, U8G2_BTN_BW1, 0, 1, 1, "L");
  u8g2.drawButtonUTF8(0, 59, U8G2_BTN_BW1, 0, 1, 1, "Z");
  u8g2.drawButtonUTF8(8, 59, U8G2_BTN_BW1, 0, 1, 1, "X");
  u8g2.drawButtonUTF8(16, 59, U8G2_BTN_BW1, 0, 1, 1, "C");
  u8g2.drawButtonUTF8(24, 59, U8G2_BTN_BW1, 0, 1, 1, "V");
  u8g2.drawButtonUTF8(32, 59, U8G2_BTN_BW1, 0, 1, 1, "B");
  u8g2.drawButtonUTF8(40, 59, U8G2_BTN_BW1, 0, 1, 1, "N");
  u8g2.drawButtonUTF8(48, 59, U8G2_BTN_BW1, 0, 1, 1, "M");
  u8g2.drawButtonUTF8(56, 59, U8G2_BTN_BW1, 0, 1, 1, "___");
}

char getKeyboard() {
  int WX = round(float(mouseX + 5) / 8);
  int WY = round(float(mouseY - 32 + 5) / 9);
  return keyboard[WY - 1][WX - 1];
}


uint8_t FreeFiles() {

  for (int u = 64; u < 1024; u = u + 81) {
   if (EEPROM.read(u + 1) == 0) {
    freefiles++;
    Serial.println(freefiles);
   }

  } 
    return freefiles;
}



void WriteAll() {
  EEPROM.update(0, 250);
  EEPROM.update(1, jezyk);
  EEPROM.update(2, admin);
  EEPROM.update(3, name[0]);
  EEPROM.update(4, name[1]);
  EEPROM.update(5, name[2]);
  EEPROM.update(6, name[3]);
  EEPROM.update(7, name[4]);
  EEPROM.update(8, name[5]);
  EEPROM.update(9, name[6]);
  EEPROM.update(10, name[7]);
  Serial.print(EEPROM.read(0));
  Serial.print(EEPROM.read(1));
  Serial.print(EEPROM.read(2));
}

int32_t daysFromCivil(int y, unsigned m, unsigned d) {
  y -= m <= 2;
  const int32_t  era = (y >= 0 ? y : y - 399) / 400;
  const uint32_t yoe = y - era * 400;
  const uint32_t doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
  const uint32_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
  return era * 146097 + (int32_t)doe - 719468;
}

void civilFromDays(int32_t z, int &y, unsigned &m, unsigned &d) {
  z += 719468;
  const int32_t  era = (z >= 0 ? z : z - 146096) / 146097;
  const uint32_t doe = z - era * 146097;
  const uint32_t yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
  const int      yy  = (int)yoe + era * 400;
  const uint32_t doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
  const uint32_t mp  = (5 * doy + 2) / 153;
  d = doy - (153 * mp + 2) / 5 + 1;
  m = mp + (mp < 10 ? 3 : -9);
  y = yy + (m <= 2);
}

uint32_t unixNow() {
  Ds1302::DateTime dt;
  rtc.getDateTime(&dt);
  return (uint32_t)daysFromCivil(2000 + dt.year, dt.month, dt.day) * 86400UL
       + dt.hour   * 3600UL
       + dt.minute * 60UL
       + dt.second;
}

void unixSet(uint32_t t) {
  const int32_t  days = (int32_t)(t / 86400UL);
  const uint32_t rem  = (uint32_t)(t % 86400UL);
  int y; unsigned m, d;
  civilFromDays(days, y, m, d);

  Ds1302::DateTime dt;
  dt.year   = y - 2000;
  dt.month  = m;
  dt.day    = d;
  dt.hour   = rem / 3600;
  dt.minute = (rem % 3600) / 60;
  dt.second = rem % 60;
  dt.dow    = 1;
  rtc.setDateTime(&dt);
}


void Buzz(uint16_t dur, uint16_t freq) {
  if (wycisz == 0) { 
if (urz == 1) {
tone(A0, freq, dur);
}}
}
