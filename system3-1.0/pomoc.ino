int8_t x = 0;
void pomocScreen() {

  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setCursor(x + 16, 16);
  print(F("Witaj w menu pomocy!"), F("Welcome to the help menu!"));
  u8g2.setCursor(x, 32);
  print(F("Podstawy -  ."), F("Basics -  ."));
  u8g2.setCursor(x, 40);
  printo(F("* - back, B & C - scroll."));
  u8g2.setCursor(x, 48);
  print(F("Myszka:"), F("Mouse:"));
  printo(F("2,8,4,6 / joystick."));
  u8g2.setCursor(x, 56);
  print(F("Aplikacje: dino - 5, notatnik: k. ekranowa, B - zapisz, # - usun. Ustawienia - wiesz. Admin: EEPROM BUM i artefakty"), F("Apps: dino - 5, notes: screen key. B - save, # - delete. Settings: you know. Admin: EEPROM BUM and artefacts"));
}
void pomoc() {
  x--;

}