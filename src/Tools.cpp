#include "Tools.h"
using namespace Tools;

// -- LED -- //

void LED::_updateTween()
{
    f_delta = min(f_delta + CLOCK_TIME, f_time);

    i32_brightness = i32_brightnessOrigin + i32_brightnessDelta * f_delta;

    tweening = (f_delta < f_time);

    if (!tweening)
    {
        i32_brightness = i32_brightnessGoal;
    }
}

int LED::GetBrightness()
{
    return i32_brightness;
}

bool LED::IsOn()
{
    return b_on;
}

bool LED::Mode()
{
    return b_pinType;
}

void LED::EnableDigital()
{
    b_pinType = 1;
}

void LED::EnableAnalog()
{
    b_pinType = 0;
}

void LED::Brightness(int power)
{
    i32_brightness = (power > 255) ? 255 : (power < 0) ? 0
                                                       : power;
}

void LED::SetPin(int pin)
{
    pinMode(pin, OUTPUT);
    i32_pin = pin;
}

void LED::Tween(int power, float time)
{
    power = (power > 255) ? 255 : (power < 0) ? 0
                                              : power;

    i32_brightnessOrigin = i32_brightness;
    i32_brightnessGoal = power;
    i32_brightnessDelta = (power - i32_brightness) / time;
    f_time = time;
    f_delta = 0.0;

    tweening = true;
}

void LED::BlinkOn(int delay)
{
    i32_blinkTime = max(CLOCK_TIME, delay);
    blink = 1;
}

void LED::BlinkOff()
{
    blink = 0;
}

void LED::On()
{
    b_on = 1;
}

void LED::Off()
{
    b_on = 0;
}

void LED::Update()
{

    bool on = b_on;

    if (tweening)
    {
        _updateTween();
    }

    if (blink)
    {

        if (i32_blinkCooldown > 0)
        {
            i32_blinkCooldown -= CLOCK_TIME_MS;
            return;
        }

        i32_blinkCooldown = i32_blinkTime;
        b_blinkOn = !b_blinkOn;
        on = b_blinkOn & on;
    }

    switch (b_pinType)
    {
    case 0:
        analogWrite(i32_pin, i32_brightness * on);
        break;
    case 1:
        digitalWrite(i32_pin, HIGH * on + LOW * (!on));
        break;
    }
}

// -- BUTTON -- //

void Button::Update()
{

    bool read = digitalRead(i32_pin);

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
        held_time = 0.0;
        released = 0;
        break;
    }
}

Button::Button(int pin)
{
    i32_pin = pin;
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
