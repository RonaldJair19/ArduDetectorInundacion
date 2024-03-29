#include "libreria.h"
#include <Arduino.h>

Scanner::Scanner(/* args */){
    _currentTime = 0;
    _previusTime = 0;
    _elapsedTime = 0;
    _blk = 0;
    _bl = 0;
    _gr = 0;
    _yw = 0;
    _org = 0;
    _re = 0;
    _indexMain = 0;
    _presentColor = COLORLESS;
}

void Scanner::SetCurrentTime(uint32_t currentTime){
    _previusTime = _currentTime;
    _currentTime = currentTime;
}

void Scanner::CalculateElapsedTime(){
    _elapsedTime = _currentTime - _previusTime;
}

uint32_t Scanner::GetElapsedTime(uint32_t currentTime){
    _previusTime = _currentTime;
    _currentTime = currentTime;
    _elapsedTime = _currentTime - _previusTime;
    return _elapsedTime;
}



void Scanner::AddColorDetected(uint8_t newColor){
    if(_colorsAssigned[_indexMain] == newColor){
        switch (newColor){
            case BLACK:
                    _blk++;
                break;
            case BLUE:
                    _bl++;
                break;
            case GREEN:
                    _gr++;
                break;
            case YELLOW:
                    _yw++;
                break;
            case ORANGE:
                    _org++;
                break;
            case RED:
                    _re++;
                break;
            default:
                break;
        }
    _colorAdded[_indexMain] = newColor;
    _presentColor = _colorAdded[_indexMain];
    _indexMain++;
    }
    else if((_blk != 0) && (_colorsAssigned[_indexMain-2] == newColor) && (newColor != GRAY)){
        _indexMain--;
        switch (_colorAdded[_indexMain]){
            case BLACK:
                    _blk--;
                break;
            case BLUE:
                    _bl--;
                break;
            case GREEN:
                    _gr--;
                break;
            case YELLOW:
                    _yw--;
                break;
            case ORANGE:
                    _org--;
                break;
            case RED:
                    _re--;
                break;
            default:
                break;
        }
        _presentColor = _colorAdded[_indexMain-1];
        _colorAdded[_indexMain] = COLORLESS;
    }
    // else if(newColor == GRAY){
    //     _blk--;
    //     _indexMain = 0;
    //     _colorAdded[_indexMain] = COLORLESS;
    //     _presentColor = _colorAdded[_indexMain];
    // }
    // if(_indexMain > 0){
    //     _presentColor = _colorAdded[_indexMain-1];
    // }
}

uint8_t Scanner::GetCountColor(Colors Color){
    switch (Color){
        case BLACK:
                return _blk;
            break;
        case BLUE:
                return _bl;
            break;
        case GREEN:
                return _gr;
            break;
        case YELLOW:
                return _yw;
            break;
        case ORANGE:
                return _org;
            break;
        case RED:
                return _re;
            break;
        default:
            break;
    }
}

uint8_t Scanner::GetColorState(){
    return _presentColor;
}

float Scanner::GetDistanceTraveled(){
    _distanceTraveledY = (_blk+_bl+_gr+_yw+_org+_re) * (SEPARATION_DISTANCE);
}
