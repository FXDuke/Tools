

# Multipurpose Tool API for Arduino

## Features
* LED Class
* Button Class

## Documentation

### LED
#### SetPin(int)
- Sets the pin of the LED.
#### EnableDigital()
- Sets output mode to Digital (Output mode is Digital by default)
#### EnableAnalog()
- Sets output mode to Analog. Allows for 1-255 brightness control for LEDs attached to ~pins.
#### Brightness(int)
- Sets brightness for Analog Mode. (100 by default)
#### Mode() -> bool
- Returns the current output mode. (1 for Digital, 0 for Analog)
#### GetBrightness() -> int
- Returns the current brightness.
#### Tween(int, float)
- Animates brightness linearly into (int) in (float) seconds.
#### BlinkOn(int)
- Enables blinking with a specified (int)ms delay.
#### BlinkOff()
- Disables blinking.
#### On()
- Enables LED
#### Off()
- Disables LED
#### Update()
- Updates the LED, should be placed in loop function.
#### Attributes
- bool tweening
- bool blink

### Button
#### Button(int)
- Sets the pin of the Button.
#### Update()
- Updates the button.
#### Attributes
- bool pressed
- bool held
- bool released 
- float held_time