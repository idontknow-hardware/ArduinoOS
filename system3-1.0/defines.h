extern bool mouse;
extern uint8_t mouseX;
extern uint8_t mouseY;
extern int jezyk;
extern bool admin;
#define printo(tekst)  u8g2.print(tekst)
#define input() klawiatura.getKey()
#define changeMouse() mouse = !mouse
#define GetMouseX() mouseX
#define GetMouseY() mouseY
#define SetLanguage(j) jezyk = j
#define SetAdmin(a) admin = a
#define DrawMouse() u8g2.drawFilledEllipse(X, Y, 5, 5)