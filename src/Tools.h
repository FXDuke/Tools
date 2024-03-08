#include <Arduino.h>
#pragma once

namespace Tools
{

    const float CLOCK_TIME = 0.01;
    const float CLOCK_TIME_MS = 10;

    class LED
    {

    private:
        // Basic
        int i32_pin = 0;

        int i32_brightness = 100; // Only active with analog output

        bool b_pinType = 1; // 1 = Digital, 0 = Analog

        bool b_on = 0;

        int i32_blinkTime = CLOCK_TIME_MS;
        int i32_blinkCooldown = 0;
        bool b_blinkOn = 0; // Flips on and off on a delay, doenst set b_on;

        // Tween

        int i32_brightnessDelta;
        int i32_brightnessGoal;
        int i32_brightnessOrigin = 100;
        float f_delta = 0.0;
        float f_time = 0.0;

        void _updateTween();

    public:
        bool tweening = 0;
        bool blink = 0;

        int GetBrightness();
        bool Mode();
        bool IsOn();
        void EnableDigital();
        void EnableAnalog();
        void Brightness(int);
        void SetPin(int);
        void Tween(int, float);
        void BlinkOn(int);
        void BlinkOff();
        void On();
        void Off();
        void Update();
    };

    class Button
    {

    private:
        int i32_pin = 0;
        bool b_debounce = 0;

    public:
        bool pressed = 0;
        bool released = 0;
        bool held = 0;

        float held_time = 0.0;

        void Update();

        Button(int);
    };

    class ShiftRegister
    {

    private:
        uint8_t i8_clockPin;
        uint8_t i8_latchPin;
        uint8_t i8_dataPin;

        uint8_t i8_storage = 0;

    public:
        bool Read(uint8_t);
        void Append(uint8_t, bool);
        void Write(uint8_t);
        void Store();
        ShiftRegister(uint8_t, uint8_t, uint8_t);
    };

};