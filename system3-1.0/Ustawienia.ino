String appNamePL2 = "Ustawienia";
String appNameEN2 = "Settings  ";
uint8_t set_min = 0;
uint8_t set_h = 0;
uint8_t set_day = 0;
uint8_t set_month = 0;
uint8_t set_year = 0;
uint8_t stru = 0;
uint8_t i_n = 0;
int scroll = 0;
void SettScreen() {
 u8g2.setFont(u8g2_font_5x7_tr);
 if (stru == 0) {
if (i == 'B') {
  scroll--;
}
if (i == 'C') {
  scroll++;
}
 DrawButtonLang(16, scroll + 16, 0, 1, 1, "Czas", "Time");
 DrawButtonLang(16, scroll + 32, 0, 1, 1, "Czas dzialania", "Work time      ");
 DrawButtonLang(16, scroll + 48, 0, 1, 1, "Zmien nazwe", "Change nick");
 DrawButtonLang(16, scroll + 64, 0, 1, 1, "Opcje Admina   ", "Admin Settings");
 DrawButtonLang(16, scroll + 80, 0, 1, 1, "Jezyk   ", "Language");
 DrawButtonLang(16, scroll + 96, 0, 1, 1, "Info o systemie", "System info    ");
 DrawButtonLang(16, scroll + 112, 0, 1, 1, "Czulosc myszy  ", "Mouse sensivity");
}if (stru == 1) {
 u8g2.setCursor(16, 16);
 printo(set_min);
 printo(F(" min "));
 printo(set_h);
 printo(F(" h "));
 printo(set_day);
 printo(F(" d "));
 printo(set_month);
 printo(F(" mn "));
 printo(set_year);
 printo(F(" y"));
 u8g2.drawButtonUTF8(16, 32, U8G2_BTN_BW1, 0, 1, 1, "+");
 u8g2.drawButtonUTF8(16, 48, U8G2_BTN_BW1, 0, 1, 1, "-");
 u8g2.drawButtonUTF8(47, 32, U8G2_BTN_BW1, 0, 1, 1, "+");
 u8g2.drawButtonUTF8(47, 48, U8G2_BTN_BW1, 0, 1, 1, "-");
 u8g2.drawButtonUTF8(68, 32, U8G2_BTN_BW1, 0, 1, 1, "+");
 u8g2.drawButtonUTF8(68, 48, U8G2_BTN_BW1, 0, 1, 1, "-");
 u8g2.drawButtonUTF8(89, 32, U8G2_BTN_BW1, 0, 1, 1, "+");
 u8g2.drawButtonUTF8(89, 48, U8G2_BTN_BW1, 0, 1, 1, "-");
 u8g2.drawButtonUTF8(113, 32, U8G2_BTN_BW1, 0, 1, 1, "+");
 u8g2.drawButtonUTF8(113, 48, U8G2_BTN_BW1, 0, 1, 1, "-");
}if (stru == 2) {
  u8g2.setCursor(0, 32);
  print("Urzadzenie dziala przez: ", "System works for: ");
  u8g2.setCursor(0, 48);
  printo(millis());
  printo("ms/");
  printo(millis() / 1000);
  printo("s/");
  printo(millis() / 60000);
  printo("min/");
  printo(millis() / 3600000);
  printo("h");
}if (stru == 3) {
  Keyboard(i);
  u8g2.setCursor(64, 8);
  for (int o = 0; o < 9; o++) {
    printo(name[o]);
  }
}if (stru == 4) {
  u8g2.setCursor(0, 6);
  printo("Admin: ");
  printo(admin);
  DrawButtonLang(0, 16, 0, 1, 1, "Artefakty graficzne", "Grafphic artefacts");
  u8g2.setCursor(0, 32);
  printo(liczbaart);
  DrawButtonLang(0, 48, 0, 1, 1, "Zmien Admin", "Change Admin");
  DrawButtonLang(0, 60, 0, 1, 1, "Wyczysc EEPROM", "Erase EEPROM");
}if (stru == 5) {
  u8g2.setCursor(16, 16);
  print("Zmien jezyk", "Change Language");
  u8g2.drawButtonUTF8(16, 32, U8G2_BTN_BW1, 0, 1, 1, "PL");
  u8g2.drawButtonUTF8(32, 32, U8G2_BTN_BW1, 0, 1, 1, "EN");
}if (stru == 6) {
  u8g2.setCursor(0, 16);
  print("Informacje o systemie:", "System info:");
  u8g2.setCursor(0, 24);
  print("Rozdzielczosc ekranu: ", "Screen Resolution: ");
  u8g2.setCursor(0, 32);
  printo(u8g2.getDisplayWidth());
  printo("x");
  printo(u8g2.getDisplayHeight());
  u8g2.setCursor(0, 48);
  print("Wersja systemu:", "System version:");
  u8g2.setCursor(0, 56);
  printo("ArduinoOS 3 v. pre1f3-1.0");
}if (stru == 7) {
  u8g2.setCursor(0, 16);
  print("Ustaw czulosc myszy", "Set mouse sensivity");
  u8g2.setCursor(0, 32);
  printo(sens);
  u8g2.drawButtonUTF8(16, 48, U8G2_BTN_BW1, 0, 1, 1, "+");
  u8g2.drawButtonUTF8(32, 48, U8G2_BTN_BW1, 0, 1, 1, "-");
}
  DrawMouse();}
