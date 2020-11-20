#include "pitches.h"

int tonePin = 5;

int noteCount[3] =
{
    1, 2, 1
};

int melody[3][4] =
{
    {
        NOTE_C5
    },
    {
        NOTE_C5, NOTE_G4
    },
    {
        NOTE_A4, NOTE_A4, NOTE_A4
    }
};

int noteDurations[3][4] =
{
    {
        8
    },
    {
        8, 4
    },
    {
        8, 8, 8
    }
};

void playMelody(int variety)
{
    for (int thisNote = 0; thisNote < noteCount[variety]; thisNote++)
    {
        int noteDuration = 1000 / noteDurations[variety][thisNote];
        tone(tonePin, melody[variety][thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(tonePin);
    }
}
