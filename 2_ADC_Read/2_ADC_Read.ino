/*/
 * ESP8266, got only one analog pin, A0
 * 10-Bit ADC multiplexed with A0 and battery voltage
 * 
 * To select which input to take in the ADC, use,
 * ADC_MODE(mode)
 * Where mode can be,
 *    ADC_TOUT - external voltage
 *    ADC_VCC  - ADC_VCC 
 */
ADC_MODE(ADC_VCC);
int x;
float v;

void setup() 
{
    Serial.begin(9600);
    Serial.println("       ADC Read      ");
    Serial.println("---------------------");
}

void loop() 
{
    sysADC();
}
void extADC()
{
    x = analogRead(A0);
    v = x * 3.3/1023.0;
    Serial.print("ADC Read : ");
    Serial.print(x);
    Serial.print(" | voltage : ");
    Serial.print(v);
    Serial.println("V |");  
}
void sysADC()
{
    x = ESP.getVcc();
    Serial.print("voltage : ");
    Serial.print(x);
    Serial.println("mV |");
}
