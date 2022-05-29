#include "Arduino.h"
#include "heltec.h"
#include "ArduDetectorLibrary.h"

/* Board Heltec Wireless Stick */
#define S0 12    // S0 a pin 4
#define S1 13    // S1 a pin 5
#define S2 17    // S2 a pin 6
#define S3 23    // S3 a pin 7
#define outputTCS 39 // salidaTCS a pin 8
SensorRGB sensorRGB(S0, S1, S2, S3, outputTCS);

void setup() {
  Heltec.begin(true /*Display Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  // Heltec.display->setContrast(255);
  // Heltec.display->clear();
  // Heltec.display->flipScreenVertically();
  // Heltec.display->setFont(ArialMT_Plain_10);
  Serial.begin(9600);
  sensorRGB.InitSensorRGB();

}

void loop() {
  //if(millis() > tiempoInicio + INTERVALO_MENSAJE){
    //tiempoInicio = millis();
   //}
    Heltec.display->clear();
    sensorRGB.ReadRGB();
    Serial.print("R:");     // muestra texto
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::REDLIGHT));     // muestra valor de variable rojo
    Serial.print("\t");     // espacio de tabulacion
    

    Serial.print("V:");     // muestra texto
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::GREENLIGHT));      // muestra valor de variable verde
    Serial.print("\t");     // espacio de tabulacion
    
    
    Serial.print("A:");     // muestra texto
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::BLUELIGHT));     // muestra valor de variable azul
    Serial.println();// y salto de linea

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    sensorRGB.SetParametersColors(SensorRGB::RED, 180,581,419);
    if(sensorRGB.DetectedColor()){
      Heltec.display->drawString(0, 0, "Red: " + String(sensorRGB.DetectedColor()));
    }
    else{
      Heltec.display->drawString(0, 0, "Red: " + String(sensorRGB.GetValueRGB(SensorRGB::REDLIGHT)));
      Heltec.display->drawString(0, 10, "Green: " + String(sensorRGB.GetValueRGB(SensorRGB::GREENLIGHT)));
      Heltec.display->drawString(0, 20, "Blue: " + String(sensorRGB.GetValueRGB(SensorRGB::BLUELIGHT)));
    }
    
    Heltec.display->setColor(WHITE);
    Heltec.display->display();
    //Serial.println(millis());
    // if((rojo >= 140 && rojo <=160) && (verde >= 400 && verde <= 430)&& (azul >= 290 && azul <=330)){
    //   Serial.println("Color rojo");
    //   t1 = millis();
    //   Serial.println(t1/1000);
    // }
    // if((rojo >= 100 && rojo <=130) && (verde >= 130 && verde <= 160)&& (azul >= 200 && azul <=230)){
    //   Serial.println("Color amarillo");
    //   t2 = millis();
    //   Serial.println(t2/1000);
    // }
    // if(t1 != 0 && t2 != 0){
    //   tf = t2 - t1;
    //   Serial.println(tf/1000);
    //   v = 0.30 / ((tf/1000));
    //   Serial.println("Velocidad: " + String(v));
    //   t1 = 0;
    //   t2 = 0;
    // }
    
}
