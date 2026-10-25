int8_t obframe = 0;
int8_t lastframe = -1;
bool frame[4][8];
bool modeE = 0;
uint8_t frames = 4;
uint8_t roz = 4;
void edytorScreen() {
if (modeE == 0) {
    u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setCursor(16, 16);
  print(F("Witaj"), F("Welcome"));
  printo(plikMenu);

}else {
  for (uint8_t y = 0; y < 4; y++) {
    for (uint8_t x = 0; x < roz; x++) {
      if (frame[y][x]) {
      u8g2.drawBox(x * 8, y * 8, 8, 8);}
    }
  }
  u8g2.setCursor(16, 48);
  printo(obframe);
  DrawMouse();
if (i == '5') {
  if (roz == 4 && mouseX < 32) {
  frame[mouseY / 8][mouseX / 8] = !frame[mouseY / 8][mouseX / 8];}
  if (roz == 8) {
  frame[mouseY / 8][mouseX / 8] = !frame[mouseY / 8][mouseX / 8];   
  }
  i = 0;
}
}
}
void edytor() {
  if (GetFileType(plikMenu) == TYPE_ANIMATION) {
    frames = 4;
    roz = 4;
  }else {
    frames = 16;
    roz = 8;
  }
  if (plikMenu != 1) {
    modeE = 1;
  }
  if (i == 'B') {
    saveFrame();
    if (obframe < frames - 1) obframe++;
    delay(50);
  } 
  else if (i == 'C') {
    saveFrame();
    if (obframe > 0) obframe--;
    delay(50);
  }

  if (lastframe != obframe) {
    loadFrame();
    lastframe = obframe;
  }
}
void loadFrame() {
  uint8_t frameSize = (roz == 4) ? 16 : 4;
  uint16_t addr = GetFileAddress(plikMenu) + DataStart + obframe * frameSize;

  for (uint8_t y = 0; y < 4; y++) {
    uint8_t row = 0;

    if (roz == 4) {
      // Stary format 4x4: jeden bajt na piksel
      for (uint8_t x = 0; x < 4; x++) {
        frame[y][x] = EEPROM.read(addr + y * 4 + x) != 0;
      }
    } else {
      // Nowy format 8x4: jeden bit na piksel
      row = EEPROM.read(addr + y);

      for (uint8_t x = 0; x < 8; x++) {
        frame[y][x] = row & (1 << (7 - x));
      }
    }
  }
}
void saveFrame() {
  uint8_t frameSize = (roz == 4) ? 16 : 4;
  uint16_t addr = GetFileAddress(plikMenu) + DataStart + obframe * frameSize;

  for (uint8_t y = 0; y < 4; y++) {
    if (roz == 4) {
      // Stary format 4x4
      for (uint8_t x = 0; x < 4; x++) {
        EEPROM.update(addr + y * 4 + x, frame[y][x]);
      }
    } else {
      // Nowy format 8x4
      uint8_t row = 0;

      for (uint8_t x = 0; x < 8; x++) {
        if (frame[y][x]) {
          row |= (1 << (7 - x));
        }
      }

      EEPROM.update(addr + y, row);
    }
  }

  FileEditDate(plikMenu);
}