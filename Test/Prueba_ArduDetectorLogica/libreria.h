#include <Arduino.h>

#define SEPARATION_DISTANCE 0.30
class Scanner
{
private:
    /* data */
    uint8_t _colorsAssigned[13] = {2,3,4,5,6,7,2,3,4,5,6,7};
    uint8_t _colorAdded[13], _blk, _bl, _gr, _yw, _org, _re;
    uint8_t _indexMain;
    uint8_t _presentColor;
    uint32_t _currentTime, _previusTime, _elapsedTime;
    float _distanceTraveledY;

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
    void SetCurrentTime(uint32_t currentTime);
    void CalculateElapsedTime();
    uint32_t GetElapsedTime();
    void AddColorDetected(uint8_t newColor);
    uint8_t GetCountColor(Colors Color);
    uint8_t GetColorState();
    float GetDistanceTraveled();
    // ~Scanner();
};

