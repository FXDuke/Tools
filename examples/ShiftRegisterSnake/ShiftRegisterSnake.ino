
#include "Tools.h"
using namespace Tools;

int Tools::CLOCK_TIME = 50;

ShiftRegister Register(6,5,4);

void setup()
{

  Register.Write(0);
  Register.Store();

}


int snake = 0b11110000;

void loop()
{

  bool add = snake&0x80;
  snake<<=1;
  snake+=add;

  Register.Write(snake);
  Register.Store();

  delay(CLOCK_TIME);

}