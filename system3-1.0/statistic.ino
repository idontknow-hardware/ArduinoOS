void statScreen() {
  u8g2.setCursor(16, 16);
  printo("RAM: ");
  printo(2048 - freeRam());
  u8g2.setCursor(16, 32);
  printo("Error: ");
  printo(blad);
}
void stat() {

}