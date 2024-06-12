/*
 * L298 - interfacing
 * 
 * 
 */
#include "L298.h"

uint16_t i;

void setup() 
{
    Serial.begin(9600);
    int d = 1000;
    config_pins();
    for(d = 0 ; d < 100 ; d+=10)
      move_tank(d, 0, 1000);
   
}
void loop() 
{
  
}