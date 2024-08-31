# PPSv2

![Licence](https://img.shields.io/badge/license-GNU-blue.svg)
![Version](https://img.shields.io/badge/version-1.2.0-green.svg)

## Index

- [Introduction](#introduction)
- [Features](#features)
- [Use](#use)
- [BOM (Bill of Materials)](#bom)
- [Elettrical Diagram](#diagram)
- [License](#license)
- [Contact](#contact)


## Introduction
PPSv2 is a new version of PPS (Particoular Power Strip), it can manage the state of 4 sockets with HTTP server, provided by ESP32.
PPSv2 doesn't expect any encryption currently.

## Features
- **Web Server**: you can use PSv2 with a web server, it works with 5544 port.
- **State**: you can view the state of 4 socket without sending any command.
- **Debug**: PPSv2 has a debug on the ESP32 serial monitor

## Use:
PPSv2 works with a web server, just enter the URL in the browser. You'll find the URL on the ESP32 serial monitor.

## BOM:
- ESP32
- Jumper
- Step-Down, STEPD5V32
- Relay Module 4 5V
- Uncovered Power Supply 12V 1A
- Bivalent electric sockets x 4
- White cover hole x 6
- Male Eletrical socket 16A
- Eletrical Cable (blue, brown, yellow-green) 2.5mm^2
- BTICINO 25412 - IDROBOXMATIX - COVER IP40 12P
- Cable press PG9

## Diagram:
![Diagram](https://github.com/jim-bug/PPS/blob/pps-v2/Documents/Diagram/PPSv2_diagram.png)

## License
[GPL-3.0](https://choosealicense.com/licenses/gpl-3.0/)


## Contact
You can contact me with -> ignazioandsperandeo@gmail.com
