// SevenSegmentDisplay.h

#ifndef _SEVENSEGMENTDISPLAY_h
#define _SEVENSEGMENTDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TimeValue.h"

class SevenSegmentDisplayClass
{
 protected:
    byte _current_digit;
    byte _digit_values[5];

 public:
    SevenSegmentDisplayClass();

	void init();
    void SetDigitValue(byte digitIndex, byte digitValue);
    void SelectDisplayDigit(byte displayDigit);
    void DisplayDigitValue(byte displayValue);
    void RefreshDisplay();
    void InitDisplayTimer();
    void SetTime(TimeValueClass& timeValue);
    void SetIntensity(unsigned short intensity);
    void SwitchOffDisplay();
    void SetDigitVisibility(byte digit, byte is_visible);
};

extern SevenSegmentDisplayClass SevenSegmentDisplay;

#endif

