#include <Arduino.h>

#define offsetNegative 100
#define offsetPositive 150

class SensorRGB{
private:
    /* data */
    int8_t _S0, _S1, _S2, _S3, _outputTCS;
    uint16_t _redLight, _greenLight, _blueLight;
    int16_t _RedForGrayColor, _GreenForGrayColor, _BlueForGrayColor;
    int16_t _RedForBlackColor, _GreenForBlackColor, _BlueForBlackColor;
    int16_t _RedForBlueColor, _GreenForBlueColor, _BlueForBlueColor;
    int16_t _RedForGreenColor, _GreenForGreenColor, _BlueForGreenColor;
    int16_t _RedForYellowColor, _GreenForYellowColor, _BlueForYellowColor;
    int16_t _RedForOrangeColor, _GreenForOrangeColor, _BlueForOrangeColor;
    int16_t _RedForRedColor, _GreenForRedColor, _BlueForRedColor;

public:
    enum Colors{
        COLORLESS,
        GRAY,
        BLACK,
        BLUE,
        GREEN,
        YELLOW,
        ORANGE,
        RED
    };
    enum ValuesRGB{
        REDLIGHT,
        GREENLIGHT,
        BLUELIGHT
    };
    SensorRGB(int8_t S0, int8_t S1, int8_t S2, int8_t S3, int8_t outputTCS);
    void InitSensorRGB();
    bool ReadRGB();
    int DetectedColor();
    void SetParametersColors(Colors color, int16_t avgRedLight, int16_t avgGreenLight, int16_t avgBlueLight);
    int GetValueRGB(ValuesRGB colorRGB);
    // ~SensorRGB();
};


