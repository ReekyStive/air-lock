#ifndef __MELDIES_H__
#define __MELDIES_H__

#include <Arduino.h>

#include "pitches.h"

const int tonePin = 5;

enum MelodyVariants {
    OPEN = 0,
    OPEN_DONE = 1,
    SET_ANGLE_FROM_SERIAL = 2,
    START_INIT = 3,
    INIT_DONE = 4,
    RECEIVED_FROM_SERIAL = 5
};

int melodyNoteCount[] = {1, 2, 3, 1, 2, 1};

int melody[][4] = {
    {NOTE_A5},                    // open
    {NOTE_A5, NOTE_E5},           // open done
    {NOTE_C5, NOTE_E5, NOTE_G5},  // set angle from serial
    {NOTE_A5},                    // start init
    {NOTE_A5, NOTE_A5},           // init done
    {NOTE_C6},                    // received from serial
};

int melodyNoteDurations[][4] = {{8}, {16, 8}, {16, 16, 16}, {2}, {8, 8}, {16}};

void playMelody(MelodyVariants melodyId) {
    if (melodyId < 0 || melodyId >= sizeof(melodyNoteCount)) {
        return;
    }

    for (int thisNote = 0; thisNote < melodyNoteCount[melodyId]; thisNote++) {
        int noteDuration = 1000 / melodyNoteDurations[melodyId][thisNote];
        tone(tonePin, melody[melodyId][thisNote]);
        delay(noteDuration);
        noTone(tonePin);
        digitalWrite(tonePin, HIGH);
        int pauseBetweenNotes = noteDuration * 0.30;
        delay(pauseBetweenNotes);
    }
}

#endif
