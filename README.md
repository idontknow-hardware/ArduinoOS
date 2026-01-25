## Wydania

Lista wydań:

- **pre1f1.1** – dodano wskaźnik baterii.  
  Uwaga: edytor kodu nie ma jeszcze wszystkich poleceń, które są planowane.
  Uwaga nr. 2: zawiera błędy! Zalecana instalacja pre1af1.1!
  *Wydana: 23.01.2026*
- **pre1af1.1** – naprawiono literówkę w wskazniku baterii oraz błąd w animacji dinozaura w grze.
  *Wydana: 23.01.2026*
- **pre2f1.1** – dodana obsługa 2 ekranów LCD.
*Wydana: 23.01.2026*
- **pre2af1.1** - naprawa błędów
- *Wydana: 24.01.2026*
- **pre3f1.1** *(mam nadzieję, że do tego czasu chociaż 1 osoba odwiedzi repo)* – dokończenie edytora kodu!  
  Informacje o skrypcie, którym tworzysz niestandardowe aplikacje, znajdują się w dalszej części README.
- **pre4f1.1** - usuwanie aplikacji
- **pre5f1.1** - narzędzie diagnostyczne
  
# ArduinoOS

**ArduinoOS** – prosty system operacyjny na Arduino, stworzony przez `idontknow-arduino` (2026).

Na ten moment projekt jest w całości po polsku. W przyszłości planowane jest dodanie wersji angielskiej.

---

## Wymagania minimalne

- Arduino Uno  
- Ekran LCD  16 * 2
- Keypad 4×4  
- Arduino IDE do wgrania kodu

## Wymagania zalecane

- Arduino Uno  
- 2 Ekrany LCD  16 * 2 (2 to wyswietlacz informacji systemowych)
- Keypad 4×4  
- 3 diody LED  

## Wymagane biblioteki

- `LiquidCrystal_I2C`  
- `Wire`  
- `Keypad` (obsługa klawiatury 4×4)

---

## Instalacja i uruchomienie

1. Pobierz to repozytorium:
   - przez przycisk **Code → Download ZIP** i rozpakuj, albo  
   - przez `git clone`, jeśli używasz gita.

2. Otwórz główny plik `.ino` w **Arduino IDE**.

3. W Arduino IDE:
   - wybierz odpowiednią płytkę (**Narzędzia → Płytka → Arduino Uno**),  
   - wybierz port (**Narzędzia → Port**).

4. Wgraj szkic na Arduino (przycisk **Wgraj**).

---
## Pomoc w instalacji drugiego ekranu I2C
płytka z grubsza:
+-------------------------------------------------------------+
|                                          +-----+            |
|                                          |poten |     GND   |---
|                                          + - - +      VCC   |---
|                                               [2] [] []SDA   |---
|                                              [1] [] []SCL   |---
|                                             A0 A1 A2        |
+-------------------------------------------------------------+
aby zmienić adres na 0x26 należy przylutować kabel z początkiem w [1] i końcem w [2]
## Sterowanie i użycie systemu

### Menu główne

- `1` – wybór użytkownika  
- `2` – wybór użytkownika 2  
- `1–8` – wybór ulubionych aplikacji  
- `9` – lista wszystkich aplikacji  

### Gra „Dinozaur”

- `5` – skok / restart gry  
- `6` – reset high score  

### W menu „Wszystkie aplikacje” (`9`)

- `1` – wybierz aplikację  
- `2` – dodaj do ulubionych  
- `A` – lista w górę  
- `D` – lista w dół  
- (przycisk powrotu – opisz tutaj, jeśli masz dedykowany klawisz)
-------
## Skrypt (stan na 23.01.2026)

- **Przycisk 1 – `printznak`**  
  - `1` – potwierdzasz aktualny znak  
  - `2` – zmiana znaku w górę (A, B, C itd.)  
  - `3` – zmiana znaku w dół (C, B, A itd.)

- **Przycisk 2** – wyczyść

- **Przycisk 3** – kursor w prawo

- **Przycisk 4** – kursor w lewo

- **Przycisk 5** – zmiana linii (przejście do nowej linii)
## Podłączenie

**I²C (ekran)**  
- Arduino **SCL** → SCL ekranu I²C  
- Arduino **SDA** → SDA ekranu I²C  

**Keypad 4×4**  
- Arduino **2** → C4 (kolumna 4)  
- Arduino **3** → C3 (kolumna 3)  
- Arduino **4** → C2 (kolumna 2)  
- Arduino **5** → C1 (kolumna 1)  
- Arduino **6** → R1 (wiersz 1)  
- Arduino **7** → R2 (wiersz 2)  
- Arduino **8** → R3 (wiersz 3)  
- Arduino **9** → R4 (wiersz 4)  

**Diody LED**  
- LED 1 – dłuższa noga (anoda) → Arduino **10**  
- LED 2 – dłuższa noga (anoda) → Arduino **11**  
- LED 3 – dłuższa noga (anoda) → Arduino **12**  

Pamiętaj o podłączeniu:
- wspólnej **masy (GND)** dla Arduino, ekranu I²C i LED,  
- **rezystorów** do diod LED (np. 220–330 Ω w szereg z anodą).

## Licencja

Projekt jest dostępny na licencji **GNU General Public License w wersji 3 (GPLv3)**.  
Szczegóły znajdują się w pliku `LICENSE`.

---



© 2025–2026 `idontknow-arduino`
