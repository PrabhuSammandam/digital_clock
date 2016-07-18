//
//
//
#include "SevenSegmentDisplay.h"
#include "RTC.h"

#define BCD_SEG_A       6 // uC pin 12
#define BCD_SEG_B       3 // uC pin 5
#define BCD_SEG_C       4 // uC pin 6
#define BCD_SEG_D       5 // uC pin 11

#define DIGIT_0         12
#define DIGIT_1         11
#define DIGIT_2         10

#define LED_INTENSITY   9

byte    _digit_0[5] = { 0, 1, 0, 1, 0 };
byte    _digit_1[5] = { 0, 0, 1, 1, 0 };
byte    _digit_2[5] = { 0, 0, 0, 0, 1 };
byte    _bcd_seg_a[10] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
byte    _bcd_seg_b[10] = { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 };
byte    _bcd_seg_c[10] = { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0 };
byte    _bcd_seg_d[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
byte    _digit_visible[5];

SevenSegmentDisplayClass::SevenSegmentDisplayClass(void)
{
    _current_digit = 0;

    for(byte i = 0; i < 5; i++) {
        _digit_values[i] = 0;
        _digit_visible[i] = 1;
    }
}

void SevenSegmentDisplayClass::init(void)
{
    pinMode(BCD_SEG_A, OUTPUT);
    pinMode(BCD_SEG_B, OUTPUT);
    pinMode(BCD_SEG_C, OUTPUT);
    pinMode(BCD_SEG_D, OUTPUT);

    pinMode(DIGIT_0, OUTPUT);
    pinMode(DIGIT_1, OUTPUT);
    pinMode(DIGIT_2, OUTPUT);

    pinMode(LED_INTENSITY, OUTPUT);

    digitalWrite(LED_INTENSITY, HIGH);

    _digit_values[2] = 2;

    InitDisplayTimer();
}

void SevenSegmentDisplayClass::SetDigitValue(byte    digitIndex,
                                             byte    digitValue)
{
    _digit_values[digitIndex] = digitValue;
}

/* set the current display digit. */
void SevenSegmentDisplayClass::SelectDisplayDigit(byte    displayDigit)
{
    digitalWrite(DIGIT_0, _digit_0[displayDigit]);
    digitalWrite(DIGIT_1, _digit_1[displayDigit]);
    digitalWrite(DIGIT_2, _digit_2[displayDigit]);
}

void SevenSegmentDisplayClass::DisplayDigitValue(byte    displayValue)
{
    digitalWrite(BCD_SEG_A, _bcd_seg_a[displayValue]);
    digitalWrite(BCD_SEG_B, _bcd_seg_b[displayValue]);
    digitalWrite(BCD_SEG_C, _bcd_seg_c[displayValue]);
    digitalWrite(BCD_SEG_D, _bcd_seg_d[displayValue]);
}

void SevenSegmentDisplayClass::RefreshDisplay(void)
{
    SwitchOffDisplay();
    delay(1);

    if (_digit_visible[_current_digit])
    {
        SelectDisplayDigit(_current_digit);
        DisplayDigitValue(_digit_values[_current_digit]);
    }

    if(_current_digit == 4) {
        _current_digit = 0;
    }
    else {
        _current_digit++;
    }
}

void SevenSegmentDisplayClass::SetTime(TimeValueClass&     timeValue)
{
    SetDigitValue(0, timeValue.Minutes() % 10);
    SetDigitValue(1, timeValue.Minutes() / 10);
    SetDigitValue(2, ((timeValue.Seconds() % 2) == 0) ? 2 : 1);
    SetDigitValue(3, timeValue.Hours() % 10);
    SetDigitValue(4, timeValue.Hours() / 10);
}

void SevenSegmentDisplayClass::SetIntensity(unsigned short  intensity)
{
    analogWrite(LED_INTENSITY, intensity);
}

void SevenSegmentDisplayClass::SwitchOffDisplay(void)
{
    digitalWrite(BCD_SEG_A, LOW);
    digitalWrite(BCD_SEG_B, HIGH);
    digitalWrite(BCD_SEG_C, LOW);
    digitalWrite(BCD_SEG_D, HIGH);

    digitalWrite(DIGIT_0, HIGH);
    digitalWrite(DIGIT_1, HIGH);
    digitalWrite(DIGIT_2, HIGH);
}

void SevenSegmentDisplayClass::SetDigitVisibility(byte digit, byte is_visible)
{
    _digit_visible[digit] = is_visible;
}

void SevenSegmentDisplayClass::InitDisplayTimer(void)
{
    TCNT2 = 0;              // Initialize the Timer/Counter Register to 0
    TIMSK2 |= (1 << TOIE2); //enable timer0 overflow interrupt
    TCCR2B |= (1 << CS22) | (1 << CS20);    //pre-scale by 128
}

SevenSegmentDisplayClass    SevenSegmentDisplay;

ISR(TIMER2_OVF_vect)
{
    SevenSegmentDisplay.RefreshDisplay();
}
