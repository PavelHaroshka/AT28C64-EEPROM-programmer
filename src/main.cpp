#include <Arduino.h>

#ifndef EEPROM_H
#include "EEPROM.h"
#endif

#ifndef HEX_DECODER_H
#include "hex_decoder.h"
#endif

#define MONITOR_SPEED 115200

EEPROM eeprom = {
  DATA_PINS : {16, 17, 5, 18, 32, 33, 25, 26},
  SHIFT_DATA_PIN : 13,
  SHIFT_CLK_PIN : 14,
  SHIFT_LATCH_PIN : 12,
  WRITE_ENABLE_PIN : 27,
  adressLinesAmount : 8192,
};

void setup()
{
  Serial.begin(MONITOR_SPEED);
  ProgramHexDecoder(&eeprom);
}

void loop()
{
}
