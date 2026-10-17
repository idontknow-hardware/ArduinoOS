
uint8_t s_file = 0;
bool n_file = 0;
uint8_t type = 0;
uint8_t poz = 0;
int plikPodMyszka = -1;
int plikMenu = 0;
bool menu = 0;
const unsigned char NOTKA[] PROGMEM = {
 0xfc,0x3f,0x04,0x20,0x84,0x27,0xfc,0x3f,0x04,0x26,0xfc,0x2f,
 0x04,0x38,0x74,0x23,0xd4,0x27,0xe4,0x3c,0xb4,0x26,0x94,0x3f,
 0x14,0x3e,0xf4,0x3c,0x14,0x30,0xfc,0x3f};
 const unsigned char DANE[] PROGMEM = {
  0xa7,0x13,0xb5,0x1a,0xa5,0x12,0xa5,0x12,0xa7,0x13,0xa7,0x13,
  0xb5,0x1a,0xa5,0x12,0xa5,0x12,0xa7,0x13,0xa7,0x13,0xb5,0x1a,
  0xa5,0x12,0xa5,0x12,0xa7,0x13};
const unsigned char ANIMACJA[] PROGMEM = {
 0xff,0x07,0xad,0x05,0x21,0x04,0xb3,0x05,0x6d,0x06,0xff,0x07,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char ANIMACJAL[] PROGMEM = {
 0xff,0x03,0x49,0x02,0x49,0x02,0x85,0x02,0x79,0x02,0xff,0x03,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char KOSZ[] PROGMEM = {
 0xe0,0x03,0xf0,0x07,0xf8,0x1f,0xff,0xff,0xf8,0x1f,0xf8,0x1f,
 0xf8,0x1f,0xf8,0x1f,0xf8,0x1f,0xf8,0x1f,0xf8,0x1f,0xf8,0x1f,
 0xf8,0x1f,0xf8,0x1f,0xf8,0x1f,0xf8,0x1f};
void PrzegScreen() {
  u8g2.setFont(u8g2_font_5x7_tr);
  if (n_file == 0) {
    if (menu == 0) {
  DrawButtonLang(16, 16, 9, "Nowy plik", "New file ");
  plikPodMyszka = -1;

for (int x = 0; x < 11; x++) {
  uint8_t type = GetFileType(x);
  uint8_t flag = getFileFlag(x);
  
  bool prawidlowyTyp = (type == TYPE_NOTE || type == TYPE_DATA || type == TYPE_ANIMATION || type == TYPE_BANIMATION);

  if (prawidlowyTyp) {

    if (flag == FLAG_DELETE) {
      u8g2.drawXBMP(x * 16, 32, 16, 16, KOSZ);
    } 
    else if (flag >= FLAG_CORRUPTED) {

      u8g2.drawXBMP(x * 16, 32, 16, 16, KOSZ); 
    } 
    else {

      if (type == TYPE_NOTE) u8g2.drawXBMP(x * 16, 32, 16, 16, NOTKA);
      if (type == TYPE_DATA) u8g2.drawXBMP(x * 16, 32, 16, 16, DANE);
      if (type == TYPE_ANIMATION) u8g2.drawXBMP(x * 16, 32, 16, 16, ANIMACJA);
      if (type == TYPE_BANIMATION) u8g2.drawXBMP(x * 16, 32, 16, 16, ANIMACJAL);
    }


    int xStart = x * 16;
    int xEnd = xStart + 16;
    int yStart = 32; 
    int yEnd = yStart + 16;
    
    if (mouseX >= xStart && mouseX < xEnd && mouseY >= yStart && mouseY < yEnd) {
      plikPodMyszka = x;
    }
  }
}


if (plikPodMyszka != -1) {
  u8g2.setCursor(16, 56);
  print(F("Nazwa: "), F("Name: "));
  GetFileName(plikPodMyszka);
  for (int u = 0; u < 8; u++) {
    printo(namef[u]);
  }
  u8g2.setCursor(0, 63);
  uint8_t y = 0;
  uint8_t m = 0;
  uint8_t d = 0;
  uint8_t h = 0;
  uint8_t min = 0;
  GetFileDate(y, m, d, h, min, plikPodMyszka);
  printo(F("Mod: "));
  if (h < 10) printo('0');
  printo(h); 
  printo(':');
  if (min < 10) printo('0');
  printo(min);
  
  printo(' ');
  if (d < 10) printo('0');
  printo(d);
  printo('.');
  if (m < 10) printo('0');
  printo(m);
  printo('.');
  printo("20");
  if (y < 10) printo('0');
  printo(y);
  
}
    }else {
     DrawButtonLang(16, 12, 9, "Usun  ", "Delete");
     DrawButtonLang(16, 28, 9, "Odzyskaj", "Restore ");
     DrawButtonLang(16, 44, 9, "Otworz", "Open  ");
     DrawButtonLang(16, 60, 9, "Zamknij", "Close  ");
    }
  DrawMouse();}else {
    if (s_file == 0) {
    DrawButtonLang(16, 12, 9, "Notatka", "Note   ");
    DrawButtonLang(16, 28, 9, "Dane", "Data");
    DrawButtonLang(16, 44, 9, "Animacja ", "Animation");
    DrawButtonLang(16, 60, 9, "Animacja+ ", "Animation+");}
    if (s_file == 1) {
      u8g2.setCursor(16, 16);
      for (int r = 0; r < 8; r++) {
      printo(namef[r]);}
      Keyboard(i);
    }
    DrawMouse();
  }
}
void Przeg() {
  DEBUG_PRINTLN(type);
if (n_file == 0) {
  if (menu == 0) {
if (X > 14 && Y > 8 && X < 60 && Y < 18) {
  if (i == '5') {
  n_file = 1;}}
if (i == '5' && menu == 0 && plikPodMyszka != -1) {
  plikMenu = plikPodMyszka;
  menu = 1;
  DEBUG_PRINTLN("HALO!");

}
}else {
  if (X > 14 && Y > 4 && X < 45 && Y < 13) {
    if (i == '5') {
    setFileFlag(plikMenu, FLAG_DELETE);
    DEBUG_PRINTLN("USUNIĘTO");}
  }
  if (X > 14 && Y > 22 && X < 55 && Y < 30) {
    if (i == '5') {
    setFileFlag(plikMenu, FLAG_IS);}
  }
  if (X > 14 && Y > 53 && X < 51 && Y < 61) {
    if (i == '5') {
    menu = 0;}
  }
  if (X > 14 && Y > 36 && X < 46 && Y < 46) {
    if (i == '5') {
      app = 4;
    }
  }
}}else {
  uint8_t freef = FirstFree();
  if (s_file == 0) {
    GetFileName(freef);
  if (X > 15 && Y > 6 && X < 50 && Y < 13) {
    if (i == '5') {
    type = TYPE_NOTE;
    s_file = 1;}
  }
  if (X > 15 && Y > 20 && X < 35 && Y < 30) {
    if (i == '5') {
    type = TYPE_DATA;
    s_file = 1;}
  }
  if (X > 15 && Y > 36 && X < 61 && Y < 46) {
    if (i == '5') {
      type = TYPE_ANIMATION;
      s_file = 1;
    }
  }
  if (X > 15 && Y > 53 && X < 66 && Y < 61) {
    if (i == '5') {
      type = TYPE_BANIMATION;
      s_file = 1;
    }
  }
  }if (s_file == 1) {
    if (p == 0) {
    char naz = getKeyboard();
    if (i == '5') {
      UpdateTable(naz);
    }}else {
      setFileFlag(freef, FLAG_IS);
      FileTypeUpdate(type, freef);
      UpdateFileName(freef);
      FileEditDate(freef);
      p = 0;
      s_file = 0;
      n_file = 0;
    }
  }
}
}