#include "Tools.h"
using namespace Tools;

const int Button1Pin = 2;
const int LEDPin = 3;

Button Button1(Button1Pin);
LED led;

void setup()
{

  led.SetPin(LEDPin);
  led.On();

}


void loop()
{

  Button1.Update();

  if (Button1.released)
  {

    switch(led.blink)
    {
      case 1:
        led.BlinkOff();
        break;
      case 0:
        led.BlinkOn(250);
        break;
    }
    
  }

  led.Update();
  delay(CLOCK_TIME_MS);

}