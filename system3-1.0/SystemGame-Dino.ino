

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define GROUND_Y        32
#define JUMP_AMPLITUDE  16
#define JUMP_DURATION   2000UL
#define CLEAR_Y         24
#define SINTAB_LEN      32

uint8_t y_player = GROUND_Y;
int x_kaktus[3] = {16, 16, 16};
unsigned long czass = 0;
unsigned long zapis_czas = 0;
unsigned long roz_czas = 0;
uint8_t wynik = 0;
uint8_t naj_wynik = EEPROM.read(12);
uint8_t speed = 1;
uint8_t ostatni_wynik = 0;

unsigned long jump_start = 0;
bool is_jumping = false;

const uint8_t sintab[32] PROGMEM = {
    0,  10,  20,  30,  39,  49,  57,  65,
   72,  79,  85,  90,  94,  97,  99, 100,
  100,  99,  97,  94,  90,  85,  79,  72,
   65,  57,  49,  39,  30,  20,  10,   0
};

const unsigned char dino[] PROGMEM = {
 0x00,0x00,0xf8,0x03,0x08,0x3c,0x2c,0x60,0x0c,0x78,0xf8,0x0f,
 0xf0,0x03,0x18,0x1f,0x08,0x12,0x08,0x02,0x08,0x1f,0x18,0x11,
 0xf0,0x01,0x20,0x01,0x20,0x01,0x60,0x03};
const unsigned char kaktus[] PROGMEM = {
 0xc0,0x00,0xe0,0x01,0xe0,0x01,0xe6,0x19,0xec,0x0d,0xf8,0x07,
 0xf0,0x07,0xe0,0x01,0xe6,0x19,0xec,0x09,0xf8,0x0d,0xf8,0x07,
 0xf0,0x03,0xe0,0x01,0xe0,0x01,0xe0,0x01};

void dino_jump() {
  if (!is_jumping) {
    is_jumping = true;
    jump_start = millis();
  }
}

void update_jump() {
  if (!is_jumping) return;

  unsigned long elapsed = millis() - jump_start;

  if (elapsed >= JUMP_DURATION) {
    is_jumping = false;
    y_player = GROUND_Y;
    return;
  }

  uint8_t idx = (uint8_t)((uint32_t)elapsed * SINTAB_LEN / JUMP_DURATION);
  if (idx >= SINTAB_LEN) idx = SINTAB_LEN - 1;

  uint8_t arc = pgm_read_byte(&sintab[idx]);
  y_player = GROUND_Y - (uint8_t)((uint16_t)JUMP_AMPLITUDE * arc / 100);
}

void DinoScreen() {
  u8g2.setFont(u8g2_font_5x7_tr);
  for (int ik = 0; ik < 3; ik++) {
    u8g2.drawXBMP(x_kaktus[ik], 32, 16, 16, kaktus);
  }
  u8g2.drawXBMP(16, y_player, 16, 16, dino);
  u8g2.setCursor(16, 8);
  print("Wynik: ", "Score: ");
  printo(wynik);
  print(" Naj wynik: ", " Best score: ");
  printo(naj_wynik);
}

void Dino() {
  czass = millis();
  update_jump();

  for (int ik = 0; ik < 3; ik++) {
    if (x_kaktus[ik] < 17) {
      if (y_player < CLEAR_Y) {
        wynik++;
        Buzz(100, 200);
      } else {
        wynik = 0;
        speed = 1;
      }
      x_kaktus[ik] = random(16, 128);
      for (int ik2 = 0; ik2 < 3; ik2++) {
       if (x_kaktus[ik2] > x_kaktus[ik] - 32 and x_kaktus[ik2] < x_kaktus[ik] + 1) {
        x_kaktus[ik2] = x_kaktus[ik2] + 32;
        Serial.println("DZIALA!!!!");
       }
      }
    } else {
      x_kaktus[ik] = x_kaktus[ik] - speed;
    }
  }

  if (wynik > naj_wynik) {
    naj_wynik = wynik;
    EEPROM.update(12, naj_wynik);
  }
    if (wynik - ostatni_wynik > 5) {
      speed++;
      ostatni_wynik = wynik;
    }

  if (i == '5') {
    dino_jump();
  }
}