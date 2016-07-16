/*
  Sample application to post data from ESP8266 module
  to the cloud for storage, visualization and analysis.
  Please check repository below for details

  Repository: https://github.com/krzychb/EspToCloud
  Version: All
  File: EspToCloud-All.ino
  Revision: 0.1.1
  Date: 18-Jul-2016
  Author: krzychb at gazeta.pl

  Copyright (c) 2016 Krzysztof Budzynski. All rights reserved.

  This application is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This application is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

const char* ssid = "********";
const char* password = "********";

#define UPDATE_PERIOD_EMONCMS 60000
#define TIMEOUT_PERIOD_EMONCMS 3000
#define DATA_HOST_EMONCMS "emoncms.org"
#define API_KEY_EMONCMS "enter-your-api-key-here"

void logToEmoncms(void)
{
  WiFiClient client;
  static long dataLogTimer = 0;
  static long transmissionAttempts;
  static long replyTimeouts;
  static long connectionFailures;
  static long postingTime = -1;

  // is it the time for next data logging?
  if (millis() -  dataLogTimer < UPDATE_PERIOD_EMONCMS)
  {
    return;
  }
  dataLogTimer = millis();
  transmissionAttempts++;

  Serial.printf("DATALOG > %s > ", DATA_HOST_EMONCMS);

  // connect to the host
  if (!client.connect(DATA_HOST_EMONCMS, 80))
  {
    Serial.print("Connection failure!");
    connectionFailures++;
    return;
  }

  Serial.print("Sending > ");

  // send the data to the host
  client.print(
  String("GET http://") + DATA_HOST_EMONCMS +
        "/input/post.json?json={" +
          "EspCloud_UpTime:" + String (dataLogTimer / 60000) +
          ",EspCloud_HeapSize:" + String (system_get_free_heap_size()) +
          ",EspCloud_TransmissionAttempts:" + String (transmissionAttempts) +
          ",EspCloud_ReplyTimeouts:" + String (replyTimeouts) +
          ",EspCloud_ConnectionFailures:" + String (connectionFailures) +
          ",EspCloud_PostingTime:" + String (postingTime) +
          "}&apikey=" + API_KEY_EMONCMS + "\r\n" +
        "Connection: close\r\n\r\n");

  // wait for reply from the host
  while (!client.available())
  {
    if (millis() - dataLogTimer > TIMEOUT_PERIOD_EMONCMS)
    {
      Serial.println("Reply timeout!");
      replyTimeouts++;
      postingTime = -1;
      client.stop();
      return;
    }
    delay(1);
  }

  // show reply from the host
  while (client.available())
  {
    Serial.write(client.read());
  }
  Serial.print(" > Done");
  client.stop();

  // show time to log the data
  postingTime = millis() - dataLogTimer;
  Serial.printf(" in %d ms\n", postingTime);
}


#define UPDATE_PERIOD_THINGSPEAK 60000
#define TIMEOUT_PERIOD_THINGSPEAK 3000
#define DATA_HOST_THINGSPEAK "api.thingspeak.com"
#define API_KEY_THINGSPEAK "enter-your-api-key-here"

void logToThingSpeak(void)
{
  WiFiClient client;
  static long dataLogTimer = -20000;
  static long transmissionAttempts;
  static long replyTimeouts;
  static long connectionFailures;
  static long postingTime = -1;

  // is it the time for next data logging?
  if (millis() -  dataLogTimer < UPDATE_PERIOD_THINGSPEAK)
  {
    return;
  }
  dataLogTimer = millis();
  transmissionAttempts++;

  Serial.printf("DATALOG > %s > ", DATA_HOST_THINGSPEAK);

  // connect to the host
  if (!client.connect(DATA_HOST_THINGSPEAK, 80))
  {
    Serial.print("Connection failure!");
    connectionFailures++;
    return;
  }

  Serial.print("Sending > ");

  // send the data to the host
  client.print(
    String("GET /update?key=") + API_KEY_THINGSPEAK +
          "&field1=" + String (dataLogTimer / 60000) +
          "&field2=" + String (system_get_free_heap_size()) +
          "&field3=" + String (transmissionAttempts) +
          "&field4=" + String (replyTimeouts) +
          "&field5=" + String (connectionFailures) +
          "&field6=" + String (postingTime) +
          " " +
          "HTTP/1.1\r\n" +
          "Host: " + DATA_HOST_THINGSPEAK + "\r\n" +
          "Connection: close\r\n\r\n");

  // wait for reply from the host
  while (!client.available())
  {
    if (millis() - dataLogTimer > TIMEOUT_PERIOD_THINGSPEAK)
    {
      Serial.println("Reply timeout!");
      replyTimeouts++;
      postingTime = -1;
      client.stop();
      return;
    }
    delay(1);
  }

  // show reply from the host
  while (client.available())
  {
    Serial.write(client.read());
  }
  Serial.print(" > Done");
  client.stop();

  // show time to log the data
  postingTime = millis() - dataLogTimer;
  Serial.printf(" in %d ms\n", postingTime);
}


#define UPDATE_PERIOD_KEENIO 60000
#define TIMEOUT_PERIOD_KEENIO 3000
#define DATA_HOST_KEENIO "api.keen.io"
#define API_KEY_KEENIO "enter-your-api-key-here"
#define REQUEST_URL_KEENIO "enter-your-KeenIO-request-url-here"

void logToKeenIO(void)
{
  WiFiClient client;
  static long dataLogTimer = -40000;
  static long transmissionAttempts;
  static long replyTimeouts;
  static long connectionFailures;
  static long postingTime = -1;

  // is it the time for next data logging?
  if (millis() -  dataLogTimer < UPDATE_PERIOD_KEENIO)
  {
    return;
  }
  dataLogTimer = millis();
  transmissionAttempts++;

  Serial.printf("DATALOG > %s > ", DATA_HOST_KEENIO);

  // connect to the host
  if (!client.connect(DATA_HOST_KEENIO, 80))
  {
    Serial.print("Connection failure!");
    connectionFailures++;
    return;
  }

  Serial.print("Sending > ");

  String jsonData = String("{") +
          "\"EspCloud_UpTime\":" + String (dataLogTimer / 60000) +
          ",\"EspCloud_HeapSize\":" + String (system_get_free_heap_size()) +
          ",\"EspCloud_TransmissionAttempts\":" + String (transmissionAttempts) +
          ",\"EspCloud_ReplyTimeouts\":" + String (replyTimeouts) +
          ",\"EspCloud_ConnectionFailures\":" + String (connectionFailures) +
          ",\"EspCloud_PostingTime\":" + String (postingTime) +
          "}";

  // send the data to the host
  client.print(
    String("POST ") + REQUEST_URL_KEENIO + " HTTP/1.1\r\n" +
           "Host: " + DATA_HOST_KEENIO + "\r\n" +
           "Content-Type: application/json\r\n" +
           "User-Agent: ESP8266 MyCloud\r\n" +
           "Authorization:" + API_KEY_KEENIO + " \r\n" +
           "Content-Length:" + jsonData.length() + "\r\n" +
           "Connection: close\r\n\r\n");
  client.print(jsonData);

  // wait for reply from the host
  while (!client.available())
  {
    if (millis() - dataLogTimer > TIMEOUT_PERIOD_KEENIO)
    {
      Serial.println("Reply timeout!");
      replyTimeouts++;
      postingTime = -1;
      client.stop();
      return;
    }
    delay(1);
  }

  // show reply from the host
  while (client.available())
  {
    Serial.write(client.read());
  }
  Serial.print(" > Done");
  client.stop();

  // show time to log the data
  postingTime = millis() - dataLogTimer;
  Serial.printf(" in %d ms\n", postingTime);
}


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("EspToCloud-All 0.1.1");

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  Serial.printf("Data are posted to %s everyy %d seconds\n", DATA_HOST_EMONCMS, UPDATE_PERIOD_EMONCMS/1000);
  Serial.printf("Data are posted to %s everyy %d seconds\n", DATA_HOST_THINGSPEAK, UPDATE_PERIOD_THINGSPEAK/1000);
  Serial.printf("Data are posted to %s everyy %d seconds\n", DATA_HOST_KEENIO, UPDATE_PERIOD_KEENIO/1000);
  Serial.println();
}


void loop(void)
{
  logToEmoncms();
  logToThingSpeak();
  logToKeenIO();
}
