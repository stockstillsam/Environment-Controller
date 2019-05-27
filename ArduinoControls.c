
#include <SimpleDHT.h>

#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define ENABLE2 6
#define DIRC 7
#define DIRD 8

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;

int pinLight = 0;

void setup() {
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(ENABLE2,OUTPUT);
  pinMode(DIRC,OUTPUT);
  pinMode(DIRD,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Reading sensors...");
  
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }
  
  Serial.print("Sample DHT11 RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  
  Serial.print("Sample DHT11 OK: ");
  Serial.print((int)temperature); Serial.print("° Celsius, ");
  Serial.print((int)humidity); Serial.println("% Humidity");
  
  Serial.print("Sample Photocell: ");
  int light = analogRead(pinLight);
  Serial.print((int)light); Serial.println(" Brightness");

  if(humidity>78 || temperature>20) {
  Serial.println("Exhaust On");
  delay(1000);
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,LOW); //one way
  digitalWrite(DIRB,HIGH);
  delay(1000);
  }
  else {
  digitalWrite(ENABLE,LOW); //fast stop
  digitalWrite(ENABLE2,HIGH);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,HIGH);
  delay(2000);
  }
  digitalWrite(ENABLE2,LOW);
  
  // DHT11 sampling rate is 1HZ.
  delay(10000);
}
