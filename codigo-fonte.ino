#include "Arduino.h"
#include "WiFi.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>


#define DHTPIN 7  
#define DHTTYPE DHT11 

// Portas
const byte RED = 10;
const byte BLUE = 11;
const byte GREEN = 12;
const int BUZZER = 8;
int analogInPin = A0;
int PinSensor = 6;
#include "Arduino.h"
#include "WiFi.h"
#include <HTTPClient.h>
HTTPClient client;
char nomeWifi[] = "samsung fli3";
char senhaWifi[] = "jubsleu19";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[]   = "87ae2cb3-f941-45b6-8d8c-1e61f3ccd949";
float temperatura = 0;
void setup() {
  Serial.begin(9600);
  init_wifi();
}
void loop() {
  // put your main code here, to run repeatedly:
  temperatura++;
  send_temperatura();
  delay(5000);
}
void init_wifi() {
  Serial.println("Conectando WiFi");
  Serial.print("Wifi: ");
  Serial.println(nomeWifi);
  WiFi.begin(nomeWifi, senhaWifi);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("WiFi Conectado");
  Serial.print("Meu IP eh: ");
  Serial.println(WiFi.localIP());
}
void send_temperatura() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;
  strcpy(postData, "{\n\t\"variable\": \"temperature\",\n\t\"value\": ");
  dtostrf(temperatura, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);
  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
} 