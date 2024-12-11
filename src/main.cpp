#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <Wire.h>

const char* ssid     = "this.wifi";
const char* password = "this@wifi";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://20.189.125.134:9000/product";


int ph0 = A0;
int samples = 10;
float adc_resolution = 1024.0;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(115200);
  delay(1000);
  Serial.println("pH sense");
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  }

float pH(float voltage){
  return 7 + ((2.5 - voltage) / 0.18);
}

void loop() {
  // put your main code here, to run repeatedly:
  int measurings = 0;
  for (int i =0; i <samples; i++){
    measurings+= analogRead(ph0);
    delay(10);
  }
  float voltage = 5 / adc_resolution * measurings/samples;
  Serial.print("pH = ");
  Serial.println(pH(voltage));
  delay(3000);
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"name\":\"string\",\"price\":7000,\"description\":\"string\"}");
    if(httpResponseCode > 0){
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);
      if (httpResponseCode == 200 || httpResponseCode == 201)
      {
        Serial.println("Data berhasil dikirim");
      }
      
    } else {
      Serial.print("Error Code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}