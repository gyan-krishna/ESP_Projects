uint8_t GPIO_Pin = D2;
void ICACHE_RAM_ATTR  IntCallback();
void setup() 
{
  Serial.begin(9600);
  Serial.println("NodeMCU interrupts example, active high switch on D2");
  pinMode(16, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin), IntCallback, RISING);
}

void loop() 
{
    
}

void ICACHE_RAM_ATTR IntCallback()
{
  Serial.print("Stamp(ms): ");
  Serial.println(millis());
} 
