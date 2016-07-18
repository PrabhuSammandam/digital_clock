// Keypad.h
#ifndef _KEYPAD_h
#define _KEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define KEY_MENU    0
#define KEY_UP    1
#define KEY_NONE    0xFF

class   KeypadClass
{
    protected:

    public:
        KeypadClass(void);
        void    init(void);
        byte    GetPressedKey(void);
};

extern KeypadClass  Keypad;

#endif
