#include <EEPROM.h>
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
    for (int i = 63; i < EEPROM.length(); i = i + 76) {
      
    for (int i_P = 1; i_P < 76; i_P++) {
      Serial.print(" ");
      Serial.println(i + i_P);
      Serial.println("i:");
      Serial.print(i);

      if (i_P == 1) {
        EEPROM.put(i + i_P, 0);

      }if (i_P == 2) {
        EEPROM.put(i + i_P, 1);
      }if (i_P > 2 and i_P < 12) {
        EEPROM.put(i + i_P, 'a');
      }if (i_P > 11) {
        EEPROM.put(i + i_P, 0);
      }
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < EEPROM.length(); i++) {
    Serial.print(i);
    Serial.print(" ");
    Serial.print(EEPROM.read(i));
    Serial.println("");
  }
}
