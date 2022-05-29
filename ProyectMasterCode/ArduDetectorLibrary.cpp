#include "ArduDetectorLibrary.h"
#include "Arduino.h"


SensorRGB::SensorRGB(int8_t S0, int8_t S1, int8_t S2, int8_t S3, int8_t outputTCS){
    _S0 = S0;
    _S1 = S1;
    _S2 = S2;
    _S3 = S3;
    _outputTCS = outputTCS;
}

bool SensorRGB::ReadRGB(){
    digitalWrite(_S2,LOW);
    digitalWrite(_S3,LOW);
    _redLight = pulseIn(_outputTCS, LOW);
    delay(200);
    digitalWrite(_S2,HIGH);    // establece fotodiodos
    digitalWrite(_S3,HIGH);
    _greenLight = pulseIn(_outputTCS, LOW);
    delay(200);
    digitalWrite(_S2,LOW);     // establece fotodiodos
    digitalWrite(_S3,HIGH);
    _blueLight= pulseIn(_outputTCS, LOW);
}

void SensorRGB::InitSensorRGB(){
    pinMode(_S0, OUTPUT);
    pinMode(_S1, OUTPUT);
    pinMode(_S2, OUTPUT);
    pinMode(_S3, OUTPUT); 
    pinMode(_outputTCS, INPUT);
    digitalWrite(_S0,HIGH);  // establece frecuencia de salida
    digitalWrite(_S1,LOW);   // del modulo al 20 por ciento
}

int SensorRGB::GetValueRGB(ValuesRGB ColorRGB){
    switch (ColorRGB){
    case REDLIGHT:
            return _redLight;
        break;
    case GREENLIGHT:
            return _greenLight;
        break;
    case BLUELIGHT:
            return _blueLight;
    default:
        break;
    }
}


void SensorRGB::SetParametersColors(Colors color, int16_t avgRedLight, int16_t avgGreenLight, int16_t avgBlueLight){
    switch (color){
    case GRAY:
            _RedForGrayColor = avgRedLight;
            _GreenForGrayColor = avgGreenLight;
            _BlueForGrayColor = avgBlueLight;
        break;
    case BLACK:
            _RedForBlackColor = avgRedLight;
            _GreenForBlackColor = avgGreenLight;
            _BlueForBlackColor = avgBlueLight;
        break;
    case BLUE:
            _RedForBlueColor = avgRedLight;
            _GreenForBlueColor = avgGreenLight;
            _BlueForBlueColor = avgBlueLight;
        break;
    case GREEN:
            _RedForGreenColor = avgRedLight;
            _GreenForGreenColor = avgGreenLight;
            _BlueForGreenColor = avgBlueLight;
        break;
    case YELLOW:
            _RedForYellowColor = avgRedLight;
            _GreenForYellowColor = avgGreenLight;
            _BlueForYellowColor = avgBlueLight;
        break;
    case ORANGE:
            _RedForOrangeColor = avgRedLight;
            _GreenForOrangeColor = avgGreenLight;
            _BlueForOrangeColor = avgBlueLight;
        break;
    case RED:
            _RedForRedColor = avgRedLight;
            _GreenForRedColor = avgGreenLight;
            _BlueForRedColor = avgBlueLight;
        break;
    default:
        break;
    }
}

int SensorRGB::DetectedColor(){
    /* =========== Detecting Gray color ===========*/
    if((_redLight >= _RedForGrayColor - offsetNegative && _redLight <= _RedForGrayColor  + offsetPositive) && (_greenLight >= _GreenForGrayColor - offsetNegative && _greenLight <= _GreenForGrayColor + offsetPositive) && (_blueLight >= _BlueForGrayColor - offsetNegative && _blueLight <= _BlueForGrayColor + offsetPositive)){
        return BLACK;
    }
    /* =========== Detecting Black color ===========*/
    if((_redLight >= _RedForBlackColor - offsetNegative && _redLight <= _RedForBlackColor  + offsetPositive) && (_greenLight >= _GreenForBlackColor - offsetNegative && _greenLight <= _GreenForBlackColor + offsetPositive) && (_blueLight >= _BlueForBlackColor - offsetNegative && _blueLight <= _BlueForBlackColor + offsetPositive)){
        return BLACK;
    }
    /* =========== Detecting Blue color ===========*/
    if((_redLight >= _RedForBlueColor - offsetNegative && _redLight <= _RedForBlueColor  + offsetPositive) && (_greenLight >= _GreenForBlueColor - offsetNegative && _greenLight <= _GreenForBlueColor + offsetPositive) && (_blueLight >= _BlueForBlueColor - offsetNegative && _blueLight <= _BlueForBlueColor + offsetPositive)){
        return BLUE;
    }
    /* =========== Detecting Green color ===========*/
    if((_redLight >= _RedForGreenColor - offsetNegative && _redLight <= _RedForGreenColor  + offsetPositive) && (_greenLight >= _GreenForGreenColor - offsetNegative && _greenLight <= _GreenForGreenColor + offsetPositive) && (_blueLight >= _BlueForGreenColor - offsetNegative && _blueLight <= _BlueForGreenColor + offsetPositive)){
        return GREEN;
    }
    /* =========== Detecting Yellow color ===========*/
    if((_redLight >= _RedForYellowColor - offsetNegative && _redLight <= _RedForYellowColor  + offsetPositive) && (_greenLight >= _GreenForYellowColor - offsetNegative && _greenLight <= _GreenForYellowColor + offsetPositive) && (_blueLight >= _BlueForYellowColor - offsetNegative && _blueLight <= _BlueForYellowColor + offsetPositive)){
        return YELLOW;
    }
    /* =========== Detecting Orange color ===========*/
    if((_redLight >= _RedForOrangeColor - offsetNegative && _redLight <= _RedForOrangeColor  + offsetPositive) && (_greenLight >= _GreenForOrangeColor - offsetNegative && _greenLight <= _GreenForOrangeColor + offsetPositive) && (_blueLight >= _BlueForOrangeColor - offsetNegative && _blueLight <= _BlueForOrangeColor + offsetPositive)){
        return ORANGE;
    }
    /* =========== Detecting Red color ===========*/
    if((_redLight >= _RedForRedColor - offsetNegative && _redLight <= _RedForRedColor  + offsetPositive) && (_greenLight >= _GreenForRedColor - offsetNegative && _greenLight <= _GreenForRedColor + offsetPositive) && (_blueLight >= _BlueForRedColor - offsetNegative && _blueLight <= _BlueForRedColor + offsetPositive)){
        return RED;
    }
    /* =========== No color detected ===========*/
    else{
        return COLORLESS;
    }
}