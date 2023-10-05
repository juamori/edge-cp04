#include "Arduino.h"
#include "WiFi.h"
#include "DHT.h"
#include <HTTPClient.h>

 

DHT dht(15, DHT11);

 

HTTPClient client;
char nomeWifi[] = "iPhone Airton";
char senhaWifi[] = "2153818aa";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[] = "4400d025-0122-4d35-bde9-f2f621db6844";
float umidade = 0; // Change the variable name to umidade (humidity)

 

void setup() {
  Serial.begin(9600);
  dht.begin();
  init_wifi();
}

 

void loop() {
  umidade = dht.readHumidity(); // Read humidity instead of temperature
  send_umidade(); // Call the function to send humidity data
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

 

void send_umidade() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;
  strcpy(postData, "{\n\t\"variable\": \"humidity\",\n\t\"value\": "); // Change variable to "humidity"
  dtostrf(umidade, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"%\"\n\t}\n"); // Change unit to "%"
  strncat(postData, anyData1, 100);
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

 

  strcpy(postData, "{\n\t\"variable\": \"temperature\",\n\t\"value\": "); // Change variable to "humidity"
  dtostrf(umidade, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat(postData, anyData1, 100);
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