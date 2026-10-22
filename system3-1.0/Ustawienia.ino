

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
  switch (stru) {
case 0: {
    if (i == 'B') scroll--;
    if (i == 'C') scroll++;
    u8g2.setCursor(8, 56);
    u8g2.print(scroll);
    DrawButtonLang(16, scroll + 16,  9, "Czas", "Time");
    DrawButtonLang(16, scroll + 32,  9, "Czas dzialania", "Work time      ");
    DrawButtonLang(16, scroll + 48,  9, "Zmien nazwe", "Change nick");
    DrawButtonLang(16, scroll + 64,  9, "Opcje Admina   ", "Admin Settings");
    DrawButtonLang(16, scroll + 80,  9, "Jezyk   ", "Language");
    DrawButtonLang(16, scroll + 96,  9, "Info o systemie", "System info    ");
    DrawButtonLang(16, scroll + 112, 9, "Czulosc myszy  ", "Mouse sensivity");
    DrawButtonLang(16, scroll + 128, 9, "Ustawienia portu", "Port settings");
    DrawButton(16, scroll + 144, 9, "Backup");
    break;}
 case 1: {
    u8g2.setCursor(16, 16);
    printo(set_min);   printo(F(" min "));
    printo(set_h);     printo(F(" h "));
    printo(set_day);   printo(F(" d "));
    printo(set_month); printo(F(" mn "));
    printo(set_year);  printo(F(" y"));
    

    DrawButton(16, 32, 9, "+");
    DrawButton(16, 48, 9, "-");
    DrawButton(47, 32, 9, "+");
    DrawButton(47, 48, 9, "-");
    DrawButton(68, 32, 9, "+");
    DrawButton(68, 48, 9, "-");
    DrawButton(89,  32, 9, "+");
    DrawButton(89,  48, 9, "-");
    DrawButton(113, 32, 9, "+");
    DrawButton(113, 48, 9, "-");
    break;}
 case 2: {
    u8g2.setCursor(0, 32);
    print(F("Urzadzenie dziala przez: "), F("System works for: "));
    
    u8g2.setCursor(0, 48);
    uint32_t ms = millis();
    printo(ms);                 printo(F("ms/"));
    printo(ms / 1000);          printo(F("s/"));
    printo(ms / 60000);         printo(F("min/"));
    printo(ms / 3600000);       printo(F("h"));
    break;}
case 3: {
  u8g2.setCursor(0, 10);
  Keyboard(i);
  u8g2.setCursor(64, 8);

  for (int o = 0; o < 9; o++) {
    printo(name[o]);
  }
  break;}
case 4: {
    u8g2.setCursor(0, 6);
    printo(F("Admin: "));
    printo(admin);
    DrawButtonLang(0, 16,9, "Artefakty graficzne", "Grafphic artefacts");
    u8g2.setCursor(0, 32);
    printo(liczbaart);
    DrawButtonLang(0, 48,9, "Zmien Admin", "Change Admin");
    DrawButtonLang(0, 60,9, "Wyczysc EEPROM", "Erase EEPROM");
    break;}
case 5: {u8g2.setCursor(16, 16);
    print(F("Zmien jezyk"), F("Change Language"));
    DrawButton(16, 32, 9, "PL");
    DrawButton(32, 32, 9, "EN");
    break;}
case 6: {
    u8g2.setCursor(0, 16);
    print(F("Informacje o systemie:"), F("System info:"));
    u8g2.setCursor(0, 24);
    print(F("Rozdzielczosc ekranu: "), F("Screen Resolution: "));
    u8g2.setCursor(0, 32);
    
    printo(128);
    printo('x');
    printo(64);
    
    u8g2.setCursor(0, 48);
    print(F("Wersja systemu:"), F("System version:"));
    u8g2.setCursor(0, 56);
    printo(F("ArduinoOS 3 v. pre7af3-1.0"));
    break;}
case 7: { 
    u8g2.setCursor(0, 16);
    print(F("Ustaw czulosc myszy"), F("Set mouse sensivity"));
    u8g2.setCursor(0, 32);
    printo(sens);
    DrawButton(16, 48, 9, "+");
    DrawButton(32, 48, 9, "-");
    break;}
case 8: {    if (urz == PORT_BUZZER) {
    DrawButtonLang(16, 16,9, "Wycisz", "Mute  ");}
    if (urz == PORT_DISTANCE) {
      if (distMode == DIST_MODE_SAVER) {
      DrawButtonLang(16, 16,9, "Odleglosc: wygaszacz", "Distance: saver");}else {
        DrawButtonLang(16, 16,9, "Odleglosc: scroll", "Distance: scroll");
      }
    }
    switch (urz) {
      case PORT_NOTHING:
    DrawButtonLang(16, 32,9, "Nic        ", "Nothing    ");
    break;
    case PORT_BUZZER:
    DrawButton(16, 32,9, "Buzzer     ");   
    break;
    case PORT_JOYSTICK:
    DrawButton(16, 32,9, "Joystick   ");
    break;
    case PORT_DISTANCE:
    DrawButtonLang(16, 32,9, "Odleglosc  ", "Distance   "); 
    break;
    case PORT_BALI:
    DrawButton(16, 32,9, "Bali Switch    "); 
    break;
    case PORT_RGB:
    DrawButton(16, 32,9, "RGB             ");   
    break;
    case PORT_BUTTONS:
        DrawButtonLang(16, 32,9, "Przyciski  ", "Buttons    ");
        break;    
    }
    break;}
}

  
  DrawMouse();
}

