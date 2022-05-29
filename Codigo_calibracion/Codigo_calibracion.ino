#include "Arduino.h"
#include "heltec.h"

#define S0 12    // S0 a pin 4
#define S1 13    // S1 a pin 5
#define S2 17    // S2 a pin 6
#define S3 23    // S3 a pin 7
#define salidaTCS 39 // salidaTCS a pin 8

void filtroRGB();
unsigned long t1, t2, tf;
int rojo, azul, verde;
float v;
void setup() {
  Heltec.begin(true /*Display Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  pinMode(S0, OUTPUT);    
  pinMode(S1, OUTPUT);    
  pinMode(S2, OUTPUT);    
  pinMode(S3, OUTPUT);   
  pinMode(salidaTCS, INPUT);
  digitalWrite(S0,HIGH); 
  digitalWrite(S1,LOW);   
  Serial.begin(9600); 
}

void loop() {

    Heltec.display->clear();
    filtroRGB();
    Serial.print("R:");     
    Serial.print(rojo);     
    Serial.print("\t");     
    
    Serial.print("V:");     
    Serial.print(verde);    
    Serial.print("\t");     
    
    Serial.print("A:");    
    Serial.print(azul);     
    Serial.println();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(0, 0, "Red: " + String(rojo));
    Heltec.display->drawString(0, 10, "Green: " + String(verde));
    Heltec.display->drawString(0, 20, "Blue: " + String(azul));  
    Heltec.display->setColor(WHITE);
    Heltec.display->display();
}

void filtroRGB(){
    digitalWrite(S2,LOW);     
    digitalWrite(S3,LOW);    
    rojo = pulseIn(salidaTCS, LOW);
    delay(200);
    digitalWrite(S2,HIGH);   
    digitalWrite(S3,HIGH);    
    verde = pulseIn(salidaTCS, LOW); 
    delay(200);
    digitalWrite(S2,LOW);    
    digitalWrite(S3,HIGH);   
    azul = pulseIn(salidaTCS, LOW);
}
