//
//
//
#include "RTC.h"
#include "Wire.h"

#define SQW_PIN 2

#define DS3231_I2C_ADDRESS  0x68
#define DS3231_CONTROL      0x0E

// Convert normal decimal numbers to binary coded decimal
static byte decToBcd(byte    val)
{
    return ((val / 10 * 16) + (val % 10));
}

// Convert binary coded decimal to normal decimal numbers
static byte bcdToDec(byte    val)
{
    return ((val / 16 * 10) + (val % 16));
}

static uint8_t read_i2c_register(uint8_t addr,
                                 uint8_t reg)
{
    Wire.beginTransmission(addr);
    Wire.write((byte) reg);
    Wire.endTransmission();

    Wire.requestFrom(addr, (byte) 1);
    return Wire.read();
}

static void write_i2c_register(uint8_t addr,
                               uint8_t reg,
                               uint8_t val)
{
    Wire.beginTransmission(addr);
    Wire.write((byte) reg);
    Wire.write((byte) val);
    Wire.endTransmission();
}

void RTCClass::writeSqwPinMode(Ds3231SqwPinMode    mode)
{
    uint8_t ctrl;
    ctrl = read_i2c_register(DS3231_I2C_ADDRESS, DS3231_CONTROL);

    ctrl &= ~0x04;                      // turn off INTCON
    ctrl &= ~0x18;                      // set freq bits to 0

    if(mode == DS3231_OFF) {
        ctrl |= 0x04;                   // turn on INTCN
    }
    else {
        ctrl |= mode;
    }

    write_i2c_register(DS3231_I2C_ADDRESS, DS3231_CONTROL, ctrl);
}

void RTCClass::setDS3231time(byte    second,
                             byte    minute,
                             byte    hour,
                             byte    dayOfWeek,
                             byte    dayOfMonth,
                             byte    month,
                             byte    year)
{
    // sets time and date data to DS3231
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0);                      // set next input to start at the seconds register
    Wire.write(decToBcd(second));       // set seconds
    Wire.write(decToBcd(minute));       // set minutes
    Wire.write(decToBcd(hour));         // set hours
    Wire.write(decToBcd(dayOfWeek));    // set day of week (1=Sunday, 7=Saturday)
    Wire.write(decToBcd(dayOfMonth));   // set date (1 to 31)
    Wire.write(decToBcd(month));        // set month
    Wire.write(decToBcd(year));         // set year (0 to 99)
    Wire.endTransmission();
}

void RTCClass::readDS3231time(byte*   second,
                              byte*   minute,
                              byte*   hour)
{
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0);                      // set DS3231 register pointer to 00h
    Wire.endTransmission();
    Wire.requestFrom(DS3231_I2C_ADDRESS, 7);

    *second = bcdToDec(Wire.read() & 0x7f);
    *minute = bcdToDec(Wire.read());
    *hour = bcdToDec(Wire.read() & 0x3f);
}

void RTCClass::readDS3231time(byte*   second,
                              byte*   minute,
                              byte*   hour,
                              byte*   dayOfWeek,
                              byte*   dayOfMonth,
                              byte*   month,
                              byte*   year)
{
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0);                      // set DS3231 register pointer to 00h
    Wire.endTransmission();
    Wire.requestFrom(DS3231_I2C_ADDRESS, 7);

    // request seven bytes of data from DS3231 starting from register 00h
    *second = bcdToDec(Wire.read() & 0x7f);
    *minute = bcdToDec(Wire.read());
    *hour = bcdToDec(Wire.read() & 0x3f);
    *dayOfWeek = bcdToDec(Wire.read());
    *dayOfMonth = bcdToDec(Wire.read());
    *month = bcdToDec(Wire.read());
    *year = bcdToDec(Wire.read());
}

void RTCClass::displayTime(void)
{
    byte    second;
    byte    minute;
    byte    hour;

    // retrieve data from DS3231
    readDS3231time(&second, &minute, &hour);

    // send it to the serial monitor
    Serial.print(hour, DEC);

    // convert the byte variable to a decimal number when displayed
    Serial.print(":");
    if(minute < 10) {
        Serial.print("0");
    }

    Serial.print(minute, DEC);
    Serial.print(":");
    if(second < 10) {
        Serial.print("0");
    }

    Serial.print(second, DEC);
    Serial.println();
}

void RTCClass::SetSqwCallback(rtc_sqw_cb cb)
{
    if(!_rtc_sqw_cb)
    {
        detachInterrupt(digitalPinToInterrupt(SQW_PIN));
    }

    _rtc_sqw_cb = cb;

    attachInterrupt(digitalPinToInterrupt(SQW_PIN), cb, RISING);
}

 RTCClass::RTCClass()
{
    _rtc_sqw_cb = 0;
}


void RTCClass::init(void)
{
    pinMode(SQW_PIN, INPUT_PULLUP);

    writeSqwPinMode(DS3231_SquareWave1Hz);
}

RTCClass    RTC;