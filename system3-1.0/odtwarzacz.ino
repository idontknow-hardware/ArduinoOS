uint8_t oobframe = 0;
uint8_t file = 0;
long ostat = 0;
bool pauza = 0;
uint8_t ok = 4;
bool framen[4][8];
uint8_t framess = 4;
void odtwarzScreen() {
  GetFileName(file);
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setCursor(16, 48);
  print(F("Odtwarzanie: "), F("Playing: "));
  for (int r = 0; r < 8; r++) {
    printo(namef[r]);}
  u8g2.setCursor(16, 56);
  print(F("B, C - przewin"), F("B, C - scroll"));
  if (pauza) {
    u8g2.setCursor(16, 16);
    print(F("PAUZA"), F("PAUSED"));
  }

  u8g2.setCursor(0, 48);
  printo(oobframe + 1);
  printo('/');
  printo(framess);
  for (uint8_t y = 0; y < 4; y++) {
    for (uint8_t x = 0; x < ok; x++) {
      if (framen[y][x]) {
      u8g2.drawBox(x * 8, y * 8, 8, 8);}
    }
  }
}
void odtwarz() {
  if (GetFileType(file) == TYPE_ANIMATION) {
    ok = 4;
    framess = 4;
  }else {
    ok = 8;
    framess = 16;
  }
  char i = input();
if (i == 'B') {
  oobframe++;
}
if (i == 'C') {
  oobframe--;
} 
if (i == 'A') {
  pauza = !pauza;
  delay(50);
}
loadFrameO();
if (pauza == 0) {
if (millis() - ostat > 1000) {
  oobframe++;
  ostat = millis();
}}
if (oobframe > framess - 1) {
  file++;
  oobframe = 0;
}
if (GetFileType(file) == TYPE_NOTE) {
file++;
}
if (file > 10 || file < 0) {
  file = 0;
}
}
void loadFrameO() {
  uint8_t frameSize = (ok == 4) ? 16 : 4;
  uint16_t addr = GetFileAddress(plikMenu) + DataStart + oobframe * frameSize;

  for (uint8_t y = 0; y < 4; y++) {
    uint8_t row = 0;

    if (ok == 4) {
      // Stary format 4x4: jeden bajt na piksel
      for (uint8_t x = 0; x < 4; x++) {
        framen[y][x] = EEPROM.read(addr + y * 4 + x) != 0;
      }
    } else {
      // Nowy format 8x4: jeden bit na piksel
      row = EEPROM.read(addr + y);

      for (uint8_t x = 0; x < 8; x++) {
        framen[y][x] = row & (1 << (7 - x));
      }
    }
  }
}