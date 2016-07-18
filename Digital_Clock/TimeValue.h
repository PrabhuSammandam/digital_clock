// TimeValue.h
#ifndef _TIMEVALUE_h
#define _TIMEVALUE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class   TimeValueClass
{
    protected:
        byte    _minutes;
        byte    _seconds;
        byte    _hours;

    public:
        TimeValueClass(void);

        void    init(void);

        byte    Seconds(void) const;
        void    Seconds(byte second);

        byte    Minutes(void) const;
        void    Minutes(byte minute);

        byte    Hours(void) const;
        void    Hours(byte val);

        void    AddSecond(void);
        void    AddMinute(void);
        void    AddHour(void);

        bool    IsValid(void);
        void    Reset(void);

        void    SetTime(byte hour, byte minute, byte second);
};

extern TimeValueClass   TimeValue;

#endif
