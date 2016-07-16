# EspToCloud

A collection of code snippets I am using frequently to post data from ESP8266 to the cloud for storage, visualization and analysis.


## Table of Contents
- [Introduction](#introduction)
- [Functionality](#functionality)
- [Application](#application)
  - [Emoncms](#emoncms)
  - [ThinkSpeak](#thinkspeak) :construction:
  - [KeenIO](#keenio) :construction:
  - [EspToCloud](#espeocloud) :construction:
- [Compatibility](#compatibility)
  - [Hardware](#hardware)
  - [Arduino Core](#arduino-core)
  - [Programming Environment](#programming-environment)
- [Contribute](#contribute)
- [Credits](#credits)
- [License](#license)


## Introduction

When doing projects with ESP8266 I often need to collect and analyse some data. For instance process variables as humidity or temperature like in [OnlineHumidifier](https://github.com/krzychb/OnlineHumidifier) project. On other occasion I may need to record and compare up time as well as performance parameters for couple of ESP8266 modules running various versions of similar application as in [EspFire2012](https://github.com/krzychb/EspFire2012) project. 

In cases like that, instead of developing storage and analysis tools on my own, it may be much easier, quicker and convenient to use external cloud service. There are several services like that to provide you with ready and tested tools to store, visualize and analyze the data.

Below is summary of three cloud services I am using on my projects together with sample sketches. 

## Functionality

Each sketch is posting the following variables to respective cloud service:

* sketch up time in minutes : ``` EspCloud_UpTime ```
* free heap size reported by module in bytes : ``` EspCloud_HeapSize ```
* number of transmission attempts to the cloud service : ``` EspCloud_TransmissionAttempts ```
* number of reply timeouts by the cloud service : ``` EspCloud_ReplyTimeouts ```
* number of connection failures : ``` EspCloud_ConnectionFailures ```
* time in miliseconds that took to transmit the data and obtain a reply from the service in previous post request : ``` EspCloud_PostingTime ```

To make particular sketch running you need to:

1. Set up an account on particular cloud service.

2. Copy and paste an API key provided by the service (it typically looks like ``` 9a3e3c9cf65c70a597097b065dcb24e3 ```) to the sketch in the following line:

  ```cpp
  #define API_KEY "enter-your-api-key-here"
  ```
3. For KeenIO you will also need to update request url (it looks like ``` #define REQUEST_URL_KEENIO "/3.0/projects/5359bcb513e406c26c910dac/events/esp" ```) in the following line:

  ```cpp
  #define REQUEST_URL "enter-your-KeenIO-request-url-here"
  ```
4. Enter ssid and password to your Wi-Fi network (instead of ``` ******** ```, see below), so the module can join the network:

  ```cpp
  const char* ssid = "********";
  const char* password = "********";
  ```

## Application

### Emoncms

The first cloud service I have tried and adopted to my needs was [Emoncms](http://emoncms.org/). It is optimized for processing, logging and visualising energy, temperature and other environmental data. I am using it quite frequently for all sorts of data, also those not mentioned by Emoncms, and found this service very quick and reliable. Once I had an issue with posting data and [reported](https://community.openenergymonitor.org/t/all-my-feeds-stopped-recording-data-on-emoncms-org/828) it on the forum. It was resolved within less than 12 hours what I really like. Did I mention it is a free service? Excellent job Emoncms team!

What I like about [Emoncms](http://emoncms.org/):
* Data posting up to every 10s
* Quick an concise "OK" message confirming each successful data transmission that saves processing time
* Handy dashboard with various containers, widgets and visualizations to organize and show my data
* Ability to show several variables on a single "multigraph" chart

What can be improved:
* Provide possibility to generate new API keys
* Add more stuff to show on dashboard like links and graphics 

[Check the sketch](EspToCloud-Emoncms)


### ThinkSpeak :construction:


### KeenIO :construction:


### EspToCloud :construction:


## Compatibility

All sketches have been tested using components described below.


### Hardware

* NodeMCU 1.0 (ESP-12E Module)


### Arduino Core

* [Esp8266 / Arduino](https://github.com/esp8266/Arduino) core [2.3.0](https://github.com/esp8266/Arduino/releases/tag/2.3.0) for Arduino IDE and Visual Micro
* [framework-arduinoespressif](http://platformio.org/platforms/espressif) version 13 for PlatformIO


### Programming Environment

* [Arduino IDE](https://www.arduino.cc/en/Main/Software) 1.6.9 portable version running on Windows 7 x64
* [PlatformIO IDE](http://platformio.org/platformio-ide) 1.3.0 CLI 2.11.0 running on Windows 7 x64
* [Visual Micro](http://www.visualmicro.com/) 1606.17.10 with Visual Studio Community 2015 running on Windows 7 x64


## Contribute

Feel free to contribute to the project in any way you like!

If you find any issues with code or description please report them using *Issues* tab above.


## Credits

Software for this project has been prepared thanks to applications prepared by the following teams and individuals:
* esp8266/Arduino team lead by [Ivan Grokhotkov](https://twitter.com/i_grr) that brought to us excellent [ESP8266 core for Arduino](https://github.com/esp8266/Arduino).
* Arduino team that develops and maintains versatile [Arduino IDE](https://www.arduino.cc/)
* PlatformIO team lead by [Ivan Kravets](https://twitter.com/ikravets) that develops and maintains quick, modern and versatile [PlatformIO](http://platformio.org/) that is an open source ecosystem for IoT development.
* [VisualMicro](http://www.visualmicro.com/) that provides excellent Arduino IDE for Microsoft Visual Studio and Atmel Studio.

This repository could not be created without the following great cloud services that you can use for free:
* [Emoncms](http://emoncms.org/) - A powerful open-source web-app for processing, logging and visualising energy, temperature and other environmental data.
* [ThinkSpeak](https://thingspeak.com/) - An open source data platform and API for the Internet of Things.
* [KeenIO](https://keen.io/) - With Keen’s developer-friendly APIs, it’s easy to collect, explore, and visualize data anywhere. Apps and websites, customer-facing dashboards, IoT devices, you name it.


## License

[GNU LESSER GENERAL PUBLIC LICENSE - Version 2.1, February 1999](LICENSE)

