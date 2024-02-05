#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>
const byte firstPin = 2; // First PinChangeInterrupt on D-bus
const byte lastPin =  5; // Last PinChangeInterrupt on D-bus


void initButtonsAndButtonInterrupts(void);

#endif