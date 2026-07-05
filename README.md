⚠️ UWAGA: Projekt nie jest powiązany z firmą Arduino i nie jest oficjalnym produktem.
⚠️ NOTE: The project is not affiliated with Arduino and is not an official product.
## Spis treści
1. Info o systemie: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#arduinoos-2
2. Wydania: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#wydania
3. wymagania: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#wymagania-minimalne-i-zalecane
4. Instalacja: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#instalacja
5. Co jeśli pilot nie działa?: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#co-je%C5%9Bli-m%C3%B3j-pilot-nie-dzia%C5%82a
6. Pliki: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#pliki
7. Instrukcja obsługi bakcupu: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#instrukcja-obs%C5%82ugi-backupu
8. skrypt: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#skrypt
9. Licencja: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#licencja
## ArduinoOS 2
oficjalnje rozpoczynam prace nad ArduinoOS 2. Nowa wersja systemu będzie miała lepszy kod i wiele nowych funkcji!
## Wydania
- pre1f2-1.0 - pierwsza wersja! *Wydano: 30.05.2026*
- pre2f2-1.0 - dodano ulubione aplikacje i gre dinozaur oraz zmieniono if'y w funkcji input() na switch *Wydano: 1.06.2026*
- pre2Of2-1.0 - optymaizacje przez @chackAJMCPE. Zawiera błędy! *Wydano: 5.06.2026*
- pre3f2-1.0 - Dodano pliki oraz notatnik. *Wydano: 6.06.2026*
- pre4f2-1.0 - Dodano skrypt, naprawiono błędy związane z plikami, zoptymalizowano funkcje input() i teraz obsługuje przytrzymanie klawisza *Wydano: 25.06.2026*
- pre5f2-1.0 - Dodano wskaźnik baterii oraz informacje ile zostało czasu *Wydano: 25.06.2026*
- pre6f2-1.0 - Dodano obsługę do trzech przycisków poza pilotem (przypisanie można zmienić w ustawieniach po kliknięciu 4) *Wydano: 26.06.2026*
- pre6af2-1.0 - Dodano informację w menu ustawień że można zmienić przypisanie przycisków *Wydano 26.06.2026*
- pre7f2-1.0 - Dodano backup plików *Wydano: 27.06.2026*
- pre8f2-1.0 - Dodano wskaźnik temperatury procesora *Wydano: 29.06.2026*
- pre9f2-1.0 - Zooptymalizowano funkcje rysujące, Dodano informacje o czasie działania, Dodano tryb  fullscreen *Wydano 30.06.2026*
- pre10f2-1.0 - Dodano port wielofunkcyjny oraz aplikacje która go wykorzystuje (opcje dla portu w języku skryptowym nie są dostępne dalej) *Wydano: 4.07.2026*
- pre11f2-1.0 - Dodano obsługę portu wielofunkcyjnego w skrypcie, dodano możliwość naprawy uszkodzonych plików *Wydano: 5.07.2026*
## wymagania minimalne i zalecane
**Uwaga! Jako że projekt jest w wersji beta wymagania mogą sie jeszcze zmienić!**
**minimalne**
- Arduino Uno
- czujnik IR
- pilot
- 2 ekrany LCD 16*2

