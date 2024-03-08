
#include "Tools.h"
using namespace Tools;

int Tools::CLOCK_TIME = 10;

Button Increase(7);
Button Decrease(8);
Button Super(9);

LED Digital(2);
LED Indicator(3);

ShiftRegister Register(6,5,4);

void setup()
{

  Register.Write(0);
  Register.Store();

  Digital.on = 0;

  Indicator.mode = 0;
  Indicator.on = 1;
  Indicator.blinkDelay = 50;
}

void loop()
{

  Increase.Update();
  Decrease.Update();
  Super.Update();

  switch(Super.held)
  {
    case 1:
      if (Increase.pressed)
      {
        if (Indicator.blink)
        {
          Indicator.blink = 0;
          break;
        }
        Indicator.blink = 1;
        
      }
      if (Decrease.pressed)
      {
        if (Indicator.mode == 1)
        {
          Indicator.mode = 0;
          Digital.on = 0;
        } else {
          Indicator.mode = 1;
          Digital.on = 1;
        }
      }
      break;
    case 0:
      if (Increase.pressed || Increase.held_time > 500)
      {
        Indicator.Brightness(Indicator.GetBrightness()+5);
      }
      if (Decrease.pressed || Decrease.held_time > 500)
      {
        Indicator.Brightness(Indicator.GetBrightness()-5);
      }
      break;
  }

  Register.Write(Indicator.GetBrightness());
  Register.Store();

  Indicator.Update();
  Digital.Update();

  delay(CLOCK_TIME);

}