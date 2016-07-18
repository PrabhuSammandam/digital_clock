// RTC.h
#ifndef _RTC_h
#define _RTC_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
enum Ds3231SqwPinMode
{
    DS3231_OFF              = 0x01,
    DS3231_SquareWave1Hz    = 0x00,
    DS3231_SquareWave1kHz   = 0x08,
    DS3231_SquareWave4kHz   = 0x10,
    DS3231_SquareWave8kHz   = 0x18
};

typedef void (*rtc_sqw_cb)(void);

class   RTCClass
{
    protected:
        rtc_sqw_cb _rtc_sqw_cb;

    public:
        RTCClass();
        void    init(void);
        void    setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
        void    readDS3231time(byte* second, byte* minute, byte* hour, byte* dayOfWeek, byte* dayOfMonth, byte* month, byte* year);
        void    readDS3231time(byte* second, byte* minute, byte* hour);
        void    writeSqwPinMode(Ds3231SqwPinMode mode);
        void    displayTime(void);
        void    SetSqwCallback(rtc_sqw_cb cb);
};

extern RTCClass RTC;

#endif
