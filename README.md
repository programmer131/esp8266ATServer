# update 
AT commands are almost obsolete, just program ESP8266 separately from Arduino IDE and then use serial communication for interfacing, may utilize JSON format to send/receive data from ESP8266.  
Below are few examples where I connected ESP8266 to Arduino/PIC/... and programmed external controller to accept JSON formatted data
* Linux CPU Frequency meter ESP-01 + Arduino UNO https://youtu.be/kL3eR1ML2SU
* Stepper motor angle control from ESP8266 + Arduino https://youtu.be/Rng7D0koDhM
* COVID-19 tracker ESP-01+Arduino UNO https://youtu.be/YlCtPTCAl0U
* ESP8266 + PIC18 programmed in mikroC, no AT commands, JSON parser needs improvements but works https://youtu.be/jDdEQywCYaY
* ESP8266 + Arduino UNO, proteus simulation, no AT commands: https://youtu.be/naSdcrKKYLY

# esp8266ATServer
Objective was to write ESP8266 interfacing code that should be able to work with any microcontroller and any C/C++ compiler.
Speed was of prime importance, I've tested several mbed examples for ESP8266, all work too slow, is hard to run real server with available libraries, so I've written my own interrupt based functions. 
ESP8266 webserver using AT commands, can work with any mbed platform, tested on STM32F407 and LPC1768. Only need to update pin configuration to make it work for respective board. Also tested on PIC18 using mikroC PRO for PIC.
Here are some videos that show how this project works

Interfacing esp8266 with stm32f407
https://youtu.be/nabJv9hEc64

Interfacing esp8266 with stm32f407 and using Android app for voice commands
https://youtu.be/svKGvChiNWk

Interfacing ESP8266 with LPC1768
https://youtu.be/FOXCza6HQII

Interfacing ESP8266 with PIC18
https://youtu.be/F53VvpxJuWk

Here are few basics how I write this code, 
https://www.youtube.com/watch?v=QVhWVu8NnZc&list=PLl7pvqnJQnZCON2TmYFSuAKT38ztHoK86
