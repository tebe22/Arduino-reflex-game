#include "display.h"
// nimetään pinnit kuvaavasti vastaamaan kytkentää
const int RESET_PIN = 12; 
const int SHIFT_CLOCK_PIN = 11; 
const int LATCH_CLOCK_PIN = 10; 
const int OUT_ENABLE_PIN = 9; 
const int SERIAL_INPUT_PIN = 8; 

// taulukko  ohjaa mitkä segmentit jäävät pois päältä, jotta haluttu numero näkyy. (Common anode 7 segmentti, joten active low)
const uint8_t digitPatterns[10][8] = { 
  {0, 0, 0, 0, 0, 0, 1, 1}, //  0
  {1, 0, 0, 1, 1, 1, 1, 1}, //  1
  {0, 0, 1, 0, 0, 1, 0, 1}, //  2
  {0, 0, 0, 0, 1, 1, 0, 1}, //  3
  {1, 0, 0, 1, 1, 0, 0, 1}, //  4
  {0, 1, 0, 0, 1, 0, 0, 1}, //  5
  {0, 1, 0, 0, 0, 0, 0, 1}, //  6
  {0, 0, 0, 1, 1, 1, 1, 1}, //  7
  {0, 0, 0, 0, 0, 0, 0, 1}, //  8
  {0, 0, 0, 1, 1, 0, 0, 1}  //  9
};
//asetetaan pinnit outputeiksi ja haluttuihin lähtöarvoihin 74HC595 datasheetin mukaan
void initializeDisplay(void) {
  pinMode(RESET_PIN, OUTPUT);
  pinMode(SHIFT_CLOCK_PIN, OUTPUT);
  pinMode(LATCH_CLOCK_PIN, OUTPUT);
  pinMode(OUT_ENABLE_PIN, OUTPUT);
  pinMode(SERIAL_INPUT_PIN, OUTPUT);

  digitalWrite(RESET_PIN, HIGH); 
  digitalWrite(SHIFT_CLOCK_PIN, LOW); 
  digitalWrite(LATCH_CLOCK_PIN, LOW); 
  digitalWrite(OUT_ENABLE_PIN, LOW); 
  digitalWrite(SERIAL_INPUT_PIN, LOW); 
}

// funktio lähettää 8 bittiä shift registerille
void writeByte(uint8_t number, bool last) {
digitalWrite(LATCH_CLOCK_PIN,LOW);
// käy läpi bitit MSB:stä LSB:hen
for (int i = 7; i >= 0; i--) {
// syöttää inputtiin halutut bitit
digitalWrite(SERIAL_INPUT_PIN, digitPatterns[number][i]);
// shift clock pin highlle jotta shift registeri vastaanottaa bitit
    digitalWrite(SHIFT_CLOCK_PIN, HIGH); 
// shift clock pin lowille shiftauksen päätyttyä
    digitalWrite(SHIFT_CLOCK_PIN, LOW);
  }
// latch clock pin highlle, jotta data menee shift registerin outputtiin
  digitalWrite(LATCH_CLOCK_PIN, HIGH); 
// jos last on true output enable pin highlle jolloin näytössä näkyy uusi numero
  if (last) {
    
    digitalWrite(OUT_ENABLE_PIN, HIGH);
  }
}
// näyttää 2 haluttua numeroa kummallakin näytöllä
void writeHighAndLowNumber(uint8_t tens, uint8_t ones) {
 
 //kympit  näytölle ilman out puttia 
  writeByte(tens, false);
   // delay jotta uusi numero ei "välähtäisi" näytöllä
  // ykköset toiselle näytölle ja output päälle
  writeByte(ones, true);
  
}
/*käyttää saatua byte numeroa ja kutsuu writeHighAndLowNumber jotta kymmenet
ja ykköset saadaan näkymään eri näytöillä.
numer/10 kymmenille ja number % 10 ykkösille */
void showResults(byte number) {
  writeHighAndLowNumber(number / 10, number % 10); 
}