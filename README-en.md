⚠️ **DISCLAIMER**

ArduinoOS is an independent project. It is not affiliated with Arduino or an official Arduino product. It is also not affiliated with other operating system projects for Arduino.

## About
ArduinoOS 3 is next version of my project ArduinoOS. You can try demo on Wokwi: https://wokwi.com/projects/478123317363453953
CAUTION! THIS IS DEMO OF PROJECT! SOME FEATURES DIDN'T EXSIST!
RTC - on Wokwi isn't exist a model that project use.
EEPROM - works until restart of simulation
## Known issues
Legend: 🟩 - error of low importance to the operation of the system (typos, errors in information functions)

🟧 - Medium severity error for system function operation (minor errors in functions that are not frequently used)

🟥 - High severity error for system operation (errors in functions that are required for operation of system)
Statuses: Suspected - the bug hasn't been verified, but there is a suspicion that such a problem exists.

Confirmed - the bug exists, but hasn't been fixed.

Fixed - the bug has been fixed.

The bug never existed (suspicions were not confirmed)

1. The function returning the number of free files does not take into account deleted files. a) Severity: 🟩 b) Effects: During startup, the user is only informed about files that have not been saved yet. c) Statute: confirmed. d) from: ?. e) version of system that repairs the bug: pre7af3-1.0
2. The number of applications in the menu overlaps with the information bar. a) Severity: 🟩 b) Impact: The user cannot see the sequence number of the application they are selecting (the name remains visible). c) Status: Confirmed. d) From: pre7f3-1.0 e) System version that fixes the bug: pre7af3-1.0
3. For unknown reasons, the "Settings" menu displays its name in both Polish and English simultaneously. a) Severity: 🟩 b) Impact: Negligible; the user can still identify the application. Notes: Cause unknown. c) Status: Confirmed. d) From: ? e) System version that fixes the bug: pre8f3-1.0
## Development plan
NOTE: THIS IS NOT A PROMISE. IF I FIND SOMETHING TOO DIFFICULT TO IMPLEMENT, IT SIMPLY WON'T BE ADDED!

1. System Statistics
2. Animations (4x4, 4 frames per file)
3. Improved Animation (8x4, 16 frames per file)
## Releases
1. pre1f3-1.0 - work on ArduinoOS 3 has begun! *Released: 28.09.2026*
2. pre2f3-1.0 - added a dinosaur game and optimizations created by @chackAJMCPE; added buzzer support with an option to mute it in the settings. *Released: 3.10.2026*
3. pre3f3-1.0 - added a file browser and a notepad. *Released: 10.10.2026*
4. pre4f3-1.0 - added a multi-purpose port (supports a joystick, distance sensor, buzzer and RGB LED). Also added missing features to the notepad (please ignore the "ghost" definitions for other multi-purpose port functions; they will be added in due course). *Released: 17.10.2026*
5. pre5f3-1.0 - added a help menu (please disregard the fact that the settings still show "ArduinoOS 3 v. pre3f3-1.0"—I forgot to update it). *Released: 17.10.2026*
6. pre6f3-1.0 - added multitasking (up to 3 background applications). *Released: 17.10.2026*
7. pre7f3-1.0 - added file import/export via Serial and an information bar. *Released: 22.10.2026*
8. pre7af3-1.0 - fixed bugs 1 and 2. *Released: 22.10.2026*
9. pre8f3-1.0 - fixed bug 3, added system statistics. *Released: 23.10.2026*
10. 1.0 - added animations and better animations *Released: 25.10.2026*
## Requirements
Minimum requirements:

Arduino Uno
128x64 OLED display
4x4 keypad
RTC (Real-Time Clock)
Recommended requirements:

Arduino Uno
128x64 OLED display
4x4 keypad
RTC (Real-Time Clock)
One of the devices that can be connected to the multifunction port (buzzer, joystick, distance sensor, or RGB LED)
A DS18B20-compatible thermometer for temperature measurement (if not connected, the information bar in the temperature section will display 48)
## Conection
2–5 -> keypad R1–R4; 6–9 -> keypad C1–C4; SCL -> display SCL; SDA -> display SDA; 10, 11, 12 -> RTC; and, of course, GND and VCC wherever required.
## Multifunctional port
The multifunctional port allows for the connection of various devices. Supported components:

1. joystick (A0 – button, A1 – X, A2 – Y)
2. buzzer (A0)
3. distance sensor (A0 – trig, A1 – echo)
4. RGB LED (A0 – R, A1 – G, A2 – B) – resistors are required for the RGB LED! PLEASE NOTE: You must manually change the port mode in the settings; the system does not do this automatically! You will also find devices listed there that do not yet have any assigned functions; these have been included for future development.
## Custom Applications
Create a new file in the system project folder.
Define two functions: `xScreen()` and `x()` (these are the recommended names, where `x` is the name or an abbreviation for your application).
Open the file `system3-1.x` (where `x` represents the current version).
In the section containing other functions, add the names of your functions (you do not need to define them here, as they are already defined in the other file).
Locate the `apps[]` array. Add a new entry within the array (don't forget to add a comma after the previous entry).
Inside the new entry, provide the following data: the application name in Polish, the application name in English, the name of your function (excluding "Screen"), the name of your function (including "Screen"), and the icon name (for example, an icon defined as `const unsigned char name[] PROGMEM = {}`). You can use a bitmap editor—such as the one at https://xbm.jazzychad.net—to generate the required array (use a 16x16 size); alternatively, you can use icons already built into the system. Example (for a calculator—note that this is just an example, as such an app does not actually exist in the system): `{"Kalkulator", "Calculator", "Calc", "CalcScreen", kalkulator}`. !NOTE! ArduinoOS 3 itself consumes a significant amount of Flash memory! If you wish to create your own application, consider removing some of the existing system functions.
## File system
The files data start from 65 byte, below there are data for system. Every file looks like this: Byte 0 - flag (1 - file exists, 2 - deleted, 3 and above - corrupted) Byte 1 - type Bytes 2-10 - name Byte 11 - year of modification Byte 12 - month of modification Byte 13 - day of modification Byte 14 - hour of modification Byte 15 - minute of modification Bytes 16-80 - data
## License

The project is licensed under the GNU General Public License version 3 (GPLv3).

Details can be found in the `LICENSE` file.

--

© 2026 `idontknow-hardware`

