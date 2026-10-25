
int8_t x = 0;
void pomocScreen() {

  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setCursor(x + 16, 16);
  print(F("Pomoc!"), F("Help!"));
  u8g2.setCursor(x, 32);
  print(F("Podstawy - "), F("Basics - "));
  u8g2.setCursor(x, 40);
  printo(F("* |_|, B/C - scroll."));
  u8g2.setCursor(x, 48);
  print(F("Mysz:"), F("Mouse:"));
  printo(F("2,8,4,6 / analog"));
  u8g2.setCursor(x, 56);
  printo(F("Admin: EEPROM BUM"));
}
void pomoc() {
  x--;

}
