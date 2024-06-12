/*
 * GPIO Output
 * Some of the GPIO pins are used while booting, so Pulling this pin HIGH or LOW can prevent NODEMCU from booting
 * 
 *  GPIO0: It oscillates and stabilizes HIGH after ~100ms. Boot Failure if pulled LOW
 *  GPIO1: LOW for ~50ms, then HIGH, Boot Failure if Pulled LOW.
 *  GPIO2: It oscillates and stabilize HIGH after ~100ms, Boot Failure if Pulled LOW.
 *  GPIO3: LOW for ~50ms, then HIGH.
 *  GPIO9: Pin is HIGH at Boot.
 *  GPIO10: Pin is HIGH at Boot.
 *  GPIO15: LOW, Boot failure if Pulled HIGH
 *  GPIO16: HIGH during Boot and Falls to ~1Volt.
 *  
 *  
 *  Current circuit:-
 *      Active high switch with pull down resistor on D2
 *      Led on D1
 */

 
uint8_t LED_PIN = D1, SW_PIN = D2;


void setup() 
{
  pinMode(SW_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);   
}

void loop() 
{
    if(digitalRead(SW_PIN) == HIGH)
    {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);            
    }
}