**zalecane**
- Arduino Uno
- czujnik IR
- pilot
- 2 ekrany LCD i2c 16*2
- RTC do pokazywania czasu
- 1-3 przyciski poza pilotem
## instalacja
1. pobierz kod
2. otwórz go w Arduino IDE
3. kliknij "upload"
4. poczekaj aż sie zakończy
## co jeśli mój pilot nie działa?
a) upewnij sie że czujnik IR jest dobrze podłączony
jeśli to nie zadziała:
1. Otwórz kod ArduinoOS 2 na swoim komputerze.
2. Znajdź definicje funkcji input().
3. Znajdź przycisk który cię interesuje
4. Otwórz Serial monitor w Arduino IDE
5. Naciskaj przycisk
6. Otrzymasz komunikat "Otrzymano kod przycisku:" oraz kod
7. Skopiuj kod
8. Prześlij kod do Arduino
## Pliki
system plików w ArduinoOS 2 umożliwia tworzenie do 13 plików (jeśli chodzi o Arduino Uno). Uwaga! Jeśli używałeś wcześniej wersji sprzed pre3f2-1.0 to uruchom wgrywanie-plikow aby stworzyć system plików w EEPROM. Jeśli nie używałeś starszych wersji to po prostu przejdź przez setup, a program w menu "konfiguracja zakonczona" zrobi system plików (dlatego trzeba tak długo czekać)
## Instrukcja obsługi backupu. 
a) pobieranie na komputer. 
1. Wybierz plik który chcesz przesłać
2. kliknij '-'
3. kliknij '5'
4. skopiuj uzyskany ciąg liczb w Serial port w Arduino IDE i zapisz gdzieś na komputerze (np. w notatnik)
b) wczytywanie z komputera
1. skopiuj z zapisanego miejsca uzyskany ciąg liczb do wejścia Serial port w Arduino IDE
2. na arduino klilnij wejdź w pliki i kliknij '+'
3. kliknij enter na komputerze
4. wybierz opcję 'Załaduj plik'(2)
5. poczekaj chwilę
## skrypt
Skrypt umożliwia tworzenie aplikacji. 

| liczba wywołująca | komenda | wartości wymagane | opis komendy |
| :--- | :---: | :---: | ---: |
| 1 | print | znak | pisze pojedyncze znaki na ekranie |
| 2 | set | wybrana zmienna(1-4), wartość | ustawia zmienne na wybraną wartość |
| 3 | if= | wybrana zmienna (1-4), wartość | porównuje zmienną z wartością, jeśli jest równa wykonuje kod, jeśli nie przeskakuje do endif |
| 4 | endif | - | oznacza koniec warunku if= |
| 5 | create file | - | tworzu plik zapisu nad plikiem z aplikacją / kodem. Jeśli ta pozycja jest zajęta prosi o usunięcie pliku |
| 6 | load byte from file (lff) | wybrana zmienna (1-4), bajt | wczytuje wybrany bajt pliku zapisu do wybranej zmiennej |
| 7 | write to file (w(t)f) | wybrana zmienna (1-4), bajt | zapisuje wybrany bajt pliku zapisu zmienną |
| 8 | cursor_s | x, y | ustawia kursor w wybrane miejsce |
| 9 | clear | - | czyści ekran |
| 10 | input | wybrana zmienna (1-4) | czyta input() i zapisuje go w wybranej zmiennej |
| 11 | ADD | - | dodaje tylko: wartosc1 + wartosc2 = wartosc3
| 12 | SUB | - | odejmuje tylko: wartosc1 - wartosc2 = wartosc3
| 13 | * | - | mnoży tylko: wartosc1 * wartosc2 = wartosc3
| 14 | / | - | dzieli tylko: wartosc1 / wartosc2 = wartosc3
| 15 | load from port | wybrana zmienna(1-4), pin portu (1-3) | wczytuje dane z portu do określonej zmiennej
| 16 | cursor_m | - | ustawia kursor na wartosc3 i wartosc4, dla współrzędnych odpowiednio: x i y
| 17 | send to port | wybrana zmienna, pin portu | wysyła dane do portu
inne przyciski:
100+ - zapisywanie komendy, następna komenda
CH- - poprzednia komenda
PLAY/PAUSE - rozpocznij wprowadzanie danych
EQ - zmiana wgrywania kod_x na kod_y i na odwrót
NEXT - opcje uruchamiania
## port
Port umożliwia połączenie kilku dodatkowych urządzeń. Obecnie dostępne to:
- joystick
- czujnik odległości
- bali switch
- LED RGB
podłączenie:
- joystick: A1 - oś x, A2 - oś y, A3 - przycisk.
- czujnik odległości: A1 - trig, A2 - echo
- bali switch: A1 - wyjście
- LED RGB: A1 - red, A2 - green, A3 - blue
## Licencja

Projekt jest dostępny na licencji **GNU General Public License w wersji 3 (GPLv3)**.  
Szczegóły znajdują się w pliku `LICENSE`.

---



© 2026 `idontknow-hardware`
