/*
 * nodeMCU PWM Generation
 * PWM Capable pins:
 * D1   - 
 * D2   - 
 * D3   - 
 * D4   - 
 * D6   - 
 * D7   - 
 * D8   - 
 * RSV  - 
 * 
 * Default PWM frequency = 1000Hz
 * 
 * PWM Functions:-
 * analogWrite(pin, dutycycle): 
 *    Enables software PWM on the specified pin. 
 *    duty cycle is in the range from 0 to PWMRANGE, i.e. 1023 by default.
 *    
 * analogWrite(pin, 0): 
 *    Disables PWM on the specified pin.
 * 
 * analogWriteRange(new_range): 
 *    This function is used to change the PWM range (duty cycle).
 * 
 * analogWriteFreq(new_frequency): 
 *    PWM frequency is 1kHz by default. 
 *    Call this function to change it with new frequency.
 *    PWM frequency is in the range of 1 – 1000Khz.
 */

int x;
void setup() 
{
    Serial.begin(9600);
    analogWrite(D1, 512); // 50% duty cycles
}

void loop() 
{
    for( x = 0 ; x < 1024 ; x++)
    {
        analogWrite(D1, x);
        Serial.print("Current duty cycle :");
        Serial.println(x);
        delay(20);
    }
}
