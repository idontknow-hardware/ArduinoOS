void ClockScreen() {
  // kod dla ekranu / code for screen

  uint32_t t = unixNow();
  int32_t days = (int32_t)(t / 86400UL);
  uint32_t rem = (uint32_t)(t % 86400UL);
  int y;
  unsigned m, d;
  civilFromDays(days, y, m, d);
  uint8_t h = rem / 3600;
  uint8_t mi = (rem % 3600) / 60;
  uint8_t se = rem % 60;

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
  printo(y);
  DrawMouse();
}
void Clock() {
  // twój kod / your code
}