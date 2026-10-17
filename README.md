⚠️ UWAGA: Projekt nie jest powiązany z firmą Arduino i nie jest oficjalnym produktem.
⚠️ NOTE: The project is not affiliated with Arduino and is not an official product.
English readme: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS3/README-en.md
## Informacje
ArduinoOS 3 to kolejna wersja mojego projektu ArduinoOS
Możesz przetestować demo w serwisie Wokwi: https://wokwi.com/projects/478123317363453953

UWAGA! JEST TO DEMO PROJEKTU! WIELE FUNKCJI ZWYCZAJNIE NIE JEST DOSTĘPNE! 

RTC - na platformie Wokwi niedostępny jest konkretny moduł zegara używany przez projekt

EEPROM - działa ale do restartu symulacji
## Wydania
1. pre1f3-1.0 - rozpoczęto prace nad ArduinoOS 3! *Wydano: 28.09.2026*
2. pre2f3-1.0 - dodano grę dinozaur oraz optymalizacje stworzone przez @chackAJMCPE oraz dodano obsługę buzzera i możliwość jego wyciszenia w ustawieniach *Wydano: 3.10.2026*
3. pre3f3-1.0 - dodano przeglądarkę plików oraz notatnik *Wydano: 10.10.2026*
4. pre4f3-1.0 - dodano port wielofunkcyjny (można podłączyć joystick, czujnik odległości i LED RGB. Dodano także brakujące funkcje w notatniku (prosimy nie przejmować się definicjami-duchami innych funkcji portu wielofunkcyjnego, zostaną dodane w swoim czasie) *Wydano: 17.10.2026*
5. pre5f3-1.0 - dodano menu pomocy (nie martwcie się tym że w ustawieniach pisze że dalej mamy ArduinoOS 3 v. pre3f3-1.0, zapomniałem zaktualizować) *Wydano: 17.10.2026*
6. pre6f3-1.0 - dodano multitasking (max. 3 aplikacje w tle) *Wydano: 17.10.2026*
## Wymagania
**Wymagania minimalne**:
1. Arduino Uno
2. OLED 128x64
3. Keypad 4x4
4. RTC

**Wymagania zalecane**:
1. Arduino Uno
2. OLED 128x64
3. Keypad 4x4
4. RTC
5. Jedno z urządzeń które można podłączyć do portu wielofunkcyjnego (buzzer, joytsick, czujnik odleglości dioda RGB)

## Podłączenie:
2-5 -> R1-R4 keypada
6-9 -> C1-C4 keypada
SCL -> SCL ekranu
SDA -> SDA ekranu
10,11,12 -> RTC
i oczywiście GND i VCC gdzie jest potrzebne.

## Port wielofunkcyjny
port wielofunkcyjny pozwala podłączać różne urządzenia. Obsługiwane:
1. joystick (A0 - przycisk, A1 - X, A2 - Y)
2. czujnik odległości (A0 - trig, A1 - echo)
3. Dioda RGB (A0 - R, A1 - G, A2 - B)

## Własne aplikacje
1. Tworzysz nowy plik w folderze
2. Tworzysz 2 funkcje: xScreen() i x() (to są zalecane nazwy gdzie x to nazwa / skrót dla twojej aplikacji)
3. przechodzisz do pliku system3-1.x gdzie x to obecna wersja
4. tutaj w miejscu gdzie są inne funkcje ponownie wpisujesz nazwy swoich funkcji (bez definiowania ponieważ są zdefiniowane w innym pliku)
5. Następnie odnajdujesz tablicę apps[]. Otwierasz nowy nawias w tablicy (nie zapomnij o przecinku na zakończeniu starego)
6. w nawias wpisujesz następujące dane: nazwa aplikacji pl, nazwa aplikacji ang, nazwa twojej funkcji bez Screen, nazwa twojej funkcji z Screen, nazwa ikony (jeśli nie chce ci się stworzyć swojej możesz użyć wbudowane w system)

## Licencja

Projekt jest dostępny na licencji **GNU General Public License w wersji 3 (GPLv3)**.  
Szczegóły znajdują się w pliku `LICENSE`.

---



© 2026 `idontknow-hardware`
