
# ArduFlood detector 

In this repository are presented the codes and libraries related to the final prototype device for flood monitoring and early warning.

## Hardware materials used
- ### Heltec Wireless Stick
![Image text](https://github.com/RonaldJair19/ArduDetectorInundacion/blob/master/DiagramsAndImages/HeltecWirelessStick.png)

- ### Sensor GY-031
![Image text](https://github.com/RonaldJair19/ArduDetectorInundacion/blob/master/DiagramsAndImages/GY031.png)

- ### Circuit
![Image text](https://github.com/RonaldJair19/ArduDetectorInundacion/blob/master/DiagramsAndImages/CircuitHeltecSensor.png)

## Contents of the repository
The following is a description of the contents of each folder and the functionalities contained in the codes.

- ### ProyectMasterCode: 
It contains the main code of the project and the libraries used within it.
- ### Test: 
It contains a calibration code for the color sensor used to detect the RGB values and display them on the OLED screen of the Heltec Wireless Stick board. It also contains a beta of the library developed for the prototype.
- ### Diagrams and components


## Documentation of the developed library
The library is divided into two files:
```c
ArduDetectorLibrary.h
```
It defines the classes used, as well as their methods and attributes.
```c
ArduDetectorLibrary.cpp
```
Provides functionality to the methods defined in the header.

### Defined classes

#### Class SensorRGB

Abstracts the operation of the GY-31 color sensor where the RGB photodiodes must be turned on or off to detect a color.

- Attributes:


` 
int8_t _colorState
`
: Color currently detected

` 
int8_t _S0, _S1, _S2, _S3
`
: RGB photodiode cell activation pins

` 
int8_t _outputTCS
`
: Value obtained when activating or deactivating a photodiode combination

` 
int8_t _redLight, _greenLight, _blueLight
`
: They store the value of ` pulseIn(_outputTCS, LOW)`  corresponding to the colors red, green and blue.

`
enum Colors
`
: Defines the colors to be sampled with the sensor, subsequently storing their RGB values for detection.

- Main methods


`
SensorRGB(int8_t S0, int8_t S1, int8_t S2, int8_t S3, int8_t outputTCS)
`
: Contructor that defines the pins to which the Sensor is connected to the microcontroller board.

`
void InitSensorRGB()
`
: Initializes the pins and sets the output frequency.

`
bool ReadRGB()
`
:It is in charge of obtaining the RGB values from the sensor, storing these values in the attributes `_redLight, _greenLight, _blueLight`

`
void SetParametersColors(Colors color, int16_t avgRedLight, int16_t avgGreenLight, int16_t avgBlueLight)
`
: Allows to set the RGB values for a specific color, among its arguments it receives the name of the color to store (stored in the `enum Colors`), its red value, green value and blue value.

`
bool DetectColor()
`
: Compares the RGB values being detected by the sensor with those stored for a specified color, returning a `true` value if applicable.

`
int GetDetectedColor()
`
: Returns the value of the color currently being detected or the last one detected, returns COLORLESS if none has been detected.

#### Class Scanner
This class abstracts the operation that the prototype must have in general to scan the established colors and determine the height, time and speed with which the prototype detects a flood in the tributary where it is installed.
- Attributes

`uint8_t _colorsAssigned[13]`: Array that stores the sequence of colors to be detected by the sensor.

`uint8_t _colorAdded[13]`: Array that stores the colors detected by the sensor and is used to compare with the `_colorsAssigned` array in order to know if the color sequence is being followed.

`uint8_t _indexMain`: Indicates in which index of the `_colorsAssigned` array the colors are compared.

`uint8_t _presentColor`: Last registered color

`uint32_t  _elapsedTime`: Time elapsed between the detection of the last color and the new one.

`float _distanceTraveledY` : Stores the height that the prototype is traveling

`float _separationDistance`: Stores the physical separation distance between each color

`enum Colors`: List with the colors for the prototype

`uint8_t _blk, _bl, _gr, _yw, _org, _re`: Counters that store the number of times a set color is detected.

- Main methods

`Scanner(/* args */)`: Empty builder

`void CalculateElapsedTime(uint32_t currentTime)`:  Calculates the time that elapses between the detection of one color and another, it receives as argument `uint32_t currentTime` which corresponds to the instant in which a color is detected.

`uint32_t GetElapsedTime()`: It allows to obtain the time interval between the detection of two colors.

`bool AddColorDetected(uint8_t newColor)`: Adds a new color to the array `_colorAdded` by receiving as argument `uint8_t newColor` which is defined in `enum Colors`. Compare the newly added color with the established pattern to see if the physical color sequence of the prototype is being followed.

`uint8_t GetCountColor(uint8_t colorNumber)`: Returns the counter value for a color specified in argument `uint8_t colorNumber`

`uint8_t GetColorState()`: Returns the current color where the prototype is located.

`float GetDistanceTraveled()`: It calculates according to the color separation distance and the stored counters, the height at which the prototype is located and returns this value.

## MainCode

### Defining the sensor pins with the board
```c
#define S0 12
#define S1 13
#define S2 17
#define S3 23
#define outputTCS 39
```
### Creating a new object of type SensorRGB by sending it the previously set pins
```c
SensorRGB sensorRGB(S0, S1, S2, S3, outputTCS);
```

### Creating the Scanner object
```
Scanner scanner;
```

### Setup code with some pre-set values
```c
void setup() {
  sensorRGB.InitSensorRGB();
  sensorRGB.SetParametersColors(SensorRGB::RED, 231,555,423);
  sensorRGB.SetParametersColors(SensorRGB::ORANGE, 60,263,229);
  sensorRGB.SetParametersColors(SensorRGB::YELLOW, 129,200,300);
  sensorRGB.SetParametersColors(SensorRGB::GREEN, 500,336,354);
  sensorRGB.SetParametersColors(SensorRGB::BLUE, 520,327,190);
  sensorRGB.SetParametersColors(SensorRGB::BLACK, 700,743,571);
  scanner.SetSeparationDistance(0.15);
}
```

### Function void loop code
```c
void loop() {
    sensorRGB.ReadRGB();
    Serial.print("R:");
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::REDLIGHT));
    Serial.print("\t");
    
    Serial.print("V:");
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::GREENLIGHT));
    Serial.print("\t");
    
    Serial.print("A:");
    Serial.print(sensorRGB.GetValueRGB(SensorRGB::BLUELIGHT));
    Serial.println();

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
      }
    }
}
```

## Authors

- Edwin Rivera
- [@eugenio05](https://github.com/eugenio05)
- [@RonaldJair19](https://github.com/RonaldJair19)
