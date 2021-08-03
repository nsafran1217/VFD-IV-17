/*
Library for IV-17 and IV-4 Sixteen segment alphanumeric soviet VFD tube
Nathan Safran - 8/2/2021
*/

#include "Arduino.h"
#include "IV17.h"

IV17::IV17(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t blankPin)
{
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT); 
    pinMode(latchPin, OUTPUT); 
    pinMode(blankPin, OUTPUT);
    _dataPin = dataPin;
    _clockPin = clockPin;
    _latchPin = latchPin;
    _blankPin = blankPin;

}
void IV17::shiftOutCharNoLatch(char c)
{   
    shiftOut20Bits(MSBFIRST, _asciiLookupIV17[c] | _gridPin); 

}
void IV17::shiftOutChar(char c)
{
    digitalWrite(_latchPin, LOW);
    shiftOut20Bits(MSBFIRST, _asciiLookupIV17[c] | _gridPin); 
    digitalWrite(_latchPin, HIGH);

}
void IV17::shiftOutString(String s) {
    digitalWrite(_latchPin, LOW);
    for (int i = s.length(); i > 0; i--)
    {
        shiftOutCharNoLatch(s[i-1]);
    }
    
    digitalWrite(_latchPin, HIGH);
}
void IV17::scrollString(String s, uint8_t direction, uint8_t numOfTubes){
    _scrollingString = s;
 

}

void IV17::shiftOut20Bits(uint8_t bitOrder, uint32_t val)
{
    uint8_t i;
    for (i = 0; i < 20; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(_dataPin, !!(val & (1ul << i)));   //1ul tells it to use an unisgned long. If we use just 1, its only 16 bits
        else    
            digitalWrite(_dataPin, !!(val & (1ul << (19 - i))));

        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);        
    }
}
