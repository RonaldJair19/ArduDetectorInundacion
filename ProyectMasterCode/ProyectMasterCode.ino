#include "Arduino.h"
#include "heltec.h"
#include "ArduDetectorLibrary.h"
#include <TTN_esp32.h>
#include "TTN_CayenneLPP.h"
#include "LoRaConfig.h" //Create this library and add your credentials of The Things Stack

/* Board Heltec Wireless Stick */
#define S0 12
#define S1 13
#define S2 17
#define S3 23
#define outputTCS 39

SensorRGB sensorRGB(S0, S1, S2, S3, outputTCS);
Scanner scanner;
TTN_esp32 ttn ;
TTN_CayenneLPP lpp;

void message(const uint8_t* payload, size_t size, int rssi)
{
    Serial.println("-- MESSAGE");
    Serial.print("Received " + String(size) + " bytes RSSI= " + String(rssi) + "dB");

    for (int i = 0; i < size; i++)
    {
        Serial.print(" " + String(payload[i]));
        // Serial.write(payload[i]);
    }
    Serial.println();
}

void setup() {
  Heltec.begin(true /*Display Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  // Heltec.display->setContrast(255);
  // Heltec.display->clear();
  // Heltec.display->flipScreenVertically();
  // Heltec.display->setFont(ArialMT_Plain_10);
  // Serial.begin(9600);
  // ttn.begin();
  // ttn.onMessage(message); // declare callback function when is downlink from server
  // ttn.personalize(devAddr, nwkSKey, appSKey);
  // ttn.showStatus();
  sensorRGB.InitSensorRGB();
  sensorRGB.SetParametersColors(SensorRGB::BLACK, 900,900,700);
  sensorRGB.SetParametersColors(SensorRGB::BLUE, 700,300,150);
  sensorRGB.SetParametersColors(SensorRGB::GREEN, 700,400,400);
  sensorRGB.SetParametersColors(SensorRGB::RED, 180,581,419);
  scanner.SetSeparationDistance(0.30);

}

void loop() {
  //if(millis() > tiempoInicio + INTERVALO_MENSAJE){
    //tiempoInicio = millis();
   //}
    lpp.reset();
    Heltec.display->clear();
    sensorRGB.ReadRGB();
    Serial.print("R:");
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::REDLIGHT));     // muestra valor de variable rojo
    Serial.print("\t");
    

    Serial.print("V:");
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::GREENLIGHT));      // muestra valor de variable verde
    Serial.print("\t");
    
    
    Serial.print("A:");
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::BLUELIGHT));     // muestra valor de variable azul
    Serial.println();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);

    if(sensorRGB.DetectColor()){
      if(scanner.AddColorDetected(sensorRGB.GetDetectedColor())){
        scanner.CalculateElapsedTime(millis());
        Serial.println("blk: "+String(scanner.GetCountColor(Scanner::BLACK)));
        Serial.println("bl: "+String(scanner.GetCountColor(Scanner::BLUE)));
        Serial.println("gr: "+String(scanner.GetCountColor(Scanner::GREEN)));
        Serial.println("Color actual: " + String(scanner.GetColorState()));
        Serial.println("Tiempo minutos: "+String(scanner.GetElapsedTime()/60000));
        Serial.println("Tiempo segundos: "+String(scanner.GetElapsedTime()/1000));
        Serial.println("Tiempo milisegundos: "+String(scanner.GetElapsedTime()));
        Serial.println("Distancia recorrida: "+String(scanner.GetDistanceTraveled()));
        /*============ Building payload ============*/
        lpp.addDigitalOutput(1,scanner.GetColorState());
        lpp.addDigitalOutput(2,scanner.GetCountColor(sensorRGB.GetDetectedColor()));
        lpp.addTIME(3,(scanner.GetElapsedTime()/1000));
        lpp.addTemperature(4,scanner.GetDistanceTraveled());
          // if (ttn.sendBytes(lpp.getBuffer(), lpp.getSize())){
            Serial.printf("TTN_CayenneLPP: %02X %02X %02X %02X %02X %02X %02X %02X\n", 
              lpp.getBuffer()[0], lpp.getBuffer()[1], 
              lpp.getBuffer()[2], lpp.getBuffer()[3],lpp.getBuffer()[4],
              lpp.getBuffer()[5],lpp.getBuffer()[6],lpp.getBuffer()[7]);
          // }
      }
      if(sensorRGB.GetDetectedColor() == scanner.GetColorState()){
        Heltec.display->drawString(0, 0, "C: " + String(sensorRGB.GetDetectedColor()) + " L: "+String(scanner.GetCountColor(sensorRGB.GetDetectedColor())));
        Heltec.display->drawString(0, 10, "Time: " + String(((int)scanner.GetElapsedTime())/1000));
        Heltec.display->drawString(0, 20, "Dist: " + String(scanner.GetDistanceTraveled()));
      }
      else{
        Heltec.display->drawString(0, 0, "C: " + String(sensorRGB.GetDetectedColor()));
      }
    }
    else{
      Heltec.display->drawString(0, 0, "Red: " + String(sensorRGB.GetValueRGB(SensorRGB::REDLIGHT)));
      Heltec.display->drawString(0, 10, "Green: " + String(sensorRGB.GetValueRGB(SensorRGB::GREENLIGHT)));
      Heltec.display->drawString(0, 20, "Blue: " + String(sensorRGB.GetValueRGB(SensorRGB::BLUELIGHT)));
    }
    
    Heltec.display->setColor(WHITE);
    Heltec.display->display();
}
