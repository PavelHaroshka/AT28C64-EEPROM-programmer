#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>

struct EEPROM
{
  uint8_t DATA_PINS[8];
  uint8_t SHIFT_DATA_PIN;
  uint8_t SHIFT_CLK_PIN;
  uint8_t SHIFT_LATCH_PIN;
  uint8_t WRITE_ENABLE_PIN;
  uint16_t adressLinesAmount;
};

void init(EEPROM *self);
void setAddress(EEPROM *self, uint16_t address, bool outputEnable);
uint8_t read(EEPROM *self, uint16_t address);
void print(EEPROM *self, int size);
void write(EEPROM *self, int address, byte data);
void erase(EEPROM *self);

#endif