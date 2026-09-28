String appNamePL = "Zegar";
String appNameEN = "Clock";
void ClockScreen() {
  // kod dla ekranu / code for screen

  UpdateTime();
  uint8_t sec = Time(0);
  uint8_t min = Time(1);
  uint8_t h = Time(2);
  uint8_t d = Time(3);
  uint8_t m = Time(4);
  uint8_t y = Time(5);
  u8g2.setCursor(0, 32);
  if (h < 10) {
    printo('0');
  }
  printo(h);
  printo(':');
  if (min < 10) {
    printo('0');
  }
  printo(min);
  printo(':');
  if (sec < 10) {
    printo('0');
  }
  printo(sec);
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
String GetNamePLC() {
 return appNamePL;
}
String GetNameENC() {
  return appNameEN;
}