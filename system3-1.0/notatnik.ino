char loaded[64] = {};
uint8_t obecny = 0;
uint8_t o_n = 0;
bool wczytane = 0;
void NotScreen() {
  u8g2.setFont(u8g2_font_5x7_tr);
  Keyboard(i);
  u8g2.setCursor(0, 16);
  for (int x = 0; x < 64; x++) {
    printo(loaded[x]);
  }
  DrawMouse();
}
void Not() {
  if (wczytane == 0) {
  obecny = plikMenu;
  LoadNote();
}
  if (i == '5') {
    loaded[o_n] = getKeyboard();
    o_n++;
  }
  if (i == 'B') {
   SaveNote();
  }
  if (i == '*') {
    wczytane = 0;
  }
}
void LoadNote() {
  for (int x = 0; x < DataLength; x++) {
    loaded[x] = LoadFileByte(obecny, x);
  }
  wczytane = 1;
}
void SaveNote() {
  for (int x = 0; x < DataLength; x++) {
    SetFileByte(obecny, x, loaded[x]);
  }
  FileEditDate(obecny);
}