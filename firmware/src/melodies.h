#include "pitches.h"

int tonePin = 5;

int noteCount[] = { 1, 2, 3, 1, 2, 1 };

int melody[][4] =
{
    { NOTE_A5 }, // open
    { NOTE_A5, NOTE_E5 }, // open done
    { NOTE_C5, NOTE_E5, NOTE_G5 }, // set angle from serial
    { NOTE_A5 }, // start init
    { NOTE_A5, NOTE_A5 }, // init done
    { NOTE_C6 }, // received from serial
};

int noteDurations[][4] =
{
    { 8 },
    { 16, 8 },
    { 16, 16, 16 },
    { 2 },
    { 8, 8 },
    { 16 }
};

void playMelody(int variety)
{
    for (int thisNote = 0; thisNote < noteCount[variety]; thisNote++)
    {
        int noteDuration = 1000 / noteDurations[variety][thisNote];
        tone(tonePin, melody[variety][thisNote]);
        delay(noteDuration);
        noTone(tonePin);
        digitalWrite(tonePin, HIGH);
        int pauseBetweenNotes = noteDuration * 0.30;
        delay(pauseBetweenNotes);
    }
}