void Sett() {
  Serial.println(scroll);
  if (i == 'A') {
    stru = 0;
  }
if (stru == 0) {
 if (X > 15 and Y > scroll + 9 and X < 36 and Y < scroll + 18) {
  if (i == '5') {
  stru = 1;}
 }
 if (X > 15 and Y > scroll + 24 and X < 85 and Y < scroll + 33) {
  if (i == '5') {
  stru = 2;}
 }
 if (X > 14 and Y > scroll + 40 and X < 70 and Y < scroll + 50) {
  if (i == '5') {
    stru = 3;}
 }
 if (X > 15 and Y > scroll + 55 and X < 91 and Y < scroll + 64) {
  if (i == '5') {
    stru = 4;
  }
 }
 if (X > 14 and Y > scroll + 72 and X < 56 and Y < 83) {
  if (i == '5') {
    stru = 5;
  }
 }
 if (X > 14 and Y > scroll + 87 and X < 92 and Y + scroll < 98) {
  if (i == '5') {
  stru = 6;}
 }
 if (X > 14 and Y > scroll + 104 and X < 91 and Y < scroll + 114) {
  if (i == '5') {
    stru = 7;
  }
 }
}if (stru == 1) {
  if (i == '5') {
  if (X > 14 and Y > 24 and X < 21 and Y < 34) {
    set_min++;
  }
  if (X > 45 and Y > 24 and X < 52 and Y < 34) {
    set_h++;
  }
  if (X > 66 and Y > 24 and X < 73 and Y < 34) {
    set_day++;
  }
    if (X > 87 and Y > 24 and X < 94 and Y < 34) {
    set_month++;
  }
    if (X > 110 and Y > 24 and X < 117 and Y < 34) {
    set_year++;
  }
  if (X > 14 and Y > 40 and X < 21 and Y < 49) {
    set_min--;
  }
  if (X > 45 and Y > 40 and X < 52 and Y < 49) {
    set_h--;
  }
  if (X > 66 and Y > 40 and X < 73 and Y < 49) {
    set_day--;
  }
  if (X > 87 and Y > 40 and X < 94 and Y < 49) {
    set_month--;
  }
  if (X > 110 and Y > 40 and X < 117 and Y < 49) {
    set_year--;
  }
  }if (i == '#') {
          Ds1302::DateTime dt = {
  .year = set_year,
   .month = set_month,
   .day = set_day,
  .hour = set_h,
   .minute = set_min,
    .second = 0,
   .dow = 1
 };
  rtc.setDateTime(&dt);
  }
}if (stru == 3) {
  if (i == '5') {
  char k = getKeyboard();
  name[i_n] = k;
  i_n++;}
  if (i_n > 8) {
    WriteAll();
    stru = 0;
    i_n = 0;
  }
}if (stru == 4) {
  if (admin == 1) {
  if (X > 0 and Y > 8 and X < 94 and Y < 18) {
    if (i == '5') {
    liczbaart++;}
  }
  if (X > 0 and Y > 53 and X < 69 and Y < 60) {
    if (i == '5') {
      for (int io = 0; io < EEPROM.length(); io++) {
        EEPROM.update(io, 0);
      }
      app = -1;
    }
  }}
  if (X > 0 and Y > 41 and X < 54 and Y < 51) {
    if (i == '5') {
    SetAdmin(!admin);
    WriteAll();}
  }
}if (stru == 5) {
  if (X > 14 and Y > 24 and X < 25 and Y < 33) {
    if (i == '5') {
    SetLanguage(0);
    WriteAll();}
  }
  if (X > 31 and Y > 25 and X < 41 and Y < 33) {
    if (i == '5') {
    SetLanguage(1);
    WriteAll();}
  }
}if (stru == 7) {
  if (X > 15 and Y > 40 and X < 22 and Y < 49) {
    if (i == '5') {
    sens++;
    EEPROM.update(11, sens);}
  }
  if (X > 30 and Y > 41 and X < 37 and Y < 49) {
    if (i == '5') {
      sens--;
      EEPROM.update(11, sens);
    }
  }
}}
String GetNamePLU() {
 return appNamePL2;
}
String GetNameENU() {
  return appNameEN2;
}