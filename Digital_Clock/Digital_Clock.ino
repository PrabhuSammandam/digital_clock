#include "Keypad.h"
#include "RTC.h"
#include "RTC.h"
#include <Wire.h>
#include "TimeValue.h"
#include "SevenSegmentDisplay.h"
/*
 * Digital_Clock.ino
 *
 * Created: 7/13/2016 3:15:11 PM
 * Author: psammand
 */ 

#include "DigitalClock.h"

void setup()
{
	myClass.setup();
}

void loop()
{
	myClass.loop();
}
