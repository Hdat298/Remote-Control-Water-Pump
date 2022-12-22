#include <Ethernet.h>
#include <SPI.h>
#include <EthernetUdp.h>
#include <Arduino.h>
#include <string.h>

#define RELAY_PIN 2
#define MOISTURE_PIN A0

#define THRESHOLD 300

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 6 };

byte server[] = { 192, 168, 1, 5 };
unsigned int localPort = 6767;
int port = 8888;

EthernetUDP Udp;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

void setup()
{
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
}

int read() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i = 0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBuffer
    for (int i = 0; i < UDP_TX_PACKET_MAX_SIZE; i++) packetBuffer[i] = 0;
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
  }
}
char string[20];
void loop()
{
  int valueCurrent = analogRead(MOISTURE_PIN);
  itoa(valueCurrent, string, 10);


  if (valueCurrent < THRESHOLD) {
    Serial.print("The soil is DRY");
    Serial.print(" (");
    Serial.print(valueCurrent);
    Udp.beginPacket(server, port);
    Udp.write("The soil is DRY with humidity index: ");
    Udp.write(string);
    Udp.endPacket();
    Serial.println(")");
    delay(5000);
  } else if (valueCurrent > THRESHOLD) {
    Serial.print("The soil is WET");
    Serial.print(" (");
    Serial.print(valueCurrent);
    Serial.println(")");
    Udp.beginPacket(server, port);
    Udp.write("The soil is WET with humidity index: ");
    Udp.write(string);
    Udp.endPacket();
    delay(5000);
  }
  read();
  int n = atoi(packetBuffer);
  Serial.println(n);

  switch (n)
  {
    case 1:
      Serial.print("Pump Water is on");
      Udp.beginPacket(server, port);
      Udp.write("The soil is WET with humidity index: ");
      Udp.write(string);
      Udp.write(" Manual mode: ON");
      Udp.endPacket();
      digitalWrite(RELAY_PIN, HIGH);
      break;
    case 2:
      Serial.print("Pump Water is off");
      Udp.beginPacket(server, port);
      Udp.write("The soil is WET with humidity index: ");
      Udp.write(string);
      Udp.write(" Manual mode: OFF");
      Udp.endPacket();
      digitalWrite(RELAY_PIN, LOW);
      break;
    case 3:
      do {
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < THRESHOLD) {
          Serial.print("The soil is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:   ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(" (");
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(" (");
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 3 || n == 0);
      break;
    case 100:
      do {
        const int valueSensor = 100;
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < valueSensor) {
          Serial.print("The soil lala is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil lala is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 100 || n == 0);
      break;
    case 200:
      do {
        const int valueSensor = 200;
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < valueSensor) {
          Serial.print("The soil lala 2 is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Serial.print(" (");
          Serial.print(valueCurrent);
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil lala 2 is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 200 || n == 0);
      break;
    case 300:
      do {
        const int valueSensor = 300;
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < valueSensor) {
          Serial.print("The soil lala 3 is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil lala 3 is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 300 || n == 0);
      break;
    case 400:
      do {
        const int valueSensor = 400;
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < valueSensor) {
          Serial.print("The soil lala 4 is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil lala 4 is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 400 || n == 0);
      break;
    case 500:
      do {
        const int valueSensor = 500;
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < valueSensor) {
          Serial.print("The soil lala 5 is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil lala 5 is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 500 || n == 0);
      break;
    case 700:
      do {
        const int valueSensor = 700;
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < valueSensor) {
          Serial.print("The soil lala 7 is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil lala 7 is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 700 || n == 0);
      break;
      case 1000:
      do {
        const int valueSensor = 1000;
        read();
        n = atoi(packetBuffer);
        Serial.println(n);
        if (valueCurrent < valueSensor) {
          Serial.print("The soil lala 10 is DRY => turn pump ON");
          digitalWrite(RELAY_PIN, HIGH);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is DRY => turn pump ON:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        } else {
          Serial.print("The soil lala 10 is WET => turn pump OFF");
          digitalWrite(RELAY_PIN, LOW);
          Serial.print(" (");
          Udp.beginPacket(server, port);
          Udp.write("The soil is WET => turn pump OFF:  ");
          Udp.write(string);
          Udp.write(" Auto mode: ON");
          Udp.endPacket();
          Serial.print(valueCurrent);
          Serial.println(")");
          delay(5000);
        }
      } while (n == 1000 || n == 0);
      break;
  }
}