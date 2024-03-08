#include "Tools.h"
using namespace Tools;

const int Button1Pin = 2;
const int Button2Pin = 4;
const int LEDPin = 3;

Button Button1(Button1Pin);
Button Button2(Button2Pin);
LED led;

void setup()
{

  led.SetPin(LEDPin);
  led.On();

}


void loop()
{

  Button1.Update();
  Button2.Update();

  if (Button1.released)
  {
    led.On();
  }

  if (Button2.released)
  {
    led.Off();
  }

  led.Update();
  delay(CLOCK_TIME_MS);
  
}