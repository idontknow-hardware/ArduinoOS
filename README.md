⚠️ UWAGA: Projekt nie jest powiązany z firmą Arduino i nie jest oficjalnym produktem.
⚠️ NOTE: The project is not affiliated with Arduino and is not an official product.
English readme: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS3/README-en.md
## Informacje
ArduinoOS 3 to kolejna wersja mojego projektu ArduinoOS.
Możesz przetestować demo w serwisie Wokwi: https://wokwi.com/projects/478123317363453953

UWAGA! JEST TO DEMO PROJEKTU! WIELE FUNKCJI ZWYCZAJNIE NIE JEST DOSTĘPNE! 

RTC - na platformie Wokwi niedostępny jest konkretny moduł zegara używany przez projekt

EEPROM - działa ale do restartu symulacji
## Znane błędy
Legenda:
🟩 - błąd o małej ważności dla działania systemu (literówki, błędy w funkcjach informacyjnych)

🟧 - błąd o średniej wartości dla działania funkcji systemu (małe błędy w funkcjach nieczęsto używanych)

🟥 - błąd o wysokiej ważności dla działania systemu (błędy w funkcjach które są wymagane do działania systemu)

Statusy:
Podejrzenie - nie sprawdzony błąd, jednak jest podejrzenie że jest taki problem

Potwierdzone - błąd istnieje, nie naprawiony

Naprawiony - błąd został naprawiony

1. Funkcja zwracająca liczbę wolnych plików nie uwzględnia plików usuniętych.
 a) Ważność: 🟩
 b) Skutki: użytkownik w trakcie uruchamiania jest informowany tylko o plikach które nie zostały jeszcze zapisane, a pliki usunięte są przez funkcje liczone jako pliki normalnie istniejące
 c) Status: podejrzenie
 d) wersja systemu która naprawia błąd: - (błąd dalej obecny)
## Plan rozwoju
UWAGA! NIE JEST TO OBIETNICA, JEŚLI STWIERDZĘ ŻE COŚ JEST ZA TRUDNE DO ZAIMPLEMENTOWANIA TO ZWYCZAJNIE NIE ZOSTANIE DODANE!
1. Dodanie importu i eksportu plików oraz całego EEPROMu przez Serial Port
2. Pasek zadań (pokazujący informacje o: stanie baterii, temperaturze CPU, zużyciu RAMu, aplikacjach w tle)
3. Statystyki systemowe
4. Animacje (4x4, 4 klatki na plik)
5. Lepsza animacja (8x4, 16 klatek na plik)
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
3. Dioda RGB (A0 - R, A1 - G, A2 - B), dla diody RGB wymagane są rezystory!
UWAGA! W USTAWIENIACH MOŻNA ZMIENIAĆ TRYB PORTU, SYSTEM NIE ROBI TEGO AUTOMATYCZNIE!
ZNAJDZIESZ TAM TEŻ URZĄDZENIA KTÓRE JESZCZE NIE MAJĄ ŻADNYCH FUNKCJI, ONE ZOSTAWIONE SĄ NA PRZYSZŁY ROZWÓJ.

## Własne aplikacje
1. Tworzysz nowy plik w folderze projektu systemu
2. Tworzysz 2 funkcje: xScreen() i x() (to są zalecane nazwy gdzie x to nazwa / skrót dla nazwy twojej aplikacji)
3. przechodzisz do pliku system3-1.x gdzie x to obecna wersja
4. tutaj w miejscu gdzie są inne funkcje ponownie wpisujesz nazwy swoich funkcji (bez definiowania ponieważ są zdefiniowane w innym pliku)
5. Następnie odnajdujesz tablicę apps[]. Otwierasz nowy nawias w tablicy (nie zapomnij o przecinku na zakończeniu starego)
6. w nawias wpisujesz następujące dane: nazwa aplikacji pl, nazwa aplikacji ang, nazwa twojej funkcji bez Screen, nazwa twojej funkcji z Screen, nazwa ikony (przykład zdefiniowanej ikony: const unsigned char nazwa[] PROGMEM = {}, można użyć edytora bitmap który pokazuje też wynik jako tablicę np strony https://xbm.jazzychad.net (rozmiar 16x16), jeśli nie chce ci się stworzyć swojej możesz użyć wbudowane w system). Przykład (kalkulator, aplikacja nie istnieje w systemie, to przykład): {"Kalkulator", "Calculator", "Calc", "CalcScreen", kalkulator}
!UWAGA! Sam ArduinoOS 3 zajmuje dużo pamięci Flash! Jeśli chcesz stworzyć własną aplikację rozważ usunięcie części funkcji systemu!

## System plików
Dane plików zaczynają się od 65 bajtu, poniżej są dane dla systemu.
Każdy plik wygląda następująco: 
Bajt 0 - flaga (1 - plik istnieje, 2 - usunięty, 3 i więcej - zepsute)
Bajt 1 - rodzaj
Bajty 2-10 - nazwa
Bajt 11 - rok edycji
Bajt 12 - miesiąc edycji
Bajt 13 - dzień edycji
Bajt 14 - godzina edycji
Bajt 15 - minuta edycji
Bajty 16-80 - dane

## Licencja

Projekt jest dostępny na licencji **GNU General Public License w wersji 3 (GPLv3)**.  
Szczegóły znajdują się w pliku `LICENSE`.

---



© 2026 `idontknow-hardware`
