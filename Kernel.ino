bool joystick = 0;
bool distMode = EEPROM.read(15);
unsigned long OstatniPomiar = 0; 
uint8_t urz = EEPROM.read(14);
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
uint8_t blad = 0;
int8_t temp = 0;
long czasT;
long czasZT;
void print(const __FlashStringHelper* pl, const __FlashStringHelper* en) {
  if (jezyk == 0) u8g2.print(pl);
  else            u8g2.print(en);
}
void print(const char* pl, const char* en) {
  if (jezyk == 0) u8g2.print(pl);
  else            u8g2.print(en);
}


const char keyboard[4][10] PROGMEM = {
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
    if (TABidx >= 3) {
      TABidx = 0;
    }
  }
  if (i == 'D') {
    joystick = !joystick;
  }
  if (joystick == 1) {
  if (urz == PORT_JOYSTICK) {
  mouseX = mouseX + ((analogRead(A1) - 503) / 20);
  mouseY = mouseY + ((analogRead(A2) - 519) / 20);
    DEBUG_PRINTLN("Przesunięcie X, Y:");
    DEBUG_PRINT(analogRead(A1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(analogRead(A2));
  }}
}

void DrawButtonLang(uint8_t X, uint8_t Y, uint8_t h, const char *pl, const char *en) {
  if (jezyk == 0) {
    DrawButton(X, Y, h, pl);
  } else {
    DrawButton(X, Y, h, en);    
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

      u8g2.print((char)pgm_read_byte(&(keyboard[r][c])));
    }
  }

}

char getKeyboard() {
  int WX = round(float((mouseX + 5) / 8)); 
  int WY = round(float((mouseY - 32 + 5) / 9)); 

  return (char)pgm_read_byte(&(keyboard[WY - 1][WX - 1]));
}

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
  DEBUG_PRINTLN(freefiles);
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

  #if DEBUG
    DEBUG_PRINT(EEPROM.read(0));
    DEBUG_PRINT(EEPROM.read(1));
    DEBUG_PRINT(EEPROM.read(2));
  #endif
}

void UpdatePort() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  

  if (urz == PORT_BUZZER) { 
    pinMode(A0, OUTPUT);
  }
  if (urz == PORT_JOYSTICK) {
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A0, INPUT_PULLUP);
  }
  if (urz == PORT_DISTANCE) { 
    pinMode(A0, OUTPUT);
    pinMode(A1, INPUT);
  }
  if (urz == PORT_BALI || urz == PORT_BUTTONS) {
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
  }
  if (urz == PORT_RGB) { 
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
  }

}
void Buzz(uint16_t dur, uint16_t freq) {
  if (wycisz == 0 && urz == 1) { 
    tone(A0, freq, dur);
  }
}
uint16_t ReadDistance() {
  if (urz != PORT_DISTANCE) return 0;

  digitalWrite(A0, LOW);
  delayMicroseconds(2);
  digitalWrite(A0, HIGH);
  delayMicroseconds(10);
  digitalWrite(A0, LOW);

  unsigned long duration = pulseIn(A1, HIGH, 20000UL); 
  

  if (duration == 0) {
    return 999; 
  }

  uint16_t wynik = duration / 58;
  

  if (wynik == 0) {
    return 1;
  }

  #if DEBUG
    Serial.println(wynik);
  #endif

  return wynik; 
}
void RGB(uint8_t r, uint8_t g, uint8_t b) {
  if (urz == PORT_RGB) {
    digitalWrite(A0, r);
    digitalWrite(A1, g);
    digitalWrite(A2, b);
  }
} 
int8_t temperature() {
  byte data[9];
  byte addr[8];
  int8_t celsius;
  if (!ds.search(addr)) {
    ds.reset_search();
    delay(2);
    return;
  }
  if (OneWire::crc8(addr, 7) != addr[7]) {
    blad = 1;
      //Serial.println("Blad: Niepoprawna suma kontrolna adresu CRC!");
      return;
  }
  if (addr[0] != 0x28) {
    blad = 2;
      //Serial.println("Blad: Znalezione urzadzenie to nie DS18B20.");
      return;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44);
  delay(2);         
  

  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);      

  for (int i = 0; i < 9; i++) {           
    data[i] = ds.read();
  }
int16_t raw = (data[1] << 8) | data[0];
celsius = raw / 16; 
  return celsius;
}
int Battery() {
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  
  long result = ADCL;
  result |= ADCH << 8;
  result = 1125300L / result;
  int percent = map(result, 4000, 5181, 0, 100);
  return constrain(percent, 0, 100);
}
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
void Info() {
  czasT = millis();
  u8g2.drawLine(0, 55, 128, 55);
  u8g2.setCursor(1, 64);
  if (czasT - czasZT > 1000) {
    temp = temperature();
    czasZT = czasT;
  }
  printo("Temp: ");
  printo(temp);
  printo(" Batt: ");
  printo(Battery());
  printo(" RAM: ");
  printo(2048 - freeRam());
}