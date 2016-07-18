/*
 * MyClass.h
 *
 * Created: 7/13/2016 3:15:11 PM
 * Author: psammand
 */
#ifndef _MYCLASS_h
#define _MYCLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class   DigitalClock
{
    private:
        void    ReadRtcTime(void);
        void    InitModules(void);
        void    ProcessKey(void);
        void    ProcessLDR(void);
    public:
        void    setup(void);
        void    loop(void);
};

extern DigitalClock myClass;

#endif
