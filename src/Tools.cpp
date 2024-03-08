#include "Tools.h"
using namespace Tools;

// -- LED -- //

void LED::Brightness(int16_t power)
{
    power = (power > 255) ? 255 : (power < 0) ? 0
                                              : power;
    i8_brightness = power;
}

uint8_t LED::GetBrightness()
{
    return i8_brightness;
}

void LED::Update()
{

    bool _on = on;

    if (blink)
    {

        if (i8_blinkCooldown > 0)
        {
            i8_blinkCooldown -= CLOCK_TIME;
            return;
        }

        i8_blinkCooldown = blinkDelay;
        b_blinkOn = !b_blinkOn;
        _on = b_blinkOn & _on;
    }

    switch (mode)
    {
    case 0:
        analogWrite(i8_pin, i8_brightness * _on);
        break;
    case 1:
        digitalWrite(i8_pin, HIGH * _on + LOW * (!_on));
        break;
    }
}

LED::LED(uint8_t pin)
{
    i8_pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

// -- BUTTON -- //

void Button::Update()
{

    bool read = digitalRead(i8_pin);

    switch (read)
    {
    case 0:
        held_time += CLOCK_TIME;
        if (!b_debounce)
        {
            pressed = 1;
            held = 1;
            b_debounce = 1;
            break;
        }
        pressed = 0;
        break;
    case 1:
        if (b_debounce)
        {
            released = 1;
            b_debounce = 0;
            held = 0;
            pressed = 0;
            break;
        }
        held_time = 0;
        released = 0;
        break;
    }
}

Button::Button(int pin)
{
    i8_pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

// -- SHIFT REGISTER -- //

bool ShiftRegister::Read(uint8_t position)
{
    return i8_storage & (1ULL << position);
}

void ShiftRegister::Append(uint8_t position, bool value)
{
    switch (value)
    {
    case 0:
        i8_storage &= ~(1ULL << position);
    case 1:
        i8_storage |= 1ULL << position;
    }
}

void ShiftRegister::Write(uint8_t num)
{
    i8_storage = num;
}

void ShiftRegister::Store()
{
    uint8_t read = i8_storage;
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(i8_clockPin, LOW);
        digitalWrite(i8_dataPin, HIGH * (read & 1));
        digitalWrite(i8_clockPin, HIGH);
        read >>= 1;
    }
    digitalWrite(i8_latchPin, LOW);
    digitalWrite(i8_latchPin, HIGH);
}

ShiftRegister::ShiftRegister(uint8_t clockPin, uint8_t latchPin, uint8_t dataPin)
{

    i8_clockPin = clockPin;
    i8_latchPin = latchPin;
    i8_dataPin = dataPin;

    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    digitalWrite(dataPin, LOW);
    
}
