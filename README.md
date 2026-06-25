⚠️ UWAGA: Projekt nie jest powiązany z firmą Arduino i nie jest oficjalnym produktem.
⚠️ NOTE: The project is not affiliated with Arduino and is not an official product.
## Spis treści
1. Info o systemie: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#arduinoos-2
2. Wydania: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#wydania
3. wymagania: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#wymagania-minimalne-i-zalecane
4. Instalacja: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#instalacja
5. Co jeśli pilot nie działa?: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#co-je%C5%9Bli-m%C3%B3j-pilot-nie-dzia%C5%82a
6. Pliki: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#pliki
7. Licencja: https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README.md#licencja
## ArduinoOS 2
oficjalnje rozpoczynam prace nad ArduinoOS 2. Nowa wersja systemu będzie miała lepszy kod i wiele nowych funkcji!
## Wydania
- pre1f2-1.0 - pierwsza wersja! *Wydano: 30.05.2026*
- pre2f2-1.0 - dodano ulubione aplikacje i gre dinozaur oraz zmieniono if'y w funkcji input() na switch *Wydano: 1.06.2026*
- pre2Of2-1.0 - optymaizacje przez @chackAJMCPE. Zawiera błędy! *Wydano: 5.06.2026*
- pre3f2-1.0 - Dodano pliki oraz notatnik. *Wydano: 6.06.2026*
- pre4f2-1.0 - Dodano skrypt, naprawiono błędy związane z plikami, zoptymalizowano funkcje input() i teraz obsługuje przytrzymanie klawisza
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
## Licencja

Projekt jest dostępny na licencji **GNU General Public License w wersji 3 (GPLv3)**.  
Szczegóły znajdują się w pliku `LICENSE`.

---



© 2026 `idontknow-hardware`