void Sett() {
  //Serial.println(scroll);
  if (i == 'A') {
    stru = 0;
  }
  switch (stru) {
    case 0:
    if (X > 15 && Y > scroll + 9 && X < 36 && Y < scroll + 18)   if (i == '5') stru = 1;
    if (X > 15 && Y > scroll + 24 && X < 85 && Y < scroll + 33)  if (i == '5') stru = 2;
    if (X > 14 && Y > scroll + 40 && X < 70 && Y < scroll + 50)  if (i == '5') stru = 3;
    if (X > 15 && Y > scroll + 55 && X < 91 && Y < scroll + 64)  if (i == '5') stru = 4;
    if (X > 14 && Y > scroll + 72 && X < 56 && Y < 83)           if (i == '5') stru = 5;
    if (X > 14 && Y > scroll + 87 && X < 92 && Y + scroll < 98)  if (i == '5') stru = 6;
    if (X > 14 && Y > scroll + 104 && X < 91 && Y < scroll + 114) if (i == '5') stru = 7;
    if (X > 14 && Y > scroll + 120 && X < 106 && Y < scroll + 130)if (i == '5') stru = 8;

    break;
    case 1:
    if (i == '5') {
      if (X > 14 && Y > 24 && X < 21 && Y < 34)   set_min++;
      if (X > 45 && Y > 24 && X < 52 && Y < 34)   set_h++;
      if (X > 66 && Y > 24 && X < 73 && Y < 34)   set_day++;
      if (X > 87 && Y > 24 && X < 94 && Y < 34)   set_month++;
      if (X > 110 && Y > 24 && X < 117 && Y < 34) set_year++;
      
      if (X > 14 && Y > 40 && X < 21 && Y < 49)   set_min--;
      if (X > 45 && Y > 40 && X < 52 && Y < 49)   set_h--;
      if (X > 66 && Y > 40 && X < 73 && Y < 49)   set_day--;
      if (X > 87 && Y > 40 && X < 94 && Y < 49)   set_month--;
      if (X > 110 && Y > 40 && X < 117 && Y < 49) set_year--;
    }
    if (i == '#') {
  Ds1302::DateTime dt;
  dt.year   = set_year;
  dt.month  = set_month;
  dt.day    = set_day;
  dt.hour   = set_h;
  dt.minute = set_min;
  dt.second = 0;
  dt.dow    = 1;
  rtc.setDateTime(&dt);
    }
    break;
    case 3:
    if (i == '5') {
      char k = getKeyboard();
      name[i_n] = k;
      i_n++;
    }
    if (i_n > 8) {
      WriteAll();
      stru = 0;
      i_n = 0;
    }
    break;
    case 4:
    if (admin == 1) {
      if (X > 0 && Y > 8 && X < 94 && Y < 18) {
        if (i == '5') liczbaart++;
      }
      if (X > 0 && Y > 53 && X < 69 && Y < 60) {
        if (i == '5') {
          ClearEEPROM(); 
          app = -1;
        }
      }
    }
    if (X > 0 && Y > 41 && X < 54 && Y < 51) {
      if (i == '5') {
        SetAdmin(!admin);
        WriteAll();
      }
    }
    break;
    case 5:
    if (X > 14 && Y > 24 && X < 25 && Y < 33) {
      if (i == '5') { SetLanguage(0); WriteAll(); }
    }
    if (X > 31 && Y > 25 && X < 41 && Y < 33) {
      if (i == '5') { SetLanguage(1); WriteAll(); }
    }
    break;
    case 7:
    if (X > 15 && Y > 40 && X < 22 && Y < 49) {
      if (i == '5') { sens++; EEPROM.update(11, sens); }
    }
    if (X > 30 && Y > 41 && X < 37 && Y < 49) {
      if (i == '5') { sens--; EEPROM.update(11, sens); }
    }
    break;
    case 8:
    if (X > 14 && Y > 10 && X < 44 && Y < 18) {
      if (i == '5') {
        if (urz == PORT_BUZZER) {
        wycisz = !wycisz;
        EEPROM.update(13, wycisz);} if (urz == PORT_DISTANCE) {
          distMode = !distMode;
          EEPROM.update(15, distMode);
          DEBUG_PRINTLN(distMode);
        }
      }
    }

      
    
    if (X > 14 && Y > 24 && X < 72 && Y < 34) {
      if (i == '5') {
        urz++;
        EEPROM.update(14, urz);
        UpdatePort();
        if (urz > 6) {
          urz = 0;
        }
      }
    }
    break;
  }

  

  

  
  
}