#include "buttons.h"




void initButtonsAndButtonInterrupts(void)
{
   
  pinMode(2, INPUT_PULLUP); //Asetetaan pinnit 2-6 sisääntulo pinneiksi ja aktivoidaan ylösvetovastus
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  PCICR |= (1 << PCIE2);  // Alustetaan Pin Change Interupt Control Register 2
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22); // Asettaa PCMSK2 rekisterin päälle halutuille pinneille


  
}