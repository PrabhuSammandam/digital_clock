//
//
//
#include "Keypad.h"

#define MENU_PIN    8
#define UP_PIN    7

 KeypadClass::KeypadClass()
{

}

void KeypadClass::init(void)
{
    pinMode(MENU_PIN, INPUT_PULLUP);
    pinMode(UP_PIN, INPUT_PULLUP);
}

byte KeypadClass::GetPressedKey(void)
{
    if(digitalRead(MENU_PIN) == LOW)
    {
        delay(150);

        if (digitalRead(MENU_PIN) == LOW)
        {
            return KEY_MENU;
        }
    }

    if(digitalRead(UP_PIN) == LOW)
    {
        delay(150);

        if (digitalRead(UP_PIN) == LOW)
        {
            return KEY_UP;
        }
    }

    return KEY_NONE;
}

KeypadClass   Keypad;
