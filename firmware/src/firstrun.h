#ifndef __FIRSTRUN_H__
#define __FIRSTRUN_H__

#include <Arduino.h>
#include <EEPROM.h>

#include "password.h"

bool isFirstRun() { return !EEPROM.read(6); }

void flagFirstRun() { EEPROM.write(6, 1); }

#endif
