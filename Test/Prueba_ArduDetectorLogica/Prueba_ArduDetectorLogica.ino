#include "libreria.h"
#include <Arduino.h>

Scanner scanner;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println("Se agrega BLACK");
  scanner.AddColorDetected(2);
  Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
  delay(3000);
  Serial.println("Se agrega BLUE");
  scanner.AddColorDetected(3);
  Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
  delay(3000);
  Serial.println("Se agrega GREEN");
  scanner.AddColorDetected(4);
  Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));
  delay(3000);
  Serial.println("Se regresa a BLUE");
  scanner.AddColorDetected(3);
  Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
  Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
  Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));

}
