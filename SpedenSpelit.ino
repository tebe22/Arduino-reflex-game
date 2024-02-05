#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

const int RESET_PIN = 12;
const int SHIFT_CLOCK_PIN = 11;
const int LATCH_CLOCK_PIN = 10;
const int OUT_ENABLE_PIN = 9;
const int SERIAL_INPUT_PIN = 8;

int randomNumbers[99];
int userNumbers[99];

volatile int nbrOfButtonPush;
volatile bool timeToCheckGameStatus = false;

volatile int kierros = 0;
volatile int nappi = 0;
volatile int cheat = 0;

void setup() {
  TIMSK1 = 0;
  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeTimer();
  stopTheGame();
  showResults(0);
}

void loop() {
  if (timeToCheckGameStatus == true) {
    checkGame();
    showResults(nappi);
    digitalWrite(OUT_ENABLE_PIN, LOW);
    timeToCheckGameStatus = false;
  }
}

ISR(PCINT2_vect) {
  // Tarkistaa napinpainallukset
  for (int i = firstPin; i <= lastPin; i++) {
    if (digitalRead(i) == LOW) {
      for (int x = 0; x < 50; x++) {
        delayMicroseconds(5000);
      }
      nbrOfButtonPush = i - 2;
      userNumbers[nappi] = nbrOfButtonPush;
      timeToCheckGameStatus = true;
    }
  }

  // Aloittaa pelin
  if (digitalRead(6) == LOW) {
    for (int x = 0; x < 50; x++) {
      delayMicroseconds(5000);
    }
    startTheGame();
  }

  // Cheattitila päälle
  if (digitalRead(2) == LOW && digitalRead(5) == LOW){
    for (int x = 0; x < 50; x++) {
      delayMicroseconds(5000);
    }
    timeToCheckGameStatus = false;
    cheatMode();
  }
}

ISR(TIMER1_COMPA_vect) {
  // Päivittää LED-valoja
  clearAllLeds();
  byte ledNumber;

  // Valitsee satunnainen LED-valo
  if (cheat == 1) {
    do {
      ledNumber = random(0, 2);
    } while (ledNumber == randomNumbers[kierros - 1]);
    
    setLed(ledNumber);
    randomNumbers[kierros] = ledNumber;
    kierros++;
  } else {
    do {
      ledNumber = random(0, 4);
    } while (ledNumber == randomNumbers[kierros - 1]);
    
    setLed(ledNumber);
    randomNumbers[kierros] = ledNumber;
    kierros++;
  }

  // Säätää ajastimen nopeutta joka kymmenes kierros
  if (kierros % 10 == 0) {
    OCR1A = OCR1A * 0.9;
  }
}

void initializeTimer(void) {
  TCCR1A = 0;
  TCCR1B = (1 << WGM12);
  TCCR1B |= (1 << CS12);
  OCR1A = 62499;
  TIMSK1 |= (1 << OCIE1A);
}

void checkGame() {
  if (randomNumbers[nappi] == userNumbers[nappi]) {
    nappi++;
  } else {
    setAllLeds();
    stopTheGame();
  }
}

void initializeGame() {
  for (int i = 0; i < 99; i++) {
    randomNumbers[i] = -1;
    userNumbers[i] = -1;
    kierros = 0;
  }
}

void startTheGame() {
  clearAllLeds();
  nappi = 0;
  
  digitalWrite(A2, HIGH);
  delay(200000);
  digitalWrite(A3, HIGH);
  delay(200000);
  digitalWrite(A4, HIGH);
  delay(200000);
  digitalWrite(A5, HIGH);
  delay(200000);
  clearAllLeds();
  delay(200000);
  initializeGame();
  TIMSK1 |= (1 << OCIE1A);
}

void stopTheGame() {
  initializeGame();
  initializeTimer();
  clearAllLeds();
  TIMSK1 = 0;
  cheat = 0;
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
  nappi = 0;
}

void cheatMode(){
  clearAllLeds();
  nappi = 0;
  cheat = 1;
  
  digitalWrite(A2, HIGH);
  delay(200000);
  digitalWrite(A3, HIGH);
  delay(200000);
  digitalWrite(A4, HIGH);
  delay(200000);
  digitalWrite(A5, HIGH);
  delay(200000);
  clearAllLeds();
  delay(200000);
  initializeGame();
  TIMSK1 |= (1 << OCIE1A);
}
