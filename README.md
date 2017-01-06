
# Arduino to Arduino Communication using the ESP8266
====================================================

[![GithubArduinoESP8266.jpg](https://s27.postimg.org/yj1izgwpf/Github_Arduino_ESP8266.jpg)](https://postimg.org/image/hiimqsjnz/)

Demonstrates a simple TCP/IP Link enabling two Arduino's to talk to each other using 
the extremely cheap and versatile ESP8266 Wifi modules using SoftwareSerial and AT commands.

#Setup

***DISCLAIMER*** : It is highly recommended that you use LLs (Logic Level Shifters) for communication with the ESP-01 as they are not 5V tolerant (not for long at least). The way in which the modules are wired *will* fry them in the near future. 

ESPs are power hungry and is hence recommend that one uses an external power supply for powering the ESPs.

Wiring :

3.3V (Of Arduino) ----> VCC, CH_PD (of ESP)

GND               -----> GND (of ESP)

*Wire the the RX & TX lines of your ESPs as specified by the respective sketches*

