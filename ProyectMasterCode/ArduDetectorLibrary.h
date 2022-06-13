#include <Arduino.h>

#define offsetNegative 75
#define offsetPositive 75

/* ===========================================*/
/*              Class SensorRGB               */
/* ===========================================*/
class SensorRGB{
private:
    /* data */
    int8_t _colorState, _S0, _S1, _S2, _S3, _outputTCS;
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
    bool DetectColor();
    void SetParametersColors(Colors color, int16_t avgRedLight, int16_t avgGreenLight, int16_t avgBlueLight);
    int GetValueRGB(ValuesRGB colorRGB);
    int GetDetectedColor();
    // ~SensorRGB();
};

/* ===========================================*/
/*                Class Scanner               */
/* ===========================================*/
class Scanner{
private:
    /* data */
    uint8_t _colorsAssigned[13] = {2,3,4,5,6,7,2,3,4,5,6,7};
    uint8_t _colorAdded[13], _blk, _bl, _gr, _yw, _org, _re;
    uint8_t _indexMain;
    uint8_t _presentColor;
    uint32_t _currentTime, _previusTime, _elapsedTime;
    float _distanceTraveledY, _separationDistance;

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
    Scanner(/* args */);
    void SetSeparationDistance(float SeparationDistance);
    void SetCurrentTime(uint32_t currentTime);
    void CalculateElapsedTime();
    uint32_t GetElapsedTime();
    void CalculateElapsedTime(uint32_t currentTime);
    bool AddColorDetected(uint8_t newColor);
    uint8_t GetCountColor(uint8_t colorNumber);
    uint8_t GetColorState();
    float GetDistanceTraveled();
    // ~Scanner();
};
