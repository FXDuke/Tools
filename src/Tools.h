#include <Arduino.h>
#pragma once

namespace Tools
{

    extern int CLOCK_TIME;

    class LED
    {

    private:
        // Basic
        uint8_t i8_pin = 0;

        uint8_t i8_blinkCooldown = 0;
        bool b_blinkOn = 0; // Flips on and off on a delay, doenst set b_on;

        uint8_t i8_brightness = 100;

    public:
        bool mode = 1;
        bool on = 0;
        bool blink = 0;
        uint16_t blinkDelay = 100;

        uint8_t GetBrightness();
        void Brightness(int16_t);
        void Update();
        LED(uint8_t);
    };

    class Button
    {

    private:
        uint8_t i8_pin = 0;
        bool b_debounce = 0;

    public:
        bool pressed = 0;
        bool released = 0;
        bool held = 0;

        uint16_t held_time = 0;

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