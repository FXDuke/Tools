

# Multipurpose Tool API for Arduino

### Features
* LED Class
* Button Class
* ShiftRegister Class

# Documentation

## LED : 36bit
#### LED(uint8_t)
- Sets the pin of the LED.
#### Brightness(uint16_t)
- Sets brightness for Analog Mode. (100 by default)
#### GetBrightness() -> uint8_t
- Returns the current brightness.
#### Update()
- Updates the LED, should be placed in loop function.
#### Attributes
- bool blink
- bool on (0 by default)
- bool blinkDelay
- bool mode (1 = Digital, 0 = Analog, 1 by default)

## Button : 28bit
#### Button(int)
- Sets the pin of the Button.
#### Update()
- Updates the button.
#### Attributes
- bool pressed
- bool held
- bool released 
- int16_t held_time

## ShiftRegister : 16bit
#### ShiftRegister(uint8_t,uint8_t,uint8_t)
- Sets the Clock, Latch, and Data pins.
#### Read(uint8_t)
- Reads the value stored at the (uint8_t) pin.
#### Append(uint8_t, bool)
- Appends the value at (uint8_t) to (bool).
#### Write(uint8_t)
- Writes (uint8_t) to storage.
#### Store()
- Stores saved data to memory.