
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
char namef[8] = {};
uint8_t sens = EEPROM.read(11);
uint8_t o = 0;
bool p = 0;


const char keyboard[4][10] = {
  {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
  {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ' '},
  {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', ' ', ' '},
};

bool Check() {
  return EEPROM.read(0) != 250;
}

void moveMouse(char i) {
  if (sens == 0) {
    sens = 1;
  }
  if (i == '4') mouseX -= sens; 
  if (i == '6') mouseX += sens; 
  if (i == '2') mouseY -= sens; 
  if (i == '8') mouseY += sens; 

  if (i == 'D') {
    mouseX = TABX[TABidx];
    mouseY = TABY[TABidx];
    TABidx++;
    if (TABidx >= sizeof(TABX) / sizeof(TABX[0])) {
      TABidx = 0;
    }
  }
}

void DrawButtonLang(uint8_t X, uint8_t Y, uint8_t w, uint8_t padding_h, uint8_t padding_v, const char *pl, const char *en) {
  if (jezyk == 0) {
    u8g2.drawButtonUTF8(X, Y, U8G2_BTN_BW1, 0, 1, 1, pl);
  } else {
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
  for (uint8_t r = 0; r < 4; r++) {
    for (uint8_t c = 0; c < 10; c++) {
      uint8_t x = c * 8;
      uint8_t y = 32 + (r * 9);

      u8g2.drawFrame(x, y - 6, 7, 8);
      u8g2.setCursor(x + 1, y);
      
      if (r == 3 && c >= 7) {
        if (c == 7) u8g2.print(F("_"));
        break; 
      }
      u8g2.print(keyboard[r][c]);
    }
  }
}


char getKeyboard() {
  int WX = round(float(mouseX + 5) / 8); 
  int WY = round(float(mouseY - 32 + 5) / 9); 
  return keyboard[WY - 1][WX - 1];}

uint16_t GetFileAddress(uint8_t plik) {
  return StartFile + (plik * FileLength);
}

uint8_t FreeFiles() {
  freefiles = 0;
  for (uint8_t i = 0; i < 11; i++) {
    uint16_t addr = GetFileAddress(i);
    uint8_t fType = EEPROM.read(addr + Type);
    if (fType == 0 || fType == 255) {
      freefiles++;
    }
  } 
  Serial.println(freefiles);
  return freefiles;
}

uint8_t GetFileType(uint8_t plik) {
  return EEPROM.read(GetFileAddress(plik) + Type);
}

int8_t FirstFree() {
  for (uint8_t i = 0; i < 11; i++) {
    uint16_t addr = GetFileAddress(i);
    uint8_t fileType = EEPROM.read(addr + Type);
    uint8_t fileFlag = EEPROM.read(addr + Flag);
    
    if (fileType == 0 || fileType == 255 || fileFlag == FLAG_DELETE) {
      return i;
    }
  }
  return -1;
}

void GetFileName(uint8_t plik) {
  uint16_t addr = GetFileAddress(plik) + NameBegin;
  for (int y = 0; y < 8; y++) {
    namef[y] = EEPROM.read(addr + y);
  }
}

void UpdateFileName(uint8_t plik) {
  uint16_t addr = GetFileAddress(plik) + NameBegin;
  for (int y = 0; y < 8; y++) {
    EEPROM.update(addr + y, namef[y]); 
  }
}

void FileEditDate(uint8_t plik) {
  Ds1302::DateTime dt;
  rtc.getDateTime(&dt);
  
  uint16_t addr = GetFileAddress(plik);
  EEPROM.update(addr + Year, dt.year); 
  EEPROM.update(addr + Month, dt.month);
  EEPROM.update(addr + Day, dt.day);
  EEPROM.update(addr + Hour, dt.hour);
  EEPROM.update(addr + Min, dt.minute);
}

void FileTypeUpdate(uint8_t type, uint8_t plik) {
  uint16_t addr = GetFileAddress(plik);
  EEPROM.update(addr, FLAG_IS);
  EEPROM.update(addr + Type, type);
}

void UpdateTable(char ok) {
  namef[o] = ok;
  o++;
  if (o == 8) {
    p = 1;
  }
}

void GetFileDate(uint8_t &y, uint8_t &m, uint8_t &d, uint8_t &h, uint8_t &min, uint8_t plik) {
  uint16_t addr = GetFileAddress(plik);
  y = EEPROM.read(addr + Year);
  m = EEPROM.read(addr + Month);
  d = EEPROM.read(addr + Day);
  h = EEPROM.read(addr + Hour);
  min = EEPROM.read(addr + Min);
}

void setFileFlag(uint8_t plik, uint8_t flag) {
  uint16_t addr = GetFileAddress(plik);
  EEPROM.update(addr, flag);
}

uint8_t getFileFlag(uint8_t plik) {
  uint16_t addr = GetFileAddress(plik);
  return EEPROM.read(addr);
}
uint8_t LoadFileByte(uint8_t plik, uint8_t idx) {
  uint16_t addr = GetFileAddress(plik);
  return EEPROM.read(addr + DataStart + idx);
}
uint8_t SetFileByte(uint8_t plik, uint8_t idx, uint8_t war) {
  uint16_t addr = GetFileAddress(plik);
  EEPROM.update(addr + DataStart + idx, war);
}

void WriteAll() {
  EEPROM.update(0, 250);
  EEPROM.update(1, jezyk);
  EEPROM.update(2, admin);
  

  for (uint8_t k = 0; k < 8; k++) {
    EEPROM.update(3 + k, name[k]);
  }


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
  if (wycisz == 0 && urz == 1) { 
    tone(A0, freq, dur);
  }
}
