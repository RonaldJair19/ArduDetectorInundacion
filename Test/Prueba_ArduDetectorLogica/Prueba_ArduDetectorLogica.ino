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
  // scanner.SetCurrentTime(millis());
  // scanner.CalculateElapsedTime();
  Serial.println("Tiempo: "+String(scanner.GetElapsedTime(millis())));
  Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
  Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
  Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));
  Serial.println("Color actual: " + String(scanner.GetColorState()));
  Serial.println("Distancia recorrida: "+String(scanner.GetDistanceTraveled()));
  delay(3000);
  Serial.println("Se agrega BLUE");
  scanner.AddColorDetected(3);
  // scanner.SetCurrentTime(millis());
  // scanner.CalculateElapsedTime();
  Serial.println("Tiempo: "+String(scanner.GetElapsedTime(millis())));
  Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
  Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
  Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));
  Serial.println("Color actual: " + String(scanner.GetColorState()));
  Serial.println("Distancia recorrida: "+String(scanner.GetDistanceTraveled()));
  delay(2500);
  Serial.println("Se agrega GREEN");
  scanner.AddColorDetected(4);
  // scanner.SetCurrentTime(millis());
  // scanner.CalculateElapsedTime();
  Serial.println("Tiempo: "+String(scanner.GetElapsedTime(millis())));
  Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
  Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
  Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));
  Serial.println("Color actual: " + String(scanner.GetColorState()));
  Serial.println("Distancia recorrida: "+String(scanner.GetDistanceTraveled()));
  delay(4000);
  Serial.println("Se regresa a BLUE");
  scanner.AddColorDetected(3);
  // scanner.SetCurrentTime(millis());
  // scanner.CalculateElapsedTime();
  Serial.println("Tiempo: "+String(scanner.GetElapsedTime(millis())));
  Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
  Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
  Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));
  Serial.println("Color actual: " + String(scanner.GetColorState()));
  Serial.println("Distancia recorrida: "+String(scanner.GetDistanceTraveled()));
  delay(5000);
  Serial.println("Se regresa a BLACK");
  scanner.AddColorDetected(2);
  // scanner.SetCurrentTime(millis());
  // scanner.CalculateElapsedTime();
  Serial.println("Tiempo: "+String(scanner.GetElapsedTime(millis())));
  Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
  Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
  Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));
  Serial.println("Color actual: " + String(scanner.GetColorState()));
  Serial.println("Distancia recorrida: "+String(scanner.GetDistanceTraveled()));
  delay(2000);
}
