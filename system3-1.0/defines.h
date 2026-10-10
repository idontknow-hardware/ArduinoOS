extern bool mouse;
extern uint8_t mouseX;
extern uint8_t mouseY;
extern int jezyk;
extern bool admin;
extern bool p;
extern int plikMenu;
#define printo(tekst)  u8g2.print(tekst)
#define input() klawiatura.getKey()
#define changeMouse() mouse = !mouse
#define GetMouseX() mouseX
#define GetMouseY() mouseY
#define SetLanguage(j) jezyk = j
#define SetAdmin(a) admin = a
#define DrawMouse() u8g2.drawDisc(X, Y, 3)
// pliki
#define StartFile 65
#define FileLength 80
#define Flag 0
#define Type 1
#define NameBegin 2
#define NameEnd 10
#define Year 11
#define Month 12
#define Day 13
#define Hour 14
#define Min 15
#define DataStart 16
#define DataEnd 80
#define DataLength 64
#define FLAG_IS 0x01
#define FLAG_DELETE 0x02
#define FLAG_CORRUPTED 0x03
#define TYPE_NOTE 0x01
#define TYPE_DATA 0x02
#define TYPE_ANIMATION 0x03
#define TYPE_BANIMATION 0x04

template<typename T>
void print(T pl, T en) {
  if (jezyk == 0) {
    u8g2.print(pl);
  } else {
    u8g2.print(en);
  }
}