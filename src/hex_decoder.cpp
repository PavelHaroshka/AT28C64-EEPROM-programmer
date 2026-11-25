#ifndef EEPROM_H
#include "EEPROM.h"
#endif

void ProgramHexDecoder(EEPROM *eeprom)
{
    byte digits[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b};
    uint16_t offset = 256;

    init(eeprom);

    Serial.println("Programming EEPROM:");
    Serial.print("Writing positive numbers [0] - [255] ");

    for (int value = 0; value < offset; value++)
    {
        if (value % 64 == 0)
        {
            Serial.print(".");
        }

        uint8_t ones = digits[value % 10];
        uint8_t tens = digits[(value / 10) % 10];
        uint8_t hundreds = digits[(value / 100) % 10];

        write(eeprom, value, ones);
        write(eeprom, value + offset, tens);
        write(eeprom, value + (offset * 2), hundreds);
        write(eeprom, value + (offset * 3), 0x00);
    }
    Serial.println(" done");

    Serial.print("Writing twos compliment [-128] - [128] ");
    for (int value = -128; value < 128; value++)
    {
        uint8_t sign;
        uint16_t absValue = abs(value);
        int byteValue = byte(value);

        if (value > 0) {
            sign = 0x01;
        } else {
            sign = 0;
        }

        if (absValue % 64 == 0)
        {
            Serial.print(".");
        }

        uint8_t ones = digits[absValue % 10];
        uint8_t tens = digits[(absValue / 10) % 10];
        uint8_t hundreds = digits[(absValue / 100) % 10];

        write(eeprom, byteValue + (offset * 4), ones);
        write(eeprom, byteValue + (offset * 5), tens);
        write(eeprom, byteValue + (offset * 6), hundreds);
        write(eeprom, byteValue + (offset * 7), sign);
    }
    Serial.println(" done");
}