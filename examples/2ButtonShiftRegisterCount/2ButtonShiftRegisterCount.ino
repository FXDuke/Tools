#include "Tools.h"
using namespace Tools;

uint8_t count = 0;

Button Reset(2);
Button Add(3);

ShiftRegister Register(6,5,4);

void setup() {

}

void loop() {

  Reset.Update();
  Add.Update();

  if (Reset.released)
  {
    count = 0;
  }

  if (Add.released)
  {
    count += 1;

    Register.Write(count);
    Register.Store();
  }

  delay(CLOCK_TIME_MS);
}
