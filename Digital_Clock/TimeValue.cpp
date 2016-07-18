//
//
//
#include "TimeValue.h"

void TimeValueClass::init(void)
{
}

TimeValueClass::TimeValueClass(void)
{
    _seconds = 0;
    _minutes = 0;
    _hours = 0;
}

byte TimeValueClass::Seconds(void) const
{
    return _seconds;
}

void TimeValueClass::Seconds(byte    second)
{
    _seconds = second;
}

byte TimeValueClass::Minutes(void) const
{
    return _minutes;
}

void TimeValueClass::Minutes(byte    minute)
{
    _minutes = minute;
}

void TimeValueClass::AddMinute(void)
{
    if(_minutes == 59) {
        _minutes = 0;
        AddHour();
    }
    else {
        _minutes++;
    }
}

void TimeValueClass::AddHour(void)
{
    _hours = (_hours == 12) ? 0 : _hours + 1;
}

void TimeValueClass::AddSecond(void)
{
    if(_seconds == 59) {
        _seconds = 0;
        AddMinute();
    }
    else {
        _seconds++;
    }
}

bool TimeValueClass::IsValid(void)
{
    if((_minutes > 0) || (_seconds > 0)) {
        return true;
    }

    return false;
}

void TimeValueClass::Reset(void)
{
    _minutes = 0;
    _seconds = 0;
}

byte TimeValueClass::Hours(void) const
{
    return _hours;
}

void TimeValueClass::Hours(byte    val)
{
    _hours = val;
}

void TimeValueClass::SetTime(byte    hour,
                             byte    minute,
                             byte    second)
{
    if (hour >= 12)
    {
        _hours = hour - 12;
    }
    else
    {
        _hours = hour;
    }
    _minutes = minute;
    _seconds = second;
}

TimeValueClass  TimeValue;
