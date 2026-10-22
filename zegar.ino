void ClockScreen() {
  // kod dla ekranu / code for screen

  Ds1302::DateTime dt;
  rtc.getDateTime(&dt);
  uint8_t h = dt.hour;
  uint8_t mi = dt.minute;
  uint8_t se = dt.second;
  uint8_t d = dt.day;
  uint8_t m = dt.month;
  uint8_t y = dt.year;

  u8g2.setCursor(0, 32);
  if (h < 10) {
    printo('0');
  }
  printo(h);
  printo(':');
  if (mi < 10) {
    printo('0');
  }
  printo(mi);
  printo(':');
  if (se < 10) {
    printo('0');
  }
  printo(se);
  printo(' ');
  if (d < 10) {
    printo('0');
  }
  printo(d);
  printo('.');
  if (m < 10) {
    printo('0');
  }
  printo(m);
  printo('.');
  printo("20");
  printo(y);
  DrawMouse();
}
void Clock() {
  // twój kod / your code
}