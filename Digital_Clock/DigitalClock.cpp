/*
 * MyClass.cpp
 *
 * Created: 7/13/2016 3:15:11 PM
 * Author: psammand
 */
#include "DigitalClock.h"
#include "SevenSegmentDisplay.h"
#include "TimeValue.h"
#include "RTC.h"
#include "Wire.h"
#include "Keypad.h"

#define SYSTEM_STATE_RUNNING            0
#define SYSTEM_STATE_MINUTE_SELECTION   1
#define SYSTEM_STATE_HOUR_SELECTION     2
#define SYSTEM_STATE_TIME_CHANGED       3

#define VISIBLE_ALL                     0
#define VISIBLE_HOUR                    1
#define VISIBLE_MINUTE                  2

#define LDR_PIN                         A0

byte    system_state = SYSTEM_STATE_RUNNING;

void    rtc_callback(void);
void    set_minutes_visible(byte is_visible);
void    set_hours_visible(byte is_visible);
void    set_digit_visibility(byte visible_type);

void DigitalClock::ReadRtcTime(void)
{
    byte    second;
    byte    min;
    byte    hour;

    RTC.readDS3231time(&second, &min, &hour);

    TimeValue.SetTime(hour, min, second);
    SevenSegmentDisplay.SetTime(TimeValue);
}

void DigitalClock::InitModules(void)
{
    Serial.begin(115200);
    Wire.begin();

    TimeValue.init();
    SevenSegmentDisplay.init();
    RTC.init();
    Keypad.init();
}

void DigitalClock::ProcessKey()
{
    byte key = Keypad.GetPressedKey();

    if (key == KEY_NONE)
    {
        return;
    }

    if(key == KEY_MENU) {
        if(system_state == SYSTEM_STATE_RUNNING) {
            Serial.print("RUN=>HR\n");
            TimeValue.SetTime(0, 0, 0);
            SevenSegmentDisplay.SetTime(TimeValue);

            system_state = SYSTEM_STATE_HOUR_SELECTION;

            set_digit_visibility(VISIBLE_HOUR);
        }
        else if(system_state == SYSTEM_STATE_TIME_CHANGED) {
            Serial.print("TC=>HR\n");
            system_state = SYSTEM_STATE_HOUR_SELECTION;

            set_digit_visibility(VISIBLE_HOUR);
        }
        else if(system_state == SYSTEM_STATE_HOUR_SELECTION) {
            Serial.print("HR=>MIN\n");
            system_state = SYSTEM_STATE_MINUTE_SELECTION;

            set_digit_visibility(VISIBLE_MINUTE);
        }
        else if(system_state == SYSTEM_STATE_MINUTE_SELECTION) {
            Serial.print("MIN=>TC\n");
            system_state = SYSTEM_STATE_TIME_CHANGED;

            set_digit_visibility(VISIBLE_ALL);
        }
    }
    else if(key == KEY_UP) {
        if(system_state == SYSTEM_STATE_HOUR_SELECTION) {
            TimeValue.AddHour();
            SevenSegmentDisplay.SetTime(TimeValue);
        }
        else if(system_state == SYSTEM_STATE_MINUTE_SELECTION) {
            TimeValue.AddMinute();
            SevenSegmentDisplay.SetTime(TimeValue);
        }
        else if(system_state == SYSTEM_STATE_TIME_CHANGED) {
            system_state = SYSTEM_STATE_RUNNING;
        }
    }
}

void DigitalClock::ProcessLDR(void)
{
    int light = analogRead(LDR_PIN);
    //Serial.print("Light level ");
    //Serial.print(light);
    //Serial.println();

    if(light < 50)
    {
        SevenSegmentDisplay.SetIntensity(5);
    }
    else if (light < 100)
    {
        SevenSegmentDisplay.SetIntensity(50);
    }
    else if (light < 200)
    {
        SevenSegmentDisplay.SetIntensity(75);
    }
    else
    {
        SevenSegmentDisplay.SetIntensity(100);
    }
}

void DigitalClock::setup(void)
{
    InitModules();

    RTC.SetSqwCallback(rtc_callback);
    SevenSegmentDisplay.SwitchOffDisplay();

    SevenSegmentDisplay.SetIntensity(50);
    ReadRtcTime();

    interrupts();
}

void DigitalClock::loop(void)
{
    delay(500);
    ProcessKey();
    ProcessLDR();
}

void rtc_callback(void)
{
    if(system_state == SYSTEM_STATE_RUNNING) {
        TimeValue.AddSecond();
        SevenSegmentDisplay.SetTime(TimeValue);
    }
}

void set_minutes_visible(byte    is_visible)
{
    SevenSegmentDisplay.SetDigitVisibility(0, is_visible);
    SevenSegmentDisplay.SetDigitVisibility(1, is_visible);
}

void set_hours_visible(byte    is_visible)
{
    SevenSegmentDisplay.SetDigitVisibility(3, is_visible);
    SevenSegmentDisplay.SetDigitVisibility(4, is_visible);
}

void set_digit_visibility(byte    visible_type)
{
    if(visible_type == VISIBLE_ALL) {
        set_minutes_visible(true);
        set_hours_visible(true);
    }
    else if(visible_type == VISIBLE_MINUTE) {
        set_minutes_visible(true);
        set_hours_visible(false);
    }
    else {
        set_minutes_visible(false);
        set_hours_visible(true);
    }
}

DigitalClock    myClass;
