#ifndef EEPROM_H
#include "EEPROM.h"
#endif

void init(EEPROM *self)
{
  pinMode(self->SHIFT_DATA_PIN, OUTPUT);
  pinMode(self->SHIFT_CLK_PIN, OUTPUT);
  pinMode(self->SHIFT_LATCH_PIN, OUTPUT);
  digitalWrite(self->WRITE_ENABLE_PIN, HIGH);
  pinMode(self->WRITE_ENABLE_PIN, OUTPUT);
}

void setAddress(EEPROM *self, uint16_t address, bool outputEnable)
{
  shiftOut(
      self->SHIFT_DATA_PIN,
      self->SHIFT_CLK_PIN,
      MSBFIRST,
      (address >> 8) | (outputEnable ? 0x00 : 0x80));

  shiftOut(
      self->SHIFT_DATA_PIN,
      self->SHIFT_CLK_PIN,
      MSBFIRST,
      address & 0xFF);

  digitalWrite(self->SHIFT_LATCH_PIN, LOW);
  digitalWrite(self->SHIFT_LATCH_PIN, HIGH);
  digitalWrite(self->SHIFT_LATCH_PIN, LOW);
}

// Read one byte from EEPROM
uint8_t read(EEPROM *self, uint16_t address)
{
  for (int pin = 0; pin <= 7; pin++)
  {
    pinMode(self->DATA_PINS[pin], INPUT);
  }
  setAddress(self, address, true);

  byte data = 0;
  for (int pin = 7; pin >= 0; pin--)
  {
    data = (data << 1) + digitalRead(self->DATA_PINS[pin]);
  }
  return data;
}

// Print EEPROM values
void print(EEPROM *self, int size)
{
  Serial.print("EEPROM content: \n");
  for (int base = 0; base <= size; base += 16)
  {
    byte data[16];
    for (int offset = 0; offset <= 15; offset++)
    {
      data[offset] = read(self, base + offset);
    }

    Serial.printf("%03x:", base);
    for (int i = 0; i <= 15; i++)
    {
      if (i == 9)
      {
        Serial.printf("\t");
      }
      Serial.printf("%02x ", data[i]);
    }
    Serial.printf("\n");
  }
}

// Write to EEPROM
void write(EEPROM *self, int address, byte data)
{
  setAddress(self, address, false);

  for (int pin = 0; pin <= 7; pin++)
  {
    pinMode(self->DATA_PINS[pin], OUTPUT);
  }

  for (int pin = 0; pin <= 7; pin++)
  {
    digitalWrite(self->DATA_PINS[pin], data & 1);
    data = data >> 1;
  }

  digitalWrite(self->WRITE_ENABLE_PIN, LOW);
  delayMicroseconds(1);
  digitalWrite(self->WRITE_ENABLE_PIN, HIGH);
  delay(10);
}

// Erase EEPROM
void erase(EEPROM *self)
{
  Serial.print("Erasing EEPROM");
  for (int address = 0; address <= self->adressLinesAmount; address++)
  {
    write(self, address, 0xff);

    if (address % 512 == 0)
    {
      Serial.print(".");
    }
  }
  Serial.println(" done");
}