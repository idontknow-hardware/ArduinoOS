⚠️ NOTE: The project is not affiliated with Arduino and is not an official product.
## Contents
1. ArduinoOS 2 - https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README-en.md#arduinoos-2
2. Realeses - https://github.com/idontknow-hardware/ArduinoOS/blob/ArduinoOS2/README-en.md#realases
3. Minimum and recomended requirments - https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#minimum-and-recommended-requirements
4. instalation - https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#instalation
5. What if my remote isn't working - https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#what-if-my-remote-isnt-working
6. Files - https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#files
7. https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#backup-user-guide
8. Script - https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#script
9. Port - https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#port
10. https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#errors
11. License - https://github.com/idontknow-hardware/ArduinoOS/edit/ArduinoOS2/README-en.md#license
## ArduinoOS 2
Officialy I begining work on ArduinoOS 2. New version of system will have better code and lots of new features!
## Realases
- pre1f2-1.0 - first version! *Realesed: 30.05.2026*
- pre2f2-1.0 - added favourite apps and changed if's in function input() to switch *Realesed: 1.06.2026*
- pre2Of2-1.0 - optymalizations by  @chackAJMCPE. Have errors! *Realesed: 5.06.2026*
- pre3f2-1.0 - Added files and notes *Realesed: 6.06.2026*
- pre4f2-1.0 - Added script, fixed file-related errors, optymalized function input() and now supports holding down the key*Realesed: 25.06.2026*
- pre5f2-1.0 - Added battery indicator and information on how much time is left *Realesed: 25.06.2026*
- pre6f2-1.0 - Added support for up to three buttons outside the remote control (button assignments can be changed in the settings under the button 4) *Realesed: 26.06.2026*
- pre6af2-1.0 - Added information in settings menu that you can change the button assignment *Realesed 26.06.2026*
- pre7f2-1.0 - Added files backup *Wydano: 27.06.2026*
- pre8f2-1.0 - added CPU temperature indicator *Realesed: 29.06.2026*
- pre9f2-1.0 - Optimized drawing functions, added information about uptime, added fullscreen mode *Relesed 30.06.2026*
- pre10f2-1.0 - Added a multifunction port and an application that uses it (functions that use it in the scripting language are still unavailable) *Realesed: 4.07.2026*
- pre11f2-1.0 - Added multifunction port support in scripting language, added option to fix corrupted files *Realesed: 5.07.2026*
- pre12f2-1.0 - Added error screens *Realesed: 6.07.2026*
- pre13f2-1.0 - Added diagnostic tool, added clock of uptime if the RTC is not wired
## Minimum and recommended requirements
Note: As this project is in beta, the requirements may change! Minimum:

- Arduino Uno
- IR sensor
- Remote control
- 2 x 16x2 LCD screens
Recommended

- Arduino Uno
- IR sensor
- Remote control
- 2 x 16x2 I2C LCD screens
- RTC to show the time
- 1-3 buttons outside the remote control
## Instalation
1. Download the code
2. Open it in the Arduino IDE
3. Click "Upload"
4. Wait for it to finish
## what if my remote isn't working?
a) Make sure the IR sensor is connected correctly.
If that doesn't work:
1. Open the ArduinoOS 2 code on your computer.
2. Find the definition of the input() function.
3. Find the button you're interested in
4. Open the Serial Monitor in the Arduino IDE
5. Press the button
6. You'll receive the message "Odebrano komendę: " and the code
7. Copy the code
8. Paste code after case in input()
9. Upload the code to the Arduino
## Files
The ArduinoOS 2 file system allows you to create up to 13 files (for Arduino Uno). Note: If you've used a version before pre3f2-1.0, run wgrywanie-plikow to create the file system. If you haven't used older versions, just go through setup and the program will create a file system in the "config ended" menu (that's why you have to wait so long)
## Backup User Guide.

a) Downloading to your computer.

1. Select the file you want to upload.
2. Click '-'
3. Click '5'
4. Copy the resulting string of numbers to the Serial port in the Arduino IDE and save it somewhere on computer (for example notes)b) Loading from a computer
1. Copy the resulting string of numbers from the saved location to the Serial port input in the Arduino IDE
2. On the Arduino, click , go to files, and click '+'
3. Click enter on the computer
4. Choose option "Load file"(2)
5. Wait for a while
## Script
The script allows you to create applications.

| invoking number | command | required values | command description |
| :--- | :---: | :---: | ---: |
| 1 | print | character | writes single characters to the screen |
| 2  | set | selected variable (1-4), value | sets variables to selected value |
| 3 | if= | selected variable (1-4), value | compares variable with value, if equal executes code, if not  jumps to endif |
| 4 | endif | - | marks the end of the if= condition |
| 5 | create file | - | creates a save file above the application/code file. If this position is occupied, it asks to delete the file |
| 6 | load byte from file (lff) | selected variable (1-4), byte | loads the selected byte from the write file into the selected variable | 
| 7 | write to file (w(t)f) | selected variable (1-4), byte | writes the selected byte with selected variable
| 8 |  cursor_s | x, y | sets the cursor to the selected location |
| 9 | clear | - | clears the screen |
| 10 | input | selected variable (1-4) | reads input() and stores it in the selected variable |
| 11 | ADD | - | adds only value1 + value2 = value3 |
| 12 | SUB | - | subtracts only: value1 - value2 = value3
| 13 | * | - | multiplies only: value1 * value2 = value3
| 14 | / | - | divides only: value1 / value2 = value3
| 15 | load from  port | selected variable (1-4), port pin (1-3) | loads data from the port into the specified variable
| 16 | cursor_m | - | sets the cursor to value3 and value4, for coordinates: x and y, respectively
| 17 | send to port | selected variable, port pin | sends data to port
Other buttons:
100+ - save command, next command
CH- - previous command
PLAY/PAUSE - start data entry
EQ - change  Uploading code_x to code_y and vice versa
NEXT - Startup options
## port
The port allows you to connect several additional devices. Currently available are:
- joystick
- distance sensor
- bali switch
- RGB LED
Connection:
- joystick: A1 - x-axis, A2 - y-axis, A3 - button.
- Distance sensor: A1 - trig, A2 - echo
- Bali switch: A1 - output
- RGB LED: A1 - red, A2 - green, A3 - blue
## Errors
Here's what each error code means:
Error 0x0 - RAM usage is too high
Error 0x1 - CPU temperature is too high
## License

The project is licensed under the GNU General Public License version 3 (GPLv3).

Details can be found in the `LICENSE` file.

--

© 2026 `idontknow-hardware`

