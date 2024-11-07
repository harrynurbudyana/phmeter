#include <Arduino.h>

int ph0 = A0;
int samples = 10;
float adc_resolution = 1024.0;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
  delay(1000);
  Serial.println('pH sense');
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
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}