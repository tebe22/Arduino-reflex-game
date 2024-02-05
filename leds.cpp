#include "leds.h"

void initializeLeds() {
    // Asetetaan jokaisen LEDin pinni OUTPUT-tilaan
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
}

void setLed(byte ledNumber) {
    // Käytetään switch-lausetta määrittämään, mikä LED laitetaan päälle 
    switch (ledNumber) {
        case 0:
            digitalWrite(A2, HIGH);  
            break;
        case 1:
            digitalWrite(A3, HIGH);  
            break;
        case 2:
            digitalWrite(A4, HIGH);  
            break;
        case 3:
            digitalWrite(A5, HIGH);  
            break;
    }
}

// Funktio sammuttaa kaikki LEDit
void clearAllLeds() {
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
}

// Funktio laittaa kaikki LEDit päälle
void setAllLeds() {
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A5, HIGH);
}
